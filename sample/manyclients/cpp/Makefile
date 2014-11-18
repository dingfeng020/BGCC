ifeq ($(shell if [ -f /opt/compiler/gcc-4.8.2/bin/make ]; then echo "yes"; else echo "no"; fi;), yes)
	INC_PATH_PREFIX = ../../../output/gcc482/include
	LD_PATH = -L../../../output/gcc482/lib/
else
	INC_PATH_PREFIX = ../../../output/include
	LD_PATH = -L../../../output/lib/
endif
SERVER = server
CLIENT = client
LOG = log
CFLAGS = -g -Wall -L.. -lbgcc -lssl -lpthread -lcrypto

INC_PATH += -I$(INC_PATH_PREFIX)
INC_PATH += -I../output-cpp

SRC += ../output-cpp/manyclients.cpp

all: $(CLIENT) $(SERVER)

$(SERVER): $(SERVER).cpp $(SRC)
	$(CXX) -o $@ $^ $(INC_PATH) $(LD_PATH)  $(CFLAGS)

$(CLIENT): $(CLIENT).cpp $(SRC)
	$(CXX) -o $@ $^ $(INC_PATH)  $(LD_PATH) $(CFLAGS)

clean:
	rm -rf $(CLIENT) $(SERVER) $(LOG)
