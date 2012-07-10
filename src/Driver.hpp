#ifndef _ALT_IMAGENEX_DRIVER_HPP_
#define _ALT_IMAGENEX_DRIVER_HPP_

#include "AltHandler.hpp"
#include "AltRaw.hpp"
#include "AltTypes.hpp"

namespace alt_imagenex
{
  
  class Driver : public AltHandler
  {
   public: 
      Driver(int max_packet_size = 64, bool extract_last = false);
	
	/** Tries to access the device at the provided URI
         *
         */
      void open(std::string const& uri);
      
      void collectData();
      
   protected:  
     
	/** reading reply  */
        virtual void read(int timeout);

        /** Extract a valid response from incoming Data
         *
         */
        virtual int extractPacket (uint8_t const *buffer, size_t buffer_size) const;
	
	  
  };

} 

#endif 
