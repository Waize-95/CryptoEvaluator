#ifndef EVALUATOR_H
#define EVALUATOR_H
#include<iostream>
#include"Mystr.h"
#include"cryptocoin.h"
using namespace std;
class Evaluator{
public:
    virtual bool recommend(const cryptoCoin& cc)const=0;
    virtual const String getEvaluatorName()const=0;
    virtual ~Evaluator(){}
};
#endif //EVALUATOR_H