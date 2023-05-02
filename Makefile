TESTSRCDIR := src/
TESTOBJDIR := obj/
TESTBINDIR := bin/

LIBSRCDIR := lib/src/
LIBOBJDIR := lib/obj/
LIBBINDIR := lib/bin/

TESTSOURCES := $(shell find "$(TESTSRCDIR)/" -name "*.c")
TESTOBJECTS := $(TESTSOURCES:$(TESTSRCDIR)/%.c=$(TESTOBJDIR)/%.c.o)

LIBSOURCES := $(shell find "$(LIBSRCDIR)/" -name "*.c")
LIBOBJECTS := $(LIBSOURCES:$(LIBSRCDIR)/%.c=$(LIBOBJDIR)/%.c.o)

CC := gcc
CCARGS := -g -O3 -Wall -Wextra -Wpedantic -I$(TESTSRCDIR)/include/ -I$(LIBSRCDIR)/include/

LD := gcc
LDARGS :=

AR := ar
ARARGS := 

.PHONY: all cleanRun genclang run clean mkdirs library binary install

all: mkdirs library binary
cleanBuild: clean all
cleanRun: clean run

genclang: mkdirs
	bear -- clang -c $(CCARGS) $(TESTSRCDIR)/rayextest.c -o $(TESTOBJDIR)/rayextest.c.o
	rm $(TESTOBJDIR)/rayextest.c.o

$(TESTOBJDIR)/%.c.o: $(TESTSRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c $(CCARGS) $< -o $@

$(LIBOBJDIR)/%.c.o: $(LIBSRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c -fPIC $(CCARGS) $< -o $@

binary: library $(TESTBINDIR)/rayextest

$(TESTBINDIR)/rayextest: $(TESTOBJECTS)
	mkdir -p "$(dir $@)"
	echo "Using compiler $(CC) $(CCARGS)"
	echo "Using linker $(LD) $(LDARGS)"
	$(LD) $(LDARGS) $^ -o $@ -L$(LIBBINDIR)/ -lrayex -lraylib

library: $(LIBBINDIR)/librayex.so $(LIBBINDIR)/librayex.a

$(LIBBINDIR)/librayex.so: $(LIBOBJECTS)
	mkdir -p "$(dir $@)"
	$(LD) $(LDARGS) -shared $^ -o $@ -lraylib

$(LIBBINDIR)/librayex.a: $(LIBOBJECTS)
	mkdir -p "$(dir $@)"
	$(AR) $(ARARGS) r $@ $^

run: binary
	LD_LIBRARY_PATH=$(LIBBINDIR)/ ./$(TESTBINDIR)/rayextest

clean:
	rm -f vgcore*
	rm -fr $(TESTBINDIR)/ $(TESTOBJDIR)/
	rm -fr $(LIBBINDIR)/ $(LIBOBJDIR)/

install:
	mkdir -p /usr/local/include/rayex/
	cp lib/bin/librayex.so /usr/local/lib/
	cp lib/bin/librayex.a /usr/local/lib/
	cp -r lib/src/include/rayex/* /usr/local/include/rayex/
