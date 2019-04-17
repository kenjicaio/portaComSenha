#define LED_VM 2 // nome e porta do LED vermelho
#define LED_VD 3 // nome e porta do LED verde
#define FECHADO 0 // ângulo do servo quando considerado fechado
#define ABERTO 80 // ângulo do servo quando considerado aberto
#include <Servo.h> // biblioteca servo

Servo motor; // nome do motor(servo) que vai abrir ou fechar a porta
byte senha[] = {3, 1, 4}; // Dígitos da senha
byte pots[] = {A1, A2, A3}; // Lista com as portas dos potenciômetros
byte leituraDosPotenciometros[sizeof(pots)]; // Lista com as leituras dos potenciêmetros (é do mesmo tamanho da lista com os Potenciômetros, por isso o 'sizeof(pots)')
boolean senhaCorreta = false; // resultado da verificação da senha
boolean primeiraVez = true; // marcador do primeiro loop

void setup() {
  Serial.begin(9600); // serial para verificar valor da senha
  motor.attach(5); // ligar porta 5 ao servo
  pinMode(LED_VM, OUTPUT); // configurar porta LED_VM para lidar com o LED vermelho
  pinMode(LED_VD, OUTPUT); // configurar porta LED_VM para lidar com o LED verde
}

void loop() {
  if (primeiraVez) {
    lerPotenciometros();
    imprimirValoresEncontrados();
    verificarSenha();

    if (senhaCorreta) {
      abrirPorta();
    } else {
      fecharPorta();
    }

    primeiraVez = false;
  } else {
    piscarResultado();
  }
}
