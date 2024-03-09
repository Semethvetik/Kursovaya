/**
* @file interface.cpp
* @author Сорокина С.В.
* @version 1.0
* @date 02.03.2024
* @copyright ИБСТ ПГУ
* @brief Интерфейс программы
*/

// Клиент, отвечающий за взаимодействие с сервером и обработку ошибок
#include "Client.h"
// Библиотека для изменения цвета в консоли (выбрано для более удобного взаимодействия пользователя с интерфейсом)
#include "termcolor.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// @brief Основная функция интерфейса
int main (int argc, char *argv[])
{
	// @details Соединение
    Client Soedinenie;
    
	// @details Справка при запуске программы без параметров
    if(argc == 1) {
        cout << termcolor::bold << termcolor::magenta << "-help или -h — справка доступных параметров" << termcolor::reset << endl;
       	cout << termcolor::bold << termcolor::magenta << "-a — адрес сервера - обязательный параметр" << termcolor::reset << endl;
        cout << termcolor::bold << termcolor::magenta << "-p — порт сервера - необязательный параметр - значение по умолчанию: 33333" << termcolor::reset << endl;
        cout << termcolor::bold << termcolor::magenta << "-d — имя файла с исходными данными - обязательный параметр" << termcolor::reset  << endl;
        cout << termcolor::bold << termcolor::magenta << "-r — имя файла для сохранения результата - обязательный параметр" << termcolor::reset << endl;
        cout << termcolor::bold << termcolor::magenta << "-e — имя файла для авторизации - необязательный параметр" << termcolor::reset << endl;
        return 0;
    }

    string str1;
    string str2;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int opt;
    // @brief Кейсы с параметрами, доступные для ввода
    
    while ((opt=getopt (argc,argv,"h::a:p:d:r:e:"))!=-1) {

        switch(opt) {
        
		// @brief Кейс со справкой об использовании программы
        case 'h':
        	cout << termcolor::bold << termcolor::magenta << "-help или -h — справка доступных параметров" << termcolor::reset << endl;
       		cout << termcolor::bold << termcolor::magenta << "-a — адрес сервера - обязательный параметр" << termcolor::reset << endl;
        	cout << termcolor::bold << termcolor::magenta << "-p — порт сервера - необязательный параметр - значение по умолчанию: 33333" << termcolor::reset << endl;
        	cout << termcolor::bold << termcolor::magenta << "-d — имя файла с исходными данными - обязательный параметр" << termcolor::reset  << endl;
        	cout << termcolor::bold << termcolor::magenta << "-r — имя файла для сохранения результата - обязательный параметр" << termcolor::reset << endl;
        	cout << termcolor::bold << termcolor::magenta << "-e — имя файла для авторизации - необязательный параметр" << termcolor::reset << endl;
            return 0;
        
        // @brief Кейс для установки адреса сервера
        case 'a':
            str1 = string(optarg);
            break;
            
		// @brief Кейс для установки порта сервера
        case 'p':
                str2 = string(optarg);
            break;
            
        // @brief Кейс для входного текстового файла    
        case 'd':
            Soedinenie.vectora = string(optarg);
            break;
            
		// @brief Кейс для выходного текстового файла
        case 'r':
            Soedinenie.result = string(optarg);
            break;
            
		// @brief Кейс для файла с логином и паролем
        case 'e':
            Soedinenie.autification = string(optarg);
            break;
            
		// @brief Кейс для неизвестных параметров
        case '?':
            cout << termcolor::bold << termcolor::red << "Неверный параметр - ознакомьтесь со справкой доступных параметров (-h или -help)" << termcolor::reset << endl;
            return 0;
        };
    };

    Soedinenie.Server(str1, str2);
    return 0;
};
