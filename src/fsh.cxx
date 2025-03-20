#include "internals.hxx"

int main(int argc, char* argv[], char* envp[]) {

    if(argc > 1) {
        if(std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version") {
            std::cout << "fsh v0.0.1" << std::endl;
            exit(0);
        }

        if(std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
            std::cout << "Usage: fsh <-d|--debug>" << std::endl;
            exit(0);
        }

        if(std::string(argv[1]) == "-d" || std::string(argv[1]) == "--debug")
            _DEBUG = true;
    }

    utils::setup_config();

    // Load the plugins.
    if(config::autoload_plugins)
        PluginLoader::load(config::plugins_path);

    utils::do_setup();

    while(true) {
        std::cout << config::PS1;
        std::string tmp;
        std::getline(std::cin, tmp);

        if(std::cin.eof())
            exit(0);

        if (std::cin.fail()) {
            std::cin.ignore();
            std::cin.clear();
            continue;
        }

        auto [command, args] = utils::parse_command(tmp);

        // A Builtin command:
        if(List::in_list(_base, command)) {
            builtin_base(command, args);
            continue;
        }

        // Not a valid command:
        if(builtins.find(command) == builtins.end()) {
            std::cerr << "fsh: command not found: " << command << std::endl;
            continue;
        }
        builtins[command]->execute(args);
    }

    return 0;
}