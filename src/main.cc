/**
 * @author Victor
 * @brief Al berro incomplete unsat
 * */

#include <iostream>
#include <utility>
#include <tuple>

#include "gameSet.h"
#include "judge.h"

int main(){

    //All values are added as a tuple {input, correct_output}
    GameSet<std::tuple<std::string, std::string>> names;

    names += {"internationalization", "i18n"};
    names += {"internet", "internet"};
    names += {"tizadurapuerca", "t12a"};
    names += {"lol", "lol"};

    for(auto tupl: names) {
        std::cout << "Possible input for problem x: " << names.pinput (tupl) << std::endl;
        std::cout << "Correct output for problem x: " << names.coutput (tupl) << std::endl;
        std::cout << endl;
    }

    //End of game set functionality

     //std::string path2file = "/home/victor/Projects/HskellOwn/LongWords.hs";
     //std::string tmpdir = "/home/victor/tmp/";

     std::string path2file = "/home/victor/Projects/Checker/test.lisp";
     std::string tmpdir = "/home/victor/tmp/";

     Judge* jdg = new Judge ();

     cout << jdg->compile(path2file, tmpdir) << endl;
     if (jdg->judge(tmpdir+"LongWords", names))
         std::cout << "You passed the test" << std::endl;
     else std::cout << "U piece of shit, unsat retarded clown do not deserve to live" << endl;

    return 0;
}
