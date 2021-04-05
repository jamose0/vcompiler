#ifndef PARSEERROR_H
#define PARSEERROR_H

#include <string>
#include <exception>

class ParseError : public std::exception {
private:
    std::string m_msg;

public:
    ParseError(std::string_view msg)
        : m_msg{msg}
    {
    }

    const char* what() const noexcept override;
};

#endif
