#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cinttypes>

namespace ArgumentParser {

template <typename T>

class Argument {
private:
  T value;
  std::vector<T> multivalues;
  T* container_to_store_value = nullptr;
  std::vector<T>* vector_to_store_values; 
public:
  int values_count = 0;
  int min_args_count = -1;
  bool has_default = false;
  bool is_positional = false;
  bool is_multivalue = false;
  bool has_value = false;
  char short_name = '\0';
  std::string long_name;
  std::string description = "";
  std::string type;

  Argument(std::string given_long_name) {
    long_name = given_long_name;
  }

  Argument(std::string given_long_name, std::string given_description) {
    long_name = given_long_name;
    given_description = description;
  }

  Argument(char given_short_name, std::string given_long_name) {
    short_name = given_short_name;
    long_name = given_long_name;
  }

  Argument(char given_short_name, std::string given_long_name, std::string given_description) {
    short_name = given_short_name;
    long_name = given_long_name;
    description = given_description;
  }

  Argument& StoreValue(T& given_container) {
    container_to_store_value = &given_container;
    return *this;
  }

  Argument& StoreValues(std::vector<T>& given_container) {
    vector_to_store_values = &given_container;
    return *this;
  }

  Argument& MultiValue(int argument_count = 0) {
    is_multivalue = true;
    min_args_count = argument_count;
    return *this;
  }
  
  Argument& Default(T default_value) {
    if(has_value) {
      return *this;
    }
    has_default = true;
    value = default_value;
    has_value = true;
    return *this;
  }

  Argument& Default(std::vector<T> default_vector) {
    if(!is_multivalue) {
      std::cerr << "Error: Trying to set non-muliargument value's default to a vector";
      exit(EXIT_FAILURE);
    }
    if(multivalues.size() != 0) {
      return *this;
    }
    has_default = true;
    multivalues = default_vector;
    return *this;
  }

  Argument& SetArgument(T given_argument) {
    value = given_argument;
    has_value = true;
    if(container_to_store_value != nullptr) {
      (*container_to_store_value) = value;
    }
    return *this;
  }

  Argument& AddMultiargument(T given_argument) {
    has_value = true;
    multivalues.push_back(given_argument);
    ++values_count;
    vector_to_store_values->push_back(given_argument);
    return *this;
  }

  Argument& Positional() {
    is_positional = true;
    ++values_count;
    return *this;
  }

  T GetValue() {
    if(!has_value) {
      std::cerr << "Error: trying to get empty value";
      exit(EXIT_FAILURE);
    }
    return value;
  }

  T GetMultivalue(int pos) {
    if(!is_multivalue) {
      std::cerr << "Argument is not multivalue";
      exit(EXIT_FAILURE);
    }
    if(pos >= multivalues.size()) {
      std::cerr << "Index out of range";
      exit(EXIT_FAILURE);
    }
    return multivalues[pos];
  }

};

}