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


using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

struct ExchangeRate {
    long double ask; // Цена продажи
    long double bid; // Цена покупки
};

ExchangeRate GetExchangeRateBinance(const std::string& symbol)
{
    http_client_config config;
    config.set_validate_certificates(false);

    http_client client(U("https://api.binance.com"), config);

    uri_builder builder(U("/api/v3/ticker/bookTicker"));
    builder.append_query(U("symbol"), conversions::to_string_t(symbol));

    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();


    json::value json;
    try {
        json = json::value::parse(jsonData);
    }
    catch (const json::json_exception& e) {
        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return { 0.0, 0.0 };
    }

    if (json.has_string_field(U("bidPrice")) && json.has_string_field(U("askPrice")))
    {
        std::string bidStr = conversions::to_utf8string(json[U("bidPrice")].as_string());
        std::string askStr = conversions::to_utf8string(json[U("askPrice")].as_string());

        double bid = std::stod(bidStr);
        double ask = std::stod(askStr);

        return { ask, bid };
    }
    else
    {
        std::cout << "Invalid JSON response : " << symbol << " " << " on Binance" << std::endl;
        return { 0, 0 };
    }
}

ExchangeRate GetExchangeRateBinanceForBUSD(const std::string& symbol)
{
    http_client_config config;
    config.set_validate_certificates(false);

    http_client client(U("https://api.binance.com"), config);

    uri_builder builder(U("/api/v3/ticker/bookTicker"));
    builder.append_query(U("symbol"), conversions::to_string_t(symbol));

    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();


    json::value json;
    try {
        json = json::value::parse(jsonData);
    }
    catch (const json::json_exception& e) {
        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return { 0.0, 0.0 };
    }

    if (json.has_string_field(U("bidPrice")) && json.has_string_field(U("askPrice")))
    {
        std::string bidStr = conversions::to_utf8string(json[U("bidPrice")].as_string());
        std::string askStr = conversions::to_utf8string(json[U("askPrice")].as_string());

        double bid = std::stod(bidStr);
        double ask = std::stod(askStr);

        return { ask, bid };
    }
    else
    {
        std::cout << "Invalid JSON response : " << symbol << " " << " on Binance" << std::endl;
        return { 0, 0 };
    }
}

ExchangeRate GetExchangeRateHuobi(const std::string& symbol)
{
    http_client_config config;
    config.set_validate_certificates(false); // Опционально: отключение проверки сертификата

    http_client client(U("https://api.huobi.pro"), config);

    uri_builder builder(U("/market/detail/merged"));
    builder.append_query(U("symbol"), conversions::to_string_t(symbol));

    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();

    json::value json;
    try {
        json = json::value::parse(jsonData);
    }
    catch (const json::json_exception& e) {
        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return { 0.0, 0.0 };
    }

    if (json.has_object_field(U("tick")))
    {
        const json::value& tick = json.at(U("tick"));
        if (tick.has_array_field(U("ask")) && tick.has_array_field(U("bid")))
        {
            const json::array& askArray = tick.at(U("ask")).as_array();
            const json::array& bidArray = tick.at(U("bid")).as_array();
            if (askArray.size() > 0 && bidArray.size() > 0)
            {
                double ask = askArray.at(0).as_double();
                double bid = bidArray.at(0).as_double();
                return { ask, bid };
            }
        }
    }

    std::cout << "Invalid JSON response : " << symbol << " " << " on Huobi" << std::endl;
    return { 0, 0 };
}

ExchangeRate GetExchangeRateKukoin(const std::string& symbol)
{
    http_client_config config;
    config.set_validate_certificates(false); // Опционально: отключение проверки сертификата

    http_client client(U("https://api.kucoin.com"), config);

    uri_builder builder(U("/api/v1/market/orderbook/level1"));
    builder.append_query(U("symbol"), conversions::to_string_t(symbol));

    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();

    json::value json;
    try {
        json = json::value::parse(jsonData);
    }
    catch (const json::json_exception& e) {
        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return { 0.0, 0.0 };
    }

    if (json.has_object_field(U("data")))
    {
        const json::value& data = json.at(U("data"));
        if (data.has_string_field(U("bestAsk")) && data.has_string_field(U("bestBid")))
        {
            double ask = std::stod(data.at(U("bestAsk")).as_string());
            double bid = std::stod(data.at(U("bestBid")).as_string());
            return { ask, bid };
        }
    }

    std::cout << "Invalid JSON response : " << symbol << " " << " on Kukoin" << std::endl;
    return { 0, 0 };
}

ExchangeRate GetExchangeRateBitMart(const std::string& symbol)
{
    http_client_config config;
    config.set_validate_certificates(false); // Опционально: отключение проверки сертификата

    http_client client(U("https://api-cloud.bitmart.com"), config);

    uri_builder builder(U("/spot/v1/ticker"));
    builder.append_query(U("symbol"), conversions::to_string_t(symbol));

    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();

    json::value json;
    try {
        json = json::value::parse(jsonData);
    }
    catch (const json::json_exception& e) {
        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return { 0.0, 0.0 };
    }

    if (json.has_field(U("data")))
    {
        const json::value& data = json.at(U("data"));
        if (data.has_array_field(U("tickers")))
        {
            const json::array& tickers = data.at(U("tickers")).as_array();
            if (tickers.size() > 0)
            {
                const json::value& ticker = tickers.at(0);
                if (ticker.has_field(U("best_ask")) && ticker.has_field(U("best_bid")))
                {
                    double ask = std::stod(ticker.at(U("best_ask")).as_string());
                    double bid = std::stod(ticker.at(U("best_bid")).as_string());
                    return { ask, bid };
                }
            }
        }
    }

    std::cout << "Invalid JSON response : " << symbol << " " << " on BitMart" << std::endl;
    return { 0, 0 };
}

ExchangeRate GetExchangeRateKraken(const std::string& symbol)
{
    http_client_config config;
    config.set_validate_certificates(false); // Опционально: отключение проверки сертификата

    http_client client(U("https://api.kraken.com"), config);

    uri_builder builder(U("/0/public/Ticker"));
    builder.append_query(U("pair"), conversions::to_string_t(symbol));

    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();

    json::value json;
    try {
        json = json::value::parse(jsonData);
    }
    catch (const json::json_exception& e) {
        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return { 0, 0 };
    }

    if (json.has_object_field(U("result")))
    {
        const json::value& result = json.at(U("result"));
        if (result.has_object_field(conversions::to_string_t(symbol)))
        {
            const json::value& symbolData = result.at(conversions::to_string_t(symbol));
            if (symbolData.has_array_field(U("a")) && symbolData.has_array_field(U("b")))
            {
                const json::value& askArray = symbolData.at(U("a"));
                const json::value& bidArray = symbolData.at(U("b"));
                if (askArray.is_array() && askArray.size() > 0 && bidArray.is_array() && bidArray.size() > 0)
                {
                    double ask = std::stod(askArray.at(0).as_string());
                    double bid = std::stod(bidArray.at(0).as_string());
                    return { ask, bid };
                }
            }
        }
    }

    std::cout << "Invalid JSON response : " << symbol << " " << "on Kraken" << std::endl;
    return { 0, 0 };
}

ExchangeRate GetExchangeRateOKXe(const std::string& symbol)
{
    http_client_config config;
    config.set_validate_certificates(false); // Опционально: отключение проверки сертификата

    http_client client(U("https://www.okxe.com"), config);

    uri_builder builder(U("/v1/ticker/depth"));
    builder.append_query(U("symbol"), conversions::to_string_t(symbol));

    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();

    json::value json;
    try {
        json = json::value::parse(jsonData);
    }
    catch (const json::json_exception& e) {
        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return { 0, 0 };
    }

    if (json.has_array_field(U("bids")) && json.has_array_field(U("asks")))
    {
        const json::array& bidsArray = json.at(U("bids")).as_array();
        const json::array& asksArray = json.at(U("asks")).as_array();
        if (bidsArray.size() > 0 && asksArray.size() > 0)
        {
            double bid = std::stod(bidsArray.at(0).at(0).as_string());
            double ask = std::stod(asksArray.at(0).at(0).as_string());
            return { ask, bid };
        }
    }

    std::cout << "Invalid JSON response : " << symbol << " " << "on OKX" << std::endl;
    return { 0, 0 };
}

ExchangeRate GetExchangeRateByBit(const std::string& symbol) {
    http_client client(U("https://api.bybit.com"));

    // Используем новый URL для запроса к API Bybit
    uri_builder builder(U("/v5/market/tickers"));
    builder.append_query(U("category"), U("inverse"));
    builder.append_query(U("symbol"), conversions::to_string_t(symbol));

    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();

    // Разбор JSON-ответа для получения котировок
    json::value json;
    try {
        json = json::value::parse(jsonData);
    }
    catch (const json::json_exception& e) {
        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return { 0, 0 };
    }

    if (json.has_field(U("result"))) {
        const auto& result = json.at(U("result"));
        if (result.has_field(U("category")) && result.has_field(U("list"))) {
            const auto& category = result.at(U("category")).as_string();
            const auto& list = result.at(U("list")).as_array();

            if (category == U("inverse") && list.size() > 0) {
                const auto& ticker = list.at(0);
                if (ticker.has_field(U("bid1Price")) && ticker.has_field(U("ask1Price"))) {
                    const utility::string_t& bidStr = ticker.at(U("bid1Price")).as_string();
                    const utility::string_t& askStr = ticker.at(U("ask1Price")).as_string();
                    std::string bid = utility::conversions::to_utf8string(bidStr);
                    std::string ask = utility::conversions::to_utf8string(askStr);

                    // Создаем объект ExchangeRate и возвращаем его
                    return { std::stod(ask), std::stod(bid) };
                }
            }
        }
    }

    std::cout << "Invalid JSON response :" << symbol << " " << "on ByBit" << std::endl;
    return { 0, 0 };
}


void ParseExchangeRates(const std::string& jsonData)
{
    web::json::value json = web::json::value::parse(jsonData);

}

/* double CalculateProfit(double exchangeRateWhiteBit, double exchangeRate2, double commission1, double commission2)
{
    double difference = exchangeRateWhiteBit - exchangeRate1;
    double netDifference = difference - (difference * (commission1 + commission2));
    double profitPercentage = (netDifference / exchangeRate1) * 100;

    return profitPercentage;
}
*/

/*
double GetExchangeRateWhiteBit(const std::string& symbol)
{
    web::http::client::http_client_config config;
    config.set_validate_certificates(false); // Опционально: отключение проверки сертификата

    web::http::client::http_client client(U("https://api.whitebit.com"), config);

    web::uri_builder builder(U("/public/v4/tickers"));
    builder.append_query(U("symbol"), utility::conversions::to_string_t(symbol));

    web::http::http_request request(web::http::methods::GET);
    request.set_request_uri(builder.to_string());

    auto response = client.request(request).get();
    auto jsonData = response.extract_utf8string().get();

    web::json::value json = web::json::value::parse(jsonData);

    double exchangeRateWhiteBit = json[0][U("result")][U("last")].as_double();

    return exchangeRateWhiteBit;
}
*/
