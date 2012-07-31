#ifndef ALT_IMAGENEX_ALTRAW_HPP
#define ALT_IMAGENEX_ALTRAW_HPP

namespace alt_imagenex {
  namespace raw {
    
#define ALT_CMD_LEN		0x1B
#define ALT_HEADER1		0xFE
#define ALT_HEADER2		0x44
#define ALT_TERM		0xFD
#define ALT_HEAD_ID		0x10
#define ALT_LOGF 		0x01
#define ALT_ABSORPTION 		0x0A
#define ALT_DATA_POINTS		0x32
#define ALT_DATA_BITS		0x08
#define ALT_FREQ		0x1F
#define ALT_REPLY_START		0x49
#define ALT_REPLY_G		0x47
#define ALT_REPLY_P		0x50
#define ALT_REPLY_TERM		0xFC
#define ALT_REPLY_LEN		0x0D
#define ALT_REPLY_LEN_ECHO	0x201

#define ALT_SAMPLE_INT		0.000013333
#define ALT_DEFAULT_SV		1500



    struct AltSwitchCmd{
      uint8_t header1;
      uint8_t header2;
      uint8_t headId;
      uint8_t range;
      uint8_t reserved0;
      uint8_t hold;
      uint8_t reserved1;
      uint8_t reserved2;
      uint8_t startGain;
      uint8_t logf;
      uint8_t absorption;
      uint8_t reserved3;
      uint8_t reserved4;
      uint8_t reserved5;
      uint8_t pulseLength;
      uint8_t profMinRange;
      uint8_t extTrigger;
      uint8_t reserved6;
      uint8_t reserved7;
      uint8_t dataPoints;
      uint8_t dataBits;
      uint8_t reserved8;
      uint8_t profile;
      uint8_t reserved9;
      uint8_t switchDelay;
      uint8_t frequency;
      uint8_t term;
      AltSwitchCmd()
	: header1(ALT_HEADER1),
	  header2(ALT_HEADER2),
	  headId(ALT_HEAD_ID),
	  range(1),
	  reserved0(0),
	  hold(0),
	  reserved1(0),
	  reserved2(0),
	  startGain(6),
	  logf(ALT_LOGF),
	  absorption(ALT_ABSORPTION),
	  reserved3(0),
	  reserved4(0),
	  reserved5(0),
	  pulseLength(1),
	  profMinRange(0),
	  extTrigger(0),
	  reserved6(0),
	  reserved7(0),
	  dataPoints(ALT_DATA_POINTS),
	  dataBits(ALT_DATA_BITS),
	  reserved8(0),
	  profile(1),
	  reserved9(0),
	  switchDelay(0),
	  frequency(ALT_FREQ),
	  term(ALT_TERM)
	  {}
	  
      AltSwitchCmd & operator>>(std::vector<uint8_t>& msg)
      {
	msg.resize(ALT_CMD_LEN);
	msg[0] = header1;
	msg[1] = header2;
	msg[2] = headId;
	msg[3] = range;
	msg[4] = reserved0;
	msg[5] = hold;
	msg[6] = reserved1;
	msg[7] = reserved2;
	msg[8] = startGain;
	msg[9] = logf;
	msg[10] = absorption;
	msg[11] = reserved3;
	msg[12] = reserved4;
	msg[13] = reserved5;
	msg[14] = pulseLength;
	msg[15] = profMinRange;
	msg[16] = extTrigger;
	msg[17] = reserved6;
	msg[18] = reserved7;
	msg[19] = dataPoints;
	msg[20] = dataBits;
	msg[21] = reserved8;
	msg[22] = profile;
	msg[23] = reserved9;
	msg[24] = switchDelay;
	msg[25] = frequency;
	msg[26] = term;
	return *this;
      }
    };

    
  }
}


#endif
