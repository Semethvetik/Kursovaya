#!/bin/bash

# Проверка неверного порта сервера
echo "Тест 3: Вывод ошибки при неверном порте"
./client -a 127.0.0.1 -p 7777 -d /home/stud/Desktop/gotovay_kursovay/vector.txt -r /home/stud/Desktop/gotovay_kursovay/rez.txt -e /home/stud/Desktop/gotovay_kursovay/vclient.conf
