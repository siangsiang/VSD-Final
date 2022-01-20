.PHONY: convert_weights
convert_weights: src/convert_weights.cpp
	g++ --std=c++11 -o convert_weights src/convert_weights.cpp
	./convert_weights

.PHONY: convert_input
convert_input: src/convert_input.cpp
	g++ --std=c++11 -o convert_input src/convert_input.cpp
	./convert_input

.PHONY: ml
ml:
	g++ --std=c++11 -o ml src/ml.cpp

.PHONY: ml_dbl
ml_dbl:
	g++ --std=c++11 -o ml_dbl src/ml_dbl.cpp

.PHONY: run_ml
run_ml: ml
	./ml

.PHONY: run_ml-dbl
run_ml-dbl: ml_dbl
	./ml_dbl

.PHONY: gencode
gencode:
	cd data && mkdir -p generated_code
	cd data && python3 gencode_conv.py > generated_code/generated_fc.sv
	cd data && python3 gencode_fc.py > generated_code/generated_conv.sv

.PHONY: clean_data
clean_data:
	rm -f data/input/*
	rm -f data/weights/*
	rm -f data/generated_code/*
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