/**
* @file md5.cpp
* @author Сорокина С.В.
* @version 1.0
* @date 02.03.2024
* @copyright ИБСТ ПГУ
* @brief Модуль хэширования
*/
 
#include "md5.h"
// @brief Объявление именного пространства CryptoPP
using namespace CryptoPP;

// @param hash Сообщение получаемое для хэширования
string MD5_hash(string hash)
{

    // @brief Переменная получаемого сообщения
    string massange; 
    
    Weak1::MD5 hashmd4;  
    // @brief Класс, использующийся для чтения данных из источника и записи их в приемник
    StringSource(hash, true, 
                    new HashFilter(hashmd4, // @brief Класс, использующийся для фильтрации данных перед их хешированием
                                    new HexEncoder( // @brief Класс, использующийся для преобразования двоичных данных в шестнадцатеричную строку
                                        new StringSink(massange)))); // @brief Класс, использующийся для записи данных в приемник
                                        
    // @return Вывод сообщения и его хэша
    return massange;
}
