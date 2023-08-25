#pragma once
#pragma warning(disable : 4996)
#include <chrono>
#include <iomanip>
#include <sstream>

namespace aiafpb1
{
	// класс используется для фиксации времени отправки сообщений
	class  TimeData
	{
	private:
		std::chrono::system_clock::time_point m_time;
		static std::string m_format;

	public:
		TimeData();
		~TimeData();
		static void setFormat(const std::string&);
		std::string toString() const;
		void renew();
		void clear();
		TimeData& operator=(const TimeData&);
		friend std::ostream& operator<< (std::ostream&, const TimeData&);
		friend bool operator== (const TimeData&, const TimeData&);
		friend bool operator!= (const TimeData&, const TimeData&);
		friend bool operator< (const TimeData&, const TimeData&);
		friend bool operator> (const TimeData&, const TimeData&);
		friend bool operator<= (const TimeData&, const TimeData&);
		friend bool operator>= (const TimeData&, const TimeData&);
	};
}