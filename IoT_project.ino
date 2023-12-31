// motor control pin
const int motorDirPin = 11;  // L298 Input 1
const int motorPWMPin = 8;   // L298 Input 2
const int stop = 9;
const int start = 10;

// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 4;
int encoderPos = 0;
const float ratio = 360. / 264. / 26.;

const int TRIG = 6; //TRIG
const int ECHO = 7; //ECHO 7

// P control
float Kp = 25;
float targetDeg;

// Floor button, toggle, angle for each floor
int button1 = 14;
int button2 = 15;
int button3 = 16;
int button4 = 17;
int button5 = 18;
int button6 = 19;
int button7 = 13;

unsigned int toggle1 = 0;
unsigned int toggle2 = 0;
unsigned int toggle3 = 0;
unsigned int toggle4 = 0;
unsigned int toggle5 = 0;
unsigned int toggle6 = 0;
unsigned int toggle7 = 0;

int angle0; //기준이 되는 각도
unsigned int angleToggle = 0;

int angle1;
int angle2;
int angle3;
int angle4;
int angle5;
int angle6;

unsigned int box1 = 0;
unsigned int box2 = 0;
unsigned int box3 = 0;
unsigned int box4 = 0;
unsigned int box5 = 0;
unsigned int box6 = 0;

unsigned int label1 = 0;
unsigned int label2 = 0;
unsigned int label3 = 0;
unsigned int label4 = 0;
unsigned int label5 = 0;
unsigned int label6 = 0;
unsigned int label7 = 0;

unsigned int time = 0;

// targets
int targets[6] = {};

void doEncoderA() {
  encoderPos += (digitalRead(encoderPinA) == digitalRead(encoderPinB)) ? 1 : -1;
}
void doEncoderB() {
  encoderPos += (digitalRead(encoderPinA) == digitalRead(encoderPinB)) ? -1 : 1;
}

void doMotor(bool dir, int vel) {
  digitalWrite(motorDirPin, dir ? LOW : HIGH);
  analogWrite(motorPWMPin, dir ? (255 - vel) : vel);
}

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
  pinMode(motorDirPin, OUTPUT);
  
  pinMode(stop, OUTPUT);
  pinMode(start, OUTPUT);
  pinMode(button7, INPUT);
  pinMode(button1, INPUT);  //1st 
  pinMode(button2, INPUT);  //2nd 
  pinMode(button3, INPUT);  //3rd 
  pinMode(button4, INPUT);  //3rd 
  pinMode(button5, INPUT);  //3rd 
  pinMode(button6, INPUT);  //3rd 

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

}

void loop()
{
  float motorDeg = float(encoderPos) * ratio;
  double error = targetDeg - motorDeg;
  float control = Kp * error;

  long duration, distance;
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH); // 초음파를 받은 시간 (LOW 에서 HIGH 로)
  distance = duration * 17 / 1000; // cm 로 환산 (34000 / 10000000 / 2 를 간단하게)

  if (angleToggle == 0)
  {
    if(distance > 3)
    {
      digitalWrite(start, HIGH);
      digitalWrite(stop, HIGH);
      doMotor(LOW, 255);
    }
    else
    {
      digitalWrite(start, LOW);
      digitalWrite(stop, LOW);
      angle0 = motorDeg;
      targets[0] = angle0;
      targets[1] = angle0;
      targets[2] = angle0;
      targets[3] = angle0;
      targets[4] = angle0;
      targets[5] = angle0;
      angle1 = angle0 + 1;
      angle2 = angle0 + 60;
      angle3 = angle0 + 120;
      angle4 = angle0 + 180;
      angle5 = angle0 + 240;
      angle6 = angle0 + 300;
      angleToggle = 1;
    }
  }

  

  else if(angleToggle == 1)
  {
    if (label2 != 0 && label3 != 0 && label4 != 0 && label5 != 0 && label6 != 0 && label7 != 0)
    {
      if (digitalRead(button1) == HIGH)
      {
        if (toggle1 == 0)
        {
          toggle1 = 1;
        }
      }
      else
      {
        if (toggle1 == 1)
        {
          angleToggle = 2;
          Serial.println("S T O P !");
        }
      }
    }  
    else
    {
      if (digitalRead(button1) == HIGH)
      {
        if (toggle1 == 0)
        {
          toggle1 = 1;
        }
      }
      else
      {
        if (toggle1 == 1)
        {
          if(label1 == 0)
          {
            if(box1 == 0)
            {
              label1 = 1;
              box1 += 1;
              target(angle1);
            }
            else if(box2 == 0)
            {
              label1 = 2;
              box2 += 1;
              target(angle2);
            }
            else if(box3 == 0)
            {
              label1 = 3;
              box3 += 1;
              target(angle3);
            }
            else if(box4 == 0)
            {
              label1 = 4;
              box4 += 1;
              target(angle4);
            }
            else if(box5 == 0)
            {
              label1 = 5;
              box5 += 1;
              target(angle5);
            }
            else if(box6 == 0)
            {
              label1 = 6;
              box6 += 1;
              target(angle6);
            }
            toggle1 = 0;
          }
          else
          {
            if(label1 == 1)
            {
              box1 += 1;
              target(angle1);
            }
            else if(label1 == 2)
            {
              box2 += 1;
              target(angle2);
            }
            else if(label1 == 3)
            {
              box3 += 1;
              target(angle3);
            }
            else if(label1 == 4)
            {
              box4 += 1;
              target(angle4);
            }
            else if(label1 == 5)
            {
              box5 += 1;
              target(angle5);
            }
            else if(label1 == 6)
            {
              box6 += 1;
              target(angle6);
            }
            toggle1 = 0;
          }
        }
      }
    }

    if (label1 != 0 && label3 != 0 && label4 != 0 && label5 != 0 && label6 != 0 && label7 != 0)
    {
      if (digitalRead(button2) == HIGH)
      {
        if (toggle2 == 0)
        {
          toggle2 = 1;
        }
      }
      else
      {
        if (toggle2 == 1)
        {
          angleToggle = 2;
          Serial.println("S T O P !");
        }
      }
    }
    else
    {
      if (digitalRead(button2) == HIGH)
      {
        if (toggle2 == 0)
        {
          toggle2 = 1;
        }
      }
      else
      {
        if (toggle2 == 1)
        {
          if(label2 == 0)
          {
            if(box1 == 0)
            {
              label2 = 1;
              box1 += 1;
              target(angle1);
            }
            else if(box2 == 0)
            {
              label2 = 2;
              box2 += 1;
              target(angle2);
            }
            else if(box3 == 0)
            {
              label2 = 3;
              box3 += 1;
              target(angle3);
            }
            else if(box4 == 0)
            {
              label2 = 4;
              box4 += 1;
              target(angle4);
            }
            else if(box5 == 0)
            {
              label2 = 5;
              box5 += 1;
              target(angle5);
            }
            else if(box6 == 0)
            {
              label2 = 6;
              box6 += 1;
              target(angle6);
            }
            toggle2 = 0;
          }
          else
          {
            if(label2 == 1)
            {
              box1 += 1;
              target(angle1);
            }
            else if(label2 == 2)
            {
              box2 += 1;
              target(angle2);
            }
            else if(label2 == 3)
            {
              box3 += 1;
              target(angle3);
            }
            else if(label2 == 4)
            {
              box4 += 1;
              target(angle4);
            }
            else if(label2 == 5)
            {
              box5 += 1;
              target(angle5);
            }
            else if(label2 == 6)
            {
              box6 += 1;
              target(angle6);
            }
            toggle2 = 0;
          }
        }
      }
    }

    if (label1 != 0 && label2 != 0 && label4 != 0 && label5 != 0 && label6 != 0 && label7 != 0)
    {
      if (digitalRead(button3) == HIGH)
      {
        if (toggle3 == 0)
        {
          toggle3 = 1;
        }
      }
      else
      {
        if (toggle3 == 1)
        {
          angleToggle = 2;
          Serial.println("S T O P !");
        }
      }
    }
    else
    {
      if (digitalRead(button3) == HIGH)
      {
        if (toggle3 == 0)
        {
          toggle3 = 1;
        }
      }
      else
      {
        if (toggle3 == 1)
        {
          if(label3 == 0)
          {
            if(box1 == 0)
            {
              label3 = 1;
              box1 += 1;
              target(angle1);
            }
            else if(box2 == 0)
            {
              label3 = 2;
              box2 += 1;
              target(angle2);
            }
            else if(box3 == 0)
            {
              label3 = 3;
              box3 += 1;
              target(angle3);
            }
            else if(box4 == 0)
            {
              label3 = 4;
              box4 += 1;
              target(angle4);
            }
            else if(box5 == 0)
            {
              label3 = 5;
              box5 += 1;
              target(angle5);
            }
            else if(box6 == 0)
            {
              label3 = 6;
              box6 += 1;
              target(angle6);
            }
            toggle3 = 0;
          }
          else
          {
            if(label3 == 1)
            {
              box1 += 1;
              target(angle1);
            }
            else if(label3 == 2)
            {
              box2 += 1;
              target(angle2);
            }
            else if(label3 == 3)
            {
              box3 += 1;
              target(angle3);
            }
            else if(label3 == 4)
            {
              box4 += 1;
              target(angle4);
            }
            else if(label3 == 5)
            {
              box5 += 1;
              target(angle5);
            }
            else if(label3 == 6)
            {
              box6 += 1;
              target(angle6);
            }
            toggle3 = 0;
          }
        }
      }
    }

    if (label1 != 0 && label2 != 0 && label3 != 0 && label5 != 0 && label6 != 0 && label7 != 0)
    {
      if (digitalRead(button4) == HIGH)
      {
        if (toggle4 == 0)
        {
          toggle4 = 1;
        }
      }
      else
      {
        if (toggle4 == 1)
        {
          angleToggle = 2;
          Serial.println("S T O P !");
        }
      }
    }
    else
    {
      if (digitalRead(button4) == HIGH)
      {
        if (toggle4 == 0)
        {
          toggle4 = 1;
        }
      }
      else
      {
        if (toggle4 == 1)
        {
          if(label4 == 0)
          {
            if(box1 == 0)
            {
              label4 = 1;
              box1 += 1;
              target(angle1);
            }
            else if(box2 == 0)
            {
              label4 = 2;
              box2 += 1;
              target(angle2);
            }
            else if(box3 == 0)
            {
              label4 = 3;
              box3 += 1;
              target(angle3);
            }
            else if(box4 == 0)
            {
              label4 = 4;
              box4 += 1;
              target(angle4);
            }
            else if(box5 == 0)
            {
              label4 = 5;
              box5 += 1;
              target(angle5);
            }
            else if(box6 == 0)
            {
              label4 = 6;
              box6 += 1;
              target(angle6);
            }
            toggle4 = 0;
          }
          else
          {
            if(label4 == 1)
            {
              box1 += 1;
              target(angle1);
            }
            else if(label4 == 2)
            {
              box2 += 1;
              target(angle2);
            }
            else if(label4 == 3)
            {
              box3 += 1;
              target(angle3);
            }
            else if(label4 == 4)
            {
              box4 += 1;
              target(angle4);
            }
            else if(label4 == 5)
            {
              box5 += 1;
              target(angle5);
            }
            else if(label4 == 6)
            {
              box6 += 1;
              target(angle6);
            }
            toggle4 = 0;
          }
        }
      }
    }

    if (label1 != 0 && label2 != 0 && label3 != 0 && label4 != 0 && label6 != 0 && label7 != 0)
    {
      if (digitalRead(button5) == HIGH)
      {
        if (toggle5 == 0)
        {
          toggle5 = 1;
        }
      }
      else
      {
        if (toggle5 == 1)
        {
          angleToggle = 2;
          Serial.println("S T O P !");
        }
      }
    }
    else
    {
      if (digitalRead(button5) == HIGH)
      {
        if (toggle5 == 0)
        {
          toggle5 = 1;
        }
      }
      else
      {
        if (toggle5 == 1)
        {
          if(label5 == 0)
          {
            if(box1 == 0)
            {
              label5 = 1;
              box1 += 1;
              target(angle1);
            }
            else if(box2 == 0)
            {
              label5 = 2;
              box2 += 1;
              target(angle2);
            }
            else if(box3 == 0)
            {
              label5 = 3;
              box3 += 1;
              target(angle3);
            }
            else if(box4 == 0)
            {
              label5 = 4;
              box4 += 1;
              target(angle4);
            }
            else if(box5 == 0)
            {
              label5 = 5;
              box5 += 1;
              target(angle5);
            }
            else if(box6 == 0)
            {
              label5 = 6;
              box6 += 1;
              target(angle6);
            }
            toggle5 = 0;
          }
          else
          {
            if(label5 == 1)
            {
              box1 += 1;
              target(angle1);
            }
            else if(label5 == 2)
            {
              box2 += 1;
              target(angle2);
            }
            else if(label5 == 3)
            {
              box3 += 1;
              target(angle3);
            }
            else if(label5 == 4)
            {
              box4 += 1;
              target(angle4);
            }
            else if(label5 == 5)
            {
              box5 += 1;
              target(angle5);
            }
            else if(label5 == 6)
            {
              box6 += 1;
              target(angle6);
            }
            toggle5 = 0;
          }
        }
      }
    }

    if (label1 != 0 && label2 != 0 && label3 != 0 && label4 != 0 && label5 != 0 && label7 != 0)
    {
      if (digitalRead(button6) == HIGH)
      {
        if (toggle6 == 0)
        {
          toggle6 = 1;
        }
      }
      else
      {
        if (toggle6 == 1)
        {
          angleToggle = 2;
          Serial.println("S T O P !");
        }
      }
    }
    else
    {
      if (digitalRead(button6) == HIGH)
      {
        if (toggle6 == 0)
        {
          toggle6 = 1;
        }
      }
      else
      {
        if (toggle6 == 1)
        {
          if(label6 == 0)
          {
            if(box1 == 0)
            {
              label6 = 1;
              box1 += 1;
              target(angle1);
            }
            else if(box2 == 0)
            {
              label6 = 2;
              box2 += 1;
              target(angle2);
            }
            else if(box3 == 0)
            {
              label6 = 3;
              box3 += 1;
              target(angle3);
            }
            else if(box4 == 0)
            {
              label6 = 4;
              box4 += 1;
              target(angle4);
            }
            else if(box5 == 0)
            {
              label6 = 5;
              box5 += 1;
              target(angle5);
            }
            else if(box6 == 0)
            {
              label6 = 6;
              box6 += 1;
              target(angle6);
            }
            toggle6 = 0;
          }
          else
          {
            if(label6 == 1)
            {
              box1 += 1;
              target(angle1);
            }
            else if(label6 == 2)
            {
              box2 += 1;
              target(angle2);
            }
            else if(label6 == 3)
            {
              box3 += 1;
              target(angle3);
            }
            else if(label6 == 4)
            {
              box4 += 1;
              target(angle4);
            }
            else if(label6 == 5)
            {
              box5 += 1;
              target(angle5);
            }
            else if(label6 == 6)
            {
              box6 += 1;
              target(angle6);
            }
            toggle6 = 0;
          }
        }
      }
    }

    if (label1 != 0 && label2 != 0 && label3 != 0 && label4 != 0 && label5 != 0 && label6 != 0)
    {
      if (digitalRead(button7) == HIGH)
      {
        if (toggle7 == 0)
        {
          toggle7 = 1;
        }
      }
      else
      {
        if (toggle7 == 1)
        {
          angleToggle = 2;
          Serial.println("S T O P !");
        }
      }
    }
    else
    {
      if (digitalRead(button7) == HIGH)
      {
        if (toggle7 == 0)
        {
          toggle7 = 1;
        }
      }
      else
      {
        if (toggle7 == 1)
        {
          if(label7 == 0)
          {
            if(box1 == 0)
            {
              label7 = 1;
              box1 += 1;
              target(angle1);
            }
            else if(box2 == 0)
            {
              label7 = 2;
              box2 += 1;
              target(angle2);
            }
            else if(box3 == 0)
            {
              label7 = 3;
              box3 += 1;
              target(angle3);
            }
            else if(box4 == 0)
            {
              label7 = 4;
              box4 += 1;
              target(angle4);
            }
            else if(box5 == 0)
            {
              label7 = 5;
              box5 += 1;
              target(angle5);
            }
            else if(box6 == 0)
            {
              label7 = 6;
              box6 += 1;
              target(angle6);
            }
            toggle7 = 0;
          }
          else
          {
            if(label7 == 1)
            {
              box1 += 1;
              target(angle1);
            }
            else if(label7 == 2)
            {
              box2 += 1;
              target(angle2);
            }
            else if(label7 == 3)
            {
              box3 += 1;
              target(angle3);
            }
            else if(label7 == 4)
            {
              box4 += 1;
              target(angle4);
            }
            else if(label7 == 5)
            {
              box5 += 1;
              target(angle5);
            }
            else if(label7 == 6)
            {
              box6 += 1;
              target(angle6);
            }
            toggle7 = 0;
          }
        }
      }
    }
    digitalWrite(start, LOW);
    digitalWrite(stop, LOW);
  }

    if (angleToggle == 2)
    {
      if (box1 > 0)
      {
        target2(angle1);
        box1 = 0;
        if (label1 == 1)
        {
          label1 = 0;
        }
        else if (label2 == 1)
        {
          label2 = 0;
        }
        else if (label3 == 1)
        {
          label3 = 0;
        }
        else if (label4 == 1)
        {
          label4 = 0;
        }
        else if (label5 == 1)
        {
          label5 = 0;
        }
        else if (label6 == 1)
        {
          label6 = 0;
        }
        else if (label7 == 1)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box2 > 0)
      {
        target2(angle2);
        box2 = 0;
        if (label1 == 2)
        {
          label1 = 0;
        }
        else if (label2 == 2)
        {
          label2 = 0;
        }
        else if (label3 == 2)
        {
          label3 = 0;
        }
        else if (label4 == 2)
        {
          label4 = 0;
        }
        else if (label5 == 2)
        {
          label5 = 0;
        }
        else if (label6 == 2)
        {
          label6 = 0;
        }
        else if (label7 == 2)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box3 > 0)
      {
        target2(angle3);
        box3 = 0;
        if (label1 == 3)
        {
          label1 = 0;
        }
        else if (label2 == 3)
        {
          label2 = 0;
        }
        else if (label3 == 3)
        {
          label3 = 0;
        }
        else if (label4 == 3)
        {
          label4 = 0;
        }
        else if (label5 == 3)
        {
          label5 = 0;
        }
        else if (label6 == 3)
        {
          label6 = 0;
        }
        else if (label7 == 3)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box4 > 0)
      {
        target2(angle4);
        box4 = 0;
        if (label1 == 4)
        {
          label1 = 0;
        }
        else if (label2 == 4)
        {
          label2 = 0;
        }
        else if (label3 == 4)
        {
          label3 = 0;
        }
        else if (label4 == 4)
        {
          label4 = 0;
        }
        else if (label5 == 4)
        {
          label5 = 0;
        }
        else if (label6 == 4)
        {
          label6 = 0;
        }
        else if (label7 == 4)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box5 > 0)
      {
        target2(angle5);
        box5 = 0;
        if (label1 == 5)
        {
          label1 = 0;
        }
        else if (label2 == 5)
        {
          label2 = 0;
        }
        else if (label3 == 5)
        {
          label3 = 0;
        }
        else if (label4 == 5)
        {
          label4 = 0;
        }
        else if (label5 == 5)
        {
          label5 = 0;
        }
        else if (label6 == 5)
        {
          label6 = 0;
        }
        else if (label7 == 5)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box6 > 0)
      {
        target2(angle6);
        box6 = 0;
        if (label1 == 6)
        {
          label1 = 0;
        }
        else if (label2 == 6)
        {
          label2 = 0;
        }
        else if (label3 == 6)
        {
          label3 = 0;
        }
        else if (label4 == 6)
        {
          label4 = 0;
        }
        else if (label5 == 6)
        {
          label5 = 0;
        }
        else if (label6 == 6)
        {
          label6 = 0;
        }
        else if (label7 == 6)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
    }    
   
    if (box1 == 3 || box2 == 3 || box3 == 3 || box4 == 3 || box5 == 3 || box6 == 3)
    {
      angleToggle = 3;
    }

    if (angleToggle == 3)
    {
      if (box1 == 3)
      {
        target2(angle1);
        box1 = 0;
        if (label1 == 1)
        {
          label1 = 0;
        }
        else if (label2 == 1)
        {
          label2 = 0;
        }
        else if (label3 == 1)
        {
          label3 = 0;
        }
        else if (label4 == 1)
        {
          label4 = 0;
        }
        else if (label5 == 1)
        {
          label5 = 0;
        }
        else if (label6 == 1)
        {
          label6 = 0;
        }
        else if (label7 == 1)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box2 == 3)
      {
        target2(angle2);
        box2 = 0;
        if (label1 == 2)
        {
          label1 = 0;
        }
        else if (label2 == 2)
        {
          label2 = 0;
        }
        else if (label3 == 2)
        {
          label3 = 0;
        }
        else if (label4 == 2)
        {
          label4 = 0;
        }
        else if (label5 == 2)
        {
          label5 = 0;
        }
        else if (label6 == 2)
        {
          label6 = 0;
        }
        else if (label7 == 2)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box3 == 3)
      {
        target2(angle3);
        box3 = 0;
        if (label1 == 3)
        {
          label1 = 0;
        }
        else if (label2 == 3)
        {
          label2 = 0;
        }
        else if (label3 == 3)
        {
          label3 = 0;
        }
        else if (label4 == 3)
        {
          label4 = 0;
        }
        else if (label5 == 3)
        {
          label5 = 0;
        }
        else if (label6 == 3)
        {
          label6 = 0;
        }
        else if (label7 == 3)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box4 == 3)
      {
        target2(angle4);
        box4 = 0;
        if (label1 == 4)
        {
          label1 = 0;
        }
        else if (label2 == 4)
        {
          label2 = 0;
        }
        else if (label3 == 4)
        {
          label3 = 0;
        }
        else if (label4 == 4)
        {
          label4 = 0;
        }
        else if (label5 == 4)
        {
          label5 = 0;
        }
        else if (label6 == 4)
        {
          label6 = 0;
        }
        else if (label7 == 4)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box5 == 3)
      {
        target2(angle5);
        box5 = 0;
        if (label1 == 5)
        {
          label1 = 0;
        }
        else if (label2 == 5)
        {
          label2 = 0;
        }
        else if (label3 == 5)
        {
          label3 = 0;
        }
        else if (label4 == 5)
        {
          label4 = 0;
        }
        else if (label5 == 5)
        {
          label5 = 0;
        }
        else if (label6 == 5)
        {
          label6 = 0;
        }
        else if (label7 == 5)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
      else if (box6 == 3)
      {
        target2(angle6);
        box6 = 0;
        if (label1 == 6)
        {
          label1 = 0;
        }
        else if (label2 == 6)
        {
          label2 = 0;
        }
        else if (label3 == 6)
        {
          label3 = 0;
        }
        else if (label4 == 6)
        {
          label4 = 0;
        }
        else if (label5 == 6)
        {
          label5 = 0;
        }
        else if (label6 == 6)
        {
          label6 = 0;
        }
        else if (label7 == 6)
        {
          label7 = 0;
        }
        angleToggle = 1;
      }
    }


    

    

    targetDeg = targets[0];

    if (targetDeg != angle0 && time == 0)
    {
      time = 30;
    }

    if (time != 0)
    {
      if (abs(error) > 2 && distance > 3 )
      {
        digitalWrite(start, HIGH);
        digitalWrite(stop, HIGH);
        doMotor((control > 0) ? HIGH : LOW, min(abs(control), 255));
      }
      else
      {
        if (time > 1)
        {
          time -= 1;
          digitalWrite(start, LOW);
          digitalWrite(stop, LOW);
        }
        else if (time > 0)
        {
          time -= 1;
          digitalWrite(start, LOW);
          digitalWrite(stop, LOW);
          targets[0] = targets[1];
          targets[1] = targets[2];
          targets[2] = targets[3];
          targets[3] = targets[4];
          targets[4] = targets[5];
          targets[5] = angle0;
        }
      }
    }
  
  Serial.print("error : ");
  Serial.print(error);
  Serial.print(" / targetDeg : ");
  Serial.print(targetDeg);
  Serial.print(" / targets : ");
  Serial.print(targets[0]);
  Serial.print("/");
  Serial.print(targets[1]);
  Serial.print("/");
  Serial.print(targets[2]);
  Serial.print("/");
  Serial.print(targets[3]);
  Serial.print("/");
  Serial.print(targets[4]);
  Serial.print("/");
  Serial.print(targets[5]);
  Serial.print(" / time : ");
  Serial.print(time);
  Serial.print(" / angle0 : ");
  Serial.print(angle0);
  Serial.print(" / distance : ");
  Serial.println(distance);
  
}

void target(int A)
{
  if (targets[0] == angle0)
  {
    targets[0] = A;
  }
  else if (targets[1] == angle0)
  {
    targets[1] = A;
  }
  else if (targets[2] == angle0)
  {
    targets[2] = A;
  }
  else if (targets[3] == angle0)
  {
    targets[3] = A;
  }
  else if (targets[4] == angle0)
  {
    targets[4] = A;
  }
  else if (targets[5] == angle0)
  {
    targets[5] = A;
  }
}

void target2(int A)
{
  if (targets[0] == angle0)
  {
    targets[0] = A + 180;
  }
  else if (targets[1] == angle0)
  {
    targets[1] = A + 180;
  }
  else if (targets[2] == angle0)
  {
    targets[2] = A + 180;
  }
  else if (targets[3] == angle0)
  {
    targets[3] = A + 180;
  }
  else if (targets[4] == angle0)
  {
    targets[4] = A + 180;
  }
  else if (targets[5] == angle0)
  {
    targets[5] = A + 180;
  }
}
