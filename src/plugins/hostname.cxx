#include "../interface.hxx"

class Hostname : public Command {
public:
    Hostname() {
        this->name    = "hostname";
        this->version = "0.0.1";
        this->help    = R"([GREEN]hostname[RESET](1)
    [BOLD]id[RESET]
                hostname - display the system name

    [BOLD]DESCRIPTION[RESET]
                Hostname is used to display the system's DNS name

    [BOLD]USAGE[RESET]
                hostname
    )";
        this->valid_args = {};
    }
private:
    void _impl(strlist argv = {}) {
        std::array<char, 0x100> hostname;
        std::cout << (
            (gethostname(hostname.data(), hostname.size()) != 0 ) ? "<unknown>" :
            std::string(hostname.data())
        ) << std::endl;
    }
};

extern "C" Command* plugin_create() { return new Hostname(); }
extern "C" void plugin_destroy(Command* cmd) { delete cmd; }