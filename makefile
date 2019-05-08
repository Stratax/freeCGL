LIBDIR := lib
BINDIR := bin
IMGDIR := img
OBJDIR := obj

CFLAGS = -g -Wall
LDFLAGS = -lgraph -lm

pract := $(addprefix $(BINDIR)/,1000lines model rotation projection solid test light curve)
libs := $(addprefix $(LIBDIR)/,libgraph.a)

all: $(pract)

$(BINDIR)/%: src/%.c $(libs) | $(BINDIR)
	gcc $< -o $@ $(CFLAGS) -Iinclude -Llib $(LDFLAGS)


$(BINDIR)/raw2vlf: src/raw2vlf.c lib/libformat.a | $(BINDIR)
	gcc $< -o $@ $(CFLAGS) -Iinclude -Llib -lformat -lm

$(LIBDIR)/%.a: $(OBJDIR)/%.o | $(LIBDIR)
	ar -rv $@ $<
	ranlib $@


$(OBJDIR)/libgraph.o: src/myGraphics.c include/myGraphics.h | $(OBJDIR)
	gcc -c $< -Iinclude $(CFLAGS) -o $@


$(OBJDIR)/libformat.o: src/formats3d.c include/formats3d.h | $(OBJDIR)
	gcc -c $< -Iinclude $(CFLAGS) -o $@


$(OBJDIR):
	mkdir obj

$(LIBDIR):
	mkdir lib

$(BINDIR):
	mkdir bin
	mkdir img

clean:
	rm -r bin lib obj img
