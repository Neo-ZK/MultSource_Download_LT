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
        return 0;
    }else{
        memcpy(&(*vContent_),src,len);
        return 1;
    }
}

int Matrix_content::setVectorContent(int rowIndex,char* src,int len){
    if(rowIndex < 0 || rowIndex > row_ || col_ != len){
        return 0;
    }else{
        return mContent_[rowIndex]->setValue(src,len);
    }
}

int Matrix_content::setVectorContent(int rowIndex,std::shared_ptr<Vector_content> v){
    if(rowIndex < 0 || rowIndex > row_ || col_ != v->col_){
        return 0;
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
