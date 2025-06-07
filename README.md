
# AquaSlim - Monitoramento Inteligente da Qualidade da Água

Este repositório contém o projeto desenvolvido para a disciplina de **Objetos Inteligentes Conectados**.

## ✅ Descrição

Sistema de monitoramento da qualidade da água utilizando sensor de turbidez e acionamento automático de uma bomba (simulada com LED), com comunicação via protocolo MQTT (simulada).

## ✅ Componentes

- ESP32
- Sensor de turbidez (simulado com potenciômetro)
- LED (simula a bomba d’água)
- Broker MQTT (HiveMQ)
- Node-RED para visualização e controle

## ✅ Como reproduzir

1. Configure seu ESP32 com o código disponível em `/codigo/`.
2. Monte o circuito conforme o diagrama na pasta `/diagramas/`.
3. Configure seu Node-RED com os fluxos MQTT correspondentes aos tópicos utilizados.
4. Ao detectar turbidez elevada, o LED será ativado e uma mensagem será publicada no tópico MQTT.
5. O botão físico também pode ser usado para envio de eventos simulando interferências externas.

## 📡 Comunicação e Protocolos

- Protocolo: MQTT
- Broker: broker.hivemq.com
- Porta: 1883
- Tópicos:
  - `aquaslim/sensors/turbidity` (publicações do sensor)
  - `aquaslim/actuators/pump` (comando para a bomba)
- Formato das mensagens: JSON

## ✅ Estrutura do Repositório

- `/codigo/` — Código-fonte para ESP32.
- `/diagramas/` — Diagrama esquemático do circuito.
- `/documentacao/` — Artigo completo do projeto.
- `/imagens/` — Capturas de tela e montagem real.
- `README.txt` — Você está aqui.

## ✅ Autor

- Guilherme H. Cizenando
