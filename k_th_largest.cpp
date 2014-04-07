#include "includes/utilities.h"
#include "includes/priority-queue.h"

#include <vector>
#include <iostream>

using namespace std;

void swap(int nums[], int ind1, int ind2) {
  int temp = nums[ind1];
  nums[ind1] = nums[ind2];
  nums[ind2] = temp;
}

int pivotShuffle(int nums[], int start, int end) {
  int left = start;
  int right = end;
  int pivot = start;
  int pivot_item = nums[pivot];

  while (left < right) {
    while (nums[left] <= pivot_item) left++;
    while (nums[right] > pivot_item) right--;

    if (left < right) swap(nums, left, right);
  }

  nums[start] = nums[right];
  nums[right] = pivot_item;

  return right;
}

int findKLargestImpl(int nums[], int start, int end, int k) {
  if (end - start <= 1) return nums[start];

  int pivot = pivotShuffle(nums, start, end);
  int rank = pivot - start + 1;

  if (k < rank) {
    return findKLargestImpl(nums, start, pivot-1, k);
    
  }
  else if (k > rank) {
    return findKLargestImpl(nums, pivot+1, end, k - rank);
  }

  return nums[pivot];

}

void findKLargest(int nums[], int len, int k) {
  std::vector<int> arr(nums, nums + len);

  int num = findKLargestImpl(&arr[0], 0, arr.size()-1, k);

  IC::printArray(&arr[0], arr.size());
  cout << "Found " << k << " largest elem :" << num << endl << endl;;
}

void findKLargestMethod2(int nums[], int len, int k) {
  ADM::PriorityQueue heap(nums, len);

  int rank = k;
  int k_th_val = -1;
  while (!heap.empty() && rank >= 1) {
    k_th_val = heap.extract_min();
    cout << k_th_val << " ";

    rank--;
  }
  cout << endl;
  if (rank < 1) {
    cout << "Found " << k << " largest elem :" << k_th_val << endl << endl;;
  }
}

int main() {
  int nums[] = { 4, 4, 9,  5, 2 , 20, 15, 6};
  int len = sizeof(nums) / sizeof(int);

  cout << "Original Array :" << endl;
  IC::printArray(nums, len);

  cout << "Method #1:" << endl;
  findKLargest(nums, len, 1);
  findKLargest(nums, len, 2);
  findKLargest(nums, len, 3);
  findKLargest(nums, len, 4);
  findKLargest(nums, len, 5);

  cout << "Method #2:" << endl;
  findKLargestMethod2(nums, len, 1);
  findKLargestMethod2(nums, len, 2);
  findKLargestMethod2(nums, len, 3);
  findKLargestMethod2(nums, len, 4);
  findKLargestMethod2(nums, len, 5);

  return 0;
}
