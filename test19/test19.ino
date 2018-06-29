#include  <TimerOne.h>
#include <IRremote.h>

#define b1 0x1FE50AF
#define b2 0x1FED827
#define b3 0x1FEF807
#define b4 0x1FE30CF
#define b5 0x1FEB04F
#define b6 0x1FE708F
#define b7 0x1FE00FF
#define b8 0x1FEF00F
#define b9 0x1FE9867
#define b0 0x1FEE01F
#define mode 0x1FE20DF
#define prev 0x1FEC03F
#define next 0x1FE40BF


int st=0;
int m=0;
int to=0;
int toff=0;
int tn=0;

int hour=0;
int minute=0;
int second=0;

int L1=5;
int RECV_PIN = 4;

int timenow[3]={00,00,00};;
int timeon[3]={21,03,00};
int timeoff[3]={21,04,00};
int currenttime[3]={0,0,0};


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  irrecv.enableIRIn();
  Timer1.initialize(1000);  
  Timer1.attachInterrupt(time_check, 1000000); 
  pinMode(L1, OUTPUT);
  digitalWrite(L1,LOW);
  Serial.begin(9600);
}

void time_check(){
  if(st==0)
  {
     second++;
    if(second>=60){  
    minute++;
    second=0;
  }
  if(minute>=60){
    hour++;
    minute=0;
  }
  if(hour>=24){
    hour=0;
  }
  }
   
}

void printNow(){
  
  Serial.print("Now : ");
  Serial.print(currenttime[0]);
  Serial.print(":");
  Serial.print(currenttime[1]);
  Serial.print(":");
  Serial.println(currenttime[2]);
}
void printTo(){
  
}
void printTn(){
  
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
  switch(results.value){
    case mode:{
      if(m==0){
        st=1;
        second=0;
        m=1;
        printNow(); 
      }
      else{
        st=0;
        m=0;
        printNow();  
      }
      break;
    }
    case b1:{
      if(st==1)
      timenow[0]++;
      printNow(); 
     break; 
    }
    case b2:{
      if(st==1)
      timenow[1]++;
      printNow(); 
     break; 
    }
    case b3:{
      if(st==1)
      second++;
      printNow(); 
     break; 
    }
    case b4:{
      if(st==1){
        timenow[0]--;
      }
      printNow(); 
     break; 
    }
    case b5:{
      if(st==1)
      timenow[1]--;
      printNow(); 
     break; 
    }
    case b6:{
      if(st==1)
      second--;
      printNow(); 
     break; 
    }
    case b7:{
      
     break; 
    }
    case b8:{
      if(to==0){
        
      }
      else{
        
      }
     break; 
    }
    case b9:{
      tn=3;
     break; 
    }
    case prev:{
     break; 
    }
    case next:{
     break; 
    }
    default:{
      break;
    }
  }
    
    irrecv.resume();
  }

  
  
  currenttime[0]=timenow[0]+hour;
  currenttime[1]=timenow[1]+minute;
  currenttime[2]=timenow[2]+second;
  //printNow();
  /*
  Serial.print("Time On : ");
  Serial.print(timeon[0]);
  Serial.print(":");
  Serial.print(timeon[1]);
  Serial.print(":");
  Serial.println(timeon[2]);
  */
  if(currenttime[0]==timeon[0] && currenttime[1]==timeon[1] && currenttime[2]==timeon[2]){
     digitalWrite(L1,HIGH);
     Serial.println("FIRED");
  }
  if(currenttime[0]==timeoff[0] && currenttime[1]==timeoff[1] && currenttime[2]==timeoff[2]){
     digitalWrite(L1,LOW);
     Serial.println("FIRED");
  }
  //delay(1000);
}
