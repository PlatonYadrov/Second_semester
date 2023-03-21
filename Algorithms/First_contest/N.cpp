#include <iostream>
#include <string>
#include <queue>
#include <map>

class TrackAndScore {
 public:
  TrackAndScore() {
    track = 0;
    score = 0;
  }
  TrackAndScore(const int64_t& track, const int64_t& score) {
    this->track = track;
    this->score = score;
  }
  int64_t track;
  int64_t score;
  TrackAndScore(const TrackAndScore& other) {
    track = other.track;
    score = other.score;
  }

  TrackAndScore& operator=(const TrackAndScore& other) = default;
};

std::ostream& operator<<(std::ostream& element, const TrackAndScore& trackandscore) {
  element << trackandscore.track << ' ' << trackandscore.score;
  return element;
}

bool operator<(const TrackAndScore& t_1, const TrackAndScore& t_2) {
  if (t_1.score != t_2.score) {
    return t_1.score < t_2.score;
  }
  return t_1.track > t_2.track;
}

int main() {
  std::map<std::string, int64_t> my_map;
  std::map<int64_t, int64_t> my_map_tracks;
  std::priority_queue<TrackAndScore> radio;
  for (int i = 1; i < 100002; ++i) {
    TrackAndScore temp(i, 0);
    radio.push(temp);
    my_map_tracks[i] = 0;
  }
  std::string command;
  std::cin >> command;
  while (command != "EXIT") {
    if (command == "GET") {
      while (radio.top().score != my_map_tracks[radio.top().track]) {
        radio.pop();
      }
      TrackAndScore top;
      top = radio.top();
      std::cout << top << '\n';
      top.score = -1;
      radio.pop();
      radio.push(top);
      my_map_tracks[top.track] = -1;
    }
    if (command == "VOTE") {
      std::string id;
      std::cin >> id;
      int64_t track_id;
      std::cin >> track_id;
      int64_t score;
      std::cin >> score;
      int64_t time;
      std::cin >> time;
      if ((time - my_map[id] >= 600) || (my_map[id] == 0)) {
        my_map[id] = time;
        my_map_tracks[track_id] += score;
        TrackAndScore temp(track_id, my_map_tracks[track_id]);
        radio.push(temp);
        std::cout << my_map_tracks[track_id] << '\n';
      } else {
        std::cout << my_map_tracks[track_id] << '\n';
      }
    }
    std::cin >> command;
  }
  std::cout << "OK";
  return 0;
}
