#pragma once

#include <list>
#include <memory>

#include "condition.h"
#include "record.h"

namespace Db {

struct Query
{
    std::list<std::shared_ptr<Condition>> conditions;
    std::list<Record> hits;
};

using QueryPtr = std::shared_ptr<Query>;

} //ns Db

