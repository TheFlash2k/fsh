// This is a template for the command that we can 
#include "../interface.hxx"

class COMMAND_NAME : public Command {
public:
    COMMAND_NAME() {
        this->name    = "NAME";
        this->version = "0.0.0";
        this->help    = R"([GREEN]NAME[RESET](1)
    [BOLD]NAME[RESET]
                NAME - SMALL_DESC

    [BOLD]DESCRIPTION[RESET]
                LONGER DESCRIPTION

    [BOLD]USAGE[RESET]
                USAGE IN DETAILS

    [BOLD]EXAMPLES[RESET]
                A FEW EXAMPLES
    )";

        // A list of valid arguments that will be automatically checked.
        // Only those beginning with - are checked. Nothing else.
        this->valid_args = {};
    }
private:
    void _impl(strlist argv = {}) {
        // This is where the actual implementation of the class goes.
    }
};

extern "C" Command* plugin_create() { return new COMMAND_NAME(); }
extern "C" void plugin_destroy(Command* cmd) { delete cmd; }