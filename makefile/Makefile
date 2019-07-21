CPPFLAGS = -Iinclude
CFLAGS = -g -Wall
LDFLAGS = -L../lib -lcalc
CC = gcc


src = $(wildcard *.c)
obj = $(patsubst %.c,%.o,$(src))
target = calc
calc:$(obj)
	$(CC) $(obj) -o $(target)

%.o:%.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

.PHONY : clean
clean:
	-rm -f $(target)
	-rm -f *.o

test:
	echo $(src)
	echo $(obj)


