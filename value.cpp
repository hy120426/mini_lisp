#include<iostream>
#include<iomanip>
#include<sstream>
#include"./value.h"
#include"./eval_env.h"

Value::Value(){};
bool Value::isNil() {
    if (typeid(*this) == typeid(NilValue)) return 1;
    return 0;
}
bool Value::isList() {
    if (typeid(*this) == typeid(NilValue)) return 1;
    if (typeid(*this) == typeid(PairValue)) {
        if (static_cast<PairValue &>(*this).is_list()) return 1;
    }
    return 0;
}
bool Value::isNumber() {
    if (typeid(*this) == typeid(NumericValue)) return 1;
    return 0;
}
bool Value::isSelfEvaluating() {
    if (typeid(*this) == typeid(BooleanValue) ||
        typeid(*this) == typeid(NumericValue) ||
        typeid(*this) == typeid(StringValue)||
        typeid(*this)==typeid(BuiltinProcValue)||
        typeid(*this)==typeid(LambdaValue))
        return 1;
    if (typeid(*this) == typeid(PairValue)) {
        if (!static_cast<PairValue &>(*this).is_list()) return 1;
    }
    return 0;
}
std::optional<std::string> Value::asSymbol() {
    if (typeid(*this) == typeid(SymbolValue)) {
        return this->toString();
    } else if (typeid(*this) == typeid(BuiltinProcValue))
        return static_cast<BuiltinProcValue &>(*this).GetType();
    return std::nullopt;
}
BooleanValue::BooleanValue(const bool x) : typebool(x){};
std::string BooleanValue::toString() {
    if (typebool) return "#t";
    return  "#f";
}
std::vector<ValuePtr> BooleanValue::toVector() {
    throw LispError("Not a list!");
}
NumericValue::NumericValue(const double x) : typenumber(x){};
std::string NumericValue::toString() {
    std::string str = std::to_string(typenumber);
    for (auto i = str.end()-1; i != str.begin(); i--) {
        if (*i != '0' && *i != '.') break;
        if (*i == '.') {
            str.erase(i, str.end());
            break;
        }
    }
    return str;
}
std::vector<ValuePtr> NumericValue::toVector() {
    throw LispError("Not a list!");
}
StringValue::StringValue(const std::string x) : typestring(x){};
std::string StringValue::toString() {
    std::stringstream s;
    s << std::quoted(typestring);
    return s.str();
}
std::vector<ValuePtr> StringValue::toVector() {
    throw LispError("Not a list!");
}
NilValue::NilValue(){};
std::string NilValue::toString() {
    return "()";
}
std::vector<ValuePtr> NilValue::toVector() {
    std::vector<ValuePtr> v(0);
    return v;
}
SymbolValue::SymbolValue(const std::string x) : typesymbol(x){};
std::string SymbolValue::toString() {
    return typesymbol;
}
std::vector<ValuePtr> SymbolValue::toVector() {
    throw LispError("Not a list!");
}
int PairValue::count = 0;
PairValue::PairValue(ValuePtr x, ValuePtr y) : left(x), right(y) {};
std::string PairValue::toString() {
    std::string str{};
    if (count==0)
        str = '(';
    if (typeid(*left) == typeid(PairValue)) str += '(';
    count++;
    str += left->toString();
    if (typeid(*left) == typeid(PairValue)) str += ')';
    typeid(*right) != typeid(NilValue)
        ? typeid(*right) != typeid(PairValue)
                                             ? str += " ." + right->toString()
                                             : str += ' ' + right->toString()
                                       : str;
    count--;
    if (count==0) 
    str += ')';
    return str;
}
ValuePtr PairValue::GetCdr() {
    return right;
}
ValuePtr PairValue::getCar() {
    return left;
}
std::vector<ValuePtr> PairValue::toVector() {
    std::vector<ValuePtr> v(0);
    if (this->is_list()) {
        v.push_back(left);
        for (auto x : right->toVector()) {
            if (typeid(*x) != typeid(NilValue)) v.push_back(x);
        }
        return v;
    } else
        throw LispError("Not a list!");
}
bool PairValue::is_list() {
    if (typeid(*right) == typeid(NilValue) ||
        typeid(*right) == typeid(PairValue))
        return true;
    return false;
}
ValuePtr BuiltinProcValue::Function(std::vector<ValuePtr> args, EvalEnv &env) {
    return func(args,env);
}
std::string BuiltinProcValue::toString() {
    return "#<procedure>";
}
std::string BuiltinProcValue::GetType() {
    return symbol;
}
std::vector<ValuePtr> BuiltinProcValue::toVector() {
    throw LispError("Not a list!");
}
std::string LambdaValue::toString() {
    return "#<procedure>";
}
std::vector<ValuePtr> LambdaValue::toVector() {
    throw LispError("Not a list!");
}
std::ostream &operator<<(std::ostream &os, Value &x) {
    os << x.toString();
    return os;
}
ValuePtr toValue(std::deque<ValuePtr> args) {
    if (args.size() == 0) return std::make_shared<NilValue>();
    ValuePtr car = args.front();
    args.pop_front();
    ValuePtr cdr= toValue(args);
    return std::make_shared<PairValue>(car, cdr);
}
