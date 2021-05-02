#include "comment_server.h"
#include "gtest/gtest.h"
#include "parsed_response.h"

#include <sstream>
#include <iostream>

void TestOfCommentServer(CommentServer &srv, const HttpRequest &request, const ParsedResponse &expected)
{
    std::stringstream ss;
    HttpResponse httpResponse = srv.ServeRequest(request);
    ss << httpResponse;
    ParsedResponse resp;
    ss >> resp;
    EXPECT_EQ(resp.code, expected.code);
    EXPECT_EQ(resp.headers, expected.headers);
    EXPECT_EQ(resp.content, expected.content);
}

TEST(Basic, TestServer)
{
    CommentServer cs;

    const ParsedResponse ok{200};
    const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
    const ParsedResponse not_found{404};

    TestOfCommentServer(cs, {"POST", "/add_user"}, {200, {}, "0"});
    TestOfCommentServer(cs, {"POST", "/add_user"}, {200, {}, "1"});
    TestOfCommentServer(cs, {"POST", "/add_comment", "0 Hello"}, ok);
    TestOfCommentServer(cs, {"POST", "/add_comment", "1 Hi"}, ok);
    TestOfCommentServer(cs, {"POST", "/add_comment", "1 Buy my goods"}, ok);
    TestOfCommentServer(cs, {"POST", "/add_comment", "1 Enlarge"}, ok);
    TestOfCommentServer(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
    TestOfCommentServer(cs, {"POST", "/add_comment", "0 What are you selling?"}, ok);
    TestOfCommentServer(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
    TestOfCommentServer(
        cs,
        {"GET", "/user_comments", "", {{"user_id", "0"}}},
        {200, {}, "Hello\nWhat are you selling?\n"});
    TestOfCommentServer(
        cs,
        {"GET", "/user_comments", "", {{"user_id", "1"}}},
        {200, {}, "Hi\nBuy my goods\nEnlarge\n"});
    TestOfCommentServer(
        cs,
        {"GET", "/captcha"},
        {200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"}});
    TestOfCommentServer(cs, {"POST", "/checkcaptcha", "1 24"}, redirect_to_captcha);
    TestOfCommentServer(cs, {"POST", "/checkcaptcha", "1 42"}, ok);
    TestOfCommentServer(cs, {"POST", "/add_comment", "1 Sorry! No spam any more"}, ok);
    TestOfCommentServer(
        cs,
        {"GET", "/user_comments", "", {{"user_id", "1"}}},
        {200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n"});

    TestOfCommentServer(cs, {"GET", "/user_commntes"}, not_found);
    TestOfCommentServer(cs, {"POST", "/add_uesr"}, not_found);
}