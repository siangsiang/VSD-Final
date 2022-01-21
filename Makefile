SIGN_BITS = 1
INT_BITS  = 3
FRAC_BITS = 12
FIXED_ARGS = SIGN_BITS=$(SIGN_BITS) INT_BITS=$(INT_BITS) FRAC_BITS=$(FRAC_BITS)

.PHONY: help
help:
	echo "hi"

.PHONY: __all
all:
	$(MAKE) $(FIXED_ARGS) -C . __all 2>&1 | tee all.log

.PHONY: __all
__all: clean_all dsp ml ml_hw dram_data confusion_matrix

.PHONY: clean_all
clean_all: clean_dsp clean_ml clean_ml_hw clean_dram_data

.PHONY: clean_dsp
clean_dsp:
	$(MAKE) $(FIXED_ARGS) -C DSP clean_data


.PHONY: dsp
dsp:
	$(MAKE) $(FIXED_ARGS) -C . __dsp 2>&1 | tee dsp.log

.PHONY: __dsp
__dsp: clean_dsp
	$(MAKE) $(FIXED_ARGS) -C DSP process_data
	$(MAKE) $(FIXED_ARGS) -C DSP main

.PHONY: clean_ml
clean_ml:
	$(MAKE) $(FIXED_ARGS) -C ML clean_data

.PHONY: ml
ml:
	$(MAKE) $(FIXED_ARGS) -C . __ml 2>&1 | tee ml.log

.PHONY: __ml
__ml: clean_ml
	$(MAKE) $(FIXED_ARGS) -C ML ml

.PHONY: clean_ml_hw
clean_ml_hw:
	$(MAKE) $(FIXED_ARGS) -C ML-HW clean_data

.PHONY: ml_hw
ml_hw:
	$(MAKE) $(FIXED_ARGS) -C . __ml_hw 2>&1 | tee ml_hw.log

.PHONY: __ml_hw
__ml_hw:
	$(MAKE) $(FIXED_ARGS) -C ML-HW convert_weights
	$(MAKE) $(FIXED_ARGS) -C ML-HW gencode
	$(MAKE) $(FIXED_ARGS) -C ML-HW convert_input
	$(MAKE) $(FIXED_ARGS) -C ML-HW run_ml
	
.PHONY: clean_dram_data
clean_dram_data:
	$(MAKE) $(FIXED_ARGS) -C DRAM-Data clean_data

.PHONY: dram_data
dram_data:
	$(MAKE) $(FIXED_ARGS) -C . __dram_data 2>&1 | tee dram_data.log

.PHONY: __dram_data
__dram_data:
	$(MAKE) $(FIXED_ARGS) -C DRAM-Data run_gen_dram_data

.PHONY: confusion_matrix
confusion_matrix:
	$(MAKE) $(FIXED_ARGS) -C . __confusion_matrix 2>&1 | tee confusion_matrix.log

.PHONY: __confusion_matrix
__confusion_matrix:
	$(MAKE) $(FIXED_ARGS) -C DRAM-Data confusion_matrix