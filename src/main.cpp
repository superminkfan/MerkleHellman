#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include "big_integer.h"

using std::string;

big_integer invert(big_integer a, big_integer m)
{
    if (a < 1 or m < 2)
        return -1;

    big_integer u1 = m;
    big_integer u2 = 0;
    big_integer v1 = a;
    big_integer v2 = 1;

    while (v1 != 0)
    {
        big_integer q = u1 / v1;
        big_integer t1 = u1 - q * v1;
        big_integer t2 = u2 - q * v2;
        u1 = v1;
        u2 = v2;
        v1 = t1;
        v2 = t2;
    }
    return u1 == 1 ? (u2 + m) % m : -1;
}
string readName(string file)
{
    string name;

    std::ifstream in(file);
    if (in.is_open())
    {
        getline(in, name);
    }
    in.close();

    return name;
}
std::string to_binary_string(unsigned int n)
{
    std::string buffer;
    buffer.reserve(std::numeric_limits<unsigned int>::digits);
    do
    {
        buffer += char('0' + n % 2);
        n = n / 2;
    } while (n > 0);
    return std::string(buffer.crbegin(), buffer.crend());
}
int main()
{
    setlocale(LC_ALL, "Russian");

    string name;
    string bin_w;
    name = readName("Name.txt");

    const int N = name.length();
    const int t = to_binary_string(name[0]).length();

    int** M = new int* [N];
    for (int i = 0; i < N; i++)
    {
        M[i] = new int[t];
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < t; j++)
        {

            bin_w = to_binary_string(name[i]);
            M[i][j] = (bin_w[j] - 48);
        }
    }

    big_integer** r = new big_integer * [N];         //ÃÅÍÅÐÀÖÈß ÊËÞ×ÅÉ
    for (int i = 0; i < N; i++)
    {
        r[i] = new big_integer[t];
    }
    big_integer s = 1;
    big_integer sum;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < t; j++)
        {
            s *= 2;
            r[i][j] = s;
            sum += s;
        }
    }

    big_integer k = sum + 1;
    big_integer n = 215;
    big_integer** L = new big_integer * [N];
    for (int i = 0; i < N; i++)
    {
        L[i] = new big_integer[t];
    }
    for (int i = 0; i < N; i++)                       //âû÷èñëèòü âåêòîð L íà îñíîâå ÑÂÏ r
    {
        for (int j = 0; j < t; j++)
        {
            L[i][j] = (r[i][j] * n) % k;

        }
    }

    big_integer** S = new big_integer * [N];         //ØÈÔÐÎÂÀÍÈÅ
    for (int i = 0; i < N; i++)
    {
        S[i] = new big_integer[t];
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < t; j++)
        {
            S[i][j] += M[i][j] * L[i][j];
        }
    }

    big_integer nn = invert(n, k);
    big_integer** P = new big_integer * [N];        //ÄÅØÈÔÐÎÂÀÍÈÅ
    for (int i = 0; i < N; i++)
    {
        P[i] = new big_integer[t];
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < t; j++)
        {
            P[i][j] = (S[i][j] * nn) % k;
        }
    }

    std::cout << "Èñõîäíûé òåêñò: " << "\n" << name << "\n" << std::endl;
    std::cout << "Êëþ÷ (n,k): " << "\n" << n << "\n" << k << "\n" << std::endl;
    std::cout << "Øèôðîâàíèå: " << "\n";

    std::ofstream out, out2, out3;
    out.open("Encoded_Name.txt");
    if (out.is_open())
    {
        for (int i = 0; i < N; i++)            //ØÈÔÐÎÒÅÊÑÒ
        {
            for (int j = 0; j < t; j++)
            {
                std::cout << S[i][j] << "    ";
                out << S[i][j] << "    ";
            }
            std::cout << std::endl;
            out << std::endl;
        }
    }
    out.close();
    out2.open("Decoded_Name.txt");
    if (out2.is_open())
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < t; j++)
            {

                out2 << P[i][j] / r[i][j];
            }
            out2 << " ";
        }
    }
    out2.close();

    string deName;
    int* W = new int[N];

    std::ifstream fin("Decoded_Name.txt");
    if (fin.is_open())
    {
        for (int i = 0; i < N; i++)
        {

            fin >> deName;
            W[i] = std::bitset<32>(deName).to_ulong();
        }
    }
    fin.close();

    char cc;
    std::cout << "\n" << "Ðàñøèôðîâûâàííûé òåêñò: " << "\n";
    out3.open("Decoded_Name.txt");
    if (out3.is_open())
    {
        for (int i = 0; i < N; i++)
        {
            cc = W[i];
            out3 << cc << " ";
            std::cout << cc << " ";
        }
    }
    std::cout << "\n" << std::endl;
    delete[] W;
    for (int i = 0; i < N; i++)
        delete[] M[i];
    for (int i = 0; i < N; i++)
        delete[] r[i];
    for (int i = 0; i < N; i++)
        delete[] L[i];

    system("pause");
    return 0;
}
/*
      for (int i = 0; i < N; i++)
  {
      for (int j = 0; j < t; j++)
      {

          std::cout << M[i][j] << "    ";
      }
      std::cout << std::endl;
  }

  std::cout << std::endl;

  std::cout << std::endl;
  */