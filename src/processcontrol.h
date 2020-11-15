#ifndef __PROCESSCONTROL_H_
#define __PROCESSCONTROL_H_

#include <filesystem>
#include <iostream>

#include "unistd.h"
#include "fcntl.h"
#include "sys/wait.h"

#define MAX_PROCESSES 2

class processcontrol {

    private:
        __pid_t pid;

    public:
        virtual int child_process() = 0;
        virtual int parent_process() {
            int waiti;
            wait (&waiti);
            return waiti;
        }

        __pid_t startNewProcess() {
            if(this->pid < 0 || this->pid > MAX_PROCESSES)
                return this->pid = fork();
            return -1;
        }

        void run() {
            this->startNewProcess(); //UNHANDLED
            if (this->pid == -1)
                std::cout << "Error in run; couldn't fork" << std::endl;
            if (this->pid == 0)
                this->child_process();
            else
                this->parent_process();
        }
    
};

#endif // __PROCESSCONTROL_H_
