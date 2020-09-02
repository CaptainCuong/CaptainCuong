#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif
#include<cmath>
using namespace std;
struct  deNina{
    bool    active;
    int     time;
};
struct  Lionheart{
    bool    active;
    int     time;
};
struct  fake_armor{
    bool    active;
    int     time;
};
struct  POISON{
    bool    active;
    int     time;
};
struct  Odin{
    bool    active;
    bool    clactive;
    int     time;
    int     cltime;
    bool    die;
};
struct Revival{
    bool    active;
    int     castle;
    int     event;
};
struct troll{
    bool usedto;
    bool wing;
    int castle;
    int event;
    int time;
};

//Kiem tra Knight

        //Kiem tra Smith number
int tongchuso(int n){
	int sum=0;
	int chuso=(int)log(n)+1;
	int* Chuso=new int [chuso];
	for(int i=0; i<chuso; i++){
		Chuso[i]=n%10;
		n/=10;
	}
	for( int i=0; i<chuso; i++)
		sum+=Chuso[i];
	return sum;
}

bool isSmith(int n){
    int dem=0;
    int a=n;
    int sum=0;
    //Tao day prime
    bool* prime=new bool[n+1];
    for( int i=0; i<n+2; i++)
        prime[i]=true;
    prime[0]=false;
    prime[1]=false;
    for( int i=2; i<n+2; i++)
        if(prime[i])
            for(int j=2*i; j<n+1; j+=i)
                prime[j]=false;
    //Tao day uoc so
    int* factor= new int [n];
    for( int i=0; i<n; i++)
    	factor[i]=0;
    while(a>1){
        for(int i=2; i<=a; i++)
            if(a%i==0 && prime[i]){
                factor[dem]=i;
                a/=i;
                dem++;
            }
	}
    //Tong cac chu so cua cac uoc
    int sumuoc=0;
        for(int i=0; i< dem; i++){
    	sumuoc+=tongchuso(factor[i]);
	}
	if(sumuoc==tongchuso(n))
		return true;
	else return false;
}


bool checkPytago(int n){
    bool check;
    for(int i=n/(2+sqrt(2));i<=n/2 && ! check; i++){
        for( int j=3; j<i && !check; j++){
            if(i+j+sqrt(pow(i, 2)+pow(j, 2))==n)
                check=true;
        }
    }
    return check;
}


void checkKnight(knight theKnight, bool& normal, bool& King, bool& Lancelot, bool& Princess, bool& Paladin, bool& Dragon, bool& event95, bool& event96, bool& event97, int& nPetal){
    if(theKnight.HP==999){
        King=true;
        event95=true;
        event96=true;
        event97=true;
        return;}
    if(theKnight.HP==888){
        Lancelot=true;
        event96=true;
        return;}
    if(theKnight.HP==777){
        Princess=true;
        event97=true;
        return;}
    if(isSmith(theKnight.HP)){
        Paladin=true;
        event95=true;
        return;}
    if(checkPytago(theKnight.HP)){
        Dragon=true;
        return;}
    normal=true;

    //King Arthur
    if(King){//King có th? rút ki?m b?t kì lúc nào mà không c?n 3 treasures
        event95=true;
        event96=true;
        event97=true;
    }
}

//Cau a) va b) Gap Ultimeca va rut guom Excalibur

void treasure1(int code95, int code96, int code97, bool& event95, bool& event96, bool& event97){
    if((code95==1 && event95 && code96==2 && event96 || code96==1 && event96 && code95==2 && event95) && code97==3){ event97=true; cout<<"Bang 3"<<endl;}
    if((code95==1 && event95 || code96==1 && event96) && code97==2) {event97=true;cout<<"Bang 2"<<endl;}
    if(code97==1) {event97=true;cout<<"Bang 1"<<endl;}
}


bool Ultimecia(knight& theKnight, bool& Exsword, bool& Ulti, bool& Mythrillarmor, POISON& poison, Lionheart& lionheart){
    bool ketqua;
    if(Exsword || lionheart.active){//Neu co Exsword thi THANG
        Ulti= true;
        ketqua=true;
    }else {//Khong co Exsword
        if(!Mythrillarmor){//Neu khong co Mythrill se bi mat mau
            if(theKnight.HP>=3){
                theKnight.HP/=3;
            }else
                theKnight.HP=1;
        }

        ketqua=false;
    }
    if(poison.active){//Neu bi trung doc
        if(theKnight.HP>=3)
                theKnight.HP/=3;
        else
            theKnight.HP=1;
    }
    return ketqua;
}
//Cau c)
void passcastle(knight& theKnight, bool& opponent, int& MaxHP ){
    if(opponent){
        theKnight.level++;
        if(MaxHP<=899)
            MaxHP+=100;
        else
            MaxHP=999;
    }
}

//Cau d) Dieu kien chien THANG quai vat tu 1-5


bool opponent1_5(knight& theKnight,int eventcode, int eventorder, int& MaxHP, POISON& poison, int& antidote,fake_armor& fakearmor, bool& normal,bool& Lancelot, bool& King, bool& Princess, bool& Exsword, Odin& odin, bool& Mythrill, troll& Troll, int castle, int event){
    bool ketqua=false;
    int i=eventorder;
    int b=i%10;
    int levelO= i>6? (b>5? b: 5) : b;
    bool    binhthuong=false;

    //!!!Knight sieu anh hung
    if(King && Exsword || Lancelot){//Thang
        if(eventcode==1) if(theKnight.gil<=899) theKnight.gil+=100; else theKnight.gil=999;
        if(eventcode==2) if(theKnight.gil<=849) theKnight.gil+=150; else theKnight.gil=999;
        if(eventcode==3){//Danh voi Elf
            if(theKnight.gil<=549) theKnight.gil+=450; else theKnight.gil=999;
            antidote++;//THANG dc item antidote
            if(antidote && poison.active){//Neu co antidote va bi poison se giai doc
                poison.active=false;
                antidote--;
            }
        }
        if(eventcode==4) theKnight.gil+=650;
        if(eventcode==5){//Thang troll bi trung loi nguyen
            if(theKnight.gil<=149) theKnight.gil+=850; else theKnight.gil=999;
            if(Troll.usedto==false){
                    if(!antidote){// Khong co antidote se bi trung loi nguyen
                        Troll.usedto=true;
                        Troll.wing=true;
                        Troll.time=6;
                        Troll.event=event;
                        Troll.castle=castle;
                    }else antidote--;
                }
        }

        ketqua=true;

    }else   binhthuong=true;

     //!!!Trường hợp King Arthur không có kiem thì dánh nhu bình thuong thua van tra ve gia tri false nhung có nghia là hòa
    //!!!!Knight binh thuong
    if(binhthuong){
        //Neu co Odin thi thang
        if(odin.active){

            if(eventcode==1) if(theKnight.gil<=899) theKnight.gil+=100; else theKnight.gil=999;
            if(eventcode==2) if(theKnight.gil<=849) theKnight.gil+=150; else theKnight.gil=999;
            if(eventcode==3){//Danh voi Elf
                if(theKnight.gil<=549) theKnight.gil+=450; else theKnight.gil=999;
                antidote++;//THANG dc item antidote
                if(antidote && poison.active){//Neu co antidote va bi poison se giai doc
                    poison.active=false;
                    antidote--;
                }
            }
            if(eventcode==4) theKnight.gil+=650;
            if(eventcode==5){//Thang troll bi trung loi nguyen
                if(theKnight.gil<=149) theKnight.gil+=850; else theKnight.gil=999;
                if(Troll.usedto==false){
                        if(!antidote){// Khong co antidote se bi trung loi nguyen
                            Troll.usedto=true;
                            Troll.wing=true;
                            Troll.time=6;
                            Troll.event=event;
                            Troll.castle=castle;
                        }else antidote--;
                    }
            }

            ketqua=true;
        }

        //Neu co fake Odin thi thua
        if(odin.clactive){
            if(!King){//King khong thua
                if(!Mythrill){//Có Mythrill không bi mat mau
                    if(eventcode==1) theKnight.HP-=1*levelO*10;
                    if(eventcode==2){
                        if(!Princess){
                            theKnight.HP-=1.5*levelO*10;
                        }else{
                            theKnight.HP= (theKnight.HP>=4)? 3/4*theKnight.HP: 1;
                    }
                    if(eventcode==3) theKnight.HP-=4.5*levelO*10;
                    if(eventcode==4) theKnight.HP-=6.5*levelO*10;
                    if(eventcode==5) theKnight.HP-=8.5*levelO*10;
                    }
                }
                ketqua=false;
            }
        }

        //Neu khong co Odin hay fake Odin thi danh nhu binh thuong check lv
        if(!odin.active && !odin.clactive){

            //Mang fakearmor thi THUA
            if(fakearmor.active){
                    //THUA bi tru mau
                if(!King){//King khong thua
                    if(!Mythrill){//Có Mythrill không b? m?t máu
                        if(eventcode==1) theKnight.HP-=1*levelO*10;
                        if(eventcode==2){
                            if(!Princess){
                                theKnight.HP-=1.5*levelO*10;
                            }else{
                                theKnight.HP= (theKnight.HP>=4)? 3/4*theKnight.HP: 1;
                        }
                        if(eventcode==3) theKnight.HP-=4.5*levelO*10;
                        if(eventcode==4) theKnight.HP-=6.5*levelO*10;
                        if(eventcode==5) theKnight.HP-=8.5*levelO*10;
                        }
                    }
                    ketqua=false;
                }
            }
            //Neu khong mang fakearmor thi danh nhu binh thuong
            if(!fakearmor.active){
                if( theKnight.level>= levelO){//Neu THANG duoc thuong tien

                if(eventcode==1) if(theKnight.gil<=899) theKnight.gil+=100; else theKnight.gil=999;
                if(eventcode==2) if(theKnight.gil<=849) theKnight.gil+=150; else theKnight.gil=999;
                if(eventcode==3){//Danh voi Elf
                    if(theKnight.gil<=549) theKnight.gil+=450; else theKnight.gil=999;
                    antidote++;//THANG dc item antidote
                    if(antidote && poison.active){//Neu co antidote va bi poison se giai doc
                        poison.active=false;
                        antidote--;
                    }
                }
                if(eventcode==4) theKnight.gil+=650;
                if(eventcode==5){//Thang troll bi trung loi nguyen
                    if(theKnight.gil<=149) theKnight.gil+=850; else theKnight.gil=999;
                    if(Troll.usedto==false){
                            if(!antidote){// Khong co antidote se bi trung loi nguyen
                                Troll.usedto=true;
                                Troll.wing=true;
                                Troll.time=6;
                                Troll.event=event;
                                Troll.castle=castle;
                            }else antidote--;
                        }
                }

                ketqua=true;
                }else{//Neu lv thap hon thi thua
                    if(!King){//King khong thua
                        if(!Mythrill){//Co Mythrill khong mat mau
                            if(eventcode==1) theKnight.HP-=1*levelO*10;
                            if(eventcode==2){
                                if(!Princess){
                                    theKnight.HP-=1.5*levelO*10;
                                }else{
                                    theKnight.HP= (theKnight.HP>=4)? 3/4*theKnight.HP: 1;
                            }
                            if(eventcode==3) theKnight.HP-=4.5*levelO*10;
                            if(eventcode==4) theKnight.HP-=6.5*levelO*10;
                            if(eventcode==5) theKnight.HP-=8.5*levelO*10;
                            }
                        }

                        ketqua=false;
                    }
                }
            }
        }
    }
    //!!!!Ket thuc knight binh thuong
        //Neu bi trung doc cho du thang hay thua
    if(poison.active){
        if(eventcode==1) theKnight.HP-=1*levelO*10;
        if(eventcode==2) theKnight.HP-=1.5*levelO*10;
        if(eventcode==3) theKnight.HP-=4.5*levelO*10;
        if(eventcode==4) theKnight.HP-=6.5*levelO*10;
        if(eventcode==5) theKnight.HP-=8.5*levelO*10;
    }


    return ketqua;
}

//Cau e (Tornbery)


bool Tornbery6(knight& theKnight, int& MaxHP,int eventnumber, POISON& poison, int& antidote, fake_armor& fakearmor, bool& normal, bool& King, bool& Paladin, bool& Exsword, Odin& odin){
    bool ketqua;
    int i=eventnumber;
    int b=i%10;
    int levelO= i>6? (b>5? b: 5) : b;
    bool binhthuong=false;
    if(King && Exsword){
        if(theKnight.level<=9)
                theKnight.level++;

        ketqua=true;
    }else binhthuong=true;

    if(binhthuong){//Chien binh binh thuong
        //Neu co Odin thi thang
        if(odin.active){
            if(theKnight.level<=9)
                theKnight.level++;

            ketqua=true;
        }

        //Neu khong co Odin thi thua

        if(odin.clactive){//Copy thua khong can thay doi
            if(!Paladin && !King){//N?u là Paladin thì không b? trúng d?c và King không thua
                poison.active=true;
                poison.time=6;
            }
            ketqua=false;
        }
        //Neu khong co Odin thi danh nhu binh thuong
        if(!odin.active && !odin.clactive){
            if(fakearmor.active){//Mang fakearmor thi THUA
                //Neu THUA thi bi trung doc 6 lan
                if(!Paladin && !King){//Neu là Paladin thì không b? trúng d?c
                    poison.active=true;
                    poison.time=6;
                }

                ketqua=false;
            }else{//Neu khong mang fakearmor thi danh nhu binh thuong
                if( theKnight.level>= levelO){//Danh THANG thi level tang 1

                    if(theKnight.level<=9)
                        theKnight.level++;
                    ketqua=true;

                }else{//Neu THUA thi bi trung doc 6 lan
                    if(!Paladin && !King){//N?u là Paladin thì không b? trúng d?c và King không thua
                        poison.active=true;
                        poison.time=6;
                    }
                    ketqua=false;
                }
            }
        }
    }

    //Neu bi trung doc va co thuoc giai
    if(antidote && poison.active){
        poison.active=false;
        poison.time=0;
        antidote--;
    }

    return ketqua;
}

//Cau f (Queen of Card)
bool checkfibo(int n){
    int f1=1;
    int f2=1;
    int f3=2;
    while(f3<n){
        f3=f1+f2;
        f1=f2;
        f2=f3;
    }

    if(f3==n)
        return true;
    return false;
}

bool queenofcard(knight& theKnight, bool& Mythrillarmor, fake_armor& fakearmor,bool& King,bool& normal, bool& Exsword, Odin odin, bool& Katana){
    bool ketqua;
    bool binhthuong=false;
    if(King && Exsword){
        theKnight.gil*=2;//Double gil
    }else   binhthuong=true;

    if(binhthuong){
        if(!odin.active && !odin.clactive){//Neu khong co Odin thi binh thuong
            if(checkfibo(theKnight.HP)){//Chien THANG
                theKnight.gil*=2;//Double gil

                if(Mythrillarmor==false && Katana==false && normal){//Khong co Mythrill va Katana nhan fakearmor va la nguoi thuong
                    fakearmor.active=true;
                    fakearmor.time=6;
                }

                ketqua=true;
            }else{//THUA
                if(!King){//King khong thua
                    if(Katana==false){//Khong co Katana
                        theKnight.gil=0.5*theKnight.gil;
                        theKnight.HP=0.5*theKnight.HP;
                        Mythrillarmor=false;
                    }else theKnight.gil +=50;// Co Katana thua dc cong 50 gil va Mythrill armor khong thay doi
                    ketqua=false;
                }
            }
        }

        //Neu Odin fake thi thua
        if(odin.clactive){
            if(!King){//King khong thua
                    if(Katana==false){//Khong co Katana
                        theKnight.gil=0.5*theKnight.gil;
                        if(!Mythrillarmor) theKnight.HP=0.5*theKnight.HP;
                        Mythrillarmor=false;
                    }else theKnight.gil +=50;// Co Katana thua dc cong 50 gil va Mythrill armor khong thay doi
                    ketqua=false;
                }
        }

        //Neu co Odin thi thang
        if(odin.active){
            theKnight.gil*=2;
            if(Mythrillarmor==false && Katana==false && normal){//Khong co Mythrill va Katana nhan fakearmor va la nguoi thuong
                fakearmor.active=true;
                fakearmor.time=6;
            }
            ketqua=true;
        }
    }


    return ketqua;
}


//Cau g (merchant Nina de Rings)

bool isLucky(int n)
{
    if(n ==1 ||3 ||7|| 9|| 13|| 15|| 21|| 25|| 31|| 33|| 37|| 43|| 49|| 51|| 63|| 67|| 69|| 73|| 75|| 79|| 87|| 93|| 99|| 105|| 111|| 115|| 127|| 129|| 133|| 135|| 141|| 151|| 159|| 163|| 169|| 171|| 189|| 193|| 195|| 201|| 205|| 211|| 219|| 223|| 231|| 235|| 237|| 241|| 259|| 261|| 267|| 273|| 283|| 285|| 289|| 297|| 303|| 307|| 319|| 321|| 327|| 331|| 339|| 349|| 357|| 361|| 367|| 385|| 391|| 393|| 399|| 409|| 415|| 421|| 427|| 429|| 433|| 451|| 463|| 475|| 477|| 483|| 487|| 489|| 495|| 511|| 517|| 519|| 529|| 535|| 537|| 541|| 553|| 559|| 577|| 579|| 583|| 591|| 601|| 613|| 615|| 619|| 621|| 631|| 639|| 643|| 645|| 651|| 655|| 673|| 679|| 685|| 693|| 699|| 717|| 723|| 727|| 729|| 735|| 739|| 741|| 745|| 769|| 777|| 781|| 787 ||801|| 805|| 819 ||823 ||831 ||841 ||855 ||867 ||873|| 883|| 885|| 895 ||897|| 903|| 925|| 927 ||931|| 933 ||937 ||957|| 961 ||975 ||979 ||981 ||991 ||993 ||997 )
    return true;
    return false;
}

int sumofFactors(int n)
{

    int res = 1;
    for (int i = 2; i <= sqrt(n); i++) {

        int count = 0, curr_sum = 1;
        int curr_term = 1;
        while (n % i == 0) {
            count++;

            n = n / i;

            curr_term *= i;
            curr_sum += curr_term;
        }

        res *= curr_sum;
    }
    if (n >= 2)
        res *= (1 + n);

    return res;
}

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

bool checkFriendly(int n, int m) {
    int sumFactors_n = sumofFactors(n);
    int sumFactors_m = sumofFactors(m);


    int gcd_n = gcd(n, sumFactors_n);

    int gcd_m = gcd(m, sumFactors_m);

    if (n / gcd_n == m / gcd_m &&
        sumFactors_n / gcd_n == sumFactors_m / gcd_m)
        return true;

    else
        return false;
}



void Nina( knight& theKnight, POISON& poison, fake_armor& fakearmor, Lionheart& lionheart, int MaxHP, deNina denina, bool& Princess){
    if(denina.active==false){
        denina.active=true;
        denina.time=6;

        if(isLucky(theKnight.HP)){//THOA MAN
            if(theKnight.gil<50)
                return;
            else{
                if(poison.active || fakearmor.active){
                    if(!Princess){
                    poison.active=false;
                    poison.time=0;
                    fakearmor.active=false;
                    theKnight.gil -=50;
                    }else   theKnight.gil +=60;
                }

                if(theKnight.HP+theKnight.gil<=MaxHP){//Doi mau 1:1 cho den khi day mau
                    theKnight.HP+=theKnight.gil;
                    theKnight.gil=0;
                }
                else{
                    theKnight.gil-=(MaxHP-theKnight.HP);
                    theKnight.HP=MaxHP;
                }
            }
        }
        //KHONG THOA MAN thi bi duoi di khong mat gi
        //Neu mau va tien la friendly number
        if(checkFriendly(theKnight.HP, theKnight.gil)){
            poison.active=false;
            poison.time=0;
            theKnight.HP=MaxHP;
            lionheart.active=true;
            lionheart.time=6;
        }
    }
}

//Cau h (Durian Garden)
void DurianGarden(knight& theKnight, POISON& poison, int& Duriantime, int& nPetal, int MaxHP, Odin& odin, bool&Katana){
    if(Katana==false){// Khong co Katana
        Duriantime=3;
        if(poison.active){
            poison.active   =false;
            poison.time     =0;
        }

        if(odin.active){//Gap Durian Garden thi Odin se bien mat
            odin.active     =false;
            odin.time       =0;
        }

        theKnight.HP=MaxHP;
        if(nPetal>=79)
            nPetal=99;
        else nPetal +=20;
    }
    //Co Katana , just ignore it
}

//Cau i (Poisonous mushroom)
void Mushroom(knight& theKnight, POISON& poison,Odin& odin){
    if(!odin.active){
        poison.active=true;
        poison.time=6;
        theKnight.HP/=2;

        if(poison.active)//Neu bi doc nhung van nhat nam
            theKnight.HP=0;
    }
}

//Cau k (Odin)
void Odinfunc(knight& theKnight, Odin& odin, int& Duriantime){
    if(odin.die==false){//Neu Odin chua chet (ca hai real va clone)
        if(odin.clactive==false){//Odin chua chet
            if(odin.active==false){//Neu Odin chua du?c kích ho?t n?u r?i thì thôi
                odin.active=true;
                odin.time=6;
            }
        }else   odin.cltime++; //Neu ch?t r?i mà di qua thì s? l?n tang
                            //Tích d? 3 l?n thì ch?t luôn
        if(odin.cltime==3){
            odin.clactive==false;
            odin.die=true;
        }
    }

}

//Cau l (Merlin)
void Merlin(knight& theKnight, POISON& poison, fake_armor& fakearmor, int MaxHP, bool& goldcoin){
    poison.active=false;
    poison.time=0;
    fakearmor.active=false;
    fakearmor.time=0;
    theKnight.HP=MaxHP;
    goldcoin=true;
}

//Câu n (Hades)
bool	checkprime(int n){
bool* prime=new bool[n+1];
    for( int i=0; i<n+2; i++)
        prime[i]=true;
    prime[0]=false;
    prime[1]=false;
    for( int i=2; i<n+2; i++)
        if(prime[i])
            for(int j=2*i; j<n+1; j+=i)
                prime[j]=false;
    if(prime[n]==true)
    	return true;
    return false;
}



//-------------------------------------------------------------------------------------------------




report*  walkthrough (knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
    report* pReturn;
    //fighting for the existence of mankind here
    int MaxHP=theKnight.HP;
    int code95=2;
    int code96=1;
    int code97=3;
    POISON poison;
    poison.active   =false;
    poison.time=0;

    fake_armor fakearmor;
    fakearmor.active=false;
    fakearmor.time=0;

    Lionheart lionheart;
    lionheart.active=false;
    lionheart.time=0;

    deNina denina;
    denina.active   =false;
    denina.time     =0;


    Odin    odin;
    odin.active     =false;
    odin.clactive   =false;
    odin.cltime     =0;
    odin.time       =0;
    odin.die        =false;

    Revival revivaldoor;
    revivaldoor.active=false;

    troll Troll;
    Troll.wing=false;
    Troll.usedto=false;
    Troll.time=0;


    int lose        =0;
    int win         =0;
    int disNina     =0;//So lan Nina khong duoc xuat hien lai
    int Duriantime  =0;
    int antidote    =0;

    bool event95    =false;
    bool event96    =false;
    bool event97    =false;
    bool Exsword    =false;
    bool Ulti       =false;
    bool Mythrillarmor=false;
    bool goldcoin   =false;
    bool Omega      =true; //Khi nao danh THANG Omega se bat ve false
    bool Katana     =false;

//----------Cac loai Knight
    bool normal     =false;
    bool King       =false;
    bool Lancelot   =false;
    bool Princess   =false;
    bool Paladin    =false;
    bool Dragon     =false;
    checkKnight(theKnight, normal, King, Lancelot, Princess, Paladin, Dragon, event95, event96, event97, nPetal);
    if(normal)  cout<<"Normal"<<endl;
    if(King)  cout<<"King"<<endl;
    if(Lancelot)  cout<<"Lancelot"<<endl;
    if(Princess)  cout<<"Princess"<<endl;
    if(Paladin)  cout<<"Paladin"<<endl;
    if(Dragon)  cout<<"Dragon"<<endl;
    int icastle=0;
    for( ;(nPetal>0 || King) && Ulti==false; ){

        if(icastle==nCastle)
            icastle=0;

        //Set bien opponent
        bool opponent=false;

        //Chay cac event
        int j;
        if(Troll.wing==false)
            j=0;
        else    j=arrCastle[icastle].nEvent-1;
        for( ; (nPetal>0 || King) && Ulti==false; ){
            cout<<arrCastle[icastle].arrEvent[j]<<"    HP   "<<theKnight.HP<<"   gil   "<<theKnight.gil<<"   level  "<<theKnight.level<< "   petal   "<<nPetal<< "   win   "<<win<<"   lose   "<<lose<< "Castle     "<<icastle+1<<"   Event      "<<j+1<< endl;
//---1-5----Cac quai tu 1 den 5
            if(arrCastle[icastle].arrEvent[j]==1 || arrCastle[icastle].arrEvent[j]==2 ||
            arrCastle[icastle].arrEvent[j]==3 ||arrCastle[icastle].arrEvent[j]==4 ||arrCastle[icastle].arrEvent[j]==5){

                bool ketqua=opponent1_5(theKnight,arrCastle[icastle].arrEvent[j], j+1, MaxHP, poison, antidote, fakearmor, normal, Lancelot, King, Princess, Exsword, odin, Mythrillarmor, Troll, icastle, j);
                //Kiem tra thang thua
                if(ketqua)
                    win++;
                else
                    if(!King)
                        lose++;
                opponent=true;

            }

//---06-----Quai so 6(Tornbery)
            if(arrCastle[icastle].arrEvent[j]==6){
                bool ketqua=Tornbery6(theKnight, MaxHP,j+1 , poison, antidote, fakearmor, normal, King, Paladin, Exsword, odin);

                //Kiem tra thang thua
                if(ketqua)
                    win++;
                else
                    if(!King)
                        lose++;
                opponent=true;
            }

//---07-----Quai so 7(Queen of Cards)
            if(arrCastle[icastle].arrEvent[j]==7){
                bool ketqua=queenofcard(theKnight, Mythrillarmor, fakearmor, King, normal, Exsword, odin, Katana);//Vua chay ham vua tra ket qua, cam chay ham 2 lan

                //Kiem tra thang thua
                if(ketqua)
                    win++;
                else
                    if(!King)
                        lose++;
                opponent=true;
            }

//---08-----Quai so 8(merchant Nina de Rings)
            if(arrCastle[icastle].arrEvent[j]==8){
                Nina(theKnight, poison, fakearmor, lionheart, MaxHP, denina, Princess);
            }
//---09-----Event code 9(Durian Garden)
            if(arrCastle[icastle].arrEvent[j]==9){
                DurianGarden(theKnight, poison, Duriantime, nPetal, MaxHP, odin, Katana);
            }

//---10-----Quai so 10(Poisonous Mushroom)
            if(arrCastle[icastle].arrEvent[j]==10){
                Mushroom(theKnight, poison, odin);
            }

//---11-----Event code 11(Odin)
            if(arrCastle[icastle].arrEvent[j]==11){
                Odinfunc(theKnight, odin, Duriantime);
            }

//---12-----Event code 12(Merlin)
            if(arrCastle[icastle].arrEvent[j]==12){
                Merlin(theKnight, poison, fakearmor, MaxHP, goldcoin);
            }

//---13-----Event code 13(Omega Weapon)
            if(arrCastle[icastle].arrEvent[j]==13){
                if(Omega){//Neu chua danh THANG Omega
                    if(theKnight.level==10 && Exsword || Dragon && lionheart.active){//THANG
                        theKnight.level=10;
                        MaxHP =999;
                        theKnight.HP=999;
                        theKnight.gil=999;
                        Omega=false;
                    }else{//THUA
                        if(!Mythrillarmor)//Neu khong co Mythrill armor
                            theKnight.HP=0;//Neu co Mythrill armor thi thoi
                    }
                }
                opponent=true;


            }

//---14-----Event code 14(Hades)
            if(arrCastle[icastle].arrEvent[j]==14){
                bool thang=false;
                bool binhthuong=true;
                if(!Paladin) {//N?u là Paladin thì Hades d? cho qua
                    if((King || Dragon) && odin.active || checkprime(theKnight.HP)&&(event96 && event97 && !Exsword || King && event97 || Lancelot && event97 || Princess && event96)){//(King hoac Dragon + Odin) defeats Hades ho?c External Love
                        thang=true;
                        Mythrillarmor=true;
                        binhthuong=false;
                    }

                    if(binhthuong){
                        if(odin.active==true){//Hades will create a clone of Odin and kill the real Odin immediately
                            odin.active=false;
                            odin.time=0;
                            odin.clactive=true;
                        }
                        if(!goldcoin){//Khong co goldcoin thi phai danh
                            if(Katana){//Neu co Katana thi se THANG
                                thang=true;
                                Katana=false;
                            }else{//Neu khong co Katana se phai danh binh thuong nhu d
                                int i=j+1;
                                int b=i%10;
                                int levelO= i>6? (b>5? b: 5) : b;
                                if(theKnight.level>=levelO) thang=true;
                            }
                        }else goldcoin=false;

                        if(thang)//Neu THANG thi se duoc Mythrillarmor
                            Mythrillarmor=true;

                        if(!thang)//Neu THUA va khong co Mythrill armor
                            if(!Mythrillarmor)
                                theKnight.HP=0;

                        theKnight.gil=0;//Thoat ra hang phai mat het gil

                        //Neu Odin dang giup thi se giet chet Odin va tao ra clOdin trong 3 event
                        if(odin.active){
                            odin.active=false;
                            odin.time=0;
                            odin.clactive=true;
                        }
                    }

                    if(thang){
                        win++;
                    }
                    else{
                        lose++;
                    }
                    opponent=true;
                }
                // N?u là Paladin và odin active thì dánh b?i Hades
            }

//---15-----Event code 15(Scarlet Katana)
            if(arrCastle[icastle].arrEvent[j]==15){
                Katana=true;
            }

//---16-----Event code 16(LockedDoor)
            if(arrCastle[icastle].arrEvent[j]==16){
                if(theKnight.level<=(j+1)%10 && !Princess && !Dragon){
                    j=arrCastle[icastle].nEvent+10;
                }
            }

//---17-----Event code 17(RevivalDoor)
            if(arrCastle[icastle].arrEvent[j]==17){
                if(revivaldoor.active==false){
                    revivaldoor.active=true;
                    revivaldoor.castle=icastle;
                    revivaldoor.event=j;
                }
            }

//---95-----Treasure1 (Paladin shield)
            if(arrCastle[icastle].arrEvent[j]==95){
                if(mode==0){
                    event95=true;
                }else{
                    treasure1(code96, code97, code95, event96, event97, event95);
                }
            }

//---96-----Treasure2 (Lancelot's spear)
            if(arrCastle[icastle].arrEvent[j]==96){
                if(mode==0){
                    event96=true;
                }else{
                    treasure1(code95, code97, code96, event95, event97, event96);
                }
            }

//---97-----Treasure3 (Guinevere's hair)
            if(arrCastle[icastle].arrEvent[j]==97){
                if(mode==0){
                    event97=true;
                }else{
                    treasure1(code95, code96, code97, event95, event96, event97);
                }
            }

//---98-----Excalibur sword
            if(arrCastle[icastle].arrEvent[j]==98){
                Exsword=(event95&&event96&&event97);
            }

//---99-----Ultimecia
            if(arrCastle[icastle].arrEvent[j]==99){
                Ultimecia(theKnight, Exsword, Ulti, Mythrillarmor, poison, lionheart);

                //Kiem tra thang thua
                if(Ulti)
                    win++;
                else
                    lose++;
                opponent=true;
            }
//---------------KET THUC CAC TRUONG HOP--------------//
//---------------Giam cac tac dung sau 1 vong---------//
            if(poison.active){
                poison.time--;
                if(poison.time==0)
                    poison.active=false;
            }

            if(odin.active){
                odin.time--;
                if(odin.time==0){
                    odin.active=false;
                    odin.time=0;
                }
            }

            if(odin.clactive){
                odin.cltime--;
                if(odin.cltime==0)
                    odin.clactive=false;
            }

            if(Duriantime){
                Duriantime--;
            }

            if(denina.active){
                denina.time--;
                if(denina.time==0)
                    denina.active=false;
            }

            if(lionheart.active){
                if(!Paladin)//N?u là Paladin thì Lionheart ? l?i vinh vi?n
                    lionheart.time--;
                if(lionheart.time==0)
                    lionheart.active=false;
            }

            if(fakearmor.active){
                fakearmor.time--;
                if(fakearmor.time==0)
                    fakearmor.active=false;
            }

            if(Duriantime){
                Duriantime--;
                if(Duriantime==0){
                    odin.active=false;
                    odin.time=0;
                }
            }

//----------Neu het mau goi phoenix
            if(theKnight.HP<=0){
                callPhoenix(theKnight, MaxHP);
                if(poison.active){
                    poison.active=false;
                    poison.time=0;
                }
                if(revivaldoor.active){
                    icastle=revivaldoor.castle;
                    j=revivaldoor.event;
                }
            }


//Hoa bi tru sau khi ket thuc event
			if(!(King && nPetal==0))
                nPetal--;


            //Dieu kien chuyen event
            if(Troll.wing==false){
                j++;
                if(j>=arrCastle[icastle].nEvent)    break;//Chu y truong hop Locked Door
            }else{
                Troll.time--;
                if(Troll.time==0){
                    icastle=Troll.castle;
                    j=Troll.event+1;
                    Troll.wing =true;
                }
                if(icastle==0&&j==0){
                    Troll.wing=false;
                    icastle=Troll.castle;
                    j=Troll.event+1;
                    break;
                }

                j--;
                if(j==-1)    break;
            }
        }

        //Dieu kien chuyen castle
        if(!Ulti)
            passcastle(theKnight, opponent, MaxHP);

        if(Troll.wing ==false)
            icastle++;
        else icastle--;

    }

    // success or failure?


    pReturn = (Ulti)? new report : NULL;

    if(pReturn != NULL)
    {
        pReturn->nLose = lose;
        pReturn->nWin = win;
        pReturn->nPetal = nPetal;
    }
    return pReturn;
}
