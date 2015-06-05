/*
 * Timer.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: scmimc
 */

#include "Timer.h"

namespace imc {


//  Windows
#ifdef _WIN32
#include <Windows.h>
double Timer::get_wall_time(){
    LARGE_INTEGER time,freq;
    if (!QueryPerformanceFrequency(&freq)){
        //  Handle error
        return 0;
    }
    if (!QueryPerformanceCounter(&time)){
        //  Handle error
        return 0;
    }
    return (double)time.QuadPart / freq.QuadPart;
}
double Timer::get_cpu_time(){
    FILETIME a,b,c,d;
    if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0){
        //  Returns total user time.
        //  Can be tweaked to include kernel times as well.
        return
            (double)(d.dwLowDateTime |
            ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    }else{
        //  Handle error
        return 0;
    }
}

//  Posix/Linux
#else
#include <sys/time.h>
double Timer::get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
double Timer::get_cpu_time(){
    return (double)clock() / CLOCKS_PER_SEC;
}
#endif

Timer::Timer() {
	this->name = "tmpName";
	start = get_wall_time();;
	duration = 0;
}
Timer::Timer(std::string aName) {
	// TODO Auto-generated constructor stub
	this->name = aName;
	start = get_wall_time();;
	last = start;
	duration = 0;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::end(){
	auto tmp = get_wall_time();;
	duration = (tmp - start);
	last = tmp;
}


void Timer::point(std::string marker){
	this->pointNames.push_back(marker);
	auto tmp = get_wall_time();
	this->pointTimes.push_back(tmp - last );
	last = tmp;
}

void Timer::addTo(std::string marker){
	auto it = std::find(this->pointNames.begin(), this->pointNames.end(), marker);
	if (it == this->pointNames.end()){
	  point(marker);
	} else{
	  auto index = std::distance(this->pointNames.begin(), it);
	  auto tmp = get_wall_time();
	  this->pointTimes.at(index) = this->pointTimes.at(index)+(tmp - last );
	  last = tmp;
	}
}


void Timer::addOneOffValue(std::string valueName, double value){
        this->pointNames.push_back(valueName);
        this->pointTimes.push_back(value);
}

void Timer::print(std::string collectionName /*= "Timer   "*/){
	std::cout << std::setw(10);
	std::cout<<std::setw(10)<<collectionName <<std::setw(10)<<this->name<<std::endl;
	for (int i=0;i<this->pointNames.size();i++){
		std::cout <<std::setw(10)<<this->pointNames.at(i)<<",";
		std::cout <<std::setw(10)<<this->pointTimes.at(i) <<std::endl;// / (double) CLOCKS_PER_SEC<<std::endl;
	}
	std::cout <<std::setw(10)<<"total (s) "<<std::setw(10)<<this->duration<<std::endl; // / (double) CLOCKS_PER_SEC<<std::endl;
}

void Timer::print(std::vector<imc::Timer> timers, std::string collectionName /*= "Timer   "*/){
	std::cout << std::setw(10)<<collectionName <<",";
	for (int j=0;j<timers.size();j++)
		std::cout  <<std::setw(10)<<timers.at(j).name<<",";
	std::cout <<std::endl;
	for (int i=0;i<timers.at(0).pointNames.size();i++){
		std::cout  <<std::setw(10)<<timers.at(0).pointNames.at(i)<<",";
		for (int j=0;j<timers.size();j++){
			std::cout  <<std::setw(10)<<timers.at(j).pointTimes.at(i)<<",";// / (double) CLOCKS_PER_SEC;
		}
		std::cout  <<std::endl;
	}
	std::cout  <<std::setw(10)<<"total (s) ";
	for (int j=0;j<timers.size();j++)
		std::cout <<std::setw(10)<<timers.at(j).duration; // / (double) CLOCKS_PER_SEC;
	std::cout  <<std::endl;
}

void Timer::firstFile(std::vector<imc::Timer> timers, std::string filename, std::string collectionName /*= "Timer   "*/){
	std::ofstream stream;
	stream.open ("filename");
	stream << std::setw(10)<< collectionName <<",";
	for (int j=0;j<timers.size();j++)
		stream <<std::setw(10)<<timers.at(j).name<<",";
	stream<<std::endl;
	for (int i=0;i<timers.at(0).pointNames.size();i++){
		stream <<std::setw(10)<<timers.at(0).pointNames.at(i)<<",";
		for (int j=0;j<timers.size();j++){
			stream <<std::setw(10)<<timers.at(j).pointTimes.at(i)<<","; //  / (double) CLOCKS_PER_SEC;
		}
		stream <<std::endl;
	}
	stream <<std::setw(10)<<"total (s) ";
	for (int j=0;j<timers.size();j++)
		stream <<std::setw(10)<<timers.at(j).duration<<","; // / (double) CLOCKS_PER_SEC;
	stream <<std::endl;
	stream.close();
}

void Timer::setOpps(int nOpps){
	this->numOpps = nOpps;
}

void Timer::file(std::vector<imc::Timer> timers, std::string filename, std::string collectionName /*= "Timer   "*/){
	std::ofstream stream;
	stream.open (filename,  std::fstream::app);
	stream << std::setw(10)<< collectionName<<",";
	for (int j=0;j<timers.size();j++)
		stream <<std::setw(10)<<timers.at(j).name<<",";
	stream<<std::endl;
	for (int i=0;i<timers.at(0).pointNames.size();i++){
		stream <<std::setw(9)<<timers.at(0).pointNames.at(i)<<",";
		for (int j=0;j<timers.size();j++){
			stream <<std::setw(10)<<timers.at(j).pointTimes.at(i)<<","; //  / (double) CLOCKS_PER_SEC<<",";
		}
		stream <<std::endl;
	}
	stream <<std::setw(9)<<"total (s) ,";
	for (int j=0;j<timers.size();j++)
		stream <<std::setw(10)<<timers.at(j).duration<<","; //  / (double) CLOCKS_PER_SEC;
	stream <<std::endl;
	stream.close();
}



} /* namespace imc */













































