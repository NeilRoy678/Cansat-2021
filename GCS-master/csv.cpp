#include<iostream>
#include<conio.h>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
#include<windows.h>
using namespace std;
struct altair
{
    float tid=1357;
    char time[10]="23:01:00",gpstime[10]="23:01:00",sp1time[10]="23:01:00",sp2time[10]="23:01:00";
    int p;
    char pt='c';
    int sp1;
    char spt1[3]="s1",spr1='N';
    int sp2;
    char spt2[3]="s2",spr2='N';
    char Mode='S';
    float v=5,lat,lon,roll1=0,roll2=0;
    int alt,temp,gpsalt,gpssat=1,s,alt1=0,alt2=0,temp1=0,temp2=0;
}obj[1000];
int main( )
{    
    int k,j,a=0,b=0,l=1,m=1,n=1;
       unsigned int x;
       time_t t;
       x=(unsigned)time(&t);
        srand(x);
    ofstream out;
    out.open("a.csv");
    for(int i=1;i<=300;i++)
    {
       obj[i].p=i;
       obj[i].v=((rand()%(5-3))+3);
       obj[i].temp=((rand()%(28-13))+13);
       obj[i].lon=((rand()%(65-45))+45);
       obj[i].lat=((rand()%(50-41))+41);   
    }
    for(int i=1;i<=300;i++)
    {
            k=i%10; 
            obj[i].time[7]=k+'0';
            obj[i].gpstime[7]=k+'0';
            obj[i].sp1time[7]=k+'0';
            obj[i].sp2time[7]=k+'0';
            l=i/60;
            m=(i-(l*60));
            m=m/10;
            obj[i].time[6]=m+'0';
            obj[i].time[4]=l+'1';
            obj[i].gpstime[6]=m+'0';
            obj[i].gpstime[4]=l+'1';
            obj[i].sp1time[6]=m+'0';
            obj[i].sp1time[4]=l+'1';
            obj[i].sp2time[6]=m+'0';
            obj[i].sp2time[4]=l+'1';
    }
    for(int i=1,j=0;i<=150;i++,j+=5)
       {
           obj[i].alt=j;
           obj[i].gpsalt=j;
       }
       for(int i=150,k=740 ;i<=300;i++,k=k-5)
       {
           obj[i].alt=k;
           obj[i].gpsalt=k;
           if(k<=500)
           {
               obj[i].sp1=a++;
               obj[i].alt1=k;
               obj[i].temp1=obj[i].temp;
               obj[i].spr1='R';
               obj[i].roll1=((rand()%(340-241))+241);
           }  
           if(k<=400)
           {
               obj[i].sp2=b++;
               obj[i].alt2=k;
               obj[i].temp2=obj[i].temp;
               obj[i].spr2='R';
               obj[i].roll2=((rand()%(340-241))+241);
           }  
       }
        
    out<<"<TEAM_ID>,"<<"<MISSION_TIME>,"<<"<PACKET_COUNT>,"<<"<PACKET_TYPE>,"<<"<MODE>,"<<"<SP1_RELEASED>,"<<"<SP2_RELEASED>,"<<"<ALTITUDE>,"<<"<TEMP>,"<<"<VOLTAGE>,"<<"<GPS_TIME>,"<<"<GPS_LATITUDE>,"<<"<GPS_LONGITUDE>,"<<"<GPS_ALTITUDE>,"<<"<GPS_SATS>,"<<"<SP1_PACKET_COUNT>,"<<"<SP1_TIME>,"<<"<SP1_PACKET_TYPE>,"<<"<SP1_ALTITUDE>,"<<"<SP1_TEMP>,"<<"<SP1_ROTATION_RATE>,"<<"<SP2_PACKET_COUNT>,"<<"<SP2_TIME>,"<<"<SP2_PACKET_TYPE>,"<<"<SP2_ALTITUDE>,"<<"<SP2_TEMP>,"<<"<SP2_ROTATION_RATE>"<<"\n";  
    for(int i=1;i<=300;i++)
    {
         out<<obj[i].tid<<","<<obj[i].time<<","<<obj[i].p<<","<<obj[i].pt<<","<<obj[i].Mode<<","<<obj[i].spr1<<","<<obj[i].spr2<<","<<obj[i].alt<<","<<obj[i].temp<<","<<obj[i].v<<","<<obj[i].gpstime<<","<<obj[i].lat<<","<<obj[i].lon<<","<<obj[i].gpsalt<<","<<obj[i].gpssat<<","<<obj[i].sp1<<","<<obj[i].sp1time<<","<<obj[i].spt1<<","<<obj[i].alt1<<","<<obj[i].temp1<<","<<obj[i].roll1<<","<<obj[i].sp2<<","<<obj[i].sp2time<<","<<obj[i].spt2<<","<<obj[i].alt2<<","<<obj[i].temp2<<","<<obj[i].roll2<<"\n";
         Sleep(1000);
    }  
   return 0;
}
