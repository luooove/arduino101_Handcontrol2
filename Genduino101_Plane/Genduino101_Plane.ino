
//这是莱昂纳多一侧的程序
#include <Keyboard.h>
int up = 2, down = 3, left = 4, right = 5, fire = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void senddata()
{
  if ((digitalRead(up) == 1))
  {
    Keyboard.press('w');
    Serial.println("up");
  }
  else if ((digitalRead(down) == 1))
  {
    Keyboard.press('s');
    Serial.println("down");
  }
  else if ((digitalRead(left) == 1))
  {
    Keyboard.press('a');
    Serial.println("left");
  }
  else if ((digitalRead(right) == 1))
  {
    Keyboard.press('d');
    Serial.println("right");
  }
   else if ((digitalRead(fire) == 1))
  {
    Keyboard.press('j');
    Serial.println("fire");
  }
  
  else
  {
    Keyboard.releaseAll();
    Serial.println("releaseAll");
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  senddata();
  delay(10);
}
