# makefile generico para os TADs
# Carlos Maziero - DINF/UFPR

CC     = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LIB    = fprio
BIN    = testa-fprio
OUT    = saida.txt

$(BIN):   $(BIN).o $(LIB).o
$(BIN).o: $(BIN).c $(LIB).h
$(LIB).o: $(LIB).c $(LIB).h

teste: $(BIN)
	@./$(BIN) > $(OUT)
	diff $(BIN).txt $(OUT)

valgrind: $(BIN)
	valgrind --leak-check=full --track-origins=yes ./$(BIN)

clean:
	rm -f *.o *~ $(BIN) $(OUT)
