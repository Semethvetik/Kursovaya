/**
* @file Client.cpp
* @author Сорокина С.В.
* @version 1.0
* @date 02.03.2024
* @copyright ИБСТ ПГУ
* @brief Модуль клиента
*/

//@brief Подключение Модулей
#include "md5.h"
#include "Client.h"
#include "termcolor.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//@brief Функция клиента
int Client::Server(string str1, string str2)
{
	// Порт по умолчанию
    if(str2 == "") {
        str2 = "33333";
    }
	// Проверка на пустую строку файла аутентификации, назначение по умолчанию
    if(autification == "") {
        autification = "vclient.conf";
    }

    // Открытие файла для аутентификации
    ifstream fautf(autification);

    if(!fautf.is_open()) {
        throw client_error(string("Функция: autification.\n Ошибка открытия файла для аутентификации"));
    }
    if(fautf.peek() == EOF) {
        fautf.close();
        throw client_error(string("Функция: autification.\n Файл для аутентификации пуст"));
    }

    getline(fautf, line);
    int k = line.find(" ");
    username = line.substr(0, k);
    password = line.erase(0, k+1);

    // Открытие файла для чтения векторов
    ifstream fvector(vectora);

    if(!fvector.is_open()) {
        fvector.close();
        throw client_error(string("Функция: vectora.\n Ошибка отрытия исходного файла с векторами"));
    }
    if(fvector.peek() == EOF) {
        fvector.close();
        throw client_error(string("Функция: vectora.\n Файл с векторами пуст"));
    }
    
    // Открытие файла для записи суммы
    ofstream fresultat(result);

    if(!fresultat.is_open()) {
        fresultat.close();
        throw client_error(string("Функция: result.\n Ошибка отрытия файла для результатов"));
    }

    char buf[255];

    try {
        
        strcpy(buf,str1.c_str());
    } catch (...) {
        throw client_error(std::string("Функция: buf.\n Невозможно получить адрес"));
    }

    try {

        port = stoi(str2);
    } catch (...) {
        throw client_error(string("Функция: port.\n Невозможно получить порт"));
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Соединение клиента с сервером
    
    // @brief объект, selfAddr, инициализируется с использованием семейства адресов AF_INET, порт устанавливается в 0, IP-адрес устанавливается в 0.
    sockaddr_in * selfAddr = new (sockaddr_in);
    selfAddr->sin_family = AF_INET;
    selfAddr->sin_port = 0;
    selfAddr->sin_addr.s_addr = 0;
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	// @brief объект, remoteAddr, также инициализируется с использованием семейства адресов AF_INET, порт устанавливается с использованием функции htons, которая преобразует 16-битное беззнаковое целое число из  сетевого порядка байтов в порядок байтов хоста, а IP-адрес устанавливается с использованием функции inet_addr, которая преобразует строку IP-адреса в 32-битное беззнаковое целое число.
    sockaddr_in * remoteAddr = new (sockaddr_in);
    remoteAddr->sin_family = AF_INET;
    remoteAddr->sin_port = htons(port);
    remoteAddr->sin_addr.s_addr = inet_addr(buf);

    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if(mySocket == -1) {
        close(mySocket);
        throw client_error(string("Функция: mySocket.\n Ошибка создания сокета"));
    }

    int rc = bind(mySocket,(const sockaddr *) selfAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: selfAddr.\n Ошибка привязки сокета с локальным адресом"));
    }

    rc = connect(mySocket, (const sockaddr*) remoteAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: remoteAddr.\n Ошибка подключения сокета к удаленному серверу"));
    }

    char *buffer = new char[4096];
    strcpy(buffer,username.c_str());
    int massageLen = strlen(buffer);

    rc = send(mySocket, buffer, massageLen, 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\n Ошибка отправки логина"));
    }
    cout << termcolor::bold << termcolor::green << "Логин: " << buffer << termcolor::reset << endl;

    rc = recv(mySocket, buffer, 4096, 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\n Ошибка получения ответа"));
    }
    string s1 = string(buffer);
    buffer[rc] = '\0';
    cout << termcolor::bold << termcolor::green << "Соль: " << buffer << termcolor::reset << endl;

    string hsh = s1 + password;
    massage = MD5_hash(hsh);

    strcpy(buffer,massage.c_str());
    rc = send(mySocket, buffer, massage.length(), 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: massage.\n Ошибка отправки хэша"));
    }
    cout << termcolor::bold << termcolor::green << "Хэш: " << buffer << termcolor::reset << endl;

    rc = recv(mySocket, buffer, sizeof(buffer), 0);
    buffer[rc] = '\0';
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\n Ошибка получения ответа об аутентификации"));
    }
    cout << termcolor::bold << termcolor::green << "Ответ об аутентификации: " << buffer << termcolor::reset << endl;

    getline(fvector, line);
    int len = stoi(line);

    rc = send(mySocket, &len, sizeof(len), 0);
    if (rc == -1) {
        close(mySocket);
        throw client_error(string("Функция: buffer.\n Ошибка отправки количества векторов"));
    }
    cout << termcolor::bold << termcolor::green << "Число векторов: " << len << termcolor::reset << endl;


    for(int l = 0; l < len; l++) {
        getline(fvector, line);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Получение вектора
        
        int r=0;
        int strl = line.length();
        for (int k=0; k<strl; k++)
            if (line[k]==' ') r++;
        int size = r+1;

        int16_t array[size] = {0};
        for(int j = 0; j < size; j++) {
            string a;
            int i = line.find(" ");
            a = line.substr(0, i); 
            line = line.erase(0, i+1);
            array[j] = stod(a);
        }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Отправка векторов
        
        rc = send(mySocket, &size, sizeof(size), 0);
        if (rc == -1) {
            close(mySocket);
            throw client_error(string("Функция: buffer.\n Ошибка отправки размера векторов"));
        }
        cout << termcolor::bold << termcolor::green << "Размер вектора: " << size << termcolor::reset << endl;

        rc = send(mySocket, &array, sizeof(array), 0);
        if (rc == -1) {
            close(mySocket);
            throw client_error(string("Функция: buffer.\n Ошибка отправки векторов"));
        }
        cout << termcolor::bold << termcolor::green << "Весь вектор: " << array << termcolor::reset << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Получение результата
		rc = recv(mySocket, &summa, sizeof(summa), 0);
		if (rc == -1) {
    		close(mySocket);
    		throw client_error(string("Функция: buffer.\n Ошибка получения ответа в виде суммы"));
		}
		cout << termcolor::bold << termcolor::green << "Результат вычислений: " << summa << termcolor::reset << endl;
		
		ofstream outputFile(result);
		outputFile << static_cast<int16_t>(summa);
		outputFile.close();
    }

    close(mySocket);

    delete selfAddr;
    delete remoteAddr;
    delete[] buffer;
    return 0;
}
