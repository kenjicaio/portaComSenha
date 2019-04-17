void lerPotenciometros() { // Versão reduzida
  for (byte i = 0; i < sizeof(pots); i++) { // para cada potenciômetro
    leituraDosPotenciometros[i] = byte(map(analogRead(pots[i]), 0, 1023, 0, 5)); // ler o valor, redimensionar para valores entre 0 e 5, guardar o valor encontrado
  }
}

void imprimirValoresEncontrados() {
  Serial.print("Senha encontrada: ");
  for (byte i = 0; i < sizeof(leituraDosPotenciometros); i++) { // para cada valor encontrado
    Serial.print(leituraDosPotenciometros[i]); //imprimir o dígito de cada potenciômetro
  }
  Serial.print("\n"); // Pular linha no final
}

void verificarSenha() {
  for (byte i = 0; i < sizeof(senha); i++) { // para cada dígito da senha verificar se potenciômetro correspondente
    if (senha[i] == leituraDosPotenciometros[i]) { // se estiver correto
      senhaCorreta = true; // indicar que está correto e continuar a verificação
    } else { // Caso contrário
      senhaCorreta = false; // indicar que está errado
      break; // e sair da verificação imediatamente
    }
  }
}

void abrirPorta() {
  motor.write(ABERTO); // mover o motor servo para a posição que abre a porta
  Serial.println("Senha correta");
  motor.detach(); // desligar o motor
}

void fecharPorta() {
  motor.write(FECHADO); // mover o motor servo para a posição que fecha a porta
  Serial.println("Senha incorreta");
  motor.detach();  // desligar o motor
}

void piscarResultado() { // Versão Simples Reduzida
  digitalWrite((senhaCorreta ? LED_VD : LED_VM), HIGH); // Acende o LED de acorodo com a senha
  delay(500); // espera
  digitalWrite((senhaCorreta ? LED_VD : LED_VM), LOW);// Apaga o LED de acorodo com a senha
  delay(500); //espera
}

/*------------------------------------------- Outras formas de escrever as funções acima

void lerPotenciometros() { // Versão normal
  int valorTemp = 0; // variável para guardar os valores das leituras do potenciômetros
  
  for (byte i = 0; i < sizeof(pots); i++) { // para cada potenciômetro
    valorTemp = analogRead(pots[i]); // Ler e guardar o valor bruto
    valorTemp = map(valorTemp, 0, 1023, 0, 5); // Redimensionar para um valor entre 0-5
    leituraDosPotenciometros[i] = byte(valorTemp); // guardar o valor encontrado convertendo para o formato Byte
  }
}

void piscarResultado() { // Versão Simples
  byte led; // variável para guardar QUAL LED será acionado
  
  if(senhaCorreta) { // Se a senha estiver correta
    led = LED_VD; // usaremos o LED verde
  } else { // caso contrário
    led = LED_VM; // usaremos o LED vermelho
  }
  
  digitalWrite(led, HIGH); // Acende
  delay(500); // espera
  digitalWrite(led, LOW); // apaga
  delay(500); // espera
}

void piscarResultado() { // Versão que exija simultaneidade de processos durante o loop
  static unsigned long timer = 0;
  static boolean aceso = true;

  if (millis() - timer > 500) {
    aceso = !aceso;
    if (senhaCorreta) {
      digitalWrite(LED_VD, aceso);
    } else {
      digitalWrite(LED_VM, aceso);
    }
    timer = millis();
  }
}
*/
