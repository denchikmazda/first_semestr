#include "pch.h" 
#include <iostream> 
#include <fstream> 
#include <string> 
using namespace std;
const int r = 3;
/////////////////////////
inline bool bukva(char c) {
	return (c >= 'A'&&c <= 'Z');
}
inline bool cifra(char c) {
	return (c >= '0'&&c <= '9');
}
inline bool znak(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
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
			cout << top->data[i] << ' ';
		cout << endl;
		top = top->next;
	} cout << endl;
}
bool empty(node *top) {
	return top == NULL;
}
void change(node*top, int mas[r], string name)
{
	bool b = false;
	while (!empty(top) && !b)
	{
		if (top->name == name)
		{
			for (int i = 0; i < r; i++)
				top->data[i] = mas[i];
			b = true;
		}
		top = top->next;
	}
}
node *find_adress(node *top, string name) {
	while (top)
	{
		if (name == top->name)
			return top;
		top = top->next;
	}
	return nullptr;
}
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
	setlocale(LC_ALL, "ru");
	ifstream in("in.txt");
	int s = 0; //состояние
	int p=0,k = 0; //счетчик для массивов 
	int gorner = 0;
	node *top = NULL;
	char c;
	char znakch; //знак для образования числа
	char znakop = '0'; //знак операции 
	string namemas; //название первого массива
	string namemasfind; //название второго массива 
	int temp1[r], temp2[r]; //массивы для выполнения операций
	while (in.get(c) && s != 12 )
	{
		++p;
		switch (s)
		{
		case 0:
			if (bukva(c))
			{
				s = 1;
				namemas.clear();
				namemasfind.clear();
				namemas.push_back(c);
			}
			else { cout << "неправильное имя массива в позиции "<< p << endl; s = 12; } break;
		case 1:
			if (cifra(c) || bukva(c))
			{
				s = 1;
				namemas.push_back(c);
			}
			else if (c == '=') s = 2;
			else { cout << "не найден символ '=' " << endl; s = 12; }
			break;
		case 2:
			if (bukva(c))
			{
				s = 6;
				namemasfind.push_back(c);
			}
			else if (c == '(')
			{
				s = 3;  k = 0; // temp1[0] = c-'0';
			}
			else { cout << "неправильное имя после = или не найдено (" << endl; s = 12; }
			break;
		case 3:
			if (c == '-' || c == '+')
			{
				znakch = c; s = 4;
			}
			else { cout << "error in case 3, dont find znak of number" << endl; s = 12; }
			break;
		case 4:
			if (cifra(c))
			{
				gorner = (c - '0') + gorner * 10; //собираем число 
				s = 4;
			}
			else if (c == ','&&k < 2)
			{
				if (znakch == '-')
					temp1[k] = gorner * -1;
				else temp1[k] = gorner;
				gorner = 0;
				++k;
				s = 3;
			}
			else if (c == ')'&&k == 2)
			{
				s = 5;
				if (znakch == '-')
					temp1[k] = gorner * -1;
				else temp1[k] = gorner;
				gorner = 0;
			}
			else
			{
				cout << "error in case 4, dont find ',' or ')' " << endl;
				s = 12;
			} break;
		case 5:
			if (c == ';')
			{
				if (find_adress(top, namemas))
				{
					change(top, temp1, namemas);
					s = 0;
					k = 0;
					namemas.clear();
				}
				else {
					push(top, temp1, namemas);
					s = 0;
					k = 0;
					namemas.clear();
				}
			}
			else if (k < 2)
			{
				cout << "kolvo numbers in array < 3 case 4 " << endl;
				s = 12;
				k = 0;
			}
			else if (znak(c)) {
				znakop = c;
				k = 0;
				s = 7;
			}
			else {
				cout << "error in case 5, dont find ';' " << endl;
				s = 12;
			} break;
		case 6:
			if (cifra(c) || bukva(c))
			{
				s = 6;
				namemasfind.push_back(c);
			}
			else if (c == ';')
			{
				if (find_adress(top, namemasfind)) // если namemasfind определён то присваиваем
				{
					node*add = find_adress(top, namemasfind);
					for (int i = 0; i < 3; ++i)
						temp1[i] = add->data[i];
					change(top, temp1, namemas);
				}
				else
				{
					cout << "error, var after '=' did not identify в позиции " << p ;
					exit(-1);
				}
			}
			else if (znak(c))
			{
				if (find_adress(top, namemasfind))
				{
					node *add = find_adress(top, namemasfind);
					for (int i = 0; i < 3; ++i)
						temp1[i] = add->data[i];
					znakop = c;
					s = 7;
					namemasfind.clear();
				}
				else
				{
					cout << "error,var not defined в позиции "<< p ;
					exit(-1);
				}
			}
			else
			{
				cout << "error in case 6" << endl; s = 12;
			}
			break;
		case 7:
			if (c == '(')
				s = 8;
			else if (bukva(c))
			{
				namemasfind.push_back(c);
				s = 11;
			}
			else { cout << "error in case 7" << endl; s = 12; }
			break;
		case 8:
			if (c == '-' || c == '+')
			{
				znakch = c; s = 9;
			}
			else { cout << "error in case 8, dont find znak of number" << endl; s = 12; }
			break;
		case 9:
			if (cifra(c))
			{
				gorner = (c - '0') + gorner * 10; //собираем число 
				s = 9;
			}
			else if (c == ','&&k < 2)
			{
				if (znakch == '-')
					temp2[k] = gorner * -1;
				else temp2[k] = gorner;
				gorner = 0;
				++k;
				s = 8;
			}
			else if (c == ')'&&k == 2)
			{
				s = 10;
				if (znakch == '-')
					temp2[k] = gorner * -1;
				else temp2[k] = gorner;
				gorner = 0;
				k = 0;
			}
			else
			{
				cout << "error in case 9" << endl;
				s = 12;
			} break;
		case 10:
			if (c == ';')
			{
				if (find_adress(top, namemas))
				{
					for (int i = 0; i < r; i++)
						temp1[i] = perfomance(temp1[i], temp2[i], znakop);
					change(top, temp1, namemas);
					s = 0;
					k = 0;
				}
				else
				{
					for (int i = 0; i < r; i++)
						temp1[i] = perfomance(temp1[i], temp2[i], znakop);
					push(top, temp1, namemas);
					s = 0;
					k = 0;
				}
			}
			else { cout << "error in 10 case, dont find ';' " << endl; s = 12; }
			break;
		case 11:
			if (cifra(c) || bukva(c))
			{
				s = 11;
				namemasfind.push_back(c);
			}
			else if (c == ';')
			{
				if (find_adress(top, namemas))
				{
					if (find_adress(top, namemasfind))
					{
						node*add = find_adress(top, namemasfind);
						for (int i = 0; i < r; i++)
							temp2[i] = add->data[i];
						for (int i = 0; i < r; i++)
							temp1[i] = perfomance(temp1[i], temp2[i], znakop);
						change(top, temp1, namemas);
						s = 0;
						k = 0;
					}
					else
					{
						cout << "var after '=' did not  identify в позиции " << p << endl;
						exit(-1);
					}
				}
				else
				{
					if (find_adress(top, namemasfind))
					{
						node*add = find_adress(top, namemasfind);
						for (int i = 0; i < r; i++)
							temp2[i] = add->data[i];
						for (int i = 0; i < r; i++)
							temp1[i] = perfomance(temp1[i], temp2[i], znakop);
						push(top, temp1, namemas);
						s = 0;
						k = 0;
					}
					else
					{
						cout << "var after '=' did not  identify в позиции " << p << endl;
						exit(-1);
					}
				}
			}// end c=';'
			else
			{
				cout << "End of file, ';' not found " << endl;
				s = 12;
			}
		} //switch
	} //while
	show_list(top);
	if (s == 12) cout << "Error" << endl;
	else if (s == 0) cout << "Okay" << endl;
	in.close();
	return 0;
}