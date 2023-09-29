#ifndef CONSOLE
	#define CONSOLE

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>

#include "utils.h"
#include "processor.h"
#include "assembler.h"

#ifdef _WIN32 // note the underscore: without it, it's not msdn official!
    #define IS_SHELL true
#else
    #define IS_SHELL false
#endif

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