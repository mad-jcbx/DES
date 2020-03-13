#include"table.h"

typedef unsigned char ElemType;

ElemType APK[256][8];

int ReadPlain(ElemType plain[8]);
int ReadCipher(ElemType cipher[8]);
int ReadKey(ElemType by[8]);
int ReadSubKey(ElemType by[6]);
int byte6tobite48(ElemType by[6],ElemType bi[48]);
int bite48tobyte6(ElemType bi[48],ElemType by[6]);
int bytetobite(ElemType C,ElemType M[8]);
int bitetobyte(ElemType M[8],ElemType *c);
int byte8tobite64(ElemType by[8],ElemType bi[64]);
int bite64tobyte8(ElemType bi[64],ElemType by[8]);
int IP1(ElemType IP[64]);
int IP2(ElemType IP[64]);
int PC1(ElemType K[64],ElemType k1[56]);
int PC2(ElemType K[56],ElemType K1[48]);
int CycleShift(ElemType C[28],ElemType D[28],int cycle);
int CD_Key(ElemType C[28],ElemType D[28],ElemType Key[56]);
int Key_CD(ElemType C[28],ElemType D[28],ElemType Key[56]);
int MakeSubsKeys1(ElemType subsKey[16][48],ElemType K1[56]);
int MakeSubsKeys(ElemType subsKey[16][48],ElemType Key[64]);
int EP(ElemType R[32],ElemType E1[48]);
int PP(ElemType S[32]);
int SP(ElemType K[48],ElemType S[32]);
int XOR(ElemType L[48],ElemType R[48],int count);
int Feistel(ElemType R[32],ElemType K[48],ElemType F[32]);
int Main_Cycle(ElemType L[32],ElemType R[32],ElemType K[48]);
int DES_encrypt(ElemType bi[64],ElemType subsKeys[16][48]);
int DES_decrypt(ElemType bi[64],ElemType subsKeys[16][48]);

int rightfun(ElemType temp[8],int *t,int *d);
int leftfun(ElemType temp[8],int *t,int *d);
int fun(ElemType temp[8],int *t,int *d);
int Re_PC(ElemType Key[56]);
int Re_CycleShift(ElemType C[28],ElemType D[28],int cycle);
int Crack_Cycle(ElemType Key[64],ElemType cipher[64]);
int Crack(ElemType Key[64],ElemType cipher[64]);
int Initial_APK();



int ReadPlain(ElemType plain[8])//��ȡԭ��
{
	
	FILE *f1;
	if((fopen("D:\\VC++ 6.0 Ӣ�İ�\\DES_decipher\\DES_decipher\\plain.txt","r"))==NULL)
		printf("file open failed!\n");
	else
		f1=fopen("plain.txt","r");
	fread(plain,1,9,f1);
	return 0;
}

int ReadCipher(ElemType cipher[8])
{
	
	FILE *f1;
	if((fopen("cipher.txt","r"))==NULL)
		printf("file open failed!\n");
	else
		f1=fopen("cipher.txt","r");
	fread(cipher,1,9,f1);
	//fgets(cipher,9,f1);
	return 0;
}


int ReadKey(ElemType by[8])
{
	FILE *f;
	if((fopen("key.txt","r"))==NULL)
		printf("file open failed!\n");
	else
		f=fopen("key.txt","r");
	fread(by,1,9,f);	
	return 0;
}

int ReadSubKey(ElemType by[6])
{
	FILE *f;
	if((fopen("subkey.txt","r"))==NULL)
		printf("file open failed!\n");
	else
		f=fopen("subkey.txt","r");
	fread(by,1,7,f);	
	return 0;
}

int byte6tobite48(ElemType by[6],ElemType bi[48])
{
	for(int i=0;i<6;i++)
	{
		bytetobite(*(by+i),bi+i*8);
	}

	return 0;
}

int bite48tobyte6(ElemType bi[48],ElemType by[6])
{
	ElemType *p;
	for(int i=0;i<6;i++)
	{
		p=&by[i];
		bitetobyte(bi+i*8,p);
	}
	return 0;

}


int bytetobite(ElemType C,ElemType M[8])
{
	for(int i=0;i<8;i++)
		*(M+i)=(C>>(7-i))&1;
	return 0;
}

int bitetobyte(ElemType M[8],ElemType *c)
{
	*c=0;
	for(int i=0;i<8;i++)
		*c+= M[i]<<(7-i);
	return 0;
}

int byte8tobite64(ElemType by[8],ElemType bi[64])
{
	for(int i=0;i<8;i++)
	{
		bytetobite(*(by+i),bi+i*8);
	}

	return 0;
}

int bite64tobyte8(ElemType bi[64],ElemType by[8])
{
	ElemType *p;
	for(int i=0;i<8;i++)
	{
		p=&by[i];
		bitetobyte(bi+i*8,p);
	}
	return 0;

}

int IP1(ElemType IP[64])//IP1
{
	ElemType temp[64];
	for(int i=0;i<64;i++)
		temp[i]=IP[IP_1[i]-1];
	memcpy(IP,temp,64);
	return 0;
}

int IP2(ElemType IP[64])//ReIP
{
	ElemType temp[64];
	for(int i=0;i<64;i++)
		temp[i]=IP[IP_2[i]-1];
	memcpy(IP,temp,64);
	return 0;
}


int PC1(ElemType K[64],ElemType k1[56])//PC1
{
	for(int i=0;i<56;i++)
		k1[i]=K[PC_1[i]-1];
	return 0;
}

int PC2(ElemType K[56],ElemType K1[48])//PC2
{
	for(int i=0;i<48;i++)
		K1[i]=K[PC_2[i]-1];
	return 0;
}

int CycleShift(ElemType C[28],ElemType D[28],int cycle)
{
	ElemType temp[28];
	int time=shift[cycle];
	memcpy(temp,C,time);
	memcpy(C,C+time,28-time);
	memcpy(C+28-time,temp,time);

	memcpy(temp,D,time);
	memcpy(D,D+time,28-time);
	memcpy(D+28-time,temp,time);
	return 0;
}

int CD_Key(ElemType C[28],ElemType D[28],ElemType Key[56])
{
	for(int i=0;i<28;i++)
		Key[i]=C[i];
	for(i=28;i<56;i++)
		Key[i]=D[i-28];
	return 0;
}
int Key_CD(ElemType C[28],ElemType D[28],ElemType Key[56])
{
	for(int i=0;i<56;i++)
		if(i<28)
			C[i]=Key[i];
		else
			D[i-28]=Key[i];
	return 0;

}

int MakeSubsKeys1(ElemType subsKey[16][48],ElemType K1[56])
{
	ElemType C[28];
	ElemType D[28];
	Key_CD(C,D,K1);
	for(int i=0;i<16;i++)
	{
		CycleShift(C,D,i);
		CD_Key(C,D,K1);
	
		PC2(K1,subsKey[i]);
/*	printf("K%d",i);
		for(int j=0;j<48;j++){
			if(j%8==0)
				printf(" ");
			printf("%d",subsKey[i][j]);
		}
		printf("\n");*/
	}


	return 0;
}

int MakeSubsKeys(ElemType subsKey[16][48],ElemType Key[64])
{
	ElemType K1[56];
	PC1(Key,K1);

	MakeSubsKeys1(subsKey,K1);
	return 0;
}

int EP(ElemType R[32],ElemType E1[48])
{
	for(int i=0;i<48;i++)
		E1[i]=R[E[i]-1];
	return 0;
}

int PP(ElemType S[32])
{
	ElemType temp[32];
	for(int i=0;i<32;i++)
		temp[i]=S[P[i]-1];
	memcpy(S,temp,32);
	return 0;
}

int SP(ElemType K[48],ElemType S[32])
{
	int line,row,output;
	ElemType temp[6];
	for(int i=0;i<8;i++)
	{
		memcpy(temp,K+6*i,6);
		line=(temp[0]<<1)+temp[5];
		row=(temp[1]<<3)+(temp[2]<<2)+(temp[3]<<1)+temp[4];
		output=Sbox[i][line][row];
		for(int j=0;j<4;j++)
			S[i*4+j]=(output>>(3-j))&1;
	}
	return 0;
}

int XOR(ElemType L[48],ElemType R[48],int count)
{
	for(int i=0;i<count;i++)
		L[i]^=R[i];
	return 0;
}

int Feistel(ElemType R[32],ElemType K[48],ElemType F[32])
{
	ElemType E1[48];
	EP(R,E1);
	XOR(E1,K,48);
	SP(E1,F);
	PP(F);
	return 0;
}
	
int Main_Cycle(ElemType L[32],ElemType R[32],ElemType K[48])
{
	ElemType temp[32];
	ElemType F[32];

	Feistel(R,K,F);
	memcpy(temp,R,32);
	for(int i=0;i<32;i++)
		R[i]=F[i]^L[i];
	memcpy(L,temp,32);
	return 0;
}

int DES_encrypt(ElemType bi[64],ElemType subsKeys[16][48])
{
	ElemType L[32];
	ElemType R[32];

	IP1(bi);
	for(int i=0;i<32;i++)
		L[i]=bi[i];
	for(i=32;i<64;i++)
		R[i-32]=bi[i];

	//16�ּ���
	for(i=0;i<16;i++)
		Main_Cycle(L,R,subsKeys[i]);

	memcpy(bi,R,32);
	memcpy(bi+32,L,32);

	IP2(bi);
	return 0;
}

int DES_decrypt(ElemType bi[64],ElemType subsKeys[16][48])
{
	ElemType L[32];
	ElemType R[32];

	IP1(bi);
	for(int i=0;i<32;i++)
		L[i]=bi[i];
	for(i=32;i<64;i++)
		R[i-32]=bi[i];

	
	for(i=0;i<16;i++)
		Main_Cycle(L,R,subsKeys[15-i]);

	memcpy(bi,R,32);
	memcpy(bi+32,L,32);
	IP2(bi);
  return 0;
}



int leftfun(ElemType temp[8],int *t,int *d)
{
	temp[*d]=0;
	if(*d==7)
	{
		for(int i=0;i<8;i++)
			APK[*t][i]=temp[i];

		*d=*d-1;
		*t=*t+1;
		return 0;
	}
	else{
		*d=*d+1;
		leftfun(temp,t,d);
		*d=*d+1;
		rightfun(temp,t,d);
		*d=*d-1;
	}
	return 0;
}


int rightfun(ElemType temp[8],int *t,int *d)
{
	temp[*d]=1;
	if(*d==7)
	{
		for(int i=0;i<8;i++)
			APK[*t][i]=temp[i];
		*d=*d-1;
		*t=*t+1;
		return 0;
	}
	else{
		*d=*d+1;
		leftfun(temp,t,d);
		*d=*d+1;
		rightfun(temp,t,d);
		*d=*d-1;
	}
	return 0;
}



int fun(ElemType temp[8],int *t,int *d)
{
	*d=*d+1;
	leftfun(temp,t,d);	
	*d=*d+1;
	rightfun(temp,t,d);
	*d=*d-1;

	return 0;
}

int Re_PC(ElemType Key[56])
{
	ElemType temp[56];
	for(int i=0;i<48;i++)
	{
		temp[PC_2[i]-1]=Key[i];
	}
	memcpy(Key,temp,56);
	return 0;
	
}

int Re_CycleShift(ElemType C[28],ElemType D[28],int cycle)
{
	ElemType temp[28];
	int time=shift[cycle];
	memcpy(temp,C+28-time,time);
	memcpy(C+time,C,28-time);
	memcpy(C,temp,time);

	memcpy(temp,D+28-time,time);
	memcpy(D+time,D,28-time);
	memcpy(D,temp,time);
	return  0;
}





int Crack_Cycle(ElemType Key[64],ElemType cipher[64])
{
	ElemType C[28];
	ElemType D[28];
	ElemType subsKey[16][48];
	ElemType by[8];
	ElemType temp1[64];
	ElemType temp2[64];	
	for(int i=0;i<16;i++)
	{
		memcpy(temp2,cipher,64);
		memcpy(temp1,Key,64);		
		Key_CD(C,D,temp1);
		for(int k=i;k>=0;k--)
			Re_CycleShift(C,D,k);
			

		CD_Key(C,D,temp1);
		MakeSubsKeys1(subsKey,temp1);			
		DES_decrypt(temp2,subsKey);		
		bite64tobyte8(temp2,by);
		if(by[0]==1){//filter
			for(int l=0;l<8;l++)		
				printf("%c",by[l]);	
		printf("\n");
		}
	}
	return 0;
}



int Crack(ElemType Key[64],ElemType cipher[64])
{
	Re_PC(Key);	

	ElemType temp[64];
	memcpy(temp,Key,64);
	for(int j=0;j<256;j++)//253
	{
		memcpy(Key,temp,64);
		Key[8]=APK[j][0];
		Key[17]=APK[j][1];
		Key[21]=APK[j][2];
		Key[24]=APK[j][3];
		Key[34]=APK[j][4];
		Key[37]=APK[j][5];
		Key[42]=APK[j][6];
		Key[53]=APK[j][7];//all possible key			

		Crack_Cycle(Key,cipher);
	}
	return 0;
}


int Initial_APK()
{
	ElemType temp[8];
	int *t;
	int *d;
	int t1=0;
	int d1=-1;
	t=&t1;
	d=&d1;
	fun(temp,t,d);
	return 0;
}



int main()
{
	int a;
	ElemType bi[64];
	ElemType by[8];
	ElemType by1[6];
	ElemType Key[48];
	
	ElemType subsKeys[16][48];
	printf("----------------------------------------------\n");
	printf("|                                            |\n");
	printf("|                                            |\n");
	printf("|                 DES                    |\n");
	printf("|                                            |\n");
	printf("|                                            |\n");
	printf("----------------------------------------------\n");

	printf("function: ");
	printf("1.encrypt ");
	printf("2.decrypt ");
	printf("3.crack ");
	printf("0.exit\n\n");
	printf("tips:fill files!(key,plain,cipher,subskey)\n\n\n");
	scanf("%d",&a);


	switch(a){
	case 1:{
		ReadKey(by);
		byte8tobite64(by,bi);
 		MakeSubsKeys(subsKeys,bi);
		ReadPlain(by);
		byte8tobite64(by,bi);
		printf("\n");
		DES_encrypt(bi,subsKeys);
		printf("\n");
		bite64tobyte8(bi,by);		
		   }break;
	case 2:{
		ReadKey(by);
		byte8tobite64(by,bi);
 		MakeSubsKeys(subsKeys,bi);
		ReadCipher(by);
		byte8tobite64(by,bi);
		DES_decrypt(bi,subsKeys);
		bite64tobyte8(bi,by);
		for(int i=0;i<8;i++)
			printf("%c ",by[i]);		
		   }break;
	case 3:{
		Initial_APK();
		ReadSubKey(by1);
		byte6tobite48(by1,Key);
		ReadCipher(by);
		byte8tobite64(by,bi);
		Crack(Key,bi);		   
		   }break;
	case 0:{		   
		   }break;
	default:return 0;
	}
	
	return 0;
}
//3 days by jcbx-----------------------------------2020.3.10 22:53
