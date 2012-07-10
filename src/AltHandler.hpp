#ifndef _ALT_IMAGENEX_ALTHANDLER_HPP_
#define _ALT_IMAGENEX_ALTHANDLER_HPP_

#include <iodrivers_base/Driver.hpp>
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
      
      void setGain(const int& gain);
      
      void setRange(const int& range);
   
  protected:
    
    void sendSwitchCmd();
    
    virtual void parseReply(const std::vector<uint8_t>* buffer);
    
    AltData mData;
    AltStatus mStatus;
    raw::AltSwitchCmd mSwitchCmd;
    
  };

}

#endif