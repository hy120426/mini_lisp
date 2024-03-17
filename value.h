#ifndef VALUE_H
#define VALUE_H
#include<string>
#include<memory>
#include<vector>
#include <optional>
#include<deque>
#include"./error.h"
class Value;
class EvalEnv;
using ValuePtr = std::shared_ptr<Value>;
using BuiltinFuncType = ValuePtr(const std::vector<ValuePtr>&,EvalEnv& env);
class Value {
public: 
    Value();
    virtual std::string toString()=0;
    virtual std::vector<ValuePtr> toVector()=0;
    bool isNil();
    bool isSelfEvaluating();
    bool isList();
    bool isNumber();
    std::optional<std::string> asSymbol();
};
class BooleanValue : public Value {
    bool typebool;

public:
    BooleanValue(const bool x);
    std::string toString();
    std::vector<ValuePtr> toVector();
};
class NumericValue : public Value {
    double typenumber;

public:
    double asNumber() {
        return typenumber;
    }
    NumericValue(const double x);
    std::string toString();
    std::vector<ValuePtr> toVector();
};
class StringValue : public Value {

public:
    std::string typestring;
    StringValue(const std::string x);
    std::string toString();
    std::vector<ValuePtr> toVector();
};
class NilValue : public Value {
public:
    NilValue();
    std::string toString();
    std::vector<ValuePtr> toVector();
};
class SymbolValue : public Value {
    std::string typesymbol;

public:
    SymbolValue(const std::string x);
    std::string toString();
    std::vector<ValuePtr> toVector();
};
class PairValue : public Value {
    ValuePtr left;
    ValuePtr right;
    static int count;

public:
    ValuePtr GetCdr();
    PairValue(ValuePtr x, ValuePtr y);
    std::string toString();
    std::vector<ValuePtr> toVector();
    ValuePtr getCar();
    bool is_list();
};
class BuiltinProcValue : public Value {
    BuiltinFuncType* func{};
    std::string symbol;

public:
    BuiltinProcValue(BuiltinFuncType fun, std::string symbol)
        : func{fun}, symbol{symbol} {};
     std::string toString(); 
     std::vector<ValuePtr> toVector();
     std::string GetType();
     ValuePtr Function(std::vector<ValuePtr> args,EvalEnv& env);
};
class LambdaValue : public Value {
     std::vector<std::string> params;
     std::vector<ValuePtr> body;
     std::shared_ptr<EvalEnv> nowenv;
 public:
     LambdaValue(std::vector<std::string> params, std::vector<ValuePtr> body,
                 std::shared_ptr<EvalEnv> nowenv)
         : params{params}, body{body}, nowenv{nowenv} {};
     std::string toString();  
     std::vector<ValuePtr> toVector();
     ValuePtr apply(const std::vector<ValuePtr>& args);
};
ValuePtr toValue(std::deque<ValuePtr> args);
#endif  // !VALUE_H
