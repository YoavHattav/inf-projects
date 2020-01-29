#make file - sortedlist

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= -DNDBUG -03
CC=gcc
TARGET=scheduler
HEAPIFY=heapify
DS_INCLUDE_DIR = /home/codezila/git/ds/include/
SP_INCLUDE_DIR = /home/codezila/git/system_programming/include/
SP_LIB_DIR = /home/codezila/git/system_programming/lib/
DS_LIB_DIR = /home/codezila/git/ds/lib/
TASK=task
NOPIE= '-ansi -pedantic-errors -Wall -Wextra -no-pie'

$(TARGET).out: $(SP_LIB_DIR)lib$(TARGET).so $(TARGET)_test.o
	$(CC) $(CFLAGS) -o $@ $(TARGET)_test.o -L$(SP_LIB_DIR) -L$(DS_LIB_DIR) -Wl,-rpath=$(SP_LIB_DIR) -l$(TARGET) -Wl,-rpath=$(DS_LIB_DIR) -l$(HEAPIFY)

$(SP_LIB_DIR)lib$(TARGET).so: $(TARGET).o 
	$(CC) $(CFLAGS) -shared -o $@ $< -L$(DS_LIB_DIR) -Wl,-rpath=$(DS_LIB_DIR) -l$(HEAPIFY) -L$(SP_LIB_DIR) -Wl,-rpath=$(SP_LIB_DIR) -l$(TASK)

$(TARGET).o: $(SP_INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $(TARGET).c -I$(SP_INCLUDE_DIR) -I$(DS_INCLUDE_DIR) -o $@

$(TARGET)_test.o: $(SP_INCLUDE_DIR)$(TARGET).h $(TARGET)_test.c
	$(CC) -c $(CFLAGS) $(DEBUG) $(TARGET)_test.c -I$(SP_INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	*.o $(TARGET).out $(SP_LIB_DIR)lib$(TARGET).so

.PHONY: memmap
memmap:
	make -f scheduler.mk CFLAGS=$(NOPIE)