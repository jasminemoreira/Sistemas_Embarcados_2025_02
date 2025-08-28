/*
 * Projeto Educacional - Sistema Embarcados com Arduino Mega
 * Objetivo: Aprender uso de memória e comunicação serial
 * Firmware básico para impressão de tabuleiro de jogo da velha
 */

// Definições de constantes para melhor organização do código
#define BAUDRATE 9600      // Velocidade da comunicação serial
#define DELAY_TIME 2000    // Tempo entre atualizações (2 segundos)
#define ESPACO 5

// Array que representa o tabuleiro do jogo da velha
// Usamos char para economizar memória (1 byte por posição)
char tabuleiro[3][3] = {
  {'-', '-', '-'},  // Linha 1
  {'-', '-', '-'},  // Linha 2
  {'-', '-', '-'}   // Linha 3
};

void setup() {
  /*
   * Função setup: executada uma vez ao iniciar o Arduino
   * Objetivo: configurar a comunicação serial
   */
  
  // Inicializa a comunicação serial com a velocidade definida
  Serial.begin(BAUDRATE);
  
  // Pequena pausa para estabilização
  delay(100);
  
  // Mensagem inicial para identificar o programa
  Serial.println("=== SISTEMA JOGO DA VELHA ===");
  Serial.println("Inicializando tabuleiro...");
  Serial.println();


}

char casa = 0;
char jogador = 'X';
void loop() {
  /*
   * Função loop: executada repetidamente após o setup
   * Objetivo: imprimir o tabuleiro periodicamente
   */
  
  // Chama a função para imprimir o tabuleiro
  imprimirTabuleiro();
  
  // Adiciona uma linha separadora
  Serial.println("-------------------");
  
  // Aguarda o tempo definido antes da próxima impressão
  delay(DELAY_TIME);

  casa = Serial.read();
  if (casa){
    jogar(casa-48,jogador);
    if (jogador=='X'){
      jogador = 'O';
    }else{
      jogador = 'X';
    }   
  }

}

void imprimirTabuleiro() {
  /*
   * Função para imprimir o tabuleiro formatado
   * Objetivo: demonstrar organização de dados em matriz
   * e uso eficiente da comunicação serial
   */
  
  Serial.println("Tabuleiro Atual:");
  Serial.println();
  
  // Loop através das linhas do tabuleiro
  for (int linha = 0; linha < 3; linha++) {
    
    // Loop através das colunas do tabuleiro
    for (int coluna = 0; coluna < 3; coluna++) {
      
      // Imprime o conteúdo da posição atual
      Serial.print(" ");
      Serial.print(tabuleiro[linha][coluna]);
      Serial.print(" ");
      
      // Adiciona separador vertical (exceto após a última coluna)
      if (coluna < 2) {
        Serial.print("|");
      }
    }
    
    // Quebra de linha após cada linha do tabuleiro
    Serial.println();
    
    // Adiciona separador horizontal (exceto após a última linha)
    if (linha < 2) {
      Serial.println("-----------");
    }
  }

  for (int i=0; i<=ESPACO; i++){
    Serial.println();  // Linha em branco para melhor legibilidade
  }
}


void jogar(int casa, char jogador){
  int n = casa - 1;
  int linha = int(n/3);
  int coluna = n - 3*(linha);
  tabuleiro[linha][coluna] = jogador;
}





// Função adicional para demonstrar uso de memória (opcional)
void informacoesMemoria() {
  /*
   * Função para mostrar uso de memória (para evolução futura)
   * Demonstrará conceitos de memória RAM e Flash
   */
  Serial.print("Memória RAM utilizada: ");
  Serial.print(sizeof(tabuleiro));
  Serial.println(" bytes");
  
  Serial.print("Tamanho total do programa: ");
  // Aqui poderíamos adicionar código para verificar tamanho do sketch
}
