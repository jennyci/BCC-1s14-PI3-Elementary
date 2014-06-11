TARGETS = Elementary

CC = gcc

FLAGS = -std=c99

LIBS = -lopencv_core -lopencv_highgui -lallegro -lallegro_main -lallegro_image -lallegro_primitives

all: $(TARGETS)

camera.o: lib/camera.c lib/camera.h
	$(CC) $(FLAGS) $< -c

Elementary: src/elementary.c bin/camera.o
	$(CC) $(FLAGS) $^ -o $@ -Wall -Werror -O2 -pedantic $(LIBS)

clean:
	rm -f *~ *.o

destroy: clean
	rm -f $(TARGETS)
