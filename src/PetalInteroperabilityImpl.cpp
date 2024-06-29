#include "PetalInteroperabilityImpl.h"
#include "PetalUtils.h"
#include "pirate-midi-main-extern.h"

const byte BANK_STATUS = 0x10;
const byte PC_STATUS = 0xc0;
const byte CC_STATUS = 0xb0;

PetalInteroperabilityImpl *current = nullptr;

void petal_controlChangeHandler(uint8_t channel, uint8_t number, uint8_t value) {
  if (!current || !current->bridge() || !current->isConnected()) { 
    PETAL_LOGI("Received (but not connected) CC %d on Arduino channel %d with value 0x%x", number, channel, value);
    return;
  }
  PETAL_LOGI("Received (and processing) CC %d on Arduino channel %d with value 0x%x", number, channel, value);
  current->bridge()->receiveControlChange(channel, number, value);
}

void petal_sysExHandler(uint8_t* array, unsigned size) {
  if (!current || !current->bridge() || !current->isConnected()) { 
    PETAL_LOGI("Received (but not connected) SysEx");
    return;
  }
  current->bridge()->receiveSysExMessage(array, size);
}

PetalInteroperabilityImpl::PetalInteroperabilityImpl() {
  current = this;
  _bridge = new PetalMidiBridge(this);
  _bridge->setup();
  midi_AssignPetalControlChangeCallback(petal_controlChangeHandler);
  midi_AssignPetalSysemExclusiveCallback(petal_sysExHandler);
}

PetalInteroperabilityImpl::~PetalInteroperabilityImpl() { 
  _bridge = nullptr; 
  current = nullptr;
}

void PetalInteroperabilityImpl::processLoop() {
  if (!_bridge) { return; }
  _bridge->processLoop();
}

bool PetalInteroperabilityImpl::isConnected() {
  // TODO: determine what is connected means
  return true;
}

void PetalInteroperabilityImpl::sendSysExMessage(const byte * message, unsigned length) {
  midi_SendPetalSysEx(message, length);
}

void PetalInteroperabilityImpl::sendProgramChange(byte channel, byte number) {
  midi_SendPetalProgramChange(channel, number);
}

void PetalInteroperabilityImpl::sendControlChange(byte channel, byte number, byte value) {
  midi_SendPetalControlChange(channel, number, value);
}

void PetalInteroperabilityImpl::setCurrentColor(u_int32_t color) {
}