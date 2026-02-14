#pragma once

#include <string>

namespace otus
{

class IProperty
{
public:
    virtual ~IProperty() = default;
    virtual std::string name() = 0;
};

}
