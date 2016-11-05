#include "Math/Common.h"

namespace dissim {
namespace Math {

DissimType::Value_t Common::Truncate(DissimType::Value_t &value, double accuracy) {
    for (int i = 0; i < value.rows(); i++) {
        for (int j = 0; j < value.cols(); j++) {
            double tempIntVal = static_cast<double>(static_cast<long int>(value(i, j) * accuracy));
            value(i, j) = static_cast<double>(tempIntVal / accuracy);
        }
    }
    return value;
}

}
}
