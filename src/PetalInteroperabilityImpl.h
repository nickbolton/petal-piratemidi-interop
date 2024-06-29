#include "PetalInteroperability.h"
#include "PetalMidiBridge.h"
#pragma once

class PetalInteroperabilityImpl : public PetalInteroperability {
protected:
bool _isConnected = false;
private:
  PetalMidiBridge *_bridge = nullptr;

public:
  PetalInteroperabilityImpl();
  ~PetalInteroperabilityImpl();

  bool isConnected();
  void sendSysExMessage(const byte * message, unsigned length);
  void sendProgramChange(byte channel, byte number);
  void sendControlChange(byte channel, byte number, byte value);
  void setCurrentColor(u_int32_t color);

  PetalMidiBridge *bridge() { return _bridge; };
  void processLoop();
 };

#define PETAL_CREATE_INSTANCE PetalInteroperability *PETAL_INTEROP = new PetalInteroperabilityImpl
