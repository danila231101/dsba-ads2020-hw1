//
//  Number.h
//  Module_1
//
//  Created by Danila Kokin on 28.04.2020.
//  Copyright © 2020 Danila Kokin. All rights reserved.
//
#ifndef Number_h
#define Number_h

#include <stdio.h>
#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <fstream>

//Class, where I store extremele large numbrs, separetad by digit and put in a vector.
//I decided to store my numbers in little-endian notation (or siply reversed notation) to perform action in easier way.
class Number
{
private:
    std::vector<int> data;
public:
    //default constuctor
    Number() {}

    //constuctor from vector
    Number(const std::vector<int> &v) : data(v) {}

    //copy constuctor
    Number(const Number &number) : data(number.data)
    {
        data.resize(number.data.size());
        for (size_t i = 0; i < data.size(); i++)
        {
            data[i] = number.data[i];
        }
    }

    //constuctor from size to resize new number
    Number(size_t size)
    {
        if (size > 0)
        {
            data.resize(size);
        }
    }

    //two overloads of [] operator to get elements by index
    int operator [] (size_t i)
    {
        return (i < data.size() ? data[i] : 0);
    }

    const int operator [] (size_t i) const
    {
        return (i < data.size() ? data[i] : 0);
    }

    //constant function to get size of the number
    size_t size() const
    {
        return data.size();
    }

    //constant function to print number
    void print() const
    {
        if (data.empty())
        {
            std::cout << 0 << std::endl;
            return;
        }
        for (ssize_t i = data.size() - 1; i >= 0; i--)
        {
            data.size();
            std::cout << data[i];
        }
        std::cout << std::endl;
    }

    //function, which erases non_valuable zeroes, which can appear in rsult of - or * operation
    void erase_leading_zeros()
    {
        if (data.empty())
        {
            return;
        }
        for (size_t i = data.size(); i > 0; i--)
        {
            if (data.back() != 0)
            {
                return;
            }
            data.pop_back();
        }
    }

    //overload of += operator to use it in all algorithms
    Number& operator += (const Number& number2)
    {
        if (data.size() < number2.data.size())
        {
            data.resize(number2.data.size());
        }
        int add = 0;
        for (size_t i = 0; i < data.size(); i++)
        {
            int first_number_digit = (i < data.size() ? data[i] : 0);
            int second_number_digit = (i < number2.data.size() ? number2.data[i] : 0);

            int current_digit = first_number_digit + second_number_digit + add;

            data[i] = current_digit % 10;
            add = current_digit / 10;
        }
        if (add != 0)
        {
            data.push_back(add);
        }
        return *this;
    }

    //constant overload of + operator
    Number operator + (const Number &number2) const
    {
        Number sum(*this);
        sum += number2;

        return sum;
    }

    //overload of -= operator to use it in Karatsuba algorithm
    Number& operator -= (const Number& number2)
    {
        int substract = 0;
        for(size_t i = 0; i < data.size(); i++)
        {
            int first_number_digit = data[i];
            int second_number_digit = (i < number2.data.size() ? number2.data[i] : 0);

            int current_digit = first_number_digit - second_number_digit + substract;
            if (current_digit < 0)
            {
                data[i] = (current_digit + 10) % 10;
                substract = -1;
            }
            else
            {
                data[i] = current_digit % 10;
                substract = 0;
            }
        }
        this->erase_leading_zeros();
        return *this;
    }

    //overload of << operator.
    //In Karatsuba and Divide&Conquer algorithm I need to multiply number by 10 raised to some power.
    //To make it easier and more understandable, I overloaded << operator (similarly to binary operator <<)
    //It shifts number by inserting zeroes in the beginning of it.
    Number operator << (size_t shift) const
    {
        Number shifted(*this);
        shifted.data.insert(shifted.data.begin(), shift, 0);
        return shifted;
    }

    //overload of <<= operator I did to make shift more efficient
    Number& operator <<= (size_t shift)
    {
        data.insert(data.begin(), shift, 0);
        return *this;
    }

    //overload of * operator works super fast and is used in School algorytm and in base cases of Karatsuba and D&Q
    Number operator * (int digit) const
    {
        Number mult(data.size());
        int add = 0;
        for (size_t i = 0; i < data.size(); i++)
        {
            int curr = data[i] * digit + add;
            mult.data[i] += curr % 10;
            add = curr / 10;
        }
        if (add != 0)
        {
            mult.data.push_back(add);
        }

        mult.erase_leading_zeros();
        return mult;
    }

    //costant split function split number into two halves (used in Karatsuba and D&Q)
    std::pair<Number, Number> split(size_t split_point) const
    {
        split_point = std::min(data.size(), split_point);

        size_t first_len = split_point;
        size_t second_len = data.size() - split_point;
        Number first_half_numb(first_len);
        Number second_half_numb(second_len);

        std::copy(data.begin(), data.begin() + split_point, first_half_numb.data.begin());
        std::copy(data.begin() + split_point, data.end(), second_half_numb.data.begin());

        first_half_numb.erase_leading_zeros();
        return std::make_pair (first_half_numb, second_half_numb);
    }

    //default destuctor
    ~Number() {}
};

#endif /* Number_h */