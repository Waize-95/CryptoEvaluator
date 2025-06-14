#ifndef STABLECOIN_H
#define STABLECOIN_H
#include<iostream>
#include"cryptocoin.h"
using namespace std;
class stableCoin: public cryptoCoin{
public:
    stableCoin():cryptoCoin(){}
    stableCoin(const String& _name,const String& _sym,double _price,double _marketcap,
    double _trend,double _volatility):cryptoCoin(_name,_sym,_price,_marketcap,_trend,_volatility){}
    stableCoin(const stableCoin& other):cryptoCoin(other){}
    ~stableCoin() override{}
    
    void displayCoinInfo() const override {
        cout << "[StableCoin] " << getname() << " (" << getSymbol() << "): $" << getPrice() <<" MarketCap: "<<
        getMarketCap()<<" Trend: "<<getTrend()<<" Volatility: "<<getvolatility()<<endl;
    }
    const String displayCoinSymbol()const override{
        return getSymbol();
    }
    friend ostream& operator<<(ostream& strm,const stableCoin& sc){
        strm<<"[StableCoin] " << sc.getname() << " (" << sc.getSymbol() << "): $" << sc.getPrice() <<" MarketCap: "<<
        sc.getMarketCap()<<" Trend: "<<sc.getTrend()<<" Volatility: "<<sc.getvolatility()<<endl;
        return strm;
    }
    friend istream& operator>>(istream& strm,stableCoin& sc){
        String _name,_sym;
        double _price,_marketcap,_trend,_volatility;
        cout<<"Enter the name,symbol,marketcap,trend and volatility of the stable coin: ";
        strm>>_name>>_sym>>_price>>_marketcap>>_trend>>_volatility;
        sc.setName(_name);
        sc.setMarketCap(_marketcap);
        sc.setSymbol(_sym);
        sc.setPrice(_price);
        sc.setVolatility(_volatility);
        sc.setTrend(_trend);
        return strm;
    }
};

#endif //STABLECOIN_H
