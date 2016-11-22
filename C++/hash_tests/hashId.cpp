#include <string>
#include <iostream>
#include <fstream>

#include "hash.cpp"
#include <sys/types.h>
#include <stdio.h>



int 
main(int argc, char* argv[])
{
    std::string  x;
    std::cin >> x;

    uint32_t hash_val = hashlittle(x.c_str(), x.length(), 0);
   
    printf("%u", hash_val) ;
    
}

