#include"./eval_env.h"
#include"./forms.h"

using namespace std::literals;
std::vector<ValuePtr> EvalEnv::evalList(ValuePtr expr) {
    std::vector<ValuePtr> v = expr->toVector();
    std::vector<ValuePtr> result;
    std::ranges::transform(v,
                           std::back_inserter(result),
                           [this](ValuePtr v) { return this->eval(v);});
    return result;
}
ValuePtr EvalEnv::apply(ValuePtr proc, std::vector<ValuePtr> args) {
    if (typeid(*proc) == typeid(BuiltinProcValue)) {
        return static_cast<BuiltinProcValue&>(*proc).Function(args,*this);
    } else if (typeid(*proc) == typeid(LambdaValue)) {
        return static_cast<LambdaValue&>(*proc).apply(args);
    }
        else {
        throw LispError("Unimplemented");
    }
}
EvalEnv::EvalEnv() {
    for (auto& i : Functions) {
        SymbolList.insert({i.first, i.second});
    }
}
ValuePtr EvalEnv::lookupBinding(std::string nameToBeFind) {
    if (SymbolList.find(nameToBeFind) != SymbolList.end())
        return SymbolList[nameToBeFind];
    else if (parent != nullptr) {
        if (parent->SymbolList.find(nameToBeFind) !=parent->SymbolList.end()) 
            return parent->SymbolList[nameToBeFind];
    }
    else
        throw LispError("Variable " + nameToBeFind + " not defined.");
}
ValuePtr EvalEnv::eval(ValuePtr expr) {
    if (expr->isSelfEvaluating()) {
        return expr;
    } 
    else if (expr->isNil()) {
        throw LispError("Evaluating nil is prohibited.");
    } 
    else if (expr->isList()) {
        if (!static_cast<PairValue&>(*expr).is_list()) return expr;
        std::vector<ValuePtr> v = expr->toVector();
        if (v[0]->asSymbol()) {
            if (SPECIAL_FORMS.find(*v[0]->asSymbol()) == SPECIAL_FORMS.end()) {
                ValuePtr proc = this->eval(v[0]);
                std::vector<ValuePtr> args =
                    evalList(static_cast<PairValue&>(*expr).GetCdr());
                return this->apply(proc, args);
            } 
            else if (auto name = static_cast<PairValue&>(*expr)
                                       .getCar()->asSymbol()) {
                if (SPECIAL_FORMS.find(*name) != SPECIAL_FORMS.end()) {
                    return SPECIAL_FORMS[*name](
                        static_cast<PairValue&>(*expr).GetCdr()->toVector(),
                        *this);
                }
            } 
            else {
                throw LispError("Malformed define.");
            }
        } 
        else if (typeid(*v[0]) == typeid(PairValue)) {
            return eval(std::make_shared<PairValue>(
                eval(v[0]), static_cast<PairValue&>(*expr).GetCdr()));
        } 
        else if (typeid(*v[0]) == typeid(LambdaValue)) {
            std::vector<ValuePtr> args =
                evalList(static_cast<PairValue&>(*expr).GetCdr());
            return this->apply(v[0], args);
        } 
        else
            return expr;
    } 
    else if (auto name = expr->asSymbol()) {
        return lookupBinding(*name);
    } else {
        throw LispError("Unimplemented");
    }
}
std::shared_ptr<EvalEnv> EvalEnv::createChild(
    const std::vector<std::string>& params, const std::vector<ValuePtr>& args) {
    std::shared_ptr<EvalEnv> child =
        std::make_shared<EvalEnv>(this->shared_from_this());
    int size = params.size();
    for (int i = 0; i < size; i++) {
        child->SymbolList.insert({params[i], args[i]});
    }
    return child;
};
ValuePtr LambdaValue::apply(const std::vector<ValuePtr>& args) {
    for (auto& i : body) {
        if (i == *(body.end()-1)) return nowenv->createChild(params, args)->eval(i);
        nowenv->createChild(params, args)->eval(i);
    }
};
