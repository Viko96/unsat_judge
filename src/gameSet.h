#ifndef GAMESET_H
#define GAMESET_H

#include <vector>
#include <tuple>
#include <string>
#include <fstream>

//Testing puposes
#include <iostream>

using namespace std;

template <class Tuple>
class GameSet : public vector< Tuple > {

    public:
        Tuple operator+=(const Tuple &value){
            this->push_back(value);
            return value;
        };

        //possible input
        auto pinput(const Tuple &i) { return get<0>(i);};

        //correct_output
        auto coutput(const Tuple &i) { return get<1>(i);};

};
#endif
