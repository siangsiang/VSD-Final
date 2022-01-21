.PHONY: help
help:
	echo "hi"

.PHONY: dataset
dataset:
	python3 dataset.py

.PHONY: ml
ml: dataset
	python3 train.py

.PHONY: clean_data
clean_data:
	rm -f dataset.tar.gz
	rm -f weights/*
	rm -f dataset/testset/*
	rm -f dataset/trainset/*
	rm -f dataset/valset/*
	rm -f save_dir/e* save_dir/cost.npy