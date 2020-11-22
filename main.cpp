#include<iostream>
#include<loglayer.h>
using namespace std;

int main(){

	FS::Log::Init();
	TB_QT_INFO("Init Logger");
    //std::cout<<"Hello World"<<std::endl;
    return 0;
}