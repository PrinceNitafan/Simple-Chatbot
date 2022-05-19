
#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <stdexcept>

namespace cmpt {

inline void error(const std::string& message)
{
    throw std::runtime_error(message);
}

}

#endif
