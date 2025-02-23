#ifndef SESSIONLINE_H
#define SESSIONLINE_H
#include <QTimer>
#include <QDateTime>

class SessionLine
{
public:
    double speed;
    int8_t inclination;
    double distance;
    uint16_t watt;
    int8_t resistance;
    uint8_t heart;
    double pace;
    uint8_t cadence;
    QDateTime time;
    double calories;
    double elevationGain;
    uint32_t elapsedTime;
    bool lapTrigger = false;

    SessionLine();
    SessionLine(double speed, int8_t inclination, double distance, uint16_t watt, int8_t resistance, uint8_t heart, double pace, uint8_t cadence, double calories, double elevationGain, uint32_t elapsed, bool lap, QDateTime time = QDateTime::currentDateTime());
};

#endif // SESSIONLINE_H
