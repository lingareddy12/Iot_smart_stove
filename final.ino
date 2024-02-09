#include<Wire.h>
#include <LiquidCrystal_I2C.h>
#include<Keypad.h>
#include <Servo.h>
Servo s;

const int row=4;
 const int column=4;
char keys[row][column]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
       };
byte pin_rows[row]={7,6,5,4};
byte pin_columns[column]={2,3,8,9};
Keypad keypad =Keypad(makeKeymap(keys),pin_rows,pin_columns,row,column);

char temp;
String t;  
int fan_pin=10;
int i=0; 
int sound_pin=A2;
int whitsles; 
int buzz_pin=13; 
int sound_data;
int timer;
int j=0; 
int servo_pin=12;
int gas_pin=A0;
int gas_data;


LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void whistle_count()
{       
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Enter Whistles : "); 
      delay(1000);
      while(1)
      {     
       // detect_gas();
        temp=keypad.getKey(); 
        if (temp =="D" || temp=='D'){

              lcd.clear();
              lcd.print("Exiting..."); 
              delay(2000);
              lcd.clear();
             break;
        }

        else if(temp!=NO_KEY)
        {
              lcd.clear();
              t=String(temp);
              whitsles = t.toInt();
              lcd.setCursor(1,0);
              lcd.print("Whitsles = ");
              lcd.print(whitsles);
              Serial.print("Whistles=");
              Serial.print(whitsles);
              delay(1000);
              Runner();
        } 
        }
}   


 void Runner()
{       
 
          while (1)
         { 
           lcd.clear();
           lcd.print("Counting...");
           lcd.setCursor(1,1);
           lcd.print(i); 
           delay(500);
           if(i==whitsles)
             {  
               lcd.clear();
               lcd.print("Count");
               lcd.setCursor(1,1);
               lcd.print("Reached");
               buzzer();  
               servo_rotate();
                 Serial.write('1');  
               break;
            }
           else
            {   
              //detect_gas();
                sound_data= analogRead(sound_pin);
                Serial.println(sound_data);
               if(sound_data>300)
                  {
                     i=i+1;
                     lcd.clear();
                     lcd.print("Whitsle Detected...");
                     delay(1000);  
                  }
            } 
        } 
    
}    

void time_count()
{       
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Enter time : "); 
      delay(1000);
      while(1)
      {     
       // detect_gas();
        temp=keypad.getKey(); 
        if (temp =="D" || temp=='D'){

              lcd.clear();
              lcd.print("Exiting..."); 
              delay(1000);
              lcd.clear();
             break;
        }

        else if(temp!=NO_KEY)
        {
              lcd.clear();
              t=String(temp);
              timer = t.toInt();
              lcd.setCursor(1,0);
              lcd.print("Time = ");
              lcd.print(timer);
              Serial.print("time=");
              Serial.print(timer);
              delay(1000);
              Timer();
        } 
        }
}   

 void Timer()
{       
 
          while (1)
         {  
         // detect_gas();
           lcd.clear();
           if(j==timer)
             {  
               lcd.clear();
               lcd.print("Time");
               lcd.setCursor(1,1);
               lcd.print("Reached");
                 servo_rotate();
                buzzer(); 
                Serial.write('2');
               break;
            }
           else
            {    
             // lcd.clear();
              lcd.print("Coutdown......");
              for(int p=0;p<60;p++)
              {
              delay(1000);
             // detect_gas(); 
              }
               lcd.clear();
               lcd.print("Time left=");
               lcd.setCursor(1,1);
               lcd.print(timer-1);
              j=j+1;
            } 
        } 
    
} 

void buzzer()
{
       digitalWrite(buzz_pin,HIGH);    
       delay(2000);
       digitalWrite(buzz_pin,LOW);
} 

void detect_gas()
{
  gas_data=analogRead(gas_pin);
  Serial.println(gas_data);
  if(gas_data>200)
  { 
     Serial.println("Gas data");
    Serial.println(gas_data);
   // Serial.write('3');
    digitalWrite(fan_pin,HIGH);
     buzzer();
  }
}
void servo_rotate()
{
  s.write(180);
}
  void setup() 
{ 
  Serial.begin (9600); 
  pinMode(sound_pin,INPUT);
  pinMode(buzz_pin,OUTPUT);
  digitalWrite(fan_pin,LOW);
   pinMode(fan_pin,OUTPUT);
  pinMode(gas_pin,INPUT);
  s.attach(servo_pin);
  lcd.init();
  lcd.backlight(); 
  lcd.setCursor(1,0); 
  lcd.print("SMART STOVE");
    lcd.setCursor(1,1); 
  lcd.print("SELECT MODE");
  delay(1000);
  lcd.clear();
   lcd.setCursor(1,0); 
  lcd.print("press *  for");
    lcd.setCursor(1,1); 
  lcd.print("selecting mode"); 
  delay(1000);
}


void loop() { 
 mainLoop : 
          s.write(0); 
        //  detect_gas();
         // delay(1000);
       lcd.clear();
         char customKey = keypad.getKey(); 
         if (customKey)
         {  
          lcd.clear();
           lcd.setCursor(1,0);
          lcd.print("Select Mode : ");
         Serial.println("enter mode:");
         lcd.print(customKey);
         Serial.print(customKey);
         delay(1000);             
            if (customKey == 'A' || customKey=="A")
            {
                lcd.clear();      
                lcd.print("Mode A :");
                Serial.println("mode A");
                lcd.setCursor(4,1);
                lcd.print("Counter");
                delay(1000);
                lcd.clear();
                lcd.print("Counter");
                delay(1000);
               whistle_count();
               lcd.clear();
            }

            if (customKey == 'B'){

                lcd.clear();      
                lcd.print("Mode B :");
                Serial.print("mode B");
                lcd.setCursor(4,1);
                lcd.print("Remainder");
                delay(1000);
                 time_count();
                
            }
            if (customKey=='*'){

              lcd.clear();
              lcd.print("A-for cooker mode");
              lcd.setCursor(1,1);
              lcd.print("B-for timer mode");
              delay(1000);
              lcd.clear();
          }

            if (customKey=='#'){

              lcd.clear();
              lcd.print("Programed By...");
              lcd.setCursor(1,1);
              lcd.print(" Team eureka");
              delay(3000);
              lcd.clear();
          }
      
         
         // lcd.clear();
          goto mainLoop;
       }
     }
