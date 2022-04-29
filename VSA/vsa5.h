//using two hash functions
#ifndef VSA5_H
#define VSA5_H
class VSA5{
private:
    int G_T = 0;
    int G_value = 0;
    int G_rnum;
    int G_r =0;
    int G_vnum;
    int G_used=0;
    BitMap G_B;
public:
    VSA5(int num, int T):G_B(num){
        G_rnum = num;
        G_vnum = num;
        G_T = 1;
        cout<<"G_T: "<<T<<"\t G_rnum: "<<G_rnum<<endl;

        /*
        if(G_rnum >= MAX_SRBLEN){
            cout<<"enlarge MAX len"<<endl;
            exit(1);
        }*/
    }
    void insert(int i){
        int pos = murmurhash((const char*)&i,4,3477) % G_vnum;
        if(pos<G_rnum && G_B.get(pos)==0){
            G_value ++;
            G_B.set(pos);
            if(G_value >= G_T){
                G_r++;
                G_value = 0;
                G_vnum *= 2;
                if(pow(2,G_r)>G_rnum){
                    cout<<"dangerous!"<<endl;
                    exit(-1);
                }
                G_T= pow(2,G_r)-G_T;

                cout<<"current G_r: "<<G_r<<endl;
            }
        }

    }

    int estimate(){
        int ret =0;
        cout<<"G_R: "<<G_r<<endl;
        for(int i=0;i<=G_r-1;i++){
      //      cout<<"G_rnum: "<<G_rnum<<"\t G_T: "<<G_T<<endl;
            cout<<"ret: "<<-pow(2,i)*G_rnum*log(1-(pow(2,i+1)-pow(2,i))*1.0/(G_rnum-pow(2,G_r)));
        //    ret += -pow(2,i)*G_rnum*log(1-(G_T*1.0/(G_rnum-i*G_T)));
            ret+= -pow(2,i)*G_rnum*log(1-(pow(2,i+1)-pow(2,i))*1.0/(G_rnum-pow(2,G_r)));

        }
        ret += -pow(2,G_r)*G_rnum*log(1-(G_value*1.0)/(G_rnum-pow(2,G_r)));
  //      ret += -pow(2,G_r)*G_rnum*log(1-(G_value*1.0)/(G_rnum-G_r*G_T));
                cout<<"g value: "<<G_value<<endl;

        cout<<"ret last: "<<-pow(2,G_r)*G_rnum*log(1-(G_value*1.0)/(G_rnum-pow(2,G_r)))<<endl;
        cout<<"sum: "<<ret<<endl;
        return ret;
    }
};
#endif
