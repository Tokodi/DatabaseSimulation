#include "record.h"

namespace Db {

std::ostream &operator<<(std::ostream &os, const Record &r) {
    os << '{' << r.getValue() << ";" << (r.getFlag() ? "true;" : "false;")
       << (r.getData() != nullptr ? (*r.getData()) : "NULL") << '}';
    return os;
}

std::istream &operator>>(std::istream &is, Record &r) {
    int value;
    bool flag;
    std::string data;

    is >> value >> flag >> data;

    r.setValue(value);
    r.setFlag(flag);
    r.setData(data);

    return is;
}

} //ns Db
