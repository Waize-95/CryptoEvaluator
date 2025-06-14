#ifndef MEMECOIN_H
#define MEMECOIN_H
#include<iostream>
#include"cryptocoin.h"
using namespace std;
class memeCoin: public cryptoCoin{
public:
    memeCoin():cryptoCoin(){}
    memeCoin(const String& _name,const String& _sym,double _price,double _marketcap,
    double _trend,double _volatility):cryptoCoin(_name,_sym,_price,_marketcap,_trend,_volatility){}
    memeCoin(const memeCoin& other):cryptoCoin(other){}
    ~memeCoin() override{}
    
    void displayCoinInfo() const override {
        cout << "[memeCoin] " << getname() << " (" << getSymbol() << "): $" << getPrice() <<" MarketCap: "<<
        getMarketCap()<<" Trend: "<<getTrend()<<" Volatility: "<<getvolatility()<<endl;
    }
    const String displayCoinSymbol()const override{
        return getSymbol();
    }
    friend ostream& operator<<(ostream& strm,const memeCoin& mc){
        strm<<"[memeCoin] " << mc.getname() << " (" << mc.getSymbol() << "): $" << mc.getPrice() <<" MarketCap: "<<
        mc.getMarketCap()<<" Trend: "<<mc.getTrend()<<" Volatility: "<<mc.getvolatility()<<endl;
        return strm;
    }
    friend istream& operator>>(istream& strm,memeCoin& mc){
        String _name,_sym;
        double _price,_marketcap,_trend,_volatility;
        cout<<"Enter the name,symbol,marketcap,trend and volatility of the memecoin: ";
        strm>>_name>>_sym>>_price>>_marketcap>>_trend>>_volatility;
        mc.setName(_name);
        mc.setMarketCap(_marketcap);
        mc.setSymbol(_sym);
        mc.setPrice(_price);
        mc.setVolatility(_volatility);
        mc.setTrend(_trend);
        return strm;
    }
};

#endif //MEMECOIN_H
