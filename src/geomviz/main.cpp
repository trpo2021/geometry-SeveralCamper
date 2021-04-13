#include <vector>
#include <array>
#include <math.h>

#define PI 3.1415


void CirclePandS(const vector<int> &coordinates)
{
    double p = coordinates[2] * 2 * PI;
    double s = coordinates[2] * coordinates[2] * PI;
    cout << "Perimeter is " << p << "\nSquare is " << s << endl;
}

double length(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void TrianglePandS(const vector<int> &coordinates)
{
    double AB = length(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
    double BC = length(coordinates[2], coordinates[3], coordinates[4], coordinates[5]);
    double CA = length(coordinates[4], coordinates[5], coordinates[0], coordinates[1]);
    double p = AB + BC + CA;
    double p2 = p / 2;
    double s = sqrt(p2 * (p2 - AB) * (p2 - BC) * (p2 - CA));
    cout << "Perimeter is " << p << "\nSquare is " << s << endl;
}

void ShowCoordinatesCircle(const vector<int> &coordinates)
{
    cout << "\ncircle(" << coordinates[0] << " " << coordinates[1] << ", "
         << coordinates[2] << ")\n";
}

void ShowCoordinatesTriangle(const vector<int> &coordinates)
{
    cout << "\ntriangle(" << coordinates[0] << " " << coordinates[1] << ", "
         << coordinates[2] << " " << coordinates[3] << ", " << coordinates[4]
         << " " << coordinates[5] << ")\n";
}

template<std::size_t SIZE>
void Tokenizer(const array<string, SIZE> &tokens, array<int, 10> &idTokens)
{
    for (int i = 0; i < (int)tokens.size(); i++)
    {
        if (tokens[i] == "(")
            idTokens[i] = 101;

        if (tokens[i] == ")")
            idTokens[i] = 102;

        if (tokens[i] == "-")
            idTokens[i] = 103;

        if (tokens[i] == ",")
            idTokens[i] = 104;

        if (tokens[i] == "number")
            idTokens[i] = 105;

        if (tokens[i] == ".")
            idTokens[i] = 106;
    }
}

int main()
{
    // Массив содержащий координаты фигуры

    /// Набор токенов для Круга
    array<string, 6> tokensCircle = {"(", "number", "number", ",", "number", ")"};

    /// Набор токенов для Треугольника
    array<string, 10> tokensTriangle = {"(", "number", "number", ",", "number", "number", ",", "number", "number", ")"};

    array<int, 10> tokensList = {};


    // введенная пользователем строка
    string inputString;

    // Строка для обработки
    ParseString parseString;
    int count;
    string keyShow = "";
    cout << "Введите количество фигур\n";
    cin >> count;
    cin.clear();
    fflush(stdin);
    for(int i = 0; i < count + 1; i++)
    {
        vector<int> collectionCoordinates;
        if (i != 0)
            cout << "Введите строку с названием фигуры и ее параметрами \n";

        // Считываем строку введенную пользователем с пробелами и переносами
        // строк. Поскольку стандартный метод ввода не позволяет считать
        // строку с пробеламиf
        getline(cin, inputString);

        // Задаю строку
        parseString.SetString(inputString);

        // Получаю некую последовательность буквенных символов до первого вхождения
        // не буквенного симовола
        parseString.FindFirstCharDifferentFrom();

        // Флаг ошибки
        bool isError = false;
        /// Если ключевое слово - CIRCLE
        if (parseString.IsEqualsKeyWord("circle"))
        {
            isError = false;

            Tokenizer(tokensCircle, tokensList);

            keyShow = "circle";
        }

        /// Если ключевое слово - TRIANGLE
        if (parseString.IsEqualsKeyWord("triangle"))
        {
            isError = false;

            Tokenizer(tokensTriangle, tokensList);

            keyShow = "triangle";
        }

        /// Если ключевого слова нет или там ошибка
        if(i != 0)
        {
            if (!parseString.IsEqualsKeyWord("circle") && !parseString.IsEqualsKeyWord("triangle"))
            {
                isError = true;

                cout << "Ошибка в ключевом слове!";
            }
        }

        if (!isError)
        {
            for (int i = 0; i < (int)tokensList.size(); i++)
            {
                // Если ошибок не было
                if (!isError)
                {
                    /// Переходим на Ключ при определенном токене
                    switch (tokensList[i])
                    {
                    case 101: // Если токен открытая скобка

                        if (parseString.IsOpenParenthesis())
                        {
                            isError = false;
                        }
                        else
                        {
                            isError = true;
                            cout << "Символ #" << parseString.indexStr + 1
                                << " должен быть - ( \n\n";
                        }

                        break;

                    case 102: // Если токен закрытая скобка
                        if (parseString.IsCloseParenthesis())
                        {
                            isError = false;
                        }
                        else
                        {
                            isError = true;
                            cout << "Символ #" << parseString.indexStr + 1
                                << " должен быть - ) \n\n";
                        }
                        break;

                    case 104: // Если токен запятая
                        if (parseString.IsComma())
                        {
                            isError = false;
                        }
                        else
                        {
                            isError = true;
                            cout << "Символ #" << parseString.indexStr + 1
                                << " должен быть - , \n\n";
                        }
                        break;

                    case 105: // Если токен число

                        if (parseString.FindDigital())
                        {
                            if (parseString.FindNumber() == 0)
                            {
                                isError = false;

                                collectionCoordinates.push_back(
                                    parseString.StrToInt());
                            }

                            if (parseString.FindNumber() == -1)
                            {
                                isError = true;

                                cout << "None";
                            }

                            if (parseString.FindNumber() == 1)
                            {
                                isError = true;

                                cout << "Символ #" << parseString.indexStr
                                    << " должен быть цифрой или пробелом\n\n";
                            }
                        }
                        else
                        {
                            isError = true;

                            // Если не число, то указать на номер в строке
                            cout << "Символ #" << parseString.indexStr
                                << " должен быть - цифрой \n\n";
                        }

                        break;

                    default:
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            if (keyShow == "circle")
            {
                ShowCoordinatesCircle(collectionCoordinates);
                CirclePandS(collectionCoordinates);
            }

            if (keyShow == "triangle")
            {
                ShowCoordinatesTriangle(collectionCoordinates);
                TrianglePandS(collectionCoordinates);
            }
        }
    }

    return 0;
}
