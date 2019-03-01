#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

struct segment{
    unsigned int header:4;
    unsigned int gLen:4;
    char* gi;
    unsigned int contentLen:4;
    char* content;
};



#endif // SEGMENT_H_INCLUDED
