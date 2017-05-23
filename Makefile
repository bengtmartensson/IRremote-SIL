# Define this to be the directory where the IRremote sources reside
IRREMOTE_DIR := $(HOME)/Arduino/libraries/IRremote

# Default number of signals to generate
REPS := 10
	
CXX = g++

#DEFINES := -DIR_TIMER_USE_ESP32
INCLUDE :=  -I. -I$(IRREMOTE_DIR)
OPTIMIZE = -O2
WARN :=
#WARN := -Wall -Wextra
DEBUG := -g

IRENDING := seq

PROTOCOLS := Aiwa Denon JVC LG Lego_PF  NEC Panasonic RC5_RC6 Samsung Sharp Sony Whynter
PROTOCOL_FILES := $(foreach prot,$(PROTOCOLS),ir_$(prot).o)

OBJS := $(PROTOCOL_FILES) IRsend.o IRremote.o main.o

VPATH := $(IRREMOTE_DIR)

DECODE := ../IrpTransmogrifier/target/irptransmogrifier.sh -f -1 decode --keep-defaulted --all --name

%.o: %.cpp
	$(CXX) -c -o $@ $(INCLUDE) $(DEFINES) $(WARN) $(OPTIMIZE) $(DEBUG) $< 

irremote: $(OBJS)
	$(CXX) -o $@ $(OBJS)

clean:
	rm -f *.o *.$(IRENDING) irremote

test: irremote
	./irremote 0  $(REPS) > aiwa.$(IRENDING)
	./irremote 1  $(REPS) > denon.$(IRENDING)
	./irremote 2  $(REPS) > dish.$(IRENDING)
	./irremote 3  $(REPS) > jvc.$(IRENDING)
	./irremote 4  $(REPS) > jvc-repeat.$(IRENDING)
	./irremote 5  $(REPS) > lg.$(IRENDING)
	./irremote 6  $(REPS) > lego.$(IRENDING)
	./irremote 7  $(REPS) > lego-repeat.$(IRENDING)
	./irremote 8  $(REPS) > nec.$(IRENDING)
	./irremote 9  $(REPS) > panasonic.$(IRENDING)
	./irremote 10 $(REPS) > rc5.$(IRENDING)
	./irremote 11 $(REPS) > rc6.$(IRENDING)
	./irremote 12 $(REPS) > samsung.$(IRENDING)
	./irremote 13 $(REPS) > sharp.$(IRENDING)
	./irremote 14 $(REPS) > sony20.$(IRENDING)
	./irremote 15 $(REPS) > whynter.$(IRENDING)

decode: test
	$(DECODE) aiwa.$(IRENDING)
	$(DECODE) denon.$(IRENDING)
	$(DECODE) dish.$(IRENDING)
	$(DECODE) jvc.$(IRENDING)
	$(DECODE) jvc-repeat.$(IRENDING)
	$(DECODE) lg.$(IRENDING)
	$(DECODE) lego.$(IRENDING)
	$(DECODE) lego-repeat.$(IRENDING)
	$(DECODE) nec.$(IRENDING)
	$(DECODE) panasonic.$(IRENDING)
	$(DECODE) rc5.$(IRENDING)
	$(DECODE) rc6.$(IRENDING)
	$(DECODE) samsung.$(IRENDING)
	$(DECODE) sharp.$(IRENDING)
	$(DECODE) sony20.$(IRENDING)
	$(DECODE) whynter.$(IRENDING)
