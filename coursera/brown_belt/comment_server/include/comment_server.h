#pragma once
#include "http_request.h"
#include "http_response.h"

#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <functional>
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl
#define PR(x) std::cerr << #x << " = " << x << std::endl

class CommentServer
{
public:
    typedef HttpResponse (CommentServer::*pFunc)();
    using functionCall_t = std::unordered_map<std::string, pFunc>;

public:
    HttpResponse ServeRequest(const HttpRequest &req);

private:
    HttpResponse ServePostRequest();
    HttpResponse PostAddUser();
    HttpResponse PostAddComment();
    HttpResponse PostCheckCaptcha();

    HttpResponse ServeGetRequest();
    HttpResponse GetCaptcha();
    HttpResponse GetUserComments();

    HttpResponse Serve(const std::string &request, const functionCall_t &m);

private:
    functionCall_t PostGetReq{
        {"POST", &CommentServer::ServePostRequest},
        {"GET", &CommentServer::ServeGetRequest}};

    functionCall_t PostRequests{
        {"/add_comment", &CommentServer::PostAddComment},
        {"/add_user", &CommentServer::PostAddUser},
        {"/checkcaptcha", &CommentServer::PostCheckCaptcha}};

    functionCall_t GetRequests{
        {"/user_comments", &CommentServer::GetUserComments},
        {"/captcha", &CommentServer::GetCaptcha}};

private:
    HttpRequest req_;
    std::vector<std::vector<std::string>> comments_;
    std::optional<LastCommentInfo> last_comment;
    std::unordered_set<size_t> banned_users;
};