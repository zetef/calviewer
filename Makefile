PROJECT=calviewer
TYPE=cpp

CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -Wextra -Wshadow -pedantic -O3 -Wunreachable-code -Wmain #flags for C and C++
LDFLAGS=-g -s
LDLIBS= -lSDL2 -lSDL2_image -lSDL2_ttf # insert here all libraries needed


SRCS= src/main.cpp src/Calendar.cpp \
	src/Date.cpp src/Event.cpp src/Font.cpp \
	src/Game.cpp src/Media.cpp src/State.cpp \
	src/Text.cpp src/Texture.cpp src/Timer.cpp \
	src/utility.cpp
OBJS=$(subst .$(TYPE),.o,$(SRCS))

all : $(PROJECT)

$(PROJECT): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(PROJECT) $(OBJS) $(LDLIBS)

$(PROJECT).o: $(PROJECT).$(TYPE)

clean:
	$(RM) $(OBJS)

disclean: clean
	$(RM) $(PROJECT)
