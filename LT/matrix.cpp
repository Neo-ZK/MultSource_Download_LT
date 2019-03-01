#include "matrix.h"


//generate vector and Matrix
unsigned short int& Vector_g::operator[](int colIndex){
    assert(colIndex < col_);
    return vG_[colIndex];
}

std::shared_ptr<Vector_g>& Matrix_g::operator[](int rowIndex){
    assert(rowIndex < row_);
    return mG_[rowIndex];
}


//content vector and Matrix
int Vector_content::setValue(char* src,int len){
    if(len != col_){
        return -1;
    }else{
        memcpy(&(*vContent_),src,len);
        return 1;
    }
}

unsigned char& Vector_content::operator[](int colIndex){
    return vContent_[colIndex];
}

int Matrix_content::setVectorContent(int rowIndex,char* src,int len){
    if(rowIndex < 0 || rowIndex > row_ || col_ != len){
        return -1;
    }else{
        return mContent_[rowIndex]->setValue(src,len);
    }
}

int Matrix_content::setVectorContent(int rowIndex,std::shared_ptr<Vector_content> v){
    if(rowIndex < 0 || rowIndex > row_ || col_ != v->col_){
        return -1;
    }else{
        mContent_[rowIndex] = v;
        return 1;
    }
}

int Matrix_content::insertVectorToContent(std::shared_ptr<Vector_content> v){
    if(insertIndex_ >= row_){
        row_ = row_*2;
        mContent_.resize(row_);
    }
    mContent_[insertIndex_] = v;
    insertIndex_++;
    return 1;
}

std::shared_ptr<Vector_content>& Matrix_content::operator[](int rowIndex){
    assert(rowIndex < row_);
    return mContent_[rowIndex];
}

void uniXOR(char* dest,char* src1,char* src2,int len){
    for(int i = 0;i < len;i++){
        dest[i] = src1[1]^src2[i];
    }
}


//uniform function
int VectorContentXOR(Vector_content& des,Vector_content& src1,Vector_content& src2){
    if(src1.col_ != src2.col_){
        printf("VectorContentXOR error");
        return -1;
    }
    int col = src1.col_;
    for(int i = 0;i < col;i++){
        des[i] = src1[i] ^ src2[i];
    }
    return 1;
}

