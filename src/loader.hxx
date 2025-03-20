#pragma once

#include "interface.hxx"

namespace fs = std::filesystem;
typedef std::unordered_map<std::string, Command*> commands;
std::map<std::string, void*> libraries;
commands builtins;

namespace PluginLoader {

    void load_plugin(const std::string& plugin_file) {
        void* handle = dlopen(plugin_file.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Failed to load plugin " << plugin_file << ": " << dlerror() << std::endl;
            return;
        }

        using CreateFunc = Command* (*)();
        CreateFunc create = (CreateFunc) dlsym(handle, "plugin_create");
        if (!create) {
            std::cerr << "Failed to load plugin " << plugin_file << ": " << dlerror() << std::endl;
            dlclose(handle);
            return;
        }
        Command* cmd = create();
        builtins[cmd->name] = cmd;
        libraries[cmd->name] = handle;
        debug("Loaded plugin: " + cmd->name);
    }

    void load(const std::string& path) {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.path().extension() == ".so") {
                std::string path = entry.path().string();
                load_plugin(path);
            }
        }
    }
    void unload() {
        for (auto& [name, cmd] : builtins) {
            using DestroyFunc = void (*)(Command*);
            DestroyFunc destroy = (DestroyFunc) dlsym(libraries[name], "plugin_destory");
            if (destroy)
                destroy(cmd);
            dlclose(libraries[name]);
        }
    }
}