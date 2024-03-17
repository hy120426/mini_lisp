#include <iostream>
#include <string>
#include "./tokenizer.h"
#include"./value.h"
#include"./parse.h"
#include "rjsj_test.hpp"
#include"./eval_env.h"
#include"./read.h"

struct TestCtx {
    std::shared_ptr<EvalEnv> env = EvalEnv::createGlobal();
    std::string eval(std::string input) {
        auto tokens = Tokenizer::tokenize(input);
        Parser parser(std::move(tokens));
        auto value = parser.parse();
        auto result = env->eval(std::move(value));
        return result->toString();
    }
};
std::shared_ptr<EvalEnv> env = EvalEnv::createGlobal();
int main(int argc, char** argv) {
    //RJSJ_TEST(TestCtx, newfunction);
    //RJSJ_TEST(TestCtx, safety);
    //RJSJ_TEST(TestCtx, Lv2, Lv3, Lv4, Lv5, Lv5Extra, Lv6, Lv7, Lv7Lib);
    Read readline(argc, argv);
    while (true) {
        try {
            readline.readin();
            readline.doparse();
        } 
        catch (bool blank) {
        }
        catch (std::runtime_error& e) {
            std::cerr << "error: " << e.what() << std::endl;
        }
    }
    //while (true) {
    //    try {
    //        std::cout << ">>> " ;
    //        std::string line;
    //        std::getline(std::cin, line); 
    //        if (std::cin.eof()) {
    //            std::exit(0);
    //        }
    //        auto tokens = Tokenizer::tokenize(line);
    //        Parser parser(std::move(tokens));  // TokenPtr 不支持复制
    //        auto value = parser.parse();
    //        auto result = env->eval(std::move(value));
    //        std::cout << result->toString() << std::endl;
    //    } 
  
    //}
}
