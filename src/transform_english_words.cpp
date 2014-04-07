// Transfrom str1 to str2 by adding/removing/changing 1 letter at a time
// while all the intermediate letters are valid english word
// Given solution below implements just changing 1 letter, implementing other
// is just a matter of adding more case statements
#include "data_structures.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <string>

using namespace std;

typedef std::string Word;
typedef std::set<Word>  Dictionary;
typedef Node<Word> WordVertex;
typedef std::map<Word, WordVertex*> WordGraph;

void printGraph(WordGraph const& g) {
  for (WordGraph::const_iterator it = g.begin(); it != g.end(); ++it) {
    std::cout << ":" << it->first;
    WordVertex* v = it->second;
    while (v != NULL) {
      std::cout << " " << v->val;
      v = v->next;
    }
    std::cout << std::endl;
  }
}

void constructGraph(WordGraph& graph, Dictionary const& dictionary) {
  for (Dictionary::const_iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
   Word word = *it; 
   graph[word] = 0;
   for (int i=0; i<word.length(); ++i) {
     char curr_char = word.at(i);

     for (char c = 'a'; c <= 'z'; ++c) {
       if (c != curr_char) {
         Word newWord(word); 
         newWord.at(i) = c;
         if (dictionary.find(newWord) != dictionary.end()) {
           WordVertex* vertex = new WordVertex(newWord);
           vertex->next = graph[word];
           graph[word] = vertex;
         }
       }
     }

   }

  }
}

typedef map<string, string> ParentMap;

bool bfSearch(WordGraph const& graph, 
              Word const& target, 
              Word const& start, 
              Dictionary& visited_map,
              ParentMap& parent) 
{
  bool ret = false;
  std::stack<Word> frontier;

  frontier.push(start);

  while (!frontier.empty()) {
    std::stack<Word> next;

    while (!frontier.empty()) {
      Word curr_word = frontier.top();
      frontier.pop();

      if (target == curr_word) {
        return true;
      }

      WordGraph::const_iterator it = graph.find(curr_word);
      if (it != graph.end()) {

        WordVertex* v = it->second;
        while (v != NULL) {
          if (visited_map.find(v->val) == visited_map.end()) {
            visited_map.insert(curr_word);
            next.push(v->val);
            parent[v->val] = curr_word;
          }
          v = v->next;
        }
      }
    }
    frontier = next;
  }

  return ret;
}


void findTransformation(Word const& source, Word const& target, WordGraph const& graph) {
  ParentMap parent;
  Dictionary visited_map;

  if (bfSearch(graph, target, source, visited_map, parent)) {
    cout << "Found link from :" << source << " to :" << target << endl;

    const Word* next_node = &target;
    while (next_node) {
      ParentMap::const_iterator it = parent.find(*next_node);
      if (it != parent.end()) {
        cout << it->first << " -> ";
        next_node = &it->second;
      }
      else {
        next_node = 0;
      }
    }
    cout << source << endl;
  }
  else {
    cout << "Not found link from :" << source << " to :" << target << endl;
  }
}

int main() {
  WordGraph graph;
  Dictionary dict;

  dict.insert("bat");
  dict.insert("mat");
  dict.insert("fat");
  dict.insert("cat");
  dict.insert("bot");
  dict.insert("fit");
  dict.insert("fin");
  
  dict.insert("lint");
  dict.insert("mint");

  dict.insert("kite");

  constructGraph(graph, dict);
  printGraph(graph);

  findTransformation("mint", "lint", graph);
  findTransformation("bat", "fin", graph);
  findTransformation("mint", "fin", graph);

  return 0;
}
