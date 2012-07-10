#include <iostream>
#include "Driver.hpp"

using namespace alt_imagenex;
using namespace std;


Driver::Driver(int max_packet_size, bool extract_last)
  : AltHandler(max_packet_size,extract_last)
{
}	
	
void Driver::open(std::string const& uri)
{
   openURI(uri);
}

void Driver::collectData()
{
  sendSwitchCmd();
  read(2000);
}

void Driver::read(int timeout)
{
   std::vector<uint8_t>    buffer(1024);

    try {
        int size = readPacket(&buffer[0], buffer.size());
	if(size){
	  parseReply(&buffer);
	}
    } catch ( std::runtime_error &e) {
        throw;
    }
}

int Driver::extractPacket (uint8_t const *buffer, size_t buffer_size) const
{
  for (size_t i = 0; i < buffer_size; i++) {
    if (buffer[i] == ALT_REPLY_START)
    {
      if(i){
	return -i;
      }
      if(buffer_size<2){
	return 0;
      }
      size_t len = ALT_REPLY_LEN;
      if(buffer[1] == ALT_REPLY_G){
	len = ALT_REPLY_LEN_ECHO;
      }
      if(buffer_size >= len && buffer[len-1] == ALT_REPLY_TERM){
	return len;
      }
      return 0;
    }
  }
  return -buffer_size;  
}

	