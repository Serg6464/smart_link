#include <string>
#include <icondition.h>

#include <iostream>
#include <ctime>
#include <sstream>

#define PluginConditionName "date_before"

extern "C"{
void getConditionName(std::string *destination);
ICondition *CreateNewConditionObj(const std::string &param);
}

class PluginCondition: public ICondition
{
    std::string _reference_value;
public:
    PluginCondition(std::string reference_value)
        :_reference_value(reference_value)
    {
    };

    // ICondition interface
public:

    // Функция для проверки даты
    int compareDateLessFromCurrent(const std::string& dateString) {
        // Проверяем формат строки
        if (dateString.length() != 10 || dateString[2] != '-' || dateString[5] != '-') {
            std::cerr << "Неверный формат даты. Должно быть ДД-ММ-ГГГГ" << std::endl;
            return -1;
        }

        // Разбираем входную строку
        int day, month, year;
        std::istringstream iss(dateString);
        char dash;
        iss >> day >> dash >> month >> dash >> year;

        // Получаем текущую дату
        time_t now = time(0);
        struct tm now_tm = *localtime(&now);

        // Создаем tm структуру для входной даты
        struct tm input_tm = {0};
        input_tm.tm_year = year - 1900;  // в tm год относительно 1900
        input_tm.tm_mon = month - 1;    // в tm месяцы от 0 до 11
        input_tm.tm_mday = day;

        // Преобразуем tm в time_t
        time_t input_time = mktime(&input_tm);
        time_t current_time = mktime(&now_tm);

        // Сравниваем времена
        if (current_time < input_time ) {
            return 1;  // время не настало
        } else {
            return 0;  // текущее время больше или равно заданному
        }
    }
    bool Check(JsonPtr json)
    {
        //std::string date = "29-05-2025";
        return compareDateLessFromCurrent(_reference_value) > 0;
    };
};

void getConditionName(std::string *destination) {
    *destination = PluginConditionName;
}
ICondition *CreateNewConditionObj(const std::string &param)
{
    return new PluginCondition(std::string(param));
}
