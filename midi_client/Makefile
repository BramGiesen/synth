CC = g++ -g
CFLAGS = -I/usr/local/include -I/usr/local/include/rtmidi -Wall -std=c++1z
LDFLAGS=  -lrtmidi -llo

all: midi_client

example : midi_client.o
	$(CC) -o $@ $(CFLAGS)  midi_client.o $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example
