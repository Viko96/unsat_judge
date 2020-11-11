#include <iostream>
#include <tuple>
#include "gameSet.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/time.h"
#include "sys/wait.h"
#define PASSED 1;
#define FAILED 0;

// To chench
#include <fstream>

using namespace std;

class Judge {

    public:
        Judge() {};

        ~Judge();

        template <class T, class U>
        size_t judge(string outdir, const GameSet<tuple<T, U>> &gs) {

            int pid = fork();

            if (pid == -1) {cout << "Error couldn't fork from judge function" << endl; return 1;}

            if (pid == 0) {
               sleep(1);

               int rfd = open("inputs", O_RDONLY);
               int wfd = open("inputs_user", O_WRONLY | O_CREAT, 0666); //The devil's file writer

               if (rfd == -1) return 2; //ERROR NOT HANDLED
               if (wfd == -1) return 3; //ERROR NOT HANDLED

               dup2(rfd, STDIN_FILENO); //Reading from file the unsat way
               close(rfd);

               dup2(wfd, STDOUT_FILENO); // w2f
               close(wfd);

               int err = execl(outdir.c_str(), outdir.c_str(), NULL);

               if (err == -1) return 3; //ERROR NOT HANDLED

            } else {
                wait(NULL);
                fstream fiwout; //User results file
                fiwout.open("inputs_user", ios::in | ios::out);
                string buf;
                if (fiwout.is_open())
                    for (auto i: gs) {
                        fiwout >> buf;
                        if (buf.compare(get<1>(i))) return FAILED;
                        buf = "";
                    }
                fiwout.close();
            };

            return PASSED;

        };

        //Returns outputdir
        string compile (string path, string tempdir) {

            string fext = path.substr( path.find_last_of(".") + 1 ),
                bin_name = path.substr(path.find_last_of("/") + 1,
                                       path.find_last_of(".") - path.find_last_of("/") - 1);

            int pid = fork();

            string tmpdout;

            if (pid == -1) cout << "Error, couldn't fork" << endl;

            if (pid == 0) {
                int err;

                tmpdout = tempdir + bin_name;

                // Add compiler expressions here
                //Haskell
                if (fext == "hs"){
                    cout << "compiling Haskell" << endl;
                    err = execlp("/usr/bin/ghc","ghc", "-o", tmpdout.c_str(), path.c_str(), NULL);
                }
                //C++
                else if (fext == "cpp"){
                    cout << "compiling c++" << endl;
                    err = execlp ("/usr/bin/g++", "g++", "-g", "-O2", "-std=gnu++17", "-o", tmpdout.c_str(),
                                  path.c_str(), NULL);
                }
                // LISPer
                else if (fext == "lisp") {
                    string str = "(sb-ext:save-lisp-and-die" + tmpdout + ":executable t :toplevel 'main)";
                    cout << "compiling lisp";
                    err = execl("/usr/bin/sbcl", "--no-userinit", "--load", path.c_str(), "--eval",
                                str.c_str(), NULL);
                }

                else return "FAILED UNSAT SHIT"; // TODO add exception

                if (err == -1)
                    cout << "Didn't compile shit " << endl;

            }

            //status of child process (UNHANDLED)
            int waiti;
            wait (&waiti);

            return tmpdout;
        }


};
