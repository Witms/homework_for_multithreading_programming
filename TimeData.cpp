#include "TimeData.h"

namespace aiafpb1
{
	TimeData::TimeData() : m_time(std::chrono::system_clock::now()) {}	// при создании фиксируется текущее системное время
	TimeData::~TimeData() {}

	std::string TimeData::m_format = "%d.%m.%Y %H:%M:%S";	// задание формата вывода по умолчанию

	// установка формата вывода
	void TimeData::setFormat(const std::string& format) { TimeData::m_format = format; }

	// преобразование в строку
	std::string TimeData::toString() const
	{
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}

	// перезапись текущего системного времени
	void TimeData::renew() { m_time = std::chrono::system_clock::now(); }

	// установка начального "нулевого" значения
	void TimeData::clear() { m_time = std::chrono::time_point<std::chrono::system_clock>(); }

	// реализация оператора присваивания
	TimeData& TimeData::operator=(const TimeData& t)
	{
		if (&t != this) { m_time = t.m_time; }
		return *this;
	}

	// вывод в поток с преобразованием к заданному формату
	std::ostream& operator<<(std::ostream& out, const TimeData& t)
	{
		auto tt = std::chrono::system_clock::to_time_t(t.m_time);
		auto tm = *std::localtime(&tt);
		out << std::put_time(&tm, t.m_format.c_str());
		return out;
	}

	// далее реализация операторов сравнения

	bool operator==(const TimeData& t1, const TimeData& t2) { return (t1.m_time == t2.m_time); }

	bool operator!=(const TimeData& t1, const TimeData& t2) { return !(t1 == t2); }

	bool operator<(const TimeData& t1, const TimeData& t2) { return (t1.m_time < t2.m_time); }

	bool operator>(const TimeData& t1, const TimeData& t2) { return (t1.m_time > t2.m_time); }

	bool operator<=(const TimeData& t1, const TimeData& t2) { return !(t1 > t2); }

	bool operator>=(const TimeData& t1, const TimeData& t2) { return !(t1 < t2); }
}
