// finds if any two num in the array sums to a particular target in O(N)
// shows all the duplicates as well
#include "includes/utilities.h"

#include <set>
#include <iostream>

using namespace std;

typedef std::set<int> NumSet;

void findSumTo(int nums[], int len, int target) {
  NumSet set;

  for (int i=0; i<len; ++i) {
    int second_num = target - nums[i];
    if (set.find(second_num) != set.end()) {
      std::cout << nums[i] << " + " << second_num << " = " << target << std::endl;
    }
    set.insert(nums[i]);
  }
}

int main() 
{
  int nums[] = {5, 4, 3, 9, 1, 5, 2, -3};
  int len = sizeof(nums) / sizeof(int);
  int target = 6;

  IC::printArray(nums, len);

  findSumTo(nums, len, target);

  return 0;
}
