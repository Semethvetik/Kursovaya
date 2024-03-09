#!/bin/bash

# Проверка корректного ввода данных
echo "Тест 1: Корректный ввод данных"
./client -a 127.0.0.1 -d vector.txt -r rez.txt -e vclient.conf
