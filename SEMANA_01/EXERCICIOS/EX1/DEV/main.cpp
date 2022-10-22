#include <iostream>
#include <string>
using namespace std;

// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente 
// entre dois valores mínimo e máximo e retorna esse valor
float converteSensor(float medida, float min, float max) {
	float calc = (medida - min) / (max - min) * 100;
	if (calc > 100) {
		return 100;
	} else if (calc < 0) {
		return 0;
	} else {
		return calc;
	}
}

// 2 - Faça uma função que simule a leitura de um sensor lendo o
// valor do teclado ao final a função retorna este valor

int leSensor() {
	int value;
	cin >> value;
	
	return value;
}

// 3 - Faça uma função que armazena uma medida inteira qualquer
// em um vetor fornecido. Note que como C não possui vetores
// nativos da linguagem, lembre-se que você precisa passar o
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em
// uma área de memória fora do vetor

int armazenaMedida(int *values, int size, int ultPos, int value) {
	int posAtual = ultPos++;

	if(posAtual < size) {
		values[posAtual] = value;
	} else {
		throw invalid_argument( "A posição está além do tamanho maximo do vetor." );
	}

	return posAtual;
}

// 4 - Faça uma função que recebe um vetor com 4 posições que contém
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a
// segunda é esta maior distância.

pair<string, int> direcaoMaiorDistancia(int distances[4]) {
	// declarar as variáveis locais relevantes
	int maior = distances[0]; // começar pela distância no início do array
	int idMaior = 0;				// usado para lógica condicional abaixo

	// vamos percorrer todo o vetor de distância para encontrar o maior valor
	for (int i = 0; i < 4; i++) {
		// se a distância for maior que todas as anteriores, atualizar o valor e index
		if (distances[i] > maior) {
			maior = distances[i];
			idMaior = i;
		}
	}

	// converter o index do maior valor para uma string
	string maiorDir;
	switch (idMaior) {
		case 0:
			maiorDir =  "Direita";
		break;
		case 1:
			maiorDir =  "Esquerda";
		break;
		case 2:
			maiorDir =  "Frente";
		break;
		case 3:
			maiorDir =  "Tras";
		break;
	}

	// retornar uma tupla com o string da maior direção e o valor
	return pair<string, int>(maiorDir, maior);
}

// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e
// retorna verdadeiro ou falso

bool leComando() {
	cout << "Para continuar digite 1, para parar e obter o resultado digite 0: ";
	char resp;

	cin >> resp;

	if (resp ==  '1') {
		return true;
	} else {
		return false;
	}
}

// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda",
// "Frente", "Tras").
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno
// para uma movimentação futura.
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja
// enviado pelo usuário.
//
//      Complete a função com a chamada das funções já criadas

int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;

	while(dirigindo){
		cout << "Direita: ";
		int medida = leSensor(); // Chama a função de leitura da medida para "Direita"
		medida = converteSensor(medida, 0, 830);
		posAtualVetor = armazenaMedida(vetorMov, maxVetor, posAtualVetor, medida);  // Chame a função para armazenar a medida no vetor
		posAtualVetor++;

		cout << "Esquerda: ";
		medida = leSensor(); // Chama a função de leitura da medida para "Esquerda"
		medida = converteSensor(medida, 0, 830);
		posAtualVetor = armazenaMedida(vetorMov, maxVetor, posAtualVetor, medida);  // Chame a função para armazenar a medida no vetor
		posAtualVetor++;

		cout << "Frente: ";
		medida = leSensor(); // Chama a função de leitura da medida para "Frente"
		medida = converteSensor(medida, 0, 830);
		posAtualVetor = armazenaMedida(vetorMov, maxVetor, posAtualVetor, medida);  // Chame a função para armazenar a medida no vetor
		posAtualVetor++;

		cout << "Tras: ";
		medida = leSensor(); // Chama a função de leitura da medida para "Trás"
		medida = converteSensor(medida, 0, 830);
		posAtualVetor = armazenaMedida(vetorMov, maxVetor, posAtualVetor, medida);  // Chame a função para armazenar a medida no vetor
		posAtualVetor++;

		dirigindo = leComando();
	}
	return posAtualVetor;
}

// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado
// na maior distância a cada movimento

void percorre(int *v,int vetCorrido){
	int *vetorMov = v;

	for(int i = 0; i < vetCorrido; i+=4) {
		pair<string, int> distancia = direcaoMaiorDistancia(&(vetorMov[i]));
		string direcao = distancia.first;
		int valor = distancia.second;

		cout << "Indo para " << direcao << " a distancia " << valor <<'%';
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor * 4];
	int posAtualVet = 0;

	posAtualVet = dirige(vetorMov, maxVetor);
	percorre(vetorMov, posAtualVet);

	return 0;
}
