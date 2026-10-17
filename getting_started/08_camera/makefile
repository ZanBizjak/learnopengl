BUILDDIR = obj
SRCDIR = src
TEXTUREDIR = textures
MODULES = src
INPROJLINK = -Iglad/include -Iglfw/include -Istb/include -Icglm/include
STATICLINK = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
LINKAGE = $(INPROJLINK) $(STATICLINK)

build: $(BUILDDIR)
	gcc $(SRCDIR)/*.c glad/src/glad.c -o $(BUILDDIR)/main.o $(LINKAGE)
	cp -f $(SRCDIR)/*.frag $(BUILDDIR)
	cp -f $(SRCDIR)/*.vert $(BUILDDIR)
	cp -f $(TEXTUREDIR)/* $(BUILDDIR)
#include 

$(BUILDDIR):
	mkdir -p $@

shader: $(BUILDDIR)
	cp -f $(SRCDIR)/*.frag $(BUILDDIR)
	cp -f $(SRCDIR)/*.vert $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)
