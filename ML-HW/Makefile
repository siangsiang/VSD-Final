convert_weights: src/convert_weights.cpp
	g++ --std=c++11 -o convert_weights src/convert_weights.cpp

convert_input: src/convert_input.cpp
	g++ --std=c++11 -o convert_input src/convert_input.cpp

test: src/test.cpp
	g++ --std=c++11 -o test src/test.cpp

.PHONY: ml
ml:
	g++ --std=c++11 -o ml src/ml.cpp

.PHONY: ml-dbl
ml-dbl:
	g++ --std=c++11 -o ml-dbl src/ml-dbl.cpp

.PHONY: run_ml
run_ml: ml
	./ml

.PHONY: run_ml-dbl
run_ml-dbl: ml-dbl
	./ml-dbl

.PHONY: gen_dram_data
gen_dram_data:
	g++ --std=c++11 -o gen_dram_data src/gen_dram_data.cpp

.PHONY: run_gen_dram_data
run_gen_dram_data: gen_dram_data
	./gen_dram_data

.PHONY: clean_data
clean_data:
	rm -f data/input/*
	rm -f data/weights/*
	rm -f result/conv1d_0_golden/*
	rm -f result/conv1d_1_golden/*
	rm -f result/fc_0_golden/*
	rm -f result/fc_1_golden/*
	rm -f result/flatten_golden/*
	rm -f result/input/*
	rm -f result/logs/*
	rm -f result/maxpool1d_0_golden/*
	rm -f result/maxpool1d_1_golden/*
	rm -f result/output/*
	rm -f result/relu_0_golden/*
	rm -f result/relu_1_golden/*
	rm -f result-dbl/conv1d_0_golden/*
	rm -f result-dbl/conv1d_1_golden/*
	rm -f result-dbl/fc_0_golden/*
	rm -f result-dbl/fc_1_golden/*
	rm -f result-dbl/flatten_golden/*
	rm -f result-dbl/input/*
	rm -f result-dbl/logs/*
	rm -f result-dbl/maxpool1d_0_golden/*
	rm -f result-dbl/maxpool1d_1_golden/*
	rm -f result-dbl/output/*
	rm -f result-dbl/relu_0_golden/*
	rm -f result-dbl/relu_1_golden/*