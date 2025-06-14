#ifndef ALTCOIN_H
#define ALTCOIN_H
#include<iostream>
#include"cryptocoin.h"
using namespace std;
class AltCoin: public cryptoCoin{
public:
    AltCoin():cryptoCoin(){}
    AltCoin(const String& _name,const String& _sym,double _price,double _marketcap,
    double _trend,double _volatility):cryptoCoin(_name,_sym,_price,_marketcap,_trend,_volatility){}
    AltCoin(const AltCoin& other):cryptoCoin(other){}
    ~AltCoin() override{}
    
    const String displayCoinSymbol()const override{
        return getSymbol();
    }
    void displayCoinInfo() const override {
        cout << "[AltCoin] " << getname() << " (" << getSymbol() << "): $" << getPrice() <<" MarketCap: "<<
        getMarketCap()<<" Trend: "<<getTrend()<<" Volatility: "<<getvolatility()<<endl;
    }
    friend ostream& operator<<(ostream& strm,const AltCoin& ac){
        strm<<"[AltCoin] " << ac.getname() << " (" << ac.getSymbol() << "): $" << ac.getPrice() <<" MarketCap: "<<
        ac.getMarketCap()<<" Trend: "<<ac.getTrend()<<" Volatility: "<<ac.getvolatility()<<endl;
        return strm;
    }
    friend istream& operator>>(istream& strm,AltCoin& ac){
        String _name,_sym;
        double _price,_marketcap,_trend,_volatility;
        cout<<"Enter the name,symbol,marketcap,trend and volatility of the altcoin: ";
        strm>>_name>>_sym>>_price>>_marketcap>>_trend>>_volatility;
        ac.setName(_name);
        ac.setMarketCap(_marketcap);
        ac.setSymbol(_sym);
        ac.setPrice(_price);
        ac.setVolatility(_volatility);
        ac.setTrend(_trend);
        return strm;
    }
};

#endif //ALTCOIN_H
