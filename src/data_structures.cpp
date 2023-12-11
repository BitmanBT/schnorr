#include <data_structures.h>

namespace crypto {
    std::ostream& operator<<(std::ostream& os, public_key& obj) {
        os << "(" << obj.p << "," << obj.q << "," << obj.g << "," << obj.y << ")";
        return os;
    }

    bool operator==(public_key& left, public_key& right) {
        if (left.p == right.p && left.q == right.q && left.g == right.g && left.y == right.y) {
            return true;
        }
        return false;
    }
} // namespace crypto