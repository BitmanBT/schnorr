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

    void public_key::operator=(const public_key& another) {
        p = another.p;
        q = another.q;
        g = another.g;
        y = another.y;
    }

    void authentification_info_server::operator=(const authentification_info_server& another) {
        e = another.e;
        x = another.x;
        s = another.s;
    }
} // namespace crypto