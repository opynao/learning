/*#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <map>
#include <functional>
#include <sstream>

struct HttpHeader
{
    HttpHeader(const std::string &n, const std::string &v)
        : name{n}, value{v}
    {
    }
    std::string name;
    std::string value;
};

std::ostream &operator<<(std::ostream &output, const HttpHeader &h);

struct HttpRequest
{
std::string method{};
std::string path{};
std::string body{};
std::map<std::string, std::string> get_params{};
}
;

struct LastCommentInfo
{
    size_t user_id;
    size_t consecutive_count;
};

std::pair<std::string, std::string> SplitBy(const std::string &what, const std::string &by);

template <typename T>
T FromString(const std::string &s);

std::pair<size_t, std::string> ParseIdAndContent(const std::string &body);

using namespace std;

pair<string, string> SplitBy(const string &what, const string &by)
{
    size_t pos = what.find(by);
    if (by.size() < what.size() && pos < what.size() - by.size())
        return {what.substr(0, pos), what.substr(pos + by.size())};

    else
        return {what, {}};
}

template <typename T>
T FromString(const string &s)
{
    T x;
    istringstream is(s);
    is >> x;
    return x;
}

pair<size_t, string> ParseIdAndContent(const string &body)
{
    auto [id_string, content] = SplitBy(body, " ");
    return {FromString<size_t>(id_string), content};
}
bool operator==(const HttpHeader &lhs, const HttpHeader &rhs);
enum class HttpCode
{
    Ok = 200,
    NotFound = 404,
    Found = 302,
};

class HttpResponse
{
public:
    HttpResponse() {}
    explicit HttpResponse(const HttpCode &code);

    HttpResponse &AddHeader(const std::string &name, const std::string &value);
    HttpResponse &SetContent(const std::string &a_content);
    HttpResponse &SetCode(const HttpCode &a_code);

    friend std::ostream &operator<<(std::ostream &output, const HttpResponse &resp);

    std::string PrintHttpCode() const;

private:
    int AsInteger() const;
    std::unordered_map<HttpCode, std::string> HttpCodeIntoString{
        {HttpCode::Ok, "OK"},
        {HttpCode::NotFound, "Not found"},
        {HttpCode::Found, "Found"}};

private:
    HttpCode code_{};
    std::vector<HttpHeader> headers_{};
    std::string content_{};
};

HttpResponse::HttpResponse(const HttpCode &code)
    : code_{code}
{
}

HttpResponse &HttpResponse::AddHeader(const std::string &name, const std::string &value)
{
    HttpHeader httpHeader(name, value);
    headers_.push_back(httpHeader);
    return *this;
}

HttpResponse &HttpResponse::SetContent(const std::string &a_content)
{
    content_ += a_content;
    return *this;
}

HttpResponse &HttpResponse::SetCode(const HttpCode &a_code)
{
    code_ = a_code;
    return *this;
}

int HttpResponse::AsInteger() const
{
    return static_cast<int>(code_);
}

std::string HttpResponse::PrintHttpCode() const
{
    return HttpCodeIntoString.at(code_);
}

std::ostream &operator<<(std::ostream &output, const HttpResponse &resp)
{
    output << "HTTP/1.1 " << resp.AsInteger() << " " << resp.PrintHttpCode() << std::endl;

    for (auto &header : resp.headers_)
        output << header.name << ": " << header.value << std::endl;
    if (!resp.content_.empty())
        output << "Content-Length: " << resp.content_.size() << "\n\n"
               << resp.content_;
    else
        output << "\n";
    return output;
}

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

    HttpResponse ServeRequestNotFound() const;

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

HttpResponse CommentServer::ServeRequest(const HttpRequest &req)
{
    req_ = req;
    return Serve(req_.method, PostGetReq);
}

HttpResponse CommentServer::ServePostRequest()
{
    return Serve(req_.path, PostRequests);
}

HttpResponse CommentServer::ServeGetRequest()
{
    return Serve(req_.path, GetRequests);
}

HttpResponse CommentServer::Serve(const std::string &request, const functionCall_t &m)
{
    auto itFunc = m.find(request);
    if (itFunc != m.cend())
        return (this->*itFunc->second)();

    else
        return ServeRequestNotFound();
}

HttpResponse CommentServer::PostAddUser()
{
    HttpResponse httpResponse(HttpCode::Ok);
    comments_.emplace_back();
    auto response = to_string(comments_.size() - 1);
    httpResponse.SetContent(response);
    return httpResponse;
}

HttpResponse CommentServer::PostAddComment()
{
    HttpResponse httpResponse;

    auto [user_id, comment] = ParseIdAndContent(req_.body);

    if (!last_comment || last_comment->user_id != user_id)
        last_comment = LastCommentInfo{user_id, 1};

    else if (++last_comment->consecutive_count > 3)
        banned_users.insert(user_id);

    if (banned_users.count(user_id) == 0)
    {
        comments_[user_id].push_back(string(comment));
        httpResponse.SetCode(HttpCode::Ok);
    }
    else
        httpResponse.SetCode(HttpCode::Found).AddHeader("Location", "/captcha");

    return httpResponse;
}

HttpResponse CommentServer::PostCheckCaptcha()
{
    HttpResponse httpResponse;
    if (auto [id, response] = ParseIdAndContent(req_.body); response == "42")
    {
        banned_users.erase(id);
        if (last_comment && last_comment->user_id == id)
            last_comment.reset();
        httpResponse.SetCode(HttpCode::Ok);
    }
    else
        httpResponse.SetCode(HttpCode::Found).AddHeader("Location", "/captcha");

    return httpResponse;
}

HttpResponse CommentServer::ServeRequestNotFound() const
{
    HttpResponse httpResponse(HttpCode::NotFound);
    return httpResponse;
}

HttpResponse CommentServer::GetCaptcha()
{
    HttpResponse httpResponse(HttpCode::Ok);
    std::string response = "What's the answer for The Ultimate Question of Life, the Universe, and Everything?";
    httpResponse.SetContent(response);
    return httpResponse;
}

HttpResponse CommentServer::GetUserComments()
{
    HttpResponse httpResponse(HttpCode::Ok);
    auto user_id = FromString<size_t>(req_.get_params.at("user_id"));
    std::string response{};
    for (const std::string &c : comments_[user_id])
        response += c + '\n';
    httpResponse.SetContent(response);
    return httpResponse;
}
*/
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

using namespace std;

enum class HttpCode
{
    Ok = 200,
    NotFound = 404,
    Found = 302,
};

struct HttpHeader
{
    string name, value;
};

struct ParsedResponse
{
    int code;
    vector<HttpHeader> headers;
    string content;
};

class HttpResponse
{
public:
    explicit HttpResponse(HttpCode code);

    HttpResponse &AddHeader(string name, string value);
    HttpResponse &SetContent(string a_content);
    HttpResponse &SetCode(HttpCode a_code);

    friend ostream &operator<<(ostream &output, const HttpResponse &resp);

private:
    ParsedResponse response_;
    const string ADDR_HEAD = "HTTP/1.1";
};

struct HttpRequest
{
    string method, path, body;
    map<string, string> get_params;
};

pair<string, string> SplitBy(const string &what, const string &by)
{
    size_t pos = what.find(by);
    if (by.size() < what.size() && pos < what.size() - by.size())
    {
        return {what.substr(0, pos), what.substr(pos + by.size())};
    }
    else
    {
        return {what, {}};
    }
}

template <typename T>
T FromString(const string &s)
{
    T x;
    istringstream is(s);
    is >> x;
    return x;
}

pair<size_t, string> ParseIdAndContent(const string &body)
{
    auto [id_string, content] = SplitBy(body, " ");
    return {FromString<size_t>(id_string), content};
}

struct LastCommentInfo
{
    size_t user_id, consecutive_count;
};

class CommentServer
{
public:
    void ServeRequest(const HttpRequest &req, ostream &os)
    {
        os << ServeRequest(req) << "\n";
    }

    HttpResponse ServeRequest(const HttpRequest &req)
    {
        HttpResponse response(HttpCode::NotFound);

        if (req.method == "POST")
        {
            if (req.path == "/add_user")
            {
                auto userId = users_.size();
                users_[userId];
                response.SetCode(HttpCode::Ok).SetContent(to_string(userId));
            }
            else if (req.path == "/add_comment")
            {
                auto [userId, comment] = ParseIdAndContent(req.body);
                if (users_.at(userId).isBanned_)
                {
                    lastComment_ = {userId, 4};
                    response.SetCode(HttpCode::Found).AddHeader("Location", "/captcha");
                }
                else if (lastComment_ && lastComment_->user_id == userId)
                {
                    ++lastComment_->consecutive_count;
                    if (lastComment_->consecutive_count > SPAM_LIMIT)
                    {
                        // user is spammer
                        users_[userId].isBanned_ = true;
                        response.SetCode(HttpCode::Found).AddHeader("Location", "/captcha");
                    }
                    else
                    {
                        users_[userId].comments_.push_back(move(comment));
                        response.SetCode(HttpCode::Ok);
                    }
                }
                else
                {
                    lastComment_ = {userId, 1};
                    users_[userId].comments_.push_back(move(comment));
                    response.SetCode(HttpCode::Ok);
                }
            }
            else if (req.path == "/checkcaptcha")
            {
                auto [userId, answer] = ParseIdAndContent(req.body);
                if (answer == "42")
                {
                    users_.at(userId).isBanned_ = false;

                    if (lastComment_ && lastComment_->user_id == userId)
                    {
                        lastComment_->consecutive_count = 0;
                    }

                    response.SetCode(HttpCode::Ok);
                }
                else
                {
                    response.SetCode(HttpCode::Found).AddHeader("Location", "/captcha");
                }
            }
        }
        else if (req.method == "GET")
        {
            if (req.path == "/user_comments")
            {
                auto userId = FromString<size_t>(req.get_params.at("user_id"));

                string content;
                for (const auto &comment : users_.at(userId).comments_)
                {
                    content += comment + '\n';
                }

                response.SetCode(HttpCode::Ok).SetContent(content);
            }
            else if (req.path == "/captcha")
            {
                string question(
                    "What's the answer for The Ultimate Question of"
                    " Life, the Universe, and Everything?");
                response.SetCode(HttpCode::Ok).SetContent(question);
            }
        }

        return response;
    }

private:
    const size_t SPAM_LIMIT = 3;

    struct UserInfo
    {
        bool isBanned_ = false;

        vector<string> comments_;
    };

    unordered_map<size_t, UserInfo> users_;
    optional<LastCommentInfo> lastComment_;
};

ostream &operator<<(ostream &output, const HttpHeader &h)
{
    return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader &lhs, const HttpHeader &rhs)
{
    return lhs.name == rhs.name && lhs.value == rhs.value;
}

istream &operator>>(istream &input, ParsedResponse &r)
{
    string line;
    getline(input, line);

    {
        istringstream code_input(line);
        string dummy;
        code_input >> dummy >> r.code;
    }

    size_t content_length = 0;

    r.headers.clear();
    while (getline(input, line) && !line.empty())
    {
        if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length")
        {
            istringstream length_input(value);
            length_input >> content_length;
        }
        else
        {
            r.headers.push_back({std::move(name), std::move(value)});
        }
    }

    r.content.resize(content_length);
    input.read(r.content.data(), r.content.size());
    return input;
}

HttpResponse::HttpResponse(HttpCode code)
    : response_{static_cast<int>(code), {}, string()} {}

HttpResponse &HttpResponse::AddHeader(string name, string value)
{
    response_.headers.push_back({move(name), move(value)});
    return *this;
}

HttpResponse &HttpResponse::SetContent(string a_content)
{
    response_.content = move(a_content);
    return *this;
}

HttpResponse &HttpResponse::SetCode(HttpCode a_code)
{
    response_.code = static_cast<int>(a_code);
    return *this;
}

ostream &operator<<(ostream &output, const HttpResponse &resp)
{
    output << resp.ADDR_HEAD << " " << resp.response_.code << " ";

    switch (static_cast<HttpCode>(resp.response_.code))
    {
    case HttpCode::Ok:
        output << "OK";
        break;
    case HttpCode::Found:
        output << "Found";
        break;
    case HttpCode::NotFound:
        output << "Not found";
        break;
    default:
        throw invalid_argument("Unknown http code");
        break;
    }
    output << "\n";

    for (const auto &header : resp.response_.headers)
    {
        output << header << "\n";
    }

    if (!resp.response_.content.empty())
    {
        output << "Content-Length: " << resp.response_.content.size() << "\n\n";
        output << resp.response_.content;
    }
    else
    {
        output << "\n";
    }

    return output;
}

int main()
{
    return 0;
}