#include<wiringPi.h> // alike GPIO
#include<string.h>
#include<stdio.h>
 
#define m1 29
#define m2 28

#define RS 11
#define EN 10
#define D4 6
#define D5 5
#define D6 4
#define D7 1

char pass[4];
char pass1[]={'1','2','3','4'};
int n=0;
char row[4]={21, 14, 13, 12};
char col[4]={22, 23, 24, 25};

char num[4][4]={
                  {'1','2','3','A'},
                  {'4','5','6','B'},
                  {'7','8','9','C'},
                  {'*','0','#','D'}
                 };

void keypad();
void lcdcmd(unsigned int ch)
  {
    int temp=0x80;
    digitalWrite(D4, temp & ch<<3);
    digitalWrite(D5, temp & ch<<2);
    digitalWrite(D6, temp & ch<<1);
    digitalWrite(D7, temp & ch);
    digitalWrite(RS, LOW);
    digitalWrite(EN, HIGH);
    delay(10);
    digitalWrite(EN, LOW);
    digitalWrite(D4, temp & ch<<7);
    digitalWrite(D5, temp & ch<<6);
    digitalWrite(D6, temp & ch<<5);
    digitalWrite(D7, temp & ch<<4);
    digitalWrite(RS, LOW);
    digitalWrite(EN, HIGH);
    delay(10);
    digitalWrite(EN, LOW);
  }

void write(unsigned int ch)
  {
    int temp=0x80;
    digitalWrite(D4, temp & ch<<3);
    digitalWrite(D5, temp & ch<<2);
    digitalWrite(D6, temp & ch<<1);
    digitalWrite(D7, temp & ch);
    digitalWrite(RS, HIGH);
    digitalWrite(EN, HIGH);
    delay(10);
    digitalWrite(EN, LOW);
    digitalWrite(D4, temp & ch<<7);
    digitalWrite(D5, temp & ch<<6);
    digitalWrite(D6, temp & ch<<5);
    digitalWrite(D7, temp & ch<<4);
    digitalWrite(RS, HIGH);
    digitalWrite(EN, HIGH);
    delay(10);
    digitalWrite(EN, LOW);
  }
  
void clear()
  {
     lcdcmd(0x01);
  }

  void setCursor(int x, int y)
  {
    int set=0;
    if(y==0)
    set=128+x;
    if(y==1)
    set=192+x;
    lcdcmd(set);
  }

  void print(char *str)
  {
    while(*str)
    {
     write(*str);
     str++;
    }
  }

  void begin(int x, int y)
  {
    lcdcmd(0x02);
    lcdcmd(0x28);
    lcdcmd(0x06);
    lcdcmd(0x0e);
    lcdcmd(0x01);
  }

  void enter()
  {
    clear();
    print("Current Passkey:");
    setCursor(0,1);
    keypad();
    if(strncmp(pass,pass1,4)==0)
    {
       clear();
       print("Enter New Passkey");
       setCursor(0,1);
       keypad();
       for(n=0;n<4;n++)
       pass1[n]=pass[n];
       clear();
       print("Passkey Changed.");
       delay(3000);
       return;
    }

    else
    {
      clear();
      print("Wrong password");
      setCursor(0,1);
      return;
    }
  }

  void gate_open()
  {
     digitalWrite(m1, LOW);
     digitalWrite(m2, HIGH);
     delay(2000);
  }

  void gate_stop()
  {
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    delay(2000);
  }

   void gate_close()
  {
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    delay(2000);
  }

  void choice()
  {
    digitalWrite(col[0], LOW);
    digitalWrite(col[1],HIGH);
     if(digitalRead(row[3])==0)
     {
       clear();
       print("Enter Password:");
       setCursor(0,1);
       keypad();
       if(strncmp(pass,pass1,4)==0)
       {
        clear();
        setCursor(0,1);
        print("Door Unlock");
        gate_open();
        gate_stop();
        gate_close();
        gate_stop();
        return;
       }

       else
       {
          clear();
          print("Access Denied");
          setCursor(0,1);
          return;
       }
     }
     digitalWrite(col[0], HIGH);
     digitalWrite(col[1], LOW);
     if(digitalRead(row[3])==0)
     {
      enter();
     }
  }

  void setup()
  {
  if(wiringPiSetup()==-1)
  print("Error");
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  for(n=0;n<4;n++)
  pinMode(row[n], INPUT);
  for(n=0;n<4;n++)
  pinMode(col[n], OUTPUT);
  for(n=0;n<4;n++)
  digitalWrite(col[n], HIGH);
  }
  