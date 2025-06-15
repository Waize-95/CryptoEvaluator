#ifndef APILOADER_H
#define APILOADER_H
using namespace std;
#include "dynamic_template.h"
#include "cryptocoin.h"
#include "altcoin.h"
#include "memecoin.h"
#include "stablecoin.h"

class APILoader {
public:
    // Loads coins from API (mock for now)
    Dynamic_array<cryptoCoin*> loadCoinsFromAPI();

    // Utility: categorize based on symbol or name
    cryptoCoin* createCoinByCategory(const String& name, const String& symbol, double price,
                                     double marketCap, double trend, double volatility);
    void updatePricesWithVolatility();

    cryptoCoin* getcoinbyName(const String& name)const;
};

#endif // APILOADER_H
