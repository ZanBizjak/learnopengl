BUILDDIR = obj
SRCDIR = src
MODULES = src


build: $(BUILDDIR)
	gcc $(SRCDIR)/main.c glad/src/glad.c -o $(BUILDDIR)/main.o -Iglad/include -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

$(BUILDDIR):
	mkdir -p $@


clean:
	rm -rf $(BUILDDIR)
