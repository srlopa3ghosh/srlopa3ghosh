#include<iostream>
//#define xtime(x) ((x<<1)^(((x>>7)&1) * 0x1b))
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

//#define Multiply(x,y) (((y & 1)*x) ^((y>>1 & 1)* xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1)* xtime(xtime(xtime(xtime(x))))))
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))


using namespace std;
void inaddroundkey();
void decrypt();
/*
int state[4][4] ={{0x19, 0xa0,0x9a,0xe9 },
	{ 0x3d, 0xf4, 0xc6, 0xf8 } ,
	{0xe3, 0xe2, 0x8d, 0x48},
	{ 0xbe, 0x2b, 0x2a, 0x08}
	} ;

*/
/*
int state[4][4] ={{0x32, 0x88,0x31,0xe0 },
	{ 0x43, 0x5a, 0x31, 0x37 } ,
	{0x56, 0x30, 0x98, 0x07},
	{ 0xa8, 0x8d, 0xa2, 0x34}
	} ;

*/
/*
int state[4][4] ={{0x01, 0x89,0xfe,0x76 },
	{ 0x23, 0xab, 0xdc, 0x54 } ,
	{0x45, 0xcd, 0xba, 0x32},
	{ 0x67, 0xef, 0x98, 0x10}
	} ;
*/	
int state[4][4] ={{0x01, 0x99,0xfe,0x76 },
	{ 0x23, 0xab, 0xcc, 0x54 } ,
	{0x45, 0xcd, 0xaa, 0x32},
	{ 0x67, 0xef, 0x08, 0x10}
	} ;	
	
	int submat[16][16]={
{0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
{0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
{0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
{0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75},
{0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84},
{0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf},
{0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8},
{0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2},
{0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73},
{0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb},
{0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79},
{0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08},
{0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a},
{0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e},
{0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf},
{0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16} };




/*int instate[4][4] ={{0x39, 0x02,0xdc,0x19 },
	{ 0x25, 0xdc, 0x11, 0x6a } ,
	{0x84, 0x09, 0x85, 0x0b},
	{ 0x1d, 0xfb, 0x97, 0x32}
	} ;
*/
int insbox[16][16]={
{   0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb},
{	0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb},
{	0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e},
{	0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25},
{	0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92},
{	0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84},
{	0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06},
{	0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b},
{	0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73},
{	0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e},
{	0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b},
{	0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4},
{	0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f},
{	0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef},
{	0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61},
{	0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d} };







/*void take_string_input()
{
	char key[10];
	cout<<"\n Enter Key: \n"<<endl;
	cin>>key;
	cout<<key<<endl;
}*/

void substitue()
{
int i,j;	
for(i=0 ; i<4;i++)
{
	for( j=0;j<4;j++){
	
	int val= state[i][j];
	//cout<<"val= "<<val<<" ";
	int y= val%16;
	val=val/16;
	int x=val%16;
	//cout<<"x= "<<x<<"y = "<<y<<" ";
	state[i][j]=submat[x][y];
	//cout<<state[i][j]<<endl;
	
}
}
}

void shiftrow()
{
 	int i,j;
for(i=1 ; i<4;i++)
{
	int count= 1*i;
	while(count){
	
	for( j=0;j<=2;j=j+1)
	{
		int temp= state[i][j];
		state[i][j]=state[i][j+1];
		state[i][j+1]=temp;
	///	cout<<"temp ="<<temp<<"state[i][(j+count)%4]= "<<state[i][j]<<endl;
	}
	count--;
}
}

 }
 
 
void Mixcolumn()
{
	int i;
	unsigned char tmp, tm,t;
	for(i=0;i<4;i++)
	{
		t=state[0][i];
		tmp= state[0][i]^state[1][i] ^ state[2][i] ^state[3][i];
		tm= state[0][i] ^ state[1][i];
		tm= xtime(tm);
		state[0][i] ^=tm ^ tmp;
		tm= state[1][i] ^ state[2][i];
		tm= xtime(tm);
		state[1][i] ^=tm^ tmp;
		tm=state[2][i]^state[3][i];
		tm= xtime(tm);
		state[2][i]^= tm^tmp;
		tm=state[3][i] ^ t;
		tm= xtime(tm);
		state[3][i]^= tm^ tmp;
	}
	
}

int allck[40][4];
int ack=0;

/*
int ck[4][4]={{0x2b,0x28,0xab,0x09},
              {0x7e,0xae,0xf7,0xcf},
	          {0x15,0xd2,0x15,0x4f},
	          {0x16,0xa6,0x88,0x3c}};

*/
int ck[4][4]={{0x0f,0x47,0x0c,0xaf},
              {0x15,0xd9,0xb7,0x7f},
	          {0x71,0xe8,0xad,0x67},
	          {0xc9,0x59,0xd6,0x98}};

int cipher[4][4];	          
	          
void addround()
{
	state[0][0] ^= ck[0][0];
	state[1][0] ^= ck[1][0];
	state[2][0] ^= ck[2][0];
	state[3][0] ^= ck[3][0];
	
	state[0][1] ^= ck[0][1];
	state[1][1] ^= ck[1][1];
	state[2][1] ^= ck[2][1];
	state[3][1] ^= ck[3][1];
	
	state[0][2] ^= ck[0][2];
	state[1][2] ^= ck[1][2];
	state[2][2] ^= ck[2][2];
	state[3][2] ^= ck[3][2];
	
	state[0][3] ^= ck[0][3];
	state[1][3] ^= ck[1][3];
	state[2][3] ^= ck[2][3];
	state[3][3] ^= ck[3][3];

}	          
	          
	          
	          
	          
int c=0;	
void keyschedule()
{
	
	int rcon[4][10]={{0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
	int temp[4];
	int i,j;
//	cout<<"\nround  "<<c+1<<" : \n";
	 temp[0]=ck[1][3];
	 temp[1]=ck[2][3];
	 temp[2]=ck[3][3];
	 temp[3]=ck[0][3];
	 
/*	cout<<"\nrotword: \n";
	for(i=0;i<4;i++)
	{		
	cout<<hex<<temp[i]<<" ";
	}
*/	
	for(i=0 ; i<4;i++)
{
	
	int val= temp[i];
	//cout<<"val= "<<val<<" ";
	int y= val%16;
	val=val/16;
	int x=val%16;
	//cout<<"x= "<<x<<"y = "<<y<<" ";
	temp[i]=submat[x][y];
	//cout<<temp[i]<<endl;
}

/*	cout<<"\nafter sbox: \n";
	for(i=0;i<4;i++)
	{
		cout<<hex<<temp[i]<<" ";
	}
*/
	int ck1[4][4];
   ck1[0][0]=ck[0][0]^temp[0]^rcon[0][c];
    ck1[1][0]=ck[1][0]^temp[1]^rcon[1][c];
     ck1[2][0]=ck[2][0]^temp[2]^rcon[2][c];
      ck1[3][0]=ck[3][0]^temp[3]^rcon[3][c];
      
   ck1[0][1]=ck[0][1]^ck1[0][0];
    ck1[1][1]=ck[1][1]^ck1[1][0];
     ck1[2][1]=ck[2][1]^ck1[2][0];
      ck1[3][1]=ck[3][1]^ck1[3][0]; //5e	57	5b	08	f6	78	aa	d5	ed	e5	b0	69	fa	d4	ff	00
	  
   ck1[0][2]=ck[0][2]^ck1[0][1];
    ck1[1][2]=ck[1][2]^ck1[1][1];
     ck1[2][2]=ck[2][2]^ck1[2][1];
      ck1[3][2]=ck[3][2]^ck1[3][1]; 
      
    ck1[0][3]=ck[0][3]^ck1[0][2];
    ck1[1][3]=ck[1][3]^ck1[1][2];
     ck1[2][3]=ck[2][3]^ck1[2][2];
      ck1[3][3]=ck[3][3]^ck1[3][2];
    
	
	/*cout<<"\nck1: \n"; 
    for(i=0;i<4;i++)
    {
    	for(j=0;j<4;j++)
    	cout<<hex<<ck1[i][j]<<" ";
    	cout<<endl;
	}
	*/
	cout<<"\nafter copy of ck1 to ck\n";
	for(i=0;i<4;i++)
    {
    	for(j=0;j<4;j++)
    	ck[i][j]=ck1[i][j];
	}
	
	for(i=0;i<4;i++)
    {
    	for(j=0;j<4;j++)
    	allck[i+ack][j]=ck1[i][j];
	}
	ack=ack+4;
	
	cout<<"\n new ck(cipher key): \n"; 
    for(i=0;i<4;i++)
    {
    	for(j=0;j<4;j++)
    	cout<<hex<<ck[i][j]<<" ";
    	cout<<endl;
	}
	c=c+1;
	
	cout<<"\n Add roud key\n";
	state[0][0] ^= ck[0][0];
	state[1][0] ^= ck[1][0];
	state[2][0] ^= ck[2][0];
	state[3][0] ^= ck[3][0];
	
	state[0][1] ^= ck[0][1];
	state[1][1] ^= ck[1][1];
	state[2][1] ^= ck[2][1];
	state[3][1] ^= ck[3][1];
	
	state[0][2] ^= ck[0][2];
	state[1][2] ^= ck[1][2];
	state[2][2] ^= ck[2][2];
	state[3][2] ^= ck[3][2];
	
	state[0][3] ^= ck[0][3];
	state[1][3] ^= ck[1][3];
	state[2][3] ^= ck[2][3];
	state[3][3] ^= ck[3][3];

}


int main()
{

    

	int i,j;
	cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
	
//copy ck to cipher
for(i=0 ; i<4;i++)
{
	for(j=0 ; j<4;j++)
	cipher[i][j]=ck[i][j];
}

/*cout<<"sub matrix "<<endl;
for(i=0 ; i<16;i++)
	{
		for( j=0;j<16;j++)
		cout<<" "<<hex <<submat[i][j];
		cout<<endl;
	}
*/	
	//take_string_input();
	
int r;
	
addround();	

cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
for(r=0;r<9;r++)
{
cout<<"\n key encryption round "<<r+1<<":\n";
cout<<"s box substitution: :"<<r+1<<"\n "<<endl;
substitue();	
	

cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
	
cout<<"shift Rows :"<<r+1<<"\n"<<endl;
shiftrow();

cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
	
cout<<"Mix column: :"<<r+1<<"\n"<<endl;	
Mixcolumn();

cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
	
cout<<"keyschedule and Add round key :"<<r+1<<"\n"<<endl;	
keyschedule();
cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}

}

cout<<"\n key encryption round "<<r+1<<":\n";
cout<<"s box substitution: :"<<r+1<<"\n "<<endl;
substitue();	
	

cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
	
cout<<"shift Rows :"<<r+1<<"\n"<<endl;
shiftrow();

cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
	
cout<<"keyschedule and Add round key :"<<r+1<<"\n"<<endl;	
keyschedule();
cout<<"state matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
/*	
cout<<"all round key matrix "<<endl;
for(i=0 ; i<40;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<allck[i][j];
		cout<<endl;
	}
*/	
	
	cout<<"\n now decryption start\n";
	decrypt();

}

	

void insubstitue()
{
cout<<"\n inverse substitute byte\n";
int i,j;	
for(i=0 ; i<4;i++)
{
	for( j=0;j<4;j++){
	
	int val= state[i][j];
	//cout<<"val= "<<val<<" ";
	int y= val%16;
	val=val/16;
	int x=val%16;
	//cout<<"x= "<<x<<"y = "<<y<<" ";
	state[i][j]=insbox[x][y];
	//cout<<state[i][j]<<endl;
	
}
}
}


void inshiftrow()
{
	cout<<"\n inverse shift row\n";
 	int i,j;
for(i=1 ; i<4;i++)
{
	int count= 1*i;
	while(count){
	
	for( j=3;j>=1;j=j-1)
	{
		int temp= state[i][j];
		state[i][j]=state[i][j-1];
		state[i][j-1]=temp;
	///	cout<<"temp ="<<temp<<"state[i][(j+count)%4]= "<<state[i][j]<<endl;
	}
	count--;
}
}
}

int index=39;
void inaddroundkey()
{
	cout<<"\n inverse Add roud key\n";
	state[0][0] ^= allck[index-3][0];
	state[1][0] ^= allck[index-2][0];
	state[2][0] ^= allck[index-1][0];
	state[3][0] ^= allck[index-0][0];
	
	state[0][1] ^= allck[index-3][1];
	state[1][1] ^= allck[index-2][1];
	state[2][1] ^= allck[index-1][1];
	state[3][1] ^= allck[index-0][1];
	
	state[0][2] ^= allck[index-3][2];
	state[1][2] ^= allck[index-2][2];
	state[2][2] ^= allck[index-1][2];
	state[3][2] ^= allck[index-0][2];
	
	state[0][3] ^= allck[index-3][3];
	state[1][3] ^= allck[index-2][3];
	state[2][3] ^= allck[index-1][3];
	state[3][3] ^= allck[index-0][3];
	index=index-4;
}

int mixmat[4][4]=
{
	{0x0E, 0x0B,0x0D,0x09},
	{0x09,0x0E,0x0B,0x0D},
	{0x0D,0x09,0x0E,0x0B},
	{0x0B,0x0D,0x09,0x0E}
};


void inmixcolumn()
{
	int i;
	unsigned char a,b,c,d;
	for(i=0;i<4;i++)
	{
        //For Plaintext 1
		a = state[0][i];
		b = state[1][i];
		c = state[2][i];
		d = state[3][i];


		state[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		state[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		state[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		state[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);


	}
}


/*
void inmixcolumn()
{
	cout<<"\n inverse mix column\n";
	int i;
	
	for(i=0;i<4;i++)
	{
	int e[4];
	for(int j=0;j<4;j++)
	{
		e[j]=state[j][i];
	}
		
	int t[4];
	t[0]= (Multiply(e[0],0x0e)) ^(Multiply(e[1],0x0b ))^(Multiply(e[2],0x0d) )^(Multiply(e[3],0x09 ));
	t[1]= (Multiply(e[0],0x09)) ^(Multiply(e[1],0x0e ))^(Multiply(e[2],0x0b) )^(Multiply(e[3],0x0d));
	t[2]= (Multiply(e[0],0x0d)) ^(Multiply(e[1],0x09 ))^(Multiply(e[2],0x0e) )^(Multiply(e[3],0x0b));
    t[3]= (Multiply(e[0],0x0b)) ^(Multiply(e[1],0x0d ))^(Multiply(e[2],0x09) )^(Multiply(e[3],0x0e));	    

	for(int j=0;j<4;j++)
	{
		state[j][i]=t[j];
	}
	}
	
//	int t= (Multiply(0x0e,0x47)) ^(Multiply(0x0b,0x37 ))^(Multiply(0x0d,0x94 ))^(Multiply(0x09,0xed ));
//	cout<<"\n t= "<<hex<<t<<endl;
}*/




void decrypt()
{
	inaddroundkey();
	int i,j;
	cout<<"instate matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}

	int r=0;
	for(r=0;r<9;r++)
	{
	inshiftrow();
	cout<<"instate matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}

		insubstitue();
		cout<<"instate matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
		inaddroundkey();
		cout<<"instate matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
		inmixcolumn();
			cout<<"instate matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
		

}

	inshiftrow();
	cout<<"instate matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}

		insubstitue();
		cout<<"instate matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}
	
	
	
	
  cout<<"\n inverse Add roud key\n";
	state[0][0] ^= cipher[0][0];
	state[1][0] ^= cipher[1][0];
	state[2][0] ^= cipher[2][0];
	state[3][0] ^= cipher[3][0];
	
	state[0][1] ^= cipher[0][1];
	state[1][1] ^= cipher[1][1];
	state[2][1] ^= cipher[2][1];
	state[3][1] ^= cipher[3][1];
	
	state[0][2] ^= cipher[0][2];
	state[1][2] ^= cipher[1][2];
	state[2][2] ^= cipher[2][2];
	state[3][2] ^= cipher[3][2];
	
	state[0][3] ^= cipher[0][3];
	state[1][3] ^= cipher[1][3];
	state[2][3] ^= cipher[2][3];
	state[3][3] ^= cipher[3][3];
	
	cout<<"instate matrix "<<endl;
	for(i=0 ; i<4;i++)
	{
		for( j=0;j<4;j++)
		cout<<" "<<hex <<state[i][j];
		cout<<endl;
	}

}




/*
// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// Multiplty is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

// MixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the inexperienced.
// Please use the references to gain more information.
void InvMixColumns()
{
	int i;
	unsigned char a,b,c,d;
	for(i=0;i<4;i++)
	{
        //For Plaintext 1
		a = state1[0][i];
		b = state1[1][i];
		c = state1[2][i];
		d = state1[3][i];


		state1[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		state1[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		state1[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		state1[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);


	}
}
*/
