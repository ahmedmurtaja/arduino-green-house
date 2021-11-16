#include <DHT.h>
#include <DHT_U.h>



#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Constants
#define DHTPIN 8// what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
 

#define tempPin  A1    // temperature sensor 
int pos = 0;                         // position starting on 0
int motor=9;
int fan=13;
#define sensorpin A2 // for analog soil sensor
int moisture;  
int moisturepercent;
void setup() {
  pinMode(motor,OUTPUT);
    pinMode(fan,OUTPUT);

  Serial.begin(9600);
  dht.begin();                                               
   lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {


  //-----------------soil sensor---------------------------//
  moisture = analogRead(sensorpin); // Read moisture sensor value  -------> 0-1024         400(completely wet)
    moisturepercent= map(moisture, 0, 1023, 0, 100); // percent for lcd
  Serial.println(moisture);
  //activating the motor if moisture is below 400
  if(moisture > 400)  
  {  
  analogWrite(motor,0);    
  }
  else if (moisture <= 400)  
  {
   analogWrite(motor,255);    

  }
  //---------------------DHT sensor-----------------------//
  // delay(2000);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("Temp: ");
    Serial.print(temp);
   Serial.println(" Celsius");
    lcd.clear();
//     
lcd.setCursor(0, 0);
 lcd.print("soil: ");
         lcd.print(moisture);
         lcd.setCursor(0, 1);

         lcd.print("Temp:");
         lcd.print(temp);

          delay(1500);
//
if(temp > 27)  
  {  
  analogWrite(fan,255);    
  }
  else if (temp <= 27)  
  {
   analogWrite(fan,0);    

  }
   // delay(10000); //Delay 2 sec.
  //----------------------temp sensor and servo------------//
//  float value = analogRead(tempPin);
//  float tempr = (value * 500) / 1024;                             // calc of temperature in celcius
//  Serial.print("Temperature: ");
//  Serial.print(tempr);
//  Serial.print("*C");
//  Serial.println();                                               // it'll show in the serial monitor  
//  
//  if (temp <= 40){ //if (temp <= 40) --> for dht sensor
//    myservo.attach(9);
//    myservo.write(pos);                                             // stops the servo motor
//    for (pos = 0; pos >= 180; pos += 1){                            // go forward 180 degrees
//    myservo.write(pos);
//    delay(20);
//  }
    
 // }
//  else if (temp >= 40){                                          // greater than 40
//    myservo.attach(9);
//    myservo.write(pos);                                           // position for the servo to turn
//   
//  for (pos = 180; pos <= 0; pos -= 1) {                           // go backward 180 degrees
//    myservo.write(pos);
//    delay(20);
//  }
//  }
//   delay(200); 
//   

  
 
}
