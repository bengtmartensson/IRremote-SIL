# Define this to be the directory where the IRremote sources reside
IRREMOTE_DIR := $(HOME)/Arduino/libraries/IRremote

# Check that IRREMOTE_DIR is sane, producing a slightly more user friendly error message
ifeq ($(wildcard $(IRREMOTE_DIR)/*),)
    $(error IRREMOTE_DIR=$(IRREMOTE_DIR) does not denote a non-empty, readable directory)
endif

ifeq ($(wildcard $(IRREMOTE_DIR)/src),)
    IRREMOTE_SRC=$(IRREMOTE_DIR)
else
    IRREMOTE_SRC=$(IRREMOTE_DIR)/src
endif

# Default number of signals to generate
REPS := 10

CXX = g++

#DEFINES := -DIR_TIMER_USE_ESP32
INCLUDE :=  -I. -I$(IRREMOTE_SRC)
OPTIMIZE = -O2
WARN := -Wall -Wextra
DEBUG := -g

IRENDING := seq
DECODEENDING := decode

PROTOCOL_FILES := \
	ir_Aiwa.o \
	ir_Denon.o \
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
	samsung \
	sharp \
	sony20 \
	whynter


OBJS := $(PROTOCOL_FILES) IRsend.o IRremote.o main.o

VPATH := $(IRREMOTE_SRC)

DECODE := irptransmogrifier -f -1 decode --keep-defaulted --all --name

%.o: %.cpp
	$(CXX) -c -o $@ $(INCLUDE) $(DEFINES) $(WARN) $(OPTIMIZE) $(DEBUG) $<

irremote: $(OBJS)
	$(CXX) -o $@ $(OBJS)

clean:
	rm -f *.o *.$(IRENDING) *.$(DECODEENDING) irremote

test: $(foreach prot,$(PROTOCOL_NAMES),$(prot).$(IRENDING))

%.$(IRENDING): irremote
	./$< $*  $(REPS) > $@

decode: $(foreach prot,$(PROTOCOL_NAMES),$(prot).$(DECODEENDING))

%.$(DECODEENDING): %.$(IRENDING)
	$(DECODE) $< > $@

env:
	env
	@echo IRREMOTE_DIR=$(IRREMOTE_DIR)

version:
	make --version
	$(CXX) --version
	uname -a
	-git log | head -1
	-git -C $(IRREMOTE_DIR) log | head -1

.PHONY: clean env version

# Delete the default legacy suffixes, not used and makes debug output longer.
.SUFFIXES:
