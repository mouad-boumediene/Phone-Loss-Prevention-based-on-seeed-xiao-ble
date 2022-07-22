#include <ArduinoBLE.h>
 
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service
 
// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("Connection", BLERead | BLEWrite);
 
const int ledPin = LED_BUILTIN; // pin to use for the LED
const int buzzer = 9; //buzzer to pin 9

const int password = 55;
bool state = false;
 
void setup() {
  Serial.begin(9600);
 
  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
 
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
 
    while (1);
  }
 
  // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(ledService);
 
  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);
 
  // add service
  BLE.addService(ledService);
 
  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);
 
  // start advertising
  BLE.advertise();
 
  Serial.println("BLE LED Peripheral");
}
 
void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();
  digitalWrite(LEDG, HIGH); // changed from LOW to HIGH     
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDB, HIGH);
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
 
    // while the central is still connected to peripheral:
  while (central.connected()) {
     Serial.println(state); 
    
    if (state == false)
    {
      digitalWrite(LEDR, HIGH); // changed from HIGH to LOW
      digitalWrite(LEDB, LOW); // changed from HIGH to LOW
    }
    
        if (switchCharacteristic.written()) {
          if (switchCharacteristic.value()) {
            if(switchCharacteristic.value()== password)
            {
            state = true;
            digitalWrite(LEDB, HIGH); // changed from HIGH to LOW
            delay(200); 
            digitalWrite(LEDG, LOW);
            delay(200); 
            digitalWrite(LEDG, HIGH);
            delay(200); 
            digitalWrite(LEDG, LOW);
          }
        }
      }
      
 
    // when the central disconnects, print it out:
    
  }
  if (state == true){
    Serial.print(F("You Lost Your Device"));  
    digitalWrite(LEDG, HIGH); // changed from LOW to HIGH     
    digitalWrite(LEDR, LOW);
    for (int i = 0; i <= 10; i++) {
    tone(buzzer, 2000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
                                  }
    state = false;
    switchCharacteristic.writeValue(0);
    }
    
  }
  }
