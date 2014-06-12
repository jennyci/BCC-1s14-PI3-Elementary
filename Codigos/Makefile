CC= gcc -std=c99

CFLAGS= -W -Wall -Werror -pedantic 

TARGETS = Elementary

LIBS = -lopencv_core -lopencv_highgui  -lallegro_font -lallegro_ttf -lallegro -lallegro_main -lallegro_image -lallegro_primitives

all: $(TARGETS)

camera.o: libs/camera.c libs/camera.h
	$(CC) $(CFLAGS) $< -c

Elementary: src/elementary.c camera.o
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f *~ *.o

destroy: clean
	rm -f $(TARGETS)
