#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

std::unordered_map<std::string, float> variables;

bool is_binary(std::string input) {
  for (char ch : input) {
	if (ch != '1' && ch != '0') return false;
  }
  return true;
}
float binary_to_denary(std::string binary) {
  float denary = 0;
  int exp = 0;
  for (int i = binary.length() - 1; i >= 0; --i) {
	if (binary[i] == '1') denary += 1 << exp;
	exp++;
  }
  return denary;
}
void process_line(std::string line) {
  std::vector<std::string> words;
  std::string word;
  std::stringstream ss(line);
  while (std::getline(ss, word, ' ')) {
	words.push_back(word);
  }
  std::string command = words[0];
  if (command == "set") {
	if (is_binary(words[2])) {
	  variables[words[1]] = binary_to_denary(words[2]);
	} else {
	  variables[words[1]] = variables.find(words[2])->second;
	}
  } else if (command == "+" || command == "-" || command == "*" || command == "/") {
	float new_value = variables.find(words[1])->second;
	for (int i = 2; i < words.size(); ++i) {
	  float operated_value = 0;
	  if (is_binary(words[i])) {
		operated_value = binary_to_denary(words[i]);
	  } else {
		operated_value= variables.find(words[i])->second;
	  }
	  if (command == "+") new_value += operated_value;
	  if (command == "-") new_value -= operated_value;
	  if (command == "*") new_value *= operated_value;
	  if (command == "/") new_value /= operated_value;
	}
	variables[words[1]] = new_value;	
  } else if (command == "print") {
	for (int i = 1; i < words.size(); ++i) {
	  if (words[i][0] == '_') {
		for (int j = 1; j < words[i].length(); ++j) std::cout << words[i][j];
	  } else if (words[i][0] != '_' && words[i] != "\\" && words[i] != "#") {
		std::cout << variables.find(words[i])->second;
	  } else if (words[i] == "\\") {
		std::cout << "\n";
	  } else if (words[i] == "#") {
		std::cout << " ";
	  }
	}
  }
}
int main() {
  std::ifstream input("another.bri");
  if (!input) {
	std::cerr << "Unable to open file\n\n\n";
	exit(1);
  }
  std::string line;
  while (std::getline(input, line)) {
	if (line == "") continue;
	process_line(line);
  }  
}
