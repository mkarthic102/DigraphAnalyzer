#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <utility> // where pair is defined
#include "digraph_functions.h"
#include <algorithm>
#include <sstream>


using std::cout;
using std::cin;
using std::string;
using std::map;
using std::vector;
using std::pair;
using std::make_pair;
using std::ifstream;
using std::endl;
using std::sort;
using std::reverse;
using std::stringstream;
using std::isdigit;
using std::stoi;



int main(int argc, char * argv[]) {
  // if number of arguments is not correct, exit with code 1!
  if (argc != 3) {
    cout << "Invalid arguments";
    return 1;
  }

  // if the "order" argument is not valid, exit with code 1!
  char* order(argv[2]);
  if (*order != 'r' && *order != 'a' && *order != 'c') {
    cout << "Invalid arguments";
    return 1;
  }

  // TODO: WRITE CODE

  // opens the input file and assigns the number of digraphs/trigraphs to a variable
  ifstream ifile(argv[1]);
  int num_graphs;
  ifile >> num_graphs;

  // map with key (digraphs/trigraphs) and value (pair containing a vector of strings and a count)
  map<string, pair<vector<string>, int>> words_with_graphs;
  vector<string> v_graphs;

  // adds digraphs/trigraphs, words with digraphs/trigraphs, and count of digraphs/trigraphs into map
  initialize_map(words_with_graphs, v_graphs, num_graphs, ifile);
  add_words_to_map(words_with_graphs, v_graphs, num_graphs, ifile);

  // prints digraphs/trigraphs and their containing words as specified by the user
  switch(*order) {
    case 'a':
      print_ASCII_order(words_with_graphs);
      break;
    case 'r':
      print_reverse_ASCII_order(words_with_graphs);
      break;
    case 'c':
      print_based_on_count(words_with_graphs, num_graphs);
      break;
  }

  cout << "q?>";

  // takes in user input
  string token;
  while (cin >> token) {
    // exits the program
    if (token.compare("exit") == 0) {
      return 0;
    }
    // prints out digraphs/trigraphs with the same count and their associated words
    else if (isdigit(token[0])) {
      print_graphs_with_same_count(words_with_graphs, stoi(token));
    }
    // prints out the count and associated words of digraphs/trigraphs with the user-specified count
    else {
      print_graph_count(words_with_graphs, token);
    }
  }
  return 0;
}

// initializes the keys and their associated value in the map
void initialize_map(map<string, pair<vector<string>, int>>& words_with_graphs, vector<string>& v_graphs, int num_graphs, ifstream& ifile) {
  int initial_count = 0;
  string graph = "";
  vector<string> v_empty;
  for (int i = 0; i < num_graphs; i++) {
    ifile >> graph;
    graph = make_lowercase(graph);
    v_graphs.push_back(graph);
    words_with_graphs[graph] = make_pair(v_empty, initial_count);
  }
}

// updates the value (pair containing vector and count) associated with each key in the map
void add_words_to_map(map<string, pair<vector<string>, int>>& words_with_graphs, vector<string>& v_graphs, int num_graphs, ifstream& ifile) {
  string word = "";
  string graph = "";
  while (ifile >> word) {
    word = format_word(word); // makes word lower case and removes punctuation
    for (int i = 0; i < num_graphs; i++) {
      graph = v_graphs[i]; 
      if (word.find(graph) != (size_t) -1) {
        words_with_graphs[graph].first.push_back(word);
        words_with_graphs[graph].second += 1;
      }
    }
  }
}

// makes digraph/trigraph lower case
string make_lowercase(string word) {
  for (size_t i = 0; i < word.length(); i++) {
    word[i] = tolower(word[i]);
  }
  return word;
}

// makes word in input file lower case and removes punctuation
string format_word(string word) {
  size_t length = word.length();

  for (size_t i = 0; i < length; i++) {
    // checks for punctation
    if (ispunct(word[i])) {
      word.erase(i--, 1);
      length = word.length(); // updates length of word
    }
  }
  return make_lowercase(word);
}

// prints the digraphs/trigraphs in ASCII order and their containing words
void print_ASCII_order(map<string, pair<vector<string>, int>>& words_with_graphs) {
  for (map<string, pair<vector<string>, int>>::const_iterator it = words_with_graphs.cbegin(); it != words_with_graphs.cend(); it++) {
    cout << it->first << ": [";
    for (vector<string>::const_iterator p = it->second.first.cbegin(); p != it->second.first.cend(); p++) {
      if (p == it->second.first.cend() - 1) {
        cout << *p;
      }
      else {
        cout << *p << ", ";
      }
    }
    cout << "]" << endl;
  }
}

// prints the digraphs/trigraphs in reverse ASCII order and their containing words
void print_reverse_ASCII_order(map<string, pair<vector<string>, int>>& words_with_graphs) {
  for (map<string, pair<vector<string>, int>>::const_reverse_iterator it = words_with_graphs.crbegin(); it != words_with_graphs.crend(); it++) {
    cout << it->first << ": [";
    for (vector<string>::const_iterator p = it->second.first.cbegin(); p != it->second.first.cend(); p++) {
      if (p == it->second.first.cend() - 1) {
        cout << *p;
      }
      else {
        cout << *p << ", ";
      }
    }
    cout << "]" << endl;
  }
}

// initializes two vectors that are necessary in printing digraphs/trigraphs in count order if the user inputs c in the command line
void initialize_vectors(map<string, pair<vector<string>, int>> words_with_graphs, int num_graphs, vector<pair<int, string>>& graph_counts, vector<int>& counts) {
  for (int i = 0; i < num_graphs; i++) {
    graph_counts.push_back(make_pair(0, ""));
    counts.push_back(0);
  }

  // adds count and digraph/trigraph into pairs within vector
  int index = 0;
  for (map<string, pair<vector<string>, int>>::const_reverse_iterator it = words_with_graphs.crbegin(); it != words_with_graphs.crend(); it++) {
    graph_counts[index].first = it->second.second;
    graph_counts[index].second = it->first;
    counts[index] = it->second.second;
    index++;
  }
}

// rearranges digraphs/trigraphs with the same number of occurrences (count) based on ASCII if the user inputs c in the command line
void break_ties(vector<pair<int, string>>& graph_counts, vector<int> counts) {
  
  // first index in graph_counts for which the count of the digraph/trigraph is the same
  int start_index = 0;

  // only true if start_index has been updated
  bool set_start_index = false;

  // breaks ties by sorting digraphs/trigraphs with the same count in ASCII order
  for (size_t i = 0; i < counts.size(); i++) {
    // initializes a vector that will store digraphs/trigraphs with the same count
    vector<pair<string, int>> temp;
    for (size_t j = 0; j < graph_counts.size(); j++) {
      if (counts[i] == graph_counts[j].first) {
        temp.push_back(make_pair(graph_counts[j].second, graph_counts[j].first));
        if (!set_start_index) {
          start_index = j;
          set_start_index = true;
        }
      }
    }
    // if temp contains more than one digraph/trigraph with the same count, then temp will be sorted based on ASCII of digraph/trigraph
    if (temp.size() > 1) {
      // sorts temp based on ASCII order
      sort(temp.begin(), temp.end());
      for (size_t index = 0; index < temp.size(); index++) {
        // replaces current order of digraphs/trigraphs with the same count in graph_counts to new, sorted order in temp
        graph_counts[start_index].first = temp[index].second;
        graph_counts[start_index].second = temp[index].first;
        start_index++;
      }
    }
    set_start_index = false;
    start_index = 0;
  }
}

// prints the digraphs/trigraphs based on their number of occurences from largest to smallest
void print_based_on_count(map<string, pair<vector<string>, int>>& words_with_graphs, int num_graphs) {

  // initializes two vectors
  vector<pair<int, string>> graph_counts; // will contain each count and digraph/trigraph
  vector<int> counts; // will only contain the count
  initialize_vectors(words_with_graphs, num_graphs, graph_counts, counts);

  // sorts digraphs/trigraphs in descending order based on number of occurences and breaks ties by ASCII order
  sort(graph_counts.begin(), graph_counts.end());
  reverse(graph_counts.begin(), graph_counts.end());
  break_ties(graph_counts, counts);

  // prints digraphs/trigraphs from largest to smallest number of occurrences
  string graph = "";
  for (size_t i = 0; i < graph_counts.size(); i++) {
    graph = graph_counts[i].second;
    cout << graph << ": [";
    pair<vector<string>, int> map_value = words_with_graphs[graph];
    for (vector<string>::const_iterator p = map_value.first.cbegin(); p != map_value.first.cend(); p++) {
      if (p == map_value.first.cend() - 1) {
        cout << *p;
      }
      else {
        cout << *p << ", ";
      }
    }
    cout << "]" << endl; 
  }

}

// prints the digraphs/trigraphs with the same count and their associated words
void print_graphs_with_same_count(map<string, pair<vector<string>, int>> words_with_graphs, int number) {
  bool graph_exists = false;
  for (map<string, pair<vector<string>, int>>::const_iterator it = words_with_graphs.cbegin(); it != words_with_graphs.cend(); it++) {
    // determines if the count of the digraph/trigraph is equal to the user-inputted count
    if (it->second.second == number) {
      graph_exists = true;
      cout << it->first << ": [";
      for (vector<string>::const_iterator p = it->second.first.cbegin(); p != it->second.first.cend(); p++) {
        if (p == it->second.first.cend() - 1) {
          cout << *p;
        }
        else {
          cout << *p << ", ";
        }
      }
      cout << "]" << endl;
    }
  }
  if (!graph_exists) {
    cout << "None" << endl;
  }
  cout << "q?>";
}

// prints the count and associated words if user inputs a digraph/trigraph
void print_graph_count(map<string, pair<vector<string>, int>> words_with_graphs, string graph) {
  bool graph_exists = false;
  graph = make_lowercase(graph);
  for (map<string, pair<vector<string>, int>>::const_iterator it = words_with_graphs.cbegin(); it != words_with_graphs.cend(); it++) {
    // determines if digraph/trigraph is the same as the user-inputted digraph/trigraph
    if (graph.compare(it->first) == 0) {
      graph_exists = true;
      cout << it->second.second << ": [";
      for (vector<string>::const_iterator p = it->second.first.cbegin(); p != it->second.first.cend(); p++) {
        if (p == it->second.first.cend() - 1) {
          cout << *p;
        }
        else {
          cout << *p << ", ";
        }
      }
      cout << "]" << endl;
    }
  }
  if (!graph_exists) {
    cout << "No such digraph" << endl;
  }
  cout << "q?>";
}


