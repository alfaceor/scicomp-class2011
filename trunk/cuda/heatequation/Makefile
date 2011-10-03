TARG = heatequation
CC=/usr/local/cuda/bin/nvcc
INCDIR=./include
INCLUDES=-I$(INCDIR)
COMPILE= $(CC) $(INCLUDES)

build/$(TARG) : lib/$(TARG).o lib/kernel_gpu.o src/$(TARG).cu
	$(COMPILE) lib/$(TARG).o lib/kernel_gpu.o -o build/heatequation

lib/%.o: src/%.cu
	$(COMPILE) -c $< -o $@

clean:
	rm build/heatequation lib/heatequation.o lib/kernel_gpu.o
