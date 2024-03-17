#ifndef FORMS_H
#define FORMS_H
#include<unordered_map>
#include"./value.h"
#include"./error.h"
#include "eval_env.h"
using SpecialFormType = ValuePtr(const std::vector<ValuePtr>&, EvalEnv&);
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr ifForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr andForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr orForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr lambdaForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr CondForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr LetForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr UnquoteForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr quasiquoteForm(const std::vector<ValuePtr>& args, EvalEnv& env);
extern std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS;
#endif
