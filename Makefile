#####################################################################
#       (c) Copyright 2015, Hogeschool voor de Kunsten Utrecht
#                       Hilversum, the Netherlands
#####################################################################
#
# Description   : Makefile for osc server and client
#
# Author        : Marc_G
# E-mail        : marcg@dinkum.nl
#
####################################################################/

CC = g++ -g
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack


all: osc_client osc_server


osc_client: osc_client.o
	$(CC) -o $@ $(CFLAGS) osc_client.o -llo

osc_server: synth.o osc_server.o osc.o jack_module.o osc_server_main.o
	$(CC) -o $@ $(CFLAGS) synth.o osc_server.o osc.o jack_module.o osc_server_main.o $(LDFLAGS) -llo


.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm +111 -type f`
