#include "ArgParser.h"
#include <iostream>
namespace ArgumentParser{

bool ValidateInt(std::string argument) {
  bool is_negative = (argument[0] == '-');  
  for(int i = 0 + is_negative; i < argument.length(); ++i) {
    if(!isdigit(argument[i])) {
      return false;
    }
  }
  return true;
}

ArgParser::ArgParser(std::string given_name) {
  parser_name = given_name;
}

Argument<std::string>& ArgParser::AddStringArgument(std::string given_long_name) {
  Argument<std::string>* str_argument_pointer = new Argument<std::string>(given_long_name);
  str_arguments_map[given_long_name] = str_argument_pointer;
  argument_types[given_long_name] = "string";
  argument_names.push_back(given_long_name);
  return (*str_argument_pointer);
}

Argument<std::string>& ArgParser::AddstringArgument(std::string given_long_name, std::string given_description) {
  Argument<std::string>* str_argument_pointer = new Argument<std::string>(given_long_name, given_description);
  str_arguments_map[given_long_name] = str_argument_pointer;
  argument_types[given_long_name] = "string";
  argument_names.push_back(given_long_name);
  return (*str_argument_pointer);
}

Argument<std::string>& ArgParser::AddStringArgument(char given_short_name, std::string given_long_name) {
  Argument<std::string>* str_argument_pointer = new Argument<std::string>(given_short_name, given_long_name);
  str_arguments_map[given_long_name] = str_argument_pointer;
  argument_types[given_long_name] = "string";
  short_name_map[given_short_name] = given_long_name;
  argument_names.push_back(given_long_name);
  return (*str_argument_pointer);
}

Argument<std::string>& ArgParser::AddStringArgument(char given_short_name, std::string given_long_name, std::string given_description) {
  Argument<std::string>* str_argument_pointer = new Argument<std::string>(given_short_name, given_long_name, given_description);
  str_arguments_map[given_long_name] = str_argument_pointer;
  argument_types[given_long_name] = "string";
  short_name_map[given_short_name] = given_long_name;
  argument_names.push_back(given_long_name);
  return (*str_argument_pointer);
}



Argument<int>& ArgParser::AddIntArgument(std::string given_long_name) {
  Argument<int>* int_argument_pointer = new Argument<int>(given_long_name);
  int_arguments_map[given_long_name] = int_argument_pointer;
  argument_types[given_long_name] = "int";
  argument_names.push_back(given_long_name);
  return (*int_argument_pointer);
}

Argument<int>& ArgParser::AddIntArgument(std::string given_long_name, std::string given_description) {
  Argument<int>* int_argument_pointer = new Argument<int>(given_long_name, given_description);
  int_arguments_map[given_long_name] = int_argument_pointer;
  argument_types[given_long_name] = "int";
  argument_names.push_back(given_long_name);
  return (*int_argument_pointer);
}

Argument<int>& ArgParser::AddIntArgument(char given_short_name, std::string given_long_name) {
  Argument<int>* int_argument_pointer = new Argument<int>(given_short_name, given_long_name);
  int_arguments_map[given_long_name] = int_argument_pointer;
  short_name_map[given_short_name] = given_long_name;
  argument_types[given_long_name] = "int";
  argument_names.push_back(given_long_name);
  return (*int_argument_pointer);
}

Argument<int>& ArgParser::AddIntArgument(char given_short_name, std::string given_long_name, std::string given_description) {
  Argument<int>* int_argument_pointer = new Argument<int>(given_short_name, given_long_name, given_description);
  int_arguments_map[given_long_name] = int_argument_pointer;
  short_name_map[given_short_name] = given_long_name;
  argument_types[given_long_name] = "int";
  argument_names.push_back(given_long_name);
  return (*int_argument_pointer);
}



Argument<bool>& ArgParser::AddFlag(std::string given_long_name) {
  Argument<bool>* bool_argument_pointer = new Argument<bool>(given_long_name);  
  bool_arguments_map[given_long_name] = bool_argument_pointer;
  argument_types[given_long_name] = "bool";
  argument_names.push_back(given_long_name);
  return (*bool_argument_pointer);
}

Argument<bool>& ArgParser::AddFlag(std::string given_long_name, std::string given_description) {
  Argument<bool>* bool_argument_pointer = new Argument<bool>(given_long_name, given_description);
  bool_arguments_map[given_long_name] = bool_argument_pointer;
  argument_types[given_long_name] = "bool";
  argument_names.push_back(given_long_name);
  return (*bool_argument_pointer);
}

Argument<bool>& ArgParser::AddFlag(char given_short_name, std::string given_long_name) {
  Argument<bool>* bool_argument_pointer = new Argument<bool>(given_short_name, given_long_name);
  bool_arguments_map[given_long_name] = bool_argument_pointer;
  short_name_map[given_short_name] = given_long_name;
  argument_types[given_long_name] = "bool";
  argument_names.push_back(given_long_name);
  return (*bool_argument_pointer);
}

Argument<bool>& ArgParser::AddFlag(char given_short_name, std::string given_long_name, std::string given_description) {
  Argument<bool>* bool_argument_pointer = new Argument<bool>(given_short_name, given_long_name, given_description);
  bool_arguments_map[given_long_name] = bool_argument_pointer;
  short_name_map[given_short_name] = given_long_name;
  argument_types[given_long_name] = "bool";
  argument_names.push_back(given_long_name);
  return (*bool_argument_pointer);
}

void ArgParser::AddHelp(char given_short_name, std::string given_long_name, std::string given_desctiption) {
  AddStringArgument(given_short_name, given_long_name, given_desctiption);
}

bool ArgParser::Parse(std::vector<std::string> arguments) {
  if (arguments[0] != "app") {
    return false;
  }
  if (arguments.size() > 1 && arguments[1] == "--help") {
    has_help = true;
    return true;
  }
  for (uint16_t i = 1; i < arguments.size(); ++i) {
    int argument_value_start_pos = 0;
    for (int j = 0; j < arguments[i].length(); ++j) {
      if (arguments[i][j] == '=') {
        argument_value_start_pos = j + 1;
      }
    }
    for (int i = 0; i < argument_names.size(); ++i) {
      if (argument_types[argument_names[i]] == "string") {
        string_positional = str_arguments_map[argument_names[i]];
      }
      if (argument_types[argument_names[i]] == "int") {
        int_positional = int_arguments_map[argument_names[i]];
      }
      if (argument_types[argument_names[i]] == "bool") {
        bool_positional = bool_arguments_map[argument_names[i]];
      }
    }
    if (arguments[i][0] == '-' && arguments[i][1] == '-') {
      if (argument_types[arguments[i].substr(2, argument_value_start_pos - 3)] == "string"){
        if (!str_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]->is_multivalue) {
          (*str_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]).SetArgument(arguments[i].substr(argument_value_start_pos));
        } else {
          (*str_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]).AddMultiargument(arguments[i].substr(argument_value_start_pos));
        }  
      } 
      if (argument_types[arguments[i].substr(2, argument_value_start_pos - 3)] == "int"){
        if (ValidateInt(arguments[i].substr(argument_value_start_pos))) {
          if (!int_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]->is_multivalue) {
            (*int_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]).SetArgument(std::stoi(arguments[i].substr(argument_value_start_pos)));
          } else {
            (*int_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]).AddMultiargument(std::stoi(arguments[i].substr(argument_value_start_pos)));
          }
        }  
      }
      if (argument_types[arguments[i].substr(2, argument_value_start_pos - 3)] == "bool"){
        if (!bool_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]->is_multivalue) {
          (*bool_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]).SetArgument(true);
        } else {
          (*bool_arguments_map[arguments[i].substr(2, argument_value_start_pos - 3)]).AddMultiargument(true);
        }  
      }
    } else if (arguments[i][0] == '-' && arguments[i][1] != '-') {
      if (argument_types[short_name_map[arguments[i][1]]] == "string") {
        if (!str_arguments_map[short_name_map[arguments[i][1]]]->is_multivalue) {
          (*str_arguments_map[short_name_map[arguments[i][1]]]).SetArgument(arguments[i].substr(argument_value_start_pos));
        } else {
          (*str_arguments_map[short_name_map[arguments[i][1]]]).AddMultiargument(arguments[i].substr(argument_value_start_pos));
        }  
      }
      if (argument_types[short_name_map[arguments[i][1]]] == "int") {
        if (ValidateInt(arguments[i + 1])) {
          if (!int_arguments_map[short_name_map[arguments[i][1]]]->is_multivalue) {
            (*int_arguments_map[short_name_map[arguments[i][1]]]).SetArgument(std::stoi(arguments[i].substr(argument_value_start_pos)));
          } else {
            (*int_arguments_map[short_name_map[arguments[i][1]]]).AddMultiargument(std::stoi(arguments[i].substr(argument_value_start_pos)));
          }
        }
      }  
      if (argument_types[short_name_map[arguments[i][1]]] == "bool") {\
        for (int j = 1; j < arguments[i].size(); ++j) {
          if (!bool_arguments_map[short_name_map[arguments[i][j]]]->is_multivalue) {
            (*bool_arguments_map[short_name_map[arguments[i][j]]]).SetArgument(true);
          } else {
            (*bool_arguments_map[short_name_map[arguments[i][j]]]).AddMultiargument(true);
          }  
        }
      }
    } else {
      if (bool_positional != nullptr) {
        if (bool_positional->is_multivalue) {
          bool_positional->AddMultiargument(true);
        } else {
          bool_positional->SetArgument(true);
        }
      } else if (int_positional != nullptr && ValidateInt(arguments[i])) {
        if (int_positional->is_multivalue) {
          int_positional->AddMultiargument(std::stoi(arguments[i]));
        } else {
          int_positional->SetArgument(std::stoi(arguments[i]));
        }
      } else if (string_positional != nullptr && ValidateInt(arguments[i])) {
        if (string_positional->is_multivalue) {
          string_positional->AddMultiargument(arguments[i]);
        } else {
          string_positional->SetArgument(arguments[i]);
        }
      }
    }  
  }
  for (int i = 0; i < argument_names.size(); ++i) {
    if (argument_types[argument_names[i]] == "string") {
      if (!str_arguments_map[argument_names[i]]->has_default && !str_arguments_map[argument_names[i]]->has_value) {
        return false;
      }
      if (str_arguments_map[argument_names[i]]->is_multivalue && str_arguments_map[argument_names[i]]->values_count < str_arguments_map[argument_names[i]]->min_args_count) {
        return false;
      }
    }
    if (argument_types[argument_names[i]] == "int") {
      if (!int_arguments_map[argument_names[i]]->has_default && !int_arguments_map[argument_names[i]]->has_value) {
        return false;
      }
      if (int_arguments_map[argument_names[i]]->is_multivalue && int_arguments_map[argument_names[i]]->values_count < int_arguments_map[argument_names[i]]->min_args_count) {
        return false;
      }
    }
    if (argument_types[argument_names[i]] == "bool") {
      if (!bool_arguments_map[argument_names[i]]->has_default && !bool_arguments_map[argument_names[i]]->has_value) {
        return false;
      }
      if (bool_arguments_map[argument_names[i]]->is_multivalue && bool_arguments_map[argument_names[i]]->values_count < bool_arguments_map[argument_names[i]]->min_args_count) {
        return false;
      }
    }
  }
  return true;
}

bool ArgParser::Parse(int argc, char** argv) {
  std::vector<std::string> arguments;
  for(int i = 1; i < argc; ++i) {
    arguments.push_back(std::string(argv[i]));
  }
  return ArgParser::Parse(arguments);
}

std::string ArgParser::GetStringValue(std::string argument) { 
  return (*str_arguments_map[argument]).GetValue();
}

std::string ArgParser::GetStringValue(std::string argument, int index) { 
  return (*str_arguments_map[argument]).GetMultivalue(index);
}

int ArgParser::GetIntValue(std::string argument) { 
  return (*int_arguments_map[argument]).GetValue();
}

int ArgParser::GetIntValue(std::string argument, int index) {
  return (*int_arguments_map[argument]).GetMultivalue(index);
}

bool ArgParser::GetFlag(std::string argument) { 
  return (*bool_arguments_map[argument]).GetValue();
}

bool ArgParser::GetFlag(std::string argument, int index) {
  return (*bool_arguments_map[argument]).GetMultivalue(index);
}

bool ArgParser::Help() {
  for(int i = 0; i < argument_names.size(); ++i) {
    if(str_arguments_map[argument_names[i]] != 0 && str_arguments_map[argument_names[i]]->long_name == "help") {
      std::cout << str_arguments_map[argument_names[i]]->description;
      return true;
    }
  }
  return false;
}

std::string ArgParser::HelpDescription() {
  std::string description = "";
  description += (this->parser_name + "\n");
  description += (str_arguments_map[argument_names[0]]->description);
  description += ("\n");
  for(int i = 0; i < argument_names.size(); ++i) {
    std::string argument_description = "";
    if(argument_names[i] == "help") {
      continue;
    }
    if(str_arguments_map[argument_names[i]] != 0) {
      if(str_arguments_map[argument_names[i]]->short_name != '\0') {
        argument_description += std::string(1, str_arguments_map[argument_names[i]]->short_name) + ", ";
      }
      argument_description += "--" + str_arguments_map[argument_names[i]]->long_name + "=<string>, ";
      argument_description += str_arguments_map[argument_names[i]]->description;
      if(str_arguments_map[argument_names[i]]->is_multivalue) {
        argument_description += "[repeated, min_args" + std::to_string(str_arguments_map[argument_names[i]]->min_args_count) + "] ";
      }
      if(str_arguments_map[argument_names[i]]->has_default) {
        argument_description += "[default = true]";
      }
      argument_description += "\n";
    }
    if(int_arguments_map[argument_names[i]] != 0) {
      if(int_arguments_map[argument_names[i]]->short_name != '\0') {
        argument_description += std::string(1, int_arguments_map[argument_names[i]]->short_name) + ", ";
      }
      argument_description += "--" + int_arguments_map[argument_names[i]]->long_name + "=<int>, ";
      argument_description += int_arguments_map[argument_names[i]]->description;
      if(int_arguments_map[argument_names[i]]->is_multivalue) {
        argument_description += "[repeated, min_args" + std::to_string(str_arguments_map[argument_names[i]]->min_args_count) + "] ";
      }
      if(int_arguments_map[argument_names[i]]->has_default) {
        argument_description += "[default = true]";
      }
      argument_description += "\n";
    }
    if(bool_arguments_map[argument_names[i]] != 0) {
      if(bool_arguments_map[argument_names[i]]->short_name != '\0') {
        argument_description += std::string(1, bool_arguments_map[argument_names[i]]->short_name) + ", ";
      }
      argument_description += "--" + bool_arguments_map[argument_names[i]]->long_name + "=<int>, ";
      argument_description += bool_arguments_map[argument_names[i]]->description;
      if(bool_arguments_map[argument_names[i]]->is_multivalue) {
        argument_description += "[repeated, min_args" + std::to_string(bool_arguments_map[argument_names[i]]->min_args_count) + "] ";
      }
      if(bool_arguments_map[argument_names[i]]->has_default) {
        argument_description += "[default = true]";
      }
      argument_description += "\n";
    }
    description += argument_description;
  }
  return description;
}

}