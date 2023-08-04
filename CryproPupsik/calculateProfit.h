/*# **************************************************************************
# *                                                                        *
# * Copyright 2023 ZADOYA Maksym Alexandrovich                             *
# *                                                                        *
# * Licensed under the Apache License, Version 2.0 (the "License");        *
# * you may not use this file except in compliance with the License.       *
# * You may obtain a copy of the License at                                *
# *                                                                        *
# *     https://github.com/Zad0ya/CPER/blob/master/LICENSE                 *
# *                                                                        *
# * Unless required by applicable law or agreed to in writing, software    *
# * distributed under the License is distributed on an "AS IS" BASIS,      *
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
# * See the License for the specific language governing permissions and   *
# * limitations under the License.                                        *
# *                                                                        *
# **************************************************************************
*/

struct CurrencyPair {
    std::string exchange;
    std::string pair;
    std::string pairfrom;
    std::string pairto;
    int from;
    int to;
    double buyPrice;
    double sellPrice;
    double profitPercentage;
    double profitAmount;
};

/*double calculateProfit(double buyPrice, double sellPrice, int tradeSum, double buyFeePercentage, double sellFeePercentage) {
    double buyAmount = tradeSum;

    double buyFee = buyAmount * buyFeePercentage;
    double buyTotal = buyAmount + buyFee;
    double coinsBought = buyTotal / buyPrice;

    double sellTotal = coinsBought * sellPrice;
    double sellFee = sellTotal * sellFeePercentage;
    sellTotal -= sellFee;

    return sellTotal - buyTotal;
}
*/

double calculateProfit(double buyPrice, double sellPrice, int tradeSum, double buyFeePercentage, double sellFeePercentage) {

    double buyAmount = tradeSum / buyPrice;
    double buyFee = buyAmount * buyFeePercentage;
    double buyTotal = buyAmount - buyFee;

    double sellTotal = buyAmount * sellPrice;
    double sellFee = sellTotal * sellFeePercentage;
    sellTotal -= sellFee;

    return sellTotal - tradeSum;
}


// Функция для расчета процента прибыли
double calculateProfitPercentage(double buyPrice, double sellPrice, int tradeSum, double buyFeePercentage, double sellFeePercentage) {
    double profit = calculateProfit(buyPrice, sellPrice, tradeSum, buyFeePercentage, sellFeePercentage);
    double profitPercentage = (profit / (tradeSum + profit)) * 100.0;
    return profitPercentage;
}

// Функция для расчета суммы прибыли в деньгах
double calculateProfitAmount(double buyPrice, double profitPercentage) {
    double profitAmount = (buyPrice * profitPercentage) / 100.0;
    return profitAmount;
}


void calculateFinalProfitWorker(const std::vector<std::string>& currencyPairsWithSlashToUSDT,
    std::vector<ExchangeRate> currencyListBinanceToUSDT,
std::vector<ExchangeRate> currencyListHuobiToUSDT,
std::vector<ExchangeRate> currencyListKukoinToUSDT,
std::vector<ExchangeRate> currencyListBitMartToUSDT,
std::vector<ExchangeRate> currencyListKrakenToUSDT,
std::vector<ExchangeRate> currencyListByBitToUSDT, sf::Font& font, float scrollOffset, bool& isUpdaterBesetz, bool& isCalculationReady, std::vector<CurrencyPair>& pairs, bool& isReadyForNewUpdate, bool& isAllReady_ReadyForCleaning, sf::Sound& updating,
    int tradeSum, bool& isCurrencyCalculated, double comissionBinance, double comissionHuobi, double comissionKukoin, double comissionBitmart, double comissionKraken, double comissionByBit, std::vector<std::string> currencyPairsToUSDT, std::vector<std::string> currencyPairsWithoutSpaceToUSDT, std::vector<std::string> currencyPairsWithUnterToUSDT,  std::vector<std::string> currencyGetMarket,
        std::vector<std::string>& currencyPairsSmallToUSDT, sf::Clock& AutoupdateTimer, std::vector<ExchangeRate> currencyListBinanceToBUSD){

    if (currencyPairsWithSlashToUSDT.empty() || currencyListBinanceToUSDT.empty() || currencyListHuobiToUSDT.empty() ||
        currencyListKukoinToUSDT.empty() || currencyListBitMartToUSDT.empty() || currencyListKrakenToUSDT.empty() ||
        currencyListByBitToUSDT.empty()) {
        std::cout << "Error: Missing data in one or more lists." << std::endl;
        return;
    }
    isCalculationReady = false;
    CurrencyPair pair;
    for (size_t i = 0; i < currencyPairsWithSlashToUSDT.size(); i++) {
        double maxProfitPercentage = std::numeric_limits<double>::lowest();
        std::string maxExchange;

        // Binance
        if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].ask != 0) {
            double buyPrice = currencyListBinanceToUSDT[i].ask;

            // Binance <-> Huobi
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].ask != 0 &&
                currencyListHuobiToUSDT.size() > i && currencyListHuobiToUSDT[i].bid != 0) {
                double buyPrice = currencyListBinanceToUSDT[i].ask;
                double sellPrice = currencyListHuobiToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionHuobi);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;

                    maxExchange = "Binance <-> Huobi";

       
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsSmallToUSDT[i];
                    pair.buyPrice = currencyListBinanceToUSDT[i].ask;
                    pair.sellPrice = currencyListHuobiToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionHuobi);
                    pair.from = 1;
                    pair.to = 2;
                    pairs.push_back(pair);
                }
            }

            // Binance <-> Kukoin
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].ask != 0 &&
                currencyListKukoinToUSDT.size() > i && currencyListKukoinToUSDT[i].bid != 0) {
                double buyPrice = currencyListBinanceToUSDT[i].ask;
                double sellPrice = currencyListKukoinToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionKukoin);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance <-> Kukoin";
                   
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsToUSDT[i];
                    pair.buyPrice = currencyListBinanceToUSDT[i].ask;
                    pair.sellPrice = currencyListKukoinToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionKukoin);
                    pair.from = 1;
                    pair.to = 3;
                    pairs.push_back(pair);
                }
            }

            // Binance <-> BitMart
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].ask != 0 &&
                currencyListBitMartToUSDT.size() > i && currencyListBitMartToUSDT[i].bid != 0) {
                double buyPrice = currencyListBinanceToUSDT[i].ask;
                double sellPrice = currencyListBitMartToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionBitmart);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance <-> BitMart";
                  
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithUnterToUSDT[i];
                    pair.buyPrice = currencyListBinanceToUSDT[i].ask;
                    pair.sellPrice = currencyListBitMartToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionBitmart);
                    pair.from = 1;
                    pair.to = 4;
                    pairs.push_back(pair);
                }
            }

            // Binance <-> Kraken
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].ask != 0 &&
                currencyListKrakenToUSDT.size() > i && currencyListKrakenToUSDT[i].bid != 0) {
                double buyPrice = currencyListBinanceToUSDT[i].ask;
                double sellPrice = currencyListKrakenToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionKraken);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance <-> Kraken";
                  
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListBinanceToUSDT[i].ask;
                    pair.sellPrice = currencyListKrakenToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionKraken);
                    pair.from = 1;
                    pair.to = 5;
                    pairs.push_back(pair);
                }
            }

            // Binance <-> OKX
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].ask != 0 &&
                currencyListByBitToUSDT.size() > i && currencyListByBitToUSDT[i].bid != 0) {
                double buyPrice = currencyListBinanceToUSDT[i].ask;
                double sellPrice = currencyListByBitToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionByBit);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance <-> ByBit";
              
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListBinanceToUSDT[i].ask;
                    pair.sellPrice = currencyListByBitToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionByBit);
                    pair.from = 1;
                    pair.to = 6;
                    pairs.push_back(pair);
                }
            }
            
        }

        if (currencyListHuobiToUSDT.size() > i && currencyListHuobiToUSDT[i].ask != 0) {
            double buyPrice = currencyListHuobiToUSDT[i].ask;

            // Huobi <-> Binance
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].ask != 0) {
                double sellPrice = currencyListBinanceToUSDT[i].ask;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionBinance);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Huobi <-> Binance";
                 
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsSmallToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListHuobiToUSDT[i].ask;
                    pair.sellPrice = currencyListBinanceToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionBinance);
                    pair.from = 2;
                    pair.to = 1;
                    pairs.push_back(pair);
                }
            }

            // Huobi <-> Kukoin
            if (currencyListKukoinToUSDT.size() > i && currencyListKukoinToUSDT[i].ask != 0) {
                double sellPrice = currencyListKukoinToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionKukoin);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Huobi <-> Kukoin";
              
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsSmallToUSDT[i];
                    pair.pairto = currencyPairsToUSDT[i];
                    pair.buyPrice = currencyListHuobiToUSDT[i].ask;
                    pair.sellPrice = currencyListKukoinToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionKukoin);
                    pair.from = 2;
                    pair.to = 3;
                    pairs.push_back(pair);
                }
            }

            // Huobi <-> BitMart
            if (currencyListBitMartToUSDT.size() > i && currencyListBitMartToUSDT[i].bid != 0) {
                double sellPrice = currencyListBitMartToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionBitmart);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Huobi <-> BitMart";
                   
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsSmallToUSDT[i];
                    pair.pairto = currencyPairsWithUnterToUSDT[i];
                    pair.buyPrice = currencyListHuobiToUSDT[i].ask;
                    pair.sellPrice = currencyListBitMartToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionBitmart);
                    pair.from = 2;
                    pair.to = 4;
                    pairs.push_back(pair);
                }
            }

            // Huobi <-> Kraken
            if (currencyListKrakenToUSDT.size() > i && currencyListKrakenToUSDT[i].bid != 0) {
                double sellPrice = currencyListKrakenToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionKraken);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Huobi <-> Kraken";
               
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsSmallToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListHuobiToUSDT[i].ask;
                    pair.sellPrice = currencyListKrakenToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionKraken);
                    pair.from = 2;
                    pair.to = 5;
                    pairs.push_back(pair);
                }
            }

            // Huobi <-> OKX
            if (currencyListByBitToUSDT.size() > i && currencyListByBitToUSDT[i].bid != 0) {
                double sellPrice = currencyListByBitToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionByBit);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Huobi <-> ByBit";
                    
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsSmallToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListHuobiToUSDT[i].ask;
                    pair.sellPrice = currencyListByBitToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionHuobi, comissionByBit);
                    pair.from = 2;
                    pair.to = 6;
                    pairs.push_back(pair);
                }
            }
        }

        if (currencyListKukoinToUSDT.size() > i && currencyListKukoinToUSDT[i].ask != 0) {
            double buyPrice = currencyListKukoinToUSDT[i].ask;

            // Kukoin <-> Binance
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].bid != 0) {
                double sellPrice = currencyListBinanceToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionBinance);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kukoin <-> Binance";
                
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListKukoinToUSDT[i].ask;
                    pair.sellPrice = currencyListBinanceToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionBinance);
                    pair.from = 3;
                    pair.to = 1;
                    pairs.push_back(pair);
                }
            }

            // Kukoin <-> Huobi
            if (currencyListHuobiToUSDT.size() > i && currencyListHuobiToUSDT[i].bid != 0) {
                double sellPrice = currencyListHuobiToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionHuobi);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kukoin <-> Huobi";
                   
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsToUSDT[i];
                    pair.pairto = currencyPairsSmallToUSDT[i];
                    pair.buyPrice = currencyListKukoinToUSDT[i].ask;
                    pair.sellPrice = currencyListHuobiToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionHuobi);
                    pair.from = 3;
                    pair.to = 2;
                    pairs.push_back(pair);
                }
            }

            // Kukoin <-> BitMart
            if (currencyListBitMartToUSDT.size() > i && currencyListBitMartToUSDT[i].bid != 0) {
                double sellPrice = currencyListBitMartToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionBitmart);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kukoin <-> BitMart";
                
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsToUSDT[i];
                    pair.pairto = currencyPairsWithUnterToUSDT[i];
                    pair.buyPrice = currencyListKukoinToUSDT[i].ask;
                    pair.sellPrice = currencyListBitMartToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionBitmart);
                    pair.from = 3;
                    pair.to = 4;
                    pairs.push_back(pair);
                }
            }

            // Kukoin <-> Kraken
            if (currencyListKrakenToUSDT.size() > i && currencyListKrakenToUSDT[i].bid != 0) {
                double sellPrice = currencyListKrakenToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionKraken);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kukoin <-> Kraken";
              
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListKukoinToUSDT[i].ask;
                    pair.sellPrice = currencyListKrakenToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionKraken);
                    pair.from = 3;
                    pair.to = 5;
                    pairs.push_back(pair);
                }
            }

            // Kukoin <-> OKX
            if (currencyListByBitToUSDT.size() > i && currencyListByBitToUSDT[i].bid != 0) {
                double sellPrice = currencyListByBitToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionByBit);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kukoin <-> ByBit";
              
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListKukoinToUSDT[i].ask;
                    pair.sellPrice = currencyListByBitToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKukoin, comissionByBit);
                    pair.from = 3; 
                    pair.to = 6;
                    pairs.push_back(pair);
                }
            }
        }

        if (currencyListBitMartToUSDT.size() > i && currencyListBitMartToUSDT[i].ask != 0) {
            double buyPrice = currencyListBitMartToUSDT[i].ask;

            //  BitMart <-> Binance
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].bid != 0) {
                double sellPrice = currencyListBinanceToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionBinance);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "BitMart <-> Binance";
                  
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithUnterToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListBitMartToUSDT[i].ask;
                    pair.sellPrice = currencyListBinanceToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionBinance);
                    pair.from = 4;
                    pair.to = 1;
                    pairs.push_back(pair);
                }
            }

            // BitMart <-> Huobi
            if (currencyListHuobiToUSDT.size() > i && currencyListHuobiToUSDT[i].bid != 0) {
                double sellPrice = currencyListHuobiToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionHuobi);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "BitMart <-> Huobi";
                   
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithUnterToUSDT[i];
                    pair.pairto = currencyPairsSmallToUSDT[i];
                    pair.buyPrice = currencyListBitMartToUSDT[i].ask;
                    pair.sellPrice = currencyListHuobiToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionHuobi);
                    pair.from = 4;
                    pair.to = 2;
                    pairs.push_back(pair);
                }
            }

            // BitMart <-> Kukoin
            if (currencyListKukoinToUSDT.size() > i && currencyListKukoinToUSDT[i].bid != 0) {
                double sellPrice = currencyListKukoinToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionKukoin);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "BitMart <-> Kukoin";
                
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithUnterToUSDT[i];
                    pair.pairto = currencyPairsToUSDT[i];
                    pair.buyPrice = currencyListBitMartToUSDT[i].ask;
                    pair.sellPrice = currencyListKukoinToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionKukoin);
                    pair.from = 4;
                    pair.to = 3;
                    pairs.push_back(pair);
                }
            }

            // BitMart <-> Kraken
            if (currencyListKrakenToUSDT.size() > i && currencyListKrakenToUSDT[i].bid != 0) {
                double sellPrice = currencyListKrakenToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionBitmart);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "BitMart <-> Kraken";
                   
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithUnterToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListBitMartToUSDT[i].ask;
                    pair.sellPrice = currencyListKrakenToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionBitmart);
                    pair.from = 4;
                    pair.to = 5;
                    pairs.push_back(pair);
                }
            }

            // BitMart <-> OKX
            if (currencyListByBitToUSDT.size() > i && currencyListByBitToUSDT[i].bid != 0) {
                double sellPrice = currencyListByBitToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionByBit);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "BitMart <-> ByBit";
               
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithUnterToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListBitMartToUSDT[i].ask;
                    pair.sellPrice = currencyListByBitToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBitmart, comissionByBit);
                    pair.from = 4;
                    pair.to = 6;
                    pairs.push_back(pair);
                }
            }
        }

        if (currencyListKrakenToUSDT.size() > i && currencyListKrakenToUSDT[i].ask != 0) {
            double buyPrice = currencyListKrakenToUSDT[i].ask;

            // Kraken <-> Binance
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].bid != 0) {
                double sellPrice = currencyListBinanceToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionBinance);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kraken <-> Binance";
                
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListKrakenToUSDT[i].ask;
                    pair.sellPrice = currencyListBinanceToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionBinance);
                    pair.from = 5;
                    pair.to = 1;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> Huobi
            if (currencyListHuobiToUSDT.size() > i && currencyListHuobiToUSDT[i].bid != 0) {
                double sellPrice = currencyListHuobiToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionHuobi);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kraken <-> Huobi";
                 
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsSmallToUSDT[i];
                    pair.buyPrice = currencyListKrakenToUSDT[i].ask;
                    pair.sellPrice = currencyListHuobiToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionHuobi);
                    pair.from = 5;
                    pair.to = 2;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> Kukoin
            if (currencyListKukoinToUSDT.size() > i && currencyListKukoinToUSDT[i].bid != 0) {
                double sellPrice = currencyListKukoinToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionKukoin);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kraken <-> Kukoin";
                   
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsToUSDT[i];
                    pair.buyPrice = currencyListKrakenToUSDT[i].ask;
                    pair.sellPrice = currencyListKukoinToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionKukoin);
                    pair.from = 5;
                    pair.to = 3;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> BitMart
            if (currencyListBitMartToUSDT.size() > i && currencyListBitMartToUSDT[i].bid != 0) {
                double sellPrice = currencyListBitMartToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionBitmart);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kraken <-> BitMart";
                 
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithUnterToUSDT[i];
                    pair.buyPrice = currencyListKrakenToUSDT[i].ask;
                    pair.sellPrice = currencyListBitMartToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionBitmart);
                    pair.from = 5;
                    pair.to = 4;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> OKX
            if (currencyListByBitToUSDT.size() > i && currencyListByBitToUSDT[i].bid != 0) {
                double sellPrice = currencyListByBitToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionByBit);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Kraken <-> ByBit";
                  
                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListKrakenToUSDT[i].ask;
                    pair.sellPrice = currencyListByBitToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionByBit);
                    pair.from = 5;
                    pair.to = 6;
                    pairs.push_back(pair);
                }
            }
        }


        if (currencyListByBitToUSDT.size() > i && currencyListByBitToUSDT[i].ask != 0) {
            double buyPrice = currencyListByBitToUSDT[i].ask;

            // ByBit <-> Binance
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].bid != 0) {
                double sellPrice = currencyListBinanceToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionBinance);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "ByBit <-> Binance";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListByBitToUSDT[i].ask;
                    pair.sellPrice = currencyListBinanceToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionBinance);
                    pair.from = 6;
                    pair.to = 1;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> Huobi
            if (currencyListHuobiToUSDT.size() > i && currencyListHuobiToUSDT[i].bid != 0) {
                double sellPrice = currencyListHuobiToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionHuobi);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "ByBit <-> Huobi";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsSmallToUSDT[i];
                    pair.buyPrice = currencyListByBitToUSDT[i].ask;
                    pair.sellPrice = currencyListHuobiToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionHuobi);
                    pair.from = 6;
                    pair.to = 2;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> Kukoin
            if (currencyListKukoinToUSDT.size() > i && currencyListKukoinToUSDT[i].bid != 0) {
                double sellPrice = currencyListKukoinToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionKukoin);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "ByBit <-> Kukoin";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsToUSDT[i];
                    pair.buyPrice = currencyListByBitToUSDT[i].ask;
                    pair.sellPrice = currencyListKukoinToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionKukoin);
                    pair.from = 6;
                    pair.to = 3;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> BitMart
            if (currencyListBitMartToUSDT.size() > i && currencyListBitMartToUSDT[i].bid != 0) {
                double sellPrice = currencyListBitMartToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionBitmart);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "ByBit <-> BitMart";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                     pair.pairto = currencyPairsWithUnterToUSDT[i];
                    pair.buyPrice = currencyListByBitToUSDT[i].ask;
                    pair.sellPrice = currencyListBitMartToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionBitmart);
                    pair.from = 6;
                    pair.to = 4;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> OKX
            if (currencyListKrakenToUSDT.size() > i && currencyListKrakenToUSDT[i].bid != 0) {
                double sellPrice = currencyListKrakenToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionByBit);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "ByBit <-> Kraken";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListByBitToUSDT[i].ask;
                    pair.sellPrice = currencyListKrakenToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionKraken, comissionByBit);
                    pair.from = 6;
                    pair.to = 5;
                    pairs.push_back(pair);
                }
            }
        }

        //BINANCE BUSD
        if (currencyListBinanceToBUSD.size() > i && currencyListBinanceToBUSD[i].ask != 0) {
            double buyPrice = currencyListBinanceToBUSD[i].ask;

           
            if (currencyListBinanceToUSDT.size() > i && currencyListBinanceToUSDT[i].bid != 0) {
                double sellPrice = currencyListBinanceToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionBinance);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance(B) <-> Binance";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListBinanceToBUSD[i].ask;
                    pair.sellPrice = currencyListBinanceToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionBinance);
                    pair.from = 1;
                    pair.to = 1;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> Huobi
            if (currencyListHuobiToUSDT.size() > i && currencyListHuobiToUSDT[i].bid != 0) {
                double sellPrice = currencyListHuobiToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionHuobi);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "BINANCEUSD <-> Huobi";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsSmallToUSDT[i];
                    pair.buyPrice = currencyListBinanceToBUSD[i].ask;
                    pair.sellPrice = currencyListHuobiToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionHuobi);
                    pair.from = 1;
                    pair.to = 2;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> Kukoin
            if (currencyListKukoinToUSDT.size() > i && currencyListKukoinToUSDT[i].bid != 0) {
                double sellPrice = currencyListKukoinToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionKukoin);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance(B) <-> Kukoin";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsToUSDT[i];
                    pair.buyPrice = currencyListBinanceToBUSD[i].ask;
                    pair.sellPrice = currencyListKukoinToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionKukoin);
                    pair.from = 1;
                    pair.to = 3;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> BitMart
            if (currencyListBitMartToUSDT.size() > i && currencyListBitMartToUSDT[i].bid != 0) {
                double sellPrice = currencyListBitMartToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionBitmart);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance(B) <-> BitMart";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithUnterToUSDT[i];
                    pair.buyPrice = currencyListBinanceToBUSD[i].ask;
                    pair.sellPrice = currencyListBitMartToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionBitmart);
                    pair.from = 1;
                    pair.to = 4;
                    pairs.push_back(pair);
                }
            }

            // Kraken <-> OKX
            if (currencyListKrakenToUSDT.size() > i && currencyListKrakenToUSDT[i].bid != 0) {
                double sellPrice = currencyListKrakenToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionByBit);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance(B) <-> Kraken";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListBinanceToBUSD[i].ask;
                    pair.sellPrice = currencyListKrakenToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionByBit);
                    pair.from = 1;
                    pair.to = 5;
                    pairs.push_back(pair);
                }
            }

            if (currencyListByBitToUSDT.size() > i && currencyListByBitToUSDT[i].bid != 0) {
                double sellPrice = currencyListByBitToUSDT[i].bid;
                double profit = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionByBit);
                double profitPercentage = (profit / (tradeSum + profit)) * 100.0;

                if (profitPercentage > maxProfitPercentage && profit > 0) {
                    maxProfitPercentage = profitPercentage;
                    maxExchange = "Binance(B) <-> ByBit";

                    pair.exchange = maxExchange;
                    pair.pair = currencyPairsWithSlashToUSDT[i];
                    pair.pairfrom = currencyPairsWithoutSpaceToUSDT[i];
                    pair.pairto = currencyPairsWithoutSpaceToUSDT[i];
                    pair.buyPrice = currencyListBinanceToBUSD[i].ask;
                    pair.sellPrice = currencyListByBitToUSDT[i].bid;
                    pair.profitPercentage = maxProfitPercentage;
                    pair.profitAmount = calculateProfit(buyPrice, sellPrice, tradeSum, comissionBinance, comissionByBit);
                    pair.from = 1;
                    pair.to = 6;
                    pairs.push_back(pair);
                }
            }
        }
        std::sort(pairs.begin(), pairs.end(),
            [](const CurrencyPair& a, const CurrencyPair& b) {
                return a.profitPercentage > b.profitPercentage;
            });
    }





    // Сортировка вектора pairs по убыванию процента прибыли
   

    
   /* for (const auto& pair : pairs) {
        std::cout << "Exchange: " << pair.exchange << std::endl;
        std::cout << "Pair: " << pair.pair << std::endl;
        std::cout << "Buy Price: " << pair.buyPrice << std::endl;
        std::cout << "Sell Price: " << pair.sellPrice << std::endl;
        SetTextColor(TextColor::Green);
        std::cout << "Profit Percentage: " << pair.profitPercentage << "%" << std::endl;
        std::cout << "Profit Amount: " << pair.profitAmount << "$" << std::endl;
        SetTextColor(TextColor::Default);
        std::cout << std::endl;

    }
    */
    AutoupdateTimer.restart();
    isReadyForNewUpdate = true;
    isCurrencyCalculated = true;
    updating.play();
    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(5)));
    isAllReady_ReadyForCleaning = true;

}



void calculateFinalProfit(const std::vector<std::string>& currencyPairsWithSlashToUSDT,
    std::vector<ExchangeRate> currencyListBinanceToUSDT,
    std::vector<ExchangeRate> currencyListHuobiToUSDT,
    std::vector<ExchangeRate> currencyListKukoinToUSDT,
    std::vector<ExchangeRate> currencyListBitMartToUSDT,
    std::vector<ExchangeRate> currencyListKrakenToUSDT,
    std::vector<ExchangeRate> currencyListByBitToUSDT, sf::Font& font, float scrollOffset, bool& isUpdaterBesetz, bool& isCalculationReady, std::vector<CurrencyPair>& pairs, bool& isReadyForNewUpdate, bool& isAllReady_ReadyForCleaning, sf::Sound& updating,
    int tradeSum, bool& isCurrencyCalculated, double comissionBinance, double comissionHuobi, double comissionKukoin, double comissionBitmart, double comissionKraken, double comissionOkx, std::vector<std::string> currencyPairsToUSDT, std::vector<std::string> currencyPairsWithoutSpaceToUSDT, std::vector<std::string> currencyPairsWithUnterToUSDT, std::vector<std::string> currencyGetMarket,
    std::vector<std::string>& currencyPairsSmallToUSDT, sf::Clock& AutoupdateTimer, std::vector<ExchangeRate> currencyListBinanceToBUSD) {

    if (currencyPairsWithSlashToUSDT.empty() || currencyListBinanceToUSDT.empty() ||
        currencyListHuobiToUSDT.empty() || currencyListKukoinToUSDT.empty() ||
        currencyListBitMartToUSDT.empty() || currencyListKrakenToUSDT.empty() ||
        currencyListByBitToUSDT.empty()) {
        std::cout << "Error: Missing data in one or more lists." << std::endl;
        return;
    }

   
    std::thread workerThread(calculateFinalProfitWorker,
        std::ref(currencyPairsWithSlashToUSDT),
        std::move(currencyListBinanceToUSDT),
        std::move(currencyListHuobiToUSDT),
        std::move(currencyListKukoinToUSDT),
        std::move(currencyListBitMartToUSDT),
        std::move(currencyListKrakenToUSDT),
        std::move(currencyListByBitToUSDT),
        std::ref(font), scrollOffset, std::ref(isUpdaterBesetz),
        std::ref(isCalculationReady), std::ref(pairs), std::ref(isReadyForNewUpdate),
        std::ref(isAllReady_ReadyForCleaning), std::ref(updating),
        tradeSum, std::ref(isCurrencyCalculated), comissionBinance, comissionHuobi,
        comissionKukoin, comissionBitmart, comissionKraken, comissionOkx,
        std::ref(currencyPairsToUSDT), std::ref(currencyPairsWithoutSpaceToUSDT),
        std::ref(currencyPairsWithUnterToUSDT), std::ref(currencyGetMarket),
        std::ref(currencyPairsSmallToUSDT), std::ref(AutoupdateTimer), std::ref(currencyListBinanceToBUSD));

    workerThread.join();
}

