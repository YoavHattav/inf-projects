#make file - priority queue

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= -DNDBUG -O3
CC=gcc
TARGET=task
SP_INCLUDE_DIR = ../include/
DS_INCLUDE_DIR = ../../ds/include/
LIB_DIR = ../lib/
UID=uid

$(LIB_DIR)lib$(TARGET).so: $(TARGET).o $(LIB_DIR)lib$(UID).so
	$(CC) $(CFLAGS) -shared $< -L$(LIB_DIR) -l$(UID) -Wl,-rpath=$(LIB_DIR) -o $@

$(TARGET).o: $(SP_INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $(TARGET).c -I$(DS_INCLUDE_DIR) -I$(SP_INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	$(TARGET).o $(LIB_DIR)lib$(TARGET).so
