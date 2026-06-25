CC = g++
CFLAGS = -std=c++17 -Wall -Iinclude -Itests
COV_FLAGS = -fprofile-arcs -ftest-coverage

SRC = src
TST = tests
BIN = build

SOURCES = $(SRC)/AlertaManager.cpp $(SRC)/Maquina.cpp $(SRC)/Operador.cpp \
          $(SRC)/ProtocoloMarcha.cpp $(SRC)/Relatorio.cpp $(SRC)/Sensor.cpp \
          $(SRC)/Sessao.cpp $(SRC)/SistemaMonitor.cpp $(SRC)/tela.cpp

TEST_SRC = $(TST)/testesSistema.cpp

all: $(BIN)/sistema_monitor

$(BIN)/sistema_monitor: src/main.cpp $(SOURCES)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) src/main.cpp $(SOURCES) -o $(BIN)/sistema_monitor -lpthread

$(BIN)/testes: $(SOURCES) $(TEST_SRC)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(COV_FLAGS) $(SOURCES) $(TEST_SRC) -o $(BIN)/testes

test: $(BIN)/testes
	./$(BIN)/testes
	gcovr -r . --filter src/ --print-summary

clean:
	rm -rf $(BIN) *.gcda *.gcno

.PHONY: all test clean