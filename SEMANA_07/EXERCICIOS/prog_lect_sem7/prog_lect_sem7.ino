#include <WiFi.h>
#define blue 1
#define red 2

const char *ssid = "SHARE-RESIDENTE";
const char *password = "Share@residente";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

int value = 0;

void loop() {
  WiFiClient client = server.available();


  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {

          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<!DOCTYPE html><html lang='en'><head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Document</title> <style>* { margin: 0; padding: 0; box-sizing: border-box; font-family: cursive; } body { height: 100vh; display: flex; align-items: center; justify-content: center; background: #f7f7f7; } main { display: flex; flex-direction: column; gap: 5px; } h1 { text-align: center; } hr { font-weight: bold; height: 3px; background: black; margin-bottom: 10px; } .game { display: grid; grid-template-columns: 1fr 1fr 1fr; } .game button { width: 100px; height: 100px; margin: 5px; cursor: pointer; font-size: 50px; background: #f7f7f7; } </style></head><body> <main> <h1>JOGO DA VELHA</h1> <hr /> <div class='game'> <button data-i='1'></button> <button data-i='2'></button> <button data-i='3'></button> <button data-i='4'></button> <button data-i='5'></button> <button data-i='6'></button> <button data-i='7'></button> <button data-i='8'></button> <button data-i='9'></button> </div> <h2 class='currentPlayer'></h2> </main> <script> const currentPlayer = document.querySelector('.currentPlayer');let selected;let player = 'X';let positions = [ [1, 2, 3], [4, 5, 6], [7, 8, 9], [1, 4, 7], [2, 5, 8], [3, 6, 9], [1, 5, 9], [3, 5, 7],];function init() { selected = []; currentPlayer.innerHTML = `JOGADOR DA VEZ: ${player}`; document.querySelectorAll('.game button').forEach((item) => { item.innerHTML = ''; item.addEventListener('click', newMove); });}init();function newMove(e) { const index = e.target.getAttribute('data-i'); e.target.innerHTML = player; e.target.removeEventListener('click', newMove); selected[index] = player; setTimeout(() => { check(); }, [100]); player = player === 'X' ? 'O' : 'X'; currentPlayer.innerHTML = `JOGADOR DA VEZ: ${player}`;}function check() { let playerLastMove = player === 'X' ? 'O' : 'X'; const items = selected .map((item, i) => [item, i]) .filter((item) => item[0] === playerLastMove) .map((item) => item[1]); for (pos of positions) { if (pos.every((item) => items.includes(item))) { alert('O JOGADOR ' + playerLastMove.toString() + ' GANHOU!'); ligarLed(playerLastMove); init(); return; } } if (selected.filter((item) => item).length === 9) { alert('DEU EMPATE!'); init(); return; }}function ligarLed(playerLastMove){ url = 'http://10.254.18.252/';window.location = url + playerLastMove.toString();} </script></body></html>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        Serial.println(currentLine);
        if (currentLine.endsWith("GET /X")) {
          digitalWrite(1, 1);               
          digitalWrite(2, 0); 
        }
        if (currentLine.endsWith("GET /O")) {
          digitalWrite(1, 0);                
          digitalWrite(2, 1);

        }
      }
    }
    // client.stop();
    Serial.println("Client Disconnected.");
  }
}
