#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include<stdio.h>
#include<memory>
#include<vector>
#include<string.h>


class Vector_content{

public:
    Vector_content(int col):col_(col),content_(new unsigned char[col]){printf("create Vector,\n");};
    ~Vector_content(){printf("delete Vector,\n");};
    int col_;
    std::shared_ptr<unsigned char> content_;
    int setValue(char* src,int len);

};

class Matrix_content{

public:
    Matrix_content(int row,int col):row_(row),col_(col),content_(row){
        printf("create Matrix,\n");
        for(int i = 0;i < row;i++){
            content_[i] = std::make_shared<Vector_content>(col);
        }
    };
    ~Matrix_content(){
        printf("delete Matrix");
        content_.erase(content_.begin(),content_.end());
    };
    int row_;
    int col_;
    std::vector<std::shared_ptr<Vector_content>> content_;

public:
    int setVectorContent(int row_index,char* src,int len);
};

#endif // MATRIX_H_INCLUDED
