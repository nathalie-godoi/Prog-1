# makefile The Boys
# Carlos Maziero - DINF/UFPR, 2024/2

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -std=c99
LDLIBS  = -lm
MAIN    = theboys
ENTREGA = $(MAIN)

# lista de arquivos de cabeçalho (a completar)
HDR = fila.h fprio.h conjunto.h herois.h base.h evento.h missao.h mundo.h

# lista de arquivos-objeto (a completar)
# não inclua conjunto.o, senão ele será removido com "make clean"
OBJ = fila.o fprio.o herois.o base.o evento.o missao.o mundo.o  

# construir o executável
$(MAIN): $(MAIN).o $(OBJ) conjunto.o
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).o $(OBJ) conjunto.o $(LDLIBS)

# construir os arquivos-objeto (a completar)
$(MAIN).o: $(MAIN).c $(HDR)
	$(CC) $(CFLAGS) -c $(MAIN).c

# construir os TADs
fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c
fprio.o: fprio.c fprio.h
	$(CC) $(CFLAGS) -c fprio.c
herois.o: herois.c mundo.h base.h missao.h evento.h conjunto.h fprio.h fila.h 
	$(CC) $(CFLAGS) -c herois.c
base.o: base.c herois.h mundo.h missao.h evento.h conjunto.h fprio.h fila.h
	$(CC) $(CFLAGS) -c base.c
missao.o: missao.c herois.h mundo.h base.h evento.h conjunto.h fprio.h fila.h
	$(CC) $(CFLAGS) -c missao.c
mundo.o: mundo.c herois.h base.h missao.h evento.h conjunto.h fprio.h fila.h
	$(CC) $(CFLAGS) -c mundo.c
evento.o: evento.c herois.h mundo.h base.h missao.h conjunto.h fprio.h fila.h
	$(CC) $(CFLAGS) -c evento.c


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

