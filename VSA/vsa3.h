// using ration to control
// avoid that U close to T
#ifndef VSA3_H
#define VSA3_H
class VSA3{
private:
    int G_T = 0;
    int G_value = 0;
    int G_rnum;
    int G_r =0;
    int G_vnum;
    BitMap G_B;
    float ratio=0.93;
public:
    VSA3(int num, int T):G_B(num){
        G_rnum = num;
        G_vnum = num;
        G_T = T;
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
            if(G_value >= (int)(G_T*ratio)){
                G_r++;
                G_value = 0;
                G_vnum *= 2;
                cout<<"current G_r: "<<G_r<<endl;
            }
        }

    }

    int estimate(){
        int ret =0;
        cout<<"G_R: "<<G_r<<endl;
        for(int i=0;i<=G_r-1;i++){
      //      cout<<"G_rnum: "<<G_rnum<<"\t G_T: "<<G_T<<endl;
            cout<<"ret: "<<-pow(2,i)*G_rnum*log(1-(G_T*ratio*1.0/(G_rnum-(int)i*G_T*ratio)))<<endl;
            ret += -pow(2,i)*G_rnum*log(1-(G_T*ratio/(G_rnum-i*G_T*ratio)));

        }
        ret += -pow(2,G_r)*G_rnum*log(1-(G_value*1.0)/(G_rnum-G_r*G_T*ratio));
                cout<<"g value: "<<G_value<<endl;

        cout<<"ret last: "<<-pow(2,G_r)*G_rnum*log(1-(G_value*1.0)/(G_rnum-G_r*G_T*ratio))<<endl;
        cout<<"sum: "<<ret<<endl;
        return ret;
    }
};
#endif
