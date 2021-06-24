#include <iostream>
#include <vector>
#include <fstream>
#include "Function.h"
#include "tokens/Variable.h"
#include "state-machine/Parser.h"
#include "Stack.h"

Matrix &GetFromStack(Stack &stack) {
  Variable *variable = (Variable *)stack.Back();
  stack.PopBack();
  return variable->GetValue();
}

int Hello(Stack &stack) {
  std::cout << "Hello" << std::endl;
  return 0;
}

int ExitFunc(Stack &stack) {
  exit(0);
  return 0;
}

int Print(Stack &stack) {
  auto mat = GetFromStack(stack);
  std::cout << mat.Repr() << std::endl;
  return 0;
}

int Ones(Stack &stack) {
  Matrix m;
  Matrix::ParseMatrix("[[1,1,1][1,1,1][1,1,1]]", m);
  stack.PushBack(new Variable("return", m));
  return 1;
}

int Input(Stack &stack) {
  Matrix m;
  std::string input;
  std::getline(std::cin, input);
  Matrix::ParseMatrix(input, m);
  stack.PushBack(new Variable("return", m));
  return 1;
}

int Text(Stack &stack) {
  auto val = GetFromStack(stack);
  for (int i = 0; i < val.Size(); i++) {
	std::cout << (char)val.Get(i);
  }
  return 1;
}

int Eq(Stack &stack) {
  auto mat1 = GetFromStack(stack);
  auto mat2 = GetFromStack(stack);

  Matrix m;
  if (mat1 == mat2) {
	Matrix::ParseMatrix("[[1]]", m);
  } else {
	Matrix::ParseMatrix("[[0]]", m);
  }
  stack.PushBack(new Variable("return", m));
  return 1;
}

int Newline(Stack &stack) {
  std::cout << std::endl;
  return 1;
}

int NotFunc(Stack &stack) {
  Matrix val = GetFromStack(stack);
  Matrix result;
  for (int i = 0; i < val.Size(); i++) {
	result(i) = val(i) == 0 ? 1 : 0;
  }
  stack.PushBack(new Variable("return", result));
  return 1;
}

int main(int argc, char **argv) {
  Parser parser;
//    std::FUNCTION<int(Stack&)> func = Hello;
  parser.stack_.PushBack(new Function("hello", Hello));
  parser.stack_.PushBack(new Function("exit", ExitFunc));
  parser.stack_.PushBack(new Function("print", Print));
  parser.stack_.PushBack(new Function("ones", Ones));
  parser.stack_.PushBack(new Function("eq", Eq));
  parser.stack_.PushBack(new Function("input", Input));
  parser.stack_.PushBack(new Function("text", Text));
  parser.stack_.PushBack(new Function("newline", Newline));
  parser.stack_.PushBack(new Function("not", NotFunc));

  if (argc < 2) {
	// maybe repl?
	while (true) {
	  std::string line;
	  std::getline(std::cin, line);
	  parser.ParseString(line);
	  if (line == "#quit#")
		break;
	}
	return 0;
  }

  std::fstream (file);

  file.open(argv[1], std::ios::in);

  while (file.good()) {
	std::string line;
	std::getline(file, line);
	parser.ParseString(line);
  }

//    parser.ParseString("mat x = [[1]];"
//                        "x = [[1,2,3,4][5,6,7,8]];"
//                        "Hello()"
//    );

  return 0;
}
