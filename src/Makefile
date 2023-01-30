# Makefile for FTCR-LMPPDA program
# The executable file is shown as ./main in Linux system
VERSION =1.00
CC =gcc
DEBUG =-DUSE_DEBUG
CFLAGS =-Wall -O

SOURCES =$(wildcard ./*.c)
INCLUDES =-I/usr/include/
LIB_NAMES =-lm -loqs
LIB_PATH =-L/usr/local/lib/


OBJ =$(patsubst %.c, %.o, $(SOURCES))
TARGET =FTCR-LMPPDA

# compile
%.o: %.c
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

# links
$(TARGET):$(OBJ)
	$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o ./$(TARGET)$(VERSION)
	@rm -rf $(OBJ)


.PHONY:clean
clean:
	@echo "Remove linked and compiled files....."
	rm -rf $(OBJ) $(TARGET) ./