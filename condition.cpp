#include "condition.h"

namespace Db {

BoolCondition::BoolCondition(bool flag) {
    _flag = flag;
}

bool BoolCondition::eval(const Record& record) const {
    return !(record.getFlag() ^ _flag);
}

IntCondition::IntCondition(int boundary, int op) {
    _boundary = boundary;
    _op = op;
}

bool IntCondition::eval(const Record& record) const {
    switch(_op) {
        case -1:
            return _boundary < record.getValue();
            break;
        case 0:
            return _boundary == record.getValue();
            break;
        case 1:
            return _boundary > record.getValue();
            break;
        default:
            return false;
    }
}

StringCondition::StringCondition(std::string& data) {
    _data = data;
}

bool StringCondition::eval(const Record& rec) const {
    if (_data == "NULL") {
        return rec.getData() == nullptr;
    } else {
        if (rec.getData() == nullptr) {
            return false;
        }
        return *rec.getData() == _data;
    }
}

} //ns Db
