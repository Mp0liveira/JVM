CC:=g++
INCDIRS:=headers
OPT:=-O0
DEBUG:=-g
LIBS:=
CFLAGS:=-Wall -fdiagnostics-color=always $(OPT) $(foreach D,$(INCDIRS),-I$(D))


ODIR=obj
CDIR=src
DEPDIR=dep


CFILES=$(foreach D,$(CDIR),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp, $(ODIR)/%.o, $(notdir $(CFILES)))
INCLUDES=$(foreach D,$(INCDIRS), $(shell find $(D) -type f -name "*"))

BINARY=bin

debug: CFLAGS += $(DEBUG)
debug: all

all: | $(ODIR) $(BINARY) 

$(ODIR):
	mkdir -p $@

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

$(ODIR)/%.o: $(CDIR)/%.cpp $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rvf $(BINARY) $(ODIR)/*.o

run: all
	./$(BINARY)


.PHONY: clean run all

