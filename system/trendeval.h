#ifndef TRENDEVAL_H
#define TRENDEVAL_H
#include<iostream>
#include"evaluator.h"
using namespace std;
class TrendEval: public Evaluator{
private:
    double minTrend;
public:
    TrendEval(): minTrend(0.0){}
    TrendEval(double mt):minTrend(mt){}
    TrendEval(const TrendEval& other):minTrend(other.minTrend){}
    ~TrendEval()override{}

    bool recommend(const cryptoCoin& cc)const override{
        if(cc.getTrend()>=minTrend){
            return true;
        }
        return false;
    }
    const String getEvaluatorName()const override{
        return "Trend Evaluator";
    }
};
#endif