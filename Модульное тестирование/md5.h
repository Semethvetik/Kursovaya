/**
* @file md5.h
* @author Сорокина С.В.
* @version 1.0
* @date 02.03.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля md5
*/

// @brief Бибилотеки Сrypto++
#include <cryptopp/hex.h> 
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h> 

using namespace std;

string MD5_hash(string hash);
