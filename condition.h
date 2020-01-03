#pragma once

#include "record.h"

namespace Db {

struct Condition {
        virtual bool eval(const Record &) const = 0;
};

struct BoolCondition : Condition {
        BoolCondition(bool flag);

        bool eval(const Record& record) const;

        bool _flag;
};

struct IntCondition : Condition {
        IntCondition(int boundary, int op);

        bool eval(const Record& record) const;

        int _boundary, _op;
};

struct StringCondition : Condition {
        StringCondition(std::string& data);

        bool eval(const Record& rec) const;

        std::string _data;
};

} //ns Db
