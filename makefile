CC      = gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: Hello

Hello: hello.cpp
    $(CC) hello.cpp

clean veryclean:
    $(RM) Hello