
#include <atomic>
#include <thread>
#include <vector>
#include <future>

void updateCurrency(std::vector<std::string> currencyPairsToUSDT, std::vector<std::string> currencyPairsWithoutSpaceToUSDT, std::vector<std::string> currencyPairsWithUnterToUSDT, std::vector<std::string> currencyPairsWithSlashToUSDT, std::vector<std::string> currencyGetMarket,
    std::vector<std::string>& currencyPairsSmallToUSDT, sf::Clock& timeToUpdateCurrency, const float& updateInformation, std::vector<ExchangeRate>& currencyListBinanceToUSDT,
    std::vector<ExchangeRate>& currencyListHuobiToUSDT, std::vector<ExchangeRate>& currencyListKukoinToUSDT, std::vector<ExchangeRate>& currencyListBitMartToUSDT, std::vector<ExchangeRate>& currencyListKrakenToUSDT,
    std::vector<ExchangeRate>& currencyListByBitToUSDT, bool& isUpdaterBesetz, bool& isCalculationReady, std::vector<bool>& selectedMarkets, std::vector<std::string>& currencyPairsWithoutSpaceToBUSD, std::vector<ExchangeRate>& currencyListBinanceToBUSD)
{
    isUpdaterBesetz = true;

    currencyListBinanceToUSDT.clear();
    currencyListBinanceToUSDT.resize(currencyPairsToUSDT.size());
    currencyListBinanceToBUSD.clear();
    currencyListBinanceToBUSD.resize(currencyPairsWithoutSpaceToBUSD.size());
    currencyListHuobiToUSDT.clear();
    currencyListHuobiToUSDT.resize(currencyPairsToUSDT.size());
    currencyListKukoinToUSDT.clear();
    currencyListKukoinToUSDT.resize(currencyPairsToUSDT.size());
    currencyListBitMartToUSDT.clear();
    currencyListBitMartToUSDT.resize(currencyPairsToUSDT.size());
    currencyListKrakenToUSDT.clear();
    currencyListKrakenToUSDT.resize(currencyPairsToUSDT.size());
    currencyListByBitToUSDT.clear();
    currencyListByBitToUSDT.resize(currencyPairsToUSDT.size());

    std::vector<std::future<void>> futures;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<int> atomicCounter(0);

    try {
        constexpr int numThreads = 35;

        for (int t = 0; t < numThreads; t++) {
            futures.emplace_back(std::async(std::launch::async, [&](int threadId) {
                for (int i = threadId; i < currencyPairsToUSDT.size(); i += numThreads) {
                    ExchangeRate rate1 = { 0.0, 0.0 }, rate2 = { 0.0, 0.0 }, rate3 = { 0.0, 0.0 }, rate4 = { 0.0, 0.0 }, rate5 = { 0.0, 0.0 }, rate6 = { 0.0, 0.0 }, rate7 = { 0.0, 0.0 };
                    std::future<void> future1, future2, future3, future4, future5, future6, future7;

                    if (selectedMarkets[0]) {
                        future1 = std::async(std::launch::async, [&]() {
                            rate1 = GetExchangeRateBinance(currencyPairsWithoutSpaceToUSDT[i]);
                            });
                        future7 = std::async(std::launch::async, [&]() {
                            rate7 = GetExchangeRateBinanceForBUSD(currencyPairsWithoutSpaceToBUSD[i]);
                            });
                    }
                    else {
                        ;  // Записываем 0, 0
                    }

                    if (selectedMarkets[1]) {
                        future2 = std::async(std::launch::async, [&]() {
                            rate2 = GetExchangeRateHuobi(currencyPairsSmallToUSDT[i]);
                            });
                    }
                    else {
                        ;  // Записываем 0, 0
                    }
                    if (selectedMarkets[2]) {
                        future3 = std::async(std::launch::async, [&]() {
                            rate3 = GetExchangeRateKukoin(currencyPairsToUSDT[i]);
                            });
                    }
                    else {
                        ;  // Записываем 0, 0
                    }

                    if (selectedMarkets[3]) {
                        future4 = std::async(std::launch::async, [&]() {
                            rate4 = GetExchangeRateBitMart(currencyPairsWithUnterToUSDT[i]);
                            });
                    }
                    else {
                        ;  // Записываем 0, 0
                    }
                    if (selectedMarkets[4]) {
                        future5 = std::async(std::launch::async, [&]() {
                            rate5 = GetExchangeRateKraken(currencyPairsWithoutSpaceToUSDT[i]);
                            });
                    }

                    if (selectedMarkets[5]) {
                        future6 = std::async(std::launch::async, [&]() {
                            rate6 = GetExchangeRateByBit(currencyPairsWithoutSpaceToUSDT[i]);
                            });
                    }
                    else {
                        ;  // Записываем 0, 0
                    }
                    if (selectedMarkets[0] && future1.valid() && future7.valid()) {
                        future1.wait(); future7.wait();
                    }

                    if (selectedMarkets[1] && future2.valid()) {
                        future2.wait();
                    }

                    if (selectedMarkets[2] && future3.valid()) {
                        future3.wait();
                    }

                    if (selectedMarkets[3] && future4.valid()) {
                        future4.wait();
                    }

                    if (selectedMarkets[4] && future5.valid()) {
                        future5.wait();
                    }

                    if (selectedMarkets[5] && future6.valid()) {
                        future6.wait();
                    }

                    {
                        std::lock_guard<std::mutex> lock(mtx);
                        currencyListBinanceToUSDT[i] = rate1;
                        currencyListBinanceToBUSD[i] = rate7;
                        currencyListHuobiToUSDT[i] = rate2;
                        currencyListKukoinToUSDT[i] = rate3;
                        currencyListBitMartToUSDT[i] = rate4;
                        currencyListKrakenToUSDT[i] = rate5;
                        currencyListByBitToUSDT[i] = rate6;

                        if (++atomicCounter == currencyPairsToUSDT.size()) {
                            cv.notify_all();
                        }
                    }
                }
                }, t));
        }

        std::unique_lock<std::mutex> ulock(mtx);
        cv.wait(ulock, [&] { return atomicCounter >= currencyPairsToUSDT.size(); });
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return;
    }

    auto printVector = [](const std::vector<ExchangeRate>& vec) {
        for (const auto& value : vec) {
            std::cout << "Ask price: " << value.ask << ", Bid price: " << value.bid << std::endl;
        }
        std::cout << std::endl;
    };
    isCalculationReady = true;
    printVector(currencyListBinanceToUSDT);
    printVector(currencyListBinanceToBUSD);
    printVector(currencyListHuobiToUSDT);
    printVector(currencyListKukoinToUSDT);
    printVector(currencyListBitMartToUSDT);
    printVector(currencyListKrakenToUSDT);
    printVector(currencyListByBitToUSDT);

  
}
