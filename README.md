# FSH

Flash-Shell - A small utility I created as a side project.

## Compile and Run

To compile and run, just type:

```bash
make
```

This will automatically create a new `bin/` folder that will have the `fsh` and it will also compile all the existing plugins
and put them inside the `bin/plugins` folder.

To run it, just simply run:

```bash
cd bin && ./fsh
```

and you'll drop inside fsh.

## Customizations

Currently, the only customizations I have added are modifications to prompt using the `config.hxx` file and creating your own custom
plugins.

### Prompt and other modifications

Looking at [./src/config.hxx](./src/config.hxx), you can see that all the variables are modifiable. Currently, I have not added the integration with `.fshrc` file but in the near future, I will surely do that and then we'll have much more control over everything using files rather than recompiling the project every single time.

### Create Custom Plugins

Each plugin is basically a program that can be integrated directly with fsh.

To create custom plugins, you can get the `[_template].cxx` from the `src/plugins/` directory. Then, all you really need to do is just modify the variables accordingly and inside the `_impl` method, you need to write the actual implementation of the command you're trying to implement.

Make sure to also modify the `plugin_create` export methods because those will be invoked to fetch the class itself when dynamically loading.

To build, just run the `make plugins` command and you'll have your plugin built.

If you want to just build this plugin, you can use the following g++ command:

```bash
g++ -o lib<cmd>.so -fPIC -shared <cmd>.cxx
```

Then just move the `.so` file to the plugins folder and it will be implemented automatically.

During runtime, you can also use the `load-plugin` command to dynamically load a plugin.

## Bugs and other things

This is just a side project and there may be some bugs here and there. If you find any, just open an issue and I'll try and fix them. But, I'm fairly certain I won't be looking after this project that much but whenever I'm bored and want to do something different.

---