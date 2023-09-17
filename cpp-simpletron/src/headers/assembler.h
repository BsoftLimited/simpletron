#ifndef ASSEMBLER
	#define ASSEMBLER

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "utils.h"
#include "parser.h"

namespace simpletron::assembler{
    struct Subroutine{
        std::string name;
        std::vector<Expression> exps;
    };

    class Assembler{
        private:
            std::vector<Subroutine> subroutines;
            void insert(std::string sub, std::vector<Expression> codes);
        public:
            Assembler(){
                this->subroutines = {};
            }
            void init(std::string data);
            std::vector<int> run();
    };
}

#endif