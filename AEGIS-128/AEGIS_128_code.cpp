#include <bits/stdc++.h>
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
using namespace std;

void Aes();
void store();
int state[4][4] ;


int IV[4][4] ={{0x01, 0x02,0x03,0x04 },
	{ 0x05, 0x06, 0x07, 0x08 } ,
	{0x09, 0x0a, 0x0b, 0x0c},
	{ 0x0d, 0x0e, 0x0f, 0x00}
	} ;
	
int Key[4][4]={{ 0x0d, 0x0e, 0x0f, 0x00},
                {0x09, 0x0a, 0x0b, 0x0c},
				{ 0x05, 0x06, 0x07, 0x08 },
				{0x01, 0x02,0x03,0x04 }};
				
int C0[4][4] ={{0x00, 0x01,0x01,0x02 },  
	{0x03, 0x05, 0x08, 0x0d } ,
	{0x15,0x22, 0x37, 0x59},
	{ 0x90,0xe9, 0x79, 0x62}
	} ;
	
int C1[4][4] ={{0xdb, 0x3d,0x18,0x55 },
	{ 0x6d, 0xc2, 0x2f, 0xf1 } ,
	{0x20, 0x11, 0x31, 0x42},
	{ 0x73, 0xb5, 0x28, 0xdd}
	} ;

//constants, const0 := 000101020305080d1522375990e97962
  //and const1 := db3d18556dc22ff12011314273b528dd
	
	
int S0[4][4];	
int S1[4][4];
int S2[4][4];
int S3[4][4];
int S4[4][4];
	
int Meven[4][4];
int Modd[4][4];
/*
int AD0[4][4] ={{0x0a, 0xb1, 0xc2, 0xd3},
            	{0x01, 0x02, 0x03, 0x04},
	            {0x05, 0x06, 0x07, 0x08},
	            {0x09, 0x0a, 0x0b, 0x0c}
	            };

int AD1[4][4] ={{0x11, 0x22, 0x33, 0x44 },
	{ 0xaa, 0xbb,0xcc,0xdd } ,
	{0x55, 0x66, 0x77, 0x88},
	{ 0x99, 0x00, 0xb0, 0xc0}
	} ;

int AD2[4][4] ={{ 0x51, 0x61, 0x71, 0x81},
	{ 0x12, 0xf2, 0xa3, 0xa4 } ,
	{0xfa, 0xba,0xca,0xda},
	{ 0xa9, 0xea, 0xeb, 0xec}
	} ;


int AD3[4][4] ={{ 0x49, 0x4a, 0x4b, 0x4c },
	            { 0x41, 0x42, 0x43, 0x84 } ,
	            {0x45, 0x46, 0x47,0x48},
	            { 0x4a, 0xb4,0xc4,0xd4 }
	            } ;


int AD4[4][4] ={{0x0a, 0xb1,0xc2,0xd3 },
	{ 0x05, 0x06, 0x07, 0x08} ,
	{ 0x0a, 0xb1,0xc2,0xd3},
	{ 0x09, 0x0a, 0x0b, 0x0c}
	} ;


int AD5[4][4] ={{0x3a, 0xb3,0x32,0x93 },
	{  0x79, 0x03, 0x3f, 0x3c} ,
	{0x85, 0x86, 0x37, 0x38},
	{0x81, 0x32, 0xb3, 0xc4 }
	} ;

int AD6[4][4] ={{0x9a, 0xb9,0xc9,0xd9 },
	{  0x69, 0x6a, 0x6b, 0x6c} ,
	{0x71, 0x72, 0x73, 0x74},
	{ 0x75, 0x76, 0x27, 0x78 }
	} ;

int AD7[4][4] ={{0x88, 0xb8,0x82,0xd8 },
	{  0xb9, 0xba, 0xbb, 0xbc} ,
	{0xc5, 0xc6, 0xd7, 0xc8},
	{0xec, 0xed, 0xef, 0xee }
	} ;
*/
/*	
int P0[4][4] ={{0x32, 0x01,0x31,0xe0 },
	{ 0x43, 0x5a, 0x46, 0x37 } ,
	{0x56, 0x30, 0x98, 0x07},
	{0x5a, 0x93, 0xd8, 0x07},
	} ;
	
int P1[4][4] ={{0x33, 0x82,0x11,0x00 },
	{ 0x33, 0x55, 0x13, 0x77 } ,
	{0x5a, 0xa0, 0xa8, 0xa7},
	{ 0xb8, 0xbd, 0xab, 0xb4}
	} ;

int P2[4][4] ={{0xe2, 0xe8,0xe1,0xc1 },
	{ 0xe3, 0xea, 0xc1, 0xd7 } ,
	{0x50, 0x35, 0x94, 0x17},
	{ 0xa1, 0x7d, 0x14, 0x24}
	} ;

int P3[4][4] ={{0xf1, 0xf2,0xf3,0xf0 },
	{ 0x91, 0x5c, 0x41, 0xc7 } ,
	{0x06, 0x3a, 0x48, 0xe7},
	{ 0xa8, 0x1d, 0xa5, 0x3a}
	} ;

int P4[4][4] ={{0x34, 0x80,0x3a,0xe9 },
	{ 0xf3, 0x21, 0x31, 0x36 } ,
	{0x5e, 0x3d, 0x93, 0x57},
	{ 0x75, 0x19, 0x2a, 0x49}
	} ;

int P5[4][4] ={{0xe2, 0x18,0x33,0xe4 },
	{ 0x38, 0x9a, 0x2c, 0xff } ,
	{0x5e, 0x03, 0x89, 0x70},
	{ 0xa8, 0x8f, 0x12, 0x6a}
	} ;

int P6[4][4] ={{0x9f, 0xa8,0xb1,0x10 },
	{ 0x4b, 0x52, 0xd1, 0x13 } ,
	{0xb6, 0x3e, 0x07, 0xaa},
	{ 0xf0, 0x43, 0x22, 0x00}
	} ;

int P7[4][4] ={{0xa2, 0x91,0x76,0xe0 },
	{ 0x37, 0x31, 0x2b, 0xc3 } ,
	{0xcb, 0xfe, 0xa8, 0x0e},
	{ 0x08, 0x8d, 0xf2, 0x14}
	} ;

*/

int hextohex[16][16]=
{{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f},
 {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f},
 {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f},
 {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f},
 {0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f},
 {0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f},
 {0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f},
 {0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f},
 {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f},
 {0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f},
 {0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf},
 {0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf},
 {0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf},
 {0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf},
 {0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef},
 {0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff},
 
	
};


int toint( char c)
{
	switch(c)
	{
	   case '0': return 0;
	             break;
	   case '1': return 1;
	             break;  
		case '2': return 2;
	             break;	
		case '3': return 3;
	             break;	
		case '4': return 4;
	             break;	
		case '5': return 5;
	             break;
		case '6': return 6;
	             break;
		case '7': return 7;
	             break;
		case '8': return 8;
	             break;
		case '9': return 9;
	             break;
		case 'a': return 10;
	             break;
		case 'b': return 11;
	             break;
		case 'c': return 12;
	             break;
		case 'd': return 13;
	             break;
		case 'e': return 14;
	             break;
		case 'f': return 15;
	             break;
				 		 		 		 		 		 		 		 		 		 		 		 	 	 	        
	}
}
//PLAINTEXT STORE IN MATRIX

int P0[4][4]; int P1[4][4]; int P2[4][4]; int P3[4][4];
int P4[4][4]; int P5[4][4]; int P6[4][4]; int P7[4][4];
 unsigned char store1[900] = {0};
 int index1=0;
 int file_length;
 
 int Plaintext_store()
 {
 	int val=0;
 	   index1 =index1 +2;
 	if(index1<file_length){
 		cout<<"file length= \n"<<file_length;
	    if(index1 %2==0 )
	   {
	   	char a,b;
	    a= store1[index1];
	    b= store1[index1 +1];
	    int x= toint(a);
	    int y= toint(b);
	    cout<<"\nvalue= "<<hex<<hextohex[x][y];
	     val=hextohex[x][y];
	    
	    }
	}
	else 
	{
		 val=-1;
   }
    return val;
	
 }
 
void file_Plaintext()
{
 ifstream input_file;
    string input;
   input_file.open("output1.txt", ios::in | ios::binary);

    if (input_file.is_open())
    {
		 
		 for(int ind1 = 0; ind1<=7; ind1++)
                  {

					    getline(input_file, input); 
					    istringstream get_hex(input);
					    unsigned char plaintext;
					    int i2 = 0;
				            int k = 2;
					    
					    
					    while (get_hex >> hex >> plaintext)
					    {
			
						store1[i2] = plaintext; 
						i2= i2 + int(1);
				               
		
					    }
					    
					    cout<<"Reading Completed!!"<<endl;
					    cout<<"value of i2:-"<<std::dec<<i2<<endl;
				            file_length = i2;
				            
				              // cout<<"Stored Value!!"<<endl;
				            //  for(int k=0;k<i2;k++){
				             //  cout<<store[k];	}
				             
				             cout<<"store1: \n"<<store1;
				   
			    cout<<endl<<"<----Message Output Success----->!!"<<endl;    
               index1 =-2;
   
      // Key array P0 formation
 
	           if(ind1 == 0){
		             cout<<"In Array P0 Formation--->!!";
				    int flag=1;
			    

				    for(int i1=0;i1<4;i1++)

				    {

					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										P0[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								P0[i1][j1]=val;
							}	
						}

				    }

				    

				    cout<<"\n matrix P0: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<P0[i][j]<<" ";

					    cout<<endl;
				    }
				}  // Ind1 if ends                          
    
	// Key array P1 formation
 
	           if(ind1 == 1){
		             cout<<"In Array P1 Formation--->!!";
				    int flag=1;
			    
				    for(int i1=0;i1<4;i1++)

				    {
					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										P1[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								P1[i1][j1]=val;
							}	
						}
				    }
				    

				    cout<<"\n matrix P1: \n";
				    for(int i=0;i<4;i++)
				    {
					for(int j=0;j<4;j++)
					    cout<<uppercase<<hex<<P1[i][j]<<" ";
					    cout<<endl;
					
				    }
					   
		        
		        
                          }  // Ind1 if ends
           

// Key array P2 formation
 
	           if(ind1 == 2){
		             cout<<"In Array P2 Formation--->!!";
				    int flag=1;
			    

				    for(int i1=0;i1<4;i1++)

				    {

					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										P2[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								P2[i1][j1]=val;
							}	
						}

				    }

				    

				    cout<<"\n matrix P2: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<P2[i][j]<<" ";

					    cout<<endl;

					
				    }
					   
		        
		        
                          }  // Ind1 if ends
                          
// Key array P3 formation
 
	           if(ind1 == 3){
		             cout<<"In Array P3 Formation--->!!";
				    int flag=1;
			    

				    for(int i1=0;i1<4;i1++)

				    {

					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										P3[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								P3[i1][j1]=val;
							}	
						}

				    }

				    

				    cout<<"\n matrix P3: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<P3[i][j]<<" ";

					    cout<<endl;

					
				    }
					   
		        
		        
                          }  // Ind1 if ends

                          
// Key array P4 formation
 
	           if(ind1 == 4){
		             cout<<"In Array P4 Formation--->!!";
				    int flag=1;
			    

				    for(int i1=0;i1<4;i1++)

				    {

					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										P4[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								P4[i1][j1]=val;
							}	
						}

				    }

				    

				    cout<<"\n matrix P4: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<P4[i][j]<<" ";

					    cout<<endl;

					
				    }
					   
		        
		        
                          }  // Ind1 if ends

// Key array P5 formation
 
	           if(ind1 == 5){
		             cout<<"In Array P5 Formation--->!!";
				    int flag=1;
			    

				    for(int i1=0;i1<4;i1++)

				    {

					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										P5[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								P5[i1][j1]=val;
							}	
						}

				    }

				    

				    cout<<"\n matrix P5: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<P5[i][j]<<" ";

					    cout<<endl;

					
				    }
					   
		        
		        
                          }  // Ind1 if ends
                          
  // Key array P6 formation
 
	           if(ind1 == 6){
		             cout<<"In Array P6 Formation--->!!";
				    int flag=1;
			    

				    for(int i1=0;i1<4;i1++)

				    {

					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										P6[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								P6[i1][j1]=val;
							}	
						}

				    }

				    

				    cout<<"\n matrix P6: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<P6[i][j]<<" ";

					    cout<<endl;

					
				    }
					   
		        
		        
                          }  // Ind1 if ends
                        
// Key array P7 formation
 
	           if(ind1 == 7){
		             cout<<"In Array P7 Formation--->!!";
				    int flag=1;
			    

				    for(int i1=0;i1<4;i1++)

				    {

					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										P7[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								P7[i1][j1]=val;
							}	
						}

				    }

				    

				    cout<<"\n matrix P7: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<P7[i][j]<<" ";

					    cout<<endl;

					
				    }
					   
		        
		        
                          }  // Ind1 if ends
                          
                    }// for loop ends         
}//if ends
    
}


//ASSOCIATED DATA STORE IN MATRIX

int AD0[4][4]; int AD1[4][4]; int AD2[4][4]; int AD3[4][4];
int AD4[4][4]; int AD5[4][4]; int AD6[4][4]; int AD7[4][4];

void file_Associated_Data()
{
 ifstream input_file1;
    string input1;
   input_file1.open("output2.txt", ios::in | ios::binary);

    if (input_file1.is_open())
    {
		 
		 for(int ind1 = 0; ind1<=7; ind1++)
                  {

					    getline(input_file1, input1); 
					    istringstream get_hex(input1);
					    unsigned char plaintext;
					    int i2 = 0;
				            int k = 2;
					    
					    
					    while (get_hex >> hex >> plaintext)
					    {
			
						store1[i2] = plaintext; 
						i2= i2 + int(1);
				               
		
					    }
					    
					    cout<<"Reading Completed!!"<<endl;
					    cout<<"value of i2:-"<<std::dec<<i2<<endl;
				            file_length = i2;
				            
				              // cout<<"Stored Value!!"<<endl;
				            //  for(int k=0;k<i2;k++){
				             //  cout<<store[k];	}
				             
				             cout<<"store1: \n"<<store1;
				   
			    cout<<endl<<"<----Message Output Success----->!!"<<endl;    
               index1=-2;
   
      // Key array AD0 formation
 
	           if(ind1 == 0){
		             cout<<"In Array AD0 Formation--->!!";
				    int flag=1;
			    for(int i1=0;i1<4;i1++)

				    {
                       for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										AD0[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								AD0[i1][j1]=val;
							}	
						}

				    }
   
				    cout<<"\n matrix AD0: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<AD0[i][j]<<" ";

					    cout<<endl;
			
				    }
			}  // Ind1 if ends

// Key array AD1 formation
 
	           if(ind1 == 1){
		             cout<<"In Array AD1 Formation--->!!";
				    int flag=1;
			    
				    for(int i1=0;i1<4;i1++)

				    {
					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										AD1[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								AD1[i1][j1]=val;
							}	
						}
				    }
				    

				    cout<<"\n matrix AD1: \n";
				    for(int i=0;i<4;i++)
				    {
					for(int j=0;j<4;j++)
					    cout<<uppercase<<hex<<AD1[i][j]<<" ";
					    cout<<endl;
					
				    }		   
		        	        
                   }  // Ind1 if ends
           
// Key array AD2 formation
 
	           if(ind1 == 2){
		             cout<<"In Array AD2 Formation--->!!";
				    int flag=1;
			   for(int i1=0;i1<4;i1++)
                 {
				    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										AD2[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								AD2[i1][j1]=val;
							}	
						}

				    }
	    
				    cout<<"\n matrix AD2: \n";

				    for(int i=0;i<4;i++)

				    {
                       for(int j=0;j<4;j++)
					    cout<<uppercase<<hex<<AD2[i][j]<<" ";
					    cout<<endl;
		           }
					   
		        }  // Ind1 if ends
                          
// Key array AD3 formation
 
	           if(ind1 == 3){
		             cout<<"In Array AD3 Formation--->!!";
				    int flag=1;
			    for(int i1=0;i1<4;i1++)
				    {
				    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										AD3[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								AD3[i1][j1]=val;
							}	
						}

				    }
			    
				    cout<<"\n matrix AD3: \n";

				    for(int i=0;i<4;i++)

				    {

					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<AD3[i][j]<<" ";

					    cout<<endl;
				
				    }
				}  // Ind1 if ends

                          
// Key array AD4 formation
 
	           if(ind1 == 4){
		             cout<<"In Array AD4 Formation--->!!";
				    int flag=1;		    

				    for(int i1=0;i1<4;i1++)
				    {
					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										AD4[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								AD4[i1][j1]=val;
							}	
						}
				}
			    
				    cout<<"\n matrix AD4: \n";

				    for(int i=0;i<4;i++)
				    {
					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<AD4[i][j]<<" ";

					    cout<<endl;
					
				    }
				}  // Ind1 if ends

// Key array AD5 formation
 
	           if(ind1 == 5){
		             cout<<"In Array AD5 Formation--->!!";
				    int flag=1;
			    for(int i1=0;i1<4;i1++)

				    {

					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										AD5[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								AD5[i1][j1]=val;
							}	
						}

				    }

				    
				    cout<<"\n matrix AD5: \n";
				    for(int i=0;i<4;i++)
				    {
					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<AD5[i][j]<<" ";

					    cout<<endl;					
				    }
			}  // Ind1 if ends
                          
  // Key array AD6 formation
 
	           if(ind1 == 6){
		             cout<<"In Array AD6 Formation--->!!";
				    int flag=1;			    

				    for(int i1=0;i1<4;i1++)
				    {
					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										AD6[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								AD6[i1][j1]=val;
							}	
						}
				    }			    

				    cout<<"\n matrix AD6: \n";
				    for(int i=0;i<4;i++)
				    {
					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<AD6[i][j]<<" ";

					    cout<<endl;					
				    }    
		        
                }  // Ind1 if ends
                        
// Key array AD7 formation
 
	           if(ind1 == 7){
		             cout<<"In Array AD7 Formation--->!!";
				    int flag=1;  
				    for(int i1=0;i1<4;i1++)
				    {
					    for(int j1=0;j1<4;j1++)
						{
							if(flag){
							int val=Plaintext_store();
							cout<<"\nval in main= "<<val;
									if(val!=-1)
									{
										AD7[i1][j1]=val;
									}
									else if(val==-1)
									{
										flag=0;
									}
							       }
							else
							{
								int val= hextohex[0][0];
								AD7[i1][j1]=val;
							}	
						}
				    }				    

				    cout<<"\n matrix AD7: \n";

				    for(int i=0;i<4;i++)
				    {
					for(int j=0;j<4;j++)

					    cout<<uppercase<<hex<<AD7[i][j]<<" ";

					    cout<<endl;					
				    }   
		       }  // Ind1 if ends
                          
         }// for loop ends         
}//if ends
    
}


int allS[40][20];

void initialization()
{
	// initialize S0
	S0[0][0]= Key[0][0] ^ IV[0][0];
	S0[0][1]= Key[0][1] ^ IV[0][1];
	S0[0][2]= Key[0][2] ^ IV[0][2];
	S0[0][3]= Key[0][3] ^ IV[0][3];
	
    S0[1][0]= Key[1][0] ^ IV[1][0];
	S0[1][1]= Key[1][1] ^ IV[1][1];
	S0[1][2]= Key[1][2] ^ IV[1][2];
	S0[1][3]= Key[1][3] ^ IV[1][3];	
	
	S0[2][0]= Key[2][0] ^ IV[2][0];
	S0[2][1]= Key[2][1] ^ IV[2][1];
	S0[2][2]= Key[2][2] ^ IV[2][2];
	S0[2][3]= Key[2][3] ^ IV[2][3];
	
	S0[3][0]= Key[3][0] ^ IV[3][0];
	S0[3][1]= Key[3][1] ^ IV[3][1];
	S0[3][2]= Key[3][2] ^ IV[3][2];
	S0[3][3]= Key[3][3] ^ IV[3][3];
	
	// initialize S1
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
	S1[i][j]=C1[i][j];
	
	// initialize S2
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
	S2[i][j]=C0[i][j];

    // initialize S3
    S3[0][0]= Key[0][0] ^ C0[0][0];
    S3[0][1]= Key[0][1] ^ C0[0][1];
    S3[0][2]= Key[0][2] ^ C0[0][2];
    S3[0][2]= Key[0][3] ^ C0[0][3];
    
    S3[1][0]= Key[1][0] ^ C0[1][0];
    S3[1][1]= Key[1][1] ^ C0[1][1];
    S3[1][2]= Key[1][2] ^ C0[1][2];
    S3[1][2]= Key[1][3] ^ C0[1][3];

    S3[2][0]= Key[2][0] ^ C0[2][0];
    S3[2][1]= Key[2][1] ^ C0[2][1];
    S3[2][2]= Key[2][2] ^ C0[2][2];
    S3[2][2]= Key[2][3] ^ C0[2][3];

    S3[3][0]= Key[3][0] ^ C0[3][0];
    S3[3][1]= Key[3][1] ^ C0[3][1];
    S3[3][2]= Key[3][2] ^ C0[3][2];
    S3[3][2]= Key[3][3] ^ C0[3][3];

	// initialize S4
	S4[0][0]= Key[0][0] ^ C1[0][0];
	S4[0][1]= Key[0][1] ^ C1[0][1];
	S4[0][2]= Key[0][2] ^ C1[0][2];
	S4[0][3]= Key[0][3] ^ C1[0][3];
	  
	S4[1][0]= Key[1][0] ^ C1[1][0];
	S4[1][1]= Key[1][1] ^ C1[1][1];
	S4[1][2]= Key[1][2] ^ C1[1][2];
	S4[1][3]= Key[1][3] ^ C1[1][3];
	
	S4[2][0]= Key[2][0] ^ C1[2][0];
	S4[2][1]= Key[2][1] ^ C1[2][1];
	S4[2][2]= Key[2][2] ^ C1[2][2];
	S4[2][3]= Key[2][3] ^ C1[2][3];
	
	S4[3][0]= Key[3][0] ^ C1[3][0];
	S4[3][1]= Key[3][1] ^ C1[3][1];
	S4[3][2]= Key[3][2] ^ C1[3][2];
	S4[3][3]= Key[3][3] ^ C1[3][3];  
	  
}

int row=0;
void stateupdate(int M[4][4])
{

	int i,j,r=0, c=0,col=0;
	//convert S4 to R(S4)
	for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	state[i][j]=S4[i][j];
    }
    }
    
    Aes();
    
    //updated state matrix R(s4)
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	S4[i][j]=state[i][j];
    }
    }
    
	//1st stage
	for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	state[i][j]=S0[i][j];
    }
    }
	
	
    Aes();
   
	//update si,0 to si+1,0
	for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	S0[i][j] ^= M[i][j];
	S0[i][j] ^=S4[i][j] ;
    }
    }
    
    r=row;
    col=c;
    cout<<"\n si+1,0\n";
    for( i=0;i<4;i++){
      c=col;
	for( j=0;j<4;j++){
	cout<<hex<<S0[i][j]<<" ";
	//allS[r][c++]=S0[i][j];
    }
    r=r+1;
    cout<<endl;
    }
   
    
	
    int temp[4][4];
	cout<<"\n store updated state matrix to temp matrix for 2nd stage\n";
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	temp[i][j]=state[i][j];
	cout<<hex<<temp[i][j]<<" ";
    }
    cout<<endl;
    }
    
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	state[i][j]=S1[i][j];
	//cout<<hex<<temp[i][j]<<" ";
    }
    cout<<endl;
    }
    
    Aes();
    
    //update si,1 to si+1,1 
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	S1[i][j] ^= temp[i][j];
    }
    }
    
    r=row;
    col=c;
    cout<<"\n si+1,1\n";
    for( i=0;i<4;i++){
      c=col;
	for( j=0;j<4;j++){
	cout<<hex<<S1[i][j]<<" ";
	//allS[r][c++]=S1[i][j];
    }
    r=r+1;
    cout<<endl;
    }
	
	
	//3rd stage
	cout<<"\n store updated state matrix to temp matrix for 3rd stage\n";
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	temp[i][j]=state[i][j];
	cout<<hex<<temp[i][j]<<" ";
    }
    cout<<endl;
    }
    
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	state[i][j]=S2[i][j];
  //	cout<<hex<<temp[i][j]<<" ";
    }
    cout<<endl;
    }
    
    Aes();
    
    //update si,2 to si+1,2 
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	S2[i][j] ^= temp[i][j];
    }
    }
    
    r=row;
    col=c;
    cout<<"\n si+1,2\n";
    for( i=0;i<4;i++){
      c=col;
	for( j=0;j<4;j++){
	cout<<hex<<S2[i][j]<<" ";
	///allS[r][c++]=S2[i][j];
    }
    r=r+1;
    cout<<endl;
    }
    
    //4th stage
    cout<<"\n store updated state matrix to temp matrix for 4th stage\n";
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	temp[i][j]=state[i][j];
	cout<<hex<<temp[i][j]<<" ";
    }
    cout<<endl;
    }
    
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	state[i][j]=S3[i][j];
	//cout<<hex<<temp[i][j]<<" ";
    }
    cout<<endl;
    }
    
    Aes();
    
    //update si,3 to si+1,3 
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	S3[i][j] ^= temp[i][j];
    }
    }
    
    r=row;
    col=c;
    cout<<"\n si+1,3\n";
    for( i=0;i<4;i++){
      c=col;
	for( j=0;j<4;j++){
	cout<<hex<<S3[i][j]<<" ";
	//allS[r][c++]=S3[i][j];
    }
    r=r+1;
    cout<<endl;
    }
    
    //5th stage
    cout<<"\n store updated state matrix to temp matrix for 5th stage\n";
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	temp[i][j]=state[i][j];
	cout<<hex<<temp[i][j]<<" ";
    }
    cout<<endl;
    }
    
    
    //update si,4 to si+1,4 
    for( i=0;i<4;i++){
	for( j=0;j<4;j++){
	S4[i][j] ^= temp[i][j];
    }
    }
    
    r=row;
    col=c;
    cout<<"\n si+1,4\n";
    for( i=0;i<4;i++){
      c=col;
	for( j=0;j<4;j++){
	cout<<hex<<S4[i][j]<<" ";
	///allS[r][c++]=S4[i][j];
    }
    r=r+1;
    cout<<endl;
    }
    
    row=r;
}

void Authintication()
{
	
	stateupdate(AD0);
	stateupdate(AD1);
	stateupdate(AD2);
	stateupdate(AD3);
	stateupdate(AD4);
	stateupdate(AD5);
	stateupdate(AD6);
	stateupdate(AD7);
}

int US1[32][4]={0};
int US2[32][4]={0};
int US3[32][4]={0};
int US4[32][4]={0};
int j=0;
void store()
{
	int i;
	for(i=0;i<4;i++)
	{
	US1[i+j][0]=S1[i][0];
	US1[i+j][1]=S1[i][1];
	US1[i+j][2]=S1[i][2];
	US1[i+j][3]=S1[i][3];
	
	US2[i+j][0]=S2[i][0];
	US2[i+j][1]=S2[i][1];
	US2[i+j][2]=S2[i][2];
	US2[i+j][3]=S2[i][3];
	
	US3[i+j][0]=S3[i][0];
	US3[i+j][1]=S3[i][1];
	US3[i+j][2]=S3[i][2];
	US3[i+j][3]=S3[i][3];
	
	US4[i+j][0]=S4[i][0];
	US4[i+j][1]=S4[i][1];
	US4[i+j][2]=S4[i][2];
	US4[i+j][3]=S4[i][3];
    }
    
	j=j+4;
}

int C[32][4];
void Encrypt()
{
	   
        store();
		C[0][0]= (((P0[0][0]^ S1[0][0])^ S4[0][0])^ (S2[0][0]&S3[0][0] ));
		C[0][1]= (((P0[0][1]^ S1[0][1]) ^ S4[0][1]) ^ (S2[0][1]&S3[0][1]) );
		C[0][2]= (((P0[0][2]^ S1[0][2]) ^ S4[0][2]) ^ (S2[0][2]&S3[0][2] ));
		C[0][3]= (((P0[0][3]^ S1[0][3]) ^ S4[0][3] )^ (S2[0][3]&S3[0][3] ));
		
		C[1][0]= (((P0[1][0]^ S1[1][0] )^ S4[1][0] )^ (S2[1][0]&S3[1][0] ));
		C[1][1]= (((P0[1][1]^ S1[1][1] )^ S4[1][1] )^ (S2[1][1]&S3[1][1] ));
		C[1][2]= (((P0[1][2]^ S1[1][2]) ^ S4[1][2] )^ (S2[1][2]&S3[1][2] ));
		C[1][3]= (((P0[1][3]^ S1[1][3]) ^ S4[1][3] )^ (S2[1][3]&S3[1][3] ));
		
		C[2][0]= (((P0[2][0]^ S1[2][0]) ^ S4[2][0]) ^ (S2[2][0]&S3[2][0] ));
		C[2][1]= (((P0[2][1]^ S1[2][1])^ S4[2][1] )^ (S2[2][1]&S3[2][1] ));
		C[2][2]= (((P0[2][2]^ S1[2][2])^ S4[2][2]) ^ (S2[2][2]&S3[2][2]) );
		C[2][3]= (((P0[2][3]^ S1[2][3])^ S4[2][3])^ (S2[2][3]&S3[2][3] ));
		
		C[3][0]= (((P0[3][0]^ S1[3][0] )^ S4[3][0] )^ (S2[3][0]&S3[3][0] ));
		C[3][1]= (((P0[3][1]^ S1[3][1] )^ S4[3][1] )^ (S2[3][1]&S3[3][1] ));
		C[3][2]= (((P0[3][2]^ S1[3][2] )^ S4[3][2] )^ (S2[3][2]&S3[3][2] ));
		C[3][3]= (((P0[3][3]^ S1[3][3] )^ S4[3][3] )^ (S2[3][3]&S3[3][3] ));
		
		int i,j;
		cout<<"\n in encrypt s1 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S1[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s2 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S2[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s3 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S3[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s4 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S4[i][j]<<" ";
			cout<<endl;
		}
		
	 stateupdate(P0);
	
	store();  
	
		C[4][0]= (((P1[0][0]^ S1[0][0])^ S4[0][0])^ (S2[0][0]&S3[0][0] ));
		C[4][1]= (((P1[0][1]^ S1[0][1]) ^ S4[0][1]) ^ (S2[0][1]&S3[0][1]) );
		C[4][2]= (((P1[0][2]^ S1[0][2]) ^ S4[0][2]) ^ (S2[0][2]&S3[0][2] ));
		C[4][3]= (((P1[0][3]^ S1[0][3]) ^ S4[0][3] )^ (S2[0][3]&S3[0][3] ));
		
		C[5][0]= (((P1[1][0]^ S1[1][0] )^ S4[1][0] )^ (S2[1][0]&S3[1][0] ));
		C[5][1]= (((P1[1][1]^ S1[1][1] )^ S4[1][1] )^ (S2[1][1]&S3[1][1] ));
		C[5][2]= (((P1[1][2]^ S1[1][2]) ^ S4[1][2] )^ (S2[1][2]&S3[1][2] ));
		C[5][3]= (((P1[1][3]^ S1[1][3]) ^ S4[1][3] )^ (S2[1][3] &S3[1][3] ));
		
		C[6][0]= (((P1[2][0]^ S1[2][0]) ^ S4[2][0]) ^ (S2[2][0] & S3[2][0] ));
		C[6][1]= (((P1[2][1]^ S1[2][1])^ S4[2][1] )^ (S2[2][1] & S3[2][1] ));
		C[6][2]= (((P1[2][2]^ S1[2][2])^ S4[2][2]) ^ (S2[2][2] & S3[2][2]) );
		C[6][3]= (((P1[2][3]^ S1[2][3])^ S4[2][3])^ (S2[2][3] & S3[2][3] ));
		
		C[7][0]= (((P1[3][0]^ S1[3][0] )^ S4[3][0] )^ (S2[3][0] & S3[3][0] ));
		C[7][1]= (((P1[3][1]^ S1[3][1] )^ S4[3][1] )^ (S2[3][1] & S3[3][1] ));
		C[7][2]= (((P1[3][2]^ S1[3][2] )^ S4[3][2] )^ (S2[3][2] & S3[3][2] ));
		C[7][3]= (((P1[3][3]^ S1[3][3] )^ S4[3][3] )^ (S2[3][3] & S3[3][3] ));
		
	
	cout<<"\n in encrypt s1 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S1[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s2 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S2[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s3 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S3[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s4 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S4[i][j]<<" ";
			cout<<endl;
		}
	
	   stateupdate(P1);
    store();
	  	C[8][0]= (((P2[0][0]^ S1[0][0])^ S4[0][0])^    (S2[0][0] & S3[0][0] ));
		C[8][1]= (((P2[0][1]^ S1[0][1]) ^ S4[0][1]) ^ (S2[0][1] & S3[0][1]) );
		C[8][2]= (((P2[0][2]^ S1[0][2]) ^ S4[0][2]) ^ (S2[0][2] & S3[0][2] ));
		C[8][3]= (((P2[0][3]^ S1[0][3]) ^ S4[0][3] )^ (S2[0][3] & S3[0][3] ));
		
		C[9][0]= (((P2[1][0]^ S1[1][0] )^ S4[1][0] )^ (S2[1][0] & S3[1][0] ));
		C[9][1]= (((P2[1][1]^ S1[1][1] )^ S4[1][1] )^ (S2[1][1] & S3[1][1] ));
		C[9][2]= (((P2[1][2]^ S1[1][2]) ^ S4[1][2] )^ (S2[1][2] & S3[1][2] ));
		C[9][3]= (((P2[1][3]^ S1[1][3]) ^ S4[1][3] )^ (S2[1][3] &S3[1][3] ));
		
		C[10][0]= (((P2[2][0]^ S1[2][0]) ^ S4[2][0]) ^ (S2[2][0] & S3[2][0] ));
		C[10][1]= (((P2[2][1]^ S1[2][1])^ S4[2][1] )^ (S2[2][1] & S3[2][1] ));
		C[10][2]= (((P2[2][2]^ S1[2][2])^ S4[2][2]) ^ (S2[2][2] & S3[2][2]) );
		C[10][3]= (((P2[2][3]^ S1[2][3])^ S4[2][3])^ (S2[2][3] &S3[2][3] ));
		
		C[11][0]= (((P2[3][0]^ S1[3][0] )^ S4[3][0] )^ (S2[3][0] & S3[3][0] ));
		C[11][1]= (((P2[3][1]^ S1[3][1] )^ S4[3][1] )^ (S2[3][1] & S3[3][1] ));
		C[11][2]= (((P2[3][2]^ S1[3][2] )^ S4[3][2] )^ (S2[3][2] & S3[3][2] ));
		C[11][3]= (((P2[3][3]^ S1[3][3] )^ S4[3][3] )^ (S2[3][3] & S3[3][3] ));
		
		
		cout<<"\n in encrypt s1 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S1[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s2 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S2[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s3 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S3[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s4 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S4[i][j]<<" ";
			cout<<endl;
		}
		
		
	   stateupdate(P2);
    store();
	   	C[12][0]= (((P3[0][0]^ S1[0][0])^ S4[0][0])^ (S2[0][0] & S3[0][0] ));
		C[12][1]= (((P3[0][1]^ S1[0][1]) ^ S4[0][1]) ^ (S2[0][1] & S3[0][1]) );
		C[12][2]= (((P3[0][2]^ S1[0][2]) ^ S4[0][2]) ^ (S2[0][2] & S3[0][2] ));
		C[12][3]= (((P3[0][3]^ S1[0][3]) ^ S4[0][3] )^ (S2[0][3] & S3[0][3] ));
		
		C[13][0]= (((P3[1][0]^ S1[1][0] )^ S4[1][0] )^ (S2[1][0] & S3[1][0] ));
		C[13][1]= (((P3[1][1]^ S1[1][1] )^ S4[1][1] )^ (S2[1][1] & S3[1][1] ));
		C[13][2]= (((P3[1][2]^ S1[1][2]) ^ S4[1][2] )^ (S2[1][2] & S3[1][2] ));
		C[13][3]= (((P3[1][3]^ S1[1][3]) ^ S4[1][3] )^ (S2[1][3] & S3[1][3] ));
		
		C[14][0]= (((P3[2][0]^ S1[2][0]) ^ S4[2][0]) ^ (S2[2][0] & S3[2][0] ));
		C[14][1]= (((P3[2][1]^ S1[2][1])^ S4[2][1] )^ (S2[2][1] & S3[2][1] ));
		C[14][2]= (((P3[2][2]^ S1[2][2])^ S4[2][2]) ^ (S2[2][2] & S3[2][2]) );
		C[14][3]= (((P3[2][3]^ S1[2][3])^ S4[2][3])^ (S2[2][3] & S3[2][3] ));
		
		C[15][0]= (((P3[3][0]^ S1[3][0] )^ S4[3][0] )^ (S2[3][0] & S3[3][0] ));
		C[15][1]= (((P3[3][1]^ S1[3][1] )^ S4[3][1] )^ (S2[3][1] & S3[3][1] ));
		C[15][2]= (((P3[3][2]^ S1[3][2] )^ S4[3][2] )^ (S2[3][2] & S3[3][2] ));
		C[15][3]= (((P3[3][3]^ S1[3][3] )^ S4[3][3] )^ (S2[3][3] & S3[3][3] ));
		
		
		cout<<"\n in encrypt s1 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S1[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s2 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S2[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s3 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S3[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s4 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S4[i][j]<<" ";
			cout<<endl;
		}
	
	   stateupdate(P3);
	store();   
	    C[16][0]= (((P4[0][0]^ S1[0][0])^ S4[0][0])^   (S2[0][0] & S3[0][0] ));
		C[16][1]= (((P4[0][1]^ S1[0][1]) ^ S4[0][1]) ^ (S2[0][1] & S3[0][1]) );
		C[16][2]= (((P4[0][2]^ S1[0][2]) ^ S4[0][2]) ^ (S2[0][2] & S3[0][2] ));
		C[16][3]= (((P4[0][3]^ S1[0][3]) ^ S4[0][3] )^ (S2[0][3] & S3[0][3] ));
		
		C[17][0]= (((P4[1][0]^ S1[1][0] )^ S4[1][0] )^ (S2[1][0] & S3[1][0] ));
		C[17][1]= (((P4[1][1]^ S1[1][1] )^ S4[1][1] )^ (S2[1][1] & S3[1][1] ));
		C[17][2]= (((P4[1][2]^ S1[1][2]) ^ S4[1][2] )^ (S2[1][2] & S3[1][2] ));
		C[17][3]= (((P4[1][3]^ S1[1][3]) ^ S4[1][3] )^ (S2[1][3] & S3[1][3] ));
		
		C[18][0]= (((P4[2][0]^ S1[2][0]) ^ S4[2][0]) ^ (S2[2][0] & S3[2][0] ));
		C[18][1]= (((P4[2][1]^ S1[2][1])^ S4[2][1] )^ (S2[2][1] & S3[2][1] ));
		C[18][2]= (((P4[2][2]^ S1[2][2])^ S4[2][2]) ^ (S2[2][2] & S3[2][2]) );
		C[18][3]= (((P4[2][3]^ S1[2][3])^ S4[2][3])^ (S2[2][3] & S3[2][3] ));
		
		C[19][0]= (((P4[3][0]^ S1[3][0] )^ S4[3][0] )^ (S2[3][0] & S3[3][0] ));
		C[19][1]= (((P4[3][1]^ S1[3][1] )^ S4[3][1] )^ (S2[3][1] & S3[3][1] ));
		C[19][2]= (((P4[3][2]^ S1[3][2] )^ S4[3][2] )^ (S2[3][2] & S3[3][2] ));
		C[19][3]= (((P4[3][3]^ S1[3][3] )^ S4[3][3] )^ (S2[3][3] & S3[3][3] ));
		
	     cout<<"\n in encrypt s1 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S1[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s2 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S2[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s3 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S3[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s4 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S4[i][j]<<" ";
			cout<<endl;
		}
	     
	   stateupdate(P4);
    store();
        C[20][0]= (((P5[0][0]^ S1[0][0])^ S4[0][0])^ (S2[0][0] & S3[0][0] ));
		C[20][1]= (((P5[0][1]^ S1[0][1]) ^ S4[0][1]) ^ (S2[0][1] & S3[0][1]) );
		C[20][2]= (((P5[0][2]^ S1[0][2]) ^ S4[0][2]) ^ (S2[0][2] & S3[0][2] ));
		C[20][3]= (((P5[0][3]^ S1[0][3]) ^ S4[0][3] )^ (S2[0][3] & S3[0][3] ));
		
		C[21][0]= (((P5[1][0]^ S1[1][0] )^ S4[1][0] )^ (S2[1][0] & S3[1][0] ));
		C[21][1]= (((P5[1][1]^ S1[1][1] )^ S4[1][1] )^ (S2[1][1] & S3[1][1] ));
		C[21][2]= (((P5[1][2]^ S1[1][2]) ^ S4[1][2] )^ (S2[1][2] & S3[1][2] ));
		C[21][3]= (((P5[1][3]^ S1[1][3]) ^ S4[1][3] )^ (S2[1][3] & S3[1][3] ));
		
		C[22][0]= (((P5[2][0]^ S1[2][0]) ^ S4[2][0]) ^ (S2[2][0] & S3[2][0] ));
		C[22][1]= (((P5[2][1]^ S1[2][1])^ S4[2][1] )^ (S2[2][1] &S3[2][1] ));
		C[22][2]= (((P5[2][2]^ S1[2][2])^ S4[2][2]) ^ (S2[2][2] & S3[2][2]) );
		C[22][3]= (((P5[2][3]^ S1[2][3])^ S4[2][3])^ (S2[2][3] & S3[2][3] ));
		
		C[23][0]= (((P5[3][0]^ S1[3][0] )^ S4[3][0] )^ (S2[3][0] & S3[3][0] ));
		C[23][1]= (((P5[3][1]^ S1[3][1] )^ S4[3][1] )^ (S2[3][1] & S3[3][1] ));
		C[23][2]= (((P5[3][2]^ S1[3][2] )^ S4[3][2] )^ (S2[3][2] & S3[3][2] ));
		C[23][3]= (((P5[3][3]^ S1[3][3] )^ S4[3][3] )^ (S2[3][3] & S3[3][3] ));
		
	     cout<<"\n in encrypt s1 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S1[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s2 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S2[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s3 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S3[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s4 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S4[i][j]<<" ";
			cout<<endl;
		}
	
	
	   stateupdate(P5);
    store();
        C[24][0]= (((P6[0][0]^ S1[0][0])^ S4[0][0])^ (S2[0][0] & S3[0][0] ));
		C[24][1]= (((P6[0][1]^ S1[0][1]) ^ S4[0][1]) ^ (S2[0][1] & S3[0][1]) );
		C[24][2]= (((P6[0][2]^ S1[0][2]) ^ S4[0][2]) ^ (S2[0][2] & S3[0][2] ));
		C[24][3]= (((P6[0][3]^ S1[0][3]) ^ S4[0][3] )^ (S2[0][3] & S3[0][3] ));
		
		C[25][0]= (((P6[1][0]^ S1[1][0] )^ S4[1][0] )^ (S2[1][0] & S3[1][0] ));
		C[25][1]= (((P6[1][1]^ S1[1][1] )^ S4[1][1] )^ (S2[1][1] & S3[1][1] ));
		C[25][2]= (((P6[1][2]^ S1[1][2]) ^ S4[1][2] )^ (S2[1][2] & S3[1][2] ));
		C[25][3]= (((P6[1][3]^ S1[1][3]) ^ S4[1][3] )^ (S2[1][3] & S3[1][3] ));
	
		C[26][0]= (((P6[2][0]^ S1[2][0]) ^ S4[2][0]) ^ (S2[2][0] & S3[2][0] ));
		C[26][1]= (((P6[2][1]^ S1[2][1])^ S4[2][1] )^ (S2[2][1] & S3[2][1] ));
		C[26][2]= (((P6[2][2]^ S1[2][2])^ S4[2][2]) ^ (S2[2][2] & S3[2][2]) );
		C[26][3]= (((P6[2][3]^ S1[2][3])^ S4[2][3])^ (S2[2][3] &S3[2][3] ));
		
		C[27][0]= (((P6[3][0]^ S1[3][0] )^ S4[3][0] )^ (S2[3][0] & S3[3][0] ));
		C[27][1]= (((P6[3][1]^ S1[3][1] )^ S4[3][1] )^ (S2[3][1] & S3[3][1] ));
		C[27][2]= (((P6[3][2]^ S1[3][2] )^ S4[3][2] )^ (S2[3][2] & S3[3][2] ));
		C[27][3]= (((P6[3][3]^ S1[3][3] )^ S4[3][3] )^ (S2[3][3] & S3[3][3] ));
		

       cout<<"\n in encrypt s1 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S1[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s2 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S2[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s3 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S3[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s4 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S4[i][j]<<" ";
			cout<<endl;
		}

	   stateupdate(P6);
	store();   
	   C[28][0]= (((P7[0][0]^ S1[0][0])^ S4[0][0])^ (S2[0][0] & S3[0][0] ));
		C[28][1]= (((P7[0][1]^ S1[0][1]) ^ S4[0][1]) ^ (S2[0][1] & S3[0][1]) );
		C[28][2]= (((P7[0][2]^ S1[0][2]) ^ S4[0][2]) ^ (S2[0][2] & S3[0][2] ));
		C[28][3]= (((P7[0][3]^ S1[0][3]) ^ S4[0][3] )^ (S2[0][3] & S3[0][3] ));
		
		C[29][0]= (((P7[1][0]^ S1[1][0] )^ S4[1][0] )^ (S2[1][0] & S3[1][0] ));
		C[29][1]= (((P7[1][1]^ S1[1][1] )^ S4[1][1] )^ (S2[1][1] & S3[1][1] ));
		C[29][2]= (((P7[1][2]^ S1[1][2]) ^ S4[1][2] )^ (S2[1][2] & S3[1][2] ));
		C[29][3]= (((P7[1][3]^ S1[1][3]) ^ S4[1][3] )^ (S2[1][3] & S3[1][3] ));
		
		C[30][0]= (((P7[2][0]^ S1[2][0]) ^ S4[2][0]) ^ (S2[2][0] & S3[2][0] ));
		C[30][1]= (((P7[2][1]^ S1[2][1])^ S4[2][1] )^ (S2[2][1] & S3[2][1] ));
		C[30][2]= (((P7[2][2]^ S1[2][2])^ S4[2][2]) ^ (S2[2][2] & S3[2][2]) );
		C[30][3]= (((P7[2][3]^ S1[2][3])^ S4[2][3])^ (S2[2][3] & S3[2][3] ));
		
		C[31][0]= (((P7[3][0]^ S1[3][0] )^ S4[3][0] )^ (S2[3][0]& S3[3][0] ));
		C[31][1]= (((P7[3][1]^ S1[3][1] )^ S4[3][1] )^ (S2[3][1] & S3[3][1] ));
		C[31][2]= (((P7[3][2]^ S1[3][2] )^ S4[3][2] )^ (S2[3][2] & S3[3][2] ));
		C[31][3]= (((P7[3][3]^ S1[3][3] )^ S4[3][3] )^ (S2[3][3] & S3[3][3] ));


         cout<<"\n in encrypt s1 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S1[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s2 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S2[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s3 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S3[i][j]<<" ";
			cout<<endl;
		}
		cout<<"\n in encrypt s4 print\n";
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			cout<<hex<<S4[i][j]<<" ";
			cout<<endl;
		}
        stateupdate(P7);
	   
	   cout<<"\n ----------US1---------------\n";
       for(i=0;i<32;i++)
       {
       	for(j=0;j<4;j++)
       	cout<<hex<<US1[i][j]<<" ";
       	cout<<endl;
	   }
	   cout<<"\n ----------US2---------------\n";
	    for(i=0;i<32;i++)
       {
       	for(j=0;j<4;j++)
       	cout<<hex<<US2[i][j]<<" ";
       	cout<<endl;
	   }
	    cout<<"\n ----------US3---------------\n";
	    for(i=0;i<32;i++)
       {
       	for(j=0;j<4;j++)
       	cout<<hex<<US3[i][j]<<" ";
       	cout<<endl;
	   }
	   cout<<"\n ----------US4---------------\n";
	   for(i=0;i<32;i++)
       {
       	for(j=0;j<4;j++)
       	cout<<hex<<US4[i][j]<<" ";
       	cout<<endl;
	   }
	    
}

int tmp[4][4]={0};
int AdMg[4][4]={{0x00,0x00,0x00,0x00 },
                {0x00,0x00,0x04,0x00 },
				{0x00,0x00,0x00,0x00 },
				{0x00,0x00,0x04,0x00 }    
				};

int Tag[4][4]={0};

void tag_generation()
{
	int i;
	//printf("\n tmp starts\n");
	for(i=0;i<4;i++)
	{
		tmp[i][0]=S3[i][0] ^ AdMg[i][0] ; 
		tmp[i][1]=S3[i][1] ^ AdMg[i][1] ;
		tmp[i][2]=S3[i][2] ^ AdMg[i][2] ;
		tmp[i][3]=S3[i][3] ^ AdMg[i][3] ;
		
	}
	//printf("\n state up starts\n******************************************************************************************************************************************");
	for(i=0;i<6;i++)
	{
		stateupdate(tmp);  ///S 128 bit 4*4 matrix
	}
	
	//printf("\n tag starts\n");
	for(i=0;i<4;i++)
	{
		Tag[i][0]=S0[i][0] ^ S1[i][0] ^ S2[i][0] ^ S3[i][0] ^ S4[i][0] ; 
		Tag[i][1]=S0[i][1] ^ S1[i][2] ^ S2[i][1] ^ S3[i][1] ^ S4[i][1] ;
		Tag[i][2]=S0[i][2] ^ S1[i][3] ^ S2[i][2] ^ S3[i][2] ^ S4[i][2] ;
		Tag[i][3]=S0[i][3] ^ S1[i][4] ^ S2[i][3] ^ S3[i][3] ^ S4[i][3] ;
		
	}
	//printf("\n tag ends\n");
	
}

int res[32][4]={0};
void decryption()
{
	int i;
	for(i=0;i<32;i++)
	{
        res[i][0]= (((C[i][0]^ US1[i][0]) ^ US4[i][0]) ^ (US2[i][0] & US3[i][0] ));
	    res[i][1]= (((C[i][1]^ US1[i][1]) ^ US4[i][1]) ^ (US2[i][1] & US3[i][1] ));
		res[i][2]= (((C[i][2]^ US1[i][2]) ^ US4[i][2]) ^ (US2[i][2] & US3[i][2] ));
		res[i][3]= (((C[i][3]^ US1[i][3]) ^ US4[i][3]) ^ (US2[i][3] & US3[i][3] ));
    }
		
}

int Tagv[4][4]={0};
int verification()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		Tagv[i][0]=S0[i][0] ^ S1[i][0] ^ S2[i][0] ^ S3[i][0] ^ S4[i][0] ; 
		Tagv[i][1]=S0[i][1] ^ S1[i][2] ^ S2[i][1] ^ S3[i][1] ^ S4[i][1] ;
		Tagv[i][2]=S0[i][2] ^ S1[i][3] ^ S2[i][2] ^ S3[i][2] ^ S4[i][2] ;
		Tagv[i][3]=S0[i][3] ^ S1[i][4] ^ S2[i][3] ^ S3[i][3] ^ S4[i][3] ;
		
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(Tag[i][j]!= Tagv[i][j])
			return 0;
		}
		
	}
	return 1;
}


int main()
{
	file_Plaintext();
	file_Associated_Data();
	
    initialization();
	
	//checkmatrix(P0);
	int i,j;
	cout<<"\nS0\n";
	for( i=0;i<4;i++){
	for( j=0;j<4;j++)
	cout<<hex<<S0[i][j]<<" ";
	cout<<endl;
    }

cout<<"\nS1\n";
	for(i=0;i<4;i++){
	for( j=0;j<4;j++)
	cout<<hex<<S1[i][j]<<" ";
	cout<<endl;
}

cout<<"\nS2\n";
	for( i=0;i<4;i++){
	for( j=0;j<4;j++)
	cout<<hex<<S2[i][j]<<" ";
	cout<<endl;
}

cout<<"\nS3\n";
	for( i=0;i<4;i++){
	for(j=0;j<4;j++)
	cout<<hex<<S3[i][j]<<" ";
	cout<<endl;
}

cout<<"\nS4\n";
	for( i=0;i<4;i++){
	for( j=0;j<4;j++)
	cout<<hex<<S4[i][j]<<" ";
	cout<<endl;
}

//Meven = m2i
for( i=0;i<4;i++){
	for( j=0;j<4;j++)
	Meven[i][j]=Key[i][j];
	}
//Modd = m2i+1
for( i=0;i<4;i++){
	for( j=0;j<4;j++)
	Modd[i][j]=S0[i][j];
	}
	
   for(i=1;i<=10;i++)
   {
   	if(i%2==1)
   	stateupdate(Modd);
   	else if(i%2==0)
   	stateupdate(Meven);
   }
/*
cout<<"\n AllS: \n";	
for( i=0;i<40;i++){
	for( j=0;j<20;j++)
	cout<<allS[i][j]<<" ";
	cout<<endl;
	}
*/	
	
// Authinticated data


cout<<"\n AUTHENTICATION STARTS: ***********************************************************\n ";

Authintication();

cout<<"\n AUTHENTICATION ENDS: **************************************************************\n ";



//Encryption
cout<<"\n ENCRYPTION STARTS: ******************************************************************\n ";
Encrypt();
cout<<"\n encrypted plaintext: \n";	
for( i=0;i<32;i++){
	for( j=0;j<4;j++)
	cout<<C[i][j]<<" ";
	cout<<endl;
	if(i==3 || i==7 || i==11 || i==15 || i==19 || i==23 || i==27 || i==31 )
	cout<<endl;
	}
	
cout<<"\n ENCRYPTION ENDS: ********************************************************************\n ";	
// tag_generation
cout<<"\n TAG_GENERATION STARTS: ***************************************************************\n ";
tag_generation();
cout<<"\n After Tag generation: \n";	
for( i=0;i<4;i++){
	for( j=0;j<4;j++)
	cout<<Tag[i][j]<<" ";
	cout<<endl;
	}	
	
cout<<"\n TAG_GENERATION ENDS: ******************************************************************\n ";

cout<<"\n VERIFICATION STARTS: ******************************************************************\n ";
int v=verification();
if(v)
{

cout<<"VERIFIED\n";



cout<<"\n DECRYPTION STARTS: ******************************************************************\n ";
decryption();
cout<<"\n After decryption: \n";
for( i=0;i<32;i++){
	for( j=0;j<4;j++)
	cout<<res[i][j]<<" ";
	cout<<endl;
	if(i==3 || i==7 || i==11 || i==15 || i==19 || i==23 || i==27 || i==31 )
	cout<<endl;
	}
	
cout<<"\n DECRYPTION ENDS: ******************************************************************\n ";
}
else
cout<<"NOT VERIFIED\n";

cout<<"\n VERIFICATION ENDS: ******************************************************************\n ";
	
}

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


void substitue()
{int i,j;	
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


	
void Aes()
{

	int i,j;
substitue();	
shiftrow();
Mixcolumn();
}

