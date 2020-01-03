SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

test: $(OBJS)
	gcc -o $@ $(OBJS)
%.o: %.c
	gcc -c $<
