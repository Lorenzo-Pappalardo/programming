#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.cpp"

using namespace std;

const bool extraLoggingEnabled = false;
int removeDuplicates(vector<int> &nums);

int main()
{
  vector<int> nums1 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  vector<int> nums2 = {1, 2, 2};
  vector<int> nums3 = {-1, 0, 0, 0, 0, 3, 3};

  const int k1 = removeDuplicates(nums1);
  const int k2 = removeDuplicates(nums2);
  const int k3 = removeDuplicates(nums3);

  cout << "k1: " << k1 << endl;
  cout << "k2: " << k2 << endl;
  cout << "k3: " << k3 << endl;

  print(nums1) << endl;
  print(nums2) << endl;
  print(nums3) << endl;
}

int removeDuplicates(vector<int> &nums)
{
  if (nums.size() == 0)
  {
    return 0;
  }

  int k = 1;

  for (int i = k; i < nums.size(); i++)
  {
    if (extraLoggingEnabled)
      cout << "k: " << k << ", i: " << i << endl;

    if (nums[i] > nums[i - 1] && nums[i] > nums[k - 1])
    {
      const int tmp = nums[i];
      nums[i] = nums[k];
      nums[k++] = tmp;
    }

    if (extraLoggingEnabled)
      print(nums) << endl;
  }

  return k;
}
