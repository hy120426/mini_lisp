#include"./builtins.h"
#include"./eval_env.h"
void Numberjudge(const std::vector<ValuePtr> &params) {
    for (const auto &i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot add a non-numeric value.");
        }
    }
}
//用来判断是不是数字
void Stringjudge(const std::vector<ValuePtr> &params) {
    for (const auto &i : params) {
        if (typeid(*i)!=typeid(StringValue)) {
            throw LispError("Cannot operator a non-string value.");
        }
    }
}
// 用来判断是不是字符串
void Paramsize(const std::vector<ValuePtr> &params, int num) {
    if (params.size() != num)
        throw LispError("size of argc not right!");
}
//用来判断传入的参数个数是否合适
std::string asString(std::string x) {
    std::string result{};
    for (int i = 1; i < x.size() - 1; i++) result += x[i];
    return result;
}
ValuePtr add(const std::vector<ValuePtr> &params, EvalEnv &env) {
    double result = 0;
    Numberjudge(params);
    for (const auto &i : params) {
        result += static_cast<NumericValue &>(*i).asNumber();
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr jian(const std::vector<ValuePtr> &params, EvalEnv &env) {
    double result = 0;
    Numberjudge(params);
    int size = params.size();
    if (size == 1) result= -static_cast<NumericValue &>(*params[0]).asNumber();
    else if (size > 1) {
        result = static_cast<NumericValue &>(*params[0]).asNumber();
        for (int i = 1; i < size; i++) {
            result -= static_cast<NumericValue &>(*params[i]).asNumber();
        }
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr sin_(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Numberjudge(params);
    Paramsize(params, 1);
    return std::make_shared<NumericValue>(
        std::sin(static_cast<NumericValue &>(*params[0]).asNumber()));
}
ValuePtr cos_(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Numberjudge(params);
    Paramsize(params, 1);
    return std::make_shared<NumericValue>(
        std::cos(static_cast<NumericValue &>(*params[0]).asNumber()));
}
ValuePtr sqrt_(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Numberjudge(params);
    Paramsize(params, 1);
    double number=static_cast<NumericValue &>(*params[0]).asNumber();
    if (number < 0) throw LispError("cannot sqrt!");
    return std::make_shared<NumericValue>(
        std::sqrt(number));
}
ValuePtr pow_(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Numberjudge(params);
    Paramsize(params, 2);
    return std::make_shared<NumericValue>(
        std::pow(static_cast<NumericValue &>(*params[0]).asNumber(),
            static_cast<NumericValue &>(*params[1]).asNumber()));
}
ValuePtr mutiply(const std::vector<ValuePtr> &params, EvalEnv &env) {
    double result = 1;
    Numberjudge(params);
    for (const auto &i : params) {
        result *= static_cast<NumericValue &>(*i).asNumber();
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr chu(const std::vector<ValuePtr> &params, EvalEnv &env) {
    double result = 1;
    Numberjudge(params);
    int size = params.size();
    if (size == 1) {
        if (static_cast<NumericValue &>(*params[0]).asNumber() == 0)
            throw LispError("Cannot divide 0.");
        else
            result /= static_cast<NumericValue &>(*params[0]).asNumber();
    } else if (size > 1) {
        result = static_cast<NumericValue &>(*params[0]).asNumber();
        for (int i = 1; i < size; i++) {
            if (static_cast<NumericValue &>(*params[i]).asNumber() == 0)
                throw LispError("Cannot divide 0.");
            result /= static_cast<NumericValue &>(*params[i]).asNumber();
        }
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr abs_(const std::vector<ValuePtr> &params, EvalEnv &env) {
    double result = 0;
    Paramsize(params, 1);
    Numberjudge(params);
        static_cast<NumericValue &>(*params[0]).asNumber() > 0
            ? result = static_cast<NumericValue &>(*params[0]).asNumber()
            : result = -static_cast<NumericValue &>(*params[0]).asNumber();
        return std::make_shared<NumericValue>(result);
    }
ValuePtr expt(const std::vector<ValuePtr> &params, EvalEnv &env) {
        Paramsize(params, 2);
    double result = 0;
        Numberjudge(params);
        if (static_cast<NumericValue &>(*params[0]).asNumber() == 0 &&
            static_cast<NumericValue &>(*params[1]).asNumber() == 0)
            throw LispError("Not define 0^0.");
        result = pow(static_cast<NumericValue &>(*params[0]).asNumber(),
                     static_cast<NumericValue &>(*params[1]).asNumber());
        return std::make_shared<NumericValue>(result);
}
ValuePtr quotient(const std::vector<ValuePtr> &params, EvalEnv &env) {
        int result = 0;
        Paramsize(params, 2);
        Numberjudge(params);
            if (static_cast<NumericValue &>(*params[1]).asNumber() == 0)
            throw LispError("Cannot divide 0.");
            result = static_cast<NumericValue &>(*params[0]).asNumber() /
                     static_cast<NumericValue &>(*params[1]).asNumber();
            return std::make_shared<NumericValue>(result);
        }
ValuePtr modulo(const std::vector<ValuePtr> &params, EvalEnv &env) {
        int result = 0;
            Paramsize(params, 2);
            Numberjudge(params);
            int x = static_cast<NumericValue &>(*params[0]).asNumber(),
                y = static_cast<NumericValue &>(*params[1]).asNumber();
            result = x % y;
            if (result * y < 0) result += y;
            return std::make_shared<NumericValue>(result);
}
ValuePtr remainder_(const std::vector<ValuePtr> &params, EvalEnv &env) {
            int result = 0;
            Paramsize(params, 2);
            Numberjudge(params);
            int x = static_cast<NumericValue &>(*params[0]).asNumber(),
                y = static_cast<NumericValue &>(*params[1]).asNumber();
            result = x % y;
            return std::make_shared<NumericValue>(result);
            }
//上面这些是数学函数
ValuePtr eq_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
            Paramsize(params, 2);
    if (typeid(*params[0]) == typeid(BooleanValue) ||
        typeid(*params[0]) == typeid(SymbolValue) ||
        typeid(*params[0]) == typeid(NumericValue) ||
        typeid(*params[0]) == typeid(NilValue)) {
        if (params[0]->toString() == params[1]->toString())
            return std::make_shared<BooleanValue>(true);
        return std::make_shared<BooleanValue>(false);
    }
    if (params[0] == params[1]) return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr equal_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    if (params[0]->toString() == params[1]->toString())
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr not_(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (params[0]->toString() == "#f")
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr dengyu(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    Numberjudge(params);
    if (static_cast<NumericValue &>(*params[0]).asNumber() ==
        static_cast<NumericValue &>(*params[1]).asNumber())
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr dadengyu(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    Numberjudge(params);
    if (static_cast<NumericValue &>(*params[0]).asNumber() >=
        static_cast<NumericValue &>(*params[1]).asNumber())
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr xiaodengyu(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    Numberjudge(params);
    if (static_cast<NumericValue &>(*params[0]).asNumber() <=
        static_cast<NumericValue &>(*params[1]).asNumber())
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr even_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    Numberjudge(params);
    if ((int)static_cast<NumericValue &>(*params[0]).asNumber() % 2 == 0)
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr odd_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    Numberjudge(params);
    if ((int)static_cast<NumericValue &>(*params[0]).asNumber() % 2 != 0)
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr zero_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    Numberjudge(params);
    if ((int)static_cast<NumericValue &>(*params[0]).asNumber() == 0)
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr bigger(const std::vector<ValuePtr> &params, EvalEnv &env) {
        Paramsize(params, 2);
        Numberjudge(params);
    if (static_cast<NumericValue &>(*params[0]).asNumber() >
        static_cast<NumericValue &>(*params[1]).asNumber())
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
ValuePtr smaller(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    Numberjudge(params);
    if (static_cast<NumericValue &>(*params[0]).asNumber() <
        static_cast<NumericValue &>(*params[1]).asNumber())
        return std::make_shared<BooleanValue>(true);
    return std::make_shared<BooleanValue>(false);
}
//上面这些是比较函数
ValuePtr append(const std::vector<ValuePtr> &params, EvalEnv &env) {
    std::deque<ValuePtr> result;
    for (auto &i : params) {
        for (auto &j : i->toVector()) {
            result.push_back(j);
        }
    }
    return toValue(result);
}
ValuePtr map(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    std::deque<ValuePtr> result;
    int size = !params[1]->isList() ? 1 : params[1]->toVector().size();
    if (typeid(*params[0]) != typeid(BuiltinProcValue) &&
        typeid(*params[0]) != typeid(LambdaValue))
        throw LispError("Not defined!");
    for (int i = 0; i < size; i++) {
        std::vector<ValuePtr> temp{};
        temp.push_back(params[1]->toVector()[i]);
        if (typeid(*params[0]) == typeid(BuiltinProcValue))
            result.push_back(static_cast<BuiltinProcValue &>(*params[0])
                                 .Function(temp, env));
        else {
            result.push_back(env.apply(params[0], temp));
        }
    }
    return toValue(result);
}
ValuePtr filter_(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    std::deque<ValuePtr> result;
    int size = !params[1]->isList() ? 1 : params[1]->toVector().size();
    if (typeid(*params[0]) != typeid(BuiltinProcValue) &&
        typeid(*params[0]) != typeid(LambdaValue))
        throw LispError("Not defined!");
    for (int i = 0; i < size; i++) {
        std::vector<ValuePtr> temp{};
        temp.push_back(params[1]->toVector()[i]);
        if (typeid(*params[0]) == typeid(BuiltinProcValue)) {
            if (static_cast<BuiltinProcValue &>(*params[0])
                    .Function(temp, env)
                    ->toString() == "#t")
                result.push_back(params[1]->toVector()[i]);
        } else {
            if (env.apply(params[0], temp)->toString() == "#t")
                result.push_back(params[1]->toVector()[i]);
        }
    }
    return toValue(result);
}
ValuePtr car(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (!params[0]->isList()) throw LispError("not a list");
    return static_cast<PairValue &>(*params[0]).getCar();
}
ValuePtr cdr(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    return static_cast<PairValue &>(*params[0]).GetCdr();
}
ValuePtr cons(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    return std::make_shared<PairValue>(params[0], params[1]);
}
ValuePtr length(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    return std::make_shared<NumericValue>(params[0]->toVector().size());
}
ValuePtr list(const std::vector<ValuePtr> &params, EvalEnv &env) {
    std::deque<ValuePtr> result;
    for (auto &i : params) {
        result.push_back(i);
    }
    return toValue(result);
}
ValuePtr reduce_(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 2);
    std::vector<ValuePtr> list{params[1]};
    if (length(list, env)->toString() == "0") throw LispError("Cannot be 0");
    if (length(list, env)->toString() == "1")
        return car(list, env);
    else {
        std::vector<ValuePtr> args;
        std::vector<ValuePtr> leftover;
        leftover.push_back(params[0]);
        leftover.push_back(cdr(list, env));
        args.push_back(car(list, env));
        args.push_back(reduce_(leftover, env));
        return static_cast<BuiltinProcValue &>(*params[0]).Function(args, env);
    }
}
//上面这些是对子操作函数
ValuePtr atom_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(BooleanValue) ||
        typeid(*params[0]) == typeid(NumericValue) ||
        typeid(*params[0]) == typeid(StringValue) ||
        typeid(*params[0]) == typeid(SymbolValue) ||
        typeid(*params[0]) == typeid(NilValue))
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};
ValuePtr bool_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(BooleanValue))
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};
ValuePtr number_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(NumericValue))
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};
ValuePtr list_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(NilValue))
        return std ::make_shared<BooleanValue>(true);
    if (typeid(*params[0]) == typeid(PairValue) &&
        static_cast<PairValue &>(*params[0]).is_list())
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};
ValuePtr pair_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(PairValue))
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};
ValuePtr null_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(NilValue))
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};
ValuePtr string_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(StringValue))
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};
ValuePtr symbol_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(SymbolValue))
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};
ValuePtr procedure_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(BuiltinProcValue) ||
        typeid(*params[0]) == typeid(LambdaValue))
        return std ::make_shared<BooleanValue>(true);
    return std ::make_shared<BooleanValue>(false);
};  
ValuePtr integer_or_not(const std::vector<ValuePtr> &params, EvalEnv &env) {
    Paramsize(params, 1);
    if (typeid(*params[0]) == typeid(NumericValue)) {
        std::string number = params[0]->toString();
        for (int i = 0; i < number.size(); i++) {
            if (number[i] == '.') return std ::make_shared<BooleanValue>(false);
        }
        return std ::make_shared<BooleanValue>(true);
    }
    return std ::make_shared<BooleanValue>(false);
};
//上面的是类型检查函数
ValuePtr print(const std::vector<ValuePtr> &params, EvalEnv &env) {
    for (const auto &i : params) {
        std::cout << i->toString() << std::endl;
    }
    return std::make_shared<NilValue>();
}
ValuePtr display(const std::vector<ValuePtr> &params, EvalEnv &env) {
    for (const auto &i : params) {
        if (typeid(*i) == typeid(StringValue)) {
            std::cout << static_cast<StringValue &>(*i).typestring;
        } 
        else {
            std::cout <<i->toString();
        }
    }
    return std::make_shared<NilValue>();
}
ValuePtr displayln(const std::vector<ValuePtr> &params, EvalEnv &env) {
    for (const auto &i : params) {
        if (typeid(*i) == typeid(StringValue)) {
            std::cout << static_cast<StringValue &>(*i).typestring << std::endl;
        } else {
            std::cout << i->toString() << std::endl;
        }
    }
    return std::make_shared<NilValue>();
}
ValuePtr exits(const std::vector<ValuePtr> &params, EvalEnv &env) {
    if (params.size() == 0) exit(0);
    if (params[0]->isNumber())
        exit(int(static_cast<NumericValue &>(*params[0]).asNumber()));
    throw LispError("cannot exit as this!");
}
ValuePtr newline(const std::vector<ValuePtr> &params, EvalEnv &env) {
    return std::make_shared<NilValue>();
}
ValuePtr apply(const std::vector<ValuePtr> &params, EvalEnv &env){
            ValuePtr proc = env.eval(params[0]);
            std::vector<ValuePtr>args = params[1]->toVector();
            return env.apply(proc, args);
    };
ValuePtr error_(const std::vector<ValuePtr> &params, EvalEnv &env) {
            if (params.size() == 0) throw LispError(" ");
            throw LispError(params[0]->toString());
    };
ValuePtr eval(const std::vector<ValuePtr> &params, EvalEnv &env) {
            return env.eval(params[0]);
};
//上面的是核心库函数
ValuePtr cat(const std::vector<ValuePtr> &params, EvalEnv &env) {
            Stringjudge(params);
            std::string result{};
            for (const auto &i : params) {
        result += asString(i->toString());
            }
            return std::make_shared<StringValue>(result);
}//拼接
ValuePtr trans(const std::vector<ValuePtr> &params, EvalEnv &env) {
            Stringjudge(params);
            std::deque<ValuePtr> result;
            for (const auto &i : params) {
        result.push_back(
            std::make_shared<NumericValue>(std::stof(asString(i->toString()))));
            }
            return toValue(result);
}  // 转换整数
ValuePtr up(const std::vector<ValuePtr> &params, EvalEnv &env) {
            Stringjudge(params);
            std::deque<ValuePtr> result;
            for (const auto &i : params) {
        std::string argc = asString(i->toString());
        for (int j=0;j<argc.size();j++){
            if (argc[j] >= 97 && argc[j] <= 122) argc[j] -= 32;
        }
        result.push_back(std::make_shared<StringValue>(argc));
            }
            return toValue(result);
}//大写
ValuePtr down(const std::vector<ValuePtr> &params, EvalEnv &env) {
            Stringjudge(params);
            std::deque<ValuePtr> result;
            for (const auto &i : params) {
        std::string argc = asString(i->toString());
        for (int j = 0; j < argc.size(); j++) {
            if (argc[j] >= 65 && argc[j] <= 90) argc[j] += 32;
        }
        result.push_back(std::make_shared<StringValue>(argc));
            }
            return toValue(result);
}  // 大写
    //上面是添加的字符串函数
    std::unordered_map<std::string, ValuePtr> Functions{
        {"+", std::make_shared<BuiltinProcValue>(&add, "+")}, 
        {"print", std::make_shared<BuiltinProcValue>(&print ,"print" )},
        {"display", std::make_shared<BuiltinProcValue>(&display, "display")},
        {"exit", std::make_shared<BuiltinProcValue>(&exits, "exit")},
        {"newline", std::make_shared<BuiltinProcValue>(&newline, "newline")},
        {"*", std::make_shared<BuiltinProcValue>(&mutiply, "*")}, 
        {">", std::make_shared<BuiltinProcValue>(&bigger,">")},
        {"<", std::make_shared<BuiltinProcValue>(&smaller, "<")},
        {"=", std::make_shared<BuiltinProcValue>(&dengyu, "=")},
        {">=", std::make_shared<BuiltinProcValue>(&dadengyu, ">=")},
        {"<=", std::make_shared<BuiltinProcValue>(&xiaodengyu, "<=")},
        {"-", std::make_shared<BuiltinProcValue>(&jian, "-")} ,
        {"/", std::make_shared<BuiltinProcValue>(&chu, "/")},
        {"apply", std::make_shared<BuiltinProcValue>(&apply, "apply")},
        {"error", std::make_shared<BuiltinProcValue>(&error_, "error")},
        {"eval", std::make_shared<BuiltinProcValue>(&eval, "eval")},
        {"displayln", std::make_shared<BuiltinProcValue>(&displayln, "displayln")},
        {"atom?", std::make_shared<BuiltinProcValue>(&atom_or_not, "atom?")},
        {"boolean?", std::make_shared<BuiltinProcValue>(&bool_or_not, "boolean?")},
        {"number?", std::make_shared<BuiltinProcValue>(&number_or_not, "number?")},
        {"list?", std::make_shared<BuiltinProcValue>(&list_or_not, "list?")},
        {"abs", std::make_shared<BuiltinProcValue>(&abs_, "abs")},
        {"pair?", std::make_shared<BuiltinProcValue>(&pair_or_not, "pair?")},
        {"null?", std::make_shared<BuiltinProcValue>(&null_or_not, "null?")},
        {"string?", std::make_shared<BuiltinProcValue>(&string_or_not, "string?")},
        {"procedure?", std::make_shared<BuiltinProcValue>(&procedure_or_not, "procedure?")},
        {"integer?", std::make_shared<BuiltinProcValue>(&integer_or_not, "integer?")},
        {"append", std::make_shared<BuiltinProcValue>(&append, "append")}, 
        {"car", std::make_shared<BuiltinProcValue>(&car, "car")},
        {"cdr", std::make_shared<BuiltinProcValue>(&cdr, "cdr")},
        {"cons", std::make_shared<BuiltinProcValue>(&cons, "cons")},
        {"length", std::make_shared<BuiltinProcValue>(&length, "length")},
        {"list", std::make_shared<BuiltinProcValue>(&list, "list")},
        {"expt", std::make_shared<BuiltinProcValue>(&expt, "expt")},
        {"quotient", std::make_shared<BuiltinProcValue>(&quotient, "quotient")},
        {"modulo", std::make_shared<BuiltinProcValue>(&modulo, "modulo")},
        {"remainder", std::make_shared<BuiltinProcValue>(&remainder_, "remainder")},
        {"eq?",std::make_shared<BuiltinProcValue>(&eq_or_not, "eq?")},
        {"equal?", std::make_shared<BuiltinProcValue>(&equal_or_not, "equal?")},
        {"not", std::make_shared<BuiltinProcValue>(&not_, "not")},
        {"even?", std::make_shared<BuiltinProcValue>(&even_or_not, "even?")},
        {"odd?", std::make_shared<BuiltinProcValue>(&odd_or_not, "odd?")},
        {"zero?", std::make_shared<BuiltinProcValue>(&zero_or_not, "zero?")},
        {"map", std::make_shared<BuiltinProcValue>(&map, "map")},
        {"filter", std::make_shared<BuiltinProcValue>(&filter_, "filter")},
        {"reduce", std::make_shared<BuiltinProcValue>(&reduce_, "reduce")},
        {"symbol?", std::make_shared<BuiltinProcValue>(&symbol_or_not, "symbol?")},
        {"sin", std::make_shared<BuiltinProcValue>(&sin_, "sin")},
        {"cos", std::make_shared<BuiltinProcValue>(&cos_, "cos")},
        {"sqrt", std::make_shared<BuiltinProcValue>(&sqrt_, "sqrt")},
        {"pow", std::make_shared<BuiltinProcValue>(&pow_, "pow")},
        {"strcat", std::make_shared<BuiltinProcValue>(&cat ,"strcat")},
        {"transform", std::make_shared<BuiltinProcValue>(&trans, "transform")},
        {"up", std::make_shared<BuiltinProcValue>(&up, "up")},
        {"down", std::make_shared<BuiltinProcValue>(&down, "down")}};
