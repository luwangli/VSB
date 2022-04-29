#ifndef MRB_H
#define MRB_H

static const double bitsetratio = 0.93105; //(1-1/exp(rhomax)) rhomax = 2.6744

class MRB{
private:
    int MRB_level;
    int MRB_len;
    //BitMap B[2] ={10,10};
    int tmp_k = 20;
    int tmp_m = 2000;
    BitMap B[20] = {tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,
                    tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m,tmp_m};
    int setmax;


public:
    MRB(int num, int level){
        MRB_level = level;
        MRB_len = num / MRB_level;
        setmax =(int)(MRB_len*bitsetratio);
        //check
        if(MRB_level >= tmp_k){
            cout<<"level is too much"<<endl;
            exit(1);
        }
        if(MRB_len >= tmp_m){
            cout<<"length in each Bitmap is too much"<<endl;
            exit(1);
        }


    }
    void insert(int i){
        uint32_t level_hash = murmurhash((const char*)&i,4,1329);
        uint32_t level = NumberOfLeadingZeros(level_hash);
        uint32_t pos = murmurhash((const char*)&i,4,1177) % MRB_len;
     /*   if(level<MRB_level){
            B[level].set(pos);
        }else{
            B[MRB_level-1].set(pos);
        }*/
        B[level&&(MRB_level-1)].set(pos);

    }
    int loghash(int p){
        int ret = 0;
        while((p&0x00000001) == 1){
            p = p>>1;
            ret++;
        }
        return ret;
    }

    int estimate(){
        int factor = 1;
        int base;
        int z;
        double m = 0;
      //  cout<<"setmax: "<<setmax<<endl;
   //     cout<<"mrb_len: "<<MRB_len<<endl;
        for(base=0;base<MRB_level-1;base++){
            z =  B[base].countzerobits(0,MRB_len);
        //    cout<<"level: "<<base<<" zerobits: "<<z<<endl;
            if(MRB_len -z <= setmax){
                break;
            }else{
                factor = factor*2;
            }
        }
        if(base >=MRB_level-1){
            cout<<"Cannot give estimate"<<endl;
        }
        for(int i=base;i<MRB_level;i++){
            z = B[i].countzerobits(0,MRB_len);
         //   cout<<"level:"<<i<<" zerobits: "<<z<<" m value:"<<m<<endl;
        //    cout<<"add value: "<<(-MRB_len*log(z*1.0/MRB_len))<<endl;
            m +=  (-MRB_len*log(z*1.0/MRB_len));
        }
        return (int)(factor*m);
    }

};
#endif
