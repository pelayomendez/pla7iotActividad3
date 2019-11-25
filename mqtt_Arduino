/*
 * MKRENV Test
 * 
 * Lectura de los sensores de:
 * - Temperatura
 * - Humedad
 * - Presión
 * - UVA
 * - UVB
 * - Indice UV
 */

#include <Arduino_MKRENV.h>

#include <ArduinoMqttClient.h>
#include <WiFi101.h>

WiFiClient wifiClient;
char ssid[] = "Can Pelma"; 
char pass[] = "Olaya2014";
int status = WL_IDLE_STATUS;

MqttClient mqttClient(wifiClient);
const char broker[] = "130.61.99.169";
int        port     = 1883;
bool mqttclientconnected = false;

// Variable configuration HOMIE:

String HOMIE_VERSION = "3.0";
String DEVICE_NAME = "mkr10000";
String DEVICE_STATE = "ready";
String NODE_NAME = "envshield";

// Topics para publicar la información:

String topic_device = "homie/" + DEVICE_NAME + "/";
String topic_node   = topic_device + NODE_NAME + "/";

String topic_node_sensor_temperatura  = topic_node + "temperatura";
String topic_node_sensor_humedad      = topic_node + "humedad";
String topic_node_sensor_presion      = topic_node + "presion";
String topic_node_sensor_uva          = topic_node + "uva";
String topic_node_sensor_uvb          = topic_node + "uvb";
String topic_node_sensor_indiceUV     = topic_node + "indiceUV";

unsigned long previousMillis = 0;

void setup() {
  
  // Esperamos que el Serial este conectado:
  Serial.begin(9600);
  while (!Serial);
  
  // Conectamos el shield
  Serial.println("Inicializando MKR ENV shield");
  if (!ENV.begin()) {
    Serial.println("Error inicializando MKR ENV shield");
    while (1);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }

  Serial.println("You're connected to the network");

  // Fijamos un Id para que el servidor MQTT nos reconozca:
  //mqttClient.setId("mkr10000");
  // Le damos las credenciales del servidor que hemos configurado anteriormente:
  //mqttClient.setUsernamePassword("", "9");
  // Conectamos al broker
  while (!mqttclientconnected) {
    mqttclientconnected = mqttClient.connect(broker, port);
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    
    delay(10000);
  }

  publishGenericHomieTopics();

  Serial.println("Ready to go!");
}

void publishGenericHomieTopics() {
  publishTopic(topic_device + "$homie", HOMIE_VERSION);
  publishTopic(topic_device + "$name", DEVICE_NAME);
  publishTopic(topic_device + "$state", DEVICE_STATE);
  publishTopic(topic_device + "$nodes", NODE_NAME);

  publishTopic(topic_node + "$name", NODE_NAME);
  publishTopic(topic_node + "$properties", "temperatura");
  publishTopic(topic_node + "$properties", "humedad");
  publishTopic(topic_node + "$properties", "presion");
  publishTopic(topic_node + "$properties", "uva");
  publishTopic(topic_node + "$properties", "uvb");
  publishTopic(topic_node + "$properties", "temperatura");
}


void publishTopic(String topic, String value) {
  
    Serial.print("Sending message to topic: ");
    Serial.print(topic);
    Serial.print(" Value: ");
    Serial.println(value);
    
    mqttClient.beginMessage(topic);
    mqttClient.print(value);
    mqttClient.endMessage();
}

void loop()
{

  // Mandamos la señal de KEEP_ALIVE al broker para que no nos desconecte:
  mqttClient.poll();

  // Vamos a publicar el valor de los sensores en el servidoir MQTT cada 5 segundos
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000) {
    
    previousMillis = currentMillis;
  
    float temperatura = ENV.readTemperature();
    float humedad     = ENV.readHumidity();
    float presion     = ENV.readPressure();
    float uva         = ENV.readUVA();
    float uvb         = ENV.readUVB();
    float indiceUV     = ENV.readUVIndex();

    // Imprimimos en el serial el valor de los sensores:
    
    Serial.print("Temperatura = ");
    Serial.print(temperatura);
    Serial.println(" °C");
    
    publishTopic(topic_node_sensor_temperatura, String(temperatura));

    Serial.print("Humedad    = ");
    Serial.print(humedad);
    Serial.println(" %");
    
    publishTopic(topic_node_sensor_humedad, String(humedad));
  
    Serial.print("Presión    = ");
    Serial.print(presion);
    Serial.println(" kPa");
    
    publishTopic(topic_node_sensor_presion, String(presion));
  
    Serial.print("UVA         = ");
    Serial.println(uva);
    
    publishTopic(topic_node_sensor_uva, String(uva));
  
    Serial.print("UVB         = ");
    Serial.println(uvb);
    
    publishTopic(topic_node_sensor_uvb, String(uvb));
  
    Serial.print("Indice UV    = ");
    Serial.println(indiceUV);

    publishTopic(topic_node_sensor_indiceUV, String(indiceUV));
    
    Serial.println();

  }

}
