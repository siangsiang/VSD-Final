SIGN_BITS = 1
INT_BITS  = 3
FRAC_BITS = 12
DEFINE_FIXED = -DSIGN_BITS=$(SIGN_BITS) -DINT_BITS=$(INT_BITS) -DFRAC_BITS=$(FRAC_BITS)

INC = -I../common -I../FixedPointNumberLibrary/include

OPT = -Wall --std=c++14 $(DEFINE_FIXED) $(INC)

.PHONY: convert_weights
convert_weights: src/convert_weights.cpp
	rm -f convert_weights
	g++ -o convert_weights src/convert_weights.cpp $(OPT)
	./convert_weights

.PHONY: convert_input
convert_input: src/convert_input.cpp
	rm -f convert_input
	g++ -o convert_input src/convert_input.cpp $(OPT)
	./convert_input
	cp ../ML/dataset/*_list.txt data/input/dataset_list
	sed -i 's/_double_/_/g' data/input/dataset_list/*.txt

.PHONY: ml
ml: src/ml.cpp
	rm -f ml
	g++ -o ml src/ml.cpp $(OPT)

.PHONY: run_ml
run_ml: ml
	./ml

.PHONY: gencode
gencode:
	cd data && mkdir -p generated_code
	cd data && python3 gencode_conv.py > generated_code/generated_conv.sv
	cd data && python3 gencode_fc.py > generated_code/generated_fc.sv

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
	