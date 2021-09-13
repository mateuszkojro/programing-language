#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "language/parser.h"

int interpret_file(const std::string &filepath) {

  std::fstream file;

  file.open(filepath, std::ios::out);

  Parser parser;

  while (file.good()) {
	std::string line;
	std::getline(std::cin, line);
	parser.parse(line);
  }
  return 0;
}

int repl() {
  Parser parser;

  while (true) {
	std::cout << "=>";
	std::cout.flush();
	std::string line;
	std::getline(std::cin, line);

	if (line == "$q")
	  return 0;

	parser.parse(line);
  }
}

int main(int argc, char **argv) {

  if (argc == 2)
	return interpret_file(argv[1]);

  return repl();
}
