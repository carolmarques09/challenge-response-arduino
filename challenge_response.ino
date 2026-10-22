const int LED_OK = 8;
const int LED_FAIL = 7;
const unsigned long CHAVE = 7919;   // segredo compartilhado
const unsigned long MOD = 10007;

unsigned long desafio;
int tentativas = 0;

void novoDesafio() {
  desafio = random(1000, 9999);
  Serial.print("Desafio: ");
  Serial.println(desafio);
  Serial.println("Responda: (desafio * chave) % 10007");
  Serial.println((desafio * CHAVE) % MOD);
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(200);
  pinMode(LED_OK, OUTPUT);
  pinMode(LED_FAIL, OUTPUT);
  randomSeed(analogRead(A0));  // A0 solto = ruído como semente
  novoDesafio();
}

void loop() {
  if (Serial.available() > 0) {
    unsigned long resposta = Serial.parseInt();
    while (Serial.available()) Serial.read();  // limpa o buffer

    unsigned long esperado = (desafio * CHAVE) % MOD;

    if (resposta == esperado) {
      Serial.println("Acesso liberado!");
      digitalWrite(LED_OK, HIGH);
      delay(3000);
      digitalWrite(LED_OK, LOW);
      tentativas = 0;
    } else {
      tentativas++;
      Serial.println("Resposta incorreta.");
      digitalWrite(LED_FAIL, HIGH);
      delay(500);
      digitalWrite(LED_FAIL, LOW);

      if (tentativas >= 3) {
        Serial.println("Bloqueado por 10s.");
        digitalWrite(LED_FAIL, HIGH);
        delay(10000);
        digitalWrite(LED_FAIL, LOW);
        tentativas = 0;
      }
    }
    novoDesafio();  // desafio novo a cada tentativa
  }
}
