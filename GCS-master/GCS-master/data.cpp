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
    float tid=1012;
    char time[10]="19:01:00",gpstime[10]="19:01:00",sp1time[10]="19:01:00",sp2time[10]="19:01:00";
    int p;
    char pt='c';
    int sp1;
    char spt1[3]="s1",spr1='N';
    int sp2;
    char spt2[3]="s2",spr2='N';
    char Mode='S';
    string Mode1="C";
    char dep='N';
    string csw_state="";
    string tsw_state="STANDBY";
    string cmd_echo="CX-ON";
    float v=5,v1=5,lat,lon,roll1=0,roll2=0;
    double alt=0,temp=0,gpsalt,gpssat=1,s,alt1=0,alt2=0,temp1=0,temp2=0;
    int gyror=0,gyrop=0,gyroy=0,accr=0,accp=0,accy=0,magr=0,magp=0,magy=0,error=0;
}obj[2000];
int main( )
{    
    int k,j,a=0,b=0,l=1,m=1,n=1;
       unsigned int x;
       time_t t;
       x=(unsigned)time(&t);
        srand(x);
    ofstream out;
    out.open("alt.csv");
    for(int i=1;i<=300;i++)
    {
       obj[i].p=i;
       obj[i].v=((rand()%(30000))*(0.0001)+3);
       
       obj[i].temp=((rand()%(280000-130000))*(0.0001)+17);
       obj[i].lon=((rand()%(650000-450000))*(0.0001)+45);
       obj[i].lat=((rand()%(500000-410000))*(0.0001)+41);   
      // obj[i].lat=((rand()%(50-41))/1.1298982+41);  
       if(i%2!=0)
       obj[i].Mode1="C";
       else
       obj[i].Mode1="SP1";
    }
    for(int i=1;i<=1000;i++)
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
    int ht;
    for(int i=1,j=0;i<=300;i++,j+=2.654)
       {
           
           obj[i].gpsalt=obj[i].alt;
           obj[i].csw_state="ASCENT_1";
           obj[i].tsw_state="STANDBY_1";
           if(i<=285)
           obj[i].alt=((rand()%(50000))*(0.0001)+j);
           else
           {
               obj[i].alt=((rand()%(50000))*(0.0001)+obj[i].alt);
               ht=obj[i].alt;
           }
       }
       
       for(int i=300,k=ht ;i<=600;i++,k=k-(ht/300))
       {
           if(i<=317)
           obj[i].alt=((rand()%(50000))*(0.0001)+obj[i].alt);
           else
           obj[i].alt=((rand()%(50000))*(0.0001)+k);
           obj[i].gpsalt=obj[i].alt;
           obj[i].dep='R';
           obj[i].csw_state="DESCENT_1";
           //obj[i].tsw_state="RELEASED";
           if(k<=500)
           {
               obj[i].tsw_state="RELEASED_1";
               obj[i].sp1=a++;
               obj[i].alt1=k;
               obj[i].temp1=obj[i].temp;
               obj[i].spr1='R';
               obj[i].roll1=((rand()%(3400000-2410000))/10000+241);
               obj[i].v1=((rand()%(20000))/10000+3);
               obj[i].magr=((rand()%(20000))/10000-1);
               obj[i].magp=((rand()%(20000))/10000-1);
               obj[i].magy=((rand()%(20000))/10000-1);
               obj[i].accr=((rand()%(20000))/10000-10);
               obj[i].accp=((rand()%(20000))/10000-10);
               obj[i].accy=((rand()%(20000))/10000-10);
               obj[i].gyror=((rand()%(40000))/10000-20);
               obj[i].gyrop=((rand()%(40000))/10000-20);
               obj[i].gyroy=((rand()%(40000))/10000-20);
           }  
            
       }
        
    //out<<"<TEAM_ID>,"<<"<MISSION_TIME>,"<<"<PACKET_COUNT>,"<<"<MODE>,"<<"<TP DEPLOY>,"<<"<C SW STATE>,"<<"<T SW STATE>,"<<"<CMD ECHO>,"<<"<P_ALT>,"<<"<P_TEMP>,"<<"<P_VOLTS>,"<<"<P_GYRO_R>,"<<"<P_GYRO_P>,"<<"<P_GYRO_Y>,"<<"<P_ACC_R>,"<<"<P_ACC_P>,"<<"<P_ACC_Y>,"<<"<P_MAG_R>,"<<"<P_MAG_P>,"<<"<P_MAG_Y>,"<<"<P_ERROR>,"<<"<ALTITUDE>,"<<"<TEMP>,"<<"<VOLTAGE>,"<<"<GPS_TIME>,"<<"<GPS_LATITUDE>,"<<"<GPS_LONGITUDE>,"<<"<GPS_ALTITUDE>,"<<"<GPS_SATS>,"<<"\n";  
    for(int i=1;i<=600;i++)
    {
        if(i%2!=0)
        {
            //obj[i].Mode1='C';
            out<<obj[i].tid<<","<<obj[i].time<<","<<obj[i].p<<","<<obj[i].Mode1<<","<<obj[i].Mode<<","<<obj[i].dep<<","<<obj[i].alt<<","<<obj[i].temp<<","<<obj[i].v<<","<<obj[i].gpstime<<","<<obj[i].lat<<","<<obj[i].lon<<","<<obj[i].gpsalt<<","<<obj[i].gpssat<<","<<obj[i].csw_state<<","<<obj[i].cmd_echo<<"\n";
            Sleep(1000);
        }
        else
        {
            //obj[i].Mode1='SP1';
            out<<obj[i].tid<<","<<obj[i].time<<","<<obj[i].p<<","<<obj[i].Mode1<<","<<obj[i].alt<<","<<obj[i].temp<<","<<obj[i].v<<","<<obj[i].gyror<<","<<obj[i].gyrop<<","<<obj[i].gyroy<<","<<obj[i].accr<<","<<obj[i].accp<<","<<obj[i].accy<<","<<obj[i].magr<<","<<obj[i].magp<<","<<obj[i].magy<<","<<obj[i].error<<","<<obj[i].tsw_state<<","<<obj[i].cmd_echo<<"\n";
            Sleep(1000);
        }
         //out<<obj[i].tid<<","<<obj[i].time<<","<<obj[i].p<<","<<obj[i].Mode<<","<<obj[i].dep<<","<<obj[i].csw_state<<","<<obj[i].tsw_state<<","<<obj[i].cmd_echo<<","<<obj[i].alt<<","<<obj[i].temp<<","<<obj[i].v<<","<<obj[i].gyror<<","<<obj[i].gyrop<<","<<obj[i].gyroy<<","<<obj[i].accr<<","<<obj[i].accp<<","<<obj[i].accy<<","<<obj[i].magr<<","<<obj[i].magp<<","<<obj[i].magy<<","<<obj[i].error<<","<<obj[i].alt<<","<<obj[i].temp<<","<<obj[i].v<<","<<obj[i].gpstime<<","<<obj[i].lat<<","<<obj[i].lon<<","<<obj[i].gpsalt<<","<<obj[i].gpssat<<"\n";
         
    }  
   return 0;
}