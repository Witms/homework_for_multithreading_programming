#include "TArrayException.h"

namespace aiafpb1
{
	const std::map<etype, std::string> TArrayException::m_message
	{
		{etype::empty_array, "массив является пустым"},
		{etype::invalid_index, "неверное значение индекса"},
		{etype::invalid_size, "размер массива не может быть задан отрицательным числом"},
		{etype::wrong_type, "несоответствие типу элементов массива"}
	};

	const std::string TArrayException::getInfo() const
	{
		std::stringstream ss;
		ss << "При выполнении функции \"" << m_source << "\"" << std::endl << "произошла ошибка : " << TArrayException::m_message.at(m_error) << std::endl;
		if (!m_comment.empty()) ss << "комментарий к ошибке: " << m_comment << std::endl;
		return ss.str();
	}

	TArrayException::TArrayException(etype error, std::string source, std::string comment) : m_error(error), m_source(source), m_comment(comment) {}

	const char* TArrayException::what() const noexcept
	{
		return (TArrayException::m_message.at(m_error)).c_str();
	}

	std::ostream& operator<<(std::ostream& out, const TArrayException& e)
	{
		out << e.getInfo();
		return out;
	}
}
