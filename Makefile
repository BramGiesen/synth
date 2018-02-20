
CC = g++ -g
CFLAGS = -I/usr/local/include -I/usr/local/include/rtmidi -Wall -std=c++1z
LDFLAGS= -ljack -lrtmidi


all: osc_client osc_server


osc_client: midi_client.o
	$(CC) -o $@ $(CFLAGS) midi_client.o $(LDFLAGS) -llo


osc_server: synth.o ADSR.o osc_server.o osc.o jack_module.o osc_server_main.o
	$(CC) -o $@ $(CFLAGS) synth.o ADSR.o osc_server.o osc.o jack_module.o osc_server_main.o $(LDFLAGS) -llo


.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm +111 -type f`
