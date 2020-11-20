

CC=gcc
CFLAGS=-Wall -Wextra
TARGET=new_lock

all : $(TARGET).c 
	@ $(CC) -g $(CFLAGS) $(TARGET).c -o $(TARGET)

.PHONY : clean
clean:
	@ rm -f $(TARGET)
	@ rm -rf $(TARGET).dSYM
