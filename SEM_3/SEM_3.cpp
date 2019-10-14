// SEM_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;
////////////////////////
bool cifra(char c)
{
	return (c >= '0'&&c <= '9');
}
////////////////////////
bool bukva(char c)
{
	return (c >= 'A'&&c <= 'Z');
}
////////////////////////
bool oper(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}
///////////////////////
bool razdel(char c)
{
	return (c == '(' || c == ')');
}
int main()
{
	ifstream in("in.txt");
	int s = 0;
	char c;
	while (in.get(c) && s != 10)
	{
		switch (s)
		{
		case 0: if (bukva(c))s = 1;
				else
		{
			cout << "sorry dont start with symbol or cifra" << endl; s = 10;
		} 
		break;
		case 1: if (c == '=')s = 2;
				else if (!(cifra(c)))s = 10; if (bukva(c) || razdel(c)) cout << "don't find '='" << endl; break;
		case 2: if (razdel(c))s = 3;
				else if (bukva(c)) s = 4;
				else
		{
			s = 10; cout << "after '=' must be bukva or razdelitel" << endl;
		} 
		break;
		case 3: if (oper(c)) s = 5;	else
		{
			s = 10; cout << "don't find operation +|-|*|/" << endl;
		}
		break;
		case 4: if (oper(c))s = 5;
				else if (!(cifra(c)))
		{
			s = 10; cout << "don't find operation +|-|*|/" << endl;
		} 
		break;
		case 5: if (cifra(c)) s = 6;
				else if (razdel(c))s = 3;
				else if (bukva(c)) s = 7;
				else 
		{
			s = 10; cout << "don't find '('" << endl;
		} 
		break;
		case 6: if (c == ',')s = 3;
				else if (c == ')')s = 8;
				else if (!(cifra(c))) { s = 10; cout << "don't find ',' or ')'" << endl; } break;
		case 7: if (c == '.')s = 9;
				else if (c == ';')s = 0;
				else if (!(cifra(c))) s = 10; break;
		case 8: if (c == '.')s = 9;
				else if (c == ';')s = 0;
				else s = 10;  break;
		}
	}
	if (s != 9) cout << "Error" << endl;
	else cout << "Okey" << endl;
}
// need performance of array;

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
