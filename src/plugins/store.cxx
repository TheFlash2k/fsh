#include "../interface.hxx"

class Store : public Command {
public:
    Store() {
        this->name = "store";
        this->version = "0.0.1";
        this->help = R"([GREEN]STORE[RESET](1)
    [BOLD]NAME[RESET]
                store - store contents inside a file.

    [BOLD]DESCRIPTION[RESET]
                Store contents passed as args to file name.

    [BOLD]USAGE[RESET]
                store [-a/--append] <filename> [-stdin/*content]

            [BOLD] -a, --append[RESET]
                    Append contents to the file (if it exists)

            [BOLD] -stdin[RESET]
                    Read from stdin until EOF is reached.
    
    [BOLD]EXAMPLES[RESET]
                store -a /tmp/asd this is the content
                store /tmp/asd this has spaces
                store -a /tmp/asd -stdin
                store /tmp/asd -stdin
    )";
        this->valid_args = { "-a", "--append", "-stdin" };
    }

private:
    void _impl(strlist argv) {
        bool append = false;
        // Check if append is enabled. If it is, handle accordingly and remove it from list.
        if(List::in_list<std::string>(argv, "-a") || List::in_list<std::string>(argv, "--append")) {
            append = true;
            List::remove_from_list<std::string>(argv, "-a");
            List::remove_from_list<std::string>(argv, "--append");
        }

        // The first argument passed must be the output filename and then content.
        // If content is -stdin, then user input is taken until eof is reached.
        if(argv.size() < 2) {
            std::cerr << "fsh: store: missing arguments" << std::endl;
            std::cout << "Usage: store [-a/--append] <filename> [-stdin/*content]" << std::endl;
            return;
        }

        std::fstream file(
            argv[0], (append) ? std::ios::app : std::ios::out);
        
        if(!file.is_open()) {
            std::cerr << "fsh: could not open file: " << argv[0] << std::endl;
            return;
        }

        size_t nbytes = 0 ;
        if(List::in_list<std::string>(argv, "-stdin")) {
            std::string tmp;
            while(std::getline(std::cin, tmp)) {
                file << tmp << "\n";
                nbytes += tmp.size() + 1;
            }
            while(std::cin.eof()) {
                clearerr(stdin);
                std::cin.clear();
            }
        } else {
            for(size_t i = 1; i < argv.size(); i++) {
                file << argv[i];
                if(i < argv.size()-1) file << " ";
                nbytes += argv[i].size() + 1;
            }
        }
        file.close();
    }
};

extern "C" Command* plugin_create() { return new Store(); }
extern "C" void plugin_destroy(Command* cmd) { delete cmd; }