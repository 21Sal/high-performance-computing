CC=nvcc
CFLAGS=

OBJDIR = obj

_OBJ = args.o data.o setup.o vtk.o boundary.o md.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

.PHONY: directories

all: directories md

obj/%.o: %.cu
	$(CC) -c -o $@ $< $(CFLAGS) 

md: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -Rf $(OBJDIR)
	rm -f md

directories: $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
