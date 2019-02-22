#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include<stdio.h>
#include<memory>
#include<vector>
#include<string.h>
#include<assert.h>
#include <math.h>

//statement of matrix of generate vector
class Vector_g{
public:
    Vector_g(int col):col_(col){
        printf("create Vector_g,\n");
        vG_ = new unsigned short int[col];
    };
    ~Vector_g(){
        printf("delete Vector_g,\n");
        delete [] vG_;
    };

public:
    int col_;
    unsigned short int* vG_;

public:
    unsigned short int& operator[](int colIndex);
};

class Matrix_g{
public:
    Matrix_g(int row,int col):row_(row),col_(col),mG_(row){
        printf("create Matrix_g,\n");
        for(int i = 0;i < row;i++){
            mG_[i] = std::make_shared<Vector_g>(col);
        }
    };
    ~Matrix_g(){
        printf("delete Matrix_g,\n");
        mG_.erase(mG_.begin(),mG_.end());
    };
public:
    int row_;
    int col_;
    std::vector<std::shared_ptr<Vector_g>> mG_;

public:
    std::shared_ptr<Vector_g>& operator[](int rowIndex);

};



//statement of matrix of content
class Vector_content{

public:
    Vector_content(unsigned int col):col_(col){
        printf("create Vector_content,\n");
        vContent_ = new unsigned char[col];
    };
    ~Vector_content(){
        printf("delete Vector_content,\n");
        delete [] vContent_;
    };

public:
    unsigned int col_;
    unsigned char* vContent_;

public:
    int setValue(char* src,int len);

};

class Matrix_content{

public:
    Matrix_content(int row,int col):row_(row),col_(col),insertIndex_(0),mContent_(row){
        printf("create Matrix_content,\n");

        for(int i = 0;i < row;i++){
            mContent_[i] = std::make_shared<Vector_content>(col);
        }
    };
    ~Matrix_content(){
        printf("delete Matrix_content");
        mContent_.erase(mContent_.begin(),mContent_.end());
    };
//variable member
public:
    int row_;
    int col_;
    int insertIndex_;
    std::vector<std::shared_ptr<Vector_content>> mContent_;
//fucntion
public:
    int setVectorContent(int rowIndex,char* src,int len);
    int setVectorContent(int rowIndex,std::shared_ptr<Vector_content> v);
    int insertVectorToContent(std::shared_ptr<Vector_content> v);
    std::shared_ptr<Vector_content>& operator[](int rowIndex);
};



#endif // MATRIX_H_INCLUDED



