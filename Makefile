#
# Ssnif
#
#
OUT=ssniff
SRCDIR=./src
LIBSDIR=./libs
SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:.c=.o)
CFLAGS=-I$(SRCDIR) -Wall
CC=$(shell which gcc)


all:
	$(CC) -o $(OUT) $(SRCS) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)
	rm -f $(LIBSDIR)/*.so
	find . -name "*.*~" -exec rm {} \;
