CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -fPIC
LDFLAGS = -shared

LIBRARY = libelectro.so
HEADERS = electrotest.h
SOURCES = electrotest.c

all: $(LIBRARY)

$(LIBRARY): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

install: $(LIBRARY) $(HEADERS)
	install -D $(LIBRARY) /usr/lib/$(LIBRARY)
	install -D $(HEADERS) /usr/include/$(HEADERS)

uninstall:
	rm /usr/lib/$(LIBRARY)
	rm /usr/include/$(HEADERS)

clean:
	rm -f $(LIBRARY)

.PHONY: all install uninstall clean
