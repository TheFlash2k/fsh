#include "../interface.hxx"

class Alias : public Command {
public:
    Alias() {
        this->name = "alias";
        this->version = "0.0.1";
        this->help = R"([GREEN]alias[RESET](1)
    [BOLD]NAME[RESET]
                alias - Alternate name for commands

    [BOLD]DESCRIPTION[RESET]
                Setup an alternate name for another command

    [BOLD]USAGE[RESET]
                alias <new_name> <cmd_name>

    [BOLD]EXAMPLES[RESET]
                alias list ls
                alias listtbl "ls -la"
    )";
    }
private:
    void _impl(strlist argv) {
        std::cout << "Alias called!" << std::endl;
    }
};

extern "C" Command* plugin_create() { return new Alias(); }
extern "C" void plugin_destroy(Command* cmd) { delete cmd; }