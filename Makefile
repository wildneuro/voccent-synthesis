# Define the compiler
CC = clang++

# Define any compile-time flags
CFLAGS = -Wall -g -std=c++17

# Define any directories containing header files
INCLUDES = -I.

# Define library paths in addition to /usr/lib
# if your libraries are in /user/local/lib then use LFLAGS = -L/usr/local/lib
LFLAGS =

# Define any libraries to link into executable
LIBS = -lfftw3 -lm

# Define the source files
SRCS = main.cpp soundsynthesis.cpp wavefilehandle.cpp

# Define the object files (with the source directory and source file extension replaced)
OBJS = $(SRCS:.c=.o)

# Define the executable file
MAIN = main

.PHONY: clean

all: $(MAIN)
	@echo Compilation completed.

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)
