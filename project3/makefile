
all: compile execute

kladd: compilekladd executekladd

compilekladd:
	c++ -o kladd.out kladd.cpp -larmadillo

executekladd:
	./kladd.out

compile:
	c++ -o main.out main.cpp class_code.cpp -larmadillo

execute:
	./main.out

plot:
	python3 main.py
