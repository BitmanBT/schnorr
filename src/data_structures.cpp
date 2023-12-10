#include "data_structures.h"

namespace crypto {
    std::ostream& operator<<(std::ostream& os, public_key& obj) {
        os << "(" << obj.p << "," << obj.q << "," << obj.g << "," << obj.y << ")";
        return os;
    }
} // namespace crypto