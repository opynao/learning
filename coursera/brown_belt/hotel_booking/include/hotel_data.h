#pragma once

#include "client_data.h"

#include <cstdint>
#include <string>
#include <vector>
#include <deque>

class HotelData
{
public:
    using time_t = int64_t;
    using client_t = int;
    using roomCount_t = int;

public:
    void Update(time_t, client_t, roomCount_t);

    int GetClients(time_t);

    int GetRooms(time_t);

private:
    std::deque<std::pair<time_t, roomCount_t>> time_roomCount_;
    ClientData clientData_;
    roomCount_t roomCount_;
};