//
//  Multiplicator.h
//  Module_1
//
//  Created by Danila Kokin on 28.04.2020.
//  Copyright © 2020 Danila Kokin. All rights reserved.
//

#ifndef Multiplicator_h
#define Multiplicator_h

#include "Number.h"

class Multiplicator
{
public:
    //generate_random function generates random number of K-length
    Number generate_random(size_t k)
    {
        std::vector<int> v;
        srand(static_cast<unsigned int>(clock()));

        v.push_back(1 + rand() % 9);
        for (size_t i = 0; i < k - 1; i++)
        {
            v.push_back(rand() % 10);
        }
        std::reverse(v.begin(), v.end());

        return Number(v);
    }

    Number GradeSchool (Number first, Number second)
    {
        Number result_of_mult(first.size() + second.size());
        for (size_t i = 0; i < first.size(); i++)
        {
            Number tempory_prod (second * first[i]);
            tempory_prod <<= i;
            result_of_mult += tempory_prod;
        }
        return result_of_mult;
    }

    //D&Q algorythm splits numbers into two halves and make operations among them.
    Number Divide_and_Conquer (const Number& first, const Number& second)
    {
        //As D&Q works by recursion, it needs a base case which is 1 digit number;
        size_t max_len = std::max(first.size(), second.size());
        if (max_len <= 1)
        {
            return first * second[0];
        }
        size_t shift = max_len/2;

        //To show how it works, take numbers:
        //X = AB
        //Y = CD
        //X*Y = (AC * 10^((max length/2)*2) + (AD + BC) * 10^(max length/2) + BD

        std::pair<Number, Number> first_numb = first.split(max_len/2);
        std::pair<Number, Number> second_numb = second.split(max_len/2);

        //here I store halves as references to make it more eficient
        Number &A = first_numb.second;
        Number &B = first_numb.first;
        Number &C = second_numb.second;
        Number &D = second_numb.first;

        Number AC = Divide_and_Conquer(A, C);
        Number AD = Divide_and_Conquer(A, D);
        Number BC = Divide_and_Conquer(B, C);
        Number BD = Divide_and_Conquer(B, D);


        Number result(first.size() + second.size());
        result = (AC << (shift * 2)) + ((AD + BC) << shift) + BD;
        return result;
    }

    //Karatsuba algorythm works almost the same but with little impovement.
    Number Karatsuba (const Number& first, const Number& second)
    {
        //As Karatsuba works by recursion, it needs a base case which is 1 digit number;
        size_t max_len = std::max(first.size(), second.size());
        if (max_len <= 1)
        {
            return first * second[0];
        }
        size_t shift = max_len/2;

        //To show how it works, take numbers:
        //X = AB
        //Y = CD
        //X*Y = (AC * 10^((max length/2)*2) + (AD + BC) * 10^(max length/2) + BD
        //Lets rewrite AD + BC = (A + B)(C + D) - AC - BD.
        //it uses already computed values which makes algorythm faster

        std::pair<Number, Number> first_numb = first.split(max_len/2);
        std::pair<Number, Number> second_numb = second.split(max_len/2);

        //also i use references
        Number &A = first_numb.second;
        Number &B = first_numb.first;
        Number &C = second_numb.second;
        Number &D = second_numb.first;

        Number AC = Karatsuba(A, C);
        Number BD = Karatsuba(B, D);

        Number add_BA = B + A;
        Number add_CD = D + C;

        //I use unary operations to make it faster
        Number middle_step = Karatsuba(add_BA,add_CD);
        middle_step -= AC;
        middle_step -= BD;

        AC <<= shift * 2;
        middle_step <<= shift;

        Number result = AC;
        result += middle_step;
        result += BD;

        return result;
    }
};

#endif /* Multiplicator_h */
