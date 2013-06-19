#pragma once

#include <vector>
#include <boost/tokenizer.hpp>
#include <string>
#include <algorithm>


namespace csv {

  std::vector<std::string> parse_line(const std::string& line) {

    boost::tokenizer<boost::escaped_list_separator<char>> tok(line);

    std::vector<std::string> row;
    std::copy(tok.begin(), tok.end(), std::back_inserter(row));

    return row;
  }
}
