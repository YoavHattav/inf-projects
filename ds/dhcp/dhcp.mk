#make file - sortedlist

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= '-DNDBUG -O3'
CC=gcc
TARGET=dhcp
TRIE= trie
INCLUDE_DIR = /home/codezila/git/ds/include/
SHARED_OBJ_DIR = /home/codezila/git/ds/lib/
INNER_OBJ_DIR= ./obj/

$(TARGET).out: $(SHARED_OBJ_DIR)lib$(TARGET).so $(INNER_OBJ_DIR)$(TARGET)_test.o
	$(CC) $(CFLAGS) $(INNER_OBJ_DIR)$(TARGET)_test.o -L$(SHARED_OBJ_DIR) -l$(TARGET) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@ -lm

$(SHARED_OBJ_DIR)lib$(TARGET).so: $(INNER_OBJ_DIR)$(TARGET).o
	$(CC) $(CFLAGS) -L$(SHARED_OBJ_DIR) -shared $<  -l$(TRIE) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@ -lm

$(INNER_OBJ_DIR)$(TARGET).o: $(INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $(TARGET).c -I$(INCLUDE_DIR) -o $@ -lm

$(INNER_OBJ_DIR)$(TARGET)_test.o: $(INCLUDE_DIR)$(TARGET).h $(TARGET)_test.c
	$(CC) -c $(CFLAGS) $(DEBUG) $(TARGET)_test.c -I$(INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(INNER_OBJ_DIR)$(TARGET)_test.o $(TARGET).out $(SHARED_OBJ_DIR)lib$(TARGET).so
		
release:
	make -f $(TARGET).mk DEBUG=$(RELEASE)