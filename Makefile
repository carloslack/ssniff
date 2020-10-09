#
# Ssnif
#
OUT=ssnif
SRCDIR=./src
SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:.c=.o)
CFLAGS=-I$(SRCDIR) -Wall -g -ggdb
CC=$(shell which gcc)

all:
	$(CC) -o $(OUT) $(SRCS) $(CFLAGS)

clean:
	rm -f $(OUT)
