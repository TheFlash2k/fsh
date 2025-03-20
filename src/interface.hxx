#pragma once

#define EXPORT __attribute__((visibility("default")))

#include "utils.hxx"

class Command {
public:
    std::string name    = "";
    std::string help    = "";
    std::string version = "0.0.0";

    // These must begin with - or --
    // key will always be checked with -
    // and value will always be checked with --
    strlist valid_args  = {};

    void _help() {
        // Replace colors only once.
        if(!this->is_help_invk) {
            for(const auto& kv: colors)
                String::find_and_replace(
                    this->help, kv.first, kv.second);
        }
        std::cout
            << "\n"
            << this->help
            << std::endl;
        this->is_help_invk = true;
    }

    void _version() {
        std::cout <<
            colors["[GREEN]"] <<
            this->name        <<
            colors["[RESET]"] <<
            " v"              <<
            colors["[RED]"]   <<
            this->version     <<
            colors["[RESET]"] <<
            std::endl;
    }

    void execute(strlist argv) {
        this->argv = argv;
        String::strip_all(this->argv);
        if(!this->check_base_args())
            _impl(argv);
    }
    
protected:
    // List of arguments passed to the underlying commands.
    strlist  argv      = {};
    // Only used in cases where we want to run commands from
    // underlying os. (maybe taken out in future.)
    bool is_privileged = false;
    // This will be set to true once _help is invoked so we'll have colors added.
    bool is_help_invk  = false;

    virtual void _impl(strlist argv) = 0;

    bool check_base_args() {
        for(const auto& _av: this->argv) {
            // We can check for some basic arguments here.
            if(_av == "-h" || _av == "--help") {
                this->_help();
                return true;
            }
            if(_av == "-v" || _av == "--version") {
                this->_version();
                return true;
            }
        }

        // Check if the passed args exist in valid args.
        for(const auto& c_arg : this->argv) {
            if(c_arg[0] == '-' && !List::in_list(valid_args, c_arg)) {
                std::cerr
                    << name
                    << ": invalid argument "
                    << c_arg
                    << "\n\n$ help \""
                    << name
                    << "\" to see list of available arguments\n"
                    << std::endl;
                return true;
            }
        }

        return false;
    }

};

extern "C" {
    EXPORT Command* plugin_create();
    EXPORT void     plugin_destroy(Command* cmd);
}