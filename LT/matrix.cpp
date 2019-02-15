#include "matrix.h"


int Vector_content::setValue(char* src,int len){
    if(len != col_){
        return 0;
    }else{
        memcpy(&(*content_),src,len);
        return 1;
    }
}

int Matrix_content::setVectorContent(int rowIndex,char* src,int len){
    return content_[rowIndex]->setValue(src,len);
}
