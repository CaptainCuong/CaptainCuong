#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

#ifndef _sword_cpp_
#include "sword.cpp"
#define _sword_cpp_
#endif

using namespace std;
int maxHP;

const int EVENT_SIZE = 100;
const int MAX_CHARACTER_PER_LINE = 250;
const int CASTLE_SIZE = 100;

//read data from input file to corresponding variables
//return 1 if successfully done, otherwise return 0
int readFile(const char* filename, knight& theKnight, castle arrCastle[], int& nCastle, int& nPetal, int& mode)
{
	const char* file_name = filename;
	FILE* f = 0;
	char* str = new char[MAX_CHARACTER_PER_LINE];
	int num;

	f = fopen(file_name, "r");
	if (f == NULL)	//file not found || cannot read
		return 0;

	fgets(str, MAX_CHARACTER_PER_LINE, f);
	if (feof(f))
		return 0;
	int start = 0;
	int len = strlen(str);
	//read mode
	while (start < len && str[start] == ' ')
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start++] - '0';
	}
	mode = num;
	//read petals
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start++] - '0';
	}
	nPetal = num;
	if (nPetal < 0 || nPetal > 99)
		return 0;

	//read knight's information
	fgets(str, MAX_CHARACTER_PER_LINE, f);
	if (feof(f))
		return 0;
	start = 0;
	len = strlen(str);
	//read HP
	while (start < len && str[start] == ' ')
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start++] - '0';
	}
	theKnight.HP = num;
	if (theKnight.HP < 1 || theKnight.HP > 999)
		return 0;
	//read level
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start++] - '0';
	}
	theKnight.level = num;
	if (theKnight.level < 1 || theKnight.level > 10)
		return 0;
	//read gil
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start++] - '0';
	}
	theKnight.gil = num;
	if (theKnight.gil < 1 || theKnight.gil > 999)
		return 0;

	nCastle = 0;
	int nEvent = 0;

	while (1){
		str = new char[MAX_CHARACTER_PER_LINE];
		if (feof(f))
			break;
		fgets(str, MAX_CHARACTER_PER_LINE, f);
		if (str == NULL)
			break;
		start = 0;
		len = strlen(str);
		while (start < len){
			while (start < len && (str[start] > '9' || str[start] < '0'))
				start ++;
			if (start >= len)
				break;
			int num = 0;
			while (start < len && str[start] <= '9' && str[start] >= '0'){
				num = num  * 10 + str[start++] - '0';
			}
			//new castle
			if (num == 0){
				arrCastle[nCastle].nEvent = nEvent;
				nCastle++;
				nEvent = 0;
			}else{
				arrCastle[nCastle].arrEvent[nEvent++] = num;
			}
		}
	}

	fclose(f);
	return 1;
}

void display(knight theKnight, report* rp)
{
  std::cout.flush();
  if (rp==NULL) std::cout << "Love me before the last petal falls\n";
  else
  {
      // std::cout << theKnight.HP + theKnight.level + theKnight.gil + rp->nPetal + rp->nWin + rp->nLose;
			std::cout << "Win result:\n";
			std::cout << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.gil << std::endl;
			std::cout << rp->nPetal << ' ' << rp->nWin << ' ' << rp->nLose << std::endl;
      std::cout << callPhoenix(theKnight, 999);
      delete rp;
   }
}

//called when knight falling in the battle field
int callPhoenix(knight& woundedKnight, int MaxHP)
{
	static int nTimes = 0;
	woundedKnight.HP = MaxHP/2;
	woundedKnight.gil = woundedKnight.gil<100? 0: woundedKnight.gil-100;
	return ++nTimes;
}

//for mode 1 only
int hash(int eventCode)
{
	return eventCode;
}

int main(int argc, char* argv[])
{

   knight theKnight;
   int nCastle; //number of castles
   cout<<"Nhap vao so luong castle:"<<endl;
   cin>>nCastle;
   castle arrCastle[CASTLE_SIZE];// array of castles
   cout<<"Nhap vao so luong event o cac castle"<<endl;
   for( int i=0; i<nCastle; i++){
   		cin>>arrCastle[i].nEvent;
   }
   cout<<"Nhap vao cac su kien trong castle"<<endl;
   for( int i=0; i<nCastle; i++){
   		for( int j=0; j<arrCastle[i].nEvent; j++)
   			cin>>arrCastle[i].arrEvent[j];
   }
   int nPetal; // number of petals
   cout<<"Moi nhap vao so luong canh hoa"<<endl;
   cin>>nPetal;
   cout<<"Moi nhap vao hp"<<endl;
   cin>>theKnight.HP;
   cout<<"Moi nhap vao lv"<<endl;
   cin>>theKnight.level;
   cout<<"Moi nhap vao gil"<<endl;
   cin>>theKnight.gil;
   int mode; // setting mode
   cout<<"Moi nhap vao mode"<<endl;
   cin>>mode;
   report* pReport; //

   maxHP = theKnight.HP;
//------------------------------------------------XUAT RA MAN HINH---------------------
   std::cout << mode << " => " << nPetal <<  " => " <<  nCastle << std::endl;
   std::cout << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.gil << std::endl;
   for (int i = 0; i < nCastle; i++)
   {
       castle cc = arrCastle[i];
       for (int j = 0; j < cc.nEvent; j++)
				std::cout << cc.arrEvent[j] <<  ' ';
		   std::cout << std::endl;
   }
   cout<<endl<<"--------------------------"<<endl;

   pReport = walkthrough (theKnight, arrCastle, nCastle, mode, nPetal);
   display(theKnight,pReport);

   return 0;
}
