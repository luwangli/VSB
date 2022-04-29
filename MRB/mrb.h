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
          uint32_t key = murmurhash((const char*)&i,4,9137);
        int pos, crt;
        for(crt=0;crt<MRB_level-1;crt++){
            if(!(key&1)){
                key = key>>1;
                break;
            }else{
                key=key>>1;
            }
        }
        if(crt<MRB_level-1){
            pos = key %MRB_len;
            B[crt].set(pos);
        }else{
            pos = key%MRB_len;
            B[crt].set(pos);
        }


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
