#pragma once
#include <iostream>
#include <exception>
#include <sstream>
#include <map>

namespace aiafpb1
{
	enum class etype
	{
		empty_array,
		invalid_index,
		invalid_size,
		wrong_type
	};

	class TArrayException : public std::exception
	{
	private:
		static const std::map<etype, std::string> m_message;
		etype m_error;
		std::string m_source;
		std::string m_comment;

	public:
		TArrayException(etype, std::string, std::string = std::string());
		const char* what() const noexcept;
		friend std::ostream& operator<< (std::ostream&, const TArrayException&);
		const std::string getInfo() const;
	};
}