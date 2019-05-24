# This Makefile runs beautifully in parallel ("make -j").

# Define this to be the directory where IRremote resides
#IRREMOTE_DIR := $(HOME)/Arduino/libraries/IRremote
IRREMOTE_DIR := ../Arduino-IRremote

# Check that IRREMOTE_DIR is sane, producing a slightly more user friendly error message
ifeq ($(wildcard $(IRREMOTE_DIR)/*),)
    $(error IRREMOTE_DIR=$(IRREMOTE_DIR) does not denote a non-empty, readable directory)
endif

# Find the IRremote sources (allowing for the source reorganization).
ifeq ($(wildcard $(IRREMOTE_DIR)/src),)
    IRREMOTE_SRC := $(IRREMOTE_DIR)
else
    IRREMOTE_SRC := $(IRREMOTE_DIR)/src
endif

# ... and tell Make to use them
VPATH := $(IRREMOTE_SRC)

# Default number of signals to generate
REPS := 100

CXX := g++
ZIP := zip

#DEFINES := -DIR_TIMER_USE_ESP32
INCLUDE :=  -I. -I$(IRREMOTE_SRC)
OPTIMIZE = -O2
WARN := -Wall -Wextra
DEBUG := -g

IRENDING := seq
DECODEENDING := dec
ANALYZEENDING := ana

OUTPUTDIR := testoutput
RESULTFILE := result.zip

PROTOCOL_FILES := \
	ir_Aiwa.o \
	ir_Denon.o \
	ir_Dish.o \
	ir_JVC.o \
	ir_LG.o \
	ir_Lego_PF.o \
	ir_NEC.o \
	ir_Panasonic.o \
	ir_RC5_RC6.o \
	ir_Samsung.o \
	ir_Sharp.o \
	ir_Sony.o \
	ir_Whynter.o

PROTOCOL_NAMES := \
	aiwa \
	denon \
	dish \
	jvc \
	jvc-repeat \
	lg \
	lego \
	lego-repeat \
	nec \
	panasonic \
	rc5 \
	rc6 \
	samsung20 \
	sharp \
	sony20 \
	whynter


OBJS := $(PROTOCOL_FILES) IRsend.o IRremote.o main.o

all: $(RESULTFILE)

%.o: %.cpp
	$(CXX) -c -o $@ $(INCLUDE) $(DEFINES) $(WARN) $(OPTIMIZE) $(DEBUG) $<

$(OUTPUTDIR):
	mkdir $@

irremote: $(OBJS)
	$(CXX) -o $@ $(OBJS)

$(RESULTFILE): analyze decode
	$(MAKE) version > $(OUTPUTDIR)/VERSION
	$(ZIP) $@ $(OUTPUTDIR)/*

test: $(foreach prot,$(PROTOCOL_NAMES),$(OUTPUTDIR)/$(prot).$(IRENDING))

%.$(IRENDING): irremote | $(OUTPUTDIR)
	./$< $(*F)  $(REPS) > $@

decode: $(foreach prot,$(PROTOCOL_NAMES),$(OUTPUTDIR)/$(prot).$(DECODEENDING))

%.$(DECODEENDING): %.$(IRENDING) | $(OUTPUTDIR)
	irptransmogrifier -f -1 -o $@ decode --radix 16 --keep-defaulted --all --name $<

analyze: $(foreach prot,$(PROTOCOL_NAMES),$(OUTPUTDIR)/$(prot).$(ANALYZEENDING))

%.$(ANALYZEENDING): %.$(IRENDING) | $(OUTPUTDIR)
	irptransmogrifier -o $@ analyze --radix 16 --bit-usage --name $<

env:
	env
	@echo IRREMOTE_DIR=$(IRREMOTE_DIR)

version:
	make --version
	$(CXX) --version
	uname -a
	-git log | head -1
	-git -C $(IRREMOTE_DIR) log | head -1

clean:
	rm -rf *.o *.$(IRENDING) *.$(DECODEENDING) *.$(ANALYZEENDING) irremote $(OUTPUTDIR) $(RESULTFILE)

.PHONY: clean env version decode analyze all

# Delete the default legacy suffixes, not used and makes debug output longer.
.SUFFIXES:

# Do not automatically delete $(OUTPUTDIR)/$(prot).$(IRENDING) files
.SECONDARY: $(foreach prot,$(PROTOCOL_NAMES),$(OUTPUTDIR)/$(prot).$(IRENDING))
