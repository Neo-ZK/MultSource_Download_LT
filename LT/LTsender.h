#ifndef LT_H_INCLUDED
#define LT_H_INCLUDED

#include <LT/matrix.h>
#include <net/segment.h>
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
    LTsender(char* fileName,unsigned int encPacketLen):encPacketLen_(encPacketLen){
        //process file name string
    };
    LTsender(char* fileName):encPacketLen_(defaltPacketLen){
        fileName_ = fileName;
        //process file name string
    };
    ~LTsender(){};

public:
    int K_; //LT code length
    char* fileName_;
    unsigned int encPacketLen_;//encode packet len,which is equal to Vector_content's col_

private:
    std::shared_ptr<LTencoder> encoder_;
    std::shared_ptr<Matrix_content> mContent_;

public:
    int send();
private:
    long int getFileLength(char* fileName);
    int readFileIntoMatrix(char* fileName,int K,unsigned int encPacketLen);
    std::vector<int> genNnotRepeatNum(int N,std::vector<int> from);
    int genSendSegment(segment& s,int K,int degree);

};



#endif // LT_H_INCLUDED
