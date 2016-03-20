/*
    Simple example of sending an OSC message using oscpack.
*/

#include "ip/UdpSocket.h"
#include "osc/OscOutboundPacketStream.h"

#define ADDRESS "127.0.0.1"
#define PORT 57120

#define OUTPUT_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  (void)argc; // suppress unused parameter warnings
  (void)argv; // suppress unused parameter warnings

  osc::UdpTransmitSocket transmitSocket(osc::IpEndpointName(ADDRESS, PORT));

  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

  p << osc::BeginBundleImmediate << osc::BeginMessage("/oo_i")
    << "Tdef(\\aa).stop;" << osc::EndMessage << osc::EndBundle;

  transmitSocket.Send(p.Data(), p.Size());
}
