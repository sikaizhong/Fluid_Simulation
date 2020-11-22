#include<gtest/gtest.h>
#include<iostream>

using namespace std;

int main(int argc, char**argv){
	::testing::InitGoogleTest(&argc, argv);
	printf("Running main() from gtest_main.cc\n");
	return RUN_ALL_TESTS();
}