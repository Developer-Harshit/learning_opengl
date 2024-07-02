CC = gcc
CXX = gcc

COMPILE_FLAGS = -Wall -ggdb -O3
LINK_FLAGS = -lglfw3 -lopengl32 -lglu32 -lgdi32 

glfw = Z:/Blender/CPP/external/glfw
glfw_inc = $(glfw)/include
glfw_lib = $(glfw)/lib

glad = Z:/Blender/CPP/external/glad
glad_inc = $(glad)/include

INCLUDES = -I$(glfw_inc) -I$(glad_inc)
LIBRARIES = -L$(glfw_lib)

FILES = src/*.c

_debug: 
	gcc $(FILES) -D _DEBUG $(LINK_FLAGS) $(INCLUDES) $(LIBRARIES)  -o bin/Debug.exe
_release:
	gcc $(FILES) $(COMPILE_FLAGS)  $(LINK_FLAGS) $(INCLUDES) $(LIBRARIES) -o bin/Release.exe

clean: 
	rm ./bin/Release.exe 
	rm ./bin/Debug.exe 

debug : _debug
	@clear
	./bin/Debug.exe 

run : _release
	@clear
	./bin/Release.exe 
