#ifndef _H_MIDI_CLIENT_
#define _H_MIDI_CLIENT_

#include <iostream>
#include <string>
#include <unistd.h>
#include <lo/lo.h>
#include <cstdlib>
#include <signal.h>
#include "RtMidi.h"
#include <thread>
#include <sstream>
#include <vector>


class MidiClient
{
public:
  MidiClient();
  ~MidiClient();
  void thread_function();
  void usage( void );
  static void finish( int /*ignore*/ );
private:
  lo_address target;
  string symbol;
  long fake_timestamp=0;
};

#endif // _H_MIDI_CLIENT_
