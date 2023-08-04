
void notification(sf::RenderWindow& window, sf::Time deltaTime, float& notificationBarSize) {
  

    if (notificationBarSize <= 255) {
        notificationBarSize += 89 * deltaTime.asSeconds();
        sf::RectangleShape notificationBar(sf::Vector2f(notificationBarSize, 20));
        notificationBar.setFillColor(sf::Color(17, 17, 17, static_cast<sf::Uint8>(notificationBarSize)));
   
        notificationBar.setPosition(sf::Vector2f(window.getSize().x / 2 - notificationBar.getGlobalBounds().width / 2, 40));
        window.draw(notificationBar);
    }
}


void transitionToSettings(sf::RenderWindow& window, sf::RectangleShape& settingsMarketSelectionBlack, sf::RectangleShape& rightSaheOhneInternetPlus, float& positionBlackSettings, bool& isTransitionToSettingsOver, sf::RectangleShape& settingsRest,
    sf::RectangleShape& leftMenubar, float& settingsmainboard, bool& isInTransition, bool& isUserInMainMenu, float& colorrest, float& colorleftsettings) {
    if (settingsMarketSelectionBlack.getGlobalBounds().width != window.getSize().x / 4.f && colorleftsettings < 255.f) {
        positionBlackSettings += 8.f;
        settingsMarketSelectionBlack.setSize(sf::Vector2f(positionBlackSettings, window.getSize().y));
        colorleftsettings += 5.f;
        settingsMarketSelectionBlack.setFillColor(sf::Color(15, 15, 15, static_cast<sf::Uint8>(colorleftsettings)));
    }
    if (settingsMarketSelectionBlack.getGlobalBounds().width >= window.getSize().x / 4.f && colorleftsettings == 255.f) {
        settingsMarketSelectionBlack.setSize(sf::Vector2f(window.getSize().x / 4.f, window.getSize().y));
        settingsMarketSelectionBlack.setFillColor(sf::Color(15, 15, 15, 255));
    }
    if (settingsRest.getGlobalBounds().width != window.getSize().x - (settingsMarketSelectionBlack.getGlobalBounds().width + rightSaheOhneInternetPlus.getGlobalBounds().width + leftMenubar.getGlobalBounds().width) && colorrest < 255.f) {
        settingsmainboard += 12.f;
        settingsRest.setSize(sf::Vector2f(settingsmainboard, window.getSize().y));
        colorrest += 5.f;
        settingsRest.setFillColor(sf::Color(117, 117, 117, static_cast<sf::Uint8>(colorrest)));
    }
    if (settingsRest.getGlobalBounds().width != window.getSize().x - (settingsMarketSelectionBlack.getGlobalBounds().width + rightSaheOhneInternetPlus.getGlobalBounds().width + leftMenubar.getGlobalBounds().width)) {
        settingsmainboard += 12.f;
        settingsRest.setSize(sf::Vector2f(settingsmainboard, window.getSize().y));

    }
    if (settingsRest.getGlobalBounds().width >= window.getSize().x - (settingsMarketSelectionBlack.getGlobalBounds().width + rightSaheOhneInternetPlus.getGlobalBounds().width + leftMenubar.getGlobalBounds().width)) {
        settingsRest.setSize(sf::Vector2f(window.getSize().x - (settingsMarketSelectionBlack.getGlobalBounds().width + rightSaheOhneInternetPlus.getGlobalBounds().width + leftMenubar.getGlobalBounds().width), window.getSize().y));
        isInTransition = false;
        isUserInMainMenu = false;
        isTransitionToSettingsOver = true;
    }
}


void transitionToMenu(sf::RenderWindow& window, sf::RectangleShape& settingsMarketSelectionBlack, sf::RectangleShape& rightSaheOhneInternetPlus, float& positionBlackSettings, bool& isTransitionToMainOver, sf::RectangleShape& settingsRest,
    sf::RectangleShape& leftMenubar, float& settingsmainboard, bool& isInTransition, bool& isUserInMainMenu, float& colorrest, float& colorleftsettings, sf::RectangleShape& leftBackgroundInformationUpdater) {
    if (settingsRest.getGlobalBounds().width > rightSaheOhneInternetPlus.getGlobalBounds().width + leftBackgroundInformationUpdater.getGlobalBounds().width) {
        settingsmainboard -= 12.f;
        settingsRest.setSize(sf::Vector2f(settingsmainboard, window.getSize().y));
        settingsRest.setPosition(settingsMarketSelectionBlack.getPosition().x + settingsMarketSelectionBlack.getGlobalBounds().width, 0);
    }
    if (settingsRest.getGlobalBounds().width <= rightSaheOhneInternetPlus.getGlobalBounds().width + leftBackgroundInformationUpdater.getGlobalBounds().width) {
        isUserInMainMenu = true;
        settingsRest.setSize(sf::Vector2f(rightSaheOhneInternetPlus.getGlobalBounds().width + leftBackgroundInformationUpdater.getGlobalBounds().width, window.getSize().y));
        if (colorrest > 0.f) {
            colorrest -= 5.f;
            settingsRest.setFillColor(sf::Color(117, 117, 117, static_cast<sf::Uint8>(colorrest)));
        }
    }

    if (settingsMarketSelectionBlack.getGlobalBounds().width > 0.f) {
        positionBlackSettings -= 8.f;
        settingsMarketSelectionBlack.setSize(sf::Vector2f(positionBlackSettings, window.getSize().y));
    }
    if (settingsMarketSelectionBlack.getGlobalBounds().width <= 0.f) {
        settingsMarketSelectionBlack.setSize(sf::Vector2f(0.f, 0.f));

        if (colorleftsettings > 0.f) {
            colorleftsettings -= 5.f;
            settingsMarketSelectionBlack.setFillColor(sf::Color(15, 15, 15, static_cast<sf::Uint8>(colorleftsettings)));
        }
        if (colorleftsettings == 0.f) {
            settingsMarketSelectionBlack.setFillColor(sf::Color(15, 15, 15, 0));
            isInTransition = false;
            settingsmainboard = 0.f;
            colorrest = 0.f;
            isTransitionToMainOver = true;
        }
        
    }
}


void drawMainMenu(sf::RenderWindow& window, sf::RectangleShape& full, sf::RectangleShape& leftMenubar, sf::Sprite& menubars, bool& isUserInMainMenu, bool& isUserInSettingsMenu, sf::RectangleShape& selectedMenu, float scrollOffset, sf::RectangleShape& rightSaheOhneInternetPlus, bool& isUpdaterBesetz, sf::RectangleShape& leftBackgroundInformationUpdater, bool& isReadyForNewUpdate, float& buttonRotation,
    sf::Sound& openingDopMenu, bool& isUserInSettings, bool& isBinanceActive, bool& isHuobiActive, bool& isKukoinActive,
    bool& isBitMartActive, bool& isKrakenActive, bool& isOKXActive, bool& isTransitionToSettingsOver, bool& isTransitionToMainOver, sf::RectangleShape& settingsMarketSelectionBlack, float& positionBlackSettings, sf::RectangleShape& settingsRest, float& settingsmainboard, bool& isInTransition, float& colorrest, float& colorleftsettings, std::vector<std::string>& currencyGetMarket,
    std::vector<bool>& selectedMarkets, sf::Vector2f mousePosView, sf::Clock& buttonIsAvailable, const float buttonreloadTime, bool& isInputActive, sf::Event event, std::string& currentText, const float textreloadTime, bool& iWouldLikeToUpdate, float& colorselected, int& colorDirection, std::string& binanceText,
    std::string& huobiText, std::string& kukoinText, std::string& bitmartText, std::string& krakenText, std::string& okxText, sf::Sprite& smallWindowOpened, bool& isSmallWindowActivated, bool& isSmallWindowActiv, sf::Sprite& button1Sprite, sf::Sprite& button2Sprite, sf::Sprite& button3Sprite, sf::Sprite& button4Sprite, sf::Sprite& leftmenubarSprite, sf::Sprite& autoButton, bool& autoUpdate, sf::Time deltaTime, 
    sf::Sprite& lightSprite, sf::Sprite& notificationSprite, bool& isLightTheme, bool& isDarkTheme)
{

    sf::Font font2;
    if (!font2.loadFromFile("C:/WINDOWS/Fonts/arial.ttf")) {

    }

    sf::Text textsettings;
    textsettings.setFont(font2);
    textsettings.setCharacterSize(20);
    textsettings.setFillColor(sf::Color::White);



    sf::Text binanceTextVisual;
    binanceTextVisual.setFont(font2);
    binanceTextVisual.setCharacterSize(30);
    binanceTextVisual.setFillColor(sf::Color::Black);

    sf::Text textInputText;
    textInputText.setFont(font2);
    textInputText.setCharacterSize(30);
    textInputText.setFillColor(sf::Color::Black);

    sf::Text huobiTextVisual;
    huobiTextVisual.setFont(font2);
    huobiTextVisual.setCharacterSize(30);
    huobiTextVisual.setFillColor(sf::Color::Black);

    sf::Text kukoinTextVisual;
    kukoinTextVisual.setFont(font2);
    kukoinTextVisual.setCharacterSize(30);
    kukoinTextVisual.setFillColor(sf::Color::Black);

    sf::Text bitmartTextVisual;
    bitmartTextVisual.setFont(font2);
    bitmartTextVisual.setCharacterSize(30);
    bitmartTextVisual.setFillColor(sf::Color::Black);

    sf::Text krakenTextVisual;
    krakenTextVisual.setFont(font2);
    krakenTextVisual.setCharacterSize(30);
    krakenTextVisual.setFillColor(sf::Color::Black);

    sf::Text okxTextVisual;
    okxTextVisual.setFont(font2);
    okxTextVisual.setCharacterSize(30);
    okxTextVisual.setFillColor(sf::Color::Black);

    sf::Sprite buttonOnOff(menubars);
    sf::Sprite textInput(menubars);
    sf::Sprite textInputCom(menubars);
    textInputCom.setTextureRect(sf::IntRect(412, 378, 88, 46));


    leftmenubarSprite.setPosition(40, window.getSize().y / 2 - leftmenubarSprite.getGlobalBounds().height / 2);
    window.draw(leftmenubarSprite);
    rightSaheOhneInternetPlus.setFillColor(sf::Color(57, 57, 57, 200));
   
    selectedMenu.setFillColor(sf::Color(217, 217, 217, 130));
    
    settingsMarketSelectionBlack.setPosition(leftmenubarSprite.getPosition().x + leftmenubarSprite.getGlobalBounds().width - 8, 0);
    settingsRest.setPosition(settingsMarketSelectionBlack.getPosition().x + settingsMarketSelectionBlack.getGlobalBounds().width, 0);

    int xOffset_Market = settingsMarketSelectionBlack.getPosition().x + settingsMarketSelectionBlack.getGlobalBounds().width / 2;
    int yOffset_Market = 180;
    int const SETTINGS_MARKET_BUTTTON_SizeX = 159;
    int const SETTINGS_MARKET_BUTTTON_SizeY = 46;

    int const COMSA_MARKET_BUTTTON_SizeX = 88;
    int const COMSA_MARKET_BUTTTON_SizeY = 46;

  

    if (isUserInSettings && isTransitionToSettingsOver && !isInTransition) {
        menubars.setTextureRect(sf::IntRect(61, 215, 74, 68));
        window.draw(settingsRest);


        for (int i = 0; i < currencyGetMarket.size(); i++) {
            sf::Vector2f menuButtonPos = sf::Vector2f(xOffset_Market, yOffset_Market + (70 * i));
            if (mousePosView.x >= menuButtonPos.x && mousePosView.x <= menuButtonPos.x + SETTINGS_MARKET_BUTTTON_SizeX &&
                mousePosView.y >= menuButtonPos.y && mousePosView.y <= menuButtonPos.y + SETTINGS_MARKET_BUTTTON_SizeY) {
                buttonOnOff.setColor(sf::Color::White);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonIsAvailable.getElapsedTime().asSeconds() > buttonreloadTime && window.hasFocus()) {
                    selectedMarkets[i] = !selectedMarkets[i];
                    buttonIsAvailable.restart();
                }
            }
        }
        for (int i = 0; i < currencyGetMarket.size(); i++) {
            textsettings.setStyle(sf::Text::Bold);
            textsettings.setString(currencyGetMarket[i]);
            textsettings.setPosition(settingsMarketSelectionBlack.getPosition().x + 50, yOffset_Market + 12 + (70 * i));
            window.draw(textsettings);
            if (selectedMarkets[i] == true) {
                buttonOnOff.setTextureRect(sf::IntRect(195, 256, 165, 46));
            }
            else { buttonOnOff.setTextureRect(sf::IntRect(412, 256, 165, 46)); }
            buttonOnOff.setPosition(settingsMarketSelectionBlack.getPosition().x + settingsMarketSelectionBlack.getGlobalBounds().width / 2, yOffset_Market + (70 * i));
            window.draw(buttonOnOff);
        }

        textInput.setTextureRect(sf::IntRect(195, 378, 165, 46));
        textInput.setPosition(settingsMarketSelectionBlack.getPosition().x + settingsMarketSelectionBlack.getGlobalBounds().width / 2, yOffset_Market + 60 + (70 * currencyGetMarket.size()));
        if (isInputActive) {
            int targetColor = isInputActive ? 250 : 70; // Изменено минимальное значение на 40

            colorselected += 5 * colorDirection;
            if (colorselected > 250 || colorselected < 70) { // Изменено минимальное значение на 40
                colorDirection *= -1;
            }

            textInput.setColor(sf::Color(125, 125, 125, colorselected));
        }


        if (!isInputActive) {
            colorselected = 70;
            textInput.setColor(sf::Color::White);
        }
        window.draw(textInput);
        textsettings.setString("Input Cash:");
        textsettings.setPosition(settingsMarketSelectionBlack.getPosition().x + 50, yOffset_Market + 72 + (70 * currencyGetMarket.size()));
        window.draw(textsettings);

        if (textInput.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {

            isInputActive = true;
        }
        else if (!textInput.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) || isInputActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            isInputActive = false;

            if (!currentText.empty()) {
                int number = std::stoi(currentText);
                if (number < 1) {
                    currentText = "1";
                }
            }
            else {
                currentText = "1";
            }


            std::ofstream savedSumm("config/yourSum.txt", std::ios::trunc);
            savedSumm << currentText << std::endl;
            savedSumm.close();
            iWouldLikeToUpdate = true;
        }

        if (event.type == sf::Event::TextEntered && isInputActive) {
            if (event.text.unicode >= '0' && event.text.unicode <= '9' && currentText.size() < 8) {
                if (isInputActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    currentText += static_cast<char>(event.text.unicode);
                    buttonIsAvailable.restart();
                }
            }
            else if (event.text.unicode == '\b' && !currentText.empty()) {
                if (isInputActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    currentText.pop_back();
                    buttonIsAvailable.restart();
                }
            }
        }
        textInputText.setString(currentText);
        textInputText.setPosition(textInput.getPosition().x + 15, textInput.getPosition().y + 5);
        window.draw(textInputText);

        float iconSpacingX = (settingsMarketSelectionBlack.getSize().x - textInputCom.getGlobalBounds().width * 3) / 3;
        float iconSpacingY = 45.0f;  // Пространство между рядами иконок
        float startX = settingsMarketSelectionBlack.getPosition().x + 20;
        float startY = yOffset_Market + 150 + (70 * currencyGetMarket.size());

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                float xPos = startX + j * (textInputCom.getGlobalBounds().width + iconSpacingX);
                float yPos = startY + i * (textInputCom.getGlobalBounds().height + iconSpacingY);
                textInputCom.setPosition(xPos, yPos);
                window.draw(textInputCom);

                sf::Text exchangeText;
                exchangeText.setFont(font2);
                exchangeText.setString(currencyGetMarket[i * 3 + j]);
                exchangeText.setCharacterSize(16);
                exchangeText.setFillColor(sf::Color::White);
                exchangeText.setPosition(xPos + textInputCom.getGlobalBounds().width / 2 - exchangeText.getGlobalBounds().width / 2 - 5, yPos - 20);
                window.draw(exchangeText);
            }
        }

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                sf::Vector2f menuCommisionPos = sf::Vector2f(startX + j * (textInputCom.getGlobalBounds().width + iconSpacingX), startY + i * (textInputCom.getGlobalBounds().height + iconSpacingY));
                if (mousePosView.x >= menuCommisionPos.x && mousePosView.x <= menuCommisionPos.x + COMSA_MARKET_BUTTTON_SizeX &&
                    mousePosView.y >= menuCommisionPos.y && mousePosView.y <= menuCommisionPos.y + COMSA_MARKET_BUTTTON_SizeY) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && i == 0 && j == 0 && window.hasFocus()) {
                        isBinanceActive = true;
                    }

                    else if (!textInputCom.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) || isBinanceActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        isBinanceActive = false;

                        if (!binanceText.empty()) {
                            int number1 = std::stoi(binanceText);
                            if (number1 < 1) {
                                binanceText = "1";
                            }
                        }
                        else {
                            binanceText = "1";
                        }

                        std::ofstream savedSummBinance("config/commissionBinance.txt", std::ios::trunc);
                        savedSummBinance << binanceText << std::endl;
                        savedSummBinance.close();
                        iWouldLikeToUpdate = true;
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && i == 0 && j == 1 && window.hasFocus()) {
                        isHuobiActive = true;
                    }

                    else if (!textInputCom.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) || isHuobiActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        isHuobiActive = false;

                        if (!huobiText.empty()) {
                            int number2 = std::stoi(huobiText);
                            if (number2 < 1) {
                                huobiText = "1";
                            }
                        }
                        else {
                            huobiText = "1";
                        }

                        std::ofstream savedSummHuobi("config/commissionHuobi.txt", std::ios::trunc);
                        savedSummHuobi << huobiText << std::endl;
                        savedSummHuobi.close();
                        iWouldLikeToUpdate = true;
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && i == 0 && j == 2 && window.hasFocus()) {
                        isKukoinActive = true;
                    }

                    else if (!textInputCom.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) || isKukoinActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        isKukoinActive = false;

                        if (!kukoinText.empty()) {
                            int number3 = std::stoi(kukoinText);
                            if (number3 < 1) {
                                kukoinText = "1";
                            }
                        }
                        else {
                            kukoinText = "1";
                        }

                        std::ofstream savedSummKukoin("config/commissionKukoin.txt", std::ios::trunc);
                        savedSummKukoin << kukoinText << std::endl;
                        savedSummKukoin.close();
                        iWouldLikeToUpdate = true;
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && i == 1 && j == 0 && window.hasFocus()) {
                        isBitMartActive = true;
                    }

                    else if (!textInputCom.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) || isBitMartActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        isBitMartActive = false;

                        if (!bitmartText.empty()) {
                            int number4 = std::stoi(bitmartText);
                            if (number4 < 1) {
                                bitmartText = "1";
                            }
                        }
                        else {
                            bitmartText = "1";
                        }

                        std::ofstream savedSummBitMart("config/commissionBitMart.txt", std::ios::trunc);
                        savedSummBitMart << bitmartText << std::endl;
                        savedSummBitMart.close();
                        iWouldLikeToUpdate = true;
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && i == 1 && j == 1 && window.hasFocus()) {
                        isKrakenActive = true;
                    }
                    else if (!textInputCom.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) || isKrakenActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        isKrakenActive = false;

                        if (!krakenText.empty()) {
                            int number5 = std::stoi(krakenText);
                            if (number5 < 1) {
                                krakenText = "1";
                            }
                        }
                        else {
                            krakenText = "1";
                        }

                        std::ofstream savedSummKraken("config/commissionKraken.txt", std::ios::trunc);
                        savedSummKraken << krakenText << std::endl;
                        savedSummKraken.close();
                        iWouldLikeToUpdate = true;
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && i == 1 && j == 2) {
                        isOKXActive = true;
                    }
                    else if (!textInputCom.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) || isOKXActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        isOKXActive = false;

                        if (!okxText.empty()) {
                            int number6 = std::stoi(okxText);
                            if (number6 < 1) {
                                okxText = "1";
                            }
                        }
                        else {
                            okxText = "1";
                        }

                        std::ofstream savedSummOKX("config/commissionOKX.txt", std::ios::trunc);
                        savedSummOKX << okxText << std::endl;
                        savedSummOKX.close();
                        iWouldLikeToUpdate = true;
                    }

                }
            }
        }

        //Binance 

        if (event.type == sf::Event::TextEntered && isBinanceActive) {
            if (event.text.unicode >= '0' && event.text.unicode <= '9' && binanceText.size() < 2) {
                if (isBinanceActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    binanceText += static_cast<char>(event.text.unicode);
                    buttonIsAvailable.restart();
                }
            }
            else if (event.text.unicode == '\b' && !binanceText.empty()) {
                if (isBinanceActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    binanceText.pop_back();
                    buttonIsAvailable.restart();
                }
            }
        }
        binanceTextVisual.setString(binanceText);
        binanceTextVisual.setPosition(startX + 0 * (textInputCom.getGlobalBounds().width + iconSpacingX) + 25, startY + 0 * (textInputCom.getGlobalBounds().height + iconSpacingY) + 5);
        window.draw(binanceTextVisual);

        //Huobi

        if (event.type == sf::Event::TextEntered && isHuobiActive) {
            if (event.text.unicode >= '0' && event.text.unicode <= '9' && huobiText.size() < 2) {
                if (isHuobiActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    huobiText += static_cast<char>(event.text.unicode);
                    buttonIsAvailable.restart();
                }
            }
            else if (event.text.unicode == '\b' && !huobiText.empty()) {
                if (isHuobiActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    huobiText.pop_back();
                    buttonIsAvailable.restart();
                }
            }
        }
        huobiTextVisual.setString(huobiText);
        huobiTextVisual.setPosition(startX + 1 * (textInputCom.getGlobalBounds().width + iconSpacingX) + 25, startY + 0 * (textInputCom.getGlobalBounds().height + iconSpacingY) + 5);
        window.draw(huobiTextVisual);

        // Kukoin

        if (event.type == sf::Event::TextEntered && isKukoinActive) {
            if (event.text.unicode >= '0' && event.text.unicode <= '9' && kukoinText.size() < 2) {
                if (isKukoinActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    kukoinText += static_cast<char>(event.text.unicode);
                    buttonIsAvailable.restart();
                }
            }
            else if (event.text.unicode == '\b' && !kukoinText.empty()) {
                if (isKukoinActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    kukoinText.pop_back();
                    buttonIsAvailable.restart();
                }
            }
        }
        kukoinTextVisual.setString(kukoinText);
        kukoinTextVisual.setPosition(startX + 2 * (textInputCom.getGlobalBounds().width + iconSpacingX) + 25, startY + 0 * (textInputCom.getGlobalBounds().height + iconSpacingY) + 5);
        window.draw(kukoinTextVisual);


        // BitMart

        if (event.type == sf::Event::TextEntered && isBitMartActive) {
            if (event.text.unicode >= '0' && event.text.unicode <= '9' && bitmartText.size() < 2) {
                if (isBitMartActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    bitmartText += static_cast<char>(event.text.unicode);
                    buttonIsAvailable.restart();
                }
            }
            else if (event.text.unicode == '\b' && !bitmartText.empty()) {
                if (isBitMartActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    bitmartText.pop_back();
                    buttonIsAvailable.restart();
                }
            }
        }
        bitmartTextVisual.setString(bitmartText);
        bitmartTextVisual.setPosition(startX + 0 * (textInputCom.getGlobalBounds().width + iconSpacingX) + 25, startY + 1 * (textInputCom.getGlobalBounds().height + iconSpacingY) + 5);
        window.draw(bitmartTextVisual);

        // KRAKEN 

        if (event.type == sf::Event::TextEntered && isKrakenActive) {
            if (event.text.unicode >= '0' && event.text.unicode <= '9' && krakenText.size() < 2) {
                if (isKrakenActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    krakenText += static_cast<char>(event.text.unicode);
                    buttonIsAvailable.restart();
                }
            }
            else if (event.text.unicode == '\b' && !krakenText.empty()) {
                if (isKrakenActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    krakenText.pop_back();
                    buttonIsAvailable.restart();
                }
            }
        }
        krakenTextVisual.setString(krakenText);
        krakenTextVisual.setPosition(startX + 1 * (textInputCom.getGlobalBounds().width + iconSpacingX) + 25, startY + 1 * (textInputCom.getGlobalBounds().height + iconSpacingY) + 5);
        window.draw(krakenTextVisual);

        //OKX

        if (event.type == sf::Event::TextEntered && isOKXActive) {
            if (event.text.unicode >= '0' && event.text.unicode <= '9' && okxText.size() < 2) {
                if (isOKXActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    okxText += static_cast<char>(event.text.unicode);
                    buttonIsAvailable.restart();
                }
            }
            else if (event.text.unicode == '\b' && !okxText.empty()) {
                if (isOKXActive && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime) {
                    okxText.pop_back();
                    buttonIsAvailable.restart();
                }
            }
        }
        okxTextVisual.setString(okxText);
        okxTextVisual.setPosition(startX + 2 * (textInputCom.getGlobalBounds().width + iconSpacingX) + 25, startY + 1 * (textInputCom.getGlobalBounds().height + iconSpacingY) + 5);
        window.draw(okxTextVisual);
    }

    if (isUserInSettings && !isTransitionToSettingsOver) {
        transitionToSettings(window, settingsMarketSelectionBlack, rightSaheOhneInternetPlus, positionBlackSettings, isTransitionToSettingsOver, settingsRest, leftMenubar, settingsmainboard, isInTransition, isUserInMainMenu, colorrest, colorleftsettings);
        window.draw(settingsRest); 
        window.draw(settingsMarketSelectionBlack);
    }

    if (!isUserInSettings && !isTransitionToMainOver && isInTransition) {
        transitionToMenu(window, settingsMarketSelectionBlack, rightSaheOhneInternetPlus, positionBlackSettings, isTransitionToMainOver, settingsRest, leftMenubar, settingsmainboard, isInTransition, isUserInMainMenu, colorrest, colorleftsettings, leftBackgroundInformationUpdater);
        window.draw(settingsMarketSelectionBlack);
        window.draw(settingsRest);
    }



    button1Sprite.setPosition(leftmenubarSprite.getPosition().x + leftmenubarSprite.getGlobalBounds().width / 2 - button1Sprite.getGlobalBounds().width / 2, 80);
    window.draw(button1Sprite);
    sf::FloatRect button1Bounds = button1Sprite.getGlobalBounds();

    button2Sprite.setPosition(leftmenubarSprite.getPosition().x + leftmenubarSprite.getGlobalBounds().width / 2 - button2Sprite.getGlobalBounds().width / 2, 160);
    window.draw(button2Sprite);
    sf::FloatRect button2Bounds = button2Sprite.getGlobalBounds();

    button3Sprite.setOrigin(button3Sprite.getLocalBounds().width / 2, button3Sprite.getLocalBounds().height / 2);
    button3Sprite.setPosition(leftmenubarSprite.getPosition().x + leftmenubarSprite.getGlobalBounds().width / 2, 503);

    button4Sprite.setPosition(leftmenubarSprite.getPosition().x + leftmenubarSprite.getGlobalBounds().width / 2 - button4Sprite.getGlobalBounds().width / 2, 233);
    window.draw(button4Sprite);
    sf::FloatRect button4Bounds = button4Sprite.getGlobalBounds();

    lightSprite.setPosition(leftmenubarSprite.getPosition().x + leftmenubarSprite.getGlobalBounds().width / 2 - lightSprite.getGlobalBounds().width / 2, 309);
    window.draw(lightSprite);
    sf::FloatRect lightSpriteBounds = lightSprite.getGlobalBounds();

    notificationSprite.setPosition(leftmenubarSprite.getPosition().x + leftmenubarSprite.getGlobalBounds().width / 2 - notificationSprite.getGlobalBounds().width / 2, 384);
    window.draw(notificationSprite);
    sf::FloatRect notificationSpriteBounds = notificationSprite.getGlobalBounds();
    
    autoButton.setPosition(leftmenubarSprite.getPosition().x + leftmenubarSprite.getGlobalBounds().width / 2 - autoButton.getGlobalBounds().width / 2, 535);
    if (autoUpdate == true) {
        autoButton.setColor(sf::Color(255, 255, 255, 140));
    }
    else { autoButton.setColor(sf::Color(255, 255, 255, 255)); }
    window.draw(autoButton);
    sf::FloatRect autoButtonBounds = autoButton.getGlobalBounds();

    // В цикле отрисовки
    if (!isReadyForNewUpdate) {
        buttonRotation += 9.0f;
        if (buttonRotation >= 360.0f) {
            buttonRotation -= 360.0f;
        }
    }
    else {
        if (buttonRotation > 0.0f) {
            buttonRotation += 9.0f;
            if (buttonRotation >= 360.0f) {
                buttonRotation = 0.0f;
            }
        }
    }
    //22
    button3Sprite.setRotation(buttonRotation);

    if (!isReadyForNewUpdate) {
        button3Sprite.setColor(sf::Color(205, 205, 205, 185));
    }
    else {
        if (buttonRotation == 0.0f) {
            button3Sprite.setColor(sf::Color::White);
        }
    }



    window.draw(button3Sprite);
    sf::FloatRect button3Bounds = button3Sprite.getGlobalBounds();

    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

    if (button1Bounds.contains(mousePosition) && window.hasFocus())
    {
       
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !isInTransition && !isUserInMainMenu)
        {
            openingDopMenu.play();
            isTransitionToSettingsOver = false;
            isInTransition = true;
            isUserInSettings = false;
        }
    }

    if (button2Bounds.contains(mousePosition) && window.hasFocus())
    {
        
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !isInTransition && !isUserInSettings )
        {
            openingDopMenu.play();
            isTransitionToMainOver = false;
            isInTransition = true;
            isUserInSettings = true;



        }
    }

    if (button3Bounds.contains(mousePosition) && isReadyForNewUpdate && window.hasFocus())
    {
        button3Sprite.setColor(sf::Color(255, 255, 255, 190));
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && isUpdaterBesetz && isReadyForNewUpdate)
        {
            openingDopMenu.play();
            isUpdaterBesetz = false;
        }
    }

    if (button4Bounds.contains(mousePosition) && window.hasFocus())
    {
        button3Sprite.setColor(sf::Color(255, 255, 255, 190));
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            openingDopMenu.play();
            isSmallWindowActivated = true;

        }
    }

    if (lightSpriteBounds.contains(mousePosition) && window.hasFocus())
    {
        lightSprite.setColor(sf::Color(255, 255, 255, 190));
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime)
        {
            openingDopMenu.play();
            if (isLightTheme == true) {
                isDarkTheme = true;
                isLightTheme = false;
            }

            if (isDarkTheme == true) {
                isLightTheme = true;
                isDarkTheme = true;
            }

            buttonIsAvailable.restart();
        }
    }


    if (autoButtonBounds.contains(mousePosition) && window.hasFocus())
    {
        autoButton.setColor(sf::Color(255, 255, 255, 190));
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && buttonIsAvailable.getElapsedTime().asSeconds() > textreloadTime)
        {
            openingDopMenu.play();
            autoUpdate = !autoUpdate; // Инвертируем значение autoUpdate
            float notificationBarSize = 0.0f;
            notification(window, deltaTime, notificationBarSize);
            buttonIsAvailable.restart();
        }
    }



}
