#include <iostream>
#include <LT/matrix.h>
#include <string.h>

using namespace std;

int main()
{

    std::shared_ptr<Matrix_g> mg = std::make_shared<Matrix_g>(2,2);
    std::shared_ptr<Vector_g> vg(new Vector_g(2));

    printf("%d%d",(*vg)[0],(*vg)[1]);
    (*vg)[0] = 1;
    (*vg)[1] = 2;

    (*mg)[0] = vg;
    printf("%d%d \n",(*((*mg)[0]))[0],(*((*mg)[0]))[1]);


    std::shared_ptr<Matrix_content> mc = std::make_shared<Matrix_content>(2,2);
    std::shared_ptr<Vector_content> vc(new Vector_content(2));
    char* a = new char[2];
    a[0] = 'a';
    a[1] = 'b';
    int c = vc->setValue(a,2);
    (*mc)[0] = vc;
    printf("%c%c \n",((*mc)[0])->vContent_[0],((*mc)[0])->vContent_[1]);
    mc->insertVectorToContent(vc);
    mc->setVectorContent(1,a,2);

    delete[] a;
    //m->content_[1] = v;

    return 0;
}
