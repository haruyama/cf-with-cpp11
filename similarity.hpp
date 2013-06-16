#pragma once

#include <set>
#include <vector>
#include <algorithm>

namespace similarity {

  //http://stackoverflow.com/questions/1060648/fast-intersection-of-sets-c-vs-c
  template <typename T, typename OutIter> inline void stl_intersect(const T& set1, const T& set2, OutIter out) {
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), out);
  }

  template<typename T> inline double tanimoto(const std::set<T>* set1, const std::set<T>* set2) {
    std::vector<T> interset;

    std::set_intersection(set1->begin(),set1->end(),
        set2->begin(),set2->end(),
        back_inserter(interset));

    if (interset.empty()) {
      return 0.0;
    }

    return (double(interset.size()))/((set1->size())+(set2->size())-interset.size());
  }

  template<typename T> inline double tanimoto(const std::vector<T>* set1, const std::vector<T>* set2) {
    std::vector<T> interset;

    std::set_intersection(set1->begin(),set1->end(),
        set2->begin(),set2->end(),
        back_inserter(interset));

    if (interset.empty()) {
      return 0.0;
    }

    return (double(interset.size()))/((set1->size())+(set2->size())-interset.size());
  }

  template<typename T> inline double tanimoto(const std::vector<T>& set1, const std::vector<T>& set2) {
    std::vector<T> interset;

    std::set_intersection(set1.begin(),set1.end(),
        set2.begin(),set2.end(),
        back_inserter(interset));

    if (interset.empty()) {
      return 0.0;
    }

    return (double(interset.size()))/((set1.size())+(set2.size())-interset.size());
  }

  template<typename T> inline double tanimoto(const std::set<T>& set1, const std::set<T>& set2) {
    std::set<T> interset;

    std::set_intersection(set1.begin(),set1.end(),
        set2.begin(),set2.end(),
        inserter(interset, interset.begin()));

    if (interset.empty()) {
      return 0.0;
    }

    return (double(interset.size()))/((set1.size())+(set2.size())-interset.size());
  }
}
