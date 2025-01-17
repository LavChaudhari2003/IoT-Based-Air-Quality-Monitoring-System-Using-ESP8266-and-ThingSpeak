
#include<MQ2.h>
#include<MQ135.h>
#include<dht.h>
#include "WiFiEsp.h"
//#include "secrets.h"
#include "ThingSpeak.h" 

char ssid[] = "Lavchaudhari 101003";   
char pass[] = "Lav@1234";  
int keyIndex = 0;            // network key Index number (needed only for WEP)
WiFiEspClient  client;

#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"

SoftwareSerial Serial1(6, 7); // RX, TX
#define ESP_BAUDRATE  19200
#else
#define ESP_BAUDRATE  115200
#endif

unsigned long myChannelNumber = 1915100;
const char * myWriteAPIKey = "8Q850T10ZSGOVAGS";

// Initialize our values
float number1;   //CO2
float number2;   //temerature
float number3;   //humidity
float number4;   //Co
float number5;   //LPG
float number6;   //smoke
String myStatus = "";
#define CO2_pin A0
#define DHT_pin A1
#define MQ2_pin A2
MQ135 CO2 = MQ135(CO2_pin);
dht DHT;
MQ2 mq2_data(MQ2_pin);
void setup() {
  //Initialize serial and wait for port to open
  Serial.begin(115200);  // Initialize serial
  while(!Serial){
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  // initialize serial for ESP module  
  setEspBaudRate(ESP_BAUDRATE);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }

  Serial.print("Searching for ESP8266..."); 
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
  Serial.println("found it!");
   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
   mq2_data.begin();
  number1 = CO2.getPPM();
  int dht_read = DHT.read11(DHT_pin);
  number2=DHT.temperature;
  number3=DHT.humidity;
  number4 = mq2_data.readCO();
  number5 = mq2_data.readLPG();
  number6 = mq2_data.readSmoke();
  delay(5000);
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  // set the fields with the values
  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  ThingSpeak.setField(3, number3);
  ThingSpeak.setField(4, number4);
  ThingSpeak.setField(5, number5);
  ThingSpeak.setField(6, number6);

  // figure out the status message
  if(number1 > number2){
    myStatus = String("field1 is greater than field2"); 
  }
  else if(number1 < number2){
    myStatus = String("field1 is less than field2");
  }
  else{
    myStatus = String("field1 equals field2");
  }
  
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  Serial.print("CO2:");
  Serial.println(number1);
  Serial.print("Temperature:");
  Serial.println(number2);
  Serial.print("Humidity:");
  Serial.println(number3);
  Serial.print("CO:");
  Serial.println(number4);
  Serial.print("LPG:");
  Serial.println(number5);
  Serial.print("Smoke:");
  Serial.println(number6);
  delay(1000);


  // change the values
  number1 = CO2.getPPM();
  int y = DHT.read11(DHT_pin);
  number2=DHT.temperature;
  number3=DHT.humidity;
  number4 = mq2_data.readCO();
  number5 = mq2_data.readLPG();
  number6 = mq2_data.readSmoke();
  delay(3000); // Wait 30 seconds to update the channel again
}

// This function attempts to set the ESP8266 baudrate. Boards with additional hardware serial ports
// can use 115200, otherwise software serial is limited to 19200.

void setEspBaudRate(unsigned long baudrate){
  long rates[6] = {115200,74880,57600,38400,19200,9600};

  Serial.print("Setting ESP8266 baudrate to ");
  Serial.print(baudrate);
  Serial.println("...");

  for(int i = 0; i < 6; i++){
    Serial1.begin(rates[i]);
    delay(100);
    Serial1.print("AT+UART_DEF=");
    Serial1.print(baudrate);
    Serial1.print(",8,1,0,0\r\n");
    delay(100);  
  }
    
  Serial1.begin(baudrate);
}
