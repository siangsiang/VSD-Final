main: src/main.cpp include/csvreader.hpp include/FixedPointNumber.hpp
	g++ -Wall -o main --std=c++14 src/main.cpp

process: src/process_data.cpp include/csvreader.hpp include/FixedPointNumber.hpp
	g++ -Wall -o process_data --std=c++14 src/process_data.cpp

.PHONY: clean
clean:
	rm -f main
	rm -f process_data

.PHONY: cleanresult
cleanresult:
	rm -f result/golden/*
	rm -f result/golden_double/*
	rm -f result/golden_norm/*
	rm -f result/golden_norm_double/*
	rm -f result/input/*
	rm -f result/input_double/*
	rm -f result/fir_coeff.sv