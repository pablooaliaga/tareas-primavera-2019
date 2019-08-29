# Observaciones importantes:
#
# - Para usar este Makefile es necesario definir la variable
#   de ambiente NSYSTEM con el directorio en donde se encuentra
#   la raiz de nSystem.  Por ejemplo en sh esto se hace con:
#
#   $ NSYSTEM=$HOME/nsystem64 ; export NSYSTEM
#
# - Compile ingresando el comando make
#
# - Depure usando gdb o ddd.

CFLAGS= -ggdb -pedantic -Wall -std=c99 -I$(NSYSTEM)/include -I$(NSYSTEM)/src
LFLAGS= -ggdb

all: testh2o
#	./testh2o

testh2o.o: testh2o.c h2o.h
	gcc $(CFLAGS) -c testh2o.c

h2o.o: h2o.c h2o.h
	gcc $(CFLAGS) -c h2o.c

testh2o: testh2o.o h2o.o
	gcc $(LFLAGS) testh2o.o h2o.o $(NSYSTEM)/lib/libnSys.a -o testh2o

clean:
	rm -f *.o *~

cleanall:
	rm -f *.o *~ testh2o
