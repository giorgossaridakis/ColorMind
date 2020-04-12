CC=$(shell which cc)
src=colormind.c
obj=colormind.o
LDFLAGS=-lcurses

colormind: $(obj)

	$(CC) -o$@ $(src) $(LDFLAGS)
	rm -f $(obj)
