// Find if str3 is a shuffle of str1 and str2
// The chars of str1 and str2 are interleaved in str3 while preservering the order of each strings
// Two ways to do this
// #1) it O(N+M)  where n = length of str1 and m = length of str2
//     this is more difficult. need to be extra careful for minute details of false negatives and false positives;
//     dont even know if it works for all cases for non unique duplicate chars
// #2 O(N*M) recursion using dynamic programming
//    This will work for sure.
#include <iostream>
#include <string>

using namespace std;

bool findShuffledStringImpl(string const& str1, string const& str2, string const& shuffled) {

  bool visited_map[shuffled.length()];
  int ind1 = 0, ind2 = 0;

  bool str1_passed = false;
  for (int i=0; i<shuffled.length(); ++i) {
    if (ind1 < str1.length() && str1[ind1] == shuffled[i]) {
      visited_map[i] = true;
      ind1++;
    }
    else {
      visited_map[i] = false;
    }
  }
  str1_passed = ind1 == str1.length();

  cout << "Visited Map :";
  for (int i=0; i<shuffled.length(); ++i) {
    cout << visited_map[i];
  }
  cout << endl;

  bool str2_passed = false;
  for (int i=0; i<shuffled.length(); ++i) {
    if (visited_map[i] != true) {
      if (ind2 < str2.length() && str2[ind2] == shuffled[i]) {
        ind2++;
      }
    }
  }
  str2_passed = ind2 == str2.length();

  return (str1_passed && str2_passed);
}

void findShuffledString(string const& str1, string const& str2, string const& shuffled) {
  bool ret = findShuffledStringImpl(str1, str2, shuffled);
  bool ret2 = findShuffledStringImpl(str2, str1, shuffled);

  if (ret || ret2) {
    cout << shuffled << " is a correct shuffle" << endl;
  }
  else {
    cout << shuffled << " is NOT a correct shuffle" << endl;
  }
}

int main() {
  string str1 = "bat";
  string str2 = "pant";

  string str_correct = "pbanatt";
  string str_wrong = "tpbanat";

  findShuffledString(str1, str2, str_correct);
  findShuffledString(str1, str2, str_wrong);
  findShuffledString(str1, str2, "lorrpom");

  return 0;
}
