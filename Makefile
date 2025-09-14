CC = g++
CFLAGS = -Wall -std=c++11
LIBS = -lGL -lGLU -lglut
TARGET = rubiks_cube
SOURCES = main.cpp cube.cpp input_handler.cpp camera.cpp

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean
