convert_weights: src/convert_weights.cpp
	g++ --std=c++11 -o convert_weights src/convert_weights.cpp

convert_input: src/convert_input.cpp
	g++ --std=c++11 -o convert_input src/convert_input.cpp

test: src/test.cpp
	g++ --std=c++11 -o test src/test.cpp

ml: src/ml.cpp
	g++ --std=c++11 -o ml src/ml.cpp

run_ml: ml
	./ml data/input/1_golden_double_112.dat