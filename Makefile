CC = cc

CFLAGS  = -std=c99 -O3 -Wall 
LDFLAGS = -lm

NAME    = libmaple

UNAME_S = $(shell uname -s)

# respect traditional UNIX path usage
INCDIR  = /usr/local/include
LIBDIR  = /usr/local/lib

ifeq ($(UNAME_S),Darwin)
$(NAME).dylib: clean
	$(CC) -c -dynamiclib -o $@ $(CFLAGS) $(LDFLAGS)
endif
ifeq ($(UNAME_S),Linux)
$(NAME).so: clean
	$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS)
endif

.PHONY: install
install: 
	cp maple.h $(INCDIR)
ifeq ($(UNAME_S),Linux)
	cp maple.h $(INCDIR)
	cp $(NAME).so $(LIBDIR)
endif
ifeq ($(UNAME_S),Darwin)
	cp maple.h $(INCDIR)
	cp $(NAME).dylib $(LIBDIR)
endif

uninstall:
	rm -f $(INCDIR)/maple.h
ifeq ($(UNAME_S),Linux)
	rm -f $(INCDIR)/$(NAME).so
endif
ifeq ($(UNAME_S),Darwin)
	rm -f $(INCDIR)/$(NAME).dylib
endif

.PHONY: test
test: clean
	$(CC) -g -o tests/tests maple.c tests/tests.c tests/crosscheck.c $(LDFLAGS)
	tests/tests
	rm -f tests/tests

.PHONY: clean
clean:
	rm -f $(NAME).dylib
	rm -f $(NAME).so
	rm -f example
	rm -f tests/tests

.PHONY: example
example: clean
	$(CC) -g -o $@ maple.c examples/all.c $(LDFLAGS)
