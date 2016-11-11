#pragma once

#include "../Core/DissimType.h"

namespace dissim {
namespace Math {

class Common {
public:
    static DissimType::Value_t Truncate(DissimType::Value_t &value, double accuracy);
};

}
}
