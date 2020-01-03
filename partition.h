#pragma once

#include <vector>

#include "query.h"
#include "record.h"

namespace Db {

class Partition {
    public:
        Partition(int id) : _id(id) {
            _partitionFileName = "input" + std::to_string(_id)+ ".dat";
            loadFile();
        }

        void processQuery(QueryPtr q);
        void print();

    private:
        int _id;
        std::vector<Record> _data;
        std::string _partitionFileName;

        void loadFile();

};

} //ns Db
