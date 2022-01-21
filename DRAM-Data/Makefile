SIGN_BITS = 1
INT_BITS  = 3
FRAC_BITS = 12
DEFINE_FIXED = -DSIGN_BITS=$(SIGN_BITS) -DINT_BITS=$(INT_BITS) -DFRAC_BITS=$(FRAC_BITS)

INC = -I../common -I../FixedPointNumberLibrary/include

OPT = -Wall --std=c++14 $(DEFINE_FIXED) $(INC)


.PHONY: gen_dram_data
gen_dram_data:
	rm -f gen_dram_data
	g++ -o gen_dram_data src/gen_dram_data.cpp $(OPT)

.PHONY: run_gen_dram_data
run_gen_dram_data: gen_dram_data
	./gen_dram_data

.PHONY: confusion_matrix
confusion_matrix:
	cd dram_data && python3 confusion_matrix.py

.PHONY: clean_data
clean_data:
	rm -f dram_data/input/*
	rm -f dram_data/ground_truth/*
	rm -f dram_data/golden/*