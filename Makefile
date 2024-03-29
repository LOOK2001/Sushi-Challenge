# A simple Makefile for SDL projects

# set the compiler
CC = g++

# set the compiler flags
CFLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lSDL2_ttf -lm

# add header files here
HDRS =

# add source files here
SRCS = main.cpp Global.cpp GameObject.cpp Image.cpp Character.cpp Application.cpp TileHandler.cpp Sprite.cpp Map.cpp Pickup.cpp Particle.cpp ParticleEmitter.cpp Weapon.cpp Camera.cpp TextHandler.cpp Player.cpp Enemy.cpp StateMachine.cpp Scene.cpp

# generate names of object files
OBJS = $(SRCS:.cpp=.o)

# name of executable
EXEC = my_game

# default recipe
all: $(EXEC)

#showfont: showfont.c Makefile
#    $(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

#glfont: glfont.c Makefile
#    $(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC)
	rm -f $(OBJS)
