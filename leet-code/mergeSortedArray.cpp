#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.cpp"

using namespace std;

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n);

int main()
{
  auto nums1 = vector<int>{4, 5, 6, 0, 0, 0};
  const auto m = 3;
  auto nums2 = vector<int>{1, 2, 3};
  const auto n = 3;

  merge(nums1, m, nums2, n);

  print(nums1);
}

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
  for (int i = 0; i < m; i++)
  {
    int j = 0;

    while (j < n)
    {
      if (nums1.at(i) > nums2.at(j))
      {
        const auto tmp = nums2.at(j);
        nums2.at(j) = nums1.at(i);
        nums1.at(i) = tmp;
      }

      j++;
    }

    sort(nums2.begin(), nums2.end());
  }

  for (int i = 0; i < n; i++)
  {
    nums1.at(m + i) = nums2.at(i);
  }
}
