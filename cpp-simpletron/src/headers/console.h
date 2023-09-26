#ifndef CONSOLE
	#define CONSOLE

#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "processor.h"

namespace simpletron{
    class Console{
        private:
            Processor* processor;
        public:
            Console();
            void load(std::string data);
            void run();
            void read();
    };

    void intro();
    void info();
    void version();
}

#endif