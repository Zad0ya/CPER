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

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>
#include <cstdlib> 
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <fstream>
#include <windows.h>
#include <future>
#include <iphlpapi.h>
#include <limits>
#include <locale>
#include <cmath>
#include <cctype>
#include <numeric>
#include "getExchangeRates.h"
#include "checkConnectionToTheInternet.h"
#include "textVariations.h"
#include "connectionUpdater.h"
#include "STYLEdrawMainMenu.h"
#include "prufInternetConnection.h"
#include "performCalculation.h"
#include "calculateProfit.h"
#include "displayInformation.h"
#include "telegramClienUpdater.h"
#include "smallMenu.h"
#include "drawbarMini.h"
#include "widgetUpdater.h"
#include "setupActivation.h"


bool isUpdaterBesetz = false;



int main()
{

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int temp = 0;
    int tradeSum = 0;
    int openedBlockIndex = -1;
    int colorDirection = 1;
    int temporaryfrom = 0;
    int temporaryto = 0;
    int activeCellIndex = 0;
    const int numFrames = 7;
    int initialPositionX = 1283;
    int initialPositionY = 1234;
    int differenceX = 247;
    int differenceY = 0;
    int currentFrame = 0;

    double comissionBinance = 0;
    double comissionHuobi = 0;
    double comissionKukoin = 0;
    double comissionBitmart = 0;
    double comissionKraken = 0;
    double comissionByBit = 0;

    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;
    unsigned int modeForViewWidth = 1706;
    unsigned int modeForViewHeight = 960;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1706, 960), "CPER ULTRA+");
    sf::View view = window.getDefaultView();

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(75);

    HWND hWnd = window.getSystemHandle(); // Получаем дескриптор окна SFML

    LONG_PTR style = GetWindowLongPtr(hWnd, GWL_STYLE); // Получаем текущий стиль окна

    // Удаляем флаги, разрешающие изменение размера
    style &= ~WS_THICKFRAME; // Убираем возможность изменения размера окна пользователем
    style &= ~WS_MAXIMIZEBOX; // Убираем кнопку "Развернуть" (Maximize)

    SetWindowLongPtr(hWnd, GWL_STYLE, style); //

    

    /*std::string savedMACAddress = "00:11:22:33:44:55";
    std::string currentMACAddress = getMACAddress();
    if (currentMACAddress == savedMACAddress) {
        std::cout << "Hello, Cryptopupsik. :)" << std::endl;
    }
    else {
        std::cout << "Bye, your piece of sheet." << std::endl;
        return EXIT_FAILURE;
    }
    */
    

    const float retryconnection = 10.f;
    const float fadeSpeed = 2.0f;
    const float updateInformation = 10.f; //TEMP
    const float animationDuration = 0.5f; 
    const float maxAlpha = 255.0f; 
    const float buttonreloadTime = 0.3f;
    const float textreloadTime = 0.15f;
    const int numBubbles = 50;
    const float minScrollOffsetPolz = 130.0f;
    const float maxScrollOffsetPolz = window.getSize().y - 170.0f;
    const float CODE_BUTTON_SizeX = 135;
    const float CODE_BUTTON_SizeY = 58;
    const float updateCurrencyTime = 15.f;
    float minScrollOffset = 0.0f;
    float maxScrollOffset = 10.0f;
    float minScrollOffsetMini = 0.0f;
    float maxScrollOffsetMini = 10.0f;
    float buttonRotation = 0.f;
    float positionBlackSettings = 0.f;
    float settingsmainboard = 0.f;
    float scrollOffset = 0.0f;
    float scrollOffsetMini = 0.0f;
    float colorleftsettings = 0.f;
    float colorrest = 0.f;
    float colorselected = 70.f;
    float time = 0.f;
    float time2 = 0.0f;
    float sizeControlInternetX = 0;
    float sizeControlInternetY = 0;
    float sizeAnimationBarX = 650;
    float sizeAnimationBarY = 65;
    float iconscolor = 255;
    float iconvisability = 0.f;
    float dragOffset = 0;
    float emeraldbackgroundvisible = 0;
    float activationPosition = 100;
    float activationColor = 0;
    float textForLoadingDark = 0.f;
    float frameDuration = 0.05f;
    float timeSinceLastFrame = 0.0f;
    float colorWelcomeAndSchloss = 0.f;
    float elapsedFloatingTime = 0.0f;
    float targetPosX = -1445.0f;
    float currentPosX = 0.0f;
    float speed = 320.0f;
    float colorbackground = 17;
    float initialSpeedLeft = 380.0f; 
    float initialSpeedRight = 480.0f;
    float finalSpeedLeft = 30.0f;    
    float accelerationLeft = 100.0f;
    float finalSpeedRight = 30.0f;
    float accelerationRight = 100.0f;
    float textcolor = 255;
    float colorForBlack = 0;
    float colorForWhite = 255;
    int timedisplaytoupdate = 15;

    bool refreshConnection = true;
    bool noInternetConnection = false;
    bool isMainMenuOpened = true;
    bool isHovered = false;
    bool isExtectionMenuOpened = false;
    bool isInternetPruft = true;
    bool isUserInMainMenu = true;
    bool isUserInSettingsMenu = false;
    bool jatolkozashelhahah = true;
    bool isAllMarketsChecked = false;
    bool isCalculationReady = false;
    bool isBlockOpen = false;   
    bool isReadyForNewUpdate = true;
    bool connectedToTheInternet = true;
    bool isAllReady_ReadyForCleaning = false;
    bool isUserInSettings = false;
    bool isTransitionToSettingsOver = false;
    bool isTransitionToMainOver = false;
    bool isBinanceActive = true;
    bool isHuobiActive = true;
    bool isKukoinActive = true;
    bool isBitMartActive = true;
    bool isKrakenActive = true;
    bool isByBitActive = true;
    bool isInTransition = false;
    bool isInputActive = false;
    bool iWouldLikeToUpdate = true;
    bool isCurrencyCalculated = false;
    bool isSmallWindowActivated = false;
    bool isSmallWindowActiv = false;
    bool isiconselected = false;
    bool isTransitionToSmallReady = false;
    bool drawCirlceBool = true;
    bool isDraggingScrollbar = false;
    bool isOverWidget = false;
    bool updatewidgets = true;
    bool drawSmallMenu = false;
    bool isLicenseChecked = false;
    bool isBackGroundVisible = false;
    bool allCellsFilled = false;
    bool isActivating = false;
    bool requessendet = false;
    bool isActivated = false;
    bool isErrorActivation = false;
    bool loadFilesToMemory = false;
    bool isInTransitionToSetup = false;
    bool isInSetup = false;
    bool isErrorDuringActivation = false;
    bool readyForLoad = false;
    bool isLightTheme = false;
    bool isDarkTheme = true;
    bool isIWantToBetaTest = false;
    bool isIWantToBeAnonym = false;
    bool autoUpdate = false;

    sf::Image Bars;
    Bars.loadFromFile("Images/framesCryptopusik.png");
    sf::Texture informationBars;
    informationBars.loadFromImage(Bars);
    sf::Sprite informationSprites(informationBars);

    sf::Image m124;
    m124.loadFromFile("Images/menubar.png");
    sf::Texture m125;
    m125.loadFromImage(m124);
    sf::Sprite menubars(m125);

    sf::Image m127;
    m127.loadFromFile("Images/blacktheme.png");
    sf::Texture m129;
    m129.loadFromImage(m127);
    sf::Sprite icons(m129);

    sf::Image m130;
    m130.loadFromFile("Images/smallWindowMode.png");
    sf::Texture m131;
    m131.loadFromImage(m130);
    sf::Sprite smallWindowOpened(m131);

    sf::Image m136;
    m136.loadFromFile("Images/backgroundultra.png");
    sf::Texture m138;
    m138.loadFromImage(m136);
    sf::Sprite backgroundulta(m138);

    sf::Image m145;
    m145.loadFromFile("Images/dlcemerald.png");
    sf::Texture m146;
    m146.loadFromImage(m145);
    sf::Sprite emeraldicons(m146);

    sf::Image m10;
    m10.loadFromFile("Images/dlcemerald2.png");
    sf::Texture m12;
    m12.loadFromImage(m10);
    sf::Sprite emeraldiconssetup(m12);

    sf::Image m44;
    m44.loadFromFile("Images/dlcemeraldbackground.png");
    sf::Texture m45;
    m45.loadFromImage(m44);
    sf::Sprite emeraldactivationbackground(m45);
    emeraldactivationbackground.setColor(sf::Color(255, 255, 255, 0));

    sf::Image m20;
    m20.loadFromFile("Images/backgroundtransetosetup.png");
    sf::Texture m22;
    m22.loadFromImage(m20);
    sf::Sprite emeraldtransitiontosettingsbackground(m22);

    sf::Image m42;
    m42.loadFromFile("Images/kppsetuppass.png");
    sf::Texture m43;
    m43.loadFromImage(m42);
    sf::Sprite emeraldkpp(m43);


    sf::Image m31;
    m31.loadFromFile("Images/dlcemerald3.png");
    sf::Texture m32;
    m32.loadFromImage(m31);
    sf::Sprite emeraldiconssettings(m32);


    backgroundulta.setPosition(sf::Vector2f(0, 0));

    sf::Sprite button1Sprite(menubars);
    button1Sprite.setTextureRect(sf::IntRect(61, 117, 74, 68));

    sf::Sprite button2Sprite(menubars);
    button2Sprite.setTextureRect(sf::IntRect(61, 215, 74, 68));

    sf::Sprite button3Sprite(menubars);
    button3Sprite.setTextureRect(sf::IntRect(61, 313, 74, 68));

    sf::Sprite button3Spritecopy(menubars);
    button3Spritecopy.setTextureRect(sf::IntRect(61, 313, 74, 68));

    sf::Sprite button4Sprite(menubars);
    button4Sprite.setTextureRect(sf::IntRect(61, 412, 74, 68));

    sf::Sprite leftmenubarSprite(icons);
    leftmenubarSprite.setTextureRect(sf::IntRect(1739, 47, 87, 940));

    sf::Sprite iconBonusSmallSelection(icons);
    iconBonusSmallSelection.setTextureRect(sf::IntRect(899, 480, 237, 228));

    sf::Sprite iconBonusBigSelection(icons);
    iconBonusBigSelection.setTextureRect(sf::IntRect(899, 213, 662, 228));

    sf::Sprite iconBonusSmall(icons);
    iconBonusSmall.setTextureRect(sf::IntRect(495, 480, 237, 228));
    
    sf::Sprite iconBonusBig(icons);
    iconBonusBig.setTextureRect(sf::IntRect(40, 213, 662, 227));

    sf::Sprite exiticon(icons);
    exiticon.setTextureRect(sf::IntRect(502, 761, 46, 47));

    sf::Sprite scrollbarfield(icons);
    scrollbarfield.setTextureRect(sf::IntRect(1623, 136, 51, 762));

    sf::Sprite iconActivation(emeraldicons);
    iconActivation.setTextureRect(sf::IntRect(130, 168, 901, 578));
    iconActivation.setColor(sf::Color(255, 255, 255, 0));
    iconActivation.setPosition(sf::Vector2f(window.getSize().x / 2 - iconActivation.getGlobalBounds().width / 2, activationPosition));

    sf::Sprite iconActivationWhite(emeraldicons);
    iconActivationWhite.setTextureRect(sf::IntRect(130, 914, 901, 578));
    iconActivationWhite.setColor(sf::Color(255, 255, 255, 255));
    iconActivationWhite.setPosition(sf::Vector2f( -(iconActivation.getGlobalBounds().height+100) , window.getSize().y / 2 - iconActivation.getGlobalBounds().width / 2));

    sf::Sprite schloss(emeraldicons);
    schloss.setTextureRect(sf::IntRect(1538, 302, 208, 292));
    schloss.setColor(sf::Color(255, 255, 255, 0));
    schloss.setPosition(sf::Vector2f(window.getSize().x / 2 - schloss.getGlobalBounds().width / 2, 20));

    sf::Sprite textcodeicons(emeraldicons);
    textcodeicons.setTextureRect(sf::IntRect(1323, 1910, 171, 91));
    textcodeicons.setColor(sf::Color(255, 255, 255, 255));

    sf::Sprite continueButton(emeraldicons);
    continueButton.setTextureRect(sf::IntRect(2373, 415, 226, 101));
    continueButton.setColor(sf::Color(255, 255, 255, 255));

    //setup 

    sf::Sprite iconColorDark(emeraldiconssetup);
    iconColorDark.setTextureRect(sf::IntRect(38, 60, 206, 138));

    sf::Sprite iconColorLight(emeraldiconssetup);
    iconColorLight.setTextureRect(sf::IntRect(349, 60, 206, 138));

    sf::Sprite writeplankSetup(emeraldiconssetup);
    writeplankSetup.setTextureRect(sf::IntRect(55, 480, 388, 47));

    sf::Sprite selectionSetupNo(emeraldiconssetup);
    selectionSetupNo.setTextureRect(sf::IntRect(48, 306, 65, 65));
    sf::Sprite selectionSetupNo2(selectionSetupNo);

    sf::Sprite selectionSetupYes(emeraldiconssetup);
    selectionSetupYes.setTextureRect(sf::IntRect(161, 306, 65, 65));
    sf::Sprite selectionSetupYes2(selectionSetupYes);

    sf::Sprite whiteIconSetup90grad(emeraldiconssettings);
    whiteIconSetup90grad.setTextureRect(sf::IntRect(1059, 138, 615, 889));
    float activationPosLeft = -(whiteIconSetup90grad.getGlobalBounds().width + 100);

    sf::Sprite whiteIconSetup90grad2(emeraldiconssettings);
    whiteIconSetup90grad2.setTextureRect(sf::IntRect(1059, 138, 615, 889));
    float activationPosRight = window.getSize().x + 100;

    sf::Sprite blackIconSetup90grad(emeraldiconssettings);
    blackIconSetup90grad.setTextureRect(sf::IntRect(131, 138, 615, 889));

    sf::Sprite blackIconSetup90grad2(blackIconSetup90grad);

    sf::Sprite notActiveCircle(emeraldicons);
    notActiveCircle.setTextureRect(sf::IntRect(1325, 1645, 78, 78));

    sf::Sprite activeCircle(emeraldicons);
    activeCircle.setTextureRect(sf::IntRect(1453, 1645, 78, 78));

    sf::Sprite autoButton(menubars);
    autoButton.setTextureRect(sf::IntRect(61, 510, 74, 68));

    sf::Sprite activeUpdateIcon(menubars);
    activeUpdateIcon.setTextureRect(sf::IntRect(79, 596, 39, 39));

    sf::Sprite lightSprite(menubars);
    lightSprite.setTextureRect(sf::IntRect(666, 232, 74, 68));

    sf::Sprite notificationSprite(menubars);
    notificationSprite.setTextureRect(sf::IntRect(816, 232, 74, 68));

    sf::Sprite upgoingSprite(menubars);
    upgoingSprite.setTextureRect(sf::IntRect(666, 118, 74, 68));

    sf::Sprite downgoingSprite(menubars);
    downgoingSprite.setTextureRect(sf::IntRect(816, 118, 74, 68));

    sf::SoundBuffer buffer1;
    if (!buffer1.loadFromFile("sounds/update.wav"))
    {
        return -1;
    }
    sf::Sound updating(buffer1);

    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("sounds/systementer.wav"))
    {
        return -1;
    }
    sf::Sound systemOpen(buffer2);
    systemOpen.setVolume(50.f);

    sf::SoundBuffer buffer3;
    if (!buffer3.loadFromFile("sounds/openingdopmenu.wav"))
    {
        return -1;
    }
    sf::Sound openingDopMenu(buffer3);
    
    std::string currentText;
    std::string binanceText;
    std::string huobiText;
    std::string kukoinText;
    std::string bitmartText;
    std::string krakenText;
    std::string bybitText;
    std::string temporaryExchangforwidget;
    std::string temporaryPairforwidget;
    std::string temporarypairFrom;
    std::string temporarypairTo;
    std::string activationKey;

    std::vector<sf::Sprite> sprites(numFrames);
    std::vector<std::string> cellText(4, "");
    std::vector<std::string> currencyGetMarket;
    std::vector<std::string> apiS;
    std::vector<bool> marketsOnline;
    sf::Vector2f defaultScale = informationSprites.getScale();
    sf::Vector2f targetScale = defaultScale * 1.0250f;
    std::vector<ExchangeRate> currencyListBinanceToUSDT;
    std::vector<ExchangeRate> currencyListBinanceToBUSD;
    std::vector<ExchangeRate> currencyListHuobiToUSDT;
    std::vector<ExchangeRate> currencyListKukoinToUSDT;
    std::vector<ExchangeRate> currencyListBitMartToUSDT;
    std::vector<ExchangeRate> currencyListKrakenToUSDT;
    std::vector<ExchangeRate> currencyListByBitToUSDT;
    std::vector<Widget> widgets(7); 
    sf::Vector2f selectedIconPosition;
    std::vector<CurrencyPair> pairs;
    std::vector<std::thread> threads;
    std::vector<bool> results;
    std::vector<bool> selectedMarkets = {true, true, true, true, true, true};
    std::vector<bool> widgetSelection = { false,false, false, false, false, false, false };
    std::vector<CurrencyPair> sortedPairs;
    std::vector<std::string> currencyPairsToUSDT;
    std::vector<std::string> currencyPairsWithoutSpaceToUSDT;
    std::vector<std::string> currencyPairsWithUnterToUSDT;
    std::vector<std::string> currencyPairsWithSlashToUSDT;
    std::vector<std::string> currencyPairsSmallToUSDT;
    std::vector<std::string> currencyPairsWithoutSpaceToBUSD;

    sf::RectangleShape full;
    sf::RectangleShape leftMenubar;
    sf::RectangleShape rectmenu;
    sf::RectangleShape selectedMenu;
    sf::RectangleShape rightSaheOhneInternet;
    sf::RectangleShape rightSaheOhneInternetPlus;
    sf::RectangleShape leftBackgroundInformationUpdater;
    sf::RectangleShape settingsMarketSelectionBlack;
    sf::RectangleShape settingsRest;
    sf::RectangleShape baranimation;
    sf::RectangleShape rectmenumini;
    sf::RectangleShape rectmenuTop;
    sf::RectangleShape rectmenugrenze;
    sf::CircleShape connectionCircle;
    sf::CircleShape сircle;
    sf::RectangleShape scrollbar;
    
   
    std::thread currencyThread;

    sf::Font font;
    if (!font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf"))
    {
    }

    sf::Text text;
    text.setFont(font);

    sf::Font fontfat;
    if (!fontfat.loadFromFile("Fonts/Inter-ExtraBold.ttf"))
    {
        std::cout << "Ошибка загрузки шрифта!" << std::endl;
    }
    sf::Text textFat;
    textFat.setFont(fontfat);

    sf::Font fontlight;
    if (!fontlight.loadFromFile("Fonts/Inter-ExtraLight.ttf"))
    {
    }
    sf::Text textlight;
    textlight.setFont(fontlight);

    sf::Font fontRegular;
    if (!fontRegular.loadFromFile("Fonts/Inter-Regular.ttf"))
    {
    }
    sf::Text textRegular;
    textRegular.setFont(fontRegular);

    sf::Clock timeToUpdateCurrency;
    sf::Clock hover;
    sf::Clock clockforinvis;
    sf::Clock clock;
    sf::Clock buttonIsAvailable;
    sf::Clock clockdelta;
    sf::Clock clockAnimation;
    sf::Clock transition;
    sf::Clock TimeToAllReady;
    sf::Clock AutoupdateTimer;

    while (window.isOpen())
    {
        sf::Time deltaTime = clockdelta.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                if (currencyThread.joinable()) {
                    currencyThread.join();
                }

                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);

                if (scrollbar.getGlobalBounds().contains(mousePosition))
                {
                    isDraggingScrollbar = true;
                    dragOffset = mousePosition.y - scrollbar.getPosition().y;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                isDraggingScrollbar = false;
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (isDraggingScrollbar)
                {
                    sf::Vector2f mousePosition(event.mouseMove.x, -event.mouseMove.y);
                    scrollbar.setPosition(scrollbar.getPosition().x, mousePosition.y + dragOffset);
                    // Ограничение положения ползунка в пределах окна
                    if (scrollbar.getPosition().y < -maxScrollOffsetPolz)
                    {
                        scrollbar.setPosition(scrollbar.getPosition().x, -maxScrollOffsetPolz);
                    }
                    else if (scrollbar.getPosition().y > -minScrollOffsetPolz)
                    {
                        scrollbar.setPosition(scrollbar.getPosition().x, -minScrollOffsetPolz);
                    }

                    // Обновление scrollOffset на основе положения ползунка
                    scrollOffset = -((scrollbar.getPosition().y) * -20) +2600;
                    // Обновление позиции ползунка на основе scrollOffset
                    scrollbar.setPosition(scrollbar.getPosition().x, (scrollOffset / -20) +130);


                    if (scrollOffset < -minScrollOffset) {
                        scrollOffset = -minScrollOffset;
                        scrollbar.setPosition(scrollbar.getPosition().x, minScrollOffset / 20 + 130);
                    }


                   // std::cout << "Scrollbar Pos:  " << scrollbar.getPosition().y << std::endl;
                    //std::cout << "Scrolloffset:  " << scrollOffset << std::endl;
                    // std::cout << "Minoffset:  " << minScrollOffset << std::endl;

                }
            }
            else if (event.type == sf::Event::MouseWheelScrolled && window.hasFocus())
            {
                if (isUserInMainMenu)
                {

                    scrollOffset += event.mouseWheelScroll.delta * 10.0f;
                    if (scrollOffset < -minScrollOffset)
                    {
                        scrollOffset = -minScrollOffset;
                    }
                    else if (scrollOffset > maxScrollOffset)
                    {
                        scrollOffset = maxScrollOffset;
                    }

                    scrollbar.setPosition(scrollbar.getPosition().x, (scrollOffset / -20) + 130);

                    if (scrollbar.getPosition().y < 130.f) {
                        scrollbar.setPosition(scrollbar.getPosition().x, 130.f);
                    }
                    else if (scrollbar.getPosition().y > window.getSize().y - 170.f) {
                        scrollbar.setPosition(scrollbar.getPosition().x, window.getSize().y - 170.f);
                    }
                }
            }
            else if (scrollbar.getPosition().y < 130.f) {
                scrollbar.setPosition(scrollbar.getPosition().x, 130.f);
            }
            else if (scrollbar.getPosition().y > window.getSize().y - 170.f) {
                scrollbar.setPosition(scrollbar.getPosition().x, window.getSize().y - 170.f);
            }
        }
        //  std::cout << scrollOffset << std::endl;

        window.clear();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos);

        if (isLicenseChecked == false) {

            activateProduct(emeraldactivationbackground, emeraldbackgroundvisible, deltaTime, window, iconActivation, activationPosition, activationColor, textlight, textFat, isBackGroundVisible, schloss, 
            textcodeicons, mousePosView, CODE_BUTTON_SizeX, CODE_BUTTON_SizeY, activeCellIndex, allCellsFilled, cellText, event, textRegular, textreloadTime, buttonIsAvailable, continueButton, isActivating,
                textForLoadingDark, clockAnimation, timeSinceLastFrame, frameDuration, currentFrame, numFrames, sprites, colorWelcomeAndSchloss, elapsedFloatingTime, activationKey, requessendet, isActivated,
                isInTransitionToSetup, isInSetup, isErrorActivation, isErrorDuringActivation, targetPosX, currentPosX, speed, view, isLightTheme, isDarkTheme, iconColorDark, iconColorLight, writeplankSetup, 
                selectionSetupNo, selectionSetupYes, full, emeraldtransitiontosettingsbackground, colorbackground, blackIconSetup90grad, whiteIconSetup90grad, initialSpeedLeft, finalSpeedLeft, accelerationLeft, whiteIconSetup90grad2,
                activationPosRight, activationPosLeft, initialSpeedRight, finalSpeedRight, accelerationRight, notActiveCircle, activeCircle, textcolor, colorForBlack, colorForWhite, blackIconSetup90grad2,
                isIWantToBetaTest, isIWantToBeAnonym, selectionSetupYes2, selectionSetupNo2, emeraldkpp, time2, isLicenseChecked, readyForLoad);

        }

        else {

            if (readyForLoad == true) {

                for (size_t i = 0; i < widgets.size(); i++) {
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
                }

                for (int i = 0; i < numFrames; ++i) {
                    sprites[i].setTexture(m146);
                    sprites[i].setTextureRect(sf::IntRect(initialPositionX + i * differenceX, initialPositionY + i * differenceY, 247, 191));
                    sprites[i].setPosition(window.getSize().x / 2 - sprites[i].getGlobalBounds().width / 2 + 20, 500); // Начальная позиция для каждого спрайта
                    sprites[i].setColor(sf::Color(255, 255, 255, 150));
                }

                currencyGetMarket = { "Binance", "Huobi", "Kukoin", "BitMart", "Kraken", "ByBit" };
                apiS = { "https://api.binance.com", "https://api.huobi.pro/market/detail/merged?symbol=btcusdt", "https://api.kucoin.com/api/v1/market/orderbook/level1?symbol=BTC-EUR", "https://api-cloud.bitmart.com", "https://api.kraken.com", "https://www.okex.com" };

                currencyPairsToUSDT = {
   "ETH-USDT", "BNB-USDT", "TRX-USDT", "LTC-USDT", "XRP-USDT", "SOL-USDT", "FLUX-USDT", "NEO-USDT",
   "ADA-USDT", "AMP-USDT", "BAND-USDT", "SFP-USDT", "DOGE-USDT", "COTI-USDT", "DAI-USDT", "DASH-USDT", "ETHC-USDT",
   "GMX-USDT", "IDEX-USDT", "IRIS-USDT", "CLAY-USDT", "LINA-USDT", "MOVR-USDT", "MATIC-USDT", "RAD-USDT", "RVN-USDT",
   "SHIB-USDT", "SOLO-USDT", "STX-USDT", "TORN-USDT", "TRU-USDT", "WAVES-USDT", "WIN-USDT", "XLM-USDT", "XMR-USDT",
   "XRP-USDT", "ZEC-USDT", "ZEN-USDT", "ZRX-USDT", "1INCH-USDT", "AAVE-USDT", "ACH-USDT", "ZRX-USDT", "ACM-USDT", "ZIL-USDT", "ZEN-USDT",
   "ADA-USDT", "ZEC-USDT", "YGG-USDT", "ADX-USDT", "YFII-USDT", "YFI-USDT", "AERGO-USDT", "XVS-USDT",
   "XVG-USDT", "AGIX-USDT", "XTZ-USDT", "XRP-USDT", "AGLD-USDT", "AKRO-USDT", "XMR-USDT",
   "ALCX-USDT", "XLM-USDT", "ALGO-USDT", "ALICE-USDT", "ALPACA-USDT", "AMB-USDT", "AMP-USDT", "ANKR-USDT",
   "ANT-USDT", "APE-USDT", "API3-USDT", "APT-USDT", "ARB-USDT", "ARDR-USDT", "ARPA-USDT", "AR-USDT",
   "ASR-USDT", "ASTR-USDT", "AST-USDT", "ATA-USDT", "ATM-USDT", "ATOM-USDT", "AUCTION-USDT", "AUDIO-USDT",
   "AVA-USDT", "AVAX-USDT", "AXS-USDT", "BADGER-USDT", "BAKE-USDT", "BAL-USDT", "BAND-USDT", "BAR-USDT",
   "BAT-USDT", "BCH-USDT", "BCH-USDT", "BEL-USDT", "BETA-USDT", "BETH-USDT", "BICO-USDT",
   "BLZ-USDT", "BNB-USDT", "BNT-USDT", "BNX-USDT", "BOND-USDT", "BSW-USDT", "BTC-USDT", "BTS-USDT",
   "BTTC-USDT", "BURGER-USDT", "BUSD-USDT", "C98-USDT", "CAKE-USDT", "CELO-USDT", "CELR-USDT", "CFX-USDT",
   "CHESS-USDT", "CHR-USDT", "CHZ-USDT", "CITY-USDT", "CRV-USDT", "CTK-USDT", "CTSI-USDT", "CTXC-USDT",
   "CVC-USDT", "CVP-USDT", "CVX-USDT", "DAR-USDT", "DASH-USDT", "DATA-USDT", "DCR-USDT", "DEGO-USDT",
   "DENT-USDT", "DEXE-USDT", "DF-USDT", "DGB-USDT", "DIA-USDT", "DOCK-USDT", "DODO-USDT", "DOGE-USDT",
   "DOT-USDT", "DREP-USDT", "DUSK-USDT", "DYDX-USDT", "EDU-USDT", "EGLD-USDT", "ELF-USDT", "ENJ-USDT",
   "ENS-USDT", "EOS-USDT", "EPX-USDT", "ERN-USDT", "ETC-USDT", "ETH-USDT", "EUR-USDT", "FARM-USDT",
   "FET-USDT", "FIDA-USDT", "FIL-USDT", "FIO-USDT", "FIRO-USDT", "FIS-USDT", "FLM-USDT", "FLOKI-USDT",
   "FLOW-USDT", "FLUX-USDT", "FORTH-USDT", "FOR-USDT", "FRONT-USDT", "FTM-USDT", "FUN-USDT", "FXS-USDT",
   "GALA-USDT", "GAL-USDT", "GAS-USDT", "GBP-USDT", "GHST-USDT", "GLMR-USDT", "GLM-USDT", "GMT-USDT",
   "GMX-USDT", "GNO-USDT", "GNS-USDT", "GRT-USDT", "GTC-USDT", "XEM-USDT", "XEC-USDT", "WTC-USDT",
   "WRX-USDT", "WOO-USDT", "WNXM-USDT", "WIN-USDT", "WING-USDT", "WBTC-USDT", "WAXP-USDT", "WAVES-USDT",
   "WAN-USDT", "VTHO-USDT", "VOXEL-USDT", "VITE-USDT", "VIDT-USDT", "VIB-USDT", "VGX-USDT", "VET-USDT",
   "UTK-USDT", "USTC-USDT", "USDP-USDT", "USDC-USDT", "UNI-USDT", "UNFI-USDT", "UMA-USDT", "UFT-USDT",
   "TWT-USDT", "TVK-USDT", "TUSD-USDT", "T-USDT", "TRX-USDT", "TRU-USDT", "TROY-USDT", "TRB-USDT",
   "TOMO-USDT", "TLM-USDT", "TKO-USDT", "THETA-USDT", "TFUEL-USDT", "SYS-USDT", "SYN-USDT", "SXP-USDT",
   "SUSHI-USDT", "SUPER-USDT", "SUN-USDT", "SUI-USDT", "STX-USDT", "STRAX-USDT", "STPT-USDT", "STORJ-USDT",
   "STMX-USDT", "STG-USDT", "STEEM-USDT", "SSV-USDT", "SPELL-USDT", "SOL-USDT", "SNX-USDT", "SNT-USDT",
   "SLP-USDT", "SKL-USDT", "SHIB-USDT", "SFP-USDT", "SC-USDT", "SCRT-USDT", "SANTOS-USDT", "SAND-USDT",
   "RVN-USDT", "RUNE-USDT", "RSR-USDT", "RPL-USDT", "ROSE-USDT", "RNDR-USDT", "RLC-USDT", "RIF-USDT",
   "REQ-USDT", "REN-USDT", "REI-USDT", "REEF-USDT", "RDNT-USDT", "RAY-USDT", "RARE-USDT", "RAD-USDT",
   "QTUM-USDT", "QNT-USDT", "QKC-USDT", "QI-USDT", "PYR-USDT", "PUNDIX-USDT", "PSG-USDT",
   "PROS-USDT", "PROM-USDT", "POWR-USDT", "PORTO-USDT", "POND-USDT", "POLYX-USDT", "POLS-USDT", "PNT-USDT",
   "PLA-USDT", "PHB-USDT", "PHA-USDT", "PERP-USDT", "PERL-USDT", "PEPE-USDT", "PEOPLE-USDT", "PENDLE-USDT",
   "PAXG-USDT", "OXT-USDT", "OSMO-USDT", "ORN-USDT", "OP-USDT", "OOKI-USDT", "ONT-USDT", "ONG-USDT",
   "ONE-USDT", "OM-USDT", "OMG-USDT", "OG-USDT", "OGN-USDT", "OCEAN-USDT", "OAX-USDT", "NULS-USDT",
   "NMR-USDT", "NKN-USDT", "NEXO-USDT", "NEO-USDT", "NEAR-USDT", "MULTI-USDT", "MTL-USDT", "MOVR-USDT",
   "MOB-USDT", "MLN-USDT", "MKR-USDT", "MINA-USDT", "MDX-USDT", "MDT-USDT", "MBOX-USDT",
   "MBL-USDT", "MAV-USDT", "MATIC-USDT", "MASK-USDT", "MANA-USDT", "MAGIC-USDT", "LUNC-USDT", "LUNA-USDT",
   "LTO-USDT", "LTC-USDT", "LSK-USDT", "LRC-USDT", "LQTY-USDT", "LPT-USDT", "LOOM-USDT", "LOKA-USDT",
   "LIT-USDT", "LINK-USDT", "LINA-USDT", "LEVER-USDT"
                };

                currencyPairsWithoutSpaceToUSDT = {
                    "ETHUSDT", "BNBUSDT", "TRXUSDT", "LTCUSDT", "XRPUSDT", "SOLUSDT", "FLUXUSDT", "NEOUSDT",
                    "ADAUSDT", "AMPUSDT", "BANDUSDT", "SFPUSDT", "DOGEUSDT", "COTIUSDT", "DAIUSDT", "DASHUSDT", "ETHCUSDT",
                    "GMXUSDT", "IDEXUSDT", "IRISUSDT", "CLAYUSDT", "LINAUSDT", "MOVRUSDT", "MATICUSDT", "RADUSDT", "RVNUSDT",
                    "SHIBUSDT", "SOLOUSDT", "STXUSDT", "TORNBUSD", "TRUUSDT", "WAVESUSDT", "WINUSDT", "XLMUSDT", "XMRUSDT",
                    "XRPUSDT", "ZECUSDT", "ZENUSDT", "ZRXUSDT", "1INCHUSDT", "AAVEUSDT", "ACHUSDT", "ZRXUSDT", "ACMUSDT", "ZILUSDT", "ZENUSDT", "ADAUSDT", "ZECUSDT",
                "YGGUSDT", "ADXUSDT", "YFIIUSDT", "YFIUSDT", "AERGOUSDT", "XVSUSDT", "XVGUSDT", "AGIXUSDT", "XTZUSDT", "XRPUSDT",
                "AGLDUSDT", "AKROUSDT","XMRUSDT", "ALCXUSDT", "XLMUSDT", "ALGOUSDT", "ALICEUSDT", "ALPACAUSDT",
                "AMBUSDT", "AMPUSDT", "ANKRUSDT", "ANTUSDT", "APEUSDT", "API3USDT", "APTUSDT", "ARBUSDT", "ARDRUSDT", "ARPAUSDT",
                "ARUSDT", "ASRUSDT", "ASTRUSDT", "ASTUSDT", "ATAUSDT", "ATUSDT", "ATOMUSDT", "AUCTIONUSDT", "AUDIOUSDT", "AVAUSDT",
                "AVAXUSDT", "AXSUSDT", "BADGERUSDT", "BAKEUSDT", "BALUSDT", "BANDUSDT", "BARUSDT", "BATUSDT", "BCHUSDT", "BCHUSDT",
                "BELUSDT", "BETAUSDT", "BETHUSDT", "BICOUSDT", "BLZUSDT", "BNBUSDT", "BNTUSDT", "BNXUSDT", "BONDUSDT",
                "BSWUSDT", "BTCUSDT", "BTSUSDT", "BTTCUSDT", "BURGERUSDT", "BUSDUSDT", "C98USDT", "CAKEUSDT", "CELOUSDT", "CELRUSDT",
                "CFXUSDT", "CHESSUSDT", "CHRUSDT", "CHZUSDT", "CITYUSDT", "CRVUSDT", "CTKUSDT", "CTSIUSDT", "CTXCUSDT", "CVCUSDT",
                "CVPUSDT", "CVXUSDT", "DARUSDT", "DASHUSDT", "DATAUSDT", "DCRUSDT", "DEGOUSDT", "DENTUSDT", "DEXEUSDT", "DFUSDT",
                "DGBUSDT", "DIAUSDT", "DOCKUSDT", "DODOUSDT", "DOGEUSDT", "DOTUSDT", "DREPUSDT", "DUSKUSDT", "DYDXUSDT", "EDUUSDT",
                "EGLDUSDT", "ELFUSDT", "ENJUSDT", "ENSUSDT", "EOSUSDT", "EPXUSDT", "ERNUSDT", "ETCUSDT", "ETHUSDT", "EURUSD",
                "FARMUSDT", "FETUSDT", "FIDAUSDT", "FILUSDT", "FIOUSDT", "FIROUSDT", "FISUSDT", "FLMUSDT", "FLOKIUSDT", "FLOWUSDT",
                "FLUXUSDT", "FORTHUSDT", "FORUSDT", "FRONTUSDT4", "FTMUSDT", "FUNUSDT", "FXSUSDT", "GALAUSDT", "GALUSDT", "GASUSDT",
                "GBPUSDT", "GHSTUSDT", "GLMRUSDT", "GLMUSDT", "GMTUSDT", "GMXUSDT", "GNOUSDT", "GNSUSDT", "GRTUSDT", "GTCUSDT",
                "XEMUSDT", "XECUSDT", "WTCUSDT", "WRXUSDT", "WOOUSDT", "WNXMUSDT", "WINUSDT", "WINGUSDT", "WBTCUSDT", "WAXPUSDT",
                "WAVESUSDT", "WANUSDT", "VTHOUSDT", "VOXELUSDT", "VITEUSDT", "VIDTUSDT", "VIBUSDT", "VGXUSDT", "VETUSDT", "UTKUSDT",
                "USTCUSDT", "USDPUSDT", "USDCUSDT", "UNIUSDT", "UNFIUSDT", "UMAUSDT", "UFTUSDT", "TWTUSDT", "TVKUSDT", "TUSDUSDT",
                "TUSDT", "TRXUSDT", "TRUUSDT", "TROYUSDT", "TRBUSDT", "TOMOUSDT", "TLMUSDT", "TKOUSDT", "THETAUSDT", "TFUELUSDT",
                "SYSUSDT", "SYNUSDT", "SXPUSDT", "SUSHIUSDT", "SUPERUSDT", "SUNUSDT", "SUIUSDT", "STXUSDT", "STRAXUSDT", "STPTUSDT",
                "STORJUSDT", "STMXUSDT", "STGUSDT", "STEEMUSDT", "SSVUSDT", "SPELLUSDT", "SOLUSDT", "SNXUSDT", "SNTUSDT", "SLPUSDT",
                "SKLUSDT", "SHIBUSDT", "SFPUSDT", "SCUSDT", "SCRTUSDT", "SANTOSUSDT", "SANDUSDT", "RVNUSDT", "RUNEUSDT", "RSRUSDT",
                "RPLUSDT", "ROSEUSDT", "RNDRUSDT", "RLCUSDT", "RIFUSDT", "REQUSDT", "RENUSDT", "REIUSDT", "REEFUSDT", "RDNTUSDT",
                "RAYUSDT", "RAREUSDT", "RADUSDT",  "QTUMUSDT", "QNTUSDT", "QKCUSDT", "QIUSDT", "PYRUSDT", "PUNDIXUSDT",
                "PSGUSDT", "PROSUSDT", "PROMUSDT", "POWRUSDT", "PORTOUSDT", "PONDUSDT", "POLYXUSDT", "POLSUSDT", "PNTUSDT", "PLAUSDT",
                "PHBUSDT", "PHAUSDT", "PERPUSDT", "PERLUSDT", "PEPEUSDT", "PEOPLEUSDT", "PENDLEUSDT", "PAXGUSDT", "OXTUSDT",
                "OSMOUSDT", "ORNUSDT", "OPUSDT", "OOKIUSDT", "ONTUSDT", "ONGUSDT", "ONEUSDT", "OMUSDT", "OMGUSDT", "OGUSDT",
                "OGNUSDT", "OCEANUSDT", "OAXUSDT", "NULSUSDT", "NMRUSDT", "NKNUSDT", "NEXOUSDT", "NEOUSDT", "NEARUSDT", "MULTIUSDT",
                "MTLUSDT", "MOVRUSDT", "MOBUSDT", "MLNUSDT", "MKRUSDT", "MINAUSDT", "MDXUSDT", "MDTUSDT", "MBOXUSDT",
                "MBLUSDT", "MAVUSDT", "MATICUSDT", "MASKUSDT", "MANAUSDT", "MAGICUSDT", "LUNCUSDT", "LUNAUSDT", "LTOUSDT", "LTCUSDT",
                "LSKUSDT", "LRCUSDT", "LQTYUSDT", "LPTUSDT", "LOOMUSDT", "LOKAUSDT", "LITUSDT", "LINKUSDT", "LINAUSDT", "LEVERUSDT"

                };
                currencyPairsWithoutSpaceToBUSD = {
                "ETHBUSD", "BNBBUSD", "TRXBUSD", "LTCBUSD", "XRPBUSD", "SOLBUSD", "FLUXBUSD", "NEOBUSD",
    "ADABUSD", "AMPBUSD", "BANDBUSD", "SFPBUSD", "DOGEBUSD", "COTIBUSD", "DAIBUSD", "DASHBUSD", "ETHCBUSD",
   "GMXBUSD", "IDEXBUSD", "IRISBUSD", "CLAYBUSD", "LINABUSD", "MOVRBUSD", "MATICBUSD", "RADBUSD", "RVNBUSD",
   "SHIBBUSD", "SOLOBUSD", "STXBUSD", "TORNBUSD", "TRUBUSD", "WAVESBUSD", "WINBUSD", "XLMBUSD", "XMRBUSD",
   "XRPBUSD", "ZECBUSD", "ZENBUSD", "ZRXBUSD", "1INCHBUSD", "AAVEBUSD", "ACHBUSD", "ZRXBUSD", "ACMBUSD", "ZILBUSD", "ZENBUSD", "ADABUSD", "ZECBUSD",
   "YGGUSDT", "ADXUSDT", "YFIIBUSD", "YFIBUSD", "AERGOBUSD", "XVSBUSD", "XVGBUSD", "AGIXBUSD", "XTZBUSD", "XRPBUSD",
   "AGLDBUSD", "AKROBUSD", "XMRBUSD", "ALCXBUSD", "XLMBUSD", "ALGOBUSD", "ALICEBUSD", "ALPACABUSD",
   "AMBBUSD", "AMPBUSD", "ANKRBUSD", "ANTBUSD", "APEBUSD", "API3BUSD", "APTUSDT", "ARBBUSD", "ARDRBUSD", "ARPABUSD",
   "ARBUSD", "ASRBUSD", "ASTRBUSD", "ASTBUSD", "ATABUSD", "ATBUSD", "ATOMBUSD", "AUCTIONBUSD", "AUDIOBUSD", "AVABUSD",
   "AVAXBUSD", "AXSBUSD", "BADGERBUSD", "BAKEBUSD", "BALBUSD", "BANDBUSD", "BARBUSD", "BATBUSD", "BCHBUSD", "BCHBUSD",
   "BELBUSD", "BETABUSD", "BETHBUSD", "BICOBUSD", "BLZBUSD", "BNBBUSD", "BNTBUSD", "BNXBUSD", "BONDBUSD",
   "BSWBUSD", "BTCBUSD", "BTSBUSD", "BTTCBUSD", "BURGERBUSD", "BIDUSDT", "C98BUSD", "CAKEBUSD", "CELOBUSD", "CELREBUSD",
   "CFXBUSD", "CHESSBUSD", "CHRBUSD", "CHZBUSD", "CITYBUSD", "CRVBUSD", "CTKBUSD", "CTSIBUSD", "CTXCBUSD", "CVCBUSD",
   "CVPBUSD", "CVXBUSD", "DARBUSD", "DASHBUSD", "DATABUSD", "DCRBUSD", "DEGOBUSD", "DENTBUSD", "DEXEBUSD", "DFBUSD",
   "DGBBUSD", "DIABUSD", "DOCKBUSD", "DODOBUSD", "DOGEBUSD", "DOTBUSD", "DREPBUSD", "DUSKBUSD", "DYDXBUSD", "EDUBUSD",
   "EGLDBUSD", "ELFBUSD", "ENJBUSD", "ENSUSDT", "EOSBUSD", "EPXBUSD", "ERNBUSD", "ETCBUSD", "ETHBUSD", "EURBUSD",
   "FARMBUSD", "FETBUSD", "FIDABUSD", "FILBUSD", "FIOBUSD", "FIROBUSD", "FISBUSD", "FLMBUSD", "FLOKIBUSD", "FLOWBUSD",
   "FLUXBUSD", "FORTHBUSD", "FORBUSD", "FRONTBUSD4", "FTMBUSD", "FUNBUSD", "FXSBUSD", "GALABUSD", "GALBUSD", "GASBUSD",
   "GBPBUSD", "GHSTBUSD", "GLMRBUSD", "GLMBUSD", "GMTBUSD", "GMXBUSD", "GNOBUSD", "GNSBUSD", "GRTBUSD", "GTCBUSD",
   "XEMBUSD", "XECBUSD", "WTCBUSD", "WRXBUSD", "WOOBUSD", "WNXMBUSD", "WINBUSD", "WINGBUSD", "WBTCBUSD", "WAXPBUSD",
   "WAVESBUSD", "WANBUSD", "VTHOBUSD", "VOXELBUSD", "VITEBUSD", "VIDTBUSD", "VIBBUSD", "VGXBUSD", "VETBUSD", "UTKBUSD",
   "USTCBUSD", "USDPBUSD", "USDCCBUSD", "UNIBUSD", "UNFIBUSD", "UMABUSD", "UFTBUSD", "TWTBUSD", "TVKBUSD", "TUSDBUSD",
   "TUSDBUSD", "TRXBUSD", "TRUBUSD", "TROYBUSD", "TRBBUSD", "TOMOBUSD", "TLMBUSD", "TKOBUSD", "THETABUSD", "TFUELBUSD",
   "SYSBUSD", "SYNBUSD", "SXPBUSD", "SUSHIBUSD", "SUPERBUSD", "SUNBUSD", "SUIBUSD", "STXBUSD", "STRAXBUSD", "STPTBUSD",
   "STORJBUSD", "STMXBUSD", "STGBUSD", "STEEMBUSD", "SSVBUSD", "SPELLBUSD", "SOLBUSD", "SNXBUSD", "SNTBUSD", "SLPBUSD",
   "SKLBUSD", "SHIBBUSD", "SFPBUSD", "SCBUSD", "SCRIBUSD", "SANTOSBUSD", "SANDBUSD", "RVNBUSD", "RUNEBUSD", "RSRBUSD",
   "RPLUSBUSD", "ROSEBUSD", "RNDRBUSD", "RLCBUSD", "RIFBUSD", "REQBUSD", "RENBUSD", "REIBUSD", "REEFBUSD", "RDNTBUSD",
   "RAYBUSD", "RAREBUSD", "RADBUSD",  "QTUMBUSD", "QNTBUSD", "QKCBUSD", "QIBUSD", "PYRBUSD", "PUNDIXBUSD",
   "PSGBUSD", "PROSBUSD", "PROMBUSD", "POWRBUSD", "PORTOBUSD", "PONDBUSD", "POLYXBUSD", "POLSBUSD", "PNTBUSD", "PLABUSD",
   "PHBBUSD", "PHABUSD", "PERPBUSD", "PERLBUSD", "PEPEBUSD", "PEOPLEBUSD", "PENDLEBUSD", "PAXGBUSD", "OXTBUSD",
   "OSMOBUSD", "ORNBUSD", "OPBUSD", "OOKIBUSD", "ONTBUSD", "ONGBUSD", "ONEBUSD", "OMBUSD", "OMGBUSD", "OGBUSD",
   "OGNBUSD", "OCEANBUSD", "OAXBUSD", "NULSBUSD", "NMRBUSD", "NKNBUSD", "NEXOBUSD", "NEOBUSD", "NEARBUSD", "MULTIBUSD",
   "MTLBUSD", "MOVRBUSD", "MOBBUSD", "MLNBUSD", "MKRBUSD", "MINABUSD", "MDXBUSD", "MDTBUSD", "MBOXBUSD",
   "MBLBUSD", "MAVBUSD", "MATICBUSD", "MASKBUSD", "MANABUSD", "MAGICBUSD", "LUNCBUSD", "LUNABUSD", "LTOBUSD", "LTCBUSD",
   "LSKBUSD", "LRCBUSD", "LQTYBUSD", "LPTBUSD", "LOOMBUSD", "LOKABUSD", "LITBUSD", "LINKBUSD", "LINABUSD", "LEVERBUSD"
                };

                currencyPairsWithUnterToUSDT = {
                   "ETH_USDT", "BNB_USDT", "TRX_USDT", "LTC_USDT", "XRP_USDT", "SOL_USDT", "FLUX_USDT", "NEO_USDT",
                   "ADA_USDT", "AMP_USDT", "BAND_USDT", "SFP_USDT", "DOGE_USDT", "COTI_USDT", "DAI_USDT", "DASH_USDT", "ETHC_USDT",
                   "GMX_USDT", "IDEX_USDT", "IRIS_USDT", "CLAY_USDT", "LINA_USDT", "MOVR_USDT", "MATIC_USDT", "RAD_USDT", "RVN_USDT",
                   "SHIB_USDT", "SOLO_USDT", "STX_USDT", "TORN_USDT", "TRU_USDT", "WAVES_USDT", "WIN_USDT", "XLM_USDT", "XMR_USDT",
                   "XRP_USDT", "ZEC_USDT", "ZEN_USDT", "ZRX_USDT",   "1INCH_USDT", "AAVE_USDT", "ACH_USDT", "ZRX_USDT", "ACM_USDT", "ZIL_USDT", "ZEN_USDT", "ADA_USDT", "ZEC_USDT",
                "YGG_USDT", "ADX_USDT", "YFII_USDT", "YFI_USDT", "AERGO_USDT", "XVS_USDT", "XVG_USDT", "AGIX_USDT", "XTZ_USDT", "XRP_USDT",
                "AGLD_USDT", "AKRO_USDT", "XMR_USDT", "ALCX_USDT", "XLM_USDT", "ALGO_USDT", "ALICE_USDT", "ALPACA_USDT", "AMB_USDT",
                "AMP_USDT", "ANKR_USDT", "ANT_USDT", "APE_USDT", "API3_USDT", "APT_USDT", "ARB_USDT", "ARDR_USDT", "ARPA_USDT", "AR_USDT",
                "ASR_USDT", "ASTR_USDT", "AST_USDT", "ATA_USDT", "ATM_USDT", "ATOM_USDT", "AUCTION_USDT", "AUDIO_USDT", "AVA_USDT", "AVAX_USDT",
                "AXS_USDT", "BADGER_USDT", "BAKE_USDT", "BAL_USDT", "BAND_USDT", "BAR_USDT", "BAT_USDT", "BCH_USDT", "BCH_USDT", "BEL_USDT",
                "BETA_USDT", "BETH_USDT", "BICO_USDT", "BLZ_USDT", "BNB_USDT", "BNT_USDT", "BNX_USDT", "BOND_USDT", "BSW_USDT",
                "BTC_USDT", "BTS_USDT", "BTTC_USDT", "BURGER_USDT", "BUSD_USDT", "C98_USDT", "CAKE_USDT", "CELO_USDT", "CELR_USDT", "CFX_USDT",
                "CHESS_USDT", "CHR_USDT", "CHZ_USDT", "CITY_USDT", "CRV_USDT", "CTK_USDT", "CTSI_USDT", "CTXC_USDT", "CVC_USDT", "CVP_USDT",
                "CVX_USDT", "DAR_USDT", "DASH_USDT", "DATA_USDT", "DCR_USDT", "DEGO_USDT", "DENT_USDT", "DEXE_USDT", "DF_USDT", "DGB_USDT",
                "DIA_USDT", "DOCK_USDT", "DODO_USDT", "DOGE_USDT", "DOT_USDT", "DREP_USDT", "DUSK_USDT", "DYDX_USDT", "EDU_USDT", "EGLD_USDT",
                "ELF_USDT", "ENJ_USDT", "ENS_USDT", "EOS_USDT", "EPX_USDT", "ERN_USDT", "ETC_USDT", "ETH_USDT", "EUR_USD", "FARM_USDT",
                "FET_USDT", "FIDA_USDT", "FIL_USDT", "FIO_USDT", "FIRO_USDT", "FIS_USDT", "FLM_USDT", "FLOKI_USDT", "FLOW_USDT", "FLUX_USDT",
                "FORTH_USDT", "FOR_USDT", "FRONT_USDT", "FTM_USDT", "FUN_USDT", "FXS_USDT", "GALA_USDT", "GAL_USDT", "GAS_USDT", "GBP_USDT",
                "GHST_USDT", "GLMR_USDT", "GLM_USDT", "GMT_USDT", "GMX_USDT", "GNO_USDT", "GNS_USDT", "GRT_USDT", "GTC_USDT", "XEM_USDT",
                "XEC_USDT", "WTC_USDT", "WRX_USDT", "WOO_USDT", "WNXM_USDT", "WIN_USDT", "WING_USDT", "WBTC_USDT", "WAXP_USDT", "WAVES_USDT",
                "WAN_USDT", "VTHO_USDT", "VOXEL_USDT", "VITE_USDT", "VIDT_USDT", "VIB_USDT", "VGX_USDT", "VET_USDT", "UTK_USDT", "USTC_USDT",
                "USDP_USDT", "USDC_USDT", "UNI_USDT", "UNFI_USDT", "UMA_USDT", "UFT_USDT", "TWT_USDT", "TVK_USDT", "TUSD_USDT", "T_USDT",
                "TRX_USDT", "TRU_USDT", "TROY_USDT", "TRB_USDT", "TOMO_USDT", "TLM_USDT", "TKO_USDT", "THETA_USDT", "TFUEL_USDT", "SYS_USDT",
                "SYN_USDT", "SXP_USDT", "SUSHI_USDT", "SUPER_USDT", "SUN_USDT", "SUI_USDT", "STX_USDT", "STRAX_USDT", "STPT_USDT", "STORJ_USDT",
                "STMX_USDT", "STG_USDT", "STEEM_USDT", "SSV_USDT", "SPELL_USDT", "SOL_USDT", "SNX_USDT", "SNT_USDT", "SLP_USDT", "SKL_USDT",
                "SHIB_USDT", "SFP_USDT", "SC_USDT", "SCRT_USDT", "SANTOS_USDT", "SAND_USDT", "RVN_USDT", "RUNE_USDT", "RSR_USDT", "RPL_USDT",
                "ROSE_USDT", "RNDR_USDT", "RLC_USDT", "RIF_USDT", "REQ_USDT", "REN_USDT", "REI_USDT", "REEF_USDT", "RDNT_USDT", "RAY_USDT",
                "RARE_USDT", "RAD_USDT","QTUM_USDT", "QNT_USDT", "QKC_USDT", "QI_USDT", "PYR_USDT", "PUNDIX_USDT", "PSG_USDT",
                "PROS_USDT", "PROM_USDT", "POWR_USDT", "PORTO_USDT", "POND_USDT", "POLYX_USDT", "POLS_USDT", "PNT_USDT", "PLA_USDT", "PHB_USDT",
                "PHA_USDT", "PERP_USDT", "PERL_USDT", "PEPE_USDT", "PEOPLE_USDT", "PENDLE_USDT", "PAXG_USDT", "OXT_USDT", "OSMO_USDT", "ORN_USDT",
                "OP_USDT", "OOKI_USDT", "ONT_USDT", "ONG_USDT", "ONE_USDT", "OM_USDT", "OMG_USDT", "OG_USDT", "OGN_USDT", "OCEAN_USDT", "OAX_USDT",
                "NULS_USDT", "NMR_USDT", "NKN_USDT", "NEXO_USDT", "NEO_USDT", "NEAR_USDT", "MULTI_USDT", "MTL_USDT", "MOVR_USDT", "MOB_USDT",
                "MLN_USDT", "MKR_USDT", "MINA_USDT", "MDX_USDT", "MDT_USDT", "MBOX_USDT", "MBL_USDT", "MAV_USDT", "MATIC_USDT",
                "MASK_USDT", "MANA_USDT", "MAGIC_USDT", "LUNC_USDT", "LUNA_USDT", "LTO_USDT", "LTC_USDT", "LSK_USDT", "LRC_USDT", "LQTY_USDT",
                "LPT_USDT", "LOOM_USDT", "LOKA_USDT", "LIT_USDT", "LINK_USDT", "LINA_USDT", "LEVER_USDT"
                };

                currencyPairsWithSlashToUSDT = {
                    "ETH/USDT", "BNB/USDT", "TRX/USDT", "LTC/USDT", "XRP/USDT", "SOL/USDT", "FLUX/USDT", "NEO/USDT",
                    "ADA/USDT", "AMP/USDT", "BAND/USDT", "SFP/USDT", "DOGE/USDT", "COTI/USDT", "DAI/USDT", "DASH/USDT", "ETHC/USDT",
                    "GMX/USDT", "IDEX/USDT", "IRIS/USDT", "CLAY/USDT", "LINA/USDT", "MOVR/USDT", "MATIC/USDT", "RAD/USDT", "RVN/USDT",
                    "SHIB/USDT", "SOLO/USDT", "STX/USDT", "TORN/USDT", "TRU/USDT", "WAVE/SUSDT", "WINU/SDT", "XLM/USDT", "XMR/USDT",
                    "XRP/USDT", "ZEC/USDT", "ZEN/USDT", "ZRX/USDT", "1INCH/USDT", "AAVE/USDT", "ACH/USDT", "ZRX/USDT", "ACM/USDT", "ZIL/USDT", "ZEN/USDT", "ADA/USDT", "ZEC/USDT",
                "YGG/USDT", "ADX/USDT", "YFII/USDT", "YFI/USDT", "AERGO/USDT", "XVS/USDT", "XVG/USDT", "AGIX/USDT", "XTZ/USDT", "XRP/USDT",
                "AGLD/USDT", "AKRO/USDT",  "XMR/USDT", "ALCX/USDT", "XLM/USDT", "ALGO/USDT", "ALICE/USDT", "ALPACA/USDT", "AMB/USDT",
                "AMP/USDT", "ANKR/USDT", "ANT/USDT", "APE/USDT", "API3/USDT", "APT/USDT", "ARB/USDT", "ARDR/USDT", "ARPA/USDT", "AR/USDT",
                "ASR/USDT", "ASTR/USDT", "AST/USDT", "ATA/USDT", "ATM/USDT", "ATOM/USDT", "AUCTION/USDT", "AUDIO/USDT", "AVA/USDT", "AVAX/USDT",
                "AXS/USDT", "BADGER/USDT", "BAKE/USDT", "BAL/USDT", "BAND/USDT", "BAR/USDT", "BAT/USDT", "BCH/USDT", "BCH/USDT", "BEL/USDT",
                "BETA/USDT", "BETH/USDT", "BICO/USDT", "BLZ/USDT", "BNB/USDT", "BNT/USDT", "BNX/USDT", "BOND/USDT", "BSW/USDT",
                "BTC/USDT", "BTS/USDT", "BTTC/USDT", "BURGER/USDT", "BUSD/USDT", "C98/USDT", "CAKE/USDT", "CELO/USDT", "CELR/USDT", "CFX/USDT",
                "CHESS/USDT", "CHR/USDT", "CHZ/USDT", "CITY/USDT", "CRV/USDT", "CTK/USDT", "CTSI/USDT", "CTXC/USDT", "CVC/USDT", "CVP/USDT",
                "CVX/USDT", "DAR/USDT", "DASH/USDT", "DATA/USDT", "DCR/USDT", "DEGO/USDT", "DENT/USDT", "DEXE/USDT", "DF/USDT", "DGB/USDT",
                "DIA/USDT", "DOCK/USDT", "DODO/USDT", "DOGE/USDT", "DOT/USDT", "DREP/USDT", "DUSK/USDT", "DYDX/USDT", "EDU/USDT", "EGLD/USDT",
                "ELF/USDT", "ENJ/USDT", "ENS/USDT", "EOS/USDT", "EPX/USDT", "ERN/USDT", "ETC/USDT", "ETH/USDT", "EUR/USD", "FARM/USDT",
                "FET/USDT", "FIDA/USDT", "FIL/USDT", "FIO/USDT", "FIRO/USDT", "FIS/USDT", "FLM/USDT", "FLOKI/USDT", "FLOW/USDT", "FLUX/USDT",
                "FORTH/USDT", "FOR/USDT", "FRONT/USDT", "FTM/USDT", "FUN/USDT", "FXS/USDT", "GALA/USDT", "GAL/USDT", "GAS/USDT", "GBP/USDT",
                "GHST/USDT", "GLMR/USDT", "GLM/USDT", "GMT/USDT", "GMX/USDT", "GNO/USDT", "GNS/USDT", "GRT/USDT", "GTC/USDT", "XEM/USDT",
                "XEC/USDT", "WTC/USDT", "WRX/USDT", "WOO/USDT", "WNXM/USDT", "WIN/USDT", "WING/USDT", "WBTC/USDT", "WAXP/USDT", "WAVES/USDT",
                "WAN/USDT", "VTHO/USDT", "VOXEL/USDT", "VITE/USDT", "VIDT/USDT", "VIB/USDT", "VGX/USDT", "VET/USDT", "UTK/USDT", "USTC/USDT",
                "USDP/USDT", "USDC/USDT", "UNI/USDT", "UNFI/USDT", "UMA/USDT", "UFT/USDT", "TWT/USDT", "TVK/USDT", "TUSD/USDT", "T/USDT",
                "TRX/USDT", "TRU/USDT", "TROY/USDT", "TRB/USDT", "TOMO/USDT", "TLM/USDT", "TKO/USDT", "THETA/USDT", "TFUEL/USDT", "SYS/USDT",
                "SYN/USDT", "SXP/USDT", "SUSHI/USDT", "SUPER/USDT", "SUN/USDT", "SUI/USDT", "STX/USDT", "STRAX/USDT", "STPT/USDT", "STORJ/USDT",
                "STMX/USDT", "STG/USDT", "STEEM/USDT", "SSV/USDT", "SPELL/USDT", "SOL/USDT", "SNX/USDT", "SNT/USDT", "SLP/USDT", "SKL/USDT",
                "SHIB/USDT", "SFP/USDT", "SC/USDT", "SCRT/USDT", "SANTOS/USDT", "SAND/USDT", "RVN/USDT", "RUNE/USDT", "RSR/USDT", "RPL/USDT",
                "ROSE/USDT", "RNDR/USDT", "RLC/USDT", "RIF/USDT", "REQ/USDT", "REN/USDT", "REI/USDT", "REEF/USDT", "RDNT/USDT", "RAY/USDT",
                "RARE/USDT", "RAD/USDT",  "QTUM/USDT", "QNT/USDT", "QKC/USDT", "QI/USDT", "PYR/USDT", "PUNDIX/USDT", "PSG/USDT",
                "PROS/USDT", "PROM/USDT", "POWR/USDT", "PORTO/USDT", "POND/USDT", "POLYX/USDT", "POLS/USDT", "PNT/USDT", "PLA/USDT", "PHB/USDT",
                "PHA/USDT", "PERP/USDT", "PERL/USDT", "PEPE/USDT", "PEOPLE/USDT", "PENDLE/USDT", "PAXG/USDT", "OXT/USDT", "OSMO/USDT", "ORN/USDT",
                "OP/USDT", "OOKI/USDT", "ONT/USDT", "ONG/USDT", "ONE/USDT", "OM/USDT", "OMG/USDT", "OG/USDT", "OGN/USDT", "OCEAN/USDT", "OAX/USDT",
                "NULS/USDT", "NMR/USDT", "NKN/USDT", "NEXO/USDT", "NEO/USDT", "NEAR/USDT", "MULTI/USDT", "MTL/USDT", "MOVR/USDT", "MOB/USDT",
                "MLN/USDT", "MKR/USDT", "MINA/USDT", "MDX/USDT", "MDT/USDT", "MBOX/USDT", "MBL/USDT", "MAV/USDT", "MATIC/USDT",
                "MASK/USDT", "MANA/USDT", "MAGIC/USDT", "LUNC/USDT", "LUNA/USDT", "LTO/USDT", "LTC/USDT", "LSK/USDT", "LRC/USDT", "LQTY/USDT",
                "LPT/USDT", "LOOM/USDT", "LOKA/USDT", "LIT/USDT", "LINK/USDT", "LINA/USDT", "LEVER/USDT"
                };

                currencyPairsSmallToUSDT = {
                "ethusdt", "bnbusdt", "trxusdt", "ltcusdt", "xrpusdt", "solusdt", "fluxusdt", "neousdt",
                "adausdt", "ampusdt", "bandusdt", "sfpusdt", "dogeusdt", "cotiusdt", "daiusdt", "dashusdt", "ethcusdt",
                "gmxusdt", "idexusdt", "irisusdt", "clayusdt", "linausdt", "movrusdt", "maticusdt", "radusdt", "rvnusdt",
                "shibusdt", "solousdt", "stxusdt", "tornusdt", "truusdt", "wavesusdt", "winusdt", "xlmusdt", "xmrusdt",
                "xrpusdt", "zecusdt", "zenusdt", "zrxusdt", "1inchusdt", "aveusdt",  "achusdt", "zrxusdt", "acmusdt", "zilusdt", "zenusdt", "adausdt", "zecusdt",
                "yggusdt", "adxusdt", "yfiiusdt", "yfiusdt", "aergousdt", "xvsusdt", "xvgusdt", "agixusdt", "xtzusdt", "xrpusdt",
                "agldusdt", "akrousdt", "xmrusdt", "alcxusdt", "xlmusdt", "algousdt", "aliceusdt", "alpacausdt", "ambusdt",
                "ampusdt", "ankrusdt", "antusdt", "apeusdt", "api3usdt", "aptusdt", "arbusdt", "ardrusdt", "arpausdt", "arusdt",
                "asrusdt", "astrusdt", "astusdt", "atausdt", "atmusdt", "atomusdt", "auctionusdt", "audiousdt", "avausdt", "avaxusdt",
                "axsusdt", "badgerusdt", "bakeusdt", "balusdt", "bandusdt", "barusdt", "batusdt", "bchusdt", "bchusdt", "belusdt",
                "betausdt", "bethusdt", "bicousdt", "blzusdt", "bnbusdt", "bntusdt", "bnxusdt", "bondusdt", "bswusdt",
                "btcusdt", "btsusdt", "bttcusdt", "burgerusdt", "busdusdt", "c98usdt", "cakeusdt", "celousdt", "celrusdt", "cfxusdt",
                "chessusdt", "chrusdt", "chzusdt", "cityusdt", "crvusdt", "ctkusdt", "ctsiusdt", "ctxcusdt", "cvcusdt", "cvpusdt",
                "cvxusdt", "darusdt", "dashusdt", "datausdt", "dcrusdt", "degousdt", "dentusdt", "dexeusdt", "dfusdt", "dgbusdt",
                "diausdt", "dockusdt", "dodousdt", "dogeusdt", "dotusdt", "drepusdt", "duskusdt", "dydxusdt", "edusdt", "egldusdt",
                "elfusdt", "enjusdt", "ensusdt", "eosusdt", "epxusdt", "ernusdt", "etcusdt", "ethusdt", "eurusdt", "farmusdt",
                "fetusdt", "fidausdt", "filusdt", "fiousdt", "firousdt", "fisusdt", "flmusdt", "flokiusdt", "flowusdt", "fluxusdt",
                "forthusdt", "forusdt", "frontusdt", "ftmusdt", "funusdt", "fxsusdt", "galausdt", "galusdt", "gasusdt", "gbpusdt",
                "ghstusdt", "glmrusdt", "glmusdt", "gmtusdt", "gmxusdt", "gnousdt", "gnsusdt", "grtusdt", "gtcusdt", "xemusdt",
                "xecusdt", "wtcusdt", "wrxusdt", "woousdt", "wnxmusdt", "winusdt", "wingusdt", "wbtcusdt", "waxpusdt", "wavesusdt",
                "wanusdt", "vthousdt", "voxelusdt", "viteusdt", "vidtusdt", "vibusdt", "vgxusdt", "vetusdt", "utkusdt", "ustcusdt",
                "usdpusdt", "usdcusdt", "uniusdt", "unfiusdt", "umausdt", "uftusdt", "twtusdt", "tvkusdt", "tusdusdt", "tusdtusdt",
                "trxusdt", "truusdt", "troyusdt", "trbusdt", "tomousdt", "tlmusdt", "tkousdt", "thetausdt", "tfuelusdt", "sysusdt",
                "synusdt", "sxpusdt", "sushiusdt", "superusdt", "sunusdt", "suiusdt", "stxusdt", "straxusdt", "stptusdt", "storjusdt",
                "stmxusdt", "stgusdt", "steemusdt", "ssvusdt", "spellusdt", "solusdt", "snxusdt", "sntusdt", "slpusdt", "sklusdt",
                "shibusdt", "sfpusdt", "scusdt", "scrtusdt", "santosusdt", "sandusdt", "rvnusdt", "runeusdt", "rsrusdt", "rplusdt",
                "roseusdt", "rndrusdt", "rlcusdt", "rifusdt", "requsdt", "renusdt", "reiusdt", "reefusdt", "rdntusdt", "rayusdt",
                "rareusdt", "radusdt", "qtumusdt", "qntusdt", "qkcusdt", "qiusdt", "pyrusdt", "pundixusdt", "psgusdt",
                "prosusdt", "promusdt", "powrusdt", "portousdt", "pondusdt", "polyxusdt", "polsusdt", "pntusdt", "plausdt", "phbusdt",
                "phausdt", "perpusdt", "perlusdt", "pepeusdt", "peopleusdt", "pendleusdt", "paxgusdt", "oxtusdt", "osmousdt", "ornusdt",
                "opusdt", "ookiusdt", "ontusdt", "ongusdt", "oneusdt", "omusdt", "omgusdt", "ogusdt", "ognusdt", "oceanusdt", "oaxusdt",
                "nulsusdt", "nmrusdt", "nknusdt", "nexousdt", "neousdt", "nearusdt", "multiusdt", "mtlusdt", "movrusdt", "mobusdt",
                "mlnusdt", "mkrusdt", "minausdt", "mdxusdt", "mdtusdt",  "mboxusdt", "mblusdt", "mavusdt", "maticusdt",
                "maskusdt", "manausdt", "magicusdt", "luncusdt", "lunausdt", "ltousdt", "ltcusdt", "lskusdt", "lrcusdt", "lqtyusdt",
                "lptusdt", "loomusdt", "lokusdt", "litusdt", "linkusdt", "linausdt", "leverusdt"
                };

                std::cout << currencyPairsToUSDT.size() << std::endl;
                std::cout << currencyPairsSmallToUSDT.size() << std::endl;
                std::cout << currencyPairsWithSlashToUSDT.size() << std::endl;
                std::cout << currencyPairsWithUnterToUSDT.size() << std::endl;
                std::cout << currencyPairsWithoutSpaceToUSDT.size() << std::endl;
                std::cout << currencyPairsWithoutSpaceToBUSD.size() << std::endl;


                currencyListBinanceToUSDT.reserve(5000);
                currencyListBinanceToBUSD.reserve(5000);
                currencyListHuobiToUSDT.reserve(5000);
                currencyListKukoinToUSDT.reserve(5000);
                currencyListBitMartToUSDT.reserve(5000);
                currencyListKrakenToUSDT.reserve(5000);
                currencyListByBitToUSDT.reserve(5000);

                full.setSize(sf::Vector2f(modeForViewWidth, modeForViewHeight));
                leftMenubar.setSize(sf::Vector2f(modeForViewWidth / 15, desktopMode.height));
                rectmenu.setSize(sf::Vector2f(0, 0));
                selectedMenu.setSize(sf::Vector2f(modeForViewWidth / 15, 94));
                rightSaheOhneInternet.setSize(sf::Vector2f(modeForViewWidth / 3.5f, modeForViewHeight));
                rightSaheOhneInternetPlus.setSize(sf::Vector2f(30, modeForViewHeight));
                leftBackgroundInformationUpdater.setSize(sf::Vector2f(modeForViewWidth / 3.2f, desktopMode.height));
                settingsMarketSelectionBlack.setSize(sf::Vector2f(1, 1)); settingsMarketSelectionBlack.setFillColor(sf::Color(15, 15, 15, 0));
                settingsRest.setSize(sf::Vector2f(1, 1)); settingsRest.setFillColor(sf::Color(117, 117, 117, 0));
                baranimation.setSize(sf::Vector2f(650, 65)); baranimation.setFillColor(sf::Color(130, 130, 130, 255));
                rectmenumini.setSize(sf::Vector2f(500, 800));
                rectmenumini.setFillColor(sf::Color(37, 37, 37, 255));
                rectmenuTop.setSize(sf::Vector2f(500, 80));
                rectmenuTop.setFillColor(sf::Color(57, 57, 57, 255));
                rectmenugrenze.setSize(sf::Vector2f(500, 5));
                rectmenugrenze.setFillColor(sf::Color(0, 0, 0, 255));
                connectionCircle.setRadius(20.f);
                scrollbar.setSize(sf::Vector2f(20, 50)); scrollbar.setPosition(sf::Vector2f(1650, 130));
                scrollbar.setFillColor(sf::Color(0, 255, 209, 255));
                scrollbarfield.setPosition(1633.5, 105);

                readyForLoad = false;
            }
        }

            if (readyForLoad == false && isLicenseChecked == true) {

                if (iWouldLikeToUpdate) {
                    std::fstream updateSumToTrade("config/yourSum.txt", std::ios::in);
                    if (updateSumToTrade.is_open()) {
                        std::string savedinfo1;
                        std::getline(updateSumToTrade >> std::ws, savedinfo1);
                        if (savedinfo1 != "") {
                            tradeSum = std::stoi(savedinfo1);
                            currentText = savedinfo1;
                        }
                        else { tradeSum = 1; currentText = "1"; }
                    }

                    updateSumToTrade.close();
                    // Для comissionBinance:
                    std::fstream updateComissionBinance("config/commissionBinance.txt", std::ios::in);
                    if (updateComissionBinance.is_open()) {
                        std::string savedinfo2;
                        std::getline(updateComissionBinance >> std::ws, savedinfo2);
                        if (!savedinfo2.empty()) {
                            try {
                                comissionBinance = std::stod(savedinfo2) / 1000.0;
                                binanceText = savedinfo2;
                            }
                            catch (const std::exception& e) {
                                comissionBinance = 0.01;
                                binanceText = "1";
                            }
                        }
                        else {
                            comissionBinance = 0.01;
                            binanceText = "1";
                        }
                    }
                    updateComissionBinance.close();

                    // Для comissionKukoin:
                    std::fstream updateComissionKukoin("config/commissionKukoin.txt", std::ios::in);
                    if (updateComissionKukoin.is_open()) {
                        std::string savedinfo3;
                        std::getline(updateComissionKukoin >> std::ws, savedinfo3);
                        if (!savedinfo3.empty()) {
                            try {
                                comissionKukoin = std::stod(savedinfo3) / 1000.0;
                                kukoinText = savedinfo3;
                            }
                            catch (const std::exception& e) {
                                comissionKukoin = 0.01;
                                kukoinText = "1";
                            }
                        }
                        else {
                            comissionKukoin = 0.01;
                            kukoinText = "1";
                        }
                    }
                    updateComissionKukoin.close();

                    // Для comissionBitmart:
                    std::fstream updateComissionBitMart("config/commissionBitMart.txt", std::ios::in);
                    if (updateComissionBitMart.is_open()) {
                        std::string savedinfo4;
                        std::getline(updateComissionBitMart >> std::ws, savedinfo4);
                        if (!savedinfo4.empty()) {
                            try {
                                comissionBitmart = std::stod(savedinfo4) / 1000.0;
                                bitmartText = savedinfo4;
                            }
                            catch (const std::exception& e) {
                                comissionBitmart = 0.01;
                                bitmartText = "1";
                            }
                        }
                        else {
                            comissionBitmart = 0.01;
                            bitmartText = "1";
                        }
                    }
                    updateComissionBitMart.close();

                    // Для comissionKraken:
                    std::fstream updateComissionKraken("config/commissionKraken.txt", std::ios::in);
                    if (updateComissionKraken.is_open()) {
                        std::string savedinfo5;
                        std::getline(updateComissionKraken >> std::ws, savedinfo5);
                        if (!savedinfo5.empty()) {
                            try {
                                comissionKraken = std::stod(savedinfo5) / 1000.0;
                                krakenText = savedinfo5;
                            }
                            catch (const std::exception& e) {
                                comissionKraken = 0.01;
                                krakenText = "1";
                            }
                        }
                        else {
                            comissionKraken = 0.01;
                            krakenText = "1";
                        }
                    }
                    updateComissionKraken.close();

                    // Для comissionOkx:
                    std::fstream updateComissionOKX("config/commissionOKX.txt", std::ios::in);
                    if (updateComissionOKX.is_open()) {
                        std::string savedinfo6;
                        std::getline(updateComissionOKX >> std::ws, savedinfo6);
                        if (!savedinfo6.empty()) {
                            try {
                                comissionByBit = std::stod(savedinfo6) / 1000.0;
                                bybitText = savedinfo6;
                            }
                            catch (const std::exception& e) {
                                comissionByBit = 0.01;
                                bybitText = "1";
                            }
                        }
                        else {
                            comissionByBit = 0.01;
                            bybitText = "1";
                        }
                    }
                    updateComissionOKX.close();

                    // Для comissionHuobi:
                    std::fstream updateComissionHuobi("config/commissionHuobi.txt", std::ios::in);
                    if (updateComissionHuobi.is_open()) {
                        std::string savedinfo7;
                        std::getline(updateComissionHuobi >> std::ws, savedinfo7);
                        if (!savedinfo7.empty()) {
                            try {
                                comissionHuobi = std::stod(savedinfo7) / 1000.0;
                                huobiText = savedinfo7;
                            }
                            catch (const std::exception& e) {
                                comissionHuobi = 0.01;
                                huobiText = "1";
                            }
                        }
                        else {
                            comissionHuobi = 0.01;
                            huobiText = "1";
                        }
                    }

                    updateComissionHuobi.close();
                    std::cout << "Binance Comission: " << comissionBinance << std::endl;
                    std::cout << "Huobi Comission: " << comissionHuobi << std::endl;
                    std::cout << "Kukoin Comission: " << comissionKukoin << std::endl;
                    std::cout << "Bitmart Comission: " << comissionBitmart << std::endl;
                    std::cout << "Kraken Comission: " << comissionKraken << std::endl;
                    std::cout << "BitMart Comission: " << comissionByBit << std::endl;
                    iWouldLikeToUpdate = false;
                }


                /* if (timetoretryconnection.getElapsedTime().asSeconds() > retryconnection || jatolkozashelhahah) {
                    if (IsInternetConnected()) { connectedToTheInternet = true; }
                    else { connectedToTheInternet = false; }
                    timetoretryconnection.restart();
                }
                */


                if (jatolkozashelhahah) {
                    jatolkozashelhahah = false;
                    pruffInternetConnection(window, full, rightSaheOhneInternet, rightSaheOhneInternetPlus, isInternetPruft, marketsOnline, currencyGetMarket, temp, apiS, jatolkozashelhahah, text, threads, results, connectedToTheInternet);
                    systemOpen.play();

                }

                if (isUserInMainMenu && connectedToTheInternet && !isSmallWindowActivated && !drawSmallMenu) {
                    full.setFillColor(sf::Color(colorbackground, colorbackground, colorbackground, 255));
                    window.draw(full);
                    drawPairs(pairs, window, scrollOffset, openedBlockIndex, isBlockOpen, animationDuration, maxAlpha, clockforinvis, minScrollOffset, openingDopMenu, isCurrencyCalculated, sortedPairs, icons, widgetSelection, iconBonusSmallSelection, iconBonusBigSelection, iconBonusSmall, iconBonusBig, baranimation, sizeAnimationBarX, sizeAnimationBarY, isiconselected,
                        iconscolor, selectedIconPosition, isTransitionToSmallReady, deltaTime, сircle, drawCirlceBool, exiticon, iconvisability, temporaryExchangforwidget, temporaryPairforwidget, isOverWidget, temporaryfrom, temporaryto, tradeSum, comissionBinance, comissionHuobi, comissionKukoin, comissionBitmart, comissionKraken, comissionByBit, temporarypairFrom, temporarypairTo, widgets, updatewidgets);
                    window.draw(scrollbarfield);
                    window.draw(scrollbar);

                }

                if (connectedToTheInternet && isInternetPruft && !isSmallWindowActivated && !drawSmallMenu) {
                    if (isMainMenuOpened) {
                        drawMainMenu(window, full, leftMenubar, menubars, isUserInMainMenu, isUserInSettingsMenu, selectedMenu, scrollOffset, rightSaheOhneInternetPlus, isUpdaterBesetz, leftBackgroundInformationUpdater, isReadyForNewUpdate, buttonRotation, openingDopMenu, isUserInSettings,
                            isBinanceActive, isHuobiActive, isKukoinActive, isBitMartActive, isKrakenActive, isByBitActive, isTransitionToSettingsOver, isTransitionToMainOver, settingsMarketSelectionBlack, positionBlackSettings, settingsRest, settingsmainboard, isInTransition,
                            colorrest, colorleftsettings, currencyGetMarket, selectedMarkets, mousePosView, buttonIsAvailable, buttonreloadTime, isInputActive, event, currentText, textreloadTime, iWouldLikeToUpdate, colorselected, colorDirection, binanceText, huobiText, kukoinText, bitmartText,
                            krakenText, bybitText, smallWindowOpened, isSmallWindowActivated, isSmallWindowActiv, button1Sprite, button2Sprite, button3Sprite, button4Sprite, leftmenubarSprite, autoButton, autoUpdate, deltaTime, lightSprite, notificationSprite, isLightTheme, isDarkTheme);
                    }

                }

                if (autoUpdate == true && isUpdaterBesetz) {
                    if (AutoupdateTimer.getElapsedTime().asSeconds() > updateCurrencyTime && isReadyForNewUpdate) {
                        isUpdaterBesetz = false;
                    }
                }
           
                


                if (!isUpdaterBesetz) {

                    currencyThread = std::thread([&]() {
                        if (/*timeToUpdateCurrency.getElapsedTime().asSeconds() > updateInformation &&*/ !isUpdaterBesetz && isMainMenuOpened) {
                            isReadyForNewUpdate = false;
                            std::cout << "Updating info..." << std::endl;
                            pairs.clear();
                            updateCurrency(currencyPairsToUSDT, currencyPairsWithoutSpaceToUSDT,
                                currencyPairsWithUnterToUSDT, currencyPairsWithSlashToUSDT,
                                currencyGetMarket, currencyPairsSmallToUSDT, timeToUpdateCurrency, updateInformation, currencyListBinanceToUSDT,
                                currencyListHuobiToUSDT, currencyListKukoinToUSDT, currencyListBitMartToUSDT, currencyListKrakenToUSDT, currencyListByBitToUSDT, isUpdaterBesetz, isCalculationReady, selectedMarkets, currencyPairsWithoutSpaceToBUSD, currencyListBinanceToBUSD);
                            if (isCalculationReady) {
                                calculateFinalProfit(currencyPairsWithSlashToUSDT, currencyListBinanceToUSDT, currencyListHuobiToUSDT,
                                    currencyListKukoinToUSDT, currencyListBitMartToUSDT, currencyListKrakenToUSDT,
                                    currencyListByBitToUSDT, font, scrollOffset, isUpdaterBesetz, isCalculationReady, pairs, isReadyForNewUpdate, isAllReady_ReadyForCleaning, updating, tradeSum, isCurrencyCalculated, comissionBinance, comissionHuobi, comissionKukoin, comissionBitmart, comissionKraken,
                                    comissionByBit, currencyPairsToUSDT, currencyPairsWithoutSpaceToUSDT, currencyPairsWithUnterToUSDT, currencyGetMarket, currencyPairsSmallToUSDT, AutoupdateTimer, currencyListBinanceToBUSD);
                            }
                        }
                        });

                    currencyThread.detach();
                }

                if (isSmallWindowActivated == true) {
                    window.setSize(sf::Vector2u(500, 800));

                    drawSmallMenu = true;
                    openSmallMenu(isSmallWindowActivated, isSmallWindowActiv, window, smallWindowOpened, pairs, scrollOffsetMini, openedBlockIndex, isBlockOpen, animationDuration, maxAlpha, clockforinvis, minScrollOffsetMini, openingDopMenu,
                        isCurrencyCalculated, sortedPairs, icons, maxScrollOffsetMini, button3Spritecopy, button4Sprite, isUpdaterBesetz, isReadyForNewUpdate, buttonRotation, mousePosView, currencyThread,
                        isCalculationReady, selectedMarkets, isAllReady_ReadyForCleaning, updating, font, scrollOffset, rectmenumini, rectmenuTop, rectmenugrenze);
                }
                if (isSmallWindowActivated == false && drawSmallMenu == true) {
                    window.setSize(sf::Vector2u(1706, 960));

                    sf::View view(sf::FloatRect(0.f, 0.f, 1706.f, 960.f));
                    window.setView(view);
                    drawSmallMenu = false;
                }

                if (isAllReady_ReadyForCleaning || !connectedToTheInternet) {

                    if (currencyThread.joinable()) {
                        currencyThread.join();
                    }
                    if (isAllReady_ReadyForCleaning) {
                        SetTextColor(TextColor::Green);
                        std::cout << "Currency Updated. Enjoy." << std::endl;
                        if (autoUpdate == true) {
                            std::cout << "Next Update in " << updateCurrencyTime-5 << " sec" << std::endl;
                        }
                        SetTextColor(TextColor::Default);
                    }
                    isAllReady_ReadyForCleaning = false;
                }

                if (!isInternetPruft) {
                    pruffInternetConnection(window, full, rightSaheOhneInternet, rightSaheOhneInternetPlus, isInternetPruft, marketsOnline, currencyGetMarket, temp, apiS, jatolkozashelhahah, text, threads, results, connectedToTheInternet);
                    SetTextColor(TextColor::Red);
                    std::cout << "NO INTERNET CONNECTION..." << std::endl;
                    SetTextColor(TextColor::Default);
                }

                if (!isSmallWindowActivated && !drawSmallMenu) {
                    updateConnectionInformation(window, connectionCircle, screenWidth, screenHeight, informationSprites, defaultScale, targetScale, hover, isHovered, isExtectionMenuOpened, rectmenu, connectedToTheInternet, sizeControlInternetX, sizeControlInternetY, autoUpdate, 
                        activeUpdateIcon, AutoupdateTimer, timedisplaytoupdate, textFat);
                }

                window.display();
            }
        
    }
}


/* if (IsInternetConnected) {
            std::string exchangeRates = std::to_string(GetExchangeRateWhiteBit(su);
            ParseExchangeRates(exchangeRates);
            window.clear();
            DrawExchangeRates(window, exchangeRates);
        }
        else if (!IsInternetConnected) {
            noInternetConnection(window, full);
        }
        */