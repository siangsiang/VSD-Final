SIGN_BITS = 1
INT_BITS  = 3
FRAC_BITS = 12
DEFINE_FIXED = -DSIGN_BITS=$(SIGN_BITS) -DINT_BITS=$(INT_BITS) -DFRAC_BITS=$(FRAC_BITS)

INC = -I../common -I../FixedPointNumberLibrary/include

OPT = -Wall --std=c++14 $(DEFINE_FIXED) $(INC)

.PHONY: main
main:
	rm -f main
	g++ -o main src/main.cpp $(OPT)
	./main

.PHONY: process_data
process_data:
	rm -f process_data
	g++ -o process_data src/process_data.cpp $(OPT)
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