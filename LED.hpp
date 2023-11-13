#pragma once

#include "Pin.hpp"

class LED {
public:
  void toggle();
  virtual void turnOn() = 0;
  virtual void turnOff() = 0;
  virtual void setBrightness(float brightness);
  void setOn(bool isOn);
  bool isOn();
protected:
  bool mIsOn = false;
};

inline void LED::toggle() {
  if (isOn())
    turnOff();
  else
    turnOn();
}

inline bool LED::isOn() {
  return mIsOn;
}

inline void LED::setOn(bool isOn) {
  isOn ? turnOn() : turnOff();
}

class DigitalLED : DigitalPin, public LED {
public:
  DigitalLED(int pinId) : DigitalPin(pinId, DigitalPin::Mode::Output) {}
  ~DigitalLED() = default;

  void turnOn() override;
  void turnOff() override;
  void setBrightness(float bightness) override;
};

inline void DigitalLED::turnOn() {
  write(HIGH);
  mIsOn = true;
}

inline void DigitalLED::turnOff() {
  write(LOW);
  mIsOn = false;
}

inline void DigitalLED::setBrightness(float brightness) {
}

class AnalogLED : AnalogPin, public LED {
public:
  AnalogLED(int pinId) : AnalogPin(pinId, AnalogPin::Mode::Output) {}
  ~AnalogLED() = default;

  void turnOn() override;
  void turnOff() override;
  void setBrightness(float brightness) override;
};

inline void AnalogLED::turnOn() {
  mIsOn = true;
	write(HIGH);
}

inline void AnalogLED::turnOff() {
  mIsOn = false;
  write(LOW);
}

inline void AnalogLED::setBrightness(float brightness) {
  write(brightness * 255);
  mIsOn = brightness != 0;
}
