CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack -llo

all: fmsynth

fmsynth : osc_server.o osc.o synth.o sineWave.o oscillator.o ADSR.o filter.o delay.o userInput.o fmSynth.o jack_module.o main.o
	$(CC) -o $@ $(CFLAGS) osc_server.o osc.o synth.o sineWave.o oscillator.o ADSR.o filter.o delay.o userInput.o fmSynth.o jack_module.o main.o $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example
