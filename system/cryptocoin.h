#ifndef CRYPTOCOIN_H
#define CRYPTOCOIN_H
#include<iostream>
#include"dynamic_template.h"
#include"Mystr.h"
using namespace std;
class cryptoCoin{
private:
    String name;
    String symbol;
    double price;
    double marketcap;
    double trend;
    double volatility;
public:
    cryptoCoin():name("Unknown"),symbol("Unknown"),price(0.0),marketcap(0.0),trend(0.0),volatility(0.0){}
    cryptoCoin(const String& _name,const String& _sym,double _price,double _marketcap,double _trend,double _volatility):
    name(_name),symbol(_sym),price(_price),marketcap(_marketcap),trend(_trend),volatility(_volatility){}
    cryptoCoin(const cryptoCoin& other):name(other.name),symbol(other.symbol),price(other.price),marketcap
    (other.marketcap),trend(other.trend),volatility(other.volatility){}
    virtual ~cryptoCoin()=default;

    String getname()const{return name;}
    String getSymbol()const{return symbol;}
    double getPrice()const{return price;}
    double getMarketCap()const{return marketcap;}
    double getTrend()const{return trend;}
    double getvolatility()const{return volatility;}

    void setName(const String& _name){this->name=_name;}
    void setSymbol(const String& _symbol){this->symbol=_symbol;}
    void setPrice(double _price){this->price=_price;}
    void setMarketCap(double _marketcap){this->marketcap=_marketcap;}
    void setTrend(double _trend){this->trend=_trend;}
    void setVolatility(double _volatility){this->volatility=_volatility;}

    virtual void displayCoinInfo()const =0;
    virtual const String displayCoinSymbol()const=0;
    

};
#endif //CRYPTOCOIN_H