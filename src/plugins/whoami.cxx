#include "../interface.hxx"

class Whoami : public Command {
public:
    Whoami() {
        this->name    = "whoami";
        this->version = "0.0.1";
        this->help    = R"([GREEN]whoami[RESET](1)
    [BOLD]NAME[RESET]
                whoami - print effective userid

    [BOLD]DESCRIPTION[RESET]
                Print the user name associated with the current effective user ID.

    [BOLD]USAGE[RESET]
                whoami
    )";
        this->valid_args = {};
    }
private:
    void _impl(strlist argv = {}) {
        std::cout << getpwuid(geteuid())->pw_name << std::endl;
    }
};

extern "C" Command* plugin_create() { return new Whoami(); }
extern "C" void plugin_destroy(Command* cmd) { delete cmd; }