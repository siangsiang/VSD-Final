.PHONY: help
help:
	echo "hi"

.PHONY: all
all: clean_all dsp ml ml_hw dram_data

.PHONY: clean_all
clean_all: clean_dsp clean_ml clean_ml_hw clean_dram_data

.PHONY: clean_dsp
clean_dsp:
	$(MAKE) -C DSP clean_data


.PHONY: DSP
dsp: clean_dsp
	$(MAKE) -C DSP process_data
	$(MAKE) -C DSP main

.PHONY: clean_ml
clean_ml:
	$(MAKE) -C ML clean_data

.PHONY: ml
ml: clean_ml
	cd ML && python3 dataset.py
	cd ML && python3 train.py

.PHONY: clean_ml_hw
clean_ml_hw:
	$(MAKE) -C ML-HW clean_data

.PHONY: ml_hw
ml_hw:
	$(MAKE) -C ML-HW convert_weights
	$(MAKE) -C ML-HW convert_input
	$(MAKE) -C ML-HW run_ml
	
.PHONY: clean_dram_data
clean_dram_data:
	$(MAKE) -C DRAM-Data clean_data

.PHONY: dram_data
dram_data:
	$(MAKE) -C DRAM-Data run_gen_dram_data