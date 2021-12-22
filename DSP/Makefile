main: src/main.cpp include/csvreader.hpp include/FixedPointNumber.hpp
	g++ -Wall -o main --std=c++14 src/main.cpp

process: src/process_data.cpp include/csvreader.hpp include/FixedPointNumber.hpp
	g++ -Wall -o process_data --std=c++14 src/process_data.cpp

.PHONY: clean
clean:
	rm -f main
	rm -f process_data