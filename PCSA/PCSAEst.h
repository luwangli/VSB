#ifndef PCSAEST_H
#define PCSAEST_H

#include "../common/param.h"
#include "../bitmap/bitmap.h"

typedef struct{
    int Size;
    int Num;
    BitMap *B[1500];
}PCSAEst;

PCSAEst *newPCSAEst(int m, int size){
    PCSAEst *pcsa = (PCSAEst*)malloc(sizeof(PCSAEst));
    pcsa->Size = size;
    pcsa->Num = m;
 //   cout<<" PCSA num: "<<pcsa->Num <<endl;
  //  pcsa->B = (BitMap*)malloc(sizeof(BitMap) * pcsa->Num);

    for(int i=0;i<pcsa->Num;i++){
        pcsa->B[i] = new BitMap(m);
    }
    return pcsa;
}

void PCSAEstInsert(PCSAEst *p, uint32_t elemID){
    uint32_t bktInd = murmurhash((const char*)&elemID,4,9870) % p->Num;
    uint32_t hashVal = murmurhash((const char*)&elemID,4,2317) ;
    int fstOnePos = NumberOfLeadingZeros(hashVal) + 1;
   // cout<<"bucket: "<<bktInd<<"\t hashVal: "<<fstOnePos<<endl;
  /* if(fstOnePos>(p->Size)){
        fstOnePos = (p->Size)-1;
   }
   if(p->B[bktInd]->get(fstOnePos)){
    cout<<"??"<<endl;
   }*/
    p->B[bktInd]->set(fstOnePos);
//    cout<<"test"<<endl;
}

float PCSAEstGetCar(PCSAEst *p){
    float estimate;
    float sum = 0.0;
    for(int i=0;i<p->Num;i++){

        sum+=p->B[i]->countConsecOne(p->Size);
   //     cout<<i<<"th bitmap, consec: "<<p->B[i]->countConsecOne(p->Size)<<endl;
   //     cout<<"sum : "<<sum<<endl;
    }
    float cor = 0.77351 ;
    float avg = sum / p->Num;
    estimate = std::pow(2,avg) * p->Num / cor;
  //  estimate = (sum/ p->Num) * (1/cor);
    return estimate;
}
#endif
