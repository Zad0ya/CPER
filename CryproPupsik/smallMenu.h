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


void openSmallMenu(bool& isSmallWindowActivated, bool& isSmallWindowActiv, sf::RenderWindow& window, sf::Sprite& smallWindowOpened, std::vector<CurrencyPair>& pairs, float scrollOffsetMini, int& openedBlockIndex, bool& isBlockOpen, const float& animationDuration, const float& maxAlpha, sf::Clock& clockforinvis, float& minScrollOffsetMini, sf::Sound& openingDopMenu,
    bool& isCurrencyCalculated, std::vector<CurrencyPair>& sortedPairs, sf::Sprite& icons, float& maxScrollOffsetMini, sf::Sprite& button3Spritecopy, sf::Sprite& button4Sprite, bool& isUpdaterBesetz, bool& isReadyForNewUpdate, float& buttonRotation, sf::Vector2f mousePosView, std::thread& currencyThread,
    bool& isCalculationReady, std::vector<bool>& selectedMarkets, bool& isAllReady_ReadyForCleaning, sf::Sound& updating, sf::Font& font, float scrollOffset, sf::RectangleShape& rectmenumini, sf::RectangleShape& rectmenuTop, sf::RectangleShape& rectmenugrenze) {
    sf::View view(sf::FloatRect(0.f, 0.f, 500.f, 800.f));
    view.setCenter(250.f, 400.f);
    window.setView(view);

        rectmenugrenze.setPosition(0, 80);

        rectmenumini.setSize(sf::Vector2f(500, 800));
        rectmenuTop.setSize(sf::Vector2f(500, 80));
        rectmenugrenze.setSize(sf::Vector2f(500, 5));

            window.draw(rectmenumini);
            drawSmallPairs(pairs, window, scrollOffset, openedBlockIndex, isBlockOpen, animationDuration,
                maxAlpha, clockforinvis, minScrollOffsetMini, openingDopMenu, isCurrencyCalculated, sortedPairs, icons);
            window.draw(rectmenuTop);
            window.draw(rectmenugrenze);

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
            button3Spritecopy.setRotation(buttonRotation);

            if (!isReadyForNewUpdate) {
                button3Spritecopy.setColor(sf::Color(205, 205, 205, 185));
            }
            else {
                if (buttonRotation == 0.0f) {
                    button3Spritecopy.setColor(sf::Color::White);
                }
            }
            window.draw(button3Spritecopy);

            button3Spritecopy.setOrigin(button3Spritecopy.getLocalBounds().width / 2, button3Spritecopy.getLocalBounds().height / 2);
            button3Spritecopy.setPosition(40, 40);
            button4Sprite.setPosition(80, 7);
            window.draw(button4Sprite);
            sf::FloatRect  button3Spritecopyfloat = button3Spritecopy.getGlobalBounds();
            sf::FloatRect  button4Spritefloat = button4Sprite.getGlobalBounds();

            sf::Vector2i mousePos2 = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosView2 = window.mapPixelToCoords(mousePos2);

            if (button3Spritecopyfloat.contains(mousePosView2) && window.hasFocus() && isReadyForNewUpdate)
            {
                button3Spritecopy.setColor(sf::Color(255, 255, 255, 190));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isUpdaterBesetz && isReadyForNewUpdate)
                {
                    std::cout << "yes" << std::endl;
                    openingDopMenu.play();
                    isUpdaterBesetz = false;

                }
            }
            if (button4Spritefloat.contains(mousePosView2) && window.hasFocus())
            {
                button4Sprite.setColor(sf::Color(255, 255, 255, 190));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    button4Sprite.setColor(sf::Color(255, 255, 255, 255));
                    std::cout << "yes" << std::endl;
                    openingDopMenu.play();
                    isSmallWindowActivated = false;

                }
            }
}