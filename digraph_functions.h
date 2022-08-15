#ifndef DIGRAPH_FUNCTIONS_H
#define DIGRAPH_FUNCTIONS_H

void initialize_map(std::map<std::string, std::pair<std::vector<std::string>, int>>& words_with_graphs, std::vector<std::string>& v_graphs, int num_graphs, std::ifstream& ifile);
void add_words_to_map(std::map<std::string, std::pair<std::vector<std::string>, int>>& words_with_graphs, std::vector<std::string>& v_graphs, int num_graphs, std::ifstream& ifile);
std::string make_lowercase(std::string word);
std::string format_word(std::string word);
void print_ASCII_order(std::map<std::string, std::pair<std::vector<std::string>, int>>& words_with_graphs);
void print_reverse_ASCII_order(std::map<std::string, std::pair<std::vector<std::string>, int>>& words_with_graphs);
void initialize_vectors(std::map<std::string, std::pair<std::vector<std::string>, int>> words_with_graphs, int num_graphs, std::vector<std::pair<int, std::string>>& graph_counts, std::vector<int>& counts);
void break_ties(std::vector<std::pair<int, std::string>>& graph_counts, std::vector<int> counts);
void print_based_on_count(std::map<std::string, std::pair<std::vector<std::string>, int>>& words_with_graphs, int num_graphs);
void print_graphs_with_same_count(std::map<std::string, std::pair<std::vector<std::string>, int>> words_with_graphs, int number);
void print_graph_count(std::map<std::string, std::pair<std::vector<std::string>, int>> words_with_graphs, std::string graph);

#endif