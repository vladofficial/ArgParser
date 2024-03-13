#pragma once
#include "Argument.h"
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>

namespace ArgumentParser {

class ArgParser {
private:
  std::unordered_map<std::string, Argument<std::string>*> str_arguments_map;
  std::unordered_map<std::string, Argument<int>*> int_arguments_map;
  std::unordered_map<std::string, Argument<bool>*> bool_arguments_map;
  std::unordered_map<char, std::string> short_name_map; 
  std::unordered_map<std::string, std::string> argument_types;
  std::vector<std::string> argument_names;
  std::string parser_name;
  Argument<bool>* bool_positional = nullptr;
  Argument<int>* int_positional = nullptr;
  Argument<std::string>* string_positional = nullptr;
  bool has_help = false;
public:
  ArgParser(std::string given_name);
  Argument<std::string>& AddStringArgument(std::string given_long_name);
  Argument<std::string>& AddstringArgument(std::string given_long_name, std::string given_description);
  Argument<std::string>& AddStringArgument(char given_short_name, std::string given_long_name);
  Argument<std::string>& AddStringArgument(char given_short_name, std::string given_long_name, std::string given_desctiption);
  Argument<int>& AddIntArgument(std::string given_long_name);  
  Argument<int>& AddIntArgument(std::string given_long_name, std::string given_description);
  Argument<int>& AddIntArgument(char given_short_name, std::string given_long_name);
  Argument<int>& AddIntArgument(char given_short_name, std::string given_long_name, std::string given_desctiption);
  Argument<bool>& AddFlag(std::string given_long_name);  
  Argument<bool>& AddFlag(std::string given_long_name, std::string given_description);
  Argument<bool>& AddFlag(char given_short_name, std::string given_long_name);
  Argument<bool>& AddFlag(char given_short_name, std::string given_long_name, std::string given_desctiption);
  void AddHelp(char given_short_name, std::string given_long_name, std::string given_desctiption);
  bool Parse(std::vector<std::string> arguments); 
  bool Parse(int argc, char** argv);
  std::string GetStringValue(std::string argument);
  std::string GetStringValue(std::string argument, int index);
  int GetIntValue(std::string argument);
  int GetIntValue(std::string argument, int index);
  bool GetFlag(std::string argument);
  bool GetFlag(std::string argument, int index);
  bool Help();
  std::string HelpDescription();
};

}