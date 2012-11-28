#ifndef KRITI__TIME_VALUE_H
#define KRITI__TIME_VALUE_H

#include <stdint.h>

namespace Kriti {

class TimeValue {
private:
    int64_t m_timeValue;
private:
    TimeValue(int64_t value) : m_timeValue(value) {}
public:
    TimeValue() : m_timeValue(0) {}

    static TimeValue current();
    static TimeValue fromUsec(int64_t us) { return TimeValue(us*1000); }
    static TimeValue fromMsec(int64_t ms) { return TimeValue(ms*1000000); }

    int64_t toUsec() const { return m_timeValue / 1000; }
    int64_t toMsec() const { return m_timeValue / 1000000; }

    bool operator<=(const TimeValue &other) const
        { return m_timeValue <= other.m_timeValue; }
    bool operator>=(const TimeValue &other) const
        { return m_timeValue >= other.m_timeValue; }

    TimeValue operator+(const TimeValue &other) const
        { return m_timeValue + other.m_timeValue; }
    TimeValue operator-(const TimeValue &other) const
        { return m_timeValue - other.m_timeValue; }
};

}  // namespace Kriti

#endif
