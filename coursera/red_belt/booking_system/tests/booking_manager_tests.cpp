#include "gtest/gtest.h"
#include "booking_manager.h"
#include "client_request.h"
#include <memory>

class BookingManagerTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    upBookingManager = std::make_unique< BookingManager >();
  }
  std::unique_ptr< BookingManager > upBookingManager;
};

TEST_F( BookingManagerTest, TestConstruct )
{
  EXPECT_NE( upBookingManager, nullptr );
}

TEST_F( BookingManagerTest, HandleClientRequestNoBookingForHotel )
{
  std::unique_ptr< Request > upRequest = std::make_unique< ClientRequest >( "Marriott" );
  upBookingManager->HandleRequest( upRequest );
  EXPECT_EQ( upRequest->GetAnswer(), 0 );
}

TEST_F( BookingManagerTest, HandleRoomsRequestNoRoomsInHotel )
{
  std::unique_ptr< Request > upRequest = std::make_unique< RoomsRequest >( "Marriott" );
  upBookingManager->HandleRequest( upRequest );
  EXPECT_EQ( upRequest->GetAnswer(), 0 );
}
