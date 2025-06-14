//Remember one beautiful thing about program! For the triggers, if the trigger sells or buys
// it only sells or buys the amount as (threshold-averagePrice) or (averagePrice-threshold)
//What this actually does is, it does not sells or buys the whole coin, it only sells the profit and keep the
// amount that was previously invested in the coin and vice versa for loss
//This is beautiful

//default: \033[0m
//green : \033[32m
//red : \033[31m
//yellow : \033[33m

#include<iostream>
#include<stdexcept>
#include<exception>
#include"dynamic_template.h"
#include"portfoliomanager.h"
#include"apiloader.h"
#include"configreader.h"
#include"priceeval.h"
#include"marketeval.h"
#include"trendeval.h"
#include"riskeval.h"
#include"compositeeval.h"
#include"transaction.h"
#include"transactionhistory.h"
#include"buylowtrigger.h"
#include"buyhightrigger.h"
using namespace std;

int main() {
    try {
        APILoader loader;
        portfolioManager pm;
        Dynamic_array<cryptoCoin*> coins;
        
        // Variables for composite evaluator
        configReader reader;
        double _price, _market, _trend, _risk;
        PriceEval* pe = nullptr;
        MarketEval* me = nullptr;
        TrendEval* te = nullptr;
        RiskEval* re = nullptr;
        compositeEvaluator* ce = nullptr;
        
        int choice;
        bool coinsLoaded = false;
        cout << "=== Cryptocurrency Trading System ===" << endl;
        
        do {
            try {
                cout << "\n" << string(50, '=') << endl;
                cout << "         \033[36mCRYPTOCURRENCY TRADING MENU\033[0m" << endl;
                cout << string(50, '=') << endl;
                cout << "0.  Load and Display Cryptocurrency Data" << endl;
                cout << "1.  Search for details of a specific coin" << endl;
                cout << "2.  Test Composite Evaluator" << endl;
                cout << "3.  Deposit Funds" << endl;
                cout << "4.  Buy Cryptocurrencies" << endl;
                cout << "5.  Add Triggers" << endl;
                cout << "6.  Test Current Triggers" << endl;
                cout << "7.  Change Prices and Test Triggers" << endl;
                cout << "8.  Manual Sell Test" << endl;
                cout << "9.  Withdraw Funds" << endl;
                cout << "10. Display Final Portfolio" << endl;
                cout << "11. Exit" << endl;
                cout << "12. Save state to a Binary File" <<endl;
                cout << "13. Load state from a Previous BInary file \033[0m" <<endl;
                cout << string(50, '=') << endl;
                cout << "\033[1mEnter your choice: ";
                
                if (!(cin >> choice)) {
                    throw invalid_argument("\033[31mInvalid input. Please enter a number.\033[0m");
                }

                switch(choice) {
                    case 0:{
                        try {
                            // Load coins (mock data for now)
                            coins = loader.loadCoinsFromAPI();
                            
                            cout << "=== Loaded Cryptocurrency Data ===" << endl;
                            // Display all coin info
                            for (cryptoCoin* coin : coins) {
                                if (coin == nullptr) {
                                    throw runtime_error("\033[31mNull coin pointer encountered\033[0m");
                                }
                                coin->displayCoinInfo();
                            }
                            cout << "\n\033[32mAll coins displayed and memory cleaned up.\033[0m\n";
                            coinsLoaded = true;
                        }
                        catch (const exception& e) {
                            cout << "\033[31mError loading coins: \033[0m" << e.what() << endl;
                        }
                        break;
                    }
                        
                case 1:{
                    try {
                        String namecoin;
                        cout<<"Enter the name/symbol of the coin you want to search for: ";
                        cin.ignore();
                        cin>>namecoin;
                        cryptoCoin* result=loader.getcoinbyName(namecoin);
                        if(result){
                            cout<<"\n \033[32mCoin Found:\033[0m ";
                            result->displayCoinInfo();
                        }
                        else{
                            cout<<"\033[31mCoin Not Found!\033[0m"<<endl;
                        }
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError searching for coin: \033[0m" << e.what() << endl;
                    }
                    break;
                }
                    
                case 2:{
                    try {
                        if (!coinsLoaded) {
                            throw runtime_error("\033[31mPlease load coins first!\033[0m");
                        }
                        cout << endl << endl << "Add Evaluators and get Recommended Coins" << endl << endl;
                        
                        reader.load("config.txt");
                        _price = reader.getpriceThreshold();
                        _market = reader.getmarketcapThrehold();
                        _trend = reader.gettrendThreshold();
                        _risk = reader.getriskThreshold();
                        pe = new PriceEval(_price);
                        me = new MarketEval(_market);
                        te = new TrendEval(_trend);
                        re = new RiskEval(_risk);
                        ce = new compositeEvaluator();
                        
                        if (!pe || !me || !te || !re || !ce) {
                            throw bad_alloc();
                        }
                        
                        ce->addEvaluator(pe);
                        ce->addEvaluator(me);
                        ce->addEvaluator(te);
                        ce->addEvaluator(re);
                        cout << endl << "\033[32mEvaluators added\033[0m" << endl;
                        for(int i = 0; i < coins.size(); i++){
                            cryptoCoin* cn = coins[i];
                            if (cn == nullptr) {
                                throw runtime_error("\033[31mNull coin pointer in evaluation\033[0m");
                            }
                            if(ce->recommend(*cn)){
                                cout << "\033[32mRecommendation checked\033[0m" << endl;
                                cn->displayCoinInfo();
                            }
                        }
                    }
                    catch (const bad_alloc& e) {
                        cout << "\033[31mMemory allocation error: \033[0m" << e.what() << endl;
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError in composite evaluator: \033[0m" << e.what() << endl;
                    }
                    break;
                }
                    
                case 3:{
                    try {
                        double funds;
                        cout << "Enter the funds you want to add: $";
                        if (!(cin >> funds)) {
                            throw invalid_argument("\033[31mInvalid input for funds amount\033[0m");
                        }
                        if (funds < 0) {
                            throw invalid_argument("\033[31mFunds amount cannot be negative\033[0m");
                        }
                        pm.depositFunds(funds);
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError depositing funds: \033[0m" << e.what() << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    break;
                }
                    
               case 4:{
                try {
                    if (!coinsLoaded) {
                        throw runtime_error("\033[31mPlease load coins first!\033[0m");
                    }
                
                    Date buyDate;
                    buyDate.setToCurrentDate();
                    Time buyTime;
                    buyTime.setToCurrentTime();
                    char choice;

                    do {
                        try {
                            String CoinName;
                            double worth;
                        
                            cin.ignore(); 
                        
                            cout << "Please enter the name or symbol of the coin you want to buy: ";
                            cin >> CoinName;
                        
                            cout << "Please enter the worth you want to buy it for: $";
                            if (!(cin >> worth)) {
                                throw invalid_argument("\033[31mInvalid input for purchase amount\033[0m");
                            }
                            if (worth <= 0) {
                                throw invalid_argument("\033[31mPurchase amount must be positive\033[0m");
                            }
                        
                            cryptoCoin* selectedCoin = loader.getcoinbyName(CoinName);
                            if (selectedCoin) {
                                if (pm.BuyCoin(selectedCoin, worth, buyDate, buyTime)) {
                                    cout << "\033[32mCoin purchased successfully!\033[0m\n";
                                }
                            } else {
                                cout << "\033[31mCoin not found. Please check the name or symbol.\033[0m\n";
                            }
                        }
                        catch (const exception& e) {
                            cout << "\033[31mError in coin purchase: \033[0m" << e.what() << endl;
                            cin.clear();
                            cin.ignore(10000, '\n');
                        }
                        
                        cout << "Do you want to continue or exit? (c/C to continue, e/E to exit): ";
                        cin >> choice;
                    
                    } while (choice != 'e' && choice != 'E');
                
                    pm.displayPortfolio();
                }
                catch (const exception& e) {
                    cout << "\033[31mError in buying process: \033[0m" << e.what() << endl;
                }
                break;
            }
                case 5:{
                    try {
                        if (!coinsLoaded) {
                            throw runtime_error("\033[31mPlease load coins first!\033[0m");
                        }
                        
                        char triggerChoice;
                        int choiceNo=1;
                        do {
                            try {
                                cout << "Enter 1 if you want to add a \"StopLoss Trigger\""<<"(Sells a coin if threshold is higher than coin)" << endl;
                                cout << "Enter 2 if you want to add a \"StopProfit Trigger\""<<"(Sells a coin if it is higher than threshold)" << endl;
                                cout << "Enter 3 if you want to add a \"BuyLow Trigger\""<<"(Buys a coin if Threshold is higher than coin price)" <<endl;
                                cout << "Enter 4 if you want to add a \"BuyHIgh Trigger\""<<"(Buys a coin if Coin Price is higher than threshold)" <<endl; 
                                cout << "Enter e/E to exit "<<endl;
                                cin >> triggerChoice;
                                choiceNo++;
                                
                                if (triggerChoice != 'e' && triggerChoice != 'E') {
                                    String coin;
                                    double thresh;
                                    
                                    switch(triggerChoice) {
                                        case '1':
                                            cin.ignore();
                                            cout << "Enter the name of the coin on which you want to apply the StopLoss Trigger: ";
                                            cin >> coin;
                                            cout << "Enter the threshold at which you want to sell the coin: ";
                                            if (!(cin >> thresh)) {
                                                throw invalid_argument("\033[31mInvalid threshold value\033[0m");
                                            }
                                            if (thresh <= 0) {
                                                throw invalid_argument("\033[31mThreshold must be positive\033[0m");
                                            }
                                            {
                                                cryptoCoin* coinPtr = loader.getcoinbyName(coin);
                                                if (!coinPtr) {
                                                    throw runtime_error("\033[31mCoin not found for trigger\033[0m");
                                                }
                                                stoplossTrigger* trigger = new stoplossTrigger(coinPtr, thresh);
                                                if (!trigger) {
                                                    throw bad_alloc();
                                                }
                                                pm.addTrigger(trigger);
                                                cout << "\033[32mStopLoss Trigger added successfully!\033[0m" << endl;
                                            }
                                            break;
                                        case '2':
                                            cin.ignore();
                                            cout << "Enter the name of the coin on which you want to apply the StopProfit Trigger: ";
                                            cin >> coin;
                                            cout << "Enter the threshold at which you want to sell the coin: ";
                                            if (!(cin >> thresh)) {
                                                throw invalid_argument("\033[31mInvalid threshold value\033[0m");
                                            }
                                            if (thresh <= 0) {
                                                throw invalid_argument("Threshold must be positive");
                                            }
                                            {
                                                cryptoCoin* coinPtr = loader.getcoinbyName(coin);
                                                if (!coinPtr) {
                                                    throw runtime_error("\033[31mCoin not found for trigger\033[0m");
                                                }
                                                stopprofitTrigger* trigger = new stopprofitTrigger(coinPtr, thresh);
                                                if (!trigger) {
                                                    throw bad_alloc();
                                                }
                                                pm.addTrigger(trigger);
                                                cout << "\033[32mStopProfit Trigger added successfully!\033[0m" << endl;
                                            }
                                            break;
                                        case '3':
                                            cin.ignore();
                                            cout << "Enter the name of the coin on which you want to apply the BuyLow Trigger: ";
                                            cin >> coin;
                                            cout << "Enter the threshold at which you want to buy the coin: ";
                                            if (!(cin >> thresh)) {
                                                throw invalid_argument("\033[31mInvalid threshold value\033[0m");
                                            }
                                            if (thresh <= 0) {
                                                throw invalid_argument("\033[31mThreshold must be positive\033[0m");
                                            }
                                            {
                                                cryptoCoin* coinPtr = loader.getcoinbyName(coin);
                                                if (!coinPtr) {
                                                    throw runtime_error("\033[31mCoin not found for trigger\033[0m");
                                                }
                                                buylowTrigger* trigger = new buylowTrigger(coinPtr, thresh);
                                                if (!trigger) {
                                                    throw bad_alloc();
                                                }
                                                pm.addTrigger(trigger);
                                                cout << "\033[32mBuyLow Trigger added successfully!\033[0m" << endl;
                                            }
                                            break;
                                        case '4':
                                            cin.ignore();
                                            cout << "Enter the name of the coin on which you want to apply the BuyHigh Trigger: ";
                                            cin >> coin;
                                            cout << "Enter the threshold at which you want to buy the coin: ";
                                            if (!(cin >> thresh)) {
                                                throw invalid_argument("\033[31mInvalid threshold value\033[0m");
                                            }
                                            if (thresh <= 0) {
                                                throw invalid_argument("\033[31mThreshold must be positive\033[0m");
                                            }
                                            {
                                                cryptoCoin* coinPtr = loader.getcoinbyName(coin);
                                                if (!coinPtr) {
                                                    throw runtime_error("\033[31mCoin not found for trigger\033[0m");
                                                }
                                                buyhighTrigger* trigger = new buyhighTrigger(coinPtr, thresh);
                                                if (!trigger) {
                                                    throw bad_alloc();
                                                }
                                                pm.addTrigger(trigger);
                                                cout << "\033[32mBuyHigh Trigger added successfully!\033[0m" << endl;
                                            }
                                            break;
                                        default:
                                            cout << "\033[31mInvalid choice! Please enter 1, 2, 3, 4 or e/E.\033[0m" << endl;
                                            break;
                                    }
                                }
                            }
                            catch (const exception& e) {
                                cout << "\033[31mError adding trigger: \033[0m" << e.what() << endl;
                                cin.clear();
                                cin.ignore(10000, '\n');
                            }
                        } while (triggerChoice != 'e' && triggerChoice != 'E');
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError in trigger management: \033[0m" << e.what() << endl;
                    }
                    break;
                }
                case 6:{
                    try {
                        cout << "\nExecuting triggers..." << endl;
                        pm.triggerexecutiontoSell();
                        pm.triggerexecutiontoBuy();
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError executing triggers: \033[0m" << e.what() << endl;
                    }
                    break;
                }
                case 7:{
                    try {
                        if (!coinsLoaded) {
                            throw runtime_error("\033[31mPlease load coins first!\033[0m");
                        }
                        
                        {
                            double newBtcPrice = 44000.0;
                            cryptoCoin* btcCoin = loader.getcoinbyName("bitcoin");
                            if (!btcCoin) {
                                throw runtime_error("\033[31mBitcoin coin not found\033[0m");
                            }
                            btcCoin->setPrice(newBtcPrice);
                            
                            // Raise Ethereum price to trigger take-profit
                            double newEthPrice = 3600.0;
                            cryptoCoin* ethCoin = loader.getcoinbyName("ethereum");
                            if (!ethCoin) {
                                throw runtime_error("\033[31mEthereum coin not found\033[0m");
                            }
                            ethCoin->setPrice(newEthPrice);
                            
                            // Lower Dogecoin price to trigger stop-loss
                            double newDogePrice = 0.05;
                            cryptoCoin* dogeCoin = loader.getcoinbyName("dogecoin");
                            if (!dogeCoin) {
                                throw runtime_error("\033[31mDogecoin coin not found\033[0m");
                            }
                            dogeCoin->setPrice(newDogePrice);
                        }
                        
                        cout << "New prices:" << endl;
                        loader.getcoinbyName("bitcoin")->displayCoinInfo();
                        loader.getcoinbyName("ethereum")->displayCoinInfo();
                        loader.getcoinbyName("dogecoin")->displayCoinInfo();
                        
                        cout << "\nExecuting triggers with new prices..." << endl;
                        pm.triggerexecutiontoSell();
                        
                        pm.displayPortfolio();
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError changing prices and testing triggers: \033[0m" << e.what() << endl;
                    }
                    break;
                }
            case 8:{
                try {
                    if (!coinsLoaded) {
                        throw runtime_error("\033[31mPlease load coins first!\033[0m");
                    }
                
                    char choice;
                    do {
                        try {
                            String coin;
                            cin.ignore(); 
                            cout << "Enter the name of the coin you want to sell: ";
                            cin >> coin;
                        
                            double worth;
                            cout << "Enter the price/worth of coin you want to sell: ";
                            if (!(cin >> worth)) {
                                throw invalid_argument("\033[31mInvalid input for sell amount\033[0m");
                            }
                            if (worth <= 0) {
                                throw invalid_argument("\033[31mSell amount must be positive\033[0m");
                            }
                        
                            Date sellDate;
                            sellDate.setToCurrentDate();
                            Time sellTime;
                            sellTime.setToCurrentTime();
                        
                            cryptoCoin* coinPtr = loader.getcoinbyName(coin);
                            if (!coinPtr) {
                                throw runtime_error("\033[31mCoin not found\033[0m");
                            }
                            
                            if (pm.SellCoin(coinPtr, worth, sellDate, sellTime)) {
                                cout << "\033[32mCoin sold successfully!\033[0m" << endl;
                            } else {
                                cout << "\033[31mSell failed. Possibly insufficient holdings or invalid coin.\033[0m" << endl;
                            }
                        }
                        catch (const exception& e) {
                            cout << "\033[31mError in sell operation: \033[0m" << e.what() << endl;
                            cin.clear();
                            cin.ignore(10000, '\n');
                        }
                        
                        cout << "Do you want to continue or exit? (c/C to continue, e/E to exit): ";
                        cin >> choice;
                    
                    } while (choice != 'e' && choice != 'E');
                
                    pm.displayPortfolio();
                }
                catch (const exception& e) {
                    cout << "\033[31mError in manual sell process: \033[0m" << e.what() << endl;
                }
                break;
            }
                case 9:{
                    try {
                        double worth;
                        cout << "Enter the amount you want to withdraw: $";
                        if (!(cin >> worth)) {
                            throw invalid_argument("\033[31mInvalid input for withdrawal amount\033[0m");
                        }
                        if (worth < 0) {
                            throw invalid_argument("\033[31mWithdrawal amount cannot be negative\033[0m");
                        }
                        pm.withdrawFunds(worth);
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError withdrawing funds: \033[0m" << e.what() << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    break;
                }
                case 10:{
                    try {
                        // Final portfolio display
                        cout << "\nPortfolio State ---" << endl;
                        pm.displayPortfolio();
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError displaying portfolio: \033[0m" << e.what() << endl;
                    }
                    break;
                }
                case 11:{
                    try {
                        // Cleanup and exit
                        for (cryptoCoin* coin : coins) {
                            delete coin;
                        }
                        
                        // Clean up evaluators if they were created
                        if (pe) delete pe;
                        if (me) delete me;
                        if (te) delete te;
                        if (re) delete re;
                        if (ce) delete ce;
                        
                        cout << "\n\n\033[32m----Program Complete----\033[0m\n\n";
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError during cleanup: \033[0m" << e.what() << endl;
                    }
                    break;
                }
                case 12:{
                    try {
                        pm.saveToFile("SaveFile.bin");
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError saving to file: \033[0m" << e.what() << endl;
                    }
                    break;
                }
                case 13:{
                    try {
                        if(coinsLoaded==true){
                            pm.loadFromBinaryFile("SaveFile.bin",loader);
                        }
                        else{
                            throw runtime_error("\033[31mLoad Coins First!\033[0m");
                        }
                    }
                    catch (const exception& e) {
                        cout << "\033[31mError loading from file: \033[0m" << e.what() << endl;
                    }
                    break;
                }

                default:
                    cout << "\033[31mInvalid choice! Please select 0-13.\033[0m" << endl;
                    break;
            }
            }
            catch (const exception& e) {
                cout << "\033[31mMenu operation error: \033[0m" << e.what() << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            
        } while (choice != 11);
    }
    catch (const exception& e) {
        cout << "\033[31mCritical program error: \033[0m" << e.what() << endl;
        return 1;
    }
    catch (...) {
        cout << "\033[31mUnknown critical error occurred\033[0m" << endl;
        return 1;
    }
                
    return 0;
}