// SEM_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
////////////////////////
const int r = 3;
struct node
{
	string name;
	int mas[r];
	node* next;
};
node*create()
{
	return nullptr;
}
bool empty(node*top)
{
	return top == nullptr;
}
void push(node*&top, int mas[r], string name)
{
	node*p = new node;
	p->name = name;
	for (int i = 0; i < r; i++)
		p->mas[i] = mas[i];
	p->next = top;
	top = p;
}
node*is_element(node*top, string name)
{
	while (top)
	{
		if (top->name == name)
			return top;
		top = top->next;
	}
	return nullptr;
}
void show(ostream&f, node*top)
{
	while (top)
	{
		f << top->name << '=';
		for (int i = 0; i < r; i++)
		{
			f << top->mas[i] << ' ';
		}
		f << endl;
		top = top->next;
	}
	f << endl;
}
void change_node(node*top, string name, int mas[])
{
	bool b = false;
	while (!empty(top) && !b)
	{
		if (top->name == name)
		{
			for (int i = 0; i < r; i++)
				top->mas[i] = mas[i];
			b = true;
		}
		top = top->next;
	}
}
inline bool cifra(char c)
{
	return (c >= '0'&&c <= '9');
}
////////////////////////
inline bool bukva(char c)
{
	return (c >= 'A'&&c <= 'Z');
}
////////////////////////
inline bool oper(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}
///////////////////////
inline bool razdel(char c)
{
	return (c == '(' || c == ')');
}
int main()
{
	ifstream in("in.txt");
	int s = 0, k, znak=1;
	char symb,op;	
	string name_temp, var_temp;
	node* top = create();
	int mas1[r], mas2[r];
	while (in.get(symb) && s != 15)
	{
		switch (s)
		{
		case 0:
			if (bukva(symb))
			{
				name_temp.clear();
				var_temp.clear();
				s = 1;
				name_temp.push_back(symb);
			}
			else { cout << "Wrong name of variable"; s = 15; } break;
		case 1:
			if (cifra(symb) || bukva(symb))
			{
				s = 1;
				name_temp.push_back(symb);
			}
			else if (symb == '=')
				s = 2;
			else { cout << "Wrong name before '='"; s = 15; } break;
		case 2:
			if (symb == '(')
			{
				s = 3; k = 0;
			}
			else if (bukva(symb)) { var_temp.push_back(symb); s = 4; }
			else { cout << "Error after '='"; s = 15; } break;
		case 3:
			if (symb == '+') { s = 5; k++; }
			else if (symb == '-') { s = 5; znak = znak * (-1); k++; }
			else { cout << "Wrong array"; s = 15; } break;
		case 4:
			if (cifra(symb) || bukva(symb))
			{
				var_temp.push_back(symb); s = 4;
			}
			else if (oper(symb)) { s = 8; op = symb; }
			else if (symb == ';') 
			{
				if (is_element(top,name_temp))
					if (is_element(top, var_temp))
					{
						node*temp = is_element(top, var_temp);
						for (int i = 0; i < r; i++)
							mas1[i] = temp->mas[i];
						change_node(top, name_temp, mas1);
					}
					else { cout << "Var is not identify" << endl; s = 15; }
				else push(top, mas1, name_temp);
				s = 0;
			}
			else if (symb == '.') 
			{
				if (is_element(top, name_temp))
					if (is_element(top, var_temp))
					{
						node*temp = is_element(top, var_temp);
						for (int i = 0; i < r; i++)
							mas1[i] = temp->mas[i];
						change_node(top, name_temp, mas1);
					}
					else { cout << "Var is not identify" << endl; s = 15; }
				else push(top, mas1, name_temp);
				s = 14;
			}
			else { cout << "Wrong operation of array"; s = 15; } break;
		case 5:
			if (cifra(symb))
			{
				s = 6;
				name_temp.push_back(symb);
			}
		}
	if (s != 9) cout << "Error" << endl;
	else cout << "Okay" << endl;
}
// need performance of array;



/*
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
		} */
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
