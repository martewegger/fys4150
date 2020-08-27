
all: compile execute

compile:
	c++ -o main.out main.cpp class_code.cpp

execute:
	./main.out
