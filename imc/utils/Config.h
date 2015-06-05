#ifndef CONFIG_H_
#define CONFIG_H_

#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>      // std::setw
#include <algorithm>    // std::find

namespace imc {
class Config {
public:
	Config(std::string filename);
	virtual ~Config();
        void printConfig();
        int getOMPNumThreads(){return oMPNumThreads;}
        int getOMPNumColapseLoops(){return oMPNumColapseLoops;}
        int getOMPChunkSize(){return oMPChunkSize;}
        int getParalutionTF(){return paralutionTF;}
        int getParalutionILU_p(){return paralutionILU_p;}
        int getParalutionMaxIter(){return paralutionMaxIter;}
        bool useOMP(){return use_OMP;}
private:
        bool use_OMP;
	int oMPNumThreads;
        int oMPNumColapseLoops;
        int oMPChunkSize;
        bool paralutionTF;
        double paralutionILU_p;
        int paralutionMaxIter;
};

} /* namespace imc */
#endif /* CONFIG_H_ */
