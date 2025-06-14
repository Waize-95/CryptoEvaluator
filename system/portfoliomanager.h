//default: \033[0m
//green : \033[32m
//red : \033[31m
//yellow : \033[33m
//bold : \033[1m 



#ifndef PORTFOLIOMANAGER_H
#define PORTFOLIOMANAGER_H
#include"dynamic_template.h"
#include"balancemanager.h"
#include"holdingsmanager.h"
#include"Mystr.h"
#include"transactionhistory.h"
#include"triggers.h"
#include"stoplosstrigger.h"
#include"stopprofittrigger.h"
#include"buylowtrigger.h"
#include"buyhightrigger.h"
#include"cryptocoin.h"
#include"transaction.h"
#include"apiloader.h"
#include<fstream>
using namespace std;
class portfolioManager{
private:
    balanceManager bm;
    transactionHistory ts;
    holdingsManager hm;
    Dynamic_array<triggers*>tr;
public:
    portfolioManager():bm(),ts(),hm(),tr(){}
    portfolioManager(const balanceManager& _bm,const transactionHistory& _ts,
    const holdingsManager& _hm,Dynamic_array<triggers*>& _tr):bm(_bm),ts(_ts),hm(_hm),tr(_tr){}
    portfolioManager(const portfolioManager& other): bm(other.bm),ts(other.ts),hm(other.hm),tr(other.tr){}
    ~portfolioManager(){}

    void depositFunds(double amount){
        double oldamount;
        oldamount=bm.getBalance();
        bm.updateBalance(amount);
        cout<<"\033[32mDeposited \033[0m"<<amount<<"$"<<endl;
        cout<<"Balance updated from "<<oldamount<<"$ to "<<bm.getBalance()<<"$"<<endl;

    }
    double getFunds(){
        return bm.getBalance();
    }
    void withdrawFunds(double amount){
        if(bm.getBalance()<amount){
            cout<<"\033[31mNot Enough Balance!\033[0m";
            return;
        }
        double original=bm.getBalance();
        bm.reduceBalance(amount);
        cout<<"Balance reduced from "<<original<<"$ to "<<bm.getBalance()<<"$"<<endl;
    }
    bool BuyCoin(cryptoCoin* coin,double userprice,const Date& date,const Time& time){
        double coinprice=coin->getPrice();
        double quantity=userprice/coinprice;
        if(bm.getBalance()<userprice){
            cout<<"\033[31mInsufficient Balance! \033[0m"<<endl;
            return false;
        }
        bm.reduceBalance(userprice);
        hm.updateholdingsinmanager(coin,quantity,coinprice);
        transaction t(coin,coin->getSymbol(),"\033[32mBUY\033[0m",quantity,userprice,date,time);
        ts.addTransaction(t);
        cout<<"\033[32mTransaction Done!\033[0m"<<endl;
        cout<<"\""<<coin->getSymbol()<<"\" Bought! Amount: "<<quantity<<" For "<<userprice<<"$"<<endl;
        return true;
    }
    bool SellCoin(cryptoCoin* coin,double userprice,const Date& date,const Time& time){
        double coinprice=coin->getPrice();
        double quantity=userprice/coinprice;
        if(hm.CheckCoinAvailabilityAndQuantity(coin,quantity)==false){
            cout<<"\033[31mNot enough coin Quantity Available!\033[0m"<<endl;
            return false;
        }
        bm.updateBalance(userprice);
        hm.reduceholding(coin,quantity);
        transaction t(coin,coin->getSymbol(),"\033[31mSELL\033[0m",quantity,userprice,date,time);
        ts.addTransaction(t);
        cout<<"\033[32mTransaction Done!\033[0m"<<endl;
        cout<<"\""<<coin->getSymbol()<<"\""<<" Sold! Amount: "<<quantity<<" For "<<userprice<<"$"<<endl;
        return true;
    }
    void addTrigger(triggers* trigger){
        tr.push(trigger);
        cout<<"\033[32mAdded Trigger: \033[0m"<<trigger->getTriggerType()<<endl;
    }
    // void triggerexecution(){
    //     for(int i=0;i<tr.size();i++){
    //         // we first check the triggers condition  (if the coin price has reached the threshold)
    //         if(tr[i]->checkTriggerCondition()){
    //             //if it is true we check if that coin is available to user and in enough quantity as which
    //             // the trigger is set. This function requires the paramters of (coin,amount).
    //             // we get the coin which has been triggered and get its quantity with the 
    //             //function checkholdingquantitybycoin which requires paramters(coin)
    //             Date date(12,4,2025);
    //             Time time(14,44,34);
    //             if(hm.CheckCoinAvailabilityAndQuantity(tr[i]->getTriggerCoin(),
    //                hm.CheckHoldingQuantityByCoin(tr[i]->getTriggerCoin()))){
    //             //if it is true we proceed.
    //                 SellCoin(tr[i]->getTriggerCoin(),tr[i]->getTriggerPrice(),
    //                 date,time);
    //                 cout<<"Trigger Executed!"<<endl;
    //                 tr[i]->executeTriggerInfo();
    //             }
    //         }
    //     }
    // }
    void triggerexecutiontoSell(){
    Date currentDate(12, 6, 2025);
    Time currentTime(12, 0, 0);
    
    for(int i = 0; i < tr.size(); i++){
        if(tr[i]->checkTriggerCondition()){
            double availableQuantity = hm.CheckHoldingQuantityByCoin(tr[i]->getTriggerCoin());
            if(availableQuantity > 0){
                // Sell at current market price, not trigger price
                double currentPrice = tr[i]->getTriggerCoin()->getPrice();
                double sellValue = availableQuantity * currentPrice;
                
                SellCoin(tr[i]->getTriggerCoin(), sellValue, currentDate, currentTime);
                cout<<"\033[32m-----Trigger Executed!-----\033[0m";
                tr[i]->executeTriggerInfo();
                
            }
        }
    }
}
void triggerexecutiontoBuy(){
    Date currentDate(12, 6, 2025);
    Time currentTime(12, 0, 0);
    
    for(int i = 0; i < tr.size(); i++){
        cryptoCoin* coin=tr[i]->getTriggerCoin();
        double currentvalue=coin->getPrice();
        double desiredvalue=tr[i]->getTriggerPrice();
        if(bm.getBalance()>=desiredvalue){
                BuyCoin(coin,desiredvalue,currentDate,currentTime);
                cout<<"\033[32m-----Trigger Executed!-----\033[0m";
                tr[i]->executeTriggerInfo();
                
        }
    }
}
    void displayPortfolio() const {
        cout << endl<<"==== Portfolio Summary ===="<<endl;
        cout << "\033[32mAvailable Balance\033[0m: $" << bm.getBalance() << endl;
        hm.displayAllHoldings();
        cout << "\n==== Transaction History ====\n";
        ts.displayAllTransactions();
    }
    void saveToFile(std::string filename) const {
    ofstream out(filename, ios::binary);
    if (!out) {
        cerr << "\033[31mCouldn't create binary file\033[0m" << endl;
        return;
    }
    
    double balance = bm.getBalance();
    out.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
    out.close(); 
    ts.saveToFile(filename);    // Will append
    hm.saveToFile(filename);    // Will append
    
    ofstream out2(filename, ios::binary | ios::app);
    if (!out2) {
        cerr << "\033[31mCouldn't reopen file for trigger data\033[0m" << endl;
        return;
    }
    
    int triggercount = tr.size();
    out2.write(reinterpret_cast<const char*>(&triggercount), sizeof(triggercount));
    out2.close();
    
    // Triggers append their data
    for(auto& t : tr) {
        t->saveToFile(filename);
    }
    
    cout << "\033[32mState Saved in a Binary File!\033[0m" << endl;
}


void loadFromBinaryFile(std::string filename, const APILoader& loader) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cerr << "\033[31mCouldn't open binary file for reading\033[0m" << endl;
        return;
    }
    
    // Clear existing data
    tr.clear();  // Assuming Dynamic_array has a clear method
    
    // Read balance
    double balance;
    in.read(reinterpret_cast<char*>(&balance), sizeof(balance));
    bm.setBalance(balance);
    
    // Read transaction history
    int transactionCount;
    in.read(reinterpret_cast<char*>(&transactionCount), sizeof(transactionCount));
    
    for (int i = 0; i < transactionCount; i++) {
        // Read symbol
        int symbolLen;
        in.read(reinterpret_cast<char*>(&symbolLen), sizeof(symbolLen));
        char* symbolBuffer = new char[symbolLen + 1];
        in.read(symbolBuffer, symbolLen);
        symbolBuffer[symbolLen] = '\0';
        String symbol(symbolBuffer);
        delete[] symbolBuffer;
        
        // Read type
        int typeLen;
        in.read(reinterpret_cast<char*>(&typeLen), sizeof(typeLen));
        char* typeBuffer = new char[typeLen + 1];
        in.read(typeBuffer, typeLen);
        typeBuffer[typeLen] = '\0';
        String type(typeBuffer);
        delete[] typeBuffer;
        
        // Read quantity and price
        double quantity, price;
        in.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
        in.read(reinterpret_cast<char*>(&price), sizeof(price));
        
        // Read date and time
        Date date;
        Time time;
        in.read(reinterpret_cast<char*>(&date), sizeof(date));
        in.read(reinterpret_cast<char*>(&time), sizeof(time));
        
        // Create transaction using loader to find coin
        cryptoCoin* coin = loader.getcoinbyName(symbol);
        transaction t(coin, symbol, type, quantity, price, date, time);
        ts.addTransaction(t);
    }
    
    // Read holdings
    int holdingsCount;
    in.read(reinterpret_cast<char*>(&holdingsCount), sizeof(holdingsCount));
    
    for (int i = 0; i < holdingsCount; i++) {
        // Read coin name length and name
        int nameLen;
        in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        char* nameBuffer = new char[nameLen + 1];
        in.read(nameBuffer, nameLen);
        nameBuffer[nameLen] = '\0';
        String coinName(nameBuffer);
        delete[] nameBuffer;
        
        // Read quantity and price
        double quantity, price;
        in.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
        in.read(reinterpret_cast<char*>(&price), sizeof(price));
        
        // Create holding using loader to find coin
        cryptoCoin* coin = loader.getcoinbyName(coinName);
        if (coin) {
            holdings h(coin, quantity, price);
            hm.addToHoldings(h);
        }
    }
    
    // Read triggers
    int triggerCount;
    in.read(reinterpret_cast<char*>(&triggerCount), sizeof(triggerCount));
    
    for (int i = 0; i < triggerCount; i++) {
        // Read trigger type
        int triggerTypeLen;
        in.read(reinterpret_cast<char*>(&triggerTypeLen), sizeof(triggerTypeLen));
        char* triggerTypeBuffer = new char[triggerTypeLen + 1];
        in.read(triggerTypeBuffer, triggerTypeLen);
        triggerTypeBuffer[triggerTypeLen] = '\0';
        String triggerType(triggerTypeBuffer);
        delete[] triggerTypeBuffer;
        
        // Read coin symbol
        int symbolLen;
        in.read(reinterpret_cast<char*>(&symbolLen), sizeof(symbolLen));
        char* symbolBuffer = new char[symbolLen + 1];
        in.read(symbolBuffer, symbolLen);
        symbolBuffer[symbolLen] = '\0';
        String symbol(symbolBuffer);
        delete[] symbolBuffer;
        
        // Read current price and threshold price
        double currentPrice, thresholdPrice;
        in.read(reinterpret_cast<char*>(&currentPrice), sizeof(currentPrice));
        in.read(reinterpret_cast<char*>(&thresholdPrice), sizeof(thresholdPrice));
        
        // Create appropriate trigger based on type using loader
        cryptoCoin* coin = loader.getcoinbyName(symbol);
        triggers* trigger = nullptr;
        
        if (coin) {
            if (triggerType == "StopLoss Trigger") {
                trigger = new stoplossTrigger(coin, thresholdPrice);
            }
            else if (triggerType == "StopProfit Trigger") {
                trigger = new stopprofitTrigger(coin, thresholdPrice);
            }
            else if (triggerType == "BuyLoss Trigger") {
                trigger = new buylowTrigger(coin, thresholdPrice);
            }
            else if (triggerType == "BuyProfit Trigger") {
                trigger = new buyhighTrigger(coin, thresholdPrice);
            }
            
            if (trigger) {
                tr.push(trigger);
            }
        }
    }
    
    cout << "\033[32mState loaded from binary file successfully!\033[0m" << endl;
}


};
#endif //PORTFOLIOMANAGER_H