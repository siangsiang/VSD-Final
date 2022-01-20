.PHONY: gen_dram_data
gen_dram_data:
	g++ --std=c++11 -o gen_dram_data src/gen_dram_data.cpp

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