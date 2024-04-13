#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "utils.cpp"

using namespace std;

int majorityElement(vector<int> &nums);

int main()
{
  vector<int> nums1 = {1, 2, 2, 3, 3, 3};
  vector<int> nums2 = {4, 5, 5, 5, 6};

  cout << majorityElement(nums1) << endl;
  cout << majorityElement(nums2) << endl;
}

int majorityElement(vector<int> &nums)
{
  auto pairs = vector<Pair<int, int>>();

  for (auto &&element : nums)
  {
    bool updated = false;

    for (auto &&pair : pairs)
    {
      if (pair.key == element)
      {
        pair.value++;
        updated = true;
      }
    }

    if (!updated)
    {
      Pair<int, int> pair = {element, 1};
      pairs.push_back(pair);
    }
  }

  print(pairs) << endl;

  Pair<int, int> &majorityElement = pairs.at(0);
  for (auto &&pair : pairs)
  {
    if (majorityElement.value < pair.value)
    {
      majorityElement = pair;
    }
  }

  return majorityElement.key;
}
