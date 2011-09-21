run:gsl_example
	./gsl_example

gsl_example:gsl_example.o
	gcc gsl_example.o -lgsl -lgslcblas -lm -o gsl_example

gsl_example.o:gsl_example.c
	gcc -Wall -c gsl_example.c
