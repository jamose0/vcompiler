#include "parseerror.h"

const char* ParseError::what() const noexcept
{
    return m_msg.c_str();
}
