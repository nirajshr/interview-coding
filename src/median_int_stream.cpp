// Finds the median of integer stream. Real time Median finder
// Complexity: O[Log(N)] to insert
//             O[1]      to find median
// Uses two heaps (a max heap + min heap)
#include "priority-queue.h"

#include <iostream>

using namespace std;

class MedianStream {
public:

  void insert(int num) {
    int min_size = min_h.size();
    int max_size = max_h.size();

    if (max_size <= min_size) {
      if (min_h.size() && num >= min_h.min()) {
         min_h.insert(num); 
         num = min_h.extract_min();
      }
      max_h.insert(num);
    }
    else if (min_size < max_size){
      if (max_h.size() && num <= max_h.max()) {
        max_h.insert(num);
        num = max_h.extract_max();
      }
      min_h.insert(num);
    }
  }

  size_t size() const { return min_h.size() + max_h.size(); }
  double getMedian() const {
    if (size() % 2 == 0) {
      return (min_h.min() + max_h.max()) / 2.0;
    }
    else {
      return max_h.max();
    }

    return -1;
  }

private:
  ADM::MinHeap min_h;
  ADM::MaxHeap max_h;
};

int main() {
  int nums[] = { 20, 44, 9, 18, 3, 7, 14, 4, 6 };
  int len = sizeof(nums) / sizeof(int);

  ADM::MinHeap min_h(nums, len);
  ADM::MaxHeap max_h(nums, len);

  cout << "MinHeap :" << min_h << endl;
  cout << "Min :" << min_h.min() << endl;

  cout << "MaxHeap :" << max_h << endl;
  cout << "Max :" << max_h.max() << endl;

  MedianStream s;
  for (int i=0; i<len; ++i) {
    s.insert(nums[i]);
  }

  cout << "Median for size N=" << s.size() 
       << ", is :" << s.getMedian() << endl;


  MedianStream ss;
  int num;

  cout << "Get real time median info" << endl;
  cout << "Input a Number :";

  do {
    cin >> num;
    ss.insert(num);
    cout << "Median for size N=" << ss.size() 
         << ", is :" << ss.getMedian() << endl;
  } while (cin.good());

  return 0;
}

