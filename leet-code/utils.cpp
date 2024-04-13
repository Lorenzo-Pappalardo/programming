#include <iostream>
#include <vector>

using namespace std;

template <typename T>
ostream &print(vector<T> &v)
{
  cout << '[';
  for (auto &&i : v)
  {
    cout << i << ' ';
  }
  cout << ']';

  return cout;
}

template <typename T, typename K>
struct Pair
{
  T key;
  K value;
};

template <typename T, typename K>
ostream &print(vector<Pair<T, K>> &pairs)
{
  cout << '[';
  for (auto &&pair : pairs)
  {
    cout << "Key: " << pair.key << ", value: " << pair.value << ' ';
  }
  cout << ']';

  return cout;
}
