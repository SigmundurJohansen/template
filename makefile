CC      = gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: Hello

Hello: Hello.c
    $(CC) $(CFLAGS) -o Hello hello.cpp

clean veryclean:
    $(RM) Hello