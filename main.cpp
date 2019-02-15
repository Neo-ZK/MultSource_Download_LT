#include <iostream>
#include "LT/matrix.h"
#include <string.h>

using namespace std;

int main()
{
    std::shared_ptr<Matrix_content> m = std::make_shared<Matrix_content>(2,2);
    std::shared_ptr<Vector_content> v(new Vector_content(2));
    m->content_[1] = v;
    return 0;
}
