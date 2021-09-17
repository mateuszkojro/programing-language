#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "language/parser.h"

Parser interpret_file(const std::string &filepath, Parser parser = Parser()) {

  std::fstream file;

  file.open(filepath, std::ios::out);

  std::string whole_file;
  while (file.good()) {
	std::string line;
	std::getline(std::cin, line);
	whole_file.append(line);
  }
  parser.parse(whole_file);
  return parser;
}

Parser repl(Parser parser = Parser()) {
  std::cout << "=== Unnamed programing languge ===" << std::endl;
  std::cout << "Compiled with " << COMPILER << " on " << __DATE__ << " " << __TIME__ << std::endl;
  while (true) {
	std::cout << "=> ";
	std::cout.flush();
	std::string line;
	std::getline(std::cin, line);

	if (line == "$q")
	  return parser;

	if (line == "%load")
	  return parser;

	parser.parse(line);
  }
}

int main(int argc, char **argv) {

  if (argc == 2) {
	interpret_file(argv[1]);
	return 0;
  }

  if (argc == 3)
	if (argv[1] == "-l") {
	  repl(interpret_file(argv[2]));
	  return 0;
	}

  repl();
  return 0;
}
