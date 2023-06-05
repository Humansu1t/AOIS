#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct float_ {
	vector <bool> mantissa;
	vector <bool> index;
};

vector <bool> to_binary_straight(int);
vector <bool> to_binary_reverse(int);
vector <bool> to_binary_addition(int);
vector <bool> from_addition_to_reverse(vector <bool>);
vector <bool> from_reverse_to_straight(vector <bool>);
vector <bool> from_straight_to_addition(vector <bool>);
vector <bool> addition(vector <bool>, vector <bool>);
vector <bool> multiplication(vector <bool>, vector <bool>);
void division(vector <bool>, vector <bool>);
void float_addition(float_, float_);
void print(vector <bool>);

const vector <bool> zero { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const vector <bool> one { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
const vector <bool> one_addition { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
const int pos_x1 = 13;
const int neg_x1 = -13;
const int pos_x2 = 21;
const int neg_x2 = -21;
const float_ f_pos_x1 = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 } };
const float_ f_neg_x1 = { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 } };
const float_ f_pos_x2 = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 } };
const float_ f_neg_x2 = { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 } };

int main()
{
	vector <bool> temp;

	////////////////ПЕРЕВОД
	cout << "**** +X1 = 17 ****" << endl;
	cout << "Straight code: ";
	temp = to_binary_straight(pos_x1);
	print(temp);
	cout << "Reverse  code: ";
	temp = to_binary_reverse(pos_x1);
	print(temp);
	cout << "Addition code: ";
	temp = to_binary_addition(pos_x1);
	print(temp);
	cout << endl;
	///////////
	cout << "**** -X1 = -17 ****" << endl;
	cout << "Straight code: ";
	temp = to_binary_straight(neg_x1);
	print(temp);
	cout << "Reverse  code: ";
	temp = to_binary_reverse(neg_x1);
	print(temp);
	cout << "Addition code: ";
	temp = to_binary_addition(neg_x1);
	print(temp);
	cout << endl;
	///////////
	cout << "**** +X2 = 9 ****" << endl;
	cout << "Straight code: ";
	temp = to_binary_straight(pos_x2);
	print(temp);
	cout << "Reverse  code: ";
	temp = to_binary_reverse(pos_x2);
	print(temp);
	cout << "Addition code: ";
	temp = to_binary_addition(pos_x2);
	print(temp);
	cout << endl;
	///////////
	cout << "**** -X2 = -9 ****" << endl;
	cout << "Straight code: ";
	temp = to_binary_straight(neg_x2);
	print(temp);
	cout << "Reverse  code: ";
	temp = to_binary_reverse(neg_x2);
	print(temp);
	cout << "Addition code: ";
	temp = to_binary_addition(neg_x2);
	print(temp);
	cout << endl;
	
	////////////////ОПЕРАЦИИ

	cout << "**** X1 + X2 = 26 **** " << endl;
	temp = addition(to_binary_straight(pos_x1), to_binary_straight(pos_x2));
	cout << "Addition code: ";
	print(temp);
	cout << "Reverse  code: ";
	print(temp);
	cout << "Straight code: ";
	print(temp);
	cout << endl;
	/////////////
	cout << "**** -X1 + X2 = 8 **** " << endl;
	temp = addition(to_binary_straight(pos_x2), to_binary_addition(neg_x1));
	cout << "Addition code: ";
	print(temp);
	cout << "Reverse  code: ";
	print(temp);
	cout << "Straight code: ";
	print(temp);
	cout << endl;
	/////////////
	cout << "**** -X1 - X2 = -26**** " << endl;
	cout << "Addition code: ";
	temp = addition(to_binary_addition(neg_x1), to_binary_addition(neg_x2));
	print(temp);
	cout << "Reverse  code: ";
	temp = from_addition_to_reverse(temp);
	print(temp);
	cout << "Straight code: ";
	temp = from_reverse_to_straight(temp);
	print(temp);
	cout << endl;
	/////////////
	cout << "**** X1 - X2 = -8 **** " << endl;
	cout << "Addition code: ";
	temp = addition(to_binary_straight(pos_x1), to_binary_addition(neg_x2));
	print(temp);
	cout << "Reverse  code: ";
	temp = from_addition_to_reverse(temp);
	print(temp);
	cout << "Straight code: ";
	temp = from_reverse_to_straight(temp);
	print(temp);
	cout << endl;
	/////////////
	cout << "**** X1 * X2 = 153 **** " << endl;
	cout << "Straight code: ";
	temp = multiplication(to_binary_straight(pos_x1), to_binary_straight(pos_x2));
	print(temp);
	cout << "Reverse  code: ";
	print(temp);
	cout << "Addition code: ";
	print(temp);
	cout << endl;
	////////////
	cout << "**** -X1 * X2 = -153 **** " << endl;
	cout << "Addition code: ";
	temp = multiplication(to_binary_straight(neg_x1), to_binary_straight(pos_x2));
	print(temp);
	cout << "Reverse  code: ";
	temp = from_addition_to_reverse(temp);
	print(temp);
	cout << "Straight code: ";
	temp = from_reverse_to_straight(temp);
	print(temp);
	cout << endl;
	////////////
	cout << "**** -X1 * -X2 = 153 **** " << endl;
	cout << "Addition code: ";
	temp = multiplication(to_binary_straight(neg_x1), to_binary_straight(neg_x2));
	print(temp);
	cout << "Reverse  code: ";
	print(temp);
	cout << "Straight code: ";
	print(temp);
	cout << endl;
	////////////
	cout << "**** X1 * -X2 = -153 **** " << endl;
	cout << "Addition code: ";
	temp = multiplication(to_binary_straight(pos_x1), to_binary_straight(neg_x2));
	print(temp);
	cout << "Reverse  code: ";
	temp = from_addition_to_reverse(temp);
	print(temp);
	cout << "Straight code: ";
	temp = from_reverse_to_straight(temp);
	print(temp);
	cout << endl;
	////////////
	cout << "**** X1 / X2 =  **** " << endl;
	division(to_binary_straight(pos_x1),to_binary_straight(pos_x2));
	////////////
	cout << "**** -X1 / X2 =  **** " << endl;
	division(to_binary_addition(neg_x1), to_binary_straight(pos_x2));
	////////////
	cout << "**** -X1 / -X2 =  **** " << endl;
	division(to_binary_addition(neg_x1), to_binary_addition(neg_x2));
	////////////
	cout << "**** X1 / -X2 =  **** " << endl;
	division(to_binary_straight(pos_x1), to_binary_addition(neg_x2));
	cout << endl;
	///////////
	cout << "**** X1_float + X2_float =  **** " << endl;
	float_addition(f_pos_x1, f_pos_x2);
	system("pause");
    return 0;
}

vector <bool> to_binary_straight(int num)
{
	vector <bool> res;
	size_t size;
	int num_;
	num_ = abs(num);
	while (num_)
	{
		res.emplace(res.begin(), num_ % 2);
		num_ /= 2;
	}
	size = res.size();
	for (size_t i = 0; i < 16 - size; i++)
	{
		res.emplace(res.begin(), 0);
	}
	if (num < 0)
	{
		res[0] = 1;
	}
	return res;
}
vector <bool> to_binary_reverse(int num)
{
	vector <bool> res = to_binary_straight(num);
	if (num > 0)
	{
		res = to_binary_straight(num);
	}
	else if (num < 0)
	{
		for (size_t i = 0; i < res.size(); i++)
		{
			res[i] = !res[i];
		}
		res[0] = 1;
	}
	return res;
}
vector <bool> to_binary_addition(int num)
{
	vector <bool> res = to_binary_reverse(num);
	if (num > 0)
	{
		res = to_binary_straight(num);
	}
	else if (num < 0)
	{
		res = addition(res, one);
	}
	return res;
}
vector <bool> from_addition_to_reverse(vector <bool> bin)
{
	if (bin[0] == 1)
	{
		bin = addition(bin, one_addition);
		return bin;
	}
	else return bin;
}
vector <bool> from_reverse_to_straight(vector <bool> bin)
{
	if (bin[0] == 1)
	{
		for (int i = 0; i < 16; i++)
		{
			bin[i] = !bin[i];
		}
		bin[0] = 1;
		return bin;
	}
	else return bin;
}
vector <bool> from_straight_to_addition(vector <bool> bin)
{
		for (size_t i = 0; i < bin.size(); i++)
		{
			bin[i] = !bin[i];
		}
		bin[0] = 1;
		bin = addition(bin, one);
		return bin;
}
vector <bool> addition(vector <bool> a, vector <bool> b)
{
	vector <bool> res;
	bool trans = false;
	//for (size_t i = 0; i = a.size() - b.size(); i++)
	//{
	//	b.emplace(b.begin(), 0); //дополняем меньшее число до совпадения кол-ва разрядов
	//}
	for (size_t i = a.size(); i > 0; i--)
	{
			if (a[i-1] == 0 && b[i-1] == 0 && trans == false)
			{
				res.emplace(res.begin(), 0);
				trans = false;
			}
			else if (a[i-1] == 0 && b[i-1] == 0 && trans == true)
			{
				res.emplace(res.begin(), 1);
				trans = false;
			}
			else if (a[i-1] == 1 && b[i-1] == 0 && trans == false)
			{
				res.emplace(res.begin(), 1);
				trans = false;
			}
			else if (a[i-1] == 1 && b[i-1] == 0 && trans == true)
			{
				res.emplace(res.begin(), 0);
				trans = true;
			}
			else if (a[i-1] == 0 && b[i-1] == 1 && trans == false)
			{
				res.emplace(res.begin(), 1);
				trans = false;
			}
			else if (a[i-1] == 0 && b[i-1] == 1 && trans == true)
			{
				res.emplace(res.begin(), 0);
				trans = true;
			}
			else if (a[i-1] == 1 && b[i-1] == 1 && trans == false)
			{
				res.emplace(res.begin(), 0);
				trans = true;
			}
			else if (a[i-1] == 1 && b[i-1] == 1 && trans == true)
			{
				res.emplace(res.begin(), 1);
				trans = true;
			}
	}
	return res;
}
vector <bool> multiplication(vector <bool> a, vector <bool> b)
{
	vector <bool> res = zero;
	bool flag = false;
	if (a[0] == b[0])
	{
		flag = true;
	}
	if (b[0] == 1)
	{
		b[0] = 0;
	}
	if (b[0] == 1)
	{
		b[0] = 0;
	}
	while (b != zero )
	{
		res = addition(a, res);
		b = addition(b, one_addition);
	}
	if (flag == true)
	{
		res[0] = 0;
	}
	else
	{
		res[0] = 1;
	}
	return res;
}
void division(vector <bool> a, vector <bool> b)
{
	vector <bool> res;
	vector <bool> remainder;
	vector <bool> b_plus;
	int off_a = 0;
	int off_b = 0;
	int off = 0;
	bool sign = false;

	if (a[0] == b[0])
	{
		sign = true;
	}

	if (a[0] == 1)
	{
		a = from_reverse_to_straight(from_addition_to_reverse(a));
		a[0] = 0;
	}

	if (b[0] == 1)
	{
		b = from_reverse_to_straight(from_addition_to_reverse(b));
		b[0] = 0;
	}
	b_plus = b;

	do
	{
		off_a++;
	}
	while (a[off_a] != 1);

	do
	{
		off_b++;
	}
	while (b[off_b] != 1);

	off = off_b - off_a;
	for (int i = 0; i < off; i++)
	{
		b.push_back(0);
		b.erase(b.begin());
	}
	b[0] = 1;
	b = from_straight_to_addition(b);
	remainder = addition(a, b);
	if (remainder[0] == 1)
	{
		res.emplace(res.begin(), 0);
	}
	else
	{
		res.emplace(res.begin(), 1);
	}
	
	for (int i = 0; i < off; i++)
	{
		b_plus.push_back(0);
		b_plus.erase(b_plus.begin());
		remainder.push_back(0);
		remainder.erase(remainder.begin());

		if (remainder[0] == 1)
		{
			remainder = addition(remainder, b_plus);
		}
		else
		{
			remainder = addition(remainder, b);
		}
		
		if (remainder[0] == 1)
		{
			res.push_back(0);
		}
		else
		{
			res.push_back(1);
		}
	}

	if (remainder[0] == 1)
	{
		remainder = addition(remainder, b_plus);
	}
	
	for (int i = 0; i < off; i++)
	{
		remainder.erase(remainder.begin() + 15);
		remainder.emplace(remainder.begin(), 0);
	}

	int sz = res.size();
	for (size_t i = 0; i < 16 - sz; i++)
	{
		res.emplace(res.begin(), 0);
	}

	if (!sign)
	{
		cout << "-";
	}
	for (size_t i = 0; i < res.size(); i++)
	{
		cout << res[i];
	}
	cout << ',';
	for (size_t i = 11; i < remainder.size(); i++)
	{
		cout << remainder[i];
	}
	cout << endl;
}
void float_addition(float_ a, float_ b)
{
	float_ res;
	bool sign = true;
	if (a.mantissa[0] != b.mantissa[0])
	{
		sign = false;
	}
	while (a.index != b.index)
	{
		a.index = addition(a.index, one);
		a.mantissa.emplace(a.mantissa.begin(), 0);
		a.mantissa.erase(a.mantissa.begin() + 1);
	}
	res.mantissa = addition(a.mantissa, b.mantissa);
	res.index = a.index;

	if (!sign)
	cout << "0,";
	for (size_t i = 0; i < res.mantissa.size(); i++)
	{
		cout << res.mantissa[i];
	}
	cout << "*2^";
	for (size_t i = 0; i < res.index.size(); i++)
	{
		cout << res.index[i];
	}
	cout << endl;
}
void print(vector <bool> bin)
{
	for (size_t i = 0; i < bin.size(); i++)
	{
		cout << bin[i];
	}
	cout << endl;
}
