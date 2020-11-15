#ifndef __COMPILER_H_
#define __COMPILER_H_

#define _null_ (char*)0

#include "processcontrol.h"
#include "sys/wait.h"
#include <filesystem>
#include <string>

typedef std::filesystem::path path;
typedef std::string string;

class compiler : public processcontrol { //call compile.run

private:
    path srcfile;
    path tmpdir;

public:
    compiler(path srcfile, path tmpdir) {this->tmpdir=tmpdir; set_srcfile(srcfile);};
    compiler(path tmpdir) {this->tmpdir=tmpdir;};

    void set_srcfile(path srcfile) {this->srcfile = srcfile;}

    int child_process() {
        const string
            fext = static_cast<string> (srcfile.extension()).substr(1),
            bin_name = srcfile.filename();

        path tmpdout;

        int err;

        tmpdout = tmpdir.concat(bin_name); //+ bin_name;

        // Add compiler expressions here
        //Haskell
        if (fext == "hs"){
            //"compiling Haskell"
            err = execlp("/usr/bin/ghc","ghc", "-o", tmpdout.c_str(), srcfile.c_str(), _null_); //right way
        }
        //C++
        else if (fext == "cpp"){
            //"compiling c++"
            err = execlp ("/usr/bin/g++", "g++", "-g", "-O2", "-std=gnu++17", "-o", tmpdout.c_str(),
                          srcfile.c_str(), _null_);
        }
        // LISPer
        else if (fext == "lisp") {
            string str = "(sb-ext:save-lisp-and-die" + tmpdout.string() + ":executable t :toplevel 'main)";
            //cout << "compiling lisp";
            err = execl("/usr/bin/sbcl", "--no-userinit", "--load", srcfile.c_str(), "--eval",
                        str.c_str(), _null_);
        }

        else err = -1;

        return err; // err == -1 didn't compile shit, something went wrong
    }

};

#endif // __COMPILER_H_
