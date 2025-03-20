#include "../interface.hxx"

class Echo : public Command {
public:
    Echo() {
        this->name    = "echo";
        this->version = "0.0.1";
        this->help    = R"([GREEN]echo[RESET](1)
    [BOLD]echo[RESET]
                echo - print content from stdin to stdout

    [BOLD]DESCRIPTION[RESET]
                print content from stdin to stdout

    [BOLD]USAGE[RESET]
                echo [-n/--no-newline] <content>

            [BOLD] -n, --no-newline[RESET]
                    Append a newline to the end or not.
    )";
        this->valid_args = {"-n", "--no-newline"};
    }
private:
    void _impl(strlist argv = {}) {
        bool newline = true;
        if(List::in_list<std::string>(argv, "-n") || List::in_list<std::string>(argv, "--no-newline")) {
            newline = false;
            List::remove_from_list<std::string>(argv, "-n");
            List::remove_from_list<std::string>(argv, "--no-newline");
        }

        if(argv.size() < 1) {
            std::string tmp;
            while(std::getline(std::cin, tmp))
                std::cout << tmp << "\n";
            while(std::cin.eof()) {
                clearerr(stdin);
                std::cin.clear();
            }
        } else {
            for(size_t i = 0; i < argv.size(); i++) {
                std::cout << argv[i];
                if(i < argv.size()-1) std::cout << " ";
            }
            std::cout << ((newline) ? "\n": "");
        }
    }
};

extern "C" Command* plugin_create() { return new Echo(); }
extern "C" void plugin_destroy(Command* cmd) { delete cmd; }