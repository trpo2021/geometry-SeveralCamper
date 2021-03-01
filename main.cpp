#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class UserString : string {
private:
    // Строка введенная пользователем
    string stringInputUser;

public:
    // Хранит индекс строки
    int indexStr = 0;

    // Метод для преобразования букв к нижнему регистру
    string ToLower(string str)
    {
        for (int index = 0; index < str.length(); index++) {
            if ((int)str[index] > 64 && (int)str[index] < 91) {
                str[index] += 32;
            }
        }

        return str;
    }

    // Метод ищет (пусть ищет) ключевое слово
    void FindKeyWord()
    {
        /// По своеобразной логике было решено, проверить сначала ключевое
        /// слово В данном случае circle || triangle || polygon Для этого
        /// будем считать, что любой символ кроме заглавных и строчных
        /// литералов будет являться ограничителем для проверки введеного
        /// ключевого слова
        for (int i = 0; i < stringInputUser.length(); i++) {
            // Если получили символ отличный от буквы
            if (IsNotLetter(i)) {
                // Запоминаем индекс, на котором остановились
                indexStr = i;

                // И выходим из цикла
                break;
            }
        }
    }

    // Метод сравнения двух строк
    bool Equals(string str_1, string str_2)
    {
        if (ToLower(str_1) == ToLower(str_2))
            return true;
        return false;
    }

    // Метод устанавливает в поле stringInputUser введную строку пользователя
    void SetString(string str)
    {
        stringInputUser = str;
    }

    // В данном случае решаю проблему при которой,
    // если отсутствует нулевой символ, то работа со строкой может возвращать
    // нкорректный результат
    void AppendZeroSymbol()
    {
        // записываю нулевой символ в конец строки
        stringInputUser.push_back('\0');
    }

    // Вернуть длину строки
    int Lenght()
    {
        return stringInputUser.length();
    }

    // Возвращает часть строки
    string SubStr(int startPos, int endPos)
    {
        return stringInputUser.substr(startPos, endPos);
    }

    // Метод возвращающий индекс элемента массива с которым происходит сравнение
    int RetunIndexArrayCompare(string array[], int sizeArray)
    {
        int index = -1;

        for (int i = 0; i < sizeArray; i++) {
            if (this->Equals(array[i], stringInputUser.substr(0, indexStr))) { 
                index = i;
            }
        }

        return index;
    }

    // Проверка на символ отличный от буквы
    bool IsNotLetter(int index)
    {
        // Если символ отличный от буквы
        if (((int)stringInputUser[index] > 91
             && (int)stringInputUser[index] < 96)
            || (int)stringInputUser[index] < 64
            || (int)stringInputUser[index] > 123)
            return true;

        return false;
    }

    // Если сивол - цифра
    bool IsDigitalSymbol(int index)
    {
        if ((int)stringInputUser[index] > 47
            && (int)stringInputUser[index] < 59)
            return true;
        return false;
    }

    // Проверка на пробел
    // Если пробел - true, если нет то false
    bool IsSpaceSymbol(int index)
    {
        if ((int)stringInputUser[index] == 32)
            return true;
        return false;
    }

    // Функция проверки введенной открытой скобки
    bool IsOpenParenthesis()
    {
        /// Поскольку следом за ключевым словом
        /// должна следовать открытая круглая скобка,
        /// проверим ее присутствие.
        // Если скобка отсутствует, то укажем на ошибку
        return stringInputUser[indexStr] == '(' ? true : false;
    }

    // Функция проверки введенной открытой скобки
    bool IscloseParenthesis(int index)
    {
        /// Завершаемым символом конструкции должна быть закрытая круглая скобка
        // Если скобка отсутствует, то укажем на ошибку
        return stringInputUser[index] == ')' ? true : false;
    }

    // Метод ищет цифру
    bool FindDigital(int index)
    {
        // Если прошли все прошлые проверки, то теперь
        // ищем первое число затем еще одно число через пробел, и
        // уже потом запятую и снова число.

        // Ищем первую цифру.
        for (int i = index; i < stringInputUser.length(); i++) {
            if (!IsSpaceSymbol(i)) {
                if (IsDigitalSymbol(i))

                    return true;
                return false;
            }
        }
        return false;
    }
};

int main()
{
    // веденная пользователем строка
    string inputString;

    // Строка для обработки
    UserString userString;

    // Размерность массива с ключевыми словами
    int sizeArrayKeyWords = 3;

    // Массив с ключевыми словами
    string arrayKeyWords[sizeArrayKeyWords] = {"circle", "triangle", "polygon"};

    // Считываем строку введенную пользователем с пробелами и переносами
    // строк. Поскольку стандартный метод ввода не позволяет считать
    // строку с пробелами
    getline(cin, inputString);

    // Задаю строку
    userString.SetString(inputString);

    // Добавляю в конец строки нулевой символ
    userString.AppendZeroSymbol();

    // Ищем ключевое слово
    userString.FindKeyWord();

    switch (userString.RetunIndexArrayCompare(arrayKeyWords, sizeArrayKeyWords)) {
    case -1: // Ввели что-то неизвестное
        cout << "ошибка";
        break;

    case 0: // Круг

        if (userString.IsOpenParenthesis()) {
            if (userString.FindDigital(userString.indexStr + 1)) {
                cout << "Digital";
            } else {
                cout << "NotDigital";
            }

        } else {
            cout << "Символ #" << userString.indexStr + 1 << " должен быть - ( \n";
        }

        break;

    case 1: // треугольник
        if (userString.IsOpenParenthesis()) {
            cout << "Скобка есть";
        } else {
            cout << "Символ #" << userString.indexStr + 1 << " должен быть - ( \n";
        }
        break;

    case 2: // Полигон
        if (userString.IsOpenParenthesis()) {
            cout << "Скобка есть";
        } else {
            cout << "Символ #" << userString.indexStr + 1 << " должен быть - ( \n";
        }
        break;

    default:
        break;
    }

    return 0;
}