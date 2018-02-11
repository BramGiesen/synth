#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include <lo/lo.h>

using namespace std;


/*
 * class OSC creates a server listening to a certain port. For every
 *  port another server (thus object) must be created
 */
class OSC
{
public:
  OSC();
  ~OSC();
  void init(string serverport);
  void set_callback(const char *path,const char *types);
  void start();

  // realcallback is meant to be overridden in a subclass
  virtual int realcallback(const char *path,const char *types,lo_arg **argv,int argc);
private:
  static int _wrap_callback(const char *path,const char *types,
          lo_arg **argv,int argc,void *data,void *user_data);

  lo_server_thread server;
};
