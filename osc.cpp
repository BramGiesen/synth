
#include "osc.h"


OSC::OSC()
{
}


/* _wrap_callback() is called by the OSC library and in turn calls the
 *    real callback of the object pointed to by user_data (!)
 *
 * For every message path the same callback is added, which means we need
 *  to separate the messages inside the callback
 */
int OSC::_wrap_callback(const char *path,const char *types,
          lo_arg **argv,int argc,void *data,void *user_data)
{
  return ((((OSC *) user_data)->realcallback(path,types,argv,argc)));
}

OSC::~OSC()
{

}


static void errorhandler(int num, const char* msg, const char* where)
{
   cout << "Error " << num <<
    msg << " " <<
    where << endl;

  exit(1);
}


/*
 * start a new server in its own thread, waiting for data on the specified port
 */
void OSC::init(string serverport)
{
  server = lo_server_thread_new(serverport.c_str(),errorhandler);
}


/*
 *  link a method to a path. In reality, because we only have one callback,
 *   every method is added to the same callback and the messages are
 *   separated within the callback
 */
void OSC::set_callback(const char *path,const char *types)
{
  lo_server_thread_add_method(server,path,types,_wrap_callback,this);
}



void OSC::start()
{
  if(lo_server_thread_start(server) < 0)
  {
    cout << "Server failed to start" << endl;
    exit(1);
  }
}


/*
 * realcallback is an empty function meant to be overridden in a subclass
 */
int OSC::realcallback(const char *path,const char *types,lo_arg **argv,int argc)
{
 cout << "blah\n";
  return 0;
} // realcallback()
