/* There are n people that are split into some unknown number of groups. Each
person is labeled with a unique ID from 0 to n - 1.

You are given an integer array groupSizes, where groupSizes[i] is the size of
the group that person i is in. For example, if groupSizes[1] = 3, then person 1
must be in a group of size 3.

Return a list of groups such that each person i is in a group of size
groupSizes[i].

Each person should appear in exactly one group, and every person must be in a
group. If there are multiple answers, return any of them. It is guaranteed that
there will be at least one valid solution for the given input.



Example 1:

Input: groupSizes = [3,3,3,3,3,1,3]
Output: [[5],[0,1,2],[3,4,6]]
Explanation:
The first group is [5]. The size is 1, and groupSizes[5] = 1.
The second group is [0,1,2]. The size is 3, and groupSizes[0] = groupSizes[1] =
groupSizes[2] = 3. The third group is [3,4,6]. The size is 3, and groupSizes[3]
= groupSizes[4] = groupSizes[6] = 3. Other possible solutions are
[[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].

Example 2:

Input: groupSizes = [2,1,3,3,3,2]
Output: [[1],[0,5],[2,3,4]]



Constraints:

    groupSizes.length == n
    1 <= n <= 500
    1 <= groupSizes[i] <= n
 */

#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T> ostream &operator<<(ostream &out, vector<T> &group) {
  out << '[';

  for (int i = 0; i < group.size(); i++) {
    out << group[i];

    if (i != group.size() - 1) {
      out << ", ";
    }
  }

  out << ']';

  return out;
}

int main() {
  vector<int> groupSizes{3, 3, 3, 3, 3, 1, 3}; // Example 1
  groupSizes = {2, 1, 3, 3, 3, 2};             // Example 2

  map<int, vector<vector<int> *> *> groupsMap{};

  for (auto i = 0; i < groupSizes.size(); i++) {
    int groupSize = groupSizes.at(i);

    if (groupsMap.count(groupSize)) {
      int activeVectorIndex = 0;
      bool addedSuccessfully = false;

      while (groupsMap.at(groupSize)->size() > activeVectorIndex &&
             !addedSuccessfully) {
        auto activeVector = groupsMap.at(groupSize)->at(activeVectorIndex);

        if (activeVector->size() < groupSize) {
          activeVector->push_back(i);

          addedSuccessfully = true;
          break;
        }

        activeVectorIndex++;
      }

      if (!addedSuccessfully) {
        groupsMap.at(groupSize)->push_back(new vector<int>{i});
      }
    } else {
      groupsMap.insert(
          make_pair(groupSize, new vector<vector<int> *>{new vector<int>{i}}));
    }
  }

  cout << '[';
  for (auto groups : groupsMap) {
    for (int i = 0; i < groups.second->size(); i++) {
      cout << *groups.second->at(i);

      if (i != groups.second->size() - 1) {
        cout << ',';
      }
    }
  }
  cout << ']';
}