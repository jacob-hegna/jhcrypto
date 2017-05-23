BUILDDIR    = ./bin/
SOURCEDIR   = ./src/

DEFINES     =

SDIRS       = $(wildcard $(SOURCEDIR)*/)
VPATH       = $(SOURCEDIR):$(SDIRS):$(foreach dir, $(SDIRS), $(wildcard $(dir)*/))

IFILES      = $(shell find $(SOURCEDIR) -name '*.cpp')

OFILES      = $(subst $(SOURCEDIR), $(BUILDDIR), $(addsuffix .o, $(shell find $(SOURCEDIR)  -name '*.cpp')))

CC          = g++
LINKER      = $(CC)
ARCH        = 64

CCFLAGS     = -c -g -O3 -m$(ARCH) -std=c++14
LINKFLAGS   = -m$(ARCH) -pthread


TARGET = jhcrypto

.PHONY: all clean

all: $(BUILDDIR) $(TARGET)

$(TARGET): $(foreach file, $(OFILES), $(file))
	$(LINKER) $^ $(LINKFLAGS) -o $(BUILDDIR)$@

bin/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(foreach def, $(DEFINES), -D $(def)) $(CCFLAGS) $< -o $@

$(BUILDDIR):
	mkdir $@

clean:
	rm -rf $(BUILDDIR)*
