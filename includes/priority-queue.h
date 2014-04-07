#include <vector>
#include <iostream>

namespace ADM {

namespace {
void swapArrayItem(int array[], int ind1, int ind2) {
  int temp = array[ind1];
  array[ind1] = array[ind2];
  array[ind2] = temp;
}
}

class PriorityQueue {
  enum { PRIORITY_QUEUE_SIZE = 1024 };

public:
  PriorityQueue() : n(0) {
    init();
  }

  void init() {
    //index starts at 1
    n = 0;
    array.resize(PRIORITY_QUEUE_SIZE + 1);
  }

  PriorityQueue(int num_array[], int len) {
    init();
    for (int i=0; i<len; ++i) {
      insert(num_array[i]);
    }
  }

  bool empty() const { return n <= 0; }
  static int get_parent(int index) {
    if (index == 1) return -1; //root
    return (index / 2);
  }

  static int get_left_child(int index) {
    return 2 * index;
  }

  static int get_right_child(int index) {
    return 2 * index + 1;
  }

  void insert(int num) {
    if (n >= PRIORITY_QUEUE_SIZE) {
      std::cerr << "Warning, queue full" << std::endl;
    }
    else {
      array[n+1] = num;
      n++;
      //std::cout << "at n: " << n << std::endl;
      bubble_up(n);
    }
  }

  int extract_min() {
    if (n < 1) {
      std::cerr << "Queue empty" << std::endl;
      return -1;
    }
    else {
      int min = array[1];
      array[1] = array[n];
      n--;
      bubble_down(1);
      return min;
    }
  }

  void bubble_down(int index) {
    if (index >= n) return;

    int left_ind = get_left_child(index);
    int right_ind = get_right_child(index);

    if (n >= left_ind && array[left_ind] < array[right_ind] && 
        array[left_ind] < array[index] ) {
      swapArrayItem(&array[0], index, left_ind);
      bubble_down(left_ind);
    }
    else if (n >= right_ind &&array[right_ind] < array[left_ind] && 
        array[right_ind] < array[index] ) {
      swapArrayItem(&array[0], index, right_ind);
      bubble_down(right_ind);
    }
  }

  void bubble_up(int index) {
    //std::cout << "Bubbling up at index: " << index << std::endl;
    if (index <= 1) return;

    int parent_ind = get_parent(index);
    if (array[parent_ind] > array[index]) {
      swapArrayItem(&array[0], parent_ind, index);
      bubble_up(parent_ind);
    }
  }

public:
    int n;
    std::vector<int> array;
};

int heap_compare(PriorityQueue const& q, int i, int count, int x) {
  if ((count <= 0) || (i > q.n)) return(count);

  if (q.array[i] < x) {
    count = heap_compare(q, PriorityQueue::get_left_child(i), count-1, x);
    count = heap_compare(q, PriorityQueue::get_right_child(i), count, x);
  }

  return count;
}

std::ostream& operator<< (std::ostream& oss, PriorityQueue const& queue) {
  std::cout << "queye size: " << queue.n << std::endl;
  for (int i=1; i<queue.n; ++i) {
    oss << queue.array[i] << std::endl;
  }
  return oss;
}

};
