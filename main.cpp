#include<iostream>
#include<loglayer.h>
using namespace std;

int main(){

	FS::Log::Init();
	TB_QT_INFO("Init Logger");
#ifdef FS_FLOAT_AS_DOUBLE
	TB_QT_INFO("Use double");
#else
	TB_QT_INFO("Use float");

#endif 
    //std::cout<<"Hello World"<<std::endl;
    return 0;
}