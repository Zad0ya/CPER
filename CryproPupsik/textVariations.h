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