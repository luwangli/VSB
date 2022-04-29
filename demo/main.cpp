#include "../common/param.h"
#include "../common/Read.h"
#include "../bitmap/bitmap.h"
#include "../MRB/mrb.h"
#include "../VSA/vsa2.h"
#include "../HLL/HLLEstBitV.h"
#include "../LL/LLEstBitV.h"
#include "../SRB/srb.h"
#include "../common/param.h"
#include "../hllp_card/hyperloglogplus_counting.h"
using namespace std;

///#define UINT32_MAX (0xFFFFFFFF)

int main(){
    vector<pair<uint32_t, uint32_t>> Stream;
    vector<pair<uint32_t, uint32_t>> Bench;

    int pkt_num;
    int flow_num;
    int vsa_thres = 1428;
    int length = 10000;

    char filename[100] = "../Data/0.txt";
  //  char resname[100] = "../data/dstspread.txt";

  //  char filename[100] = "../data/kaggleData.txt";
//    char resname[100] = "../data/kaggleItemSpread.txt";
 //   cout<<"Input data and vsb_thres, and length: "<<endl;
 //   cin>>filename>>vsa_thres>>length;

    int srb_thres = 833;//the parameter setting con find in our paper
    const int mrb_k = 11;

    pkt_num = Read(filename, Stream, flow_num);
    cout<<endl;
    timespec start_time, end_time;
    double insert_throughput=0, query_throughput=0;
    long long timediff=0;
    int query_num = 1000;
    int est_car;
    ofstream outFile;

    /**********************HLLPLUS***************/
    cout<<"\nHLLPLUSPLUS:"<<endl;
    int hllpt = log(length)/log(2);
    auto hllpp = hllp_cnt_raw_init(NULL, hllpt);
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<pkt_num;i++){
        hllp_cnt_offer(hllpp,&Stream[i].second,sizeof(int64_t));
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    insert_throughput = (double)1000.0*pkt_num / timediff;

    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<query_num;i++){
        est_car = hllp_cnt_card(hllpp);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    query_throughput = (double)1000.0*query_num /timediff;
    cout<<"estimate value: "<< est_car<<"\t error: "<<abs(est_car-flow_num)
        <<"\t insert: "<<insert_throughput
        <<"\t query: "<<query_throughput<<endl;
    outFile.open("result.csv",ios::app);
    outFile<<filename<<","<<length<<",hllpp,"<<abs(est_car-pkt_num)*1.0/pkt_num<<","<<insert_throughput<<","<<query_throughput<<endl;
    outFile.close();

      /************************LL*****************/
    cout<<"\nLL:"<<endl;
    int ll_size = 5;
    auto ll = newLLEst(length,ll_size);
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<pkt_num;i++){
        LLEstInsert(ll,Stream[i].second);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    insert_throughput = (double)1000.0*pkt_num / timediff;

    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<query_num;i++){
        est_car = LLEstGetCar(ll);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    query_throughput = (double)1000.0*query_num /timediff;
    cout<<"estimate value: "<< est_car<<"\t error: "<<abs(est_car-flow_num)
        <<"\t insert: "<<insert_throughput
        <<"\t query: "<<query_throughput<<endl;
    outFile.open("result.csv",ios::app);
    outFile<<filename<<","<<length<<",LL,"<<abs(est_car-pkt_num)*1.0/pkt_num<<","<<insert_throughput<<","<<query_throughput<<endl;
    outFile.close();

    /************************HLL*****************/
    cout<<"\nHLL:"<<endl;
    int hll_size = 5;
    auto hll = newHLLEst(length,hll_size);
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<pkt_num;i++){
        HLLEstInsert(hll,Stream[i].second);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    insert_throughput = (double)1000.0*pkt_num / timediff;


    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<query_num;i++){
        est_car = HLLEstGetCar(hll);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    query_throughput = (double)1000.0*query_num /timediff;
    cout<<"estimate value: "<< est_car<<"\t error: "<<abs(est_car-flow_num)
        <<"\t insert: "<<insert_throughput
        <<"\t query: "<<query_throughput<<endl;
    outFile.open("result.csv",ios::app);
    outFile<<filename<<","<<length<<",HLL,"<<abs(est_car-pkt_num)*1.0/pkt_num<<","<<insert_throughput<<","<<query_throughput<<endl;
    outFile.close();

/*********************MRB***********************/
    cout<<"\nMRB:"<<endl;
    auto mrbM = MRB(length,mrb_k);
   clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<pkt_num;i++){
        mrbM.insert(Stream[i].second);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    insert_throughput = (double)1000.0*pkt_num / timediff;

    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<query_num;i++){
        est_car = mrbM.estimate();
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    query_throughput = (double)1000.0*query_num /timediff;
    cout<<"estimate value: "<< est_car<<"\t error: "<<abs(est_car-flow_num)
        <<"\t insert: "<<insert_throughput
        <<"\t query: "<<query_throughput<<endl;
    outFile.open("result.csv",ios::app);
    outFile<<filename<<","<<length<<",MRB,"<<abs(est_car-pkt_num)*1.0/pkt_num<<","<<insert_throughput<<","<<query_throughput<<endl;
    outFile.close();

/*********************SRB***********************/
    cout<<"\nSRB:"<<endl;
//    auto srbM = SRB(length,srb_thres);
        auto srbM = SRB(length,srb_thres);

    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i =0;i<pkt_num;i++){
        //cout<<endl<<"insert: "<<i<<endl;
        srbM.insert(Stream[i].second);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    insert_throughput = (double)1000.0*pkt_num / timediff;
//    cout<<srbM.estimate()<<endl;

    clock_gettime(CLOCK_MONOTONIC,&start_time);
    for(int i=0;i<query_num;i++){
        est_car = srbM.estimate();
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    query_throughput = (double)1000.0*query_num /timediff;
    cout<<"estimate value: "<< est_car<<"\t error: "<<abs(est_car-flow_num)
        <<"\t insert: "<<insert_throughput
        <<"\t query: "<<query_throughput<<endl;
    outFile.open("result.csv",ios::app);
    outFile<<filename<<","<<length<<",SRB,"<<abs(est_car-pkt_num)*1.0/pkt_num<<","<<insert_throughput<<","<<query_throughput<<endl;
    outFile.close();




/***** VSA2************/
    cout<<"\nVSB:"<<endl;
    auto vsa2M = VSA2(length,vsa_thres);
    clock_gettime(CLOCK_MONOTONIC,&start_time);
  //  flow_num = pkt_num =1000000;
    for(int i =0;i<pkt_num;i++){
        vsa2M.insert(Stream[i].second);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    insert_throughput = (double)1000.0*pkt_num / timediff;

    clock_gettime(CLOCK_MONOTONIC,&start_time);
   // query_num = 1;
    for(int i=0;i<query_num;i++){
        est_car = vsa2M.estimate();
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    timediff = (long long)(end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
    query_throughput = (double)1000.0*query_num /timediff;
    cout<<"estimate value: "<< est_car<<"\t error: "<<abs(est_car-flow_num)
        <<"\t insert: "<<insert_throughput
        <<"\t query: "<<query_throughput<<endl;
    outFile.open("result.csv",ios::app);
    outFile<<filename<<","<<length<<",VSB,"<<abs(est_car-pkt_num)*1.0/pkt_num<<","<<insert_throughput<<","<<query_throughput<<endl;
    outFile.close();



}
