#pragma once

#include "IInvertedIndex.h"

struct RelativeIndex{
    size_t doc_id;
    double rank;

    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class ISearchEngine
{
private:

public:
    virtual ~ISearchEngine() = default;
    virtual std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input) = 0;
    virtual std::vector<RelativeIndex> search(std::string query) = 0;
    virtual void set_response_limit(int limit) = 0;

};




