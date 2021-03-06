#make file - bitsarray

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= '-DNDEBUG -O3'
CC=gcc
TARGET=heapify
VECTOR=vector
INCLUDE_DIR = /home/codezila/git/ds/include/
SHARED_OBJ_DIR = /home/codezila/git/ds/lib/
INNER_OBJ_DIR= /home/codezila/git/ds/heapify/obj/

#.out creation - debug vers

$(TARGET).out: $(SHARED_OBJ_DIR)lib$(TARGET).so $(INNER_OBJ_DIR)$(TARGET)_test.o $(SHARED_OBJ_DIR)lib$(VECTOR).so
	$(CC) $(CFLAGS) -o $@ $(INNER_OBJ_DIR)$(TARGET)_test.o -L$(SHARED_OBJ_DIR) -l$(TARGET) -Wl,-rpath=$(SHARED_OBJ_DIR)

#Shared lib creation
$(SHARED_OBJ_DIR)lib$(TARGET).so: $(INNER_OBJ_DIR)$(TARGET).o $(SHARED_OBJ_DIR)lib$(VECTOR).so
	$(CC) $(CFLAGS) -L$(SHARED_OBJ_DIR) -shared $< -l$(VECTOR) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@

#Shared lib obj files creation
$(INNER_OBJ_DIR)$(TARGET).o: $(INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $(TARGET).c -I$(INCLUDE_DIR) -o $@

#tests obj files creations
$(INNER_OBJ_DIR)$(TARGET)_test.o: $(INCLUDE_DIR)$(TARGET).h $(TARGET)_test.c
	$(CC) -c $(CFLAGS) $(DEBUG) $(TARGET)_test.c -I$(INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(INNER_OBJ_DIR)$(TARGET)_test.o $(TARGET).out $(SHARED_OBJ_DIR)lib$(TARGET).so

release:
	make -f $(TARGET).mk DEBUG=$(RELEASE) 