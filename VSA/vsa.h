#ifndef VSA_H
#define VSA_H
class VSA{
private:
    int G_T = 0;
    int G_value = 0;
    int G_rnum;
    int G_r =0;
    int G_vnum;
    BitMap G_B;
public:
    VSA(int num, int T):G_B(num){
        G_rnum = num;
        G_vnum = num;
        G_T = T;
        cout<<"G_T: "<<T<<"\t G_rnum: "<<G_rnum<<endl;
       /* if(G_rnum >= MAX_SRBLEN){
            cout<<"enlarge MAX len"<<endl;
            exit(1);
        }*/
    }
    void insert(int i){
        uint32_t hash_val = murmurhash((const char*)&i,4,3417);
        int leadzero = NumberOfLeadingZeros(hash_val);
        int pos;
     //   cout<<leadzero<<endl;
        if(leadzero>=G_r){
        //    cout<<"G_vnum? "<<G_vnum<<endl;
            pos = hash_val % G_vnum;
       //     cout<<"get pos: "<<pos<<endl;
            if(pos < G_rnum && G_B.get(pos)==0){
                G_value++;
                G_B.set(pos);
          //      cout<<"insert success"<<endl;
                if(G_value >= G_T){
                    G_r = G_r+1;
                    G_value = 0;
                    G_vnum = 2*G_vnum;
                }
            }
        }
    }

    int estimate(){
        int ret =0;
        cout<<"G_R: "<<G_r<<endl;
        for(int i=0;i<=G_r-1;i++){

            ret += -pow(2,i)*G_rnum*log(1-(G_T*1.0/(G_rnum-i*G_T)));
            //cout<<"ret: "<<ret<<endl;
            cout<<"ret: "<<-pow(2,2*i)*G_rnum*log(1-(G_T*1.0/(G_rnum-i*G_T)))<<endl;

        }
        ret += -pow(2,G_r)*G_rnum*log(1-(G_value*1.0)/(G_rnum-G_r*G_T));
        cout<<"g value: "<<G_value<<endl;
        cout<<"ret last: "<<-pow(2,2*G_r)*G_rnum*log(1-(G_value*1.0)/(G_rnum-G_r*G_T))<<endl;

        return ret;
    }
};
#endif
