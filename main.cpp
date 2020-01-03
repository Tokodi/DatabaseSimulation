#include <algorithm>
#include <fstream>
#include <thread>

#include "partition.h"
#include "pipe.hpp"
#include "query.h"
#include "record.h"

static const std::string inputFileName = "input.txt";
static const std::string outputFileName = "output.txt";
static const std::string noRecordsMessage = "{could not find records}";

using QueryPipe = Db::Pipe<Db::QueryPtr>;

void initPartition(int id, QueryPipe& inQ, QueryPipe& outQ) {
    Db::Partition currPartition(id);

    Db::QueryPtr q;
    while ((q = inQ.pop()) != NULL) {
        currPartition.processQuery(q);
        outQ.push(q);
    }

    outQ.push(q);
}

void writeOutput(QueryPipe& inQ) {
    std::ofstream outputFile(outputFileName);

    Db::QueryPtr q;
    while ((q = inQ.pop()) != NULL) {
        if (q->hits.empty()) {
            outputFile << noRecordsMessage << std::endl;
        } else {
            for (auto& hit : q->hits) {
                outputFile << hit << std::endl;
            }
        }
        outputFile << std::endl;
    }
}

Db::QueryPtr createQuery(std::ifstream& inputFile) {
    Db::QueryPtr q = std::make_shared<Db::Query>();

    int conditionCount;
    int conditionType;

    bool flag;
    int boundary, op;
    std::string data;

    inputFile >> conditionCount;
    for (int j = 0; j < conditionCount; ++j) {
        inputFile >> conditionType;
        switch(conditionType) {
            case 1:
                inputFile >> flag;
                q->conditions.push_back(std::make_shared<Db::BoolCondition>(Db::BoolCondition(flag)));
                break;
            case 2:
                inputFile >> boundary;
                inputFile >> op;
                q->conditions.push_back(std::make_shared<Db::IntCondition>(Db::IntCondition(boundary, op)));
                break;
            case 3:
                inputFile >> data;
                q->conditions.push_back(std::make_shared<Db::StringCondition>(Db::StringCondition(data)));
                break;
        }
    }

    return q;
}

int main() {
    std::ifstream inputFile(inputFileName);

    int partitionCount;
    inputFile >> partitionCount;

    std::vector<QueryPipe> pipes(partitionCount + 1);

    std::vector<std::thread> threads;

    for (int i = 0; i < partitionCount; ++i) {
        threads.push_back(std::thread(initPartition,
                                      i + 1,
                                      std::ref(pipes[i]),
                                      std::ref(pipes[i+1])));
    }

    std::thread writerThread(writeOutput, std::ref(pipes.back()));

    int queryCount;
    inputFile >> queryCount;
    for (int i = 0; i < queryCount; ++i) {
        pipes[0].push(createQuery(inputFile));
    }

    pipes[0].push(NULL);
    for (auto& t : threads) {
        t.join();
    }
    writerThread.join();

    return 0;
}
