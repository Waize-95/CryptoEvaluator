#ifndef COMPOSITEEVALUATOR_H
#define COMPOSITEEVALUATOR_H
#include<iostream>
#include<fstream>
#include"dynamic_template.h"
#include"evaluator.h"
#include"trendeval.h"
#include"marketeval.h"
#include"priceeval.h"
#include"riskeval.h"
#include"configreader.h"
using namespace std;
class compositeEvaluator:public Evaluator{
private:
    Dynamic_array<Evaluator*> evaluators;
    configReader Reader;
    double _price,_marketvalue,_trend,_risk;
public:
    compositeEvaluator():evaluators(){}
    compositeEvaluator(const Dynamic_array<Evaluator*>& _evaluators):evaluators(_evaluators){}
    compositeEvaluator(const compositeEvaluator& other):evaluators(other.evaluators){}
    ~compositeEvaluator() override{}

    void addEvaluator(Evaluator* ee){
        evaluators.push(ee);
    }
    void readThreshold(std::string filename){
        Reader.load(filename);
        _price=Reader.getpriceThreshold();
        _marketvalue=Reader.getmarketcapThrehold();
        _trend=Reader.gettrendThreshold();
        _risk=Reader.getriskThreshold();
    }
    bool recommend(const cryptoCoin& cc)const override{
        for(int i=0;i<evaluators.size();i++){
            Evaluator* eval=evaluators[i];
            // get all the evaluators, dont matter how many there are, store each 
            //evaluator (no matter what type) and run its recommend.
            if(!eval->recommend(cc)){
                return false;
            }
        }
        return true;
    }
    const String getEvaluatorName()const override{
        return "Composite Evaluator";
    }    
};
#endif //COMPOSITEEVALUATOR_H