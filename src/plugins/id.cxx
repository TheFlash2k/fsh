#include "../interface.hxx"

class Id : public Command {
public:
    Id() {
        this->name    = "id";
        this->version = "0.0.1";
        this->help    = R"([GREEN]id[RESET](1)
    [BOLD]id[RESET]
                id - print user and group id

    [BOLD]DESCRIPTION[RESET]
                Print real and effective user and group IDs

    [BOLD]USAGE[RESET]
                id
    )";
        this->valid_args = {};
    }
private:
    void _impl(strlist argv = {}) {
        std::cout << "uid=" << getuid() << "(" << getpwuid(getuid())->pw_name << ") "
                  << "gid=" << getgid() << "(" << getgrgid(getgid())->gr_name << ") " << std::endl;
    }
};

extern "C" Command* plugin_create() { return new Id(); }
extern "C" void plugin_destroy(Command* cmd) { delete cmd; }