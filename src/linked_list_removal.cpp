#include <iostream>

using namespace std;

struct Node {
  Node (int v) : val(v), next(0) {}
  int val;
  Node* next;
};

Node* createLinkedList(int nums[], int len) {
  Node* head = 0;
  Node* prev_node = 0;

  for (int i=0; i<len; ++i) {
    if (nums[i] == 0) continue;
    Node* node = new Node(nums[i]);
    if (!head) head = node;
    if (prev_node) prev_node->next = node;
    prev_node = node;
  }

  return head;
}

Node* removeElemFrmLinkedList(Node* head, int target) {
  while (head && head->val == target) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }

  if (!head) return head;

  Node* node = head;
  while (node->next != NULL) {
    if (node->next->val == target) {
      Node* temp = node->next;
      node->next = temp->next;
      delete temp;
    }
    else {
      node = node->next;
    }
  };

  return head;
}

void printLinkedList(Node* head) {
  Node* node = head;
  if (node) {
    std::cout << node->val;
    node = node->next;
  }

  while(node) {
    std::cout << " -> " << node->val;
    node = node->next;
  };

  std::cout << std::endl;
}

int main() {
  int target = 5;
  int nums[][6] = { 
    {1},
    {5},
    {1, 2},
    {5, 5, 5},
    {1, 2, 5, 5},
    {1, 2, 5, 5, 3}
  };

  for (int i=0; i<sizeof(nums) / sizeof(nums[0]); ++i) {
    Node* head = createLinkedList(nums[i], sizeof(nums[i]) / sizeof(int) );
    std::cout << "Linked List :";
    printLinkedList(head);

    head = removeElemFrmLinkedList(head, target);

    std::cout << "After removing " << target << std::endl;
    printLinkedList(head);
    std::cout << std::endl;
  }

  return 0;
}
