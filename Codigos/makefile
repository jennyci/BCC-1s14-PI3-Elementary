TARGETS = principal

CC = gcc

FLAGS = -std=c99

LIBS = -lopencv_core -lopencv_highgui -lallegro -lallegro_main -lallegro_image -lallegro_primitives

all: $(TARGETS)

camera.o: cameraFunctions.c cameraLibs.h
	$(CC) $(FLAGS) $< -c

jogo: principal.c camera.o
	$(CC) $(FLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *~ *.o

destroy: clean
	rm -f $(TARGETS)
