#include "stdafx.h"
#include <iostream>
#include <clocale>
#include <vector>
#include <string>

using namespace std;

class log_form
{
private:
	struct make
	{
		bool x1;
		bool x2;
		bool x3;
		bool f;
	};
	struct List
	{
		List* next;
		char info;
	};
	make tablic[8];
	string form;
	string sdnf;
	string sknf;
	string num_bin_sdnf;
	string num_bin_sknf;
	string num_dec_sdnf;
	string num_dec_sknf;
	string indeks;

	List* push_(List* res_storage, bool in)
	{
		List* temp_storage = new List;
		temp_storage->info = in;
		temp_storage->next = res_storage;
		return temp_storage;
	}
	List* add(List* res_storage, char in)
	{
		List* temp_storage = new List;
		temp_storage->info = in;
		temp_storage->next = res_storage;
		return temp_storage;
	}
	List* del(List* res_storage, char* out)
	{
		List* temp_storage = res_storage;
		*out = res_storage->info;
		res_storage = res_storage->next;
		delete temp_storage;
		return res_storage;
	}
	List* pop_(List* res_storage, bool* out)
	{
		List* temp_storage = res_storage;
		*out = res_storage->info;
		res_storage = res_storage->next;
		delete temp_storage;
		return res_storage;
	}
	int prioritet(char oper)
	{
		switch (oper)
		{
		case '!': return 4;
		case '*': return 3;
		case '+': return 2;
		case '(': return 1;
		}
		return 0;
	}
	string transfer(string inlin) {
		string outline;
		List* st = NULL;
		char buff;
		for (int i = 0; i < inlin.length(); i++) {
			if (inlin[i] == '(') {
				st = add(st, inlin[i]);
			}
			else if (inlin[i] == ')') {
				while (st != NULL && (st->info) != '(') {
					st = del(st, &buff);
					outline += buff;
				}
				if (st != NULL) {
					st = del(st, &buff);
				}
			}
			else if (inlin[i] >= 'a' && inlin[i] <= 'c') {
				outline += inlin[i];
			}
			else if (inlin[i] == '*' || inlin[i] == '+' || inlin[i] == '!') {
				while (st != NULL && prioritet(st->info) >= prioritet(inlin[i])) {
					st = del(st, &buff);
					outline += buff;
				}
				st = add(st, inlin[i]);
			}
		}
		while (st != NULL) {
			st = del(st, &buff);
			outline += buff;
		}
		return outline;
	}
	double res(string inlin, bool a, bool b, bool c) {
		List* st_sense = NULL;
		bool n1, n2, res;
		for (int i = 0; i < inlin.length(); i++) {
			switch (inlin[i]) {
			case 'a':
				st_sense = push_(st_sense, a);
				break;
			case 'b':
				st_sense = push_(st_sense, b);
				break;
			case 'c':
				st_sense = push_(st_sense, c);
				break;
			case '+': {
				if (st_sense != NULL) {
					st_sense = pop_(st_sense, &n2);
				}
				if (st_sense != NULL) {
					st_sense = pop_(st_sense, &n1);
				}
				res = n1 | n2;
				st_sense = push_(st_sense, res);
				break;
			}
			case '*': {
				if (st_sense != NULL) {
					st_sense = pop_(st_sense, &n2);
				}
				if (st_sense != NULL) {
					st_sense = pop_(st_sense, &n1);
				}
				res = n1 & n2;
				st_sense = push_(st_sense, res);
				break;
			}
			case '!': {
				if (st_sense != NULL) {
					st_sense = pop_(st_sense, &n1);
				}
				res = !n1;
				st_sense = push_(st_sense, res);
				break;
			}
			}
		}
		if (st_sense != NULL) {
			st_sense = pop_(st_sense, &res);
		}
		return res;
	}
	
public:
	log_form(string formula)
	{
		form = formula;
		sdnf = "";
		sknf = "";
		num_bin_sdnf = "";
		num_bin_sknf = "";
		num_dec_sdnf = "";
		num_dec_sknf = "";
		indeks = "";

		tablic[0] = { 0, 0, 0, 0 };
		tablic[1] = { 1, 0, 0, 0 };
		tablic[2] = { 0, 1, 0, 0 };
		tablic[3] = { 0, 0, 1, 0 };
		tablic[4] = { 1, 1, 0, 0 };
		tablic[5] = { 0, 1, 1, 0 };
		tablic[6] = { 1, 0, 1, 0 };
		tablic[7] = { 1, 1, 1, 0 };

		string reverse_pol_form = transfer(form);
		for (int iter = 0; iter < 8; iter++)
		{
			tablic[iter].f = res(reverse_pol_form,
				tablic[iter].x1, tablic[iter].x2, tablic[iter].x3);
		}
		for (int iter = 0; iter < 8; iter++)
		{
			if (tablic[iter].f == 1)
			{
				if (tablic[iter].x1 == 0)
				{
					sdnf += "!а*";
				}
				else
				{
					sdnf += "a*";
				}

				if (tablic[iter].x2 == 0)
				{
					sdnf += "!b*";
				}
				else
				{
					sdnf += "b*";
				}

				if (tablic[iter].x3 == 0)
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
		for (int iter = 0; iter < 8; iter++)
		{
			if (tablic[iter].f == 0)
			{
				sknf += "(";
				if (tablic[iter].x1 == 1)
				{
					sknf += "!а+";
				}
				else
				{
					sknf += "а+";
				}

				if (tablic[iter].x2 == 1)
				{
					sknf += "!b+";
				}
				else
				{
					sknf += "b+";
				}

				if (tablic[iter].x3 == 1)
				{
					sknf += "!с";
				}
				else
				{
					sknf += "с";
				}

				sknf += ")";
				sknf += "*";
			}
		}
		sknf.erase(sknf.begin() + sknf.size() - 1);
		for (int iter = 0; iter < 8; iter++)
		{
			if (tablic[iter].f == 1)
			{
				num_bin_sdnf += to_string(tablic[iter].x1);
				num_bin_sdnf += to_string(tablic[iter].x2);
				num_bin_sdnf += to_string(tablic[iter].x3);
				num_bin_sdnf += "+";
			}
		}
		num_bin_sdnf.erase(num_bin_sdnf.begin()
			+ num_bin_sdnf.size() - 1);
		for (int iter = 0; iter < 8; iter++)
		{
			if (tablic[iter].f == 0)
			{
				num_bin_sknf += to_string(tablic[iter].x1);
				num_bin_sknf += to_string(tablic[iter].x2);
				num_bin_sknf += to_string(tablic[iter].x3);
				num_bin_sknf += "*";
			}
		}
		num_bin_sknf.erase(num_bin_sknf.begin()
			+ num_bin_sknf.size() - 1);
		string buff = "";
		for (int iter = 0; iter < 8; iter++)
		{
			if (tablic[iter].f == 1)
			{
				buff = "";
				buff += to_string(tablic[iter].x1);
				buff += to_string(tablic[iter].x2);
				buff += to_string(tablic[iter].x3);

				int l, a, iter, k;
				l = buff.size();
				a = 0;
				k = 1;
				if (buff[l] == '1')
				{
					a = a + k;
				}
				for (iter = l - 1; iter >= 0; --iter)
				{
					if (buff[iter] == '1')
					{
						a = a + k;
					}
					k = k * 2;
				}

				buff = to_string(a);

				num_dec_sdnf += buff;
				num_dec_sdnf += "+";
			}
		}
		num_dec_sdnf.erase(num_dec_sdnf.begin()
			+ num_dec_sdnf.size() - 1);
		for (int iter = 0; iter < 8; iter++)
		{
			if (tablic[iter].f == 0)
			{
				buff = "";
				buff += to_string(tablic[iter].x1);
				buff += to_string(tablic[iter].x2);
				buff += to_string(tablic[iter].x3);

				int l, a, iter, k;
				l = buff.size();
				a = 0;
				k = 1;
				if (buff[l] == '1')
				{
					a = a + k;
				}
				for (iter = l - 1; iter >= 0; --iter)
				{
					if (buff[iter] == '1')
					{
						a = a + k;
					}
					k = k * 2;
				}

				buff = to_string(a);

				num_dec_sknf += buff;
				num_dec_sknf += "*";
			}
		}
		num_dec_sknf.erase(num_dec_sknf.begin()
			+ num_dec_sknf.size() - 1);
		buff = "";
		for (int iter = 0; iter < 8; iter++)
		{
			buff += to_string(tablic[iter].f);
		}
		int l, a, iter, k;
		l = buff.size();
		a = 0;
		k = 1;
		if (buff[l] == '1')
		{
			a = a + k;
		}
		for (iter = l - 1; iter >= 0; --iter)
		{
			if (buff[iter] == '1')
			{
				a = a + k;
			}
			k = k * 2;
		}
		indeks = to_string(a);
	}
	void print_table()
	{
		cout << "#\t1\t2\t3\t4\t5\t6\t7\t8" << endl;
		cout << "_____________________________________________________" << endl;
		cout << "a\t";
		for (int iter = 0; iter < 8; iter++)
		{
			cout << tablic[iter].x1 << "\t";
		}
		cout << endl << "b\t";
		for (int iter = 0; iter < 8; iter++)
		{
			cout << tablic[iter].x2 << "\t";
		}
		cout << endl << "c\t";
		for (int iter = 0; iter < 8; iter++)
		{
			cout << tablic[iter].x3 << "\t";
		}
		cout << endl << "_____________________________________________________" << endl;
		cout << "f\t";
		for (int iter = 0; iter < 8; iter++)
		{
			cout << tablic[iter].f << "\t";
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
	void print_num_bin_sdnf()
	{
		cout << num_bin_sdnf;
	}
	void print_num_bin_sknf()
	{
		cout << num_bin_sknf;
	}
	void print_num_dec_sdnf()
	{
		cout << num_dec_sdnf;
	}
	void print_num_dec_sknf()
	{
		cout << num_dec_sknf;
	}
	void print_indeks()
	{
		cout << indeks;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	string form;
	while (true) {
		cout << "Введите формулу: ";
		getline(cin, form);
		if (form == "1") { break; };
		log_form log_form(form);
		cout << endl;
		log_form.print_table();
		cout << endl << endl << "СДНФ: ";
		log_form.print_SDNF();
		cout << endl << "СКНФ: ";
		log_form.print_SKNF();
		cout << endl << endl << "Бинарный СДНФ: ";
		log_form.print_num_bin_sdnf();
		cout << endl << "Бинарный СКНФ: ";
		log_form.print_num_bin_sknf();
		cout << endl << endl << "Десятичный СДНФ: ";
		log_form.print_num_dec_sdnf();
		cout << endl << "Десятичный СКНФ: ";
		log_form.print_num_dec_sknf();
		cout << endl << endl << "Индекс: ";
		log_form.print_indeks();
		cout << endl << endl;
	}
	return 0;
}
