CC= gcc -std=c99

CFLAGS= -W -Wall -Werror  -pedantic 
SRC = $(wildcard */*.c)
OBJ = $(SRC:.c=.o)
TARGETS = Elementary

LIBS = -lopencv_core -lopencv_highgui -lallegro_audio -lallegro_acodec  -lallegro_font -lallegro_ttf -lallegro -lallegro_main -lallegro_image -lallegro_primitives

all: $(TARGETS)


Elementary: $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f *~ *.o

destroy: clean
	rm -f $(TARGETS)
