#ifndef PRICEEVALUATOR_H
#define PRICEEVALUATOR_H
#include<iostream>
#include"evaluator.h"
using namespace std;
class PriceEval: public Evaluator{
private:
    double minPrice;
public:
    PriceEval(): minPrice(0.0){}
    PriceEval(double mt):minPrice(mt){}
    PriceEval(const PriceEval& other):minPrice(other.minPrice){}
    ~PriceEval()override{}

    bool recommend(const cryptoCoin& cc)const override{
        if(cc.getPrice()>=minPrice){
            return true;
        }
        return false;
    }
    const String getEvaluatorName()const override{
        return "Price Evaluator";
    }

};
#endif //PRICEEVALUATOR_H