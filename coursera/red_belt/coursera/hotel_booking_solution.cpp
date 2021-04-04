#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Event {
  int64_t time;
  string hotel_name;
  unsigned int client_id;
  int room_count;
};

class BookingManager {
private:
  queue<Event> events;
  map<string, map<uint64_t, uint64_t>> clients;
  map<string, uint64_t> rooms;

  void Adjust(int64_t current_time) {
    while (!events.empty()
           && events.front().time + 86400 <= current_time)
    {
      auto it = events.front();
      clients[it.hotel_name][it.client_id] -= it.room_count;
      if (clients[it.hotel_name][it.client_id] == 0) {
        clients[it.hotel_name].erase(it.client_id);
      }

      rooms[it.hotel_name] -= it.room_count;

      events.pop();
    }
  }

public:
  BookingManager() {}

  void Book(int64_t time, const string& hotel_name,
            unsigned int client_id, int room_count)
  {
    events.push({time, hotel_name, client_id, room_count});
    clients[hotel_name][client_id] += room_count;
    rooms[hotel_name] += room_count;

    Adjust(time);
  }

  uint64_t GetClients(const string& hotel_name) {
    return clients[hotel_name].size();
  }

  uint64_t GetRooms(const string& hotel_name) {
    return rooms[hotel_name];
  }

};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  BookingManager manager;
  int query_count;
  cin >> query_count;

  for (size_t i = 0; i < query_count; ++i) {
    string query_type;
    cin >> query_type;

    string hotel_name;
    if (query_type == "BOOK") {
      uint64_t time;
      unsigned int client_id;
      int room_count;

      cin >> time >> hotel_name
          >> client_id >> room_count;

      manager.Book(time, hotel_name, client_id, room_count);

    } else {
      cin >> hotel_name;
      if (query_type == "CLIENTS") {
        cout << manager.GetClients(hotel_name) << '\n';
      } else if (query_type == "ROOMS") {
        cout << manager.GetRooms(hotel_name) << '\n';
      }
    }
  }

  return 0;
}
