#include <iostream>
#include <string>
#include <unistd.h>
#include <lo/lo.h>

using namespace std;

int main()
{
lo_address target;
string symbol;
long fake_timestamp=0;

  target = lo_address_new("localhost","7777");
  lo_send(target,"/midiNote","siii","pitch",fake_timestamp,70,42);
  // lo_send(target,"/tactile","ii",fake_timestamp,42);


  int counter = 9;
  int midiNote = 60;
  while (true) {

  std::cout << "Counter: " << counter << std::endl;;
  lo_send(target,"/midiNote","siii","pitch",fake_timestamp,midiNote,42);
  usleep(1000000);
  midiNote++;
  counter--;

  if (counter == 0) {
    break;
  }
}


  while(1)
  {
    cin >> symbol;
    if(symbol == "quit" || symbol == "q") break;

    lo_send(target,"/sound","siii","pitch",fake_timestamp,1,42);
    lo_send(target,"/tactile","ii",fake_timestamp,42);

    fake_timestamp++;
  }

}
