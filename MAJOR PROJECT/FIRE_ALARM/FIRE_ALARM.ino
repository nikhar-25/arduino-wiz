 #include <DHT.h>  
 #include <ESP8266WiFi.h>  
 #include <WiFiClient.h>  
 #include <ThingSpeak.h>  
 #define DHTPIN D3  
 #define DHTTYPE DHT11  
 DHT dht(DHTPIN, DHTTYPE); 
 const char* ssid = "MAHENDRA";  
 const char* password = "9456944904";  
 WiFiClient client;  
 unsigned long myChannelNumber = 1255578;  
 const char * myWriteAPIKey = "MSHDGDAVJKM18ZSZ";  
 uint8_t Temperature;
 int flamePin=D2; 
 void setup()  
 {  
  Serial.begin(115200);  
  dht.begin();  
  delay(10);
    
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);
  pinMode(flamePin,INPUT);  
 }  
 void loop()   
 {  
  static boolean data_state = false;  
  Temperature = dht.readTemperature();
  int Flame=digitalRead(flamePin);
  if(Flame==HIGH){
  Serial.print("Temperature Value is :");  
  Serial.print(Temperature);  
  Serial.println("C");
  Serial.print(Flame);  
  Serial.println("Fire is Not Dectected");
  }
  else if(Flame==LOW)
  {
  Serial.print("Temperature Value is :");  
  Serial.print(Temperature);  
  Serial.println("C");
  Serial.print(Flame);  
  Serial.println("Fire is Dectected");
  }
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1. 
  Serial.println("Uploading Values");  
  if( data_state )  
  {  
   ThingSpeak.writeField(myChannelNumber, 1, Temperature, myWriteAPIKey);  
   data_state = false;  
  }  
  else  
  {  
   ThingSpeak.writeField(myChannelNumber, 2, Flame, myWriteAPIKey);  
   data_state = true;  
  }  
  delay(10000); // ThingSpeak will only accept updates every 10 seconds.  
 }  
