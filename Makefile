GCC    = gcc
CFLAGS = -Iinclude -Wall
EXEC   = ode

SOURCES=src/ballistic.c src/integration.c src/main.c src/nbody.c src/vector2d.c
OBJECTS=$(patsubst src/%.c, bin/%.o, $(SOURCES))

all: $(EXEC)

$(EXEC): bin/$(OBJECTS)
	$(GCC) $(CFLAGS) -o bin/$(EXEC) $(OBJECTS) $(LIBS)

bin/%.o: src/%.c
	$(GCC) $(CFLAGS) -c $< -o $@
