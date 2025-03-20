#pragma once

#include "interface.hxx"
#include "loader.hxx"

// List of base commands that have builtin methods.
const strlist _base = { "version", "help", "info", "man", "builtins", "load-plugin" };

// List of commands that require no arguments
const strlist no_args = { "builtins" };

void builtin_base(const std::string& command, strlist args) {

    if(args.size() == 0) {
        // if no_args builtin, just add a single arg:
        if(List::in_list(no_args, command)) {
            args.push_back("[PLACEHOLDER]");
        } else {
            std::cerr
                << command
                << ": requires one argument.\n\n"
                << command
                << " <command>"
                << std::endl;
            return;
        }
    }

    for(const auto& cmd : args) {
        if(builtins.find(cmd) == builtins.end() && !List::in_list(no_args, command)) {
            std::cerr << command << ": \"" << cmd << "\" is not a valid command"<< std::endl;
            break;
        }
        if(command == "version")
            builtins[cmd]->_version();
        else if(command == "help" || command == "info" || command == "man")
            builtins[cmd]->_help();
        else if(command == "load-plugin")
            PluginLoader::load_plugin(cmd);
        else if(command == "builtins") {
            std::cout << "fsh builtins:\n\n";
            for(const auto& b: _base) {
                if(b == command) continue;
                std::cout << "\t" << b << std::endl;
            }
        }
        else {
            std::cerr << "fsh: command not found: " << cmd << std::endl;
            break;
        }
    }

    if(args[args.size()-1] == "[PLACEHOLDER]")
        args.pop_back();
}