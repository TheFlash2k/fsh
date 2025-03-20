BIN := bin/fsh
PLUGIN_DIR := src/plugins
PLUGIN_SRC := $(wildcard $(PLUGIN_DIR)/*.cxx)
BLACKLIST := [_template] # this is the only plugin that will be skipped during compilation
PLUGIN_SRC := $(filter-out $(addprefix $(PLUGIN_DIR)/, $(addsuffix .cxx, $(BLACKLIST))), $(PLUGIN_SRC))
PLUGIN_BIN := $(patsubst $(PLUGIN_DIR)/%.cxx, bin/plugins/lib%.so, $(PLUGIN_SRC))

CXX := g++
CXXFLAGS := -std=c++23 -Wall
PLUGIN_CXXFLAGS := -shared -fPIC -std=c++23

$(shell mkdir -p bin bin/plugins)

all: $(BIN) $(PLUGIN_BIN)

$(BIN): src/fsh.cxx $(wildcard src/*.hxx)
	$(CXX) $(CXXFLAGS) -o $@ $<

bin/plugins/lib%.so: $(PLUGIN_DIR)/%.cxx
	$(CXX) $(PLUGIN_CXXFLAGS) -o $@ $<

clean:
	rm -rf bin/