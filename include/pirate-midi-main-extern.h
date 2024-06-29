#pragma once

extern void midi_SendPetalSysEx(const uint8_t* data, size_t size);
extern void midi_SendPetalControlChange(uint8_t channel, uint8_t number, uint8_t value);
extern void midi_SendPetalProgramChange(uint8_t channel, uint8_t number);
extern void midi_AssignPetalControlChangeCallback(void (callback)(uint8_t channel, uint8_t number, uint8_t value));
extern void midi_AssignPetalProgramChangeCallback(void (callback)(uint8_t channel, uint8_t number));
extern void midi_AssignPetalSysemExclusiveCallback(void (callback)(uint8_t* array, unsigned size));
