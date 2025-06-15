# CryptoEvaluator
C++ app that shows User's Portfolio and tracks market-cap and price trends to recommend cryptocurrency purchases.
There is a config.txt that lets you change the thresholds of the evaluators if you want to.
When user runs the program ,a menu is shown where it gives you several options to choose from.
First of all load the cryptocoins, if you havent loaded you will not be able to perform any task,
after youve Successfully loaded the coins, you can either searach for a coin(using symbol or name (capital or small) it does not really matter, the search is comepletely autonomous which i think is a nice small feeature i have added).

# Funds
You can also add or withdraw funds according to your needs. (Mind you! you cannot buy any crptocurrencies until you hvae the right amount of funds).

# Rcommendations

Once youve added funds you can either ask the program for its own recommendations!
You can buy the recommended coin or either you can buy a coin of your own choice its totally upto you!

# AutoInvest

If you want to buy the recommended coins, you can just select the program to AutoInvest! It will buy the coins according to your funds on its own.
Or you can buy the coin of your own choice.
You can also sell the coin (But you should own the coin and in the right quantity which you are about to sell otherwise you will be shown Error message).

# Triggers

The user also have the options to add triggers!
There are 4 kinds of triggers(Almost as many as there are in a professional application)
1-StopLoss Trigger (Sells a coin if threshold is higher than coin)
2-StopProfit Trigger (Sells a coin if it is higher than threshold)
3-BuyLow Trigger (Buys a coin if Threshold is higher than coin price)
4-BuyHIgh Trigger (Buys a coin if Coin Price is higher than threshold)
The triggers will keep track of the price of the coin and the threshold and execute accordingly.

One beautiful feature ive added is that when the triggers will be executed it only sells or buys the amount as (threshold-averagePrice) or (averagePrice-threshold) What this actually does is, it does not sells or buys the whole coin, it only sells the profit and keep the amount that was previously invested in the coin and vice versa for loss
# StateSaving

Once you are done with your investments you can save the state of the file in a Binary File!, Your cureent balance, all the holdings and all the transaction histories will be saved.

# StateLoading

When you re-run the program (After loading the coins!) you can reload the state of the program that you have saved in your binary file and all of your current balance and your holdings and transaction history will be restored!
