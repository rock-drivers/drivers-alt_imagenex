#include <iostream>
#include "AltHandler.hpp"
#include "AltRaw.hpp"

using namespace alt_imagenex;
using namespace std;

AltHandler::AltHandler(int max_packet_size, bool extract_last)
  : iodrivers_base::Driver(max_packet_size,extract_last)
{
  mEchoData.bearing = base::Angle::fromDeg(0);
  mEchoData.sampling_interval = ALT_SAMPLE_INT;
  mEchoData.speed_of_sound = ALT_DEFAULT_SV;
  mEchoData.beamwidth_horizontal = 0;
  mEchoData.beamwidth_vertical = 0;
}

AltData AltHandler::getData() const
{
  return mData;
}
	
AltStatus AltHandler::getStatus() const
{
  return mStatus;
}

base::samples::SonarBeam AltHandler::getEchoData() const
{
  return mEchoData;
}

void AltHandler::setGain(const int& gain)
{
  if(gain < 0){
    mSwitchCmd.startGain = 0;
    return;
  }
  if(gain > 40){
    mSwitchCmd.startGain = 40;
    return;
  }
  mSwitchCmd.startGain = gain;  
}
    
void AltHandler::setRange(const int& range)
{
  if(range < 1){
    mSwitchCmd.range = 1;
  }
  else if(range <= 5){
    mSwitchCmd.range = range;
  }
  else if(range < 60){
    mSwitchCmd.range = (range/10 + 1)*10;
  }
  else if(range == 60){
    mSwitchCmd.range = 60;
  }
  else if(range <= 80){
    mSwitchCmd.range = 80;
  }
  else if(range <= 100){
    mSwitchCmd.range = 100;
  }
  else if(range <= 150){
    mSwitchCmd.range = 150;
  }
  else {
    mSwitchCmd.range = 200;
  }
  switch(mSwitchCmd.range){
    case 1:
    case 2:
    case 3:
    case 4: mSwitchCmd.pulseLength = 1;break;
    case 5:
    case 10: mSwitchCmd.pulseLength = 3;break;
    case 20: mSwitchCmd.pulseLength = 5;break;
    case 30: mSwitchCmd.pulseLength = 8;break;
    case 40: mSwitchCmd.pulseLength = 11;break;
    case 50: mSwitchCmd.pulseLength = 13;break;
    case 60: mSwitchCmd.pulseLength = 16;break;
    case 80: mSwitchCmd.pulseLength = 21;break;
    case 100: mSwitchCmd.pulseLength = 27;break;
    case 150: mSwitchCmd.pulseLength = 40;break;
    case 200: mSwitchCmd.pulseLength = 53;break;
    default: mSwitchCmd.pulseLength = 1;break;
  }
  return;
}

void AltHandler::setEcho(bool echoOn)
{
    mSwitchCmd.profile = echoOn ? 0 : 1;
}

void AltHandler::setSoundVelocity(double soundVelocity)
{
  mEchoData.speed_of_sound = soundVelocity;
  mEchoData.sampling_interval = 0.002/soundVelocity;
}

void AltHandler::sendSwitchCmd()
{
  std::vector<uint8_t> msg;
  mSwitchCmd >> msg;
  writePacket(msg.data(),msg.size());
}

void AltHandler::parseReply(const std::vector<uint8_t>* buffer)
{
  mStatus.time = base::Time::now();
  mStatus.serialStatus = (*buffer)[4] & 0x40;
  mStatus.range = (*buffer)[7];
  mData.time = base::Time::now();
  uint16_t high = ((*buffer)[9] & 0x7E)>>1;
  uint16_t low = ((((*buffer)[9] & 0x01)<<7) | ((*buffer)[8] & 0x7F));
  int div = (mStatus.range < 5) ? 500 : 100;
  mData.altitude = float((high<<8) | low) / div;  
  //char s[256];
  //sprintf(s,"gain %i, range %i , pulse %i - byte 8 %x, byte 9 %x sample units %i",mSwitchCmd.startGain, mStatus.range, mSwitchCmd.pulseLength,(*buffer)[8],(*buffer)[9],(high<<8) | low);
  //cout <<s <<endl;
  mEchoData.time = base::Time::now();
  if((*buffer)[1]== ALT_REPLY_G){
    mEchoData.beam.clear();
    for(int i = 12;i < ALT_REPLY_LEN_ECHO-1;i++){
      mEchoData.beam.push_back((*buffer)[i]);
    }
  }
}
