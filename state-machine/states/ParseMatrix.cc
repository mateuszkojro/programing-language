//
// Created by mateu on 6/24/2021.
//

#include "ParseMatrix.h"
#include "../../Utility.h"

RowState::RowState(Stack &stack, Matrix &matrix) : State(stack), matrix_(matrix) {
  CHANGE_STATE("RowState");
}

State *RowState::Parse(const std::string &text, int position) {
  if (text[position] == '[')
	return this;

  if (text[position] == ',') {
	matrix_.AddValue(std::stod(buffer_));
	buffer_ = "";
	return this;
  }
  if (text[position] == ']') {
	matrix_.AddValue(std::stod(buffer_));
	buffer_ = "";
	if (text[position + 1] == ']')
	  return nullptr;
	matrix_.AddRow();
	return new RowState(stack_, matrix_);
  }
  if (!Utility::whitespace(text[position])) {
	buffer_.push_back(text[position]);
	return this;
  }
  if (Utility::whitespace(text[position])) {
	return this;
  }
}

State *FirstRowState::Parse(const std::string &text, int position) {
  if (text[position - 1] == '"') {
	if (!is_string_) {
	  matrix_.AddRow();
	  matrix_.AddColumn();
	  matrix_.AddValue(text[position]);
	  is_string_ = true;
	  return this;
	}
  }

  if (!is_string_) {
	if (text[position] == '[') {
	  matrix_.AddRow();
	  return this;
	}
	if (text[position] == ',') {
	  matrix_.AddColumn();
	  matrix_.AddValue(std::stod(buffer_));
	  buffer_ = "";
	  return this;
	}
	if (text[position] == ']') {
	  matrix_.AddColumn();
	  matrix_.AddValue(std::stod(buffer_));
	  buffer_ = "";
	  if (text[position + 1] == ']')
		return nullptr;

	  matrix_.AddRow();
	  return new RowState(stack_, matrix_);
	}
  } else {
	if (text[position] == '"') {
	  return nullptr;
	}
	matrix_.AddColumn();
	matrix_.AddValue(text[position]);
	return this;
  }

  if (!Utility::whitespace(text[position])) {
	buffer_.push_back(text[position]);
	return this;
  }
  if (Utility::whitespace(text[position])) {
	return this;
  }

}
FirstRowState::FirstRowState(Stack &stack, Matrix &matrix) : State(stack), matrix_(matrix) {
  is_string_ = false;
  CHANGE_STATE("FristRowState");
}
