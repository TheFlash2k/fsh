#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#pragma once

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <vector>
#include <stdint.h>
#include <filesystem>
#include <map>
#include <dlfcn.h>

bool _DEBUG = false;

void print_error(
        const std::string& fn,
        const std::string& msg,
        bool _exit=1,
        uint8_t _code=-1
    ) {
    std::cerr << fn << ": " << msg << std::endl;
    if(_exit) exit(_code);
}

void debug(const std::string& msg) {
    if(_DEBUG) {
        std::cout << "[FSH-DEBUG] " << msg << std::endl;
    }
}

typedef std::string (*func)(void);
typedef std::unordered_map<std::string, std::string> strdict;
typedef std::unordered_map<std::string, func>        strfndict;
typedef std::vector<std::string>                     strlist;
typedef std::pair<std::string, strlist>              cmd;

strdict colors = {
    {"[RESET]", "\033[0m"},
    
    // Text Styles
    {"[BOLD]", "\033[1m"},
    {"[DIM]", "\033[2m"},
    {"[ITALIC]", "\033[3m"},
    {"[UNDERLINE]", "\033[4m"},

    // Colors
    {"[BLACK]", "\033[0;30m"},
    {"[RED]", "\033[0;31m"},
    {"[GREEN]", "\033[0;32m"},
    {"[YELLOW]", "\033[0;33m"},
    {"[BLUE]", "\033[0;34m"},
    {"[MAGENTA]", "\033[0;35m"},
    {"[CYAN]", "\033[0;36m"},
    {"[WHITE]", "\033[0;37m"},

    // Dim Colors
    {"[DIM_BLACK]", "\033[2;30m"},
    {"[DIM_RED]", "\033[2;31m"},
    {"[DIM_GREEN]", "\033[2;32m"},
    {"[DIM_YELLOW]", "\033[2;33m"},
    {"[DIM_BLUE]", "\033[2;34m"},
    {"[DIM_MAGENTA]", "\033[2;35m"},
    {"[DIM_CYAN]", "\033[2;36m"},
    {"[DIM_WHITE]", "\033[2;37m"},

    // Italic Colors
    {"[ITALIC_BLACK]", "\033[3;30m"},
    {"[ITALIC_RED]", "\033[3;31m"},
    {"[ITALIC_GREEN]", "\033[3;32m"},
    {"[ITALIC_YELLOW]", "\033[3;33m"},
    {"[ITALIC_BLUE]", "\033[3;34m"},
    {"[ITALIC_MAGENTA]", "\033[3;35m"},
    {"[ITALIC_CYAN]", "\033[3;36m"},
    {"[ITALIC_WHITE]", "\033[3;37m"},

    // Underline Colors
    {"[UNDERLINE_BLACK]", "\033[4;30m"},
    {"[UNDERLINE_RED]", "\033[4;31m"},
    {"[UNDERLINE_GREEN]", "\033[4;32m"},
    {"[UNDERLINE_YELLOW]", "\033[4;33m"},
    {"[UNDERLINE_BLUE]", "\033[4;34m"},
    {"[UNDERLINE_MAGENTA]", "\033[4;35m"},
    {"[UNDERLINE_CYAN]", "\033[4;36m"},
    {"[UNDERLINE_WHITE]", "\033[4;37m"}
};