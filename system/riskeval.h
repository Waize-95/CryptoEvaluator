#ifndef RISKEVALUATOR_H
#define RISKEVALUATOR_H
#include<iostream>
#include"evaluator.h"
using namespace std;
class RiskEval: public Evaluator{
private:
    double minRisk;
public:
    RiskEval(): minRisk(0.0){}
    RiskEval(double mt):minRisk(mt){}
    RiskEval(const RiskEval& other):minRisk(other.minRisk){}
    ~RiskEval()override{}

    bool recommend(const cryptoCoin& cc)const override{
        if(cc.getvolatility()<=minRisk){
            return true;
        }
        return false;
    }
    const String getEvaluatorName()const override{
        return "Volatility(Risk) Evaluator";
    }
};
#endif //RISKEVALUATOR_H