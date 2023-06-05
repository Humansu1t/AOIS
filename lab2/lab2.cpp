#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class logic_formula
{
private:
	struct set
	{
		bool x1;
		bool x2;
		bool x3;
		bool f;
	};
	struct Stack
	{
		Stack* next;
		char info;
	};
	set table[8];
	string formula;
	string sdnf;
	string sknf;
	string numeric_binary_sdnf;
	string numeric_binary_sknf;
	string numeric_decimal_sdnf;
	string numeric_decimal_sknf;
	string index;

	Stack* push_(Stack* p, bool in)
	{
		Stack* t = new Stack;
		t->info = in;
		t->next = p;
		return t;
	}
	Stack* push(Stack* p, char in)
	{
		Stack* t = new Stack;
		t->info = in;
		t->next = p;
		return t;
	}
	Stack* pop(Stack* p, char* out)
	{
		Stack* t = p;
		*out = p->info;
		p = p->next;
		delete t;
		return p;
	}
	Stack* pop_(Stack* p, bool* out)
	{
		Stack* t = p;
		*out = p->info;
		p = p->next;
		delete t;
		return p;
	}
	int prior(char operat)
	{
		switch (operat)
		{
		case '!': return 4;
		case '*': return 3;
		case '+': return 2;
		case '(': return 1;
		}
		return 0;
	}
	string translate(string in)
	{
		string out;
		Stack* st = NULL;
		char buff;
		for (int i = 0; i < in.length(); i++)
		{
			if (in[i] == '(')
			{
				st = push(st, in[i]);
			}
			if (in[i] == ')')
			{
				while ((st->info) != '(')
				{
					st = pop(st, &buff);
					out += buff;
				}
				st = pop(st, &buff);
			}
			if (in[i] >= 'a' && in[i] <= 'c')
			{
				out += in[i];
			}
			if (in[i] == '*' || in[i] == '+' || in[i] == '!')
			{
				while (st != NULL && prior(st->info) >= prior(in[i]))
				{
					st = pop(st, &buff);
					out += buff;
				}
				st = push(st, in[i]);
			}
		}
		while (st != NULL)
		{
			st = pop(st, &buff);
			out += buff;
		}
		return out;
	}
	double result(string in, bool a, bool b, bool c)
	{
		Stack* st_val = NULL;
		bool n1, n2, res;
		for (int i = 0; i < in.length(); i++)
		{
			switch (in[i])
			{
			case 'a': st_val = push_(st_val, a); break;
			case 'b': st_val = push_(st_val, b); break;
			case 'c': st_val = push_(st_val, c); break;
			case '+':
			{
				st_val = pop_(st_val, &n2);
				st_val = pop_(st_val, &n1);
				res = n1 | n2;
				st_val = push_(st_val, res);
				break;
			}
			case '*':
			{
				st_val = pop_(st_val, &n2);
				st_val = pop_(st_val, &n1);
				res = n1 & n2;
				st_val = push_(st_val, res);
				break;
			}
			case '!':
			{
				st_val = pop_(st_val, &n1);
				res = !n1;
				st_val = push_(st_val, res);
				break;
			}
			}
		}
		return res;
	}
public:
	logic_formula(string fl)
	{
		formula = fl;
		sdnf = "";
		sknf = "";
		numeric_binary_sdnf = "";
		numeric_binary_sknf = "";
		numeric_decimal_sdnf = "";
		numeric_decimal_sknf = "";
		index = "";

		//table initialization
		table[0].x1 = 0;
		table[0].x2 = 0;
		table[0].x3 = 0;

		table[1].x1 = 1;
		table[1].x2 = 0;
		table[1].x3 = 0;

		table[2].x1 = 0;
		table[2].x2 = 1;
		table[2].x3 = 0;

		table[3].x1 = 0;
		table[3].x2 = 0;
		table[3].x3 = 1;

		table[4].x1 = 1;
		table[4].x2 = 1;
		table[4].x3 = 0;

		table[5].x1 = 0;
		table[5].x2 = 1;
		table[5].x3 = 1;

		table[6].x1 = 1;
		table[6].x2 = 0;
		table[6].x3 = 1;

		table[7].x1 = 1;
		table[7].x2 = 1;
		table[7].x3 = 1;

		string reverse_polish_formula = translate(formula);
		for (int i = 0; i < 8; i++)
		{
			table[i].f = result(reverse_polish_formula,
				table[i].x1, table[i].x2, table[i].x3);
		}
		//SDNF initialization
		for (int i = 0; i < 8; i++)
		{
			if (table[i].f == 1)
			{
				if (table[i].x1 == 0)
				{
					sdnf += "!a*";
				}
				else
				{
					sdnf += "a*";
				}

				if (table[i].x2 == 0)
				{
					sdnf += "!b*";
				}
				else
				{
					sdnf += "b*";
				}

				if (table[i].x3 == 0)
				{
					sdnf += "!c";
				}
				else
				{
					sdnf += "c";
				}

				sdnf += "+";
			}
		}
		sdnf.erase(sdnf.begin() + sdnf.size() - 1);
		//SKNF initialization
		for (int i = 0; i < 8; i++)
		{
			if (table[i].f == 0)
			{
				sknf += "(";
				if (table[i].x1 == 1)
				{
					sknf += "!a+";
				}
				else
				{
					sknf += "a+";
				}

				if (table[i].x2 == 1)
				{
					sknf += "!b+";
				}
				else
				{
					sknf += "b+";
				}

				if (table[i].x3 == 1)
				{
					sknf += "!c";
				}
				else
				{
					sknf += "c";
				}

				sknf += ")";
				sknf += "*";
			}
		}
		sknf.erase(sknf.begin() + sknf.size() - 1);
		//numeric binary SDNF initialization
		for (int i = 0; i < 8; i++)
		{
			if (table[i].f == 1)
			{
				numeric_binary_sdnf += to_string(table[i].x1);
				numeric_binary_sdnf += to_string(table[i].x2);
				numeric_binary_sdnf += to_string(table[i].x3);
				numeric_binary_sdnf += "+";
			}
		}
		numeric_binary_sdnf.erase(numeric_binary_sdnf.begin()
			+ numeric_binary_sdnf.size() - 1);
		//numeric binary SKNF initialization
		for (int i = 0; i < 8; i++)
		{
			if (table[i].f == 0)
			{
				numeric_binary_sknf += to_string(table[i].x1);
				numeric_binary_sknf += to_string(table[i].x2);
				numeric_binary_sknf += to_string(table[i].x3);
				numeric_binary_sknf += "*";
			}
		}
		numeric_binary_sknf.erase(numeric_binary_sknf.begin()
			+ numeric_binary_sknf.size() - 1);
		//numeric decimal SDNF initialization
		string buff = "";
		for (int i = 0; i < 8; i++)
		{
			if (table[i].f == 1)
			{
				buff = "";
				buff += to_string(table[i].x1);
				buff += to_string(table[i].x2);
				buff += to_string(table[i].x3);

				int l, a, i, k;
				l = buff.size();
				a = 0;
				k = 1;
				if (buff[l] == '1')
				{
					a = a + k;
				}
				for (i = l - 1; i >= 0; --i)
				{
					if (buff[i] == '1')
					{
						a = a + k;
					}
					k = k * 2;
				}

				buff = to_string(a);

				numeric_decimal_sdnf += buff;
				numeric_decimal_sdnf += "+";
			}
		}
		numeric_decimal_sdnf.erase(numeric_decimal_sdnf.begin()
			+ numeric_decimal_sdnf.size() - 1);
		//numeric decimal SKNF initialization
		for (int i = 0; i < 8; i++)
		{
			if (table[i].f == 0)
			{
				buff = "";
				buff += to_string(table[i].x1);
				buff += to_string(table[i].x2);
				buff += to_string(table[i].x3);

				int l, a, i, k;
				l = buff.size();
				a = 0;
				k = 1;
				if (buff[l] == '1')
				{
					a = a + k;
				}
				for (i = l - 1; i >= 0; --i)
				{
					if (buff[i] == '1')
					{
						a = a + k;
					}
					k = k * 2;
				}

				buff = to_string(a);

				numeric_decimal_sknf += buff;
				numeric_decimal_sknf += "*";
			}
		}
		numeric_decimal_sknf.erase(numeric_decimal_sknf.begin()
			+ numeric_decimal_sknf.size() - 1);
		//index initialization
		buff = "";
		for (int i = 0; i < 8; i++)
		{
			buff += to_string(table[i].f);
		}
		int l, a, i, k;
		l = buff.size();
		a = 0;
		k = 1;
		if (buff[l] == '1')
		{
			a = a + k;
		}
		for (i = l - 1; i >= 0; --i)
		{
			if (buff[i] == '1')
			{
				a = a + k;
			}
			k = k * 2;
		}
		index = to_string(a);
	}

	void print_table()
	{
		cout << "#" << '\t' << "1" << '\t' << "2" << '\t' << "3"
			<< '\t' << "4" << '\t' << "5" << '\t' << "6" << '\t'
			<< "7" << '\t' << "8";
		cout << endl << "___________________________________________________________________";
		cout << endl << "a" << '\t';
		for (int i = 0; i < 8; i++)
		{
			cout << table[i].x1 << "\t";
		}
		cout << endl << "b" << '\t';
		for (int i = 0; i < 8; i++)
		{
			cout << table[i].x2 << "\t";
		}
		cout << endl << "c" << '\t';
		for (int i = 0; i < 8; i++)
		{
			cout << table[i].x3 << "\t";
		}
		cout << endl << "___________________________________________________________________";
		cout << endl << "f" << '\t';
		for (int i = 0; i < 8; i++)
		{
			cout << table[i].f << "\t";
		}
	}
	void print_SDNF()
	{
		cout << sdnf;
	}
	void print_SKNF()
	{
		cout << sknf;
	}
	void print_numeric_binary_sdnf()
	{
		cout << numeric_binary_sdnf;
	}
	void print_numeric_binary_sknf()
	{
		cout << numeric_binary_sknf;
	}
	void print_numeric_decimal_sdnf()
	{
		cout << numeric_decimal_sdnf;
	}
	void print_numeric_decimal_sknf()
	{
		cout << numeric_decimal_sknf;
	}
	void print_index()
	{
		cout << index;
	}
};

int main()
{
	string formula;
	cout << "Enter the formula: ";
	getline(cin, formula);
	logic_formula lf(formula);
	cout << endl;
	lf.print_table();
	cout << endl << endl << "SDNF: ";
	lf.print_SDNF();
	cout << endl << "SKNF: ";
	lf.print_SKNF();
	cout << endl << endl << "Binary SDNF: ";
	lf.print_numeric_binary_sdnf();
	cout << endl << "Binary SKNF: ";
	lf.print_numeric_binary_sknf();
	cout << endl << endl << "Decimal SDNF: ";
	lf.print_numeric_decimal_sdnf();
	cout << endl << "Decimal SKNF: ";
	lf.print_numeric_decimal_sknf();
	cout << endl << endl << "Index: ";
	lf.print_index();
	cout << endl << endl;
	system("pause");
	return 0;
}
