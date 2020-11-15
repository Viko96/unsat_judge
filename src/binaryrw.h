#ifndef __BINARYRW_H_
#define __BINARYRW_H_

#include "processcontrol.h"

class binaryrw : public processcontrol {


private:
    std::filesystem::path outdir;

public:

    binaryrw (std::filesystem::path outdir) {
        this->outdir = outdir;
    }

    int child_process() {
        // Changes stdin & stdout of the program
        // and executes it

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

        return err; //UNHADLED
    }

};

#endif // __BINARYRW_H_
