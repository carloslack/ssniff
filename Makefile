#
# Ssnif
#
#
OUT=ssniff
SRCDIR=./src
LIBSDIR=./libs
SRCS=$(wildcard $(SRCDIR)/*.c)
LIBS=$(wildcard $(LIBSDIR)/*.c)
OBJS=$(SRCS:.c=.o)
CFLAGS=-I$(SRCDIR) -I$(LIBSDIR) -Wall -g -ggdb -lproto
LDFLAGS=-L$(LIBSDIR)
CC=$(shell which gcc)

.PHONY : libs

all: libs
	$(CC) -o $(OUT) $(SRCS) $(CFLAGS) $(LDFLAGS)

libs:
	$(CC) -o $(LIBSDIR)/libproto.so $(LIBS) $(LDFLAGS) -shared -fPIC

clean:
	rm -f $(OUT)
	rm -f $(LIBSDIR)/*.so
