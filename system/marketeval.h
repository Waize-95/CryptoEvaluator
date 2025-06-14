#ifndef MARKETEVALUATOR_H
#define MARKETEVALUATOR_H
#include<iostream>
#include"evaluator.h"
using namespace std;
class MarketEval: public Evaluator{
private:
    double minCap;
public:
    MarketEval(): minCap(0.0){}
    MarketEval(double mt):minCap(mt){}
    MarketEval(const MarketEval& other):minCap(other.minCap){}
    ~MarketEval()override{}

    bool recommend(const cryptoCoin& cc)const override{
        if(cc.getMarketCap()>=minCap){
            return true;
        }
        return false;
    }
    const String getEvaluatorName()const override{
        return "MarketCap Evaluator";
    }


};
#endif //MARKETEVALUATOR_H