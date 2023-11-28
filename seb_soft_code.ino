#define N1 7   
#define N2 8
#define N3 11
#define N4 12
int Speed_control = A0;
int Speed = 0;
int n = 0;
int m = 0;
String command;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  pinMode(N3, OUTPUT);
  pinMode(N4, OUTPUT);

TCCR1B=TCCR1B & B11111000 | B00000010;
TCCR4B=TCCR4B & B11111000 | B00000010;
}

void loop() {
  //Speed = analogRead(Speed_control);
  //Serial.print(Speed);
  if(Serial.available()){
    command = Serial.readStringUntil('\n');
    command.trim();
    if (command.equals("CW")){
      analogWrite(N3, LOW);
      analogWrite(N2, LOW);
      delay(5000);
      Serial.print("PWM: ");
      while(!Serial.available()){}
      m = Serial.parseInt();
      Serial.print(m);
      for(n; n<=m; n++){
        analogWrite(N1, n);
        analogWrite(N4, n);
        delay(100);
      }
      for(n; n>=m; n--){ 
        analogWrite(N1, n);
        analogWrite(N4, n);
        delay(100);
      }
    }
    if (command.equals("CC")){
      analogWrite(N1, LOW);
      analogWrite(N4, LOW);
      delay(6000);
      Serial.print("PWM: ");
      while(!Serial.available()){}
      m = Serial.parseInt();
      Serial.print(m);
      for(n; n<=m; n++){
        analogWrite(N3, n);
        analogWrite(N2, n);
        delay(100);
      }
      for(n; n>=m; n--){ 
        analogWrite(N3, n);
        analogWrite(N2, n);
        delay(100);
      }
    }
  }
  if (command.equals("S")){ //this function will stop pulsing the bridge and let the motor coast to a stop 
    //Serial.print("motor will coast to a stop and braking resistor will be activated");
    analogWrite(N1, LOW);
    analogWrite(N2, LOW);
    analogWrite(N3, LOW);
    analogWrite(N4, LOW);
    return 0; 
  }
   if (command.equals("B")){ 
    //Serial.print(" program will return to the beginng");
    analogWrite(N1, LOW);
    delay(500);
    analogWrite(N2, 128);
    analogWrite(N3, LOW);
    delay(500);
    analogWrite(N4, 128);
    return 0;
    
  }
  
  }
  
