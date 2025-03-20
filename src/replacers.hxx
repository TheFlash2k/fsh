#pragma once
#include "config.hxx"

#include <array>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <filesystem>

namespace replacers {
    std::string _get_username() {
        if(config::replacments.find("[USER]") != config::replacments.end())
            return config::replacments["[USER]"];
        struct passwd *pw = getpwuid(getuid());
        if(!pw) print_error(__func__, "Failed to get username");
        return (pw) ? pw->pw_name : "<unknown>";
    }

    std::string _get_workingdir() {
        if(config::replacments.find("[DIR]") != config::replacments.end())
            return config::replacments["[DIR]"];
        return std::filesystem::current_path();
    }

    std::string _get_groupname() {
        if(config::replacments.find("[GROUP]") != config::replacments.end())
            return config::replacments["[GROUP]"];
        struct group *gr = getgrgid(getgid());
        if(!gr) print_error(__func__, "Failed to get groupname");
        return (gr) ? gr->gr_name : "<unknown>";
    }

    std::string _get_hostname() {
        if(config::replacments.find("[HOSTNAME]") != config::replacments.end())
            return config::replacments["[HOSTNAME]"];
        std::array<char, 0x100> hostname;
        if(gethostname(hostname.data(), hostname.size()) != 0 )
            return "<unknown>";
        return std::string(hostname.data());
    }

    std::string _get_seperator() {
        if(config::replacments.find("[SEP]") != config::replacments.end())
            return config::replacments["[SEP]"];
        return "|";
    }

    std::string _get_postfix() {
        if(config::replacments.find("[POSTFIX]") != config::replacments.end())
            return config::replacments["[POSTFIX]"];
        return (getuid() == 0) ? "#" : "$";
    }
};