#include <serial.h>
//#include "math.h"
#include "string.h"
#include "stdlib.h"

#include "jz4770.h"
#include "jz4770efuse.h"

//extern unsigned char Sbox[256];
//extern unsigned char InvSbox[256];
//extern unsigned char w[11][4][4];

unsigned char w[11][4][4];

unsigned char Sbox[] =
{ /*  0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f */ 
		0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76, /*0*/  
		0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0, /*1*/
		0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15, /*2*/ 
		0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75, /*3*/ 
		0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84, /*4*/ 
		0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf, /*5*/
		0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8, /*6*/  
		0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2, /*7*/ 
		0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73, /*8*/ 
		0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb, /*9*/ 
		0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79, /*a*/
		0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08, /*b*/
		0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a, /*c*/ 
		0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e, /*d*/
		0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf, /*e*/ 
		0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16  /*f*/
};

unsigned char InvSbox[256] = 
{ /*  0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f  */  
		0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb, /*0*/ 
		0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb, /*1*/
		0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e, /*2*/ 
		0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25, /*3*/ 
		0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92, /*4*/ 
		0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84, /*5*/ 
		0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06, /*6*/ 
		0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b, /*7*/
		0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73, /*8*/ 
		0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e, /*9*/
		0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b, /*a*/
		0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4, /*b*/ 
		0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f, /*c*/ 
		0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef, /*d*/ 
		0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61, /*e*/ 
		0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d  /*f*/
}; 

static unsigned char FFmul(unsigned char a, unsigned char b)
{
	unsigned char bw[4];
	unsigned char res=0;
	int i;
	bw[0] = b;
	for(i=1; i<4; i++)
	{
		bw[i] = bw[i-1]<<1;
		if(bw[i-1]&0x80)
		{
			bw[i]^=0x1b;
		}
	}
	for(i=0; i<4; i++)
	{
		if((a>>i)&0x01)
		{
			res ^= bw[i];
		}
	}
	return res;
}

static void SubBytes(unsigned char state[][4])
{
	int r,c;
	for(r=0; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
			state[r][c] = Sbox[state[r][c]];
		}
	}
}

static void ShiftRows(unsigned char state[][4])
{
	unsigned char t[4];
	int r,c;
	for(r=1; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
			t[c] = state[r][(c+r)%4];
		}
		for(c=0; c<4; c++)
		{
			state[r][c] = t[c];
		}
	}
}

static void MixColumns(unsigned char state[][4])
{
	unsigned char t[4];
	int r,c;
	for(c=0; c< 4; c++)
	{
		for(r=0; r<4; r++)
		{
			t[r] = state[r][c];
		}
		for(r=0; r<4; r++)
		{
			state[r][c] = FFmul(0x02, t[r])
						^ FFmul(0x03, t[(r+1)%4])
						^ FFmul(0x01, t[(r+2)%4])
						^ FFmul(0x01, t[(r+3)%4]);
		}
	}
}

static void AddRoundKey(unsigned char state[][4], unsigned char k[][4])
{
	int r,c;
	for(c=0; c<4; c++)
	{
		for(r=0; r<4; r++)
		{
			state[r][c] ^= k[r][c];
		}
	}
}

static void InvSubBytes(unsigned char state[][4])
{
	int r,c;
	for(r=0; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
			state[r][c] = InvSbox[state[r][c]];
		}
	}
}

static void InvShiftRows(unsigned char state[][4])
{
	unsigned char t[4];
	int r,c;
	for(r=1; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
			t[c] = state[r][(c-r+4)%4];
		}
		for(c=0; c<4; c++)
		{
			state[r][c] = t[c];
		}
	}
}

static void InvMixColumns(unsigned char state[][4])
{
	unsigned char t[4];
	int r,c;
	for(c=0; c< 4; c++)
	{
		for(r=0; r<4; r++)
		{
			t[r] = state[r][c];
		}
		for(r=0; r<4; r++)
		{
			state[r][c] = FFmul(0x0e, t[r])
						^ FFmul(0x0b, t[(r+1)%4])
						^ FFmul(0x0d, t[(r+2)%4])
						^ FFmul(0x09, t[(r+3)%4]);
		}
	}
}

 char* Cipher( char* input)
{
	unsigned char state[4][4];
	int i,r,c;

	for(r=0; r<4; r++)
	{
		for(c=0; c<4 ;c++)
		{
			state[r][c] = input[c*4+r];
		}
	}

	AddRoundKey(state,w[0]);

	for(i=1; i<=10; i++)
	{
		SubBytes(state);
		ShiftRows(state);
		if(i!=10)MixColumns(state);
		AddRoundKey(state,w[i]);
	}

	for(r=0; r<4; r++)
	{
		for(c=0; c<4 ;c++)
		{
			input[c*4+r] = state[r][c];
		}
	}

	return input;
}

 char* InvCipher( char* input)
{
	unsigned char state[4][4];
	int i,r,c;

	for(r=0; r<4; r++)
	{
		for(c=0; c<4 ;c++)
		{
			state[r][c] = input[c*4+r];
		}
	}

	AddRoundKey(state, w[10]);
	for(i=9; i>=0; i--)
	{
		InvShiftRows(state);
		InvSubBytes(state);
		AddRoundKey(state, w[i]);
		if(i)
		{
			InvMixColumns(state);
		}
	}
	
	for(r=0; r<4; r++)
	{
		for(c=0; c<4 ;c++)
		{
			input[c*4+r] = state[r][c];
		}
	}

	return input;
}

void KeyExpansion( char* key, unsigned char w[][4][4])
{
	int i,j,r,c;
	char Key[32];
	unsigned char rc[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
	strcpy(Key,key);
	for(r=0; r<4; r++)
	{
		for(c=0; c<4; c++)
		{
			w[0][r][c] = key[r+c*4];
		}
	}
	for(i=1; i<=10; i++)
	{
		for(j=0; j<4; j++)
		{
			unsigned char t[4];
			for(r=0; r<4; r++)
			{
				t[r] = j ? w[i][r][j-1] : w[i-1][r][3];
			}
			if(j == 0)
			{
				unsigned char temp = t[0];
				for(r=0; r<3; r++)
				{
					t[r] = Sbox[t[(r+1)%4]];
				}
				t[3] = Sbox[temp];
				t[0] ^= rc[i-1];
			}
			for(r=0; r<4; r++)
			{
				w[i][r][j] = w[i-1][r][j] ^ t[r];
			}
		}
	}
}

void* Cipher_len(char *key, void* input)
{
	char* in = (char*) input;
	int i,length;
	length = strlen(in);
	KeyExpansion(key, w);
	if(!length)
	{
		while(*(in+length++));
		in = ( char*) input;
	}
	for(i=0; i<length; i+=16)
	{
		Cipher(in+i);
	}
	return input;
}

void* InvCipher_len(char *key, void* input, unsigned int input_size )
{
	char* in = (char*) input;
	int i,length;
	length = input_size;
	KeyExpansion(key, w);
	for(i=0; i<length; i+=16)
	{
		InvCipher(in+i);
	}
	return input;
}

#define PUBLIC_AES_SIZE_ADDR	(512 * 1024)
#define HEAD_SIZE 12


#if 0
struct file_info
	{
		unsigned int file_size_key;
		unsigned int file_size_key_aes;
	}file_aes;

#endif

int do_msc(unsigned long addr, unsigned long off, unsigned long size);

static unsigned int cpu_id[8] = {0};

int get_public_bin_from_msc(char **public)
{
	char *public_aes = NULL;
	char *public_aes_temp = NULL;
	unsigned int public_aes_size = 0;
	char temp_data[512];
	
	int ret = -1;
	int i = 0;

	*cpu_id 			 = (unsigned int)REG_EFUSE_DATA0;
	*(cpu_id + 1) = (unsigned int)REG_EFUSE_DATA1;
	*(cpu_id + 2) = (unsigned int)REG_EFUSE_DATA2;
	*(cpu_id + 3) = (unsigned int)REG_EFUSE_DATA3;
	
	*(cpu_id + 4) = (unsigned int)REG_EFUSE_DATA4;
	*(cpu_id + 5) = (unsigned int)REG_EFUSE_DATA5;
	*(cpu_id + 6) = (unsigned int)REG_EFUSE_DATA6;
	*(cpu_id + 7) = (unsigned int)REG_EFUSE_DATA7;
	
	ret = do_msc((unsigned long)temp_data, PUBLIC_AES_SIZE_ADDR, 512);
	if(ret){
			
	}
	public_aes_size = ((unsigned int )temp_data[7] << 24)| ((unsigned int )temp_data[6] << 6) | ((unsigned int )temp_data[5] << 8)| (unsigned int )temp_data[4];
	
#if 0
	serial_puts("public_aes_size is :::......\n");
	serial_put_hex(public_aes_size);
#endif

	public_aes_temp = (char *)malloc((public_aes_size + 512 ) / 512 * 512);
	if(!public_aes_temp){
		serial_puts("public_aes_temp is NULL:::222\n");
	}
	
	if(public_aes_size > 2048){ //do_msc max read is 2k
		ret = do_msc((unsigned long )public_aes_temp, PUBLIC_AES_SIZE_ADDR, 2048);
		if(ret){
			
		}
	
		ret = do_msc(public_aes_temp + 2048, PUBLIC_AES_SIZE_ADDR + 2048, (public_aes_size - 2048 + 512) / 512 * 512);
		if(ret){
		
		}
	
	}	else if(public_aes_size > 4096){//do not happen
		
	}else{
		ret = do_msc((unsigned long )public_aes_temp, PUBLIC_AES_SIZE_ADDR, public_aes_size);
		if(ret){
			
		}
	}
 	
 	public_aes = (char *)malloc(public_aes_size - HEAD_SIZE);
 	if(public_aes == NULL){
 		 serial_puts("public_aes == NULL\n");
 	}
 	
 	memset(public_aes, 0, public_aes_size - HEAD_SIZE);
 	
 	memcpy(public_aes, public_aes_temp + HEAD_SIZE, public_aes_size - HEAD_SIZE);

#if 0
 	serial_puts("public_aes data :::......\n");
  for(i = 0; i < (public_aes_size - HEAD_SIZE) / 4 ; i++){
  	serial_put_hex(*((unsigned int *)public_aes + i));
  }
#endif

#if 0
	serial_puts("cpu_id :::......\n");

  for(i = 0; i < 8; i++){
  	serial_put_hex(*(cpu_id + i));
  }
#endif

  *public = InvCipher_len((char *)cpu_id, (void *)public_aes, public_aes_size - HEAD_SIZE); 
  if(*public == NULL){
  	serial_puts("public is NULL:::222\n");
  }   

  
#if 0
	serial_puts("public data :::......\n");
  for(i = 0; i < (public_aes_size - HEAD_SIZE) / 4; i++){
  	serial_put_hex(*((unsigned int *)(*public) + i));
  }
#endif

	serial_puts("get_public_bin_from_msc::out out out\n");
	
	return 0;	
}





