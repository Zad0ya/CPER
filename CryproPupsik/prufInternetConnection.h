

bool CheckAPIConnection(const std::string& apiUrl) {
	web::http::client::http_client_config config;
	config.set_validate_certificates(false); // Опционально: отключение проверки сертификата

	web::http::client::http_client client(utility::conversions::to_string_t(apiUrl), config);

	web::http::http_request request(web::http::methods::GET);
	request.headers().add(U("Accept"), U("application/json"));

	pplx::task<web::http::http_response> response = client.request(request);

	try {
		web::http::http_response httpResponse = response.get();
		if (httpResponse.status_code() == web::http::status_codes::OK) {
			// Успешное подключение к API
			std::cout << "Connection to API..." << std::endl;
			return true;
		}
	}
	catch (const std::exception& e) {
		// Проблемы с подключением к API
		std::cout << "Connection error: " << e.what() << std::endl;
	}

	return false;
}

void checkAPIConnectionThread(const std::string& apiUrl, std::vector<bool>& results) {
	bool isConnected = CheckAPIConnection(apiUrl);
	results.push_back(isConnected);
}

void pruffInternetConnection(sf::RenderWindow& window, sf::RectangleShape& full, sf::RectangleShape& rightSaheOhneInternet, sf::RectangleShape& rightSaheOhneInternetPlus,
	bool& isInternetPruft, std::vector<bool>& marketsOnline, std::vector<std::string>& currencyGetMarket, int& temp, std::vector<std::string> apiS, bool& jatolkozashelhahah, sf::Text text, std::vector<std::thread>& threads, std::vector<bool>& results,
	bool connectedToTheInternet) {

	full.setFillColor(sf::Color(30, 30, 30, 255));
	rightSaheOhneInternet.setFillColor(sf::Color(37, 37, 37, 255));
	rightSaheOhneInternetPlus.setFillColor(sf::Color(57, 57, 57, 255));
	rightSaheOhneInternet.setPosition(window.getSize().x - rightSaheOhneInternet.getGlobalBounds().width, 0);
	rightSaheOhneInternetPlus.setPosition(rightSaheOhneInternet.getPosition().x - 20, 0);
	window.draw(full);
	window.draw(rightSaheOhneInternet);
	window.draw(rightSaheOhneInternetPlus);

	text.setCharacterSize(15);

	float possitionforstatusX = (window.getSize().x - rightSaheOhneInternet.getSize().x + rightSaheOhneInternetPlus.getSize().x) / 2;
	float possitionforstatusY = 220;

	if (!connectedToTheInternet) {
		text.setString("Waiting for a connection");
		text.setPosition(possitionforstatusX, possitionforstatusY);
		window.draw(text);
	}

	if (connectedToTheInternet) {
		std::cout << "Making some connections..." << std::endl;
		text.setString("Connection...");
		text.setPosition(possitionforstatusX, possitionforstatusY);
		window.draw(text);

		for (std::string& apiUrl : apiS) {
			threads.emplace_back(checkAPIConnectionThread, std::ref(apiUrl), std::ref(results));
		}
		for (std::thread& thread : threads) {
			thread.join();
		}

		for (std::size_t i = 0; i < results.size(); ++i) {
			if (results[i]) {
				SetTextColor(TextColor::Green);
				std::cout << "Connected to " << currencyGetMarket[temp + i] << " successfully." << std::endl;
				marketsOnline.push_back(true);
				text.setFillColor(sf::Color::Green);
				text.setString("Connected to " + currencyGetMarket[temp + i] + " successfully.");
				text.setPosition(rightSaheOhneInternet.getPosition().x + (rightSaheOhneInternet.getGlobalBounds().width / 4 + text.getCharacterSize()), 200 + (30 * (temp + i)));
				window.draw(text);
				std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Задержка 500 мс
			
			}
			else {
				SetTextColor(TextColor::Red);
				std::cout << "Connected to " << currencyGetMarket[temp + i] << " DENIED." << std::endl;
				marketsOnline.push_back(false);
				text.setFillColor(sf::Color::Red);
				text.setString("Connected to " + currencyGetMarket[temp + i] + " DENIED.");
				text.setPosition(rightSaheOhneInternet.getPosition().x - (rightSaheOhneInternet.getGlobalBounds().width / 4 + text.getCharacterSize() / 2), 200 + (30 * (temp + i)));
				window.draw(text);
				std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Задержка 500 мс
			
			}
		}

	
		SetTextColor(TextColor::Default);
		temp = 0;
		std::cout << " " << std::endl;
		window.display();
		window.clear();
		isInternetPruft = true;
		std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(1)));
	}
}

