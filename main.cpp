#include <algorithm>
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include<iostream>
#include <stdexcept>
#include <type_traits>
#include<vector>
#include "Vector.hpp"



int main()
{
    Vector<int> a;
    a.push_back(5);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.insert(a.cbegin()+ 3, 100);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    a.push_back(7);
    
    

    for(auto &i : a) {
        std::cout << i << std::endl;
    } 

    std::vector<int> zzz;
    zzz.insert(zzz.begin(), 100);

    return 0;
}