# makefile The Boys
# Carlos Maziero - DINF/UFPR, 2024/2

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -std=c99
LDLIBS  = -lm
MAIN    = theboys
ENTREGA = $(MAIN)

# lista de arquivos de cabeçalho (a completar)
HDR = extras/fila.h extras/fprio.h extras/conjunto.h entidades/herois.h entidades/base.h eventos/evento.h eventos/missao.h entidades/mundo.h

# lista de arquivos-objeto (a completar)
# não inclua conjunto.o, senão ele será removido com "make clean"
OBJ = fila.o fprio.o herois.o base.o evento.o missao.o mundo.o  

# construir o executável
$(MAIN): $(MAIN).o $(OBJ) extras/conjunto.o
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).o $(OBJ) extras/conjunto.o $(LDLIBS)

# construir os arquivos-objeto (a completar)
$(MAIN).o: $(MAIN).c $(HDR)
	$(CC) $(CFLAGS) -c $(MAIN).c

# construir os TADs
fila.o: extras/fila.c extras/fila.h
	$(CC) $(CFLAGS) -c extras/fila.c
fprio.o: extras/fprio.c extras/fprio.h
	$(CC) $(CFLAGS) -c extras/fprio.c
herois.o: entidades/herois.c entidades/mundo.h entidades/base.h eventos/missao.h eventos/evento.h extras/conjunto.h extras/fprio.h extras/fila.h 
	$(CC) $(CFLAGS) -c entidades/herois.c
base.o: entidades/base.c entidades/herois.h entidades/mundo.h eventos/missao.h eventos/evento.h extras/conjunto.h extras/fprio.h extras/fila.h
	$(CC) $(CFLAGS) -c entidades/base.c
missao.o: eventos/missao.c entidades/herois.h entidades/mundo.h entidades/base.h eventos/evento.h extras/conjunto.h extras/fprio.h extras/fila.h
	$(CC) $(CFLAGS) -c eventos/missao.c
mundo.o: entidades/mundo.c entidades/herois.h entidades/base.h eventos/missao.h eventos/evento.h extras/conjunto.h extras/fprio.h extras/fila.h
	$(CC) $(CFLAGS) -c entidades/mundo.c
evento.o: eventos/evento.c entidades/herois.h entidades/mundo.h entidades/base.h eventos/missao.h extras/conjunto.h extras/fprio.h extras/fila.h
	$(CC) $(CFLAGS) -c eventos/evento.c


# executar
run: $(MAIN)
	./$(MAIN)

# testar no Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# gerar arquivo TGZ para entregar
tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h conjunto.o makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# limpar arquivos temporários
clean:
	rm -f *~ $(OBJ) $(MAIN) /tmp/$(USER)/$(ENTREGA) $(ENTREGA).tgz

