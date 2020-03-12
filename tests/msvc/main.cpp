/// @file main.cpp
/// 
/// Defines the entry point for the Win32 console application.
///

#include "pch.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
   cout << "Booter Tests (QBS variant)" << endl;

   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}