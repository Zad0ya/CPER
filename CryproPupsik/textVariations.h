

enum class TextColor {
    Default,
    Red,
    Green
};

// Установка цвета текста
void SetTextColor(TextColor color) {
    switch (color) {
    case TextColor::Default:
        std::cout << "\033[0m";  
        break;
    case TextColor::Red:
        std::cout << "\033[31m"; 
        break;
    case TextColor::Green:
        std::cout << "\033[32m"; 
        break;
    }
}

enum class FontStyle {
    Regular,
    Bold
};

// Установка стиля шрифта
void SetFontStyle(FontStyle style) {
    switch (style) {
    case FontStyle::Regular:
        std::cout << "\033[0m"; 
        break;
    case FontStyle::Bold:
        std::cout << "\033[1m";  
        break;
    }
}