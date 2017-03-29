   CC=g++
ARCH=-arch x86_64

INCLUDE_FLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lzbar
LDFLAGS += `pkg-config opencv --libs`
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