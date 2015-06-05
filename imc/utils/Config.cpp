#include "Config.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace imc {

Config::~Config() {
	// TODO Auto-generated destructor stu
}

Config::Config(std::string fileName){
    using namespace std;
    string line;
    fstream myfile;
    myfile.open (fileName);
    if (myfile.is_open()){
        while ( getline (myfile,line)!=NULL ){
            cout<<"line - ";
            stringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
            cout << tokens[1] << '\n';
            if (tokens[0][0] == '@'){
                if (tokens[0].compare("@OMP_NUM_THREADS") == 0){
	            cout <<"Config::Config - threads = "<<stoi(tokens[1])<<'\n';
                    oMPNumThreads = stoi(tokens[1]);
                }else if (tokens[0].compare("@OMP_NUM_COLAPSE_LOOPS") == 0){
                    cout <<"Config::Config - ColapseLoops = "<<stoi(tokens[1])<<'\n';
                    oMPNumColapseLoops = stoi(tokens[1]);
                }else if (tokens[0].compare("@OMP_CHUNK_SIZE") == 0){
                    cout <<"Config::Config - ChunkSize = "<<stoi(tokens[1])<<'\n';
                    oMPChunkSize = stoi(tokens[1]);
                }else if (tokens[0].compare("@PARALUTION_ILU_P") == 0){
                    cout <<"Config::Config - paralutionILU_p ="<< stoi(tokens[1]);
                    paralutionILU_p = stoi(tokens[1]);
                }else if (tokens[0].compare("@PARALUTION_MAX_ITER") == 0){
                    cout <<"Config::Config - paralutionMaxIter ="<< stoi(tokens[1]);
                    paralutionMaxIter = stoi(tokens[1]);
                }else if (tokens[0].compare("@USE_OMP") == 0){
                    if (tokens[1].compare("TRUE") == 0){
                       cout <<"Config::Config - use openMP = true -- "<<tokens[1]<<'\n';
                       use_OMP = 1;
                    }else{
                       cout <<"Config::Config - use openMP = false -- "<<tokens[1]<<'\n';
                       use_OMP = 0;
                    }
                }else if (tokens[0].compare("@PARALUTION_TF") == 0){
                    if (tokens[1].compare("TRUE") == 0){
                       cout <<"Config::Config - Paralution = true -- "<<tokens[1]<<'\n';
                       paralutionTF = 1;
                    }else{
                       cout <<"Config::Config - Paralution = false -- "<<tokens[1]<<'\n';
                       paralutionTF = 0;
                    }
                }else{
                    cout <<tokens[1]<<"bad line"<<'\n';
                }
            } 
        }
        myfile.close();
    }

    else cout << "Unable to open file"; 
    return;

    //oMPNumThreads = 0;
    
}

//Config::Config(std::string fileName){}

void Config::printConfig(){
    std::cout << "Config::printConfig - oMPNumThreads      = " << oMPNumThreads << "\n";
    std::cout << "Config::printConfig - oMPNumColapseLoops = " << oMPNumColapseLoops << "\n";
    std::cout << "Config::printConfig - oMPChunkSize       = " << oMPChunkSize << "\n";
    std::cout << "Config::printConfig - paralutionTF       = " << paralutionTF << "\n";
    std::cout << "Config::printConfig - paralutionILU_p    = " << paralutionILU_p << "\n";
    std::cout << "Config::printConfig - paralutionMaxIter    = " << paralutionMaxIter << "\n";
}

} //namespace imc

/*int main (int argc, char* argv[]){
    imc::Config config("config.txt");
    config.printConfig();    
}*/

