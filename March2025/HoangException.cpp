#include "HoangException.h"
#include <sstream>

HoangException::HoangException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* HoangException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* HoangException::GetType() const noexcept
{
	return "Hoang Exception";
}

int HoangException::GetLine() const noexcept
{
	return line;
}

const std::string& HoangException::GetFile() const noexcept
{
	return file;
}

std::string HoangException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}