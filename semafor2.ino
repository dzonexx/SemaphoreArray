#define LED0 2
#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define LED5 7

#define RED 14
#define YELLOW 15
#define GREEN 16
#define PB_0 17
#define PB_1 18

int Array[6] = {LED0, LED1, LED2, LED3, LED4, LED5};
int cnt = 0;

int Switches[6];
int OldSwitches[6];

uint8_t data1 = 0;

bool flag = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(PB_0, INPUT_PULLUP);
  pinMode(PB_1, INPUT_PULLUP);  

  digitalWrite(RED, HIGH);


  Serial.begin(115200);
      
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(RED) == HIGH){
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);  
  }else if(digitalRead(YELLOW) == HIGH){
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, HIGH);  
  }else if(digitalRead(GREEN) == HIGH){
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
  }
  
  if(Serial.available() > 0){
    String str = Serial.readString();
    if(str == "LED0"){
      if(digitalRead(LED0) == LOW)
        digitalWrite(LED0, HIGH);
      else
        digitalWrite(LED0, LOW);
    }
    else if(str == "LED1"){
      if(digitalRead(LED1) == LOW)
        digitalWrite(LED1, HIGH);
      else
        digitalWrite(LED1, LOW);
    }
    else if(str == "LED2"){
      if(digitalRead(LED2) == LOW)
        digitalWrite(LED2, HIGH);
      else
        digitalWrite(LED2, LOW);
    }    
    else if(str == "LED3"){
      if(digitalRead(LED3) == LOW)
        digitalWrite(LED3, HIGH);
      else
        digitalWrite(LED3, LOW);
    }
    else if(str == "LED4"){
      if(digitalRead(LED4) == LOW)
        digitalWrite(LED4, HIGH);
      else
        digitalWrite(LED4, LOW);
    }
    else if(str == "LED5"){
      if(digitalRead(LED5) == LOW)
        digitalWrite(LED5, HIGH);
      else
        digitalWrite(LED5, LOW);
    }
    else if(str == "DESNO"){
      flag = true;
      if(cnt != 5)
        cnt++;
      else
        cnt = 0;  
    }
    else if(str == "LEVO"){
      flag = true;
      if(cnt != 0)
        cnt--;
      else
        cnt = 5;  
    }     
  }
  if(flag){ 
    for(int i = 0; i < 6; i++)
      digitalWrite(Array[i], LOW); 
    digitalWrite(Array[cnt], HIGH);
  }
  
  for(int i = 0; i < 6; i++){
    OldSwitches[i] = Switches[i];  
  }
 
  if(digitalRead(RED) == HIGH){
    if(digitalRead(PB_0) == 0)
      Switches[0] = 1;
    else
      Switches[0] = 0;

    if(digitalRead(PB_1) == 0)
      Switches[1] = 1;
    else
      Switches[1] = 0;
  }else if(digitalRead(YELLOW) == HIGH){
    if(digitalRead(PB_0) == 0)
      Switches[2] = 1;
    else
      Switches[2] = 0;

    if(digitalRead(PB_1) == 0)
      Switches[3] = 1;
    else
      Switches[3] = 0;
  }else if(digitalRead(GREEN) == HIGH){
    if(digitalRead(PB_0) == 0)
      Switches[4] = 1;
    else
      Switches[4] = 0;

    if(digitalRead(PB_1) == 0)
      Switches[5] = 1;
    else
      Switches[5] = 0;
  }
  
  if(Switches[0] == 1)
    data1 = 1;
  else if(Switches[1] == 1)
    data1 = 2;
  else if(Switches[2] == 1)
    data1 = 4;
  else if(Switches[3] == 1)
    data1 = 8;
  else if(Switches[4] == 1)
    data1 = 16;
  else if(Switches[5] == 1)
    data1 = 32;
  else
    data1 = 0;
  //Serial.println(data);
  bool b = false;
  for(int i = 0; i < 6; i++){
    if(OldSwitches[i] != Switches[i])
      b = true;
  }
  if(b)
    Serial.write(data1);
 
    
  delay(10);
}
