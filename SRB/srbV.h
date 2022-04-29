#ifndef SRB_H
#define SRB_H


class SRB{
private:
    BitMap G_B;
    int G_num;
    int G_r = 0;
    int G_T =0;
    int G_value=0;
    int G_seed = 7713;
    int G_count = 0;
    int Pre[20]={0};

public:
    SRB(int num, int T):G_B(num){
        G_num =num;
        G_T = T;
        int tmp=0;
        for(int i=0;i<(G_rnum/G_T);i++){
            tmp+= -pow(2,i)*G_rnum*log(1-(G_T*1.0/(G_rnum-i*G_T)));
            Pre[i+1] = tmp;
        }
    }
    void insert(int i){
        uint32_t ghash = murmurhash((const char*)&i,3,G_seed);
        if( NumberOfLeadingZeros(ghash)>=G_r){
            ghash = murmurhash((const char*)&i,3,6417) %G_num;
            if(!G_B.get(ghash)){
                G_value++;
                G_B.set(ghash);
                if(G_value >= G_T){
                    G_r++;
                    G_value = 0;
                }
            }
        }

    }

    int estimate(){
       // cout<<"count: "<<G_count<<endl;

        int ret =0;
        /*
        for(int i=0;i<=G_r-1;i++){
            ret += -pow(2,i)*G_num*log(1-(G_T*1.0/(G_num-i*G_T)));
        }
        ret += -pow(2,G_r)*G_num*log(1-(G_value*1.0)/(G_num-G_r*G_T));
        */
        ret = Pre[G_r] -pow(2,G_r)*G_rnum*log(1-(G_value*1.0)/(G_rnum-G_r*G_T));
        return ret;
      //  return ret;
    }

};

#endif
