#include "http_response.h"
#include "comment_server.h"
#include <sstream>

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
    /*     std::stringstream ss;
    ss << output.rdbuf();
    PR(ss.str());
 */
    return output;
}