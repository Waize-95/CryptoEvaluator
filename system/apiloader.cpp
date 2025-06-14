#include "apiloader.h"

// Helper to categorize based on symbol prefix or known types
cryptoCoin* APILoader::createCoinByCategory(const String& name, const String& symbol, double price,
                                            double marketCap, double trend, double volatility) {
    // Define known categories
    String symLower = symbol;
    symLower.ToLower(); // Assuming your MyStr String class supports toLower

    if (symbol == "BTC" || symbol == "SOL" || symbol == "ETH") {
        return new AltCoin(name, symbol, price, marketCap, trend, volatility);
    } else if (symbol == "SHIB" || symbol == "PEPE" || symbol == "DOGE") {
        return new memeCoin(name, symbol, price, marketCap, trend, volatility);
    } else if (symbol == "USDT" || symbol == "FSDT" || symbol == "USDC") {
        return new stableCoin(name, symbol, price, marketCap, trend, volatility);
    } else {
        // default to altcoin
        return new AltCoin(name, symbol, price, marketCap, trend, volatility);
    }
}

   

Dynamic_array<cryptoCoin*> coins;
Dynamic_array<cryptoCoin*> APILoader::loadCoinsFromAPI() {

    // In real-world, you'd fetch this from an API and parse JSON
    // For now, this is mock data
     for(int i = 0; i < coins.size(); i++) {
        delete coins[i];  // Delete the old coin objects
    }
    coins.clear();  // Clear the array
    coins.push(createCoinByCategory("Bitcoin", "BTC", 100000, 2.11e12, 0.0002, 0.01));
    coins.push(createCoinByCategory("Ethereum", "ETH", 2578.35, 3.11e11, 0.0060, 0.03));
    coins.push(createCoinByCategory("Tether", "USDT", 1.00, 1.55e11, 0.0000, 0.001));
    coins.push(createCoinByCategory("BNB", "BNB", 655, 9.2e10, -0.003, 0.02));
    coins.push(createCoinByCategory("Solana", "SOL", 148.4, 7.8e10, -0.027, 0.05));
    coins.push(createCoinByCategory("XRP", "XRP", 2.15, 1.26e11, -0.021, 0.04));
    coins.push(createCoinByCategory("USD Coin", "USDC", 1.00, 6.2e10, 0.0000, 0.001));
    coins.push(createCoinByCategory("Dogecoin", "DOGE", 0.180, 2.7e10, -0.011, 0.06));
    coins.push(createCoinByCategory("Cardano", "ADA", 0.641, 2.27e10, -0.034, 0.07));
    coins.push(createCoinByCategory("TRON", "TRX", 0.270, 2.56e10, -0.007, 0.05));
    coins.push(createCoinByCategory("Toncoin", "TON", 3.02, 7.47e9, -0.023, 0.06));
    coins.push(createCoinByCategory("Avalanche", "AVAX", 19.36, 8.16e9, -0.048, 0.08));
    coins.push(createCoinByCategory("Shiba Inu", "SHIB", 0.0000121, 7.13e9, -0.014, 0.12));
    coins.push(createCoinByCategory("Polkadot", "DOT", 3.84, 6.09e9, -0.023, 0.07));
    coins.push(createCoinByCategory("Litecoin", "LTC", 86.39, 6.56e9, -0.003, 0.05));
    coins.push(createCoinByCategory("Chainlink", "LINK", 13.42, 8.83e9, -0.043, 0.07));
    coins.push(createCoinByCategory("Internet Computer", "ICP", 5.51, 2.94e9, -0.053, 0.1));
    coins.push(createCoinByCategory("Uniswap", "UNI", 7.75, 4.87e9, 0.023, 0.07));
    coins.push(createCoinByCategory("Pepe", "PEPE", 0.0000112, 4.71e9, -0.030, 0.15));
    coins.push(createCoinByCategory("Dai", "DAI", 1.00, 5.38e9, 0.0011, 0.001));
    coins.push(createCoinByCategory("Aave", "AAVE", 290.6, 4.41e9, -0.014, 0.06));
    coins.push(createCoinByCategory("Render", "RNDR", 7.1, 2.1e9, 0.025, 0.09));
    coins.push(createCoinByCategory("Monero", "XMR", 317, 5.85e9, -0.008, 0.06));
    coins.push(createCoinByCategory("NEAR Protocol", "NEAR", 2.23, 2.74e9, -0.063, 0.1));
    coins.push(createCoinByCategory("VeChain", "VET", 0.035, 1.9e9, -0.021, 0.07));


    return coins;
}
cryptoCoin* APILoader:: getcoinbyName(const String& name)const{
    String q=name;
    for(int i=0;i<coins.size();i++){
        if((coins[i]->getname().ToLower()==q.ToLower())||(coins[i]->getSymbol().ToLower()==q.ToLower())){
            return coins[i];
        }
    }
    return nullptr;
}

