
SERVER_DIR?=./server

all: install run_server

install:
	cd $(SERVER_DIR); npm install

run_server:
	cd $(SERVER_DIR); npm run server

.PHONY: install run_server
