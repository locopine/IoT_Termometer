# IoT_Termometer
IoT termometer using NodeMCU, DHT sensor and MQTT

Components useds in this project:
  - ESP8266 NodeMCU ESP12-E;
  - DHT11;
  - 3x Jumpers;
  - Smartphone Android.

Circuit description: 
  1 - Connect DHT VCC in 3v3 of NODEMCU;
  2 - DHT GND in GND of NODEMCU;
  3 - DHT data signal in D3 port of NODEMCU (if use other port, change the code);
  [![iot-termometer-circuit.jpg](https://i.postimg.cc/PrbbXv5H/iot-termometer-circuit.jpg)](https://postimg.cc/rKmRgm4Z)

Code changes:
  1 - Change the SSID and password of the wifi network;
  2 - Change MQTT broker if you need use some different of the mqtt.eclipse.org;
  3 - Change topics name to some most personal.
  
Smartphone config:
  1 - Install MQTT-Dashboard app in Google Play Store;
  2 - Add Broker in "+" icon;
  3 - Set your MQTT broker, the code is set for tcp://mqtt.eclipse.org in 1883 port. 
  4 - Active QoS 1 in settings of broker on app;
  5 - After of setting the MQTT Broker, enter in this;
  6 - Add tile in "+" simbol, choice standard and type text;
  7 - Define a name of the tile and in subscribe topic, insert the topic of the code, example "lab/temp";
  8 - Repeat this proccess for add topic of humidity.
  9 - Fine, revise your settings of MQTT broker and topics names and enjoy!
