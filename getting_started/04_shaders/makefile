BUILDDIR = obj
SRCDIR = src
MODULES = src
LINKAGE = -Iglad/include -Iglfw/include -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

build: $(BUILDDIR)
	gcc $(SRCDIR)/*.c glad/src/glad.c -o $(BUILDDIR)/main.o $(LINKAGE)
	cp $(SRCDIR)/*.frag $(BUILDDIR)
	cp $(SRCDIR)/*.vert $(BUILDDIR)

$(BUILDDIR):
	mkdir -p $@


clean:
	rm -rf $(BUILDDIR)
