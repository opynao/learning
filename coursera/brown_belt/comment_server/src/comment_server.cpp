
#include "comment_server.h"

using namespace std;

HttpResponse CommentServer::ServeRequest(const HttpRequest &req)
{
  req_ = std::move(req);
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
    return HttpResponse(HttpCode::NotFound);
}

HttpResponse CommentServer::PostAddUser()
{
  comments_.emplace_back();
  return HttpResponse(HttpCode::Ok).SetContent(std::to_string(comments_.size() - 1));
}

HttpResponse CommentServer::PostAddComment()
{
  auto [user_id, comment] = ParseIdAndContent(req_.body);

  if (!last_comment || last_comment->user_id != user_id)
    last_comment = LastCommentInfo{user_id, 1};

  else if (++last_comment->consecutive_count > 3)
    banned_users.insert(user_id);

  if (banned_users.count(user_id) == 0)
  {
    comments_[user_id].push_back(string(comment));
    return HttpResponse(HttpCode::Ok);
  }
  else
    return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
}

HttpResponse CommentServer::PostCheckCaptcha()
{
  if (auto [id, response] = ParseIdAndContent(req_.body); response == "42")
  {
    banned_users.erase(id);
    if (last_comment && last_comment->user_id == id)
      last_comment.reset();
    return HttpResponse(HttpCode::Ok);
  }
  else
    return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
}

HttpResponse CommentServer::GetCaptcha()
{
  std::string response = "What's the answer for The Ultimate Question of Life, the Universe, and Everything?";
  return HttpResponse(HttpCode::Ok).SetContent(response);
}

HttpResponse CommentServer::GetUserComments()
{
  auto user_id = FromString<size_t>(req_.get_params.at("user_id"));
  std::string response{};
  for (const std::string &c : comments_[user_id])
    response += c + '\n';
  return HttpResponse(HttpCode::Ok).SetContent(response);
}