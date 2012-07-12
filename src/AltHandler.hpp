#ifndef _ALT_IMAGENEX_ALTHANDLER_HPP_
#define _ALT_IMAGENEX_ALTHANDLER_HPP_

#include <iodrivers_base/Driver.hpp>
#include <base/samples/sonar_beam.h>
#include "AltTypes.hpp"
#include "AltRaw.hpp"

namespace alt_imagenex
{
  
  class AltHandler : public iodrivers_base::Driver
  {
   public: 
      AltHandler(int max_packet_size, bool extract_last = false);

      AltData getData() const;
	
      AltStatus getStatus() const;
      
      base::samples::SonarBeam getEchoData() const;
      
      void setGain(const int& gain);
      
      void setRange(const int& range);
      
      void setEcho(bool echoOn);
      
      void setSoundVelocity(double soundVelocity);
   
  protected:
    
    void sendSwitchCmd();
    
    virtual void parseReply(const std::vector<uint8_t>* buffer);
    
    AltData mData;
    AltStatus mStatus;
    base::samples::SonarBeam mEchoData;
    raw::AltSwitchCmd mSwitchCmd;    
  };
}

#endif