#ifndef BUILTINS_H
#define BUILTINS_H
#include<iostream>
#include<unordered_map>
#include<cmath>
#include"./value.h"
#include"./error.h"
class EvalEnv;

extern std::unordered_map<std::string, ValuePtr> Functions;
void Numberjudge(const std::vector<ValuePtr> &params);
// 用来判断是不是数字
void Paramsize(const std::vector<ValuePtr> &params, int num);
// 用来判断传入的参数个数是否合适
ValuePtr add(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr jian(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr sin_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr cos_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr sqrt_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr pow_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr mutiply(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr chu(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr abs_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr expt(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr quotient(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr modulo(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr remainder_(const std::vector<ValuePtr> &params, EvalEnv &env);
// 上面这些是数学函数
ValuePtr eq_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr equal_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr not_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr dengyu(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr dadengyu(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr xiaodengyu(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr even_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr odd_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr zero_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr bigger(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr smaller(const std::vector<ValuePtr> &params, EvalEnv &env);
// 上面这些是比较函数
ValuePtr append(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr map_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr filter_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr car(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr cdr(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr cons(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr length(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr list(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr reduce_(const std::vector<ValuePtr> &params, EvalEnv &env);
// 上面这些是对子操作函数
ValuePtr atom_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr bool_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr number_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr list_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr pair_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr null_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr string_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr symbol_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr procedure_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr integer_or_not(const std::vector<ValuePtr> &params, EvalEnv &env);
// 上面的是类型检查函数
ValuePtr print(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr display(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr displayln(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr exits(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr newline(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr apply(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr error_(const std::vector<ValuePtr> &params, EvalEnv &env);
ValuePtr eval(const std::vector<ValuePtr> &params, EvalEnv &env);
#endif
