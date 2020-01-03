#include "partition.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

namespace Db {

void Partition::loadFile() {
    std::ifstream partitionFile(_partitionFileName);

    int recordCount;
    partitionFile >> recordCount;

    Record r;
    while (recordCount--) {
        partitionFile >> r;
        _data.push_back(r);
    }
}

void Partition::print() {
    for (auto& r : _data) {
        std::cout << r << std::endl;
    }
}

void Partition::processQuery(QueryPtr q) {
    for (auto& r : _data) {
        if (std::all_of(q->conditions.cbegin(),
                        q->conditions.cend(),
                        [r](std::shared_ptr<Condition> condPtr){
                            return condPtr->eval(r);
                        }))
        {
            q->hits.push_back(r);
        }
    }
}

} //ns Db
