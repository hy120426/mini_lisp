#ifndef EVAL_H
#define EVAL_H
#include<unordered_map>
#include <algorithm>
#include <iterator>
#include "./value.h"
#include"./error.h"
#include "./builtins.h"



class EvalEnv : public std::enable_shared_from_this<EvalEnv> {

public:
    static std::shared_ptr<EvalEnv> createGlobal() {
        return std::make_shared<EvalEnv>();
    }
    EvalEnv();
    EvalEnv(std::shared_ptr<EvalEnv> parent) : parent{parent} {
        for (auto& i : Functions) {
            SymbolList.insert({i.first, i.second});
        }
    };
    std::shared_ptr<EvalEnv> createChild(
        const std::vector<std::string>& params,
        const std::vector<ValuePtr>& args);
    std::shared_ptr<EvalEnv> parent;
    ValuePtr apply(ValuePtr proc, std::vector<ValuePtr> args);
    std::vector<ValuePtr> evalList(ValuePtr expr);
    std::unordered_map<std::string, ValuePtr> SymbolList;
    ValuePtr eval(ValuePtr expr) ;
    ValuePtr lookupBinding(std::string nameToBeFind);
};

#endif
