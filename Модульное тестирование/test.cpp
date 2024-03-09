#include <UnitTest++/UnitTest++.h>
#include "md5.h"
#include "Client.h"
#include "termcolor.h"

using namespace std;

struct Test {
    Client * p;
    Test()
    {
        p = new Client();
    }
    ~Test()
    {
        delete p;
    }
};

SUITE(Server)
{

// Правильно
    TEST_FIXTURE(Test, Ok) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        p->Server("127.0.0.1", "33333");
        CHECK(true);
    }
    
// Не верный ip-адрес
    TEST_FIXTURE(Test, Ip1) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        CHECK_THROW(p->Server("77777777", "33333"), client_error);
    }
    
// Пустой адрес    
    TEST_FIXTURE(Test, Ip2) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        CHECK_THROW(p->Server(" ", "33333"), client_error);
    }
    
// Не верный порт
    TEST_FIXTURE(Test, Port1) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        CHECK_THROW(p->Server("127.0.0.1", "7777"), client_error);
    }
    
// Пустой порт
	TEST_FIXTURE(Test, Port2) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        CHECK_THROW(p->Server("127.0.0.1", " "), client_error);
    }
    
// Не открывается файл с авторизацией
    TEST_FIXTURE(Test, Aut1) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclietnt.conf";;
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
    
// Пустой файл авторизации
    TEST_FIXTURE(Test, Aut2) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/pustoy.txt";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
    
// Неверный логин
    TEST_FIXTURE(Test, Login) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/Nouser.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
    
// Неверный пароль
    TEST_FIXTURE(Test, Parol) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/NoPswd.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
    
// Не правильный путь к векторам
    TEST_FIXTURE(Test, Vector1) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector1.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
    
// Пустые вектора
    TEST_FIXTURE(Test, Vector2){
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/pustoy.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
    
// Неверный путь к файлу с результатами    
    TEST_FIXTURE(Test, Rez) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/resultat.bin";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
    
// Неверный путь к файлу с авторизацией
    TEST_FIXTURE(Test, InvalidVectorFile) {
    	p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
    	p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
    	p->autification = "/home/stud/Desktop/vclient.conf";
    	CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
	}
	
// Проверка на расширение файлов с векторами	
	TEST_FIXTURE(Test, Rashirenie1) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.geck";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.txt";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        CHECK_THROW(p->Server("127.0.0.1", "33333"), client_error);
    }
    
// Проверка на расширение файла с результатами
    TEST_FIXTURE(Test, Rashirenie2) {
        p->vectora = "/home/stud/Desktop/gotovay_kursovay/vector.txt";
        p->result = "/home/stud/Desktop/gotovay_kursovay/rez.geck";
        p->autification = "/home/stud/Desktop/gotovay_kursovay/vclient.conf";
        p->Server("127.0.0.1", "33333");
        CHECK(true);
    }
}

int main(){
    return UnitTest::RunAllTests();
}
