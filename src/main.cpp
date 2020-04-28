//
//  main.cpp
//  Module_1
//
//  Created by Danila Kokin on 28.04.2020.
//  Copyright © 2020 Danila Kokin. All rights reserved.
//
#include "Multiplicator.h"

int main()
{
    std::fstream resultFile;
    resultFile.open("/Users/danilakokin/Desktop/result.csv", std::ios::out | std::ios::app);
    resultFile << "length" << ',' << "GradeSchool" << ',' << "Karatsuba" << ',' << "Divivde&Conquer" << '\n';

    size_t MAX_LENGTH = 40000;
    size_t TESTS = 3;

    for (size_t i = 1; i <= MAX_LENGTH;)
    {
        double duration_G = 0;
        double duration_D = 0;
        double duration_K = 0;

        size_t number_len = i;

        for(size_t j = 0; j < TESTS; j++)
        {
            Multiplicator m;
            Number a(m.generate_random(number_len));
            Number b(m.generate_random(number_len));

            std::clock_t start_G = clock();
            m.GradeSchool(a, b);
            std::clock_t time_spent_G = clock() - start_G;
            duration_G += ((double)time_spent_G) / CLOCKS_PER_SEC;

            std::clock_t start_D = clock();
            m.Divide_and_Conquer(a, b);
            std::clock_t time_spent_D = clock() - start_D;
            duration_D += ((double)time_spent_D) / CLOCKS_PER_SEC;

            std::clock_t start_K = clock();
            m.Karatsuba(a, b);
            std::clock_t time_spent_K = clock() - start_K;
            duration_K += ((double)time_spent_K) / CLOCKS_PER_SEC;
        }

        double av_duration_G = duration_G/TESTS;
        double av_duration_D = duration_D/TESTS;
        double av_duration_K = duration_K/TESTS;

        resultFile << number_len << ',' << av_duration_G << ',' << av_duration_K << ',' << av_duration_D << '\n';

        if(i < 10)
        {
            i += 1;
        }
        else if(i >= 10 && i < 100)
        {
            i += 10;
        }
        else if(i >= 100 && i < 1000)
        {
            i += 100;
        }
        else if(i >= 1000 && i < 20000)
        {
            i += 1000;
        }
        else if(i >= 20000 && i < 40000)
        {
            i += 5000;
        }
        else if(i >= 40000)
        {
            i += 10000;
        }
    }
    resultFile.close();

    return 0;
}
