#include <iostream>
#include <vector>
#include <map>
#include <boost/foreach.hpp>
#include <cstdlib>
#include <algorithm>

#include "similarity.hpp"
#include "csv.hpp"

static const size_t MAX_RELATED =10;

typedef long item_type;
typedef std::vector<std::vector<item_type>> user_items;
typedef std::map<item_type, std::vector<size_t>> item_users;

void printout_score(item_type item_id, const std::vector<std::pair<item_type, double>>& scores) {

  std::cout << item_id << ':';
  BOOST_FOREACH(auto score_detail, scores) {
    std::cout << score_detail.second << '|' << score_detail.first << ',';
  }
  std::cout << std::endl;
}

void top_matches(const std::map<item_type, std::vector<size_t>>&  items, const size_t max_items) {

  BOOST_FOREACH(auto item1, items) {
    std::vector<std::pair<item_type, double>> scores;

    BOOST_FOREACH(auto item2, items) {
      if (item1.first == item2.first) {
        continue;
      }

      auto score = similarity::tanimoto(item1.second, item2.second);
      if (score > 0) {
        scores.push_back(std::pair<item_type, double>(item2.first, score));
      }
    }

    if (!scores.empty()) {
      if (scores.size() > max_items) {
        partial_sort(scores.begin(), scores.begin() + max_items, scores.end(),
            [](std::pair<item_type,double> a, std::pair<item_type, double> b) {
            return a.second > b.second;
            });

        scores.erase(scores.begin() + max_items, scores.end());
      } else {
        sort(scores.begin(), scores.end(),
            [](std::pair<item_type,double> a, std::pair<item_type, double> b) {
            return a.second > b.second;
            });
      }
      printout_score(item1.first, scores);
    }
  }
}

static void transform_prefs(const user_items& users, item_users& items) {

  auto user = 0;

  BOOST_FOREACH(auto item_vector, users) {
    BOOST_FOREACH(auto item_id, item_vector){
      if (items.find(item_id) == items.end()) {
        items[item_id] = std::vector<size_t>();
      }
      items[item_id].push_back(user);
    }
    ++user;
  }
}

int main(void) {

  user_items users;
  item_users items;

  std::string line;
  while(std::getline(std::cin,line)) {
    auto row = csv::parse_line(line);
    std::vector<item_type> item_vector;
    std::transform(row.begin() + 1, row.end(), std::back_inserter(item_vector),
        [](std::string& s){ return std::atol(s.c_str()); });
    item_vector.erase(std::remove(item_vector.begin(), item_vector.end(), 0), item_vector.end());
    users.push_back(item_vector);
  }

  transform_prefs(users, items);

  top_matches(items, MAX_RELATED);
  return 0;
}
