#include"./forms.h"
ValuePtr toValue(const std::vector<ValuePtr>& args) {
    ValuePtr result = std::make_shared<NilValue>();
    if (args.size() == 1) return args[0];
    int size = args.size();
    for (int i = size - 1; i >= 0;i--) {
        result = std::make_shared<PairValue>(std::move(args[i]), std::move(result));
    }
    return result;
}
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    if (auto name = args[0]->asSymbol()) {
        if (auto name1 = args[1]->asSymbol()) {
            if (env.SymbolList.find(*name1) != env.SymbolList.end()) {
                if (env.SymbolList.find(*name) != env.SymbolList.end()) {
                    env.SymbolList.erase(*name);
                }
                env.SymbolList.insert({*name, env.SymbolList[*name1]});
            } 
            else if (env.parent != nullptr) {
                if (env.parent->SymbolList.find(*name1) != env.parent->SymbolList.end()) {
                    if (env.SymbolList.find(*name) != env.SymbolList.end()) {
                        env.SymbolList.erase(*name);
                    }
                    env.SymbolList.insert({*name, env.parent->SymbolList[*name1]});
                } 
            } else
                throw LispError("Unimplemented");
        } else {
            if (env.SymbolList.find(*name) != env.SymbolList.end()) {
                env.SymbolList.erase(*name);
            }
            env.SymbolList.insert({*name, env.eval(args[1])});
        }
        return std::make_shared<NilValue>();
    }
    else if (typeid(*args[0]) == typeid(PairValue)) {
        std::vector<std::string> params(0);
        std::vector<ValuePtr> body(0);
        for (int i = 1; i < args[0]->toVector().size(); i++) {
            params.push_back(args[0]->toVector()[i]->toString());
        }
        for (int i = 1; i < args.size(); i++) {
            body.push_back(args[i]);
        }
        ValuePtr name1 =
            std::make_shared<LambdaValue>(params, body, env.shared_from_this());
        if (auto name = args[0]->toVector()[0]->asSymbol()) {
            if (env.SymbolList.find(*name) != env.SymbolList.end()) {
                env.SymbolList.erase(*name);
            }
            env.SymbolList.insert({*name, name1});
        } else {
            throw LispError("Unimplemented");
        }
        return std::make_shared<NilValue>();
    } 
    else {
        throw LispError("Unimplemented");
    }
}
ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    return args[0];
}
ValuePtr ifForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    if (env.eval(args[0])->toString() == "#f") {
        return env.eval(args[2]);
    }
    return env.eval(args[1]);
}
ValuePtr andForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    int size = args.size();
    if (size == 0) return std::make_shared<BooleanValue>(true);
    int nowptr = 0;
    for (int i = 0; i < size; i++) {
        if (env.eval(args[i])->toString() != "#f") {
            nowptr =i;
            env.eval(args[i]);
        } else
            return std::make_shared<BooleanValue>(false);
    }
    return env.eval(args[nowptr]);
}
ValuePtr orForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    int size = args.size();
    if (size == 0) return std::make_shared<BooleanValue>(false);
    for (int i = 0; i < size; i++) {
        if (env.eval(args[i])->toString() != "#f") {
            return env.eval(args[i]);
        }
    }
    return env.eval(args[size-1]);
}
ValuePtr lambdaForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    std::vector<ValuePtr> body(0);
    std::vector<std::string> params(0);
    for (auto& i : args[0]->toVector()) {
        params.push_back(i->toString());
    }
    for (int i = 1; i < args.size(); i++) {
        body.push_back(args[i]);
    }
    return std::make_shared<LambdaValue>(params, body, env.shared_from_this());
}
ValuePtr CondForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    int size = args.size();
    for (int i = 0; i < size; i++) {
        if (!args[i]->isList())
            return env.eval(args[i]);
        else if (args[i]->toVector().size()==1){
            return env.eval(args[i]->toVector()[0]);
    }
        else if (args[i]->toVector()[0]->toString() == "else")
            return env.eval(args[i]->toVector()[1]);
        else if (env.eval(args[i]->toVector()[0])->toString() == "#t")
            return env.eval(args[i]->toVector()[1]);
    }
}
ValuePtr BeginForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    int size = args.size();
    for (int i = 0; i < size - 1;i++) {
        env.eval(args[i]);
    }
    return env.eval(args[size - 1]);
}
ValuePtr LetForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    std::vector<std::string> lambda_args;
    std::vector<ValuePtr> value_args;
    std::vector<ValuePtr> body;
    int size = args[0]->toVector().size();
    for (int i = 0; i < size; i++) {
        lambda_args.push_back(args[0]->toVector()[i]->toVector()[0]->toString());
        value_args.push_back(args[0]->toVector()[i]->toVector()[1]);
    }
    for (int i = 1; i < args.size(); i++) {
        body.push_back(args[i]);
    }
    return env.apply(
        std::make_shared<LambdaValue>(lambda_args, body, env.shared_from_this()),
        value_args);
}
ValuePtr UnquoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    return env.eval(args[0]);
}
ValuePtr quasiquoteForm(const std::vector<ValuePtr>& args, EvalEnv& env) {
    std::vector<ValuePtr> result;
    if (args[0]->isSelfEvaluating()) return args[0];
    int size = args[0]->toVector().size();
    for (int i = 0; i < size;i++) {
        if (typeid(*args[0]->toVector()[i]) == typeid(PairValue)) {
            if (static_cast<PairValue&>(*args[0]->toVector()[i])
                    .getCar()->toString() == "unquote")
            result.push_back(env.eval(args[0]->toVector()[i]));
            else
                result.push_back(args[0]->toVector()[i]);
        } else
            result.push_back(args[0]->toVector()[i]);
    }
    return toValue(result);
}
 std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
    {"define", defineForm},
    {"quote", quoteForm},
    {"if", ifForm},
    {"and", andForm},       
     {"or", orForm},
    {"lambda", lambdaForm},
    {"cond",CondForm},     
     {"begin", BeginForm}, 
     {"let", LetForm},
    {"unquote", UnquoteForm},
    {"quasiquote",quasiquoteForm}};
