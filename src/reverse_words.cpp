//Reversing words in a sentence while getting rid of
// - leading spaces
// - trailing spaces
// - reducing multiple spaces between words to just one
// NOte: currently, does not get rid of the spaces.
#include <string>
#include <iostream>

using namespace std;

void swap(string& str, int i, int j) {
  char temp = str[i];
  str[i] = str[j];
  str[j] = temp;
}

void reverseString(string& sentence, int start, int end, int dest) {
  int i = start;
  int j = end;

  while (i < j) {
    swap(sentence, i, j);

    ++i; --j;
  }

  memcpy(&sentence[dest], &sentence[start], sizeof(char) * (end-start+1));

}

void reverseWords(string& sentence) {
  reverseString(sentence, 0, sentence.length()-1, 0);
  cout << sentence << endl;

  int read = 0, write = 0;
  int len = sentence.length();

  while (read < len) {
    if (sentence[read] != ' ') {
      int start = read;
      for (;read<len && sentence[read] != ' '; ++read); 

      reverseString(sentence, start, read-1, write);
      write += (read-start);
      sentence[write++] = ' ';
    }
    read++;
  }
  sentence[write-1] = '\0';
}


int main() {
  const char* str = "A very   long word indeed! ";

  string sentence(str);
  cout << sentence << endl;

  reverseWords(sentence);

  cout << "Reverse:" << endl << sentence.c_str() << endl;

  return 0;
}
