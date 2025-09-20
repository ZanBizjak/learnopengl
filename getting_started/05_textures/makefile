BUILDDIR = obj
SRCDIR = src
TEXTUREDIR = textures
MODULES = src
LINKAGE = -Iglad/include -Iglfw/include -Istb/include -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

build: $(BUILDDIR)
	gcc $(SRCDIR)/*.c glad/src/glad.c -o $(BUILDDIR)/main.o $(LINKAGE)
	cp -f $(SRCDIR)/*.frag $(BUILDDIR)
	cp -f $(SRCDIR)/*.vert $(BUILDDIR)
	cp -f $(TEXTUREDIR)/* $(BUILDDIR)
#include 

$(BUILDDIR):
	mkdir -p $@


clean:
	rm -rf $(BUILDDIR)
