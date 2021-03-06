#make file - priority queue

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= '-DNDBUG -O3'
CC=gcc
TARGET=priorityq
SORTED=sortedlist
DLL= dll
INCLUDE_DIR = /home/codezila/git/ds/include/
SHARED_OBJ_DIR = /home/codezila/git/ds/lib/
RELEASE_SHARED_OBJ_DIR = ../librelease/
INNER_OBJ_DIR = ./obj/

$(TARGET).out: $(SHARED_OBJ_DIR)lib$(TARGET).so $(INNER_OBJ_DIR)$(TARGET)_test.o $(SHARED_OBJ_DIR)lib$(SORTED).so $(SHARED_OBJ_DIR)lib$(DLL).so
	$(CC) $(CFLAGS) -o $@ $(INNER_OBJ_DIR)$(TARGET)_test.o -L$(SHARED_OBJ_DIR) -l$(TARGET) -l$(SORTED) -l$(DLL) -Wl,-rpath=$(SHARED_OBJ_DIR)

$(SHARED_OBJ_DIR)lib$(TARGET).so: $(INNER_OBJ_DIR)$(TARGET).o
	$(CC) $(CFLAGS) -L$(SHARED_OBJ_DIR) -shared $< -l$(SORTED) -l$(DLL) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET).o: $(INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $(TARGET).c -I$(INCLUDE_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET)_test.o: $(INCLUDE_DIR)$(TARGET).h $(TARGET)_test.c
	$(CC) -c $(CFLAGS) $(DEBUG) $(TARGET)_test.c -I$(INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(TARGET).out $(INNER_OBJ_DIR)$(TARGET)_test.o $(SHARED_OBJ_DIR)lib$(TARGET).so
	
release:
	make -f $(TARGET).mk DEBUG=$(RELEASE)  SHARED_OBJ_DIR=$(RELEASE_SHARED_OBJ_DIR)