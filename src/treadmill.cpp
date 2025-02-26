#include "treadmill.h"

treadmill::treadmill()
{

}

void treadmill::changeSpeed(double speed){ requestSpeed = speed;}
void treadmill::changeInclination(double inclination){ requestInclination = inclination; }
bool treadmill::changeFanSpeed(uint8_t speed){ requestFanSpeed = speed; return true; }
void treadmill::changeSpeedAndInclination(double speed, double inclination){ requestSpeed = speed; requestInclination = inclination;}
metric treadmill::currentInclination(){ return Inclination; }
uint8_t treadmill::fanSpeed() { return FanSpeed; };
bool treadmill::connected() { return false; }
bluetoothdevice::BLUETOOTH_TYPE treadmill::deviceType() { return bluetoothdevice::TREADMILL; }

uint16_t treadmill::watts(double weight)
{
    // calc Watts ref. https://alancouzens.com/blog/Run_Power.html

    uint16_t watts=0;
    if(currentSpeed().value() > 0)
    {
       double pace=60/currentSpeed().value();
       double VO2R=210.0/pace;
       double VO2A=(VO2R*weight)/1000.0;
       double hwatts=75*VO2A;
       double vwatts=((9.8*weight) * (currentInclination().value()/100.0));
       watts=hwatts+vwatts;
    }
    m_watt.setValue(watts);
    return m_watt.value();
}

void treadmill::clearStats()
{
    elapsed.clear(true);
    Speed.clear(false);
    KCal.clear(true);
    Distance.clear(true);
    Heart.clear(false);
    m_jouls.clear(true);
    elevationAcc = 0;
    m_watt.clear(false);

    Inclination.clear(false);
}

void treadmill::setPaused(bool p)
{
    paused = p;
    elapsed.setPaused(p);
    Speed.setPaused(p);
    KCal.setPaused(p);
    Distance.setPaused(p);
    Heart.setPaused(p);
    m_jouls.setPaused(p);
    m_watt.setPaused(p);
    Inclination.setPaused(p);
}

void treadmill::setLap()
{
    elapsed.setLap(true);
    Speed.setLap(false);
    KCal.setLap(true);
    Distance.setLap(true);
    Heart.setLap(false);
    m_jouls.setLap(true);
    m_watt.setLap(false);

    Inclination.setLap(false);
}
