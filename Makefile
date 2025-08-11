# It builds all programs in the current directory.
SUFFIX := cpp
BASENAME := basename
XARGS := xargs
FILES := $(wildcard *.$(SUFFIX))
BASENAME_MACRO := $(BASENAME) -a -s .cpp -z $(FILES)
CXXFLAGS := -Wall
RM := rm

all: .cpp

.cpp: $(FILES)
	$(BASENAME_MACRO) | $(XARGS) -0 -I {} $(CXX) $(CXXFLAGS) -o {} {}.$(SUFFIX)

clean:
	$(BASENAME_MACRO) | $(XARGS) -0 $(RM)
