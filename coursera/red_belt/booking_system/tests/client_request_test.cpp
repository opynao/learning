#include "gtest/gtest.h"
#include "client_request.h"

class ClientRequestTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    upClientRequest = std::make_unique< ClientRequest >("Marriott");
  }
  std::unique_ptr< ClientRequest > upClientRequest;
};

TEST_F( ClientRequestTest, ConstructWithHotelName )
{
  EXPECT_NE( upClientRequest, nullptr );
}

TEST_F( ClientRequestTest, GetAnswerIfRequestProcessed )
{
  upClientRequest->SetAnswer(0);
  const auto answer = upClientRequest->GetAnswer();
  EXPECT_EQ( answer.has_value(), true );
  EXPECT_EQ( answer.value(), 0 );
}

TEST_F( ClientRequestTest, GetAnswerIfRequestNotProcessed )
{
  EXPECT_EQ( upClientRequest->GetAnswer().has_value(), false );
}
