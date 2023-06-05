#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct set
{
	bool x1;
	bool x2;
	bool x3;
	bool f;
};
struct elem 
{
	int out;
	int count;
	char sign;
};
struct table
{
	bool x1;
	bool x2;
	bool x3;
	bool x4;
	bool y1;
	bool y2;
	bool y3;
	bool y4;
};
vector <set> table_Di;
vector <set> table_Bi1;


vector <set> set_table_Di();
vector <set> set_table_Bi1();
void print_table();
string to_SDNF(vector <set>);
string glued(string);
string dead_end(string);
vector <elem> elements(string);
vector <bool> to_bin(int);
vector <table> to_table(int);
void minimized(vector <table>);
string four_glued(string);

int main()
{
	table_Di = set_table_Di();
	table_Bi1 = set_table_Bi1();

	cout << '\t' << '\t' << '\t' << '\t' << "Variant 1" << endl << endl;

	cout << "Task 1 (1):" << endl;
	print_table();

	cout << endl;
	string sdnf_Di = "";
	string sdnf_Bi1 = "";
	sdnf_Di = to_SDNF(set_table_Di());
	sdnf_Bi1 = to_SDNF(set_table_Bi1());

	cout << "Di SDNF: " << sdnf_Di << endl;
	cout << "Bi1 SDNF: " << sdnf_Bi1 << endl;

	cout << endl << "Di dead end: " << dead_end(glued(sdnf_Di)) << endl;
	cout << "Bi+1 dead end: " << dead_end(glued(sdnf_Bi1)) << endl << endl;

	vector <elem> el_1 = elements(dead_end(glued(sdnf_Di)));
	vector <elem> el_2 = elements(dead_end(glued(sdnf_Bi1)));

	for (int i = 0; i < 3; i++)
	{
		if (el_1[i].out == el_2[i].out)
		cout << el_1[i].count + el_2[i].count << " " << el_1[i].out << "-in " <<
			el_1[i].sign << endl;
		else
		{
			cout << el_1[i].count << " " << el_1[i].out << "-in " <<
				el_1[i].sign << endl;
			cout << el_2[i].count << " " << el_2[i].out << "-in " <<
				el_2[i].sign << endl;
		}
	} 
	int total = 0;
	total += el_1[0].count;
	total += el_1[1].count * el_1[1].out;
	total += el_1[2].count * el_1[2].out;
	total += el_2[0].count;
	total += el_2[1].count * el_2[1].out;
	total += el_2[2].count * el_2[2].out;
	cout << "Total transistors: " << total << endl;


	cout << endl << endl << "Task 2 (a):" << endl;
	vector <table> tbl = to_table(5);
	minimized(tbl);

	system("pause");
    return 0;
}


vector <set> set_table_Di()
{
	set buff;
	vector <set> tbl;

	buff.x1 = 0;
	buff.x2 = 0;
	buff.x3 = 0;
	buff.f = 0;
	tbl.push_back(buff);

	buff.x1 = 0;
	buff.x2 = 0;
	buff.x3 = 1;
	buff.f = 1;
	tbl.push_back(buff);

	buff.x1 = 0;
	buff.x2 = 1;
	buff.x3 = 0;
	buff.f = 1;
	tbl.push_back(buff);

	buff.x1 = 1;
	buff.x2 = 0;
	buff.x3 = 0;
	buff.f = 1;
	tbl.push_back(buff);

	buff.x1 = 0;
	buff.x2 = 1;
	buff.x3 = 1;
	buff.f = 0;
	tbl.push_back(buff);

	buff.x1 = 1;
	buff.x2 = 0;
	buff.x3 = 1;
	buff.f = 0;
	tbl.push_back(buff);

	buff.x1 = 1;
	buff.x2 = 1;
	buff.x3 = 0;
	buff.f = 0;
	tbl.push_back(buff);

	buff.x1 = 1;
	buff.x2 = 1;
	buff.x3 = 1;
	buff.f = 1;
	tbl.push_back(buff);

	return tbl;
}
vector <set> set_table_Bi1()
{
	set buff;
	vector <set> tbl;

	buff.x1 = 0;
	buff.x2 = 0;
	buff.x3 = 0;
	buff.f = 0;
	tbl.push_back(buff);

	buff.x1 = 0;
	buff.x2 = 0;
	buff.x3 = 1;
	buff.f = 0;
	tbl.push_back(buff);

	buff.x1 = 0;
	buff.x2 = 1;
	buff.x3 = 0;
	buff.f = 0;
	tbl.push_back(buff);

	buff.x1 = 1;
	buff.x2 = 0;
	buff.x3 = 0;
	buff.f = 0;
	tbl.push_back(buff);

	buff.x1 = 0;
	buff.x2 = 1;
	buff.x3 = 1;
	buff.f = 1;
	tbl.push_back(buff);

	buff.x1 = 1;
	buff.x2 = 0;
	buff.x3 = 1;
	buff.f = 1;
	tbl.push_back(buff);

	buff.x1 = 1;
	buff.x2 = 1;
	buff.x3 = 0;
	buff.f = 1;
	tbl.push_back(buff);

	buff.x1 = 1;
	buff.x2 = 1;
	buff.x3 = 1;
	buff.f = 1;
	tbl.push_back(buff);

	return tbl;
}
void print_table()
{
	cout << "#" << '\t' << "1" << '\t' << "2" << '\t' << "3"
		<< '\t' << "4" << '\t' << "5" << '\t' << "6" << '\t'
		<< "7" << '\t' << "8";
	cout << endl << "___________________________________________________________________";
	cout << endl << "x1" << '\t';
	for (size_t i = 0; i < table_Di.size(); i++)
	{
		cout << table_Di[i].x1 << "\t";
	}
	cout << endl << "x2" << '\t';
	for (size_t i = 0; i < table_Di.size(); i++)
	{
		cout << table_Di[i].x2 << "\t";
	}
	cout << endl << "x3" << '\t';
	for (size_t i = 0; i < table_Di.size(); i++)
	{
		cout << table_Di[i].x3 << "\t";
	}
	cout << endl << "___________________________________________________________________";
	cout << endl << "Di" << '\t';
	for (size_t i = 0; i < table_Di.size(); i++)
	{
		cout << table_Di[i].f << "\t";
	}
	cout << endl << "Bi+1" << '\t';
	for (size_t i = 0; i < table_Di.size(); i++)
	{
		cout << table_Bi1[i].f << "\t";
	}
	cout << endl;
}
string to_SDNF(vector <set> table)
{
	string sdnf;
	for (size_t i = 0; i < table.size(); i++)
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
	return sdnf;
}
string glued(string sdnf)
{
	vector <string> sets;
	int i = 0;
	int buff = 0;
	struct st
	{
		bool a;
		bool b;
		bool c;
	};

	while (i - 1 != sdnf.length())
	{
		while (sdnf[i] != '+' && i != sdnf.length())
		{
			i++;
		}
		sets.push_back(sdnf.substr(buff, i - buff));
		i++;
		buff = i;
	}
	vector <st> nbr(10);

	for (size_t i = 0; i < sets.size(); i++)
	{
		for (size_t j = 0; j < sets[i].size(); j++)
		{
			if (sets[i][j] == 'a')
			{
				nbr[i].a = true;
			}
			else if (sets[i][j] == 'b')
			{
				nbr[i].b = true;
			}
			else if (sets[i][j] == 'c')
			{
				nbr[i].c = true;
			}
			else if (sets[i][j] == '!')
			{
				j++;
				if (sets[i][j] == 'a')
				{
					nbr[i].a = false;
				}
				else if (sets[i][j] == 'b')
				{
					nbr[i].b = false;
				}
				else if (sets[i][j] == 'c')
				{
					nbr[i].c = false;
				}
			}
		}
	}

	string glued = "";

	for (size_t i = 0; i < sets.size(); i++)
	{
		for (size_t j = i; j < sets.size(); j++)
		{
			if (i != j)
			{
				if (nbr[i].a != nbr[j].a && nbr[i].b == nbr[j].b && nbr[i].c == nbr[j].c)
				{
					if (nbr[i].b == true)
					{
						glued += "b*";
					}
					else
					{
						glued += "!b*";
					}

					if (nbr[i].c == true)
					{
						glued += "c+";
					}
					else
					{
						glued += "!c+";
					}
				}

				if (nbr[i].a == nbr[j].a && nbr[i].b != nbr[j].b && nbr[i].c == nbr[j].c)
				{
					if (nbr[i].a == true)
					{
						glued += "a*";
					}
					else
					{
						glued += "!a*";
					}

					if (nbr[i].c == true)
					{
						glued += "c+";
					}
					else
					{
						glued += "!c+";
					}
				}

				if (nbr[i].a == nbr[j].a && nbr[i].b == nbr[j].b && nbr[i].c != nbr[j].c)
				{
					if (nbr[i].a == true)
					{
						glued += "a*";
					}
					else
					{
						glued += "!a*";
					}

					if (nbr[i].b == true)
					{
						glued += "b+";
					}
					else
					{
						glued += "!b+";
					}
				}
			}
		}
	}

	if (glued.empty())
	{
		glued = sdnf;
	}
	else
	{
		glued.erase(glued.begin() + glued.size() - 1);
	}
	return glued;
}
string dead_end(string in)
{
	vector <string> sets;
	int i = 0;
	int buff = 0;
	struct st
	{
		int a;
		int b;
		int c;
	};

	while (i - 1 != in.length())
	{
		while (in[i] != '+' && i != in.length())
		{
			i++;
		}
		sets.push_back(in.substr(buff, i - buff));
		i++;
		buff = i;
	}

	vector <st> nbr(10);
	for (int i = 0; i < 10; i++)
	{
		nbr[i].a = 10;
		nbr[i].b = 10;
		nbr[i].c = 10;
	}

	for (size_t i = 0; i < sets.size(); i++)
	{
		for (size_t j = 0; j < sets[i].size(); j++)
		{
			if (sets[i][j] == 'a')
			{
				nbr[i].a = 2;
			}
			else if (sets[i][j] == 'b')
			{
				nbr[i].b = 2;
			}
			else if (sets[i][j] == 'c')
			{
				nbr[i].c = 2;
			}
			else if (sets[i][j] == '!')
			{
				j++;
				if (sets[i][j] == 'a')
				{
					nbr[i].a = 1;
				}
				else if (sets[i][j] == 'b')
				{
					nbr[i].b = 1;
				}
				else if (sets[i][j] == 'c')
				{
					nbr[i].c = 1;
				}
			}
		}
	}
	/////////////////////////////////////////////
	int prover;
	vector <int> to_del;
	string kek;

	for (int i = 0; i < 10; i++)
	{
		for (size_t k = 0; k < in.size(); k++)
		{
			kek.push_back(in[k]);
		}
		if (nbr[i].a * nbr[i].b * nbr[i].c != 1000)
		{
			if (nbr[i].a == 2 && nbr[i].b == 2)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'a')
					{
						kek[j] = '1';
					}
					if (kek[j] == 'b')
					{
						kek[j] = '1';
					}
				}
			}

			if (nbr[i].b == 2 && nbr[i].c == 2)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'b')
					{
						kek[j] = '1';
					}
					if (kek[j] == 'c')
					{
						kek[j] = '1';
					}
				}
			}

			if (nbr[i].a == 2 && nbr[i].c == 2)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'a')
					{
						kek[j] = '1';
					}
					if (kek[j] == 'c')
					{
						kek[j] = '1';
					}
				}
			}


			if (nbr[i].a == 1 && nbr[i].b == 2)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'a')
					{
						kek[j] = '0';
					}
					if (kek[j] == 'b')
					{
						kek[j] = '1';
					}
				}
			}

			if (nbr[i].b == 1 && nbr[i].c == 2)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'b')
					{
						kek[j] = '0';
					}
					if (kek[j] == 'c')
					{
						kek[j] = '1';
					}
				}
			}

			if (nbr[i].a == 1 && nbr[i].c == 2)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'a')
					{
						kek[j] = '0';
					}
					if (kek[j] == 'c')
					{
						kek[j] = '1';
					}
				}
			}


			if (nbr[i].a == 2 && nbr[i].b == 1)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'a')
					{
						kek[j] = '1';
					}
					if (kek[j] == 'b')
					{
						kek[j] = '0';
					}
				}
			}

			if (nbr[i].b == 2 && nbr[i].c == 1)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'b')
					{
						kek[j] = '1';
					}
					if (kek[j] == 'c')
					{
						kek[j] = '0';
					}
				}
			}

			if (nbr[i].a == 2 && nbr[i].c == 1)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'a')
					{
						kek[j] = '1';
					}
					if (kek[j] == 'c')
					{
						kek[j] = '0';
					}
				}
			}


			if (nbr[i].a == 1 && nbr[i].b == 1)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'a')
					{
						kek[j] = '0';
					}
					if (kek[j] == 'b')
					{
						kek[j] = '0';
					}
				}
			}

			if (nbr[i].b == 1 && nbr[i].c == 1)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'b')
					{
						kek[j] = '0';
					}
					if (kek[j] == 'c')
					{
						kek[j] = '0';
					}
				}
			}

			if (nbr[i].a == 1 && nbr[i].c == 1)
			{
				for (size_t j = 0; j < kek.size(); j++)
				{
					if (kek[j] == 'a')
					{
						kek[j] = '0';
					}
					if (kek[j] == 'c')
					{
						kek[j] = '0';
					}
				}
			}

			prover = i;
		}

		for (size_t i = 0; i < kek.size(); i++)
		{
			if (kek[i] == '!' && (kek[i + 1] == '1' || kek[i + 1] == '0'))
			{
				kek.erase(i, 1);
			}
			if (kek[i] == '1' || kek[i] == '0' || kek[i] == '+' ||
				kek[i] == '*')
			{
				kek.erase(i, 1);
				i--;
			}
		}

		bool lishniy = false;

		if (kek.size() == 3)
		{
			lishniy = true;
		}

		if (lishniy == true)
		{
			to_del.push_back(prover);
		}
	}

	for (size_t i = 0; i < to_del.size(); i++)
	{
		sets[to_del[i]] = "del";
	}

	string out = "";
	for (size_t i = 0; i < sets.size(); i++)
	{
		if (sets[i] != "del")
		{
			out += sets[i];
			out += "+";
		}
	}
	out.erase(out.begin() + out.size() - 1);

	return out;
}
vector <elem> elements(string in)
{
	vector <elem> out(3);
	out[0] = { 1 , 0, '!' };
	out[1] = { 0 , 0, '+' };
	out[2] = { 0 , 1 , '*' };
	int temp = 0;
	int plus = 0;
	for (size_t i = 0; i < in.size(); i++)
	{
		if (in[i] == '!')
		{
			out[0].count = 3;
		}
		string buff;
		if (in[i] == '+')
		{
			plus++;
			buff = in.substr(temp, i - temp);
			int outs = 0;
			for (size_t j = 0; j < buff.size(); j++)
			{
				if (buff[j] == '*')
				{
					outs++;
				}
			}
			out[2].count++;
			outs++;
			out[2].out = outs;
			temp = i;
		}
	}
	plus++;
	out[1].out = plus++;
	out[1].count = 1;

	return out;
}
vector <bool> to_bin(int num)
{
	vector <bool> res;
	int num_;
	num_ = abs(num);
	
	while (num_)
	{
		res.emplace(res.begin(), num_ % 2);
		num_ /= 2;
	}
	if (num == 0)
	{
		res = { 0, 0, 0, 0 };
	}
	size_t size = res.size();
	for (size_t i = 0; i < 4 - size; i++)
	{
		res.emplace(res.begin(), 0);
	}
	return res;
}
vector <table> to_table(int a)
{
	vector <table> out;
	for (int i = 0; i < 16; i++)
	{
		vector <bool> buf_x = to_bin(i);
		vector <bool> buf_y;
		if (i + a < 10)
		{
			buf_y = to_bin(i + a);
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				buf_y.push_back(0);
			}
		}
		table temp = { buf_x[0], buf_x[1], buf_x[2], buf_x[3],
			buf_y[0], buf_y[1], buf_y[2], buf_y[3] };
		out.push_back(temp);
	}

	return out;
}
string four_glued(string sdnf)
{
	vector <string> sets;
	int i = 0;
	int buff = 0;
	struct st
	{
		bool a;
		bool b;
		bool c;
		bool d;
	};

	while (i - 1 != sdnf.length())
	{
		while (sdnf[i] != '+' && i != sdnf.length())
		{
			i++;
		}
		sets.push_back(sdnf.substr(buff, i - buff));
		i++;
		buff = i;
	}
	vector <st> nbr(16);

	for (size_t i = 0; i < sets.size(); i++)
	{
		for (size_t j = 0; j < sets[i].size(); j++)
		{
			if (sets[i][j] == 'a')
			{
				nbr[i].a = true;
			}
			else if (sets[i][j] == 'b')
			{
				nbr[i].b = true;
			}
			else if (sets[i][j] == 'c')
			{
				nbr[i].c = true;
			}
			else if (sets[i][j] == 'd')
			{
				nbr[i].d = true;
			}
			else if (sets[i][j] == '!')
			{
				j++;
				if (sets[i][j] == 'a')
				{
					nbr[i].a = false;
				}
				else if (sets[i][j] == 'b')
				{
					nbr[i].b = false;
				}
				else if (sets[i][j] == 'c')
				{
					nbr[i].c = false;
				}
				else if (sets[i][j] == 'd')
				{
					nbr[i].d = false;
				}
			}
		}
	}

	string gld = "";
	size_t ex = 0;
	for (size_t k = 0; k < 15; k++)
	{
		if (nbr[k].a != nbr[k + 1].a || nbr[k].b != nbr[k + 1].b ||
			nbr[k].c != nbr[k + 1].c || nbr[k].d != nbr[k + 1].d)
		{
			ex++;
		}
	}

	for (size_t i = 0; i < ex; i++)
	{
		for (size_t j = i; j < ex; j++)
		{
			if (i != j)
			{
				if (nbr[i].a != nbr[j].a && nbr[i].b == nbr[j].b &&
					nbr[i].c == nbr[j].c && nbr[i].d == nbr[j].d)
				{
					if (nbr[i].b == true)
					{
						gld += "b*";
					}
					else
					{
						gld += "!b*";
					}

					if (nbr[i].c == true)
					{
						gld += "c*";
					}
					else
					{
						gld += "!c*";
					}

					if (nbr[i].d == true)
					{
						gld += "d+";
					}
					else
					{
						gld += "!d+";
					}
					break;
				}
				///////////////////////////////
				if (nbr[i].a == nbr[j].a && nbr[i].b != nbr[j].b &&
					nbr[i].c == nbr[j].c && nbr[i].d == nbr[j].d)
				{
					if (nbr[i].a == true)
					{
						gld += "a*";
					}
					else
					{
						gld += "!a*";
					}

					if (nbr[i].c == true)
					{
						gld += "c*";
					}
					else
					{
						gld += "!c*";
					}

					if (nbr[i].d == true)
					{
						gld += "d+";
					}
					else
					{
						gld += "!d+";
					}
					break;
				}
				///////////////////////////////
				if (nbr[i].a == nbr[j].a && nbr[i].b == nbr[j].b &&
					nbr[i].c != nbr[j].c && nbr[i].d == nbr[j].d)
				{
					if (nbr[i].a == true)
					{
						gld += "a*";
					}
					else
					{
						gld += "!a*";
					}

					if (nbr[i].b == true)
					{
						gld += "b*";
					}
					else
					{
						gld += "!b*";
					}

					if (nbr[i].d == true)
					{
						gld += "d+";
					}
					else
					{
						gld += "!d+";
					}
					break;
				}
				///////////////////////////////
				if (nbr[i].a == nbr[j].a && nbr[i].b == nbr[j].b &&
					nbr[i].c == nbr[j].c && nbr[i].d != nbr[j].d)
				{
					if (nbr[i].a == true)
					{
						gld += "a*";
					}
					else
					{
						gld += "!a*";
					}

					if (nbr[i].b == true)
					{
						gld += "b*";
					}
					else
					{
						gld += "!b*";
					}

					if (nbr[i].c == true)
					{
						gld += "c+";
					}
					else
					{
						gld += "!c+";
					}
					break;
				}
			}
		}
	}

	if (gld != "")
	{
		gld.erase(gld.begin() + gld.size() - 1);
	}
	else
	{
		gld = sdnf;
	}
	return gld;
}
void minimized(vector <table> tbl)
{
	string str = "";
	vector <string> out;

	for (size_t i = 0; i < tbl.size(); i++)
	{
		if (tbl[i].y1 == 1)
		{
			if (tbl[i].x1 == 1)
			{
				str += "a*";
			}
			else if (tbl[i].x1 == 0)
			{
				str += "!a*";
			}

			if (tbl[i].x2 == 1)
			{
				str += "b*";
			}
			else if (tbl[i].x2 == 0)
			{
				str += "!b*";
			}

			if (tbl[i].x3 == 1)
			{
				str += "c*";
			}
			else if (tbl[i].x3 == 0)
			{
				str += "!c*";
			}

			if (tbl[i].x4 == 1)
			{
				str += "d";
			}
			else if (tbl[i].x4 == 0)
			{
				str += "!d";
			}
			str += "+";
		}
	}
	str.erase(str.size() - 1);
	out.push_back(str);
	str = "";


	for (size_t i = 0; i < tbl.size(); i++)
	{
		if (tbl[i].y2 == 1)
		{
			if (tbl[i].x1 == 1)
			{
				str += "a*";
			}
			else if (tbl[i].x1 == 0)
			{
				str += "!a*";
			}

			if (tbl[i].x2 == 1)
			{
				str += "b*";
			}
			else if (tbl[i].x2 == 0)
			{
				str += "!b*";
			}

			if (tbl[i].x3 == 1)
			{
				str += "c*";
			}
			else if (tbl[i].x3 == 0)
			{
				str += "!c*";
			}
			if (tbl[i].x4 == 1)
			{
				str += "d";
			}
			else if (tbl[i].x4 == 0)
			{
				str += "!d";
			}
			str += "+";
		}
	}
	str.erase(str.begin() + str.size() - 1);
	out.push_back(str);
	str = "";


	for (size_t i = 0; i < tbl.size(); i++)
	{
		if (tbl[i].y3 == 1)
		{
			if (tbl[i].x1 == 1)
			{
				str += "a*";
			}
			else if (tbl[i].x1 == 0)
			{
				str += "!a*";
			}

			if (tbl[i].x2 == 1)
			{
				str += "b*";
			}
			else if (tbl[i].x2 == 0)
			{
				str += "!b*";
			}

			if (tbl[i].x3 == 1)
			{
				str += "c*";
			}
			else if (tbl[i].x3 == 0)
			{
				str += "!c*";
			}
			if (tbl[i].x4 == 1)
			{
				str += "d";
			}
			else if (tbl[i].x4 == 0)
			{
				str += "!d";
			}
			str += "+";
		}
	}
	str.erase(str.begin() + str.size() - 1);
	out.push_back(str);
	str = "";


	for (size_t i = 0; i < tbl.size(); i++)
	{
		if (tbl[i].y4 == 1)
		{
			if (tbl[i].x1 == 1)
			{
				str += "a*";
			}
			else if (tbl[i].x1 == 0)
			{
				str += "!a*";
			}

			if (tbl[i].x2 == 1)
			{
				str += "b*";
			}
			else if (tbl[i].x2 == 0)
			{
				str += "!b*";
			}

			if (tbl[i].x3 == 1)
			{
				str += "c*";
			}
			else if (tbl[i].x3 == 0)
			{
				str += "!c*";
			}
			if (tbl[i].x4 == 1)
			{
				str += "d";
			}
			else if (tbl[i].x4 == 0)
			{
				str += "!d";
			}
			str += "+";
		}
	}
	str.erase(str.begin() + str.size() - 1);
	out.push_back(str);
	str = "";

	cout << "SDNF y1: " << out[0] << endl;
	cout << "SDNF y2: " << out[1] << endl;
	cout << "SDNF y3: " << out[2] << endl;
	cout << "SDNF y4: " << out[3] << endl;

	for (int i = 0; i < 4; i++)
	{
		str = four_glued(out[i]);
		out[i] = glued(str);
	}

	cout << endl;
	cout << "y1: " << out[0] << endl;
	cout << "y2: " << out[1] << endl;
	cout << "y3: " << out[2] << endl;
	cout << "y4: " << out[3] << endl;
}
