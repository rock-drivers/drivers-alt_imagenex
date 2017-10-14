#ifndef ALT_IMAGENEX_ALTTYPES_HPP
#define ALT_IMAGENEX_ALTTYPES_HPP

#include <base/Time.hpp>

namespace alt_imagenex {
  
  struct AltData{
    base::Time time;
    double altitude;
    AltData()
      : time(base::Time::now()),
	altitude(0)
    {}
  };
  
  struct AltStatus{
    base::Time time;
    bool serialStatus;
    int range;
    AltStatus()
      : time(base::Time::now()),
	serialStatus(0),
	range(0)
    {}
  };
}


#endif
