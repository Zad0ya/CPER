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

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace utility;
using namespace std;


pplx::task<void> sendRequest(const string_t& activationKey, bool& isActivated, bool& isErrorActivation) {
    // Формируем JSON-объект для отправки на сервер
    json::value requestJson;
    requestJson[U("activation_key")] = json::value::string(activationKey);

    // URL сервера, куда будем отправлять запрос
    uri_builder builder(U("http://localhost:8080/activation"));

    // Создаем объект HTTP-клиента
    http_client client(builder.to_uri());

    // Создаем HTTP-запрос типа POST и устанавливаем JSON-данные
    http_request request(methods::POST);
    request.headers().set_content_type(U("application/json"));
    request.set_body(requestJson);

    // Отправляем запрос и обрабатываем ответ
	return client.request(request)
		.then([&isActivated, &isErrorActivation](http_response response)->pplx::task<void> {
		if (response.status_code() == status_codes::OK) {
			// Если сервер вернул статус 200 OK, выводим ответ
			return response.extract_json()
				.then([&isActivated](json::value jsonResponse) {
				// Обрабатываем ответ (в данном примере просто выводим его в консоль)
				wcout << L"Ответ от сервера: " << jsonResponse.serialize() << endl;
				isActivated = true; // Захватываем переменную по ссылке и изменяем её значение
					});
		}
            else {
                // Если сервер вернул другой статус, выводим сообщение об ошибке
                wcout << L"Ошибка сервера: " << response.status_code() << endl;
				isErrorActivation = true;
                return pplx::task_from_result();
            }
		
        });
	
}

bool allCellsFilled(const std::vector<std::string>& cellText) {
	for (const std::string& text : cellText) {
		if (text.size() != 4) {
			return false;
		}
	}
	return true;
}


void activateProduct(sf::Sprite& emeraldactivationbackground, float& emeraldbackgroundvisible, sf::Time deltaTime, sf::RenderWindow& window, sf::Sprite& iconActivation, float& activationPosition,
	float& activationColor, sf::Text& textlight, sf::Text& textFat, bool& isBackGroundVisible, sf::Sprite& schloss, sf::Sprite& textcodeicons, sf::Vector2f& mousePosView, const float CODE_BUTTON_SizeX, 
	const float CODE_BUTTON_SizeY, int& activeCellIndex, bool& allCellsFilled, std::vector<std::string>& cellText, sf::Event event, sf::Text& textRegular, const float textreloadTime, sf::Clock& buttonIsAvailable,
	sf::Sprite& continueButton, bool& isActivating, float& textForLoadingDark, sf::Clock& clockAnimation, float& timeSinceLastFrame, float& frameDuration, int& currentFrame, const int& numFrames,
	std::vector<sf::Sprite>& sprites, float& colorWelcomeAndSchloss, float& elapsedFloatingTime, std::string& activationKey, bool& requessendet, bool& isActivated, bool& isInTransitionToSetup, bool& isInSetup,
	bool& isErrorActivation, bool& isErrorDuringActivation, float& targetPosY, float& currentPosY, float& speed, sf::View& view, bool& isLightTheme, bool& isDarkTheme, sf::Sprite& iconColorDark, sf::Sprite& iconColorLight,
	sf::Sprite& writeplankSetup, sf::Sprite& selectionSetupNo, sf::Sprite& selectionSetupYes, sf::RectangleShape& full, sf::Sprite& emeraldtransitiontosettingsbackground, float& colorbackground, sf::Sprite& blackIconSetup90grad, 
	sf::Sprite& whiteIconSetup90grad, float& initialSpeed, float& finalSpeedLeft, float& accelerationLeft, sf::Sprite& whiteIconSetup90grad2, float& activationPosRight, float& activationPosLeft, float& initialSpeedRight, 
	float& finalSpeedRight, float& accelerationRight, sf::Sprite& notActiveCircle, sf::Sprite& activeCircle, float& textcolor, float& colorForBlack, float& colorForWhite, sf::Sprite& blackIconSetup90grad2, bool& isIWantToBetaTest,
	bool& isIWantToBeAnonym, sf::Sprite& selectionSetupYes2, sf::Sprite& selectionSetupNo2, sf::Sprite& emeraldkpp, float& time2, bool& isLicenseChecked, bool& readyForLoad) {

	if (isInSetup == false) {
		emeraldactivationbackground.setPosition(sf::Vector2f(0, 0));
		if (emeraldbackgroundvisible < 255) {
			emeraldbackgroundvisible += 51 * deltaTime.asSeconds();
			emeraldactivationbackground.setColor(sf::Color(255, 255, 255, emeraldbackgroundvisible));
		}
		else if (emeraldbackgroundvisible >= 255) {
			emeraldactivationbackground.setColor(sf::Color(255, 255, 255, 255));

		}
		window.draw(emeraldactivationbackground);

		if (activationPosition < 350) {
			activationPosition += 50 * deltaTime.asSeconds();
		}
		else if (activationPosition >= 350 && activationPosition < 400) {
			activationPosition += 25 * deltaTime.asSeconds();
		}
		else if (activationPosition >= 400) {
			activationPosition = 400;
			isBackGroundVisible = true;
		}

		if (activationColor < 255) {
			activationColor += 51 * deltaTime.asSeconds();
			iconActivation.setColor(sf::Color(255, 255, 255, activationColor));
		}
		else if (activationColor >= 255) {
			iconActivation.setColor(sf::Color(255, 255, 255, 255));
		}

		// Apply quadratic easing effect towards the end of the movement
		float normalizedPosition = activationPosition - 350; // Normalize the position to start from 0
		float easedPosition = 350 + (normalizedPosition * normalizedPosition) * 0.03; // Quadratic easing factor 0.03

		// Limit the maximum position to 400
		easedPosition = std::min(easedPosition, 400.f);

		// Update the position of the sprite
		iconActivation.setPosition(sf::Vector2f(window.getSize().x / 2 - iconActivation.getGlobalBounds().width / 2, easedPosition));

		window.draw(iconActivation);

		if (isBackGroundVisible == true) {

			if (colorWelcomeAndSchloss < 255) {
				colorWelcomeAndSchloss += 85 * deltaTime.asSeconds();
			}
			else if (colorWelcomeAndSchloss >= 255) {
				colorWelcomeAndSchloss = 255;
			}

			schloss.setColor(sf::Color(255, 255, 255, colorWelcomeAndSchloss));

			elapsedFloatingTime += deltaTime.asSeconds();

			// Вычисляем вертикальное смещение спрайта для эффекта парения
			float yOffset = 8 * sin(elapsedFloatingTime * 4);

			// Перемещаем спрайт с учетом вертикального смещения
			schloss.setPosition(sf::Vector2f(window.getSize().x / 2 - schloss.getGlobalBounds().width / 2, 20 - yOffset));
			window.draw(schloss);

			textFat.setFillColor(sf::Color(255, 255, 255, colorWelcomeAndSchloss));
			textFat.setCharacterSize(48);
			textFat.setString(sf::String("Welcome."));
			textFat.setPosition(sf::Vector2f(732, 320));
			window.draw(textFat);

			if (isActivating == true) {
				textForLoadingDark -= 127.5f * deltaTime.asSeconds();
				textFat.setFillColor(sf::Color(223, 223, 223, textForLoadingDark));
				textFat.setCharacterSize(36);
				if (isActivated == false) {
					textFat.setString(sf::String("Enter your product activation key:"));
				}
				if (isErrorDuringActivation == true) {
					textFat.setString(sf::String("There was a problem with activation:"));
				}
				if (isActivated == true) { textFat.setString(sf::String("Your product has been activated!")); }
				textFat.setPosition(sf::Vector2f(553, 490));
				if (textForLoadingDark > 0) {
					window.draw(textFat);
				}

				textlight.setFillColor(sf::Color(114, 114, 114, textForLoadingDark));
				textlight.setCharacterSize(32);
				if (isActivated == false) {
					textlight.setString(sf::String("Enter the 16-character key into four cells \nof 4 characters each. Each key is one \ntime use and cannot be reused."));
				}
				if (isErrorDuringActivation == true) {
					textlight.setString(sf::String("We encountered a problem while trying to \nactivate. Double-check your key for \naccuracy and verify it hasn't been used \npreviously. Please retry your request."));
				}
				if (isActivated == true) { textlight.setString(sf::String("Your application has been successfully \nactivated. Let's move on to your \ncustomization!")); }
				textlight.setPosition(sf::Vector2f(553, 550));
				if (textForLoadingDark > 0) {
					window.draw(textlight);
				}
			}

			else {
				if (textForLoadingDark < 255 && colorWelcomeAndSchloss >= 125) {
					textForLoadingDark += 85 * deltaTime.asSeconds();
				}
				else if (textForLoadingDark >= 255) {
					textForLoadingDark = 255;
				}
				textFat.setFillColor(sf::Color(223, 223, 223, textForLoadingDark));
				textFat.setCharacterSize(36);
				if (isActivated == false) {
					textFat.setString(sf::String("Enter your product activation key:"));
				}
				if (isErrorDuringActivation == true) {
					textFat.setString(sf::String("There was a problem with activation:"));
				}
				if (isActivated == true) { textFat.setString(sf::String("Your product has been activated!")); }

				textFat.setPosition(sf::Vector2f(553, 490));
				window.draw(textFat);

				textlight.setFillColor(sf::Color(114, 114, 114, textForLoadingDark));
				textlight.setCharacterSize(32);
				if (isActivated == false) {
					textlight.setString(sf::String("Enter the 16-character key into four cells \nof 4 characters each. Each key is one \ntime use and cannot be reused."));
				}
				if (isErrorDuringActivation == true) {
					textlight.setString(sf::String("We encountered a problem while trying to \nactivate. Double-check your key for \naccuracy and verify it hasn't been used \npreviously. Please retry your request."));
				}
				if (isActivated == true) { textlight.setString(sf::String("Your application has been successfully \nactivated. Let's move on to your \ncustomization!")); }
				textlight.setPosition(sf::Vector2f(553, 550));
				window.draw(textlight);
			}

			if (isActivated == false) {
				for (int i = 0; i < 4; i++) {
					sf::Vector2f codewriteicons = sf::Vector2f(iconActivation.getGlobalBounds().left + 115 + (i * 175), 750);
					if (mousePosView.x >= codewriteicons.x && mousePosView.x <= codewriteicons.x + CODE_BUTTON_SizeX &&
						mousePosView.y >= codewriteicons.y && mousePosView.y <= codewriteicons.y + CODE_BUTTON_SizeY) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							activeCellIndex = i;
						}
					}
					textcodeicons.setPosition(sf::Vector2f(iconActivation.getGlobalBounds().left + 102 + (i * 175), 750));
					if (isActivating == true) {
						textcodeicons.setColor(sf::Color(255, 255, 255, 160));
					}
					else {
						textcodeicons.setColor(sf::Color(255, 255, 255, textForLoadingDark));
					}
					window.draw(textcodeicons);

					textRegular.setCharacterSize(24);
					textRegular.setFillColor(sf::Color(17, 17, 17, 255));
					textRegular.setString(sf::String(cellText[i]));
					textRegular.setPosition(sf::Vector2f(iconActivation.getGlobalBounds().left + 145 + (i * 175), 780));

					window.draw(textRegular);


				}

				// Определяем обработчик события TextEntered
				if (event.type == sf::Event::TextEntered && isBackGroundVisible && isActivating == false) {
					if (event.text.unicode == '\b' && !cellText[activeCellIndex].empty()) {
						if (buttonIsAvailable.getElapsedTime().asSeconds() > (textreloadTime + 0.10f)) {
							cellText[activeCellIndex].pop_back();
							allCellsFilled = ::allCellsFilled(cellText);
							buttonIsAvailable.restart();
						}
					}

					else if (event.text.unicode >= 32 && event.text.unicode < 128 && cellText[activeCellIndex].size() < 4) {
						if (buttonIsAvailable.getElapsedTime().asSeconds() > (textreloadTime + 0.10f)) {
							cellText[activeCellIndex] += static_cast<char>(event.text.unicode);
							allCellsFilled = ::allCellsFilled(cellText);
							buttonIsAvailable.restart();
						}
					}
				}

				if (allCellsFilled == true) {
					continueButton.setPosition((sf::Vector2f(window.getSize().x / 2 - continueButton.getGlobalBounds().width / 2, 830)));
					sf::FloatRect  continueButtonfloat = continueButton.getGlobalBounds();
					if (continueButtonfloat.contains(mousePosView) && window.hasFocus() && isActivating == false)
					{
						continueButton.setColor(sf::Color(255, 255, 255, 190));
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							isActivating = true;

						}
					}
					else if (isActivating == true) {
						continueButton.setColor(sf::Color(255, 255, 255, 160));
					}
					else { continueButton.setColor(sf::Color(255, 255, 255, 255)); }
					window.draw(continueButton);
				}
				//60 воздух

			}
			//781

			if (isActivating == true && textForLoadingDark <= 0) {
				float deltaTimeAnimation = clockAnimation.restart().asSeconds();
				timeSinceLastFrame += deltaTimeAnimation;

				if (timeSinceLastFrame >= frameDuration) {

					currentFrame = (currentFrame + 1) % numFrames;
					timeSinceLastFrame = 0.0f;
				}


				window.draw(sprites[currentFrame]);
			}

			if (isActivating == true && textForLoadingDark <= 0 && requessendet == false) {
				activationKey = std::accumulate(cellText.begin(), cellText.end(), std::string(""));
				std::cout << activationKey << std::endl;
				sendRequest(conversions::to_string_t(activationKey), isActivated, isErrorActivation).wait();
				requessendet = true;
			}

			if (isActivated == true && requessendet == true) {
				isActivating = false;
				requessendet = false;
			}

			if (isErrorActivation == true && requessendet == true) {
				isErrorDuringActivation = true;
				cellText.clear();
				isActivating = false;
				requessendet = false;
				isErrorActivation = false;
			}

			if (isActivated == true) {
				continueButton.setColor(sf::Color(255, 255, 255, textForLoadingDark));
				continueButton.setPosition((sf::Vector2f(window.getSize().x / 2 - continueButton.getGlobalBounds().width / 2, 830)));
				sf::FloatRect continueButtonfloat = continueButton.getGlobalBounds();
				if (continueButtonfloat.contains(mousePosView) && window.hasFocus() && isActivating == false)
				{
					continueButton.setColor(sf::Color(255, 255, 255, 190));
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						isInTransitionToSetup = true;
					}
				}
				window.draw(continueButton);
				window.draw(full);
			}

			if (isInTransitionToSetup == true) {
				full.setSize(sf::Vector2f(1706, 960));
				full.setFillColor(sf::Color(17, 17, 17, 255));
				full.setPosition(sf::Vector2f(0, -1920));
				emeraldtransitiontosettingsbackground.setPosition(sf::Vector2f(0, -960));
				time2 += 0.01f;
				float offsetYKpp = 30 * std::sin(4 * time2);
				
				
				emeraldkpp.setPosition(emeraldtransitiontosettingsbackground.getGlobalBounds().width / 2 - emeraldkpp.getGlobalBounds().width /2, ((emeraldtransitiontosettingsbackground.getGlobalBounds().height / 2 - emeraldkpp.getGlobalBounds().height / 2) - 960) + offsetYKpp);

				float distanceToMove = speed * deltaTime.asSeconds();
				if (std::abs(targetPosY - currentPosY) < distanceToMove)
				{
					view.setCenter(view.getCenter().x, targetPosY);
					currentPosY = targetPosY;
				}
				else
				{
					
					if (targetPosY > currentPosY)
						view.move(0, distanceToMove);
					else
						view.move(0, -distanceToMove);

					currentPosY = view.getCenter().y;
				}
				if (currentPosY <= targetPosY) {
					isInSetup = true;
					view.setCenter(view.getCenter().x, -1445);
					textForLoadingDark = 0;
					isInTransitionToSetup = false;
				}

				window.draw(emeraldtransitiontosettingsbackground);
				window.draw(emeraldkpp);
				window.draw(full);

			}
		}
	}
	if (isInSetup == true)
	{
		view.setCenter(view.getCenter().x, 480);
		full.setPosition(sf::Vector2f(0, 0));

		if (activationPosLeft < 50) {
			
			float deltaSpeed = accelerationLeft * deltaTime.asSeconds();
			initialSpeed -= deltaSpeed;

			if (initialSpeed < finalSpeedLeft) {
				initialSpeed = finalSpeedLeft;
			}

			activationPosLeft += initialSpeed * deltaTime.asSeconds();
			whiteIconSetup90grad.setPosition(activationPosLeft, window.getSize().y / 2 - whiteIconSetup90grad.getGlobalBounds().height / 2);
		}

	
		if (activationPosRight > window.getSize().x - whiteIconSetup90grad2.getGlobalBounds().width - 450)
		{
			float deltaSpeedRight = accelerationRight * deltaTime.asSeconds();
			initialSpeedRight -= deltaSpeedRight;

			if (initialSpeedRight < finalSpeedRight) {
				initialSpeedRight = finalSpeedRight;
			}

			activationPosRight -= initialSpeedRight * deltaTime.asSeconds();
			whiteIconSetup90grad2.setPosition(activationPosRight, window.getSize().y / 2 - whiteIconSetup90grad2.getGlobalBounds().height / 2);
		}

		if (isDarkTheme == true)
		{
			if (activationPosLeft >= 100)
			{
				blackIconSetup90grad.setPosition(100, window.getSize().y / 2 - whiteIconSetup90grad.getGlobalBounds().height / 2);
			}

			if (colorbackground > 17)
			{
				colorbackground -= 109 * deltaTime.asSeconds();
			}
			if (textcolor < 255) {
				textcolor += 85 * deltaTime.asSeconds();
			}
			else if (textcolor >= 255) {
				textcolor = 255;
			}
			if (colorForWhite < 255) {
				colorForWhite += 85 * deltaTime.asSeconds();
			}
			if (colorForWhite >= 255) {
				colorForWhite = 255;
			}
			if (colorForBlack > 0) {
				colorForBlack -= 85 * deltaTime.asSeconds();
			}
			if (colorForBlack <= 0) {
				colorForBlack = 0;
			}
		}

		if (isLightTheme == true)
		{

			if (activationPosLeft >= 100)
			{
				whiteIconSetup90grad.setPosition(100, window.getSize().y / 2 - whiteIconSetup90grad.getGlobalBounds().height / 2);
			}
			if (activationPosRight >= window.getSize().x + 100 + whiteIconSetup90grad.getGlobalBounds().width)
			{
				whiteIconSetup90grad2.setPosition(colorWelcomeAndSchloss, window.getSize().y / 2 - whiteIconSetup90grad2.getGlobalBounds().height / 2);
			}
			if (colorbackground < 235)
			{

				colorbackground += 109 * deltaTime.asSeconds();
			}
			if (textcolor > 0) {
				textcolor -= 85 * deltaTime.asSeconds();
			}
			if (textcolor <= 0) {
				textcolor = 0;
			}

			if (colorForBlack < 255) {
				colorForBlack += 85 * deltaTime.asSeconds();
			}
			if (colorForBlack >= 255) {
				colorForBlack = 255;
			}
			if (colorForWhite > 0) {
				colorForWhite -= 85 * deltaTime.asSeconds();
			}
			if (colorForWhite <= 0) {
				colorForWhite = 0;
			}
			
		}
		full.setFillColor(sf::Color(colorbackground, colorbackground, colorbackground, 255));
		whiteIconSetup90grad.setColor(sf::Color(255, 255, 255, colorForWhite));
		whiteIconSetup90grad2.setColor(sf::Color(255, 255, 255, colorForWhite));
		blackIconSetup90grad.setColor(sf::Color(255, 255, 255, colorForBlack));
	    blackIconSetup90grad2.setColor(sf::Color(255, 255, 255, colorForBlack));

		window.draw(full);

		if (colorForWhite >= 30) {
			window.draw(whiteIconSetup90grad);
			window.draw(whiteIconSetup90grad2);
		}

		window.draw(iconColorDark);
		window.draw(iconColorLight);

		blackIconSetup90grad.setPosition(sf::Vector2f(whiteIconSetup90grad.getPosition().x, whiteIconSetup90grad.getPosition().y));
		blackIconSetup90grad2.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x, whiteIconSetup90grad2.getPosition().y));

		if (colorForBlack >= 30) {
			window.draw(blackIconSetup90grad);
			window.draw(blackIconSetup90grad2);
		}

		textFat.setFillColor(sf::Color(textcolor, textcolor, textcolor, 255));
		textFat.setCharacterSize(36);
		iconColorDark.setPosition(sf::Vector2f(whiteIconSetup90grad.getPosition().x + 85, whiteIconSetup90grad.getPosition().y + 250));
		iconColorLight.setPosition(sf::Vector2f(whiteIconSetup90grad.getPosition().x + whiteIconSetup90grad.getGlobalBounds().width - 85 - iconColorLight.getGlobalBounds().width, whiteIconSetup90grad.getPosition().y + 250));
		textFat.setCharacterSize(36);
		textFat.setPosition(sf::Vector2f(whiteIconSetup90grad.getPosition().x + 150, whiteIconSetup90grad.getPosition().y + 125));
		textFat.setString(sf::String("Choose a Theme:"));
		window.draw(textFat);

		textFat.setCharacterSize(24);
		textFat.setPosition(sf::Vector2f((iconColorDark.getPosition().x + iconColorDark.getGlobalBounds().width / 2) - 26, iconColorDark.getPosition().y + iconColorDark.getGlobalBounds().height + 10));
		textFat.setString(sf::String("Dark"));
		window.draw(textFat);

		textFat.setPosition(sf::Vector2f((iconColorLight.getPosition().x + iconColorLight.getGlobalBounds().width / 2) -30, iconColorLight.getPosition().y + iconColorLight.getGlobalBounds().height + 10));
		textFat.setString(sf::String("Light"));
		window.draw(textFat);

		textlight.setFillColor(sf::Color(114, 114, 114, textForLoadingDark));
		textlight.setCharacterSize(26);
		textlight.setPosition(sf::Vector2f(whiteIconSetup90grad.getPosition().x + 95, 720));
		textlight.setString(sf::String("You will have the option to change \nthe theme of the app at any time in \nthe settings."));
		window.draw(textlight);

		if (isDarkTheme == true) {
			activeCircle.setPosition(sf::Vector2f(iconColorDark.getPosition().x + iconColorDark.getGlobalBounds().width / 2 - activeCircle.getGlobalBounds().width / 2, iconColorDark.getPosition().y + iconColorDark.getGlobalBounds().height + 40));
			notActiveCircle.setPosition(sf::Vector2f(iconColorLight.getPosition().x + iconColorLight.getGlobalBounds().width / 2 - activeCircle.getGlobalBounds().width / 2, iconColorLight.getPosition().y + iconColorLight.getGlobalBounds().height + 40));
		}

		if (isLightTheme == true) {
			activeCircle.setPosition(sf::Vector2f(iconColorLight.getPosition().x + iconColorLight.getGlobalBounds().width / 2 - activeCircle.getGlobalBounds().width / 2, iconColorLight.getPosition().y + iconColorLight.getGlobalBounds().height + 40));
			notActiveCircle.setPosition(sf::Vector2f(iconColorDark.getPosition().x + iconColorDark.getGlobalBounds().width / 2 - activeCircle.getGlobalBounds().width / 2, iconColorDark.getPosition().y + iconColorDark.getGlobalBounds().height + 40));
		}
	
		sf::FloatRect activeCircleBounds = activeCircle.getGlobalBounds();
		sf::FloatRect notActiveCircleBounds = notActiveCircle.getGlobalBounds();

		if (notActiveCircleBounds.contains(mousePosView) && isDarkTheme == true) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				isDarkTheme = false;
				isLightTheme = true;
			}
		}
		else if (notActiveCircleBounds.contains(mousePosView) && isLightTheme == true) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				isLightTheme = false;
				isDarkTheme = true;
			}
		}
		window.draw(activeCircle);
		window.draw(notActiveCircle);

		textFat.setCharacterSize(36);
		textFat.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 115, whiteIconSetup90grad2.getPosition().y + 125));
		textFat.setString(sf::String("Do you want to Meet?"));
		window.draw(textFat);

		for (int i = 0; i < 3; i++) {
			writeplankSetup.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + whiteIconSetup90grad2.getGlobalBounds().width / 2 - writeplankSetup.getGlobalBounds().width / 2, 290 + (i*100)));
			window.draw(writeplankSetup);
		}
		textFat.setCharacterSize(16);
		textFat.setString(sf::String("Your Name"));
		textFat.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 125, 340));
		window.draw(textFat);

		textFat.setString(sf::String("Email Address"));
		textFat.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 125, 440));
		window.draw(textFat);

		textFat.setString(sf::String("Purpose of using the Program"));
		textFat.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 125, 540));
		window.draw(textFat);

		textFat.setString(sf::String("Do you want to participate in beta \ntesting of new programs and report \nbugs and crashes?"));
		textFat.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 115, 620));
		window.draw(textFat);

		textFat.setString(sf::String("I dont want to provide my information \nand remain anonymous."));
		textFat.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 115, 720));
		window.draw(textFat);


		sf::FloatRect selectionSetupNoBounds = selectionSetupNo.getGlobalBounds();
		sf::FloatRect selectionSetupNo2Bounds = selectionSetupNo2.getGlobalBounds();
		sf::FloatRect selectionSetupYesBounds = selectionSetupYes.getGlobalBounds();
		sf::FloatRect selectionSetupYes2Bounds = selectionSetupYes2.getGlobalBounds();

		if (isIWantToBetaTest == false) {
			selectionSetupNo.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 450, 610));
			window.draw(selectionSetupNo);
		}
		if (isIWantToBetaTest == true) {
			selectionSetupYes.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 450, 610));
			window.draw(selectionSetupYes);
		}

		if (isIWantToBeAnonym == false) {
			selectionSetupNo2.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 450, 710));
			window.draw(selectionSetupNo2);
		}
		else {
		
			selectionSetupYes2.setPosition(sf::Vector2f(whiteIconSetup90grad2.getPosition().x + 450, 710));
			window.draw(selectionSetupYes2);
		}

		
		if (selectionSetupNoBounds.contains(mousePosView)) {
		
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonIsAvailable.getElapsedTime().asSeconds() > (textreloadTime + 0.10f)) {
				isIWantToBetaTest = true;
			}
		}
		if (selectionSetupYesBounds.contains(mousePosView)) {
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonIsAvailable.getElapsedTime().asSeconds() > (textreloadTime + 0.10f)) {
				isIWantToBetaTest = false;
			}
		}
		if (textForLoadingDark < 255) {
			textForLoadingDark += 85 * deltaTime.asSeconds();
		}
		if (textForLoadingDark >= 255) {
			textForLoadingDark = 255;
		}
		continueButton.setColor(sf::Color(255, 255, 255, textForLoadingDark));
		continueButton.setPosition(sf::Vector2f(1450, 820));
		window.draw(continueButton);
		sf::FloatRect continueButtonfloat = continueButton.getGlobalBounds();
		if (continueButtonfloat.contains(mousePosView) && window.hasFocus())
		{
			continueButton.setColor(sf::Color(255, 255, 255, 190));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				readyForLoad = true;
				isLicenseChecked = true;
			}
		}

	}
	
	

	window.setView(view);

	window.display();
}