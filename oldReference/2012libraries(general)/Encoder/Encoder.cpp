#include <Arduino.h>
#include <Encoder.h>

Encoder::Encoder(int pA, int pB, double r, double cpr, int t, bool invertDir) : distancePerCount(2*PI*r/cpr){
  timeout=t;
  pinA=pA;
  pinB=pB;
  
  if(invertDir){ invert = true;  }
  else         { invert = false; }
  
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  p1=0; p2=0; p3=0; p4=0; p5=0;
}
Encoder::Encoder(int pA, int pB, double r, double cpr, bool invertDir) : distancePerCount(2*PI*r/cpr){
  timeout=100;
  pinA=pA;
  pinB=pB;
  
  if(invertDir){ invert = true;  }
  else         { invert = false; }
  
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  p1=0; p2=0; p3=0; p4=0; p5=0;
}
Encoder::Encoder(int pA, int pB, double distPerCount, int t, bool invertDir){
  timeout = t;
  distancePerCount = distPerCount;
  pinA = pA;
  pinB = pB;
  
  if(invertDir){ invert = true;  }
  else         { invert = false; }
  
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  p1=0; p2=0; p3=0; p4=0; p5=0;
}
Encoder::Encoder(int pA, int pB, double distPerCount, bool invertDir){
  timeout = 100;
  distancePerCount = distPerCount;
  pinA = pA;
  pinB = pB;
  
  if(invertDir){ invert = true;  }
  else         { invert = false; }
  
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  p1=0; p2=0; p3=0; p4=0; p5=0;
}
  
double Encoder::getDistance(){
  return count * distancePerCount;
}
double Encoder::getSpeed(){
  if(millis()-lastTime>=timeout){
    speed=0;
    lastTime=millis()-timeout;
  }
  return speed;
}
double Encoder::getCount(){
  return count;
}
void Encoder::setTimeout(int t){
  timeout=t;
}
void Encoder::reset(){
  count=0;
  speed=0;
}
double Encoder::getDistancePerCount(){
  return distancePerCount;
}

bool Encoder::stopped(){
  return getSpeed() == 0;

}
int Encoder::direction(){
  double s = (*this).getSpeed();
  if(s > 0){ return  1; }
  if(s < 0){ return -1; }
  return 0;
}

void Encoder::encoderEvent(bool mode){
  int temp=millis();
  double p=(double)(temp-lastTime);
  
  if(distancePerCount / p * 1000 > 100){ return; }
  
  double period = (p1+p2+p3+p4+p5+p)/6;
  p5=p4; p4=p3; p3=p2; p2=p1; p1=p;
  lastTime=temp;
  speed= distancePerCount / period * 1000.0;
  
  if(digitalRead(pinA) == digitalRead(pinB) ^ !invert ^ mode){
    count++;
  }else{
    count--;
    speed *= -1.0;
  }
}