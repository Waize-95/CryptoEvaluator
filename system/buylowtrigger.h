#ifndef BUYLOWTRIGGER_H
#define BUYLOWTRIGGER_H
#include"triggers.h"
class buylowTrigger: public triggers{
public:
    buylowTrigger():triggers(){}
    buylowTrigger(cryptoCoin* _coin,double _price):triggers(_coin,_price){}
    buylowTrigger(const buylowTrigger& other):triggers(other){}
    ~buylowTrigger()override{}

    const String getTriggerType()const override{
        return "BuyLow Trigger";
    }
    bool checkTriggerCondition()const override{
        if(getTriggerPrice()>getTriggerCoin()->getPrice()){
            return true;
        }
        return false;
    }
    void executeTriggerInfo()override{
        cout<<"[BuyLow Trigger]: \""<<getTriggerCoin()->getSymbol()<<"\" bought at $"<<getTriggerCoin()->getPrice()<<
        " Threshold Price: "<<getTriggerPrice()<<"$"<<endl;
    }

    void saveToFile(std::string filename) override {
    ofstream outFile(filename, ios::binary | ios::app);  // Added ios::app
    if (!outFile) {
        cerr << "Error: Could not open file for saving trigger.\n";
        return;
    }
    
    // Save Trigger Type
    String triggerType = getTriggerType();
    int triggerTypeLen = triggerType.getlen();
    outFile.write(reinterpret_cast<const char*>(&triggerTypeLen), sizeof(triggerTypeLen));
    outFile.write(triggerType.c_str(), triggerTypeLen);
    
    // Save Coin Symbol
    String symbol = getTriggerCoin()->getSymbol();
    int symbolLen = symbol.getlen();
    outFile.write(reinterpret_cast<const char*>(&symbolLen), sizeof(symbolLen));
    outFile.write(symbol.c_str(), symbolLen);
    
    // Save Current Coin Price
    double currentPrice = getTriggerCoin()->getPrice();
    outFile.write(reinterpret_cast<const char*>(&currentPrice), sizeof(currentPrice));
    
    // Save Threshold Price
    double thresholdPrice = getTriggerPrice();
    outFile.write(reinterpret_cast<const char*>(&thresholdPrice), sizeof(thresholdPrice));
    
    outFile.close();  // Added explicit close
}
};
#endif //BUYLOWTRIGGER_H