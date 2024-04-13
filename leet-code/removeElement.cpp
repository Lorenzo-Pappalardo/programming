#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.cpp"

using namespace std;

int removeElement(vector<int> &nums, int val);

int main()
{
  auto nums1 = vector<int>{3, 2, 2, 3};
  int val1 = 3;

  auto nums2 = vector<int>{0, 1, 2, 2, 3, 0, 4, 2};
  int val2 = 2;

  auto nums3 = vector<int>{2};
  int val3 = 3;

  auto nums4 = vector<int>{4, 5};
  int val4 = 4;

  const auto count1 = removeElement(nums1, val1);
  cout << count1 << endl;
  print(nums1);

  cout << endl;

  const auto count2 = removeElement(nums2, val2);
  cout << count2 << endl;
  print(nums2);

  cout << endl;

  const auto count3 = removeElement(nums3, val3);
  cout << count3 << endl;
  print(nums3);

  cout << endl;

  const auto count4 = removeElement(nums4, val4);
  cout << count4 << endl;
  print(nums4);
}

int removeElement(vector<int> &nums, int val)
{
  int count = 0;

  for (int i = 0; i < nums.size(); i++)
  {
    int j = i + 1;

    while (j <= nums.size())
    {
      if (j == nums.size())
      {
        if (nums.at(i) != val)
        {
          count++;
        }

        break;
      }

      if (nums.at(i) == val)
      {
        const int tmp = nums.at(i);
        nums.at(i) = nums.at(j);
        nums.at(j) = tmp;
        j++;
      }
      else
      {
        count++;
        break;
      }
    }
  }

  return count;
}
