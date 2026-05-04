CC = cc

CFLAGS  = -O3 -Wall -Wextra -fPIC -O3
TEST_CFLAGS  = -g -Wall -Wextra
LDFLAGS = -lm

NAME    = libmaple

UNAME_S = $(shell uname -s)

# respect traditional UNIX path usage
INCDIR  = /usr/local/include
LIBDIR  = /usr/local/lib

ifeq ($(UNAME_S),Darwin)
$(NAME).dylib: clean
	$(CC) -c -dynamiclib -o $@ maple.c $(CFLAGS) $(LDFLAGS)
else
$(NAME).so: clean
	$(CC) -shared -o $@ maple.c $(CFLAGS) $(LDFLAGS)
endif

.PHONY: install
install: 
	cp maple.h $(INCDIR)
ifeq ($(UNAME_S),Darwin)
	cp $(NAME).dylib $(LIBDIR)
else
	cp $(NAME).so $(LIBDIR)
endif

uninstall:
	rm -f $(INCDIR)/maple.h
ifeq ($(UNAME_S),Darwin)
	rm -f $(LIBDIR)/$(NAME).dylib
else
	rm -f $(LIBDIR)/$(NAME).so
endif

.PHONY: tests
tests: clean
	$(CC) -g -o tests/tests maple.c tests/tests.c tests/crosscheck.c $(TEST_CFLAGS) $(LDFLAGS)
	tests/tests

.PHONY: valgrind
valgrind: tests
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck ./tests/tests 2>&1 | awk -F':' '/definitely lost:/ {print $2}'
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck ./tests/tests

.PHONY: clean
clean:
	rm -f $(NAME).dylib
	rm -f $(NAME).so
	rm -f example
	rm -f tests/tests

.PHONY: example
example: clean
	$(CC) -g -o $@ maple.c examples/all.c $(CFLAGS) $(LDFLAGS)
