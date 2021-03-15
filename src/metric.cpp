#include "metric.h"
#include <QSettings>
#include <QDebug>

metric::metric()
{

}

void metric::setType(_metric_type t)
{
    m_type = t;
}

void metric::setValue(double v)
{
    QSettings settings;
    if(m_type == METRIC_WATT)
    {
        if(v > 0)
        {
            if(settings.value("watt_gain", 1.0).toDouble() <= 1.25)
            {
                if(settings.value("watt_gain", 1.0).toDouble() != 1.0)
                {
                    qDebug() << "watt value was " << v << "but it will be transformed to" << v * settings.value("watt_gain", 1.0).toDouble();
                }
                v *= settings.value("watt_gain", 1.0).toDouble();
            }
            if(settings.value("watt_offset", 0.0).toDouble() < 0)
            {
                if(settings.value("watt_offset", 0.0).toDouble() != 0.0)
                {
                    qDebug() << "watt value was " << v << "but it will be transformed to" << v + settings.value("watt_offset", 0.0).toDouble();
                }
                v += settings.value("watt_offset", 0.0).toDouble();
            }
        }
    }
    m_value = v;

    if(paused) return;

    if(value() != 0)
    {
        m_countValue++;
        m_totValue += value();

        if(value() < m_min)
            m_min = value();
    }

    if(value() > m_max)
        m_max = value();
}

void metric::clear(bool accumulator)
{
    if(accumulator)
        m_offset = m_value;
    m_max = 0;
    m_totValue = 0;
    m_countValue = 0;
    m_min = 999999999;
}

double metric::value()
{
    return m_value - m_offset;
}

double metric::average()
{
    if(m_countValue == 0)
        return 0;
    else
        return (m_totValue / m_countValue);
}

void metric::operator = (double v) {
    setValue(v);
}

void metric::operator += (double v) {
    setValue(m_value + v);
}

double metric::min()
{
    return m_min;
}

double metric::max()
{
    return m_max;
}

void metric::setPaused(bool p)
{
    paused = p;
}
