CC = gcc

CXX=g++

CFLAGS= -g -w -pthread -lseadp

CFLAGS+=-I./lib

CXXFLAGS= -g -w -pthread -lseadp  -std=c++11

all: seadp_client seadp_server

seadp_server: seadp_server.o 
	$(CXX) $^ -o ./bin/$@ $(CXXFLAGS)

seadp_client: seadp_client.o
	$(CXX) $^ -o ./bin/$@ $(CXXFLAGS)


%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	make -C $(CHANNEL_DIR) clean
	rm -f *.o
