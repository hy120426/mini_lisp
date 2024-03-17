#pragma once
#include <iostream>
#include <string>
#include<fstream>
#include "./tokenizer.h"
#include"./value.h"
#include"./parse.h"
#include "rjsj_test.hpp"
#include"./eval_env.h"
class Read {
    int argc;
    char** argv;
    std::string line;
    std::ostream* os;
    std::istream* is;
    std::shared_ptr<EvalEnv> env;

public:
    Read(int argc, char** argv) : argc(argc), argv(argv) {
        os = &std::cout;
        is = &std::cin;
        env = EvalEnv::createGlobal();
        if (argc > 1) {
            std::string file1 = argv[1];
            if (argv[1][0] != '-') {
                is = new std::ifstream(file1, std::ios::in);
            } else {
                std::string file2 = argv[2];
                os = new std::ofstream(file2, std::ios::out);
            }
            if (argc > 3) {
                std::string file2=argv[3];
                os = new std::ofstream(file2, std::ios::out);
            }
        }
    };
    ~Read() {
        if (os) delete[] os;
        if (is) delete[] is;
    }
    void readin() {
        line = {};
        int countleft = 0;
        int countright = 0;
            if (is == &std::cin) std::cout << ">>> ";
        std::string result;
            std::getline(*is, result);
        line += result;
            for (int i = 0; i < line.size(); i++) {
            if (line[i] == '(') countleft++;
            if (line[i] == ')') countright++;
            }
            while (countleft != countright) {
            if (is==&std::cin)
            for (int i = 0; i < line.size()+3; i++) std::cout << ' ';
            result = {};
            std::getline(*is, result);
            line += ' '+result;
            countright = 0;
            countleft = 0;
            for (int j = 0; j < line.size(); j++) {
                if (line[j] == '(') countleft++;
                if (line[j] == ')') countright++;
            }
            }
            if (is->eof()) std::exit(0);
    }
    void doparse(){
        auto tokens = Tokenizer::tokenize(line);
        Parser parser(std::move(tokens));  // TokenPtr 不支持复制
        auto value = parser.parse();
        auto result = env->eval(std::move(value));
        if (is==&std::cin)
        *os << result->toString() << std::endl;
    };
};
