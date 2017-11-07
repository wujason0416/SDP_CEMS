//gcc 5.4.0



#include <stdio.h>
#include <stdlib.h>
#include <string.h>   //strncpy
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>   //ifreq
#include <unistd.h>   //close
 
 
struct ifreq ifr;
//struct ifreq ifr_res; 
unsigned char sid[20];
unsigned char mac[20];
unsigned char * mac_getinfo()
{
	char cid_directory [256];
    int i = 0;
    unsigned char *sid_str;
	unsigned char *cpu_str;	
	unsigned char *mac_str;
	unsigned char *str;
	unsigned char *str_code;
	int len=0,h=0,l=0;
	FILE *fp;
    //system("udevadm info -a -n /dev/ mmcblk1 | grep -i serial > cpuinfo.log");
	system("udevadm info -a -n /dev/mmcblk0 | grep -i serial >sidinfo.log");
    system("cat /proc/cpuinfo |tail -n 1 | sed 's/^Serial.*: 00000000//g' > cpuinfo.log");    
	system("ifconfig >macinfo.log");
	
	fp = fopen("macinfo.log","rb");
	fseek(fp,0,SEEK_END);
	len=(unsigned int)ftell(fp);
	 
	mac_str = (unsigned char *)malloc( (len+1) * sizeof(char) );
    str = mac_str+3;
	fseek(fp,0,SEEK_SET);
    fread(mac_str,sizeof(char),len,fp);
	fclose(fp);
	for(i=0;i<6;i++){
		h=(str[i+i]-0x60)>0?(str[i+i]-0x60+9):(str[i+i]-0x30);
		l=(str[i+i+1]-0x60)>0?(str[i+i+1]-0x60+9):(str[i+i+1]-0x30);
		mac[i]=h*16+l;
	}
	//printf("MAC : %.2x:%.2x:%.2x:%.2x\n" , mac[0], mac[1], mac[2], mac[3]);
    free(mac_str);

	fp = fopen("cpuinfo.log","rb");
	fseek(fp,0,SEEK_END);
	len=(unsigned int)ftell(fp);
	 
	cpu_str = (unsigned char *)malloc( (len+1) * sizeof(char) );
    str=cpu_str;
	fseek(fp,0,SEEK_SET);
    fread(cpu_str,sizeof(char),len,fp);
	fclose(fp);
	for(i=0;i<4;i++){
		h=(str[i+i]-0x60)>0?(str[i+i]-0x60+9):(str[i+i]-0x30);
		l=(str[i+i+1]-0x60)>0?(str[i+i+1]-0x60+9):(str[i+i+1]-0x30);
		sid[i]=h*16+l;
		mac[i+6]=sid[i];
	}	
	//printf("CPU : %.2x:%.2x:%.2x:%.2x\n" , sid[0], sid[1], sid[2], sid[3]);
    free(cpu_str);
    
	fp = fopen("sidinfo.log","rb");
	fseek(fp,0,SEEK_END);
	len=(unsigned int)ftell(fp);
	 
	sid_str = (unsigned char *)malloc( (len+1) * sizeof(char) );
    fseek(fp,0,SEEK_SET);
    fread(sid_str,sizeof(char),len,fp);
	fclose(fp);
	//str_code=strstr("ATTRS{serial}==\"0x",sid_str); 
	str_code=(unsigned char *)strstr(sid_str,"0x");
    str=str_code+2;	
	for(i=0;i<4;i++){
		h=(str[i+i]-0x60)>0?(str[i+i]-0x60+9):(str[i+i]-0x30);
		l=(str[i+i+1]-0x60)>0?(str[i+i+1]-0x60+9):(str[i+i+1]-0x30);
		sid[i+4]=h*16+l;
		mac[i+10]=sid[i+4];
	}
	//printf("SID : %.2x:%.2x:%.2x:%.2x\n" , sid[4], sid[5], sid[6], sid[7]);
    free(sid_str);
	return sid;    
}

int LRS_Generator_0_7_9_14_15_17_18_19_21( int len,unsigned char *Fill,unsigned char *SpreadingCode )
{
	unsigned char ucRGE[22];
	unsigned int uiByte=0,uiBit=0,uiCounter=0;
	srand(20171007);
	//unsgned int seed =(rand() % 2) ;
	for( uiCounter=0;uiCounter<len;uiCounter++ )
	{
		 
		SpreadingCode[uiCounter]|=(rand() % 256);
         
	}
	/*for( uiByte=0 ; uiByte<3 ; uiByte++ )
	{
		if( (uiByte*8+uiBit)<21 )
		{
			for( uiBit=0 ; uiBit<8 ; uiBit++ )
			{
				if( Fill[uiByte]&(0x80>>uiBit) )
					ucRGE[uiByte*8+uiBit]=0xff;
				else
					ucRGE[uiByte*8+uiBit]=0x00;
			}
		}
	}
	ucRGE[21]=0x00;
    while( uiCounter<len*8 )
	{
		ucRGE[21]=(((((((ucRGE[7]^ucRGE[9])^ucRGE[14])^ucRGE[15])^ucRGE[17])^ucRGE[18])^ucRGE[19])^ucRGE[0]);
        if( ucRGE[0]==0xff )
			SpreadingCode[uiCounter/8]|=(0x80>>(uiCounter%8));
        //SpreadingCode[uiCounter]=  ucRGE[0]; 
		for( uiByte=0 ; uiByte<21 ; uiByte++ )
			ucRGE[uiByte]=ucRGE[uiByte+1];
		uiCounter++;
	}*/

	return 0;
}
/*******************************************************************************************************************************************/
int check(unsigned char *mac,unsigned char *code,int len){
	int i=0;
	for(i=0;i<len;i++){
		//printf(" %2x:%2x\n" , mac[i], code[i] );
 
		if(mac[i]!=code[i])
			return 0;
	}
	return 1;
}
int main(int argc, char *argv[])
{
	
	FILE *fp;
	unsigned char *str1;//[7189648];
	unsigned char *str;//[7189648];
	unsigned char *cstr;
	unsigned int len=0;
	unsigned char Fill[4]={7,9,1,4};//"7914";
	int i=0;
	int type=0;
	
	//char argv1[128]="/home/pi/SDP";
	
	unsigned char *mac_res;
	const size_t IFREQSZ = 6+4+4;//sizeof(struct ifreq);
	//int ifr_len=(argc==1)?IFREQSZ:0;
	int encry_len=20000;
	
	mac_getinfo();
	fp=fopen(argv[1],"rb");
	fseek(fp,0,SEEK_END);
	len=(unsigned int)ftell(fp);
	if (encry_len>len)
		encry_len=len;
	str  = (unsigned char *)malloc( (len+201) * sizeof(char) );
 	str1 = (unsigned char *)malloc( (len+201) * sizeof(char) );
    cstr = (unsigned char *)malloc( (len+201) * sizeof(char) );
 
	fseek(fp,0,SEEK_SET);
    fread(str1,sizeof(char),len,fp);
	fclose(fp);
	if(argc==3){
		type=atoi(argv[2]);
	}
	//type 1 only encrpt 20000 plaintxt
	//type 2 encrypt full plaintxt
	LRS_Generator_0_7_9_14_15_17_18_19_21(encry_len+120,Fill, str );
	if(type==0){
	   for( i=0;i<IFREQSZ;i++){
		  cstr[i]= mac[i]^str[i+24] ^str[i+53]^str[i+82];
	   }
	   for(i=IFREQSZ;i<IFREQSZ+encry_len;i++){
	       cstr[i]=str1[i-IFREQSZ]^str[i+24]^str[i+53]^str[i+82];
	   }
	}
	else{
	   for( i=0;i<IFREQSZ;i++){
		   cstr[i]= str1[i]^str[i+24] ^str[i+53]^str[i+82];
	   }
	   //printf("%2x%2x%2x\n",str[0],str[1],str[2]);
	   for( i=IFREQSZ;i<IFREQSZ+encry_len;i++){
           cstr[i]=str1[i]^str[i+24]^str[i+53]^str[i+82];
	   }
	}


	if( type!=0 && check(mac,cstr,IFREQSZ)==1 ){
		//printf("check OK\n");
		if(type==2){
	        fp=fopen("/tmp/SDP","wb");
	        fwrite(cstr+IFREQSZ,sizeof(char),encry_len,fp);
	        fwrite(str1+encry_len+IFREQSZ,sizeof(char),len-encry_len-IFREQSZ,fp);
	        fclose(fp);
	
            system("chmod 777 /tmp/SDP");
            system("/tmp/SDP&");
	        // system("rm /tmp/SDP");
            printf("Sucess 2!\n");
	        sleep(30);
	        //system("chmod 777 /tmp/SDP");
		    system("rm /tmp/SDP");
			}
		else{
			fp=fopen(argv[1],"wb");
	        fwrite(cstr+IFREQSZ,sizeof(char),encry_len,fp);
	        //fwrite(str1+encry_len+IFREQSZ,sizeof(char),len-encry_len-IFREQSZ,fp);
	        fclose(fp);
			printf("Sucess 1!\n");
			system("rasterisk -x \"dialplan reload\"");	        
		}
    }
	if(type==0){
	   fp=fopen(argv[1],"wb");
	   fwrite(cstr,sizeof(char),IFREQSZ+encry_len,fp);
	   //printf("%2x%2x%2x\n",cstr[0],cstr[1],cstr[2]);
	   fwrite(str1+encry_len,sizeof(char),len-encry_len,fp);
	   fclose(fp);
	}
	else{
	   fp=fopen(argv[1],"wb");
	   fwrite(str1,sizeof(char),len,fp);
	   //printf("%2x%2x%2x\n",cstr[0],cstr[1],cstr[2]);
	   fclose(fp);	    
	}
	
	free(str);
    free(str1);	
	free(cstr);
    return 1;
}

/*
char * mac_add()
{
    int fd=0,i=0;
    char *iface = "eth0";
    char *mac_str;
    mac_getinfo();
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);
    ioctl(fd, SIOCGIFHWADDR, &ifr);
    close(fd);
     
    mac_str = (unsigned char *)ifr.ifr_hwaddr.sa_data;
	//b8:27:eb:26:c6:a7
    //wlan0 b8:27:eb:73:93:f2	
    for(i=0;i<6;i++){
		mac[i]=mac_str[i];
	}
	for(i=0;i<8;i++){
		mac[i+6]=sid[i];
	}
    //display mac address
    printf("Mac : %2x:%2x:%2x:%2x:%2x:%2x\n" , mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
 
    return mac;
}
*/