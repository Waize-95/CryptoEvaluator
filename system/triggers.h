#ifndef TRIGGERS_H
#define TRIGGERS_H
#include"cryptocoin.h"
using namespace std;
class triggers{
private:
    cryptoCoin* coin;
    double thresholdprice;
public:
    triggers():coin(nullptr),thresholdprice(0.0){}
    triggers(cryptoCoin* _coin,double _price): coin(_coin),thresholdprice(_price){}
    triggers(const triggers& other):coin(other.coin),thresholdprice(other.thresholdprice){}
    virtual ~triggers()=default;

    virtual const String getTriggerType()const=0;
    virtual bool checkTriggerCondition()const =0;
    virtual void executeTriggerInfo()=0;

    cryptoCoin* getTriggerCoin()const{
        return coin;
    }
    double getTriggerPrice()const{
        return thresholdprice;
    }
    void setTriggerPrice(double _price){
        thresholdprice=_price;
    }
    void setTriggerCoin(cryptoCoin* _coin){
        coin=_coin;
    }
    virtual void saveToFile(std::string filename)=0;
};
#endif //TRIGGERS_H