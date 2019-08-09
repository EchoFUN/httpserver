cmake_minimum_required(VERSION 3.14)
project(httpserver)

#[[

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	@echo " Linking..."; $(CC) $^ $(LINK) -o $(BINDIR)/$(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<"; $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo " Cleaning..."; rm -r $(BUILDDIR) $(BINDIR)/$(TARGET)*

.PHONY: clean
]]

set(CC "g++")
set(SRCDIR "src")
set(BINDIR "bin")
set(TARGET "httpserver")

# CMAKE_SYSTEM_NAME equals $(shell name)

# Debug Flags
set(DEBUGFLAGS "-g3 -O0 -Wall -fmudflap")

# Production Flags
set(PRODFLAGS "-Wall -O2 -fstack-check -fstack-protector-all")

set(CFLAGS "-std=c++14 -Iinclude/ ${PRODFLAGS}")
set(LINK ${PRODFLAGS})

set(SRCEXT "cpp")
set(SOURCES find_file())
set(OBJECTS "")





set(CMAKE_CXX_STANDARD 14)

add_executable(httpserver src/main.cpp)