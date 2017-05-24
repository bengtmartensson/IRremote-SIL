# IRremote-SIL
This project offers a Software-In-the-Loop (SIL) test environment for [IRremote](https://github.com/z3t0/Arduino-IRremote).
As a SIL environment, in allows testing and debugging on the host computer.
(Presently only rendering (`IRsend::send*()`), however decoding is [planned](https://github.com/bengtmartensson/IRremote-SIL/issues/1).)
No changes to the to-be-tested software are necessary.

SIL offers the following advantages: There is no need to flash the to-be-tested software onto the target system,
saving lifetime of its flash memory. It makes debugging on the host possible, using standard debuggers like gdb.
The rendered signals can be easily analyzed on the host, using tools like e.g. IrScrutinizer and DecodeIR.
Turn-around times are much faster.

## Target audience
This is a tool aimed at programmers, that want to test protocol implementations (`IRsend::send*` and, later `IRrecv::decode*`). 
The reader is (therefore) assumed to master the basics of C++ programming and [`make`](https://www.gnu.org/software/make/manual/).

## Requirements
The present version supports the main branch of IRremote, 18f12d3affb3491abbfe708d4859df12a6f84d5f.
Minor changes might be necessary for other versions (in particular [this issue](https://github.com/z3t0/Arduino-IRremote/issues/463)).

It runs in an environment containing (host-) `make` and `gcc` (`g++`). This includes Unix-like systems
like Linux, Mac-OS with `xcode`, and Windows with [Cygwin](http://www.cygwin.com/). Porting it to, say,
VisualStudio is probably possible, if someone cares...

The use of an IDE like [Eclipse](https://eclipse.org/) or [Netbeans](https://netbeans.org/)
is not required, but recommended, in particular for debugging.

## Usage
First make sure that `gcc` (`g++`) and `make` are installed. 
Make sure you have the IRremote you want to test unpacked locally on the host.
(This directory is only read from, and not modified.)
Unpack/clone the project to another directory. Edit the Makefile so that
`IRREMOTE_DIR` points to the directory containing IRremote files. Issuing the command `make test`
should now build a program and invoke it to generate a number of test files, that can be analyzed
by your favorite IR analyzer.
By defining DECODE suitably, the generated files can be decoded under the control of the Makefile.

Note that the Makefile is parallelization safe, i.e. by using the `-j` flag to `make`, multiple processes
are run in parallel, to the extent theoretically possible.

## Adding new protocols
Extend `main.cpp` as desired. Add the cpp file to the Makefile's `PROTOCOL_FILES` variable,
and the protocol names (in the sense of main.cpp) to PROTOCOL_NAMES.

## Adding new tests
Modify `main.cpp`, and/or the `Makefile`. Or another file...

## Debugging
The generated program `irremote` can be debugged as any other C++ program on the host.
