CC = g++ -g
CFLAGS = -I/usr/local/include -I/usr/local/include/rtmidi -Wall -std=c++1z
LDFLAGS=  -lrtmidi -llo

MIDI_in :midi_client.o osc_client.o
	$(CC) -o $@ $(CFLAGS) midi_client.o osc_client.o $(LDFLAGS)


midi_client.o: midi_client.cpp
	$(CC) -c midi_client.cpp $(CFLAGS)

osc_client.o: osc_client.cpp
	$(CC) -c osc_client.cpp $(CFLAGS)
# .cpp.o:
# 	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example
