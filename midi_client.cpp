#include <iostream>
#include <string>
#include <unistd.h>
#include <lo/lo.h>
#include <cstdlib>
#include <signal.h>
#include "RtMidi.h"

using namespace std;

// Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

bool done;
static void finish( int /*ignore*/ ){ done = true; }

void usage( void ) {
  // Error function in case of incorrect command-line
  // argument specifications.
  std::cout << "\nusage: qmidiin <port>\n";
  std::cout << "    where port = the device to use (default = 0).\n\n";
  exit( 0 );
}

int main( int argc, char *argv[] )
{
/******************************************************************************/
    lo_address target;
    string symbol;
    long fake_timestamp=0;

    target = lo_address_new("localhost","7777");
    // lo_send(target,"/midiNote","siii","pitch",fake_timestamp,70,42);

/******************************************************************************/
    RtMidiIn *midiin = 0;
    std::vector<unsigned char> message;
    int nBytes, i;
    double stamp;

    // Minimal command-line check.
    if ( argc > 2 ) usage();

    // RtMidiIn constructor
    try {
      midiin = new RtMidiIn();
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
      exit( EXIT_FAILURE );
    }

    // Check available ports vs. specified.
    unsigned int port = 0;
    unsigned int nPorts = midiin->getPortCount();
    if ( argc == 2 ) port = (unsigned int) atoi( argv[1] );
    if ( port >= nPorts ) {
      delete midiin;
      std::cout << "Invalid port specifier!\n";
      usage();
    }

    try {
      midiin->openPort( port );
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
      goto cleanup;
    }

    // Don't ignore sysex, timing, or active sensing messages.
    midiin->ignoreTypes( false, false, false );

    // Install an interrupt handler function.
    done = false;
    (void) signal(SIGINT, finish);
    // int midiNote = 0;
    // Periodically check input queue.
    std::cout << "Reading MIDI from port " << midiin->getPortName() << " ... quit with Ctrl-C.\n";
    while ( !done ) {
      stamp = midiin->getMessage( &message );
      nBytes = message.size();
      //
      // if (nBytes> 0 && message[2] > 0){
      // int a = message[1];
      // lo_send(target,"/midiNote","siii","pitch",fake_timestamp,a,42);
      // std::cout << "midiNote = " << a << std::endl;
      // }

      if (nBytes> 0){
      int a = message[1];
      int b = message[2];
      lo_send(target,"/noteOn","iii",1,a,b);
      std::cout << "midiNote = " << a << std::endl;
      }

      for ( i=0; i<nBytes; i++ )
        std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
        // midiNote = (int)message[1];
      if ( nBytes > 0 )
        std::cout << "stamp = " << stamp << std::endl;

      fake_timestamp++;
      // Sleep for 10 milliseconds.
      SLEEP( 10 );
    }
    // Clean up
   cleanup:
   delete midiin;

 return 0;
}
