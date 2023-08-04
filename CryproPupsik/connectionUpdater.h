


void updateConnectionInformation(sf::RenderWindow& window, sf::CircleShape& connectionCircle, unsigned int screenWidth, unsigned int screenHeight, sf::Sprite& informationalSprite, sf::Vector2f defaultScale, 
    sf::Vector2f targetScale, sf::Clock& hover, bool& isHovered, bool& isExtectionMenuOpened, sf::RectangleShape& rectmenu, bool connectedToTheInternet, float& sizeControlInternetX, float& sizeControlInternetY,
    bool& autoUpdate, sf::Sprite& activeUpdateIcon, sf::Clock& AutoupdateTimer, int& timedisplaytoupdate, sf::Text textFat){

    informationalSprite.setPosition(165, 40);
    rectmenu.setFillColor(sf::Color(37, 37, 37, 255));
    if (connectedToTheInternet) {
        informationalSprite.setTextureRect(sf::IntRect(403, 31, 354, 57));
    }
    else if (!connectedToTheInternet) {
        informationalSprite.setTextureRect(sf::IntRect(27, 31, 354, 57));
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f spritePosition = informationalSprite.getPosition();
    sf::FloatRect spriteBounds = informationalSprite.getGlobalBounds();
    bool isMouseOverSprite = spriteBounds.contains(sf::Vector2f(mousePosition));

    rectmenu.setFillColor(sf::Color(200, 200, 200, 255));;
    rectmenu.setPosition(300, 600);

    if (isMouseOverSprite && !isHovered) {
        // јнимаци€ увеличени€ спрайта при наведении курсора
        isHovered = true;
        hover.restart();
    }
    else if (!isMouseOverSprite && isHovered) {
        // јнимаци€ уменьшени€ спрайта при убирании курсора
        isHovered = false;
        hover.restart();
    }

    if (isHovered) {
        float elapsedSeconds = hover.getElapsedTime().asSeconds();
        float t = std::min(elapsedSeconds / 0.1f, 1.0f); 

        sf::Vector2f newScale = defaultScale + (targetScale - defaultScale) * t;
        informationalSprite.setScale(newScale);
    }
    else {
        informationalSprite.setScale(defaultScale);
    }

    if (isMouseOverSprite && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        isExtectionMenuOpened = true;
    }
    if (isMouseOverSprite == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) && isExtectionMenuOpened == true) {
        isExtectionMenuOpened = false;
    }

    if (isExtectionMenuOpened == true) {
        rectmenu.setPosition(informationalSprite.getPosition().x, informationalSprite.getPosition().y);
        if (sizeControlInternetX < 400)
        {
            sizeControlInternetX += 20;
            rectmenu.setSize(sf::Vector2f(sizeControlInternetX, sizeControlInternetY));
        }
        if (sizeControlInternetY < 200)
        {
            sizeControlInternetY += 10;
            rectmenu.setSize(sf::Vector2f(sizeControlInternetX, sizeControlInternetY));
        }
        if (sizeControlInternetX == 400 && sizeControlInternetY == 200) {
            rectmenu.setSize(sf::Vector2f(400, 200));
        }
        window.draw(rectmenu);
    }
    else
    {
        if (rectmenu.getSize().y > 0)
        {
            rectmenu.setSize(sf::Vector2f(200, rectmenu.getSize().y - 10));
            rectmenu.setPosition(300, rectmenu.getPosition().y + 10);
        }
    }
    window.draw(informationalSprite);
    if (autoUpdate == true) {
        activeUpdateIcon.setPosition(informationalSprite.getPosition().x + informationalSprite.getGlobalBounds().width - 50, informationalSprite.getPosition().y + informationalSprite.getGlobalBounds().height / 2 - activeUpdateIcon.getGlobalBounds().height / 2);
        window.draw(activeUpdateIcon);

        // ѕолучаем оставшеес€ врем€ от обратного отсчета
        int timeRemainingToUpdate = AutoupdateTimer.getElapsedTime().asSeconds();

        if (timeRemainingToUpdate > 0) {
            textFat.setFillColor(sf::Color(151, 181, 255, 255));

            if (timeRemainingToUpdate <= 15) {
                textFat.setCharacterSize(16);
                textFat.setString(std::to_string(timedisplaytoupdate - timeRemainingToUpdate));
                if (timedisplaytoupdate - timeRemainingToUpdate < 10) {
                    textFat.setPosition(activeUpdateIcon.getPosition().x - 5, activeUpdateIcon.getPosition().y + 10);
                }
                if (timedisplaytoupdate - timeRemainingToUpdate >= 10 && timedisplaytoupdate - timeRemainingToUpdate <= 15) {
                    textFat.setPosition(activeUpdateIcon.getPosition().x - 15, activeUpdateIcon.getPosition().y + 10);
                }
                
            }
            else {
                textFat.setCharacterSize(16);
                textFat.setString(sf::String("Updating"));
                textFat.setPosition(activeUpdateIcon.getPosition().x - 75, activeUpdateIcon.getPosition().y + 10);
            }
        }
        else {
            // ≈сли обратный отсчет закончилс€, выводим сообщение "Updating"
            textFat.setFillColor(sf::Color(151, 181, 255, 255));
            textFat.setCharacterSize(16);
            textFat.setString(sf::String("Updating"));
            textFat.setPosition(activeUpdateIcon.getPosition().x - 75, activeUpdateIcon.getPosition().y + 10);
        }

        window.draw(textFat);
    }

}