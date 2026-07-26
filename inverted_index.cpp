#include "inverted_index.h"

InvertTerm::InvertTerm(std::string docid, int freqs, int location)
    : docid_(docid), freqs_(freqs)
{
    locations_.emplace_back(location);
}



void InvertList::addTerm(std::string docid, int location) {
    for (InvertTerm& term : termList_) {
        if (term.docid_ == docid) {
            term.freqs_++;
            term.locations_.emplace_back(location);
            return;
        }
    }
    termList_.emplace_back(docid, 1, location);
}

const std::list<InvertTerm> &InvertList::getInvertList() const {
    return termList_;
}



