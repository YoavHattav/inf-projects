
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -pthread
DEBUG=	-g
RELEASE= '-DNDBUG -O3'
CC=gcc
TARGET=pro_cons_circular_2thread_working
CIRCULAR_OVERFLOW=circular_overflow
INCLUDE_DS_DIR = /home/codezila/git/ds/include/

SHARED_SYS_OBJ_DIR = ../../lib/
SHARED_DS_OBJ_DIR = /home/codezila/git/ds/lib/
INNER_OBJ_DIR= ./obj/

.PHONY: debug
$(TARGET).out:  
	$(CC) $(CFLAGS) -o $@ $(TARGET).c $(CIRCULAR_OVERFLOW).c 

.PHONY: clean
clean:
	rm $(TARGET).out

release:
	make -f $(TARGET).mk DEBUG=$(RELEASE)