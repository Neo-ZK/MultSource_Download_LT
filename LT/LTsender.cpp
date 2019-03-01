#include "LTsender.h"
//encoder
//const static double delta = 0.05; //decode false propability
//const static double c = 0.05;

LTencoder::LTencoder(unsigned int K):K_(K),robustSolitionDistribution_(K){
    genRobustSolistionDistribution_();
    srand(time(0));
}

LTencoder::~LTencoder(){
        printf("delete LTencoder");
}

void LTencoder::genRobustSolistionDistribution_(){
    robustSolitionDistribution_.resize(K_);
    //ideal solition
    robustSolitionDistribution_[0] = (double)1/K_;
    for(unsigned int i = 1;i < K_;i++){
        robustSolitionDistribution_[i] = (double)1/(i*(i+1));
    }
     //robust solition
    double delta = 0.05; //decode false propability
    double c = 0.05;
    double R = c * log((double)K_/delta) * (double)sqrt((double)K_);

    for(unsigned int i = 0;i < K_;i++){
        double p = R/((i+1)*K_);
        robustSolitionDistribution_[i] = robustSolitionDistribution_[i] + p;
        if(robustSolitionDistribution_[i] < (0.1/K_)){
            robustSolitionDistribution_[i] = 0;
        }
    }
    //normalization
    double sum = 0;
    for(unsigned int i = 0;i < K_;i++){
        sum += robustSolitionDistribution_[i];
    }
    for(unsigned int i = 0;i < K_;i++){
        robustSolitionDistribution_[i] = robustSolitionDistribution_[i]/sum;
    }
}

//wheel gamble to get degree
int LTencoder::getDegree(){
    double v = rand()/(double)(RAND_MAX);
    double sum = 0;
    for(unsigned int i = 0;i < K_;i++){
        sum += robustSolitionDistribution_[i];
        if(sum > v){
            return i+1;
        }
    }
    printf("error in LTencoder::getDegree");
    return -1;
}



//sender
long int LTsender::getFileLength(char* fileName){
    FILE* f = fopen(fileName,"rb");
    if(f == NULL){
        printf("error in LTsender::getFileLength");
        return -1;
    }
    fseek(f,0,SEEK_END);
    long int len = ftell(f);
    fclose(f);
    return len;
}


int LTsender::send(){
    //get file len
    long int fileLen = getFileLength(fileName_);
    if(fileLen < 0){
        printf("error in LTsender::send");
        return -1;
    }

    K_ = ceil((double)fileLen/encPacketLen_);
    mContent_ = std::make_shared<Matrix_content>(K_,encPacketLen_);
    //init encoder
    encoder_ = std::make_shared<LTencoder>(K_);

    //read file into memory,and store in Matrix
    int r = readFileIntoMatrix(fileName_,K_,encPacketLen_);
    if(r < 0){
        printf("error in LTsender::send");
        return -1;
    }

    //send N packets to client
    int d = encoder_->getDegree();
    if(d < 0){
        printf("error in LTsender::send");
        return -1;
    }



    return 1;
}

int LTsender::readFileIntoMatrix(char* fileName,int K,unsigned int encPacketLen){
    FILE* f = fopen(fileName,"rb");
    if(f == NULL){
        printf("error in LTsender::readFileIntoMatrix");
        return -1;
    }
    for(int i = 0;i < K;i++){
        std::shared_ptr<Vector_content> vbuffer(new Vector_content(encPacketLen));
        fread(vbuffer->vContent_,encPacketLen,1,f);
        mContent_->insertVectorToContent(vbuffer);
    }
    fclose(f);
    return 1;
}

int LTsender::genSendSegment(segment& s,int K,int degree){
    //gen N not repeat number
    std::vector<int> from(K);
    for(int i = 0;i < K;i++){
        from[i] = i;
    }
    std::vector<int> indexRandExtract = genNnotRepeatNum(degree,from);
    if(indexRandExtract.empty()){
        printf("genVector_g error");
        return -1;
    }
    Vector_g vg(K);
    Vector_content vc(encPacketLen_);
    for(int i = 0;i < degree;i++){
        vg[indexRandExtract[i]] = 1;
        VectorContentXOR(vc,vc,*((*mContent_)[indexRandExtract[i]]));
    }
    s.header = 1;
    s.gLen = K;
    s.contentLen = encPacketLen_;

    //memcpy()
    return 1;
}

std::vector<int> LTsender::genNnotRepeatNum(int N,std::vector<int> from){
    unsigned int scale = from.size();
    std::vector<int> res;
    if((unsigned int)N > scale){
        printf("genNnotRepeatNum error");
        return res;
    }
    res.resize(N);
    srand(time(0));
    for(int i = 0;i < N;i++){
        int index = rand() % scale;
        res[i] = from[index];
        from.erase(from.begin()+index);
    }
    return res;
}
