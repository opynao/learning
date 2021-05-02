#pragma once

#include <http_header.h>

#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>

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