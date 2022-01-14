.PHONY: main
main: src/main.cpp include/csvreader.hpp include/FixedPointNumber.hpp
	g++ -Wall -o main --std=c++14 src/main.cpp
	./main

.PHONY: process_data
process_data: src/process_data.cpp include/csvreader.hpp include/FixedPointNumber.hpp
	g++ -Wall -o process_data --std=c++14 src/process_data.cpp
	./process_data

.PHONY: clean
clean:
	rm -f main
	rm -f process_data

.PHONY: clean_data
clean_data:
	rm -f result/golden/*
	rm -f result/golden_double/*
	rm -f result/golden_norm/*
	rm -f result/golden_norm_double/*
	rm -f result/input/*
	rm -f result/input_double/*
	rm -f result/fir_coeff.sv