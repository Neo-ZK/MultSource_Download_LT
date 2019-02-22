#ifndef LT_H_INCLUDED
#define LT_H_INCLUDED

#include "matrix.h"
#include <vector>
#include <string>
#include <math.h>
#include <time.h>

class LTencoder{
public:
    LTencoder(unsigned int K);
    ~LTencoder();

public:
private:
    unsigned int K_;//LT code length
    std::vector<double> robustSolitionDistribution_;

public:
    int getDegree();
private:
    void genRobustSolistionDistribution_();

};


const static unsigned int defaltPacketLen = 1000;
class LTsender{
public:
    LTsender(char* fileName,unsigned int packetLen):packetLen_(packetLen){
        //process file name string
    };
    LTsender(char* fileName):packetLen_(defaltPacketLen){
        fileName_ = fileName;
        //process file name string
    };
    ~LTsender(){};

public:
    int K_; //LT code length
    char* fileName_;
    unsigned int packetLen_;

private:
    std::shared_ptr<LTencoder> encoder_;
    std::shared_ptr<Matrix_content> mContent_;

public:
    int send();
    void foo();
private:
    long int getFileLength(char* fileName);
    int readFileIntoMatrix(char* fileName,int K,unsigned int packetLen);
};



#endif // LT_H_INCLUDED
