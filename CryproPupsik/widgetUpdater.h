
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

struct ExchangeRateWidget {
    long double ask; // Цена продажи
    long double bid; // Цена покупки
};

ExchangeRateWidget GetExchangeRateBinanceWidget(const std::string& symbol)
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

ExchangeRateWidget GetExchangeRateHuobiWidget(const std::string& symbol)
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

ExchangeRateWidget GetExchangeRateKukoinWidget(const std::string& symbol)
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

ExchangeRateWidget GetExchangeRateBitMartWidget(const std::string& symbol)
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

ExchangeRateWidget GetExchangeRateKrakenWidget(const std::string& symbol)
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

ExchangeRateWidget GetExchangeRateOKXeWidget(const std::string& symbol)
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

ExchangeRateWidget GetExchangeRateByBitWidget(const std::string& symbol) {
    http_client client(U("https://api.bybit.com"));

    uri_builder builder(U("/v2/public/tickers"));
    builder.append_query(U("symbol"), conversions::to_string_t(symbol));
    builder.append_query(U("type"), U("option"));

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

    if (json.has_field(U("result"))) {
        const auto& resultArray = json.at(U("result")).as_array();
        if (resultArray.size() > 0) {
            const auto& ticker = resultArray.at(0);
            if (ticker.has_field(U("bid_price")) && ticker.has_field(U("ask_price"))) {
                const utility::string_t& bidStr = ticker.at(U("bid_price")).as_string();
                const utility::string_t& askStr = ticker.at(U("ask_price")).as_string();
                std::string bid = utility::conversions::to_utf8string(bidStr);
                std::string ask = utility::conversions::to_utf8string(askStr);
                return { std::stod(ask), std::stod(bid) };
            }
        }
    }

    std::cout << "Invalid JSON response :" << symbol << " " << "on ByBit" << std::endl;
    return { 0, 0 };
}
