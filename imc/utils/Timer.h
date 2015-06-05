/*
 * Timer.h
 *
 *  Created on: Nov 17, 2014
 *      Author: scmimc
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <mpi.h>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>      // std::setw
#include <algorithm>    // std::find

namespace imc {

class Timer {
public:
	Timer();
	Timer(std::string);
	virtual ~Timer();
	void end();
	void setOpps(int nOpps);
	void point(std::string marker);
	void addTo(std::string marker);
        void addOneOffValue(std::string valueName, double value);
	void print(std::string collectionName = "Timer   ");
	static void print(std::vector<imc::Timer> timers, std::string collectionName = "Timer   ");
	static void file(std::vector<imc::Timer> timers, std::string filename, std::string collectionName = "Timer");
	static void firstFile(std::vector<imc::Timer> timers, std::string filename, std::string collectionName = "Timer   ");
private:
	std::vector<std::string> pointNames;
	std::vector<double> pointTimes;
    std::string name;
    double start;
    double last;
    double duration;
    int numOpps;
    static void printInternal(std::vector<imc::Timer> timers, std::ostream stream);
    double get_wall_time();
    double get_cpu_time();



};

} /* namespace imc */
#endif /* TIMER_H_ */
