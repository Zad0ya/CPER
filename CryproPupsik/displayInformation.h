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

bool isValidValue(float value) {
    // Здесь вы можете добавить свою логику проверки значения
    // Например, проверка на отрицательное значение или нулевое значение

    // Пример проверки на положительное значение
    if (value > 0.0f) {
        return true;
    }
    else {
        return false;
    }
}

bool comparePairs(const CurrencyPair& a, const CurrencyPair& b) {
    return a.profitAmount > b.profitAmount;
}

void barnimation(sf::RenderWindow& window, sf::RectangleShape& baranimation, float& sizeAnimationBarX, float& sizeAnimationBarY, sf::Vector2i mousePosition, sf::Vector2f position, 
    bool& isTransitionToSmallReady)
{
   
    baranimation.setPosition(position);
    if (baranimation.getSize().x > 40.f && baranimation.getSize().y > 40.f)
    {
        sizeAnimationBarX -= 122.f;
        sizeAnimationBarY -= 5.f;
        baranimation.setSize(sf::Vector2f(sizeAnimationBarX, sizeAnimationBarY));
        window.draw(baranimation);
    }
    if (baranimation.getGlobalBounds().width == 40.f && baranimation.getGlobalBounds().height == 40.f) {
        baranimation.setSize(sf::Vector2f(40.f, 40.f));
        isTransitionToSmallReady = true;
    }
}

struct Widget {
    std::string exchange;
    std::string pair;
    std::string pairto;
    std::string pairfrom;
    int from;
    int to;
    double buyPrice;
    double sellPrice;
    double profitPercentage;
    double profitAmount;
    double buyFeePercentage;
    double sellFeePercentage;
    int widgetnum;
    double profit;
};


void drawPairs(std::vector<CurrencyPair>& pairs, sf::RenderWindow& window, float scrollOffset, int& openedBlockIndex, bool& isBlockOpen, const float& animationDuration, const float& maxAlpha, sf::Clock& clockforinvis, float& minScrollOffset, sf::Sound& openingDopMenu,
    bool& isCurrencyCalculated, std::vector<CurrencyPair>& sortedPairs, sf::Sprite& icons, std::vector<bool>& widgetSelection, sf::Sprite& iconBonusSmallSelection, sf::Sprite& iconBonusBigSelection, sf::Sprite& iconBonusSmall, sf::Sprite& iconBonusBig, 
    sf::RectangleShape& baranimation, float& sizeAnimationBarX, float& sizeAnimationBarY, bool& isiconselected, float& iconscolor, sf::Vector2f& selectedIconPosition, bool& isTransitionToSmallReady, sf::Time deltaTime, sf::CircleShape& сircle, bool& drawCirlceBool, sf::Sprite& exiticon,
    float& iconvisability, std::string& temporaryExchangforwidget, std::string& temporaryPairforwidget, bool& isOverWidget, int& temporaryfrom, int& temporaryto, int tradeSum, double comissionBinance, double comissionHuobi, double comissionKukoin, double comissionBitmart, double comissionKraken, double comissionOkx,
    std::string& temporarypairFrom, std::string& temporarypairTo, std::vector<Widget>& widgets, bool& updatewidgets) {
    minScrollOffset = sortedPairs.size() * (60 + 5);
    const float startX = window.getSize().x / 1.65 - 650 / 5;
    const float startY = 150.0f;
    const float rectHeight = 65.0f;
    const float rectSpacing = 15.0f;
   
    сircle.setFillColor(sf::Color(130, 130, 130, 255));
    icons.setTextureRect(sf::IntRect(50, 64, 656, 67));
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Font font1;
    if (!font1.loadFromFile("C:/WINDOWS/Fonts/arial.ttf")) {
        // Обработка ошибки загрузки шрифта
    }
    CurrencyPair pair;
    Widget widget;
    if (isCurrencyCalculated) {
        sortedPairs.clear();
        sortedPairs = pairs;
        isCurrencyCalculated = false;
    }
    std::sort(sortedPairs.begin(), sortedPairs.end(), comparePairs);

    sf::Text text;
    text.setFont(font1);
    text.setCharacterSize(16);

  
  

    for (int i = 0; i < 3; i++) {
        if (!widgetSelection[i]) {
            iconBonusSmallSelection.setPosition(150 + (i * 245), 126);
            window.draw(iconBonusSmallSelection);
            sf::FloatRect widgetBounds = iconBonusSmallSelection.getGlobalBounds();
            if (widgetBounds.contains(mousePosition.x, mousePosition.y) && isiconselected) {
                iconBonusSmallSelection.setPosition(150 + (i * 245), 126);
                window.draw(iconBonusSmallSelection);
                isOverWidget = true;

                if (isiconselected && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && widgetBounds.contains(mousePosition.x, mousePosition.y) && !drawCirlceBool) {
                    iconvisability = 0.f;
                    drawCirlceBool = true;

                }


                if (drawCirlceBool) {
                    float targetRadius = std::min(widgetBounds.width - 10, widgetBounds.height - 10) / 2.f;
                    float growthSpeed = 150.f; // Скорость роста круга
                    float currentRadius = сircle.getRadius();
                    float radiusDelta = growthSpeed * deltaTime.asSeconds();

                    if (currentRadius < targetRadius && iconvisability < 255.f) {
                        currentRadius = std::min(currentRadius + radiusDelta, targetRadius);
                        float centerOffsetX = (widgetBounds.width - currentRadius * 2.f) / 2.f;
                        float centerOffsetY = (widgetBounds.height - currentRadius * 2.f) / 2.f;
                        iconvisability += 127.5f * deltaTime.asSeconds();
                        iconBonusSmall.setColor(sf::Color(255, 255, 255, iconvisability));
                        iconBonusSmall.setPosition(widgetBounds.left, widgetBounds.top);
                        window.draw(iconBonusSmall);
                        сircle.setRadius(currentRadius);
                        сircle.setPosition(widgetBounds.left + centerOffsetX, widgetBounds.top + centerOffsetY);
                    }
                    else {
                        сircle.setRadius(0.f); widgetSelection[i] = true; isiconselected = false; iconvisability = 0.f;


                        widget.widgetnum = i;
                        widget.exchange = temporaryExchangforwidget;
                        widget.pair = temporaryPairforwidget;
                        widget.pairfrom = temporaryPairforwidget;
                        widget.pairto = temporaryPairforwidget;
                        widget.from = temporaryfrom;
                        widget.to = temporaryto;
                        widget.pairfrom = temporarypairFrom;
                        widget.pairto = temporarypairTo;

                        if (temporaryfrom == 1) {
                            widget.buyFeePercentage = comissionBinance;
                        }
                        if (temporaryfrom == 2) {
                            widget.buyFeePercentage = comissionHuobi;
                        }
                        if (temporaryfrom == 3) {
                            widget.buyFeePercentage = comissionKukoin;
                        }
                        if (temporaryfrom == 4) {
                            widget.buyFeePercentage = comissionBitmart;
                        }
                        if (temporaryfrom == 5) {
                            widget.buyFeePercentage = comissionKraken;
                        }
                        if (temporaryfrom == 6) {
                            widget.buyFeePercentage = comissionOkx;
                        }

                        if (temporaryto == 1) {
                            widget.sellFeePercentage = comissionBinance;
                        }
                        if (temporaryto == 2) {
                            widget.sellFeePercentage = comissionHuobi;
                        }
                        if (temporaryto == 3) {
                            widget.sellFeePercentage = comissionKukoin;
                        }
                        if (temporaryto == 4) {
                            widget.sellFeePercentage = comissionBitmart;
                        }
                        if (temporaryto == 5) {
                            widget.sellFeePercentage = comissionKraken;
                        }
                        if (temporaryto == 6) {
                            widget.sellFeePercentage = comissionOkx;
                        }
                        std::cout << "From" << temporaryfrom << std::endl;
                        std::cout << "To" << temporaryto << std::endl;
                        std::cout << "Fee Buy " << widget.buyFeePercentage << std::endl;
                        std::cout << "Fee Sell " << widget.sellFeePercentage << std::endl;
                        widgets.insert(widgets.begin() + i, widget);
                    }
                }
            }
            else { isOverWidget = false;  сircle.setRadius(0.f); }

        }
     
    }
    for (int i = 0; i < 3; i++) {
        if (widgetSelection[i]) {
            iconBonusSmall.setColor(sf::Color(255, 255, 255, 255));
            iconBonusSmall.setPosition(150 + (i * 245), 126);
            window.draw(iconBonusSmall);

            sf::FloatRect widgetBounds2 = iconBonusSmall.getGlobalBounds();
            if (widgetBounds2.contains(mousePosition.x, mousePosition.y)) {
                exiticon.setPosition(widgetBounds2.left + (widgetBounds2.width - 59), widgetBounds2.top + 8);
                window.draw(exiticon);
                sf::FloatRect exitbuttonBounds = exiticon.getGlobalBounds();
                if (exitbuttonBounds.contains(mousePosition.x, mousePosition.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    int widgetnum = i; // Значение, которое нужно найти (здесь необходимо задать нужное значение)

                    // Поиск элемента с заданным widgetnum и очистка его содержимого
                    for (int i = 0; i < widgets.size(); ++i) {
                        if (widgets[i].widgetnum == widgetnum) {
                            widgets[i].exchange = "Fail Exchange";
                            widgets[i].pair = "Fail Pair";
                            widgets[i].pairto = "Fail Pair To";
                            widgets[i].pairfrom = "Fail Pair From";
                            widgets[i].from = 0;
                            widgets[i].to = 0;
                            widgets[i].buyPrice = 0.0;
                            widgets[i].sellPrice = 0.0;
                            widgets[i].profitPercentage = 0.0;
                            widgets[i].profitAmount = 0.0;
                            widgets[i].buyFeePercentage = 0.0;
                            widgets[i].sellFeePercentage = 0.0;
                            widgets[i].widgetnum = 0;
                            widgets[i].profit = 0.0;
                            widgetSelection[i] = false; // Сброс флага выбора элемента
                            break; // Опционально, чтобы остановить поиск после первого совпадения
                        }
                    }
                }
            }
        }
    }
    

    if (updatewidgets == true) {
        std::thread calculateThread([&widgets, &widgetSelection, &iconBonusSmall, &window, &mousePosition, tradeSum, &updatewidgets]() {
            if(updatewidgets == true) {
                updatewidgets = false;
                for (int i = 0; i < 3; i++) {
                    if (widgetSelection[i]) {

                        if (widgets[i].from >= 1 && widgets[i].from <= 6 && widgets[i].to >= 1 && widgets[i].to <= 6) {
                            ExchangeRate ratepro;
                            std::string buyExchange, sellExchange;

                            if (widgets[i].from == 1) {
                                buyExchange = "Binance";
                                ratepro = GetExchangeRateBinance(widgets[i].pairfrom);
                            }
                            else if (widgets[i].from == 2) {
                                buyExchange = "Huobi";
                                ratepro = GetExchangeRateHuobi(widgets[i].pairfrom);
                            }
                            else if (widgets[i].from == 3) {
                                buyExchange = "Kukoin";
                                ratepro = GetExchangeRateKukoin(widgets[i].pairfrom);
                            }
                            else if (widgets[i].from == 4) {
                                buyExchange = "BitMart";
                                ratepro = GetExchangeRateBitMart(widgets[i].pairfrom);
                            }
                            else if (widgets[i].from == 5) {
                                buyExchange = "Kraken";
                                ratepro = GetExchangeRateKraken(widgets[i].pairfrom);
                            }
                            else if (widgets[i].from == 6) {
                                buyExchange = "OKX";
                                ratepro = GetExchangeRateOKXe(widgets[i].pairfrom);
                            }

                            if (widgets[i].to == 1) {
                                sellExchange = "Binance";
                                ratepro = GetExchangeRateBinance(widgets[i].pairto);
                            }
                            else if (widgets[i].to == 2) {
                                sellExchange = "Huobi";
                                ratepro = GetExchangeRateHuobi(widgets[i].pairto);
                            }
                            else if (widgets[i].to == 3) {
                                sellExchange = "Kukoin";
                                ratepro = GetExchangeRateKukoin(widgets[i].pairto);
                            }
                            else if (widgets[i].to == 4) {
                                sellExchange = "BitMart";
                                ratepro = GetExchangeRateBitMart(widgets[i].pairto);
                            }
                            else if (widgets[i].to == 5) {
                                sellExchange = "Kraken";
                                ratepro = GetExchangeRateKraken(widgets[i].pairto);
                            }
                            else if (widgets[i].to == 6) {
                                sellExchange = "OKX";
                                ratepro = GetExchangeRateOKXe(widgets[i].pairto);
                            }

                            widgets[i].buyPrice = ratepro.ask;
                            widgets[i].sellPrice = ratepro.bid;
                            widgets[i].profit = calculateProfit(widgets[i].buyPrice, widgets[i].sellPrice, tradeSum, widgets[i].buyFeePercentage, widgets[i].sellFeePercentage);
          
                        }
                    }
                }

                std::this_thread::sleep_for(std::chrono::seconds(3));
                updatewidgets = true;
            }
            });

        calculateThread.detach();

    }
    for (int i = 0; i < 3; i++) {
       // std::cout << widgets[i].sellPrice << "  " << widgets[i].buyPrice << "  " << widgets[i].profit << std::endl;
        if (widgetSelection[i] && isValidValue(widgets[i].buyPrice) && isValidValue(widgets[i].sellPrice) && isValidValue(widgets[i].profit)) {
            // Отрисовка значений
            sf::Text exchange(widgets[i].exchange, font1, 20);
            exchange.setStyle(sf::Text::Bold);
            exchange.setPosition(170 + (i * 245), 160);
            exchange.setFillColor(sf::Color::Black);
            window.draw(exchange);

            sf::Text pairtext(widgets[i].pair, font1, 18);
            pairtext.setStyle(sf::Text::Bold);
            pairtext.setPosition(225 + (i * 245), 180);
            pairtext.setFillColor(sf::Color(255, 153, 0, 255));
            window.draw(pairtext);

            sf::Text buyPriceText("Buy Price: " + std::to_string(widgets[i].buyPrice), font1, 14);
            buyPriceText.setPosition(180 + (i * 245), 220);
            buyPriceText.setFillColor(sf::Color::Black);
            window.draw(buyPriceText);

            sf::Text sellPriceText("Sell Price: " + std::to_string(widgets[i].sellPrice), font1, 14);
            sellPriceText.setPosition(180 + (i * 245), 250);
            sellPriceText.setFillColor(sf::Color::Black);
            window.draw(sellPriceText);

            sf::Text profitText("Profit: " + std::to_string(widgets[i].profit), font1, 16);
            profitText.setPosition(230 + (i * 245), 310);
            profitText.setFillColor(sf::Color::Black);
            window.draw(profitText);

        }
    }
       


    window.draw(сircle);
    
    if (!widgetSelection[3]) {
        iconBonusBigSelection.setPosition(180, 378.5); //378.5
        window.draw(iconBonusBigSelection);
    }
 
    for (int i = 4; i < 7; i++) {
        if (!widgetSelection[i]) {
            iconBonusSmallSelection.setPosition(150 + ((i - 4) * 245), 626); //378.5
            window.draw(iconBonusSmallSelection);
        }
    }

    if (sortedPairs.empty()) {
        // Отрисовка сообщения об отсутствии данных

        sf::RectangleShape rectangle(sf::Vector2f(650.0f, rectHeight));
        rectangle.setPosition(startX, window.getSize().y / 2 - rectHeight / 2);
        rectangle.setFillColor(sf::Color(37, 37, 37, 255));
        rectangle.setOutlineThickness(5.0f);
        rectangle.setOutlineColor(sf::Color(57, 57, 57, 255));
        window.draw(rectangle);

        text.setString("Pairs not found");
        text.setPosition(rectangle.getPosition().x  + 270, rectangle.getPosition().y + 25);
        text.setFillColor(sf::Color(125, 125, 125, 255));
        window.draw(text);
    }
    else if (!sortedPairs.empty()) {


        // Отрисовка блоков с данными
        text.setCharacterSize(16);
        for (size_t i = 0; i < sortedPairs.size(); ++i) {
            const CurrencyPair& pair = sortedPairs[i];

            float rectY = startY + i * (rectHeight + rectSpacing) + scrollOffset;

            sf::Vector2u windowSize = window.getSize();
            float bottomY = windowSize.y - rectHeight - rectSpacing;

           
            icons.setPosition(startX, rectY);

            sf::Time elapsedTime = clockforinvis.getElapsedTime();
            float alpha = maxAlpha;

            if (rectY > bottomY) {
                alpha = maxAlpha * (1 - (rectY - bottomY) / (rectHeight + rectSpacing));
            }

            if (alpha <= 0) {
                continue;
            }
            text.setCharacterSize(16);
           

            bool isCursorOverIcon = (mousePosition.x >= startX && mousePosition.x <= startX + 656 &&
                mousePosition.y >= rectY && mousePosition.y <= rectY + 67);

            if (isCursorOverIcon && !isiconselected && window.hasFocus()) {
                icons.setColor(sf::Color(255, 255, 255, 150));
            }
            else {
                icons.setColor(sf::Color::White);
            }

            if (!isiconselected && sf::Mouse::isButtonPressed(sf::Mouse::Left) && isCursorOverIcon && window.hasFocus()) {
                isiconselected = true;
                selectedIconPosition = sf::Vector2f(startX, rectY);
                sizeAnimationBarX = 650.f;
                sizeAnimationBarY = 65.f;
                baranimation.setSize(sf::Vector2f(sizeAnimationBarX, sizeAnimationBarY));
                baranimation.setPosition(selectedIconPosition);
                temporaryExchangforwidget = pair.exchange;
                temporaryPairforwidget = pair.pair;
                temporaryfrom = pair.from;
                temporaryto = pair.to;
                temporarypairFrom = pair.pairfrom;
                temporarypairTo = pair.pairto;
                
            }

            if (isiconselected && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
                isiconselected = false;
                if (iconscolor < 255) {
                    iconscolor += 15;
                    icons.setColor(sf::Color(255, 255, 255, iconscolor));
                }
                if (iconscolor >= 255) {
                    icons.setColor(sf::Color(255, 255, 255, 255));
                }
                sizeAnimationBarX = 650.f;
                sizeAnimationBarY = 65.f;
                baranimation.setSize(sf::Vector2f(sizeAnimationBarX, sizeAnimationBarY));
                baranimation.setPosition(selectedIconPosition);
            }

            if (isiconselected) {
                sf::Vector2f targetPosition = sf::Vector2f(mousePosition.x, mousePosition.y);
                float epsilon = 1.f; // Эпсилон для сравнения плавающих точек

                

                    float speed = 4.0f;
                    sf::Vector2f currentPosition = baranimation.getPosition();
                    sf::Vector2f direction = targetPosition - currentPosition;
                    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    if (distance > 1.0f) {
                        sf::Vector2f movement = (direction / distance) * speed; // Интерполяция
                        baranimation.move(movement);
                    }
                

                float targetSizeX = 50.f;
                float targetSizeY = 50.f;

                if (baranimation.getSize().x > targetSizeX) {
                    sizeAnimationBarX -= 200.f * deltaTime.asSeconds(); // Интерполяция
                    baranimation.setSize(sf::Vector2f(sizeAnimationBarX, sizeAnimationBarY));
                }

                if (baranimation.getSize().x <= targetSizeX) {
                    baranimation.setSize(sf::Vector2f(targetSizeX, sizeAnimationBarY));
                }

                if (baranimation.getSize().y > targetSizeY) {
                    sizeAnimationBarY -= 5.f * deltaTime.asSeconds(); // Интерполяция
                    baranimation.setSize(sf::Vector2f(sizeAnimationBarX, sizeAnimationBarY));
                }

                if (baranimation.getSize().y <= targetSizeY) {
                    baranimation.setSize(sf::Vector2f(sizeAnimationBarX, targetSizeY));
                }

                if (baranimation.getGlobalBounds().width == targetSizeX && baranimation.getGlobalBounds().height == targetSizeY) {
                    isTransitionToSmallReady = true;
                }
            }


            

            window.draw(icons);
            if (isiconselected) {
                window.draw(baranimation);
            }



            text.setFillColor(sf::Color(130, 130, 130,255)); // Цвет текста в кавычках

            text.setStyle(sf::Text::Regular);
            text.setString("Exchange: ");
            text.setPosition(startX + 30.0f, rectY + 13.0f);
            window.draw(text);

            text.setStyle(sf::Text::Bold);
            text.setString(pair.exchange);
            text.setPosition(startX + 118.0f, rectY + 13.0f);
            text.setFillColor(sf::Color(230, 230, 230, 230));
            window.draw(text);

            text.setStyle(sf::Text::Regular);
            text.setFillColor(sf::Color(130, 130, 130, 255));
            text.setString("Pair: ");
            text.setPosition(startX + 30.0f, rectY + 33.0f);
            window.draw(text);

            text.setStyle(sf::Text::Bold);
            text.setString(pair.pair);
            text.setPosition(startX + 118.0f, rectY + 33.0f);
            text.setFillColor(sf::Color(230, 230, 230, 230)); // Цвет pair
            window.draw(text);

            text.setStyle(sf::Text::Regular);
            text.setFillColor(sf::Color(130, 130, 130, 255));
            text.setString("Buy Price: ");
            text.setPosition(startX + 285.0f, rectY + 13.0f);
            window.draw(text);

            text.setStyle(sf::Text::Bold);
            text.setString(std::to_string(pair.buyPrice));
            text.setPosition(startX + 360.0f, rectY + 13.0f);
            text.setFillColor(sf::Color(230, 230, 230, 230));
            window.draw(text);

            text.setStyle(sf::Text::Regular);
            text.setFillColor(sf::Color(130, 130, 130, 255));
            text.setString("Sell Price: ");
            text.setPosition(startX + 285.0f, rectY + 33.0f);
            window.draw(text);

            text.setStyle(sf::Text::Bold);
            text.setString(std::to_string(pair.sellPrice));
            text.setPosition(startX + 360.0f, rectY + 33.0f);
            text.setFillColor(sf::Color(230, 230, 230, 230));
            window.draw(text);

            std::stringstream stream;
            stream << "Profit: " << std::fixed << std::setprecision(2) << pair.profitAmount << "$";
            text.setFillColor(sf::Color::Black);
            text.setStyle(sf::Text::Bold);
            text.setCharacterSize(24);
            text.setPosition(startX + 460.0f, rectY + 20.0f);
            text.setString(stream.str());

            window.draw(text);
            text.setStyle(sf::Text::Regular);
            text.setCharacterSize(16);


            // Проверка попадания указателя мыши в блок
         
         

            // Отображение полной информации о выбранной связке
            if (isBlockOpen && openedBlockIndex == i) {
                sf::RectangleShape overlay(sf::Vector2f(window.getSize().x / 4, window.getSize().y / 1.5f));
                overlay.setPosition(window.getSize().x / 8.6f , window.getSize().x / 2 - overlay.getGlobalBounds().height);
                overlay.setFillColor(sf::Color(255, 255, 255, 255));
                overlay.setOutlineColor(sf::Color(57, 57, 57, 255));
                overlay.setOutlineThickness(10.0f);
                window.draw(overlay);

                
                text.setString("Profit: " + std::to_string(pair.profitAmount) + "$");
                text.setCharacterSize(20);
                text.setPosition(overlay.getPosition().x + 10, overlay.getPosition().y + 20);
                text.setStyle(sf::Text::Bold);
                window.draw(text);

                text.setCharacterSize(16);
                text.setString(pair.pair);
                text.setPosition(overlay.getPosition().x + (overlay.getGlobalBounds().width - 150), overlay.getPosition().y + 15);
                window.draw(text);

              
                text.setString(pair.exchange);
                text.setPosition(overlay.getPosition().x + (overlay.getGlobalBounds().width - 175), overlay.getPosition().y + 30);
                window.draw(text);


                text.setStyle(sf::Text::Regular);
                text.setString("Current Buy Price: " + std::to_string(pair.buyPrice) + "$");
                text.setPosition(overlay.getPosition().x + 10, overlay.getPosition().y + 80);
                text.setFillColor(sf::Color::Black);
                window.draw(text);

                text.setString("Current Sell Price: " + std::to_string(pair.sellPrice) + "$");
                text.setPosition(overlay.getPosition().x + 10, overlay.getPosition().y + 100);
                text.setFillColor(sf::Color::Black);
                window.draw(text);


                text.setString("RECUP" + std::to_string(pair.sellPrice) + "$");
                text.setStyle(sf::Text::Bold);
                text.setPosition(overlay.getPosition().x + overlay.getGlobalBounds().width / 2, overlay.getPosition().y + 150);
                text.setFillColor(sf::Color::Black);
                window.draw(text);
                text.setStyle(sf::Text::Regular);


            }
        }
    }

}

void drawSmallPairs(std::vector<CurrencyPair>& pairs, sf::RenderWindow& window, float scrollOffset, int& openedBlockIndex, bool& isBlockOpen, const float& animationDuration, const float& maxAlpha, sf::Clock& clockforinvis, float& minScrollOffset, sf::Sound& openingDopMenu,
    bool& isCurrencyCalculated, std::vector<CurrencyPair>& sortedPairs, sf::Sprite& icons) {
    minScrollOffset = sortedPairs.size() * (60 + 5);
    const float startX = window.getSize().x / 2 - 356 / 2;
    const float startY = 150.0f;
    const float rectHeight = 67.0f;
    const float rectSpacing = 15.0f;
    icons.setTextureRect(sf::IntRect(50, 522, 356, 77));
    sf::Font font1;
    if (!font1.loadFromFile("C:/WINDOWS/Fonts/arial.ttf")) {
        // Обработка ошибки загрузки шрифта
    }
    CurrencyPair pair;
    if (isCurrencyCalculated) {
        sortedPairs.clear();
        sortedPairs = pairs;
        isCurrencyCalculated = false;
    }
    std::sort(sortedPairs.begin(), sortedPairs.end(), comparePairs);

    sf::Text text;
    text.setFont(font1);
    text.setCharacterSize(16);

    if (sortedPairs.empty()) {
        // Отрисовка сообщения об отсутствии данных

        sf::RectangleShape rectangle(sf::Vector2f(356.0f, rectHeight));
        rectangle.setPosition(startX, window.getSize().y / 2 - rectHeight / 2);
        rectangle.setFillColor(sf::Color(37, 37, 37, 255));
        rectangle.setOutlineThickness(5.0f);
        rectangle.setOutlineColor(sf::Color(57, 57, 57, 255));
        window.draw(rectangle);

        text.setString("Pairs not found");
        text.setPosition(rectangle.getPosition().x + 270, rectangle.getPosition().y + 25);
        text.setFillColor(sf::Color(125, 125, 125, 255));
        window.draw(text);
    }
    else if (!sortedPairs.empty()) {
        // Отрисовка блоков с данными
        text.setCharacterSize(16);
        for (size_t i = 0; i < sortedPairs.size(); ++i) {
            const CurrencyPair& pair = sortedPairs[i];

            float rectY = startY + i * (rectHeight + rectSpacing) + scrollOffset;

            sf::Vector2u windowSize = window.getSize();
            float bottomY = windowSize.y - rectHeight - rectSpacing;


            icons.setPosition(startX, rectY);

            sf::Time elapsedTime = clockforinvis.getElapsedTime();
            float alpha = maxAlpha;

            if (rectY > bottomY) {
                alpha = maxAlpha * (1 - (rectY - bottomY) / (rectHeight + rectSpacing));
            }

            if (alpha <= 0) {
                continue;
            }
            text.setCharacterSize(14);
            window.draw(icons);

            text.setFillColor(sf::Color(130, 130, 130, 255)); // Цвет текста в кавычках

            text.setStyle(sf::Text::Regular);
            text.setString("Exchange: ");
            text.setPosition(startX + 15.0f, rectY + 18.0f);
            window.draw(text);

            text.setStyle(sf::Text::Bold);
            text.setString(pair.exchange);
            text.setPosition(startX + 93.0f, rectY + 18.0f);
            text.setFillColor(sf::Color(230, 230, 230, 230));
            window.draw(text);

            text.setStyle(sf::Text::Regular);
            text.setFillColor(sf::Color(130, 130, 130, 255));
            text.setString("Pair: ");
            text.setPosition(startX + 15.0f, rectY + 38.0f);
            window.draw(text);

            text.setStyle(sf::Text::Bold);
            text.setString(pair.pair);
            text.setPosition(startX + 93.0f, rectY + 38.0f);
            text.setFillColor(sf::Color(230, 230, 230, 230)); // Цвет pair
            window.draw(text);

            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(24);
            text.setPosition(startX + 250.0f, rectY + 23.0f);
            text.setStyle(sf::Text::Bold);

            // Ограничение количества цифр после точки до двух
            std::stringstream stream;
            stream << "+" << std::fixed << std::setprecision(2) << pair.profitAmount << "$";
            text.setString(stream.str());

            window.draw(text);

            text.setStyle(sf::Text::Regular);
            text.setCharacterSize(16);
        }
    }
}

