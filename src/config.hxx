#pragma once
#include "common.hxx"

namespace config {
    strdict replacments = {
        // We can also define replacements here.
        { "SEP"    , "|" },
        { "POSTFIX", "$" }
    };
    std::string PS1 = "[MAGENTA][USER][RESET]@[MAGENTA][HOSTNAME][RESET] [BLUE][DIR][RESET][POSTFIX]";

    // Do we want to store the history to a .fsh_history file?
    bool store_history = true;

    // Max Recall History Size
    uint64_t history_sz = 0x1000;

    bool autoload_plugins = true;

    // Files related to configurations
    std::string config_file  = "$HOME/.fshrc";
    std::string history_file = "$HOME/.fsh_history";
    std::string alias_file   = "$HOME/.fsh_aliases";
    std::string plugins_path = "./plugins";
};