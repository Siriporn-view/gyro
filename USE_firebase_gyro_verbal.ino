#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#define WIFI_SSID "WiFiTUSouth"   
#define WIFI_PASSWORD ""  
#define FIREBASE_HOST "https://untrasonic-3320b-default-rtdb.firebaseio.com"
#define FIREBASE_KEY "HkF1kNygfunBltIerb6He01fKuL853H0CMQeCqdT"

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int valx , valy , valz;
char rd;
int prevVal;
int ledR = 16 ;
int ledG = 14 ;
int ledY = 12 ;
int pin11 = 5 , pin10 = 4 ;
int val1 , val2 ;
int valgy1 = 0 , valgy2 = 0;
int A=0;
int B=0;
FirebaseData firebaseData;

void setup() {
    connectWifi();
    Wire.begin();
    Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
    Serial.begin(9600);
    Serial.println("Initialize MPU");
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
}

void loop() {
  
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  valx = map(ax, -17000, 17000, 0, 179);
  valy = map(ay, -17000, 17000, 0, 179);
  valz = map(az, -17000, 17000, 0, 179);
  Serial.print("axis x = ") ;
  Serial.print(valx) ;
  Serial.print(" axis y = ") ;
  Serial.print(valy) ;
  Serial.print(" axis z = ") ;
  Serial.println(valz) ;



if(((valz<90)||(valz>110))||((valy<80)||(valy>100)))
{
  A=1 ;
  }
  else
  {
    A=0 ;
  }

  
     
    if(Firebase.setInt(firebaseData, "/Int_A", A   )) {  
       // ส่งค่าตัวแปร A ในยัง firebase  ชื่อ พาส  Int A  พาสย่อยชื่อ Value  แสดงค่า ตัวแปร A
        Serial.print("A=");          // แสดงผลตัวแปร A ทาง serialmonitor
        Serial.println(A); 
    } else {
        Serial.println("Error : " + firebaseData.errorReason());
    }
       delay(1000);
    // Do something
     
     }


void connectWifi() {
    Serial.begin(9600);
    Serial.println(WiFi.localIP());
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
}
