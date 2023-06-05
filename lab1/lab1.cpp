#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

const int BIT16 = 16;
const int BIT_MANTISS = 23;
const int BIT_EXPONENTA = 9;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int* bin_sum(int* A1, int* A2, int Size_Array1, int Size_Array2)
{
    int i, iter1, iter2, sum_Iter, remainder;
    int* Result_array;
    int Max_Size = max(Size_Array1, Size_Array2);
    Result_array = new int[Max_Size];
    for (i = 0; i < Max_Size; i++) Result_array[i] = 0;
    remainder = 0;
    iter1 = Size_Array1 - 1;
    iter2 = Size_Array2 - 1;

    for (i = Max_Size - 1; i >= 0; i--)
    {
        sum_Iter = 0;
        if (iter1 >= 0) sum_Iter += A1[iter1];
        if (iter2 >= 0) sum_Iter += A2[iter2];
        sum_Iter += remainder;
        Result_array[i] = sum_Iter % 2;
        remainder = sum_Iter / 2;
        iter1--;
        iter2--;
    }
    return Result_array;
}

void float_sum(int* Sum_exponent, int* MantissX, int* MantissX2, int BIT_MANTISS)
{
    int i, iter1, iter2, sum_iter, remainder;
    int* Result_array;
    Result_array = new int[BIT_MANTISS];
    for (i = 0; i < BIT_MANTISS; i++) Result_array[i] = 0;
    remainder = 0;
    iter1 = BIT_MANTISS - 1;
    iter2 = BIT_MANTISS - 1;

    for (i = BIT_MANTISS - 1; i >= 0; i--)
    {
        sum_iter = 0;
        if (iter1 >= 0) sum_iter += MantissX[iter1];
        if (iter2 >= 0) sum_iter += MantissX2[iter2];
        sum_iter += remainder;
        Result_array[i] = sum_iter % 2;
        remainder = sum_iter / 2;
        iter1--;
        iter2--;
    }
    bool save = false;
    if (remainder == 1) {
        save = true;
    }
    if ((Result_array[0] == 1 && Result_array[1] == 0) || (Result_array[0] == 0 && Result_array[1] == 1) || (save)) {
        int* arr_for_sum_overflow = new int[BIT_EXPONENTA];
        for (int i = 0; i < BIT_EXPONENTA - 1; i++) {
            arr_for_sum_overflow[i] = 0;
        }arr_for_sum_overflow[BIT_EXPONENTA - 1] = 1;
        Sum_exponent = bin_sum(Sum_exponent, arr_for_sum_overflow, BIT_EXPONENTA, BIT_EXPONENTA);
    }
    for (i = 0; i < BIT_EXPONENTA; i++) {
        cout << Sum_exponent[i];
    }
    cout << ',';
    for (i = 0; i < BIT_MANTISS; i++) {
        cout << Result_array[i];
    } cout << endl;
}

int* pryam_bin(int x, int BIT16) {
    int* Result_Array = new int[BIT16];
    if (x < 0) {
        Result_Array[0] = 1;
    }
    else Result_Array[0] = 0;
    x = fabs(x);
    for (int i = BIT16 - 1; i > 0; i--) {
        Result_Array[i] = x % 2;
        x = x / 2;
    }
    return Result_Array;
}

vector<int> direct_code_division(int number, int size)
{
    vector<int> nums;
    int buf = 0;
    int num = abs(number);
    while (num) {
        buf = num % 2;
        nums.push_back(buf);
        num /= 2;
    }
    int length = nums.size();
    for (int i = 0; i < size - length; i++)
        nums.push_back(0);
    reverse(nums.begin(), nums.end());
    if (number < 0)
        nums[0] = 1;
    return nums;
}

int int_code_division(vector<int> nums)
{
    int number = 0;
    reverse(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size() - 1; i++)
        if (nums[i] == 1)
            number += pow(2, i);
    if (nums[nums.size() - 1] == 1)
        return -number;
    else
        return number;
}

void print_bin(vector<int>& nums)
{
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i];
    cout << "\n";
}

int* obr_bin(int* array, int x, int n) {
    if (x < 0) {
        for (int i = 1; i < n; i++) {
            if (array[i] == 0) {
                array[i] = 1;
            }
            else array[i] = 0;
        }
        return array;
    }
    else return array;
}

int* dop_bin(int* pryam_bin_array, int x, int n) {
    int* Result_Array = new int(BIT16);
    int* reversed_number = new int[n];
    if (x < 0) {
        Result_Array = obr_bin(pryam_bin_array, x, n);
        for (int i = 0; i < n - 1; i++) {
            reversed_number[i] = 0;
        }reversed_number[n - 1] = 1;
    }
    else return Result_Array;
    Result_Array = bin_sum(Result_Array, reversed_number, n, n);
    return Result_Array;
}

int* bin_raznost(int* A1, int* A2, int n1, int n2, int x1, int x2) {
    int* Result_Array = new int(BIT16);
    Result_Array = bin_sum(A1, A2, BIT16, BIT16);
    if (Result_Array[0] == 1) {
        Result_Array = dop_bin(Result_Array, -1, BIT16);
    }
    return Result_Array;
}

vector<int> reverse_code_division(vector<int>& nums)
{
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] == 1)
            nums[i] = 0;
        else
            nums[i] = 1;
    }
    return nums;
}

vector<int> to_reverse_code_division(vector<int>& nums)
{
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] == 1)
            nums[i] = 0;
        else
            nums[i] = 1;
    }
    return nums;
}

vector<int> additional_to_direct_division(vector<int>& nums)
{
    for (size_t i = nums.size() - 1; i > 0; i--) {
        if (nums[i] == 1 and (nums[i - 1] == 1 or nums[i - 1] == 0)) {
            nums[i] = 0;
            break;
        }
        if (nums[i] == 0)
            nums[i] = 1;
        else
            nums[i] = 0;
    }
    return reverse_code_division(nums);
}

vector<int> direct_to_additional_division(vector<int>& nums)
{
    nums = to_reverse_code_division(nums);
    if (nums[nums.size() - 1] == 0) {
        nums[nums.size() - 1] = 1;
        return nums;
    }
    for (int i = nums.size() - 1; i > 0; i--) {
        if (nums[i - 1] == 0) {
            nums[i] = 0;
            nums[i - 1] = 1;
            break;
        }
        else
            nums[i] = 0;
    }
    return nums;
}

vector<int> bin_sum_division(vector<int> nums1, vector<int> nums2)
{
    std::vector<int> nums;
    bool flag = false;
    for (size_t i = nums1.size(); i > 0; i--) {
        if (flag and ((nums1[i - 1] == 0 and nums2[i - 1] == 1) or (nums1[i - 1] == 1 and nums2[i - 1] == 0))) {
            nums.push_back(0);
            flag = true;
        }
        else if (!flag and ((nums1[i - 1] == 0 and nums2[i - 1] == 1) or (nums1[i - 1] == 1 and nums2[i - 1] == 0))) {
            nums.push_back(1);
            flag = false;
        }
        else if (nums1[i - 1] == 0 and nums2[i - 1] == 0 and !flag) {
            nums.push_back(0);
            flag = false;
        }
        else if (nums1[i - 1] == 0 and nums2[i - 1] == 0 and flag) {
            nums.push_back(1);
            flag = false;
        }
        else if (nums1[i - 1] == 1 and nums2[i - 1] == 1 and !flag) {
            nums.push_back(0);
            flag = true;
        }
        else if (nums1[i - 1] == 1 and nums2[i - 1] == 1 and flag) {
            nums.push_back(1);
            flag = true;
        }
    }
    std::reverse(nums.begin(), nums.end());
    if (nums[0] == 1)
        additional_to_direct_division(nums);
    return nums;
}

vector<int> bi_sum(vector<int> ArrayX1, vector<int> ArrayX2)
{
    if (ArrayX1[0] == 1 and ArrayX2[0] == 1) {
        ArrayX1 = direct_to_additional_division(ArrayX1);
        ArrayX2 = direct_to_additional_division(ArrayX2);
    }
    else if (ArrayX2[0] == 1)
        ArrayX2 = direct_to_additional_division(ArrayX2);
    else if (ArrayX1[0] == 1)
        ArrayX1 = direct_to_additional_division(ArrayX1);
    return bin_sum_division(ArrayX1, ArrayX2);
}

int* bin_proizvedenie(int* ArrayX1, int* ArrayX2, int n1, int n2) {
    int* Result_Array1 = new int[BIT16];
    for (int i = 0; i < BIT16; i++) Result_Array1[i] = 0;
    int* Result_Array2 = new int[BIT16];
    for (int i = 0; i < BIT16; i++) Result_Array2[i] = 0;
    int i = BIT16 - 1;
    int j = BIT16 - 1;
    int bias = BIT16 - 1;
    n1 = max(n1, n2);
    while (j >= i - n1) {
        int exp = bias;
        while (i >= BIT16 - n1) {
            Result_Array1[bias] = ArrayX2[j] * ArrayX1[i];
            i--;
            bias--;
        }
        bias = exp - 1;
        exp--;
        Result_Array2 = bin_sum(Result_Array1, Result_Array2, BIT16, BIT16);
        i = 15;
        for (int i = 0; i < BIT16; i++) Result_Array1[i] = 0;
        j--;
    }
    for (int i = 0; i < BIT16; i++) cout << Result_Array2[i];
    cout << endl;

    delete[]Result_Array1;
    return Result_Array2;
}

vector<int> bin_division(vector<int> Array_x1, vector<int> Array_x2)
{
    vector<int> division_result(BIT16, 0), array_1(BIT16, 0), nums_of_null(BIT16, 0);
    bool is_negative = false;
    division_result[BIT16 - 1] = 1;
    division_result[0] = 1;
    if (Array_x1[0] == 1 && Array_x2[0] == 1)
        Array_x1[0] = 0;
    else if (Array_x1[0] == 1) {
        is_negative == true;
        Array_x1[0] = 0;
    }
    else if (Array_x2[0] == 1) is_negative = true;
    array_1[BIT16 - 1] = 1;
    Array_x2[0] = 1;
    while (Array_x1[0] != 1 || Array_x1 == nums_of_null) {
        Array_x1 = bi_sum(Array_x1, Array_x2);
        division_result = bi_sum(division_result, array_1);
    }
    if (is_negative) division_result[0] = 1;
    return division_result;
}

int* bin_dvoich(int* Result_Array, double x, double y) {
    double int_part_of_number = 0;
    double fraction_part_of_number;
    for (int i = 0; i < BIT_EXPONENTA + 1; i++) {
        int_part_of_number = y * 2;
        y = modf(int_part_of_number, &fraction_part_of_number);
        Result_Array[i] = fraction_part_of_number;
        fraction_part_of_number = 0;
    }
    return Result_Array;
}

int main(int argc, char* argv[])
{
    int x1, x2;
    cout << "Input X1: " << endl;
    cin >> x1;
    cout << "Input X2: " << endl;
    cin >> x2;
    cout << "X1 = " << x1 << endl;
    cout << "X2 = " << x2 << endl;
    std::vector<int> Array_x1;
    std::vector<int> Array_x2;
    std::vector<int> division_result;
    int* Array1 = new int[BIT16];
    int* Array2 = new int[BIT16];
    for (int i = 0; i < BIT16; i++) {
        Array1[i] = 0;
        Array2[i] = 0;
    }
    int i;
    int* Result_array;
    Array1 = pryam_bin(x1, BIT16);
    Array2 = pryam_bin(x2, BIT16);
    cout << "pryam kod A1: " << endl;
    for (i = 0; i < BIT16; i++) cout << Array1[i];
    cout << endl;
    cout << "pryam kod A2: " << endl;
    for (i = 0; i < BIT16; i++) cout << Array2[i];
    cout << endl;
    int t = max(BIT16, BIT16);
    if (x1 < 0) {
        Array1 = dop_bin(Array1, x1, BIT16);
        cout << "dop kod A1: " << endl;
        for (i = 0; i < 16; i++) cout << Array1[i];
        cout << endl;
    }
    if (x2 < 0) {
        Array2 = dop_bin(Array2, x2, BIT16);
        cout << "dop kod A2: " << endl;
        for (i = 0; i < BIT16; i++) cout << Array2[i];
        cout << endl;
    }
    int l = 0;
    while (1) {
        cout << "0 - summa, 1 - raznost, 2 - proizvedenie, 3 - delenie, 4 - float_addition , 5 - exit " << endl;
        cin >> l;
        switch (l) {
        case 0:
            Result_array = bin_sum(Array1, Array2, BIT16, BIT16);
            cout << "summa: " << endl;
            for (i = 0; i < t; i++) cout << Result_array[i];
            cout << endl;
            delete[]Result_array;
            break;
        case 1:
            if (x2 > 0) {
                x2 = x2 * -1;
                Array2[0] = 1;
                Array2 = dop_bin(Array2, x2, BIT16);
            }
            Result_array = bin_raznost(Array1, Array2, BIT16, BIT16, x1, x2);
            cout << "raznost: " << endl;
            for (i = 0; i < t; i++) cout << Result_array[i];
            cout << endl;
            delete[]Result_array;
            break;
        case 2:
            Array1 = pryam_bin(fabs(x1), BIT16);
            Array2 = pryam_bin(fabs(x2), BIT16);
            Result_array = bin_proizvedenie(Array1, Array2, BIT16, BIT16);
            cout << endl;
            cout << "proizvedenie: " << endl;
            for (i = 0; i < t; i++) cout << Result_array[i];
            cout << endl;
            delete[]Result_array;
            break;
        case 3:
            for (int i = 0; i < BIT16; i++) {
                Array_x1.push_back(0);
                Array_x2.push_back(0);
            }
            Array_x1 = direct_code_division(x1, BIT16);
            Array_x2 = direct_code_division(x2, BIT16);
            for (int i = 0; i < BIT16; i++) {
                division_result.push_back(0);
            }
            division_result = bin_division(Array_x1, Array_x2);
            cout << "delenie: " << endl;
            std::cout << int_code_division(division_result) << "\n";
            print_bin(division_result);
            break;
        case 4:
            double d1 = 0.5, d2 = 10.625;
            double x, y, x2, y2;
            y = modf(d1, &x);
            y2 = modf(d2, &x2);
            int* MantissX = new int[BIT_MANTISS];
            for (int i = 0; i < BIT_MANTISS; i++) { MantissX[i] = 0; };
            int* MantissX2 = new int[BIT_MANTISS];
            for (int i = 0; i < BIT_MANTISS; i++) { MantissX2[i] = 0; };
            MantissX = bin_dvoich(MantissX, x, y);
            MantissX2 = bin_dvoich(MantissX2, x2, y2);
            int* Array_X = new int[BIT_EXPONENTA];
            int* Array_X2 = new int[BIT_EXPONENTA];
            int* Sum_exponent = new int[BIT_EXPONENTA];
            int* T4 = new int[23];
            Array_X = pryam_bin(x, BIT_EXPONENTA);
            Array_X2 = pryam_bin(x2, BIT_EXPONENTA);
            Sum_exponent = bin_sum(Array_X, Array_X2, BIT_EXPONENTA, BIT_EXPONENTA);
            cout << "x1 + x2 = " << d1 << " + " << d2 << " = " << d1 + d2 << endl;
            float_sum(Sum_exponent, MantissX, MantissX2, BIT_MANTISS);
            break;
        }
    }
    delete[]Array1;
    delete[]Array2;
    system("PAUSE");
    return 0;

}
