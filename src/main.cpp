#include "cprocessing.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

#include "OscOutboundPacketStream.h"
#include "UdpSocket.h"

#define BUFSIZE 128

#define ADDRESS "127.0.0.1"
#define PORT 57120

#define OUTPUT_BUFFER_SIZE 1024

#if WIN32
#define popen _popen
#define pclose _pclose
#endif

using namespace std;
using namespace cprocessing;

FILE *fp;
char buf[BUFSIZE];

int start() {

  string cmd = "sclang";
  string arguments = string(" start.scd");
  cmd += arguments;

  if ((fp = popen(cmd.c_str(), "w")) == NULL) {
    printf("Error opening pipe!\n");
    return -1;
  }

  return 0;
}

int evaluate(string input) {

  osc::UdpTransmitSocket transmitSocket(osc::IpEndpointName(ADDRESS, PORT));

  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

  p << osc::BeginBundleImmediate << osc::BeginMessage("/oo_i")
    << strdup(input.c_str()) << osc::EndMessage << osc::EndBundle;

  transmitSocket.Send(p.Data(), p.Size());
}

int close() {

  if (pclose(fp)) {
    printf("Command not found or exited with error status\n");
    return -1;
  }
}

// void keyPressed() { write(fp[0], "().play;"); }

int fc;
bool hit;

void setup() {
  size(600, 400, "cccolider");
  start();
  fc = 0;
  // close();
}

void draw() {
  if (fc % 100 == 0) {
    background(255);
  } else {
    background(0);
  }

  stroke(255.0);

  line(fc++, 0, fc, height);
  fc = fc % width;

  if (fgets(buf, BUFSIZE, fp) != NULL) {
    printf("OUTPUT: %s", buf);
  }

  string frames = ("frameNo: ");
  frames += to_string(fc);

  text("CCColider", 30, 30);
  text("Welcome!", 30, 45);
  text(frames.c_str(), 30, 60);

  if (fc % 100 == 0) {
    evaluate("().play;");
    evaluate("'bang!'.postln;");
  }
}
