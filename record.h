#pragma once

#include <istream>
#include <memory>
#include <ostream>

namespace Db {

using StringPtr = std::shared_ptr<std::string>;

class Record {
    public:
        Record() {};
        Record(int v, bool f, const std::shared_ptr<std::string> &ptr) : _value(v), _flag(f), _data(ptr) {}

        //Getters
        int getValue() const { return _value; }
        bool getFlag() const { return _flag; }
        StringPtr getData() const { return _data; }

        //Setters
        void setValue(int value) { _value = value; }
        void setFlag(bool flag) { _flag = flag; }
        void setData(std::string data) {
            if (data == "NULL") {
                _data = nullptr;
            } else {
                _data.reset(new std::string(data));
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const Record &r);
        friend std::istream &operator>>(std::istream &is, Record &r);

    private:
        int _value;
        bool _flag;
        StringPtr _data;
};

} //ns Db
