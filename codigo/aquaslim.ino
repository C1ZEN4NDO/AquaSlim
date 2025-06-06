#include <WiFi.h>
#include <PubSubClient.h>

// === Configuração da rede Wi-Fi ===
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// === Configuração do broker MQTT ===
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// === Definição dos pinos ===
#define LED_PIN 2           // LED que simula a bomba (atuador)
#define BUTTON_PIN 4        // Botão físico (sensor)

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Ativa resistor interno de pull-up

  // Conexão com o Wi-Fi
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWi-Fi conectado com IP: " + WiFi.localIP().toString());

  // Configuração do servidor MQTT e função de callback
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  client.setSocketTimeout(5);  // evita travamentos

  reconnect();

  // Publicação de teste ao iniciar
  client.publish("botao/estado", "teste direto do setup");
  Serial.println("Mensagem de teste enviada ao MQTT.");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT... ");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
      client.subscribe("led/comando");  // Se inscreve no tópico para receber comandos do Node-RED
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" -> nova tentativa em 2 segundos");
      delay(2000);
    }
  }
}

// Função callback: executada sempre que uma nova mensagem MQTT for recebida
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Recebido [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  // Comando para o LED (atuador físico)
  if (String(topic) == "led/comando") {
    if (message == "on") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ligado.");
    } else if (message == "off") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED desligado.");
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  static bool lastState = HIGH;
  bool currentState = digitalRead(BUTTON_PIN);

  // Verifica mudança de estado do botão
  if (lastState != currentState) {
    Serial.print("Estado do botão mudou: ");
    Serial.println(currentState);
  }

  // Quando o botão for pressionado (transição HIGH → LOW)
  if (lastState == HIGH && currentState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);

    // Publica no tópico do botão
    client.publish("botao/estado", "pressionado");

    Serial.println("Botão pressionado → mensagens enviadas aos tópicos MQTT.");

    delay(100);  // debounce
  }

  lastState = currentState;
}
