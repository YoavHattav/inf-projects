#make file - dll

CFLAGS=-ansi -pedantic-errors -Wall -Wextra -pthread
DEBUG=	-g
RELEASE= '-DNDBUG -O3'
CC=gcc
TARGET=dll_pro_cons_mutex
DLL=dll
INCLUDE_DS_DIR = /home/codezila/git/ds/include/

SHARED_SYS_OBJ_DIR = ../../lib/
SHARED_DS_OBJ_DIR = /home/codezila/git/ds/lib/
INNER_OBJ_DIR= ./obj/

.PHONY: debug
$(TARGET).out:  $(SHARED_DS_OBJ_DIR)lib$(DLL).so
	$(CC) $(CFLAGS) -o $@ -I$(INCLUDE_DS_DIR) -L$(SHARED_DS_OBJ_DIR)  -Wl,-rpath=$(SHARED_DS_OBJ_DIR) $(TARGET).c -l$(DLL)

.PHONY: clean
clean:
	rm $(TARGET).out

release:
	make -f $(TARGET).mk DEBUG=$(RELEASE)