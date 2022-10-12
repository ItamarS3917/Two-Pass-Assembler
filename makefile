FLAGS = -ansi -Wall -pedantic
CFILES = $(shell ls *.c)
OFILES = $(patsubst %.c, %.o, $(CFILES))
HFILES = $(shell ls *.h)

assembler: $(OFILES) $(HFILES)
	gcc $(FLAGS) -g $(OFILES) -o $@
	

%.o:%.c %.h
	gcc $(FLAGS) -g -c $< -o $@	

clean:
	rm -rf *.o
