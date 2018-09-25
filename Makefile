MODULES=wget.o wget_switch.o

.c.o:
	gcc -c -o $*.o $<

all: $(MODULES)
	gcc -o happy happy.c $(MODULES)

clean:
	rm happy
	rm *.o