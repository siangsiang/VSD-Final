.PHONY: help
help:
	echo "hi"

.PHONY: __all
all:
	$(MAKE) -C . __all 2>&1 | tee all.log

.PHONY: __all
__all: clean_all dsp ml ml_hw dram_data confusion_matrix

.PHONY: clean_all
clean_all: clean_dsp clean_ml clean_ml_hw clean_dram_data

.PHONY: clean_dsp
clean_dsp:
	$(MAKE) -C DSP clean_data


.PHONY: dsp
dsp:
	$(MAKE) -C . __dsp 2>&1 | tee dsp.log

.PHONY: __dsp
__dsp: clean_dsp
	$(MAKE) -C DSP process_data
	$(MAKE) -C DSP main

.PHONY: clean_ml
clean_ml:
	$(MAKE) -C ML clean_data

.PHONY: ml
ml:
	$(MAKE) -C . __ml 2>&1 | tee ml.log

.PHONY: __ml
__ml: clean_ml
	cd ML && python3 dataset.py
	cd ML && python3 train.py

.PHONY: clean_ml_hw
clean_ml_hw:
	$(MAKE) -C ML-HW clean_data

.PHONY: ml_hw
ml_hw:
	$(MAKE) -C . __ml_hw 2>&1 | tee ml_hw.log

.PHONY: __ml_hw
__ml_hw:
	$(MAKE) -C ML-HW convert_weights
	$(MAKE) -C ML-HW gencode
	$(MAKE) -C ML-HW convert_input
	$(MAKE) -C ML-HW run_ml
	
.PHONY: clean_dram_data
clean_dram_data:
	$(MAKE) -C DRAM-Data clean_data

.PHONY: dram_data
dram_data:
	$(MAKE) -C . __dram_data 2>&1 | tee dram_data.log

.PHONY: __dram_data
__dram_data:
	$(MAKE) -C DRAM-Data run_gen_dram_data

.PHONY: confusion_matrix
confusion_matrix:
	$(MAKE) -C . __confusion_matrix 2>&1 | tee confusion_matrix.log

.PHONY: __confusion_matrix
__confusion_matrix:
	$(MAKE) -C DRAM-Data confusion_matrix