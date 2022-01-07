convert_weights: src/convert_weights.cpp
	g++ --std=c++11 -o convert_weights src/convert_weights.cpp

convert_input: src/convert_input.cpp
	g++ --std=c++11 -o convert_input src/convert_input.cpp

test: src/test.cpp
	g++ --std=c++11 -o test src/test.cpp

ml: src/ml.cpp
	g++ --std=c++11 -o ml src/ml.cpp

run_ml: ml
	./ml

.PHONY:
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