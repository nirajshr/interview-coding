#include <iostream>

namespace IC {
  void printArray(int array[], int len) {
    for (int i=0; i<len; ++i) {
      std::cout << array[i];
      if (i != len-1) std::cout << ", ";
    }
    std::cout << std::endl;
  }
};
