#pragma warning( push, 0 )
#include <stdint.h>
#include <string>
#include <array>
#include <vector>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#pragma warning( pop )

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#include "include/Info.cpp"
#include "include/DataBaseInterface.cpp"
#include "include/User.cpp"

int main()
{
    srand(time(nullptr));
    ProxyDatabaseWithProtection pdb = ProxyDatabaseWithProtection(new Database());
    Client client(&pdb);
    Manager manager(&pdb);
    Administrator admin(&pdb);
    client.List_Options();
    std::cout << std::endl;
    manager.List_Options();
    std::cout << std::endl;
    admin.List_Options();
    std::cout << std::endl;

    // Mem leak, doesnt care cuz just an example
    User* some_user = new Client(&pdb);
    some_user->List_Options();
    std::cout << std::endl;

    some_user = new Manager(&pdb);
    some_user->List_Options();
    std::cout << std::endl;

    some_user = new Administrator(&pdb);
    some_user->List_Options();
    std::cout << std::endl;

    Info info;
    info = pdb.Get_Some_Info(20);
    std::cout << std::endl;
    info = pdb.Get_Some_Info(20);
    std::cout << std::endl;
    info = pdb.Get_Some_Info(30);
    std::cout << std::endl;
    info = pdb.Get_Some_Info(130);
    std::cout << std::endl;

    InfoFlyweightFactory::Flyweight_Count();
    return 0;
}
