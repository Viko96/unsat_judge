/**
 * @author Victor
 * @brief Al berro incomplete unsat
 * */

#include <iostream>
#include <utility>
#include <tuple>

#include "gameSet.h"
#include "judge.h"
#include "compiler.h"

int main(){

    //All values are added as a tuple {input, correct_output}
    GameSet<std::tuple<std::string, std::string>> names;

    names += {"internationalization", "i18n"};
    names += {"internet", "internet"};
    names += {"tizadurapuerca", "t12a"};
    names += {"lol", "lol"};

    //End of game set functionality

     std::string path2file = "~/Projects/Checker/test.lisp";
     Std::string tmpdir = "~/tmp/";

     jdg->jdge (path2file, tmpdir, names);


    return 0;
}
