MODULES=wget.o wget_switch.o rest_server.o
LIBS=-l microhttpd

.c.o:
	gcc -c -o $*.o $<

all: $(MODULES)
	gcc -o happy happy.c $(MODULES) $(LIBS)

clean:
	rm happy
	rm *.o