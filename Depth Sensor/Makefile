CC=g++
ARCH=-arch x86_64

INCLUDE_FLAGS = -I/usr/include/ni
LDFLAGS = -L/usr/lib -lOpenNI
CFLAGS = -c -Wall $(INCLUDE_FLAGS)

TARGET = main
SOURCES = $(TARGET).cpp
OBJECTS = $(SOURCES:.cpp=.o)

all : $(SOURCES) $(TARGET)

clean: 
	$(RM) *.o *~ $(TARGET)

$(TARGET) : $(OBJECTS) Makefile
	$(CC) $(ARCH) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@