#include "pch.h" 
#include <iostream> 
#include <fstream> 
#include <string> 
using namespace std;
const int r = 3;
/////////////////////////
bool bukva(char c) {
	return (c >= 'A'&&c <= 'Z');
}
bool cifra(char c) {
	return (c >= '0'&&c <= '9');
}
bool znak(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}
bool razd(char c) {
	return (c == ';' || c == ':' || c == '=' || c == '(' || c == ')' || c == '|');
}

struct node {
	string name;
	int data[r];
	node *next;
};

void push(node *&top, int temp1[r], string name) {
	node *p = new node;
	p->name = name;
	for (int i = 0; i < r; ++i)
		p->data[i] = temp1[i];
	p->next = top;
	top = p;
}

void show_list(node *top) {
	while (top) {
		cout << top->name << '=' << endl;
		for (int i = 0; i < r; i++)
		{
			cout << top->data[i] << ' ';
		}
		cout << endl;
		top = top->next;
	} cout << endl;
}
node* exist_element(string name, node*top)
{
	while (top)
	{
		if (name == top->name)
			return top;
		top = top->next;
	}
	return nullptr;
}
bool empty_list(node *top) {
	return top == NULL;
}

node *find_adress(node *top, string name) {
	node *p = top;
	while (p && (p->name != name))
		p = p->next;
	return p;
}
/*node *find_adress(node *top, string name) {
	while(top)
	{
	if(name==top->name)
			return top;
		top=top->next;
	}
	return nullptr;
}*/
int perfomance(int one, int two, char znakop)
{
	switch (znakop) {
	case '+': return one + two; break;
	case '*': return one * two; break;
	case '/': return one / two; break;
	case '-': return one - two; break;
	}
}
int main()
{
	ifstream in("in.txt");
	int q = 0; //состояние
	int k = 0; //счетчик для массивов 
	int gorner = 0;
	char c;
	node mas; //структура 
	node *top = NULL;
	char znakch; //знак для образования числа
	char znakop = '0'; //знак операции 
	string namemas;
	string namemasfind; //название второго массива 
	int temp1[3]; //массивы для выполнения операций
	int temp2[3]; //массив для выполнения операций 
	in >> c;
	while (q != 19 && !in.eof()) {
		switch (q) {

		case 0: if (bukva(c)) {
			q = 1;
			namemas = namemas + c;
		}
				else {
			cout << "wrong name" << endl;
			q = 19;
		} break;

		case 1: if (bukva(c)) {
			namemas = namemas + c;
			q = 1;
		}
				else if (cifra(c)) {
			namemas = namemas + c;
			q = 2;
		}
				else {
			cout << "wrong name in case 1" << endl;
			q = 19;
		} break;

		case 2: if (cifra(c)) {
			q = 2;
			namemas = namemas + c;
		}
				else if (c == '=') {
			q = 3;
		}
				else
		{
			cout << "dont find = " << endl;
			q = 19;
		} break;

		case 3: if (c == '(')
			q = 4;
				else if (bukva(c)) {
			namemasfind = c;
			q = 9;
		}
				else {
			cout << "dont find razdelitel (" << endl;
			q = 19;
		} break;

		case 4: if (c == '-' || c == '+') {
			znakch = c;
			q = 6;
		}
				else {
			cout << "error in case 4" << endl;
			q = 19;
		} break;

		case 6: if (cifra(c))
		{
			gorner = (c - '0') + gorner * 10; //собираем число 
			q = 6;
		}
				else if (c == ','&&k < 2) {
			if (znakch == '-')
				temp1[k] = gorner * -1;
			else temp1[k] = gorner;
			gorner = 0;
			++k;
			q = 7;
		}
				else if (c == ')') {
			q = 8;
			if (znakch == '-')
				temp1[k] = gorner * -1;
			else temp1[k] = gorner;
			gorner = 0;
		}
				else {
			cout << "error in case 6" << endl;
			q = 19;
		} break;

		case 7: if (znak(c)) {
			znakch = c;
			q = 6;
		}
				else {
			cout << "error in case 7" << endl;
			q = 19;
		} break;
		case 8: if (c == ';'&&znakop == '0'&&k >= 2) {
			if (find_adress(top, namemas) != NULL) {
				node *add = find_adress(top, namemas);
				for (int i = 0; i < 3; ++i)
					add->data[i] = temp1[i];
				q = 0;
				k = 0;
				namemas = "";
			}
			else {
				push(top, temp1, namemas);
				q = 0;
				k = 0;
				namemas = "";
			}
		}
				else if (k < 2) {
			cout << "kolvo numbers in array < 3 case 8" << endl;
			q = 19;
			k = 0;
		}
				else if (c == ';'&&znakop != '0')
		{
			for (int i = 0; i < r; i++)
			{
				temp1[i] = perfomance(temp1[i], temp2[i], znakop);
			}
			if (find_adress(top, namemas) == NULL) {
				push(top, temp1, namemas);
				q = 0;
				k = 0;
				znakop = 0;
				namemas = "";
			}
			else {
				node *add = find_adress(top, namemas);
				for (int i = 0; i < 3; ++i)
					add->data[i] = temp1[i];
				q = 0;
				k = 0;
				namemas = "";
			}
		}
				else if (znak(c)) {
			znakop = c;
			k = 0;
			q = 12;
		}
				else {
			cout << "error in case 8" << endl;
			q = 19;
		} break;
		case 9: if (bukva(c)) {
			q = 9;
			namemasfind = namemasfind + c;
		}
				else if (cifra(c)) {
			namemasfind = namemasfind + c;
			q = 10;
		}
				else {
			cout << "error in case 9" << endl;
			q = 19;
		} break;
		case 10: if (cifra(c)) {
			q = 10;
			namemasfind = namemasfind + c;
		}
				 else if (c == ';') {
			if (namemas != namemasfind) {

				if (find_adress(top, namemas) == NULL) { //если такого нет 
					node *add = find_adress(top, namemasfind);
					node *p = new node;
					p->name = namemas;
					for (int i = 0; i < 3; ++i)
						p->data[i] = add->data[i];
					p->next = top;
					top = p;
				}
				else { //присваивание 
					node *add = find_adress(top, namemas);
					for (int i = 0; i < 3; ++i)
						add->data[i] = temp1[i];
					q = 0;
					k = 0;
					namemas = "";
				}
				q = 0;
				namemas = "";
				k = 0;
			}
		}
				 else if (znak(c)) {
			node *add = find_adress(top, namemasfind);
			for (int i = 0; i < 3; ++i)
				temp1[i] = add->data[i];
			znakop = c;
			q = 11;
		}
				 else {
			cout << "error in case 10" << endl;
			q = 19;
		} break;
		case 11: if (c == '(')
			q = 15;
				 else if (bukva(c)) {
			namemasfind = c;
			q = 13;
		}
				 else {
			cout << "error in case 11" << endl;
			q = 19;
		} break;
		case 12: if (bukva(c)) {
			namemasfind = c;
			q = 13;
		}
				 else if (c == '(')
			q = 15;
				 else {
			cout << "error in case 12" << endl;
			q = 19;
		} break;
		case 13: if (bukva(c)) {
			namemasfind = namemasfind + c;
			q = 13;
		}
				 else if (cifra(c)) {
			namemasfind = namemasfind + c;
			q = 14;
		}
				 else {
			cout << "error in case 13" << endl;
			q = 19;
		} break;
		case 14: if (cifra(c)) {
			namemasfind = namemasfind + c;
			q = 14;
		}
				 else if (c == ';'&&znakop != '0') {
			node *add = find_adress(top, namemasfind);
			for (int i = 0; i < 3; ++i)
				temp2[i] = add->data[i];

			for (int i = 0; i < r; i++)
			{ temp1[i] = perfomance(temp1[i], temp2[i], znakop); }
			if (find_adress(top, namemas) == NULL) {
				push(top, temp1, namemas);
				q = 0;
				k = 0;
				znakop = 0;
				namemas = "";
			}
			else {
				node *add = find_adress(top, namemas);
				for (int i = 0; i < 3; ++i)
					add->data[i] = temp1[i];
				q = 0;
				k = 0;
				namemas = "";
			}
		}
				 else {
			cout << "error in case 14" << endl;
			q = 19;
		} break;

		case 15: if (c == '-' || c == '+') {
			znakch = c;
			q = 16;
		}
				 else {
			cout << "error in case 15" << endl;
			q = 19;
		} break;

		case 16:if (cifra(c))
		{
			gorner = (c - '0') + gorner * 10; //составление числа 
			q = 16;
		}
				else if (c == ','&&k < 2) {
			if (znakch == '-')
				temp2[k] = gorner * -1;
			else temp2[k] = gorner;
			gorner = 0;
			++k;
			q = 17;
		}
				else if (c == ')') {
			q = 18;
			if (znakch == '-')
				temp2[k] = gorner * -1;
			else temp2[k] = gorner;
			gorner = 0;

		}
				else {
			cout << "error in case 16" << endl;
			q = 19;
		}

				break;
		case 17: if (znak(c)) {
			znakch = c;
			q = 16;
		}
				 else {
			cout << "error in case 17" << endl;
			q = 19;
		}
				 break;
		case 18: if (k < 2) {
			cout << " case 18" << endl;
			q = 19;
			k = 0;
		}
				 else if (c == ';'&&znakop != '0'&&k >= 2) {
			for (int i = 0; i < r; i++)
			{
				temp1[i] = perfomance(temp1[i], temp2[i], znakop);
			}
			if (find_adress(top, namemas) == NULL) {
				push(top, temp1, namemas);
				q = 0;
				k = 0;
				znakop = 0;
				namemas = "";
			}
			else {
				node *add = find_adress(top, namemas);
				for (int i = 0; i < 3; ++i)
					add->data[i] = temp1[i];
				q = 0;
				k = 0;
				namemas = "";
			}
		}
				 else {
			cout << "kolvo numbers in array < 3 error in case 18" << endl;
			q = 19;
		}
				 break;
		}
		in >> c;
	}
	show_list(top);
	if (q == 19) cout << "Error" << endl;
	else if (q == 0) cout << "Okay" << endl;
	in.close();
	return 0;
}

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
