# [Challenge-Response Auth]

**Autora:** [Carolina Marques Magalhães Véras]  
**Data:** [10/2026]  
**Link do Projeto no Tinkercad:** [
https://www.tinkercad.com/things/5tV7Ncnufto-challenge-response-auth
]

---

## 📝 Descrição do Projeto
Um projeto de autenticação por desafio simples em Serial, em que o Arduino gera um número aleatório e você precisa responder com uma operação a partir do cálculo (número x chave secreta).

## 🛠️ Componentes Utilizados

| Componente | Quantidade | Função no Circuito |
| :--- | :---: | :--- |
| Arduino Uno R3 | 1 | Microcontrolador principal |
| Resistor 220 Ω | 2 | Limitar a passagem da corrente elétrica |
| LED verde | 1 | Simulação do braço mecânico de escape |
| LED Vermelho | 1 | Indicador visual de alerta |
| Fios (jumpers) | 5 | Conectar dois pontos elétricos para permitir a passagem de corrente elétrica |
| Protoboard | 1 | Montar e testar circuitos eletrônicos |

## 📐 Circuito e Esquemático
![Imagem do Circuito](Challenge-Response Auth.png)  

## 💻 Código-Fonte
```cpp
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
```

## 🚀 Como Executar
1. Acesse o link do projeto no Tinkercad.
2. Clique em **"Iniciar Simulação"**.
3. Altere os valores do sensor para ver a resposta do circuito.
