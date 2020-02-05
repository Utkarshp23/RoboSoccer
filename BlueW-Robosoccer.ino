int pwm1 = 3;
int dir1 = 10;
int pwm2 = 4;
int dir2 = 9;

void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm2, OUTPUT);
  Serial.begin(115200);
}
int lya, rya;

void loop() {

  lya = map(analogRead(A2), 0 , 707 ,  200 , -220);
  rya = map(analogRead(A1), 0 , 707 ,  200 , -235);



//  if (lya > -10 && lya < 20 && rya > -5 && rya < 20)
//  {
//    lya = rya = 0;
//  }

if (lya > -10 && lya < 20 )
  {
    lya = 0;
  }
  if( rya > -20 && rya < 20){
    rya=0 ;
  }
  //  lya = 20;
  Serial.print(lya);
  Serial.print("\t");
  Serial.println(rya);
  //  rya = 20;
  if (lya < 0)
  {
    digitalWrite(dir1 , 0);
    //Serial.print();
    analogWrite(pwm1 , -lya);
  }
  else
  {
    digitalWrite(dir1 , 1);
    analogWrite(pwm1 , lya);
  }

  if (rya < 0)
  {
    digitalWrite(dir2 , 0);
    analogWrite(pwm2 , -rya);
  }
  else
  {

    digitalWrite(dir2 , 1);
    analogWrite(pwm2 , rya);
  }

}
