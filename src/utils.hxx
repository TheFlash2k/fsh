#pragma once

#include "replacers.hxx"
#include "helpers.hxx"

namespace utils {

    // This is just there to avoid people just abusing the
    // best shell out there ofcourse.
    strlist blacklist = { "proc", "root", "flag", "passwd", "maps" };

    strfndict replacers = {
        {"[SEP]"     , replacers::_get_seperator},
        {"[DIR]"     , replacers::_get_workingdir},
        {"[USER]"    , replacers::_get_username},
        {"[GROUP]"   , replacers::_get_groupname},
        {"[POSTFIX]" , replacers::_get_postfix},
        {"[HOSTNAME]", replacers::_get_hostname}
        // You can define custom replacers here for more control
    };

    void _ps1() {
        for(const auto& kv : replacers)
            String::find_and_replace(
                config::PS1, kv.first, kv.second());

        // Add colors.
        for(const auto& kv: colors)
            String::find_and_replace(
                config::PS1, kv.first, kv.second);

        if(config::PS1[config::PS1.size()-1] != ' ')
            config::PS1 += ' '; // Add a space for aesthetics.
    }

    void setup_config() {
        
    }

    void do_setup() {

        // Setup buffering.
        setvbuf(stdin, NULL, _IONBF, 0);
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);

        // Setup Prompt
        utils::_ps1();
    }

    cmd parse_command(const std::string& _cmd) {
        std::istringstream stream(_cmd);
        cmd _c;

        stream >> _c.first; // store the command itself.
        std::string token;
        while(stream >> token) // store the args.
            _c.second.push_back(token);
        return _c;
    }
};