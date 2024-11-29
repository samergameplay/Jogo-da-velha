//Jogo da velha:

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Forma de como funciona uma matriz 3x3:
//	for(int i = 0; i < 3; i++){
//		for(int j = 0; j < 3; j++){
//			printf("I = %d J = %d\t", i, j);
//		}
//		printf("\n");
//	}

// Implementações das funções
void inicializarMatriz(char **matriz) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            matriz[i][j] = ' ';
    	}
	}
}

void exibirMatriz(char **matriz) {
    printf("---------------------------------\n");
    for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if (matriz[i][j] == NULL || matriz[i][j] == ' '){
					printf("\t*");
				}else{
					printf("\t%c", matriz[i][j]);
				}
			}
			printf("\n\n");
		}
    printf("---------------------------------\n");
}

void exibirMenu() {
    printf("O que você deseja fazer?\n");
    printf("1- Jogar;\n2- Ver Ranking;\n3- Créditos;\n4- Sair.\n");
}

void exibirRanking(char jogador1[], char jogador2[], int placarA, int placarB) {
    printf("---------------------------------\n");
    printf("\t   Ranking:\n");
    printf("---------------------------------\n");
    if (strcmp(jogador1, " ") == 0) {
        printf("Você ainda não jogou nenhuma partida\n\n");
    } else {
        printf("%s: %d pontos\n", jogador1, placarA);
        if (strcmp(jogador2, " ") != 0) {
            printf("%s: %d pontos\n", jogador2, placarB);
        }
    }
}

int verificarVencedor(char **matriz, int *placarA, int *placarB) {
	// Verifica linhas e colunas
	for (int i = 0; i < 3; i++) {
	    if (matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2] && matriz[i][0] != ' ') {
	         // Linha completa
	        if(matriz[i][0] == 'X'){
	        	(*placarA)++;
	        	return 1;
			}else if(matriz[i][0] == 'O'){
				(*placarB)++;
				return 2;
			}else{
				return 3;
			}
	        
	    }
	    if (matriz[0][i] == matriz[1][i] && matriz[1][i] == matriz[2][i] && matriz[0][i] != ' ') {
	        // Coluna completa
	        if(matriz[0][i] == 'X'){
	        	(*placarA)++;
	        	return 1;
			}else if(matriz[0][i] == 'O'){
				(*placarB)++;
				return 2;
			}else{
				return 3;
			}
	    }
	}

	// Verifica diagonais
	if (matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2] && matriz[0][0] != ' ') {
	    // Diagonal principal
	    if(matriz[0][0] == 'X'){
	    	(*placarA)++;
	    	return 1;
		}else if(matriz[0][0] == 'O'){
			(*placarB)++;
			return 2;
		}else{
			return 3;
		}
	}
	if (matriz[0][2] == matriz[1][1] && matriz[1][1] == matriz[2][0] && matriz[0][2] != ' ') {
	    // Diagonal secundária
	    if(matriz[0][2] == 'X'){
	    	(*placarA)++;
	    	return 1;
		}else if(matriz[0][2] == 'O'){
			(*placarB)++;
			return 2;
		}else{
			return 3;
		}
	}
	return 0;
}

void realizarJogada(char **matriz, char *simbolo, int linha, int coluna, char contra) {
    int jogada_Linha, jogada_Coluna;
    printf("É a vez do jogador %c\n", *simbolo);
    printf("Digite a posição na qual deseja jogar (ex: 0 2 [linha e coluna])");
	scanf("%d %d", &jogada_Linha, &jogada_Coluna);
	getchar();
	if(matriz[jogada_Linha][jogada_Coluna] != ' '){
		printf("Jogada inválida, tente novamente!\n");
		printf("---------------------------------\n");
	} else{
		matriz[jogada_Linha][jogada_Coluna] = *simbolo;
		if(contra == 'p'){
			if(*simbolo == 'X'){
				*simbolo = 'O';
			} else{
				*simbolo = 'X';
			}	
		} else{
			*simbolo = 'X';
		}
	}
}

void jogadaMaquina(char **matriz) {
    int linha, coluna;
    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (matriz[linha][coluna] != ' ');

    matriz[linha][coluna] = 'O';
    printf("A máquina jogou em %d %d\n", linha, coluna);
}

void pegarNomeJogador(char jogador1[50], char jogador2[50], char contra){
	if (strcmp(jogador1, " ") == 0 && strcmp(jogador2, " ") == 0) {
        printf("Digite o nome do 1º jogador (X): ");
        scanf("%s", jogador1);
        if (contra == 'p') {
            printf("Digite o nome do 2º jogador (O): ");
            scanf("%s", jogador2);
        } else {
            strcpy(jogador2, "Máquina");
        }
    }
}

int main(){
	setlocale(0, "Portuguese");
	
	// Matriz dinâmica
    char **matriz = (char **)malloc(3 * sizeof(char *));
    for (int i = 0; i < 3; i++) {
        matriz[i] = (char *)malloc(3 * sizeof(char));
    }
	
	//Inicialização das variáveis
	int jogada_Linha, jogada_Coluna, placarA, placarB = 0, vencedor = 0;
	char jogador1[50] = " ", jogador2[50] = " ";
	char contra, opcao, continuar = 's', simbolo = 'X';
	
	// Garantindo que a sequência de números aleatórios seja diferente a cada execução
	srand(time(NULL));
	
	printf("Seja bem-vindo ao jogo da velha!\n");
	exibirMatriz(matriz);

	do{
		exibirMenu();
		scanf("%d", &opcao);
		getchar();
		
		switch (opcao){
			case 1:
				printf("Contra quem você deseja jogar? jogador:(p) máquina:(m)\n");
				scanf("%c", &contra);
				
				//Reiniciando a matriz:
				inicializarMatriz(matriz);
						
				//Pegando os nomes dos jogadores
				pegarNomeJogador(jogador1, jogador2, contra); 
				
				switch (contra){
					case 'p': //OPÇÃO DE JOGAR CONTRA OUTRO JOGADOR
						do{ //Laço de repetição que só finaliza quando tiver um vencedor
							//Pegando a jogada dos jogadores
							realizarJogada(matriz, &simbolo, jogada_Linha, jogada_Coluna, contra);
							
							//Mostra a tabela
							exibirMatriz(matriz);
							
							// Verifica o vencedor e armazena o valor na variavel vencedor
						    vencedor = verificarVencedor(matriz, &placarA, &placarB);
						    
						} while (vencedor == 0);
						break; //Finalizando o case 'p'
						
					case 'm':
						//OPÇÃO DE JOGAR CONTRA A MÁQUINA (CPU)
						do{ //Laço de repetição que só finaliza quando tiver um vencedor
							//Pegando a jogada do jogador
							realizarJogada(matriz, &simbolo, jogada_Linha, jogada_Coluna, contra);
							
							// Verifica o vencedor e armazena o valor na variavel vencedor
						    vencedor = verificarVencedor(matriz, &placarA, &placarB);
						    
						    //Mostra a tabela depois da jogada do jogador;
							exibirMatriz(matriz);
							
							// Se houver um vencedor, não faz a jogada da máquina
							if(vencedor != 0){
						    	break;
							}
							
							//Informando a jogada da máquina
						    jogadaMaquina(matriz);
						    
						    //Mostra a tabela depois da jogada da máquina
							exibirMatriz(matriz);
							
							// Verifica o vencedor após a jogada da máquina
						    vencedor = verificarVencedor(matriz, &placarA, &placarB);
						    
						} while (vencedor == 0);
						
						break; //finalizando o case 'm'
					default:
						printf("Valor inválido!\n");
				}
				break; //finalizando o case 1
			case 2:
 				exibirRanking(jogador1, jogador2, placarA, placarB); //Exibindo o placar
				break;
			case 3:
				//OPÇÃO DE CRÉDITOS
				    printf("===========================================\n");
				    printf("               DESENVOLVEDORES              \n");
				    printf("===========================================\n");
				    printf("               Wálisson Andrey             \n");
				    printf("               Gabriel Albino              \n");
				    printf("               Samuel David                \n");
				    printf("               Victor Gabriel              \n");
				    printf("===========================================\n");
				    printf("         Obrigado por jogar nosso jogo!     \n");
				    printf("===========================================\n");
				break;
			case 4:
				//OPÇÃO DE SAIR
				printf("Obrigado por jogar, até mais!\n");
				continuar = 'n';
				break;
			default:
				printf("Digite uma opção válida");
		}
		
		switch (vencedor){
		case 1:
			printf("Parabéns, %s. Você venceu!!\n", jogador1);
			break;
		case 2:
			printf("Parabéns, %s. Você venceu!!\n", jogador2);
			break;
		case 3:
			printf("Essa não, deu velha!\n");
			break;
		default:
			printf("Jogo finalizado.\n");
		}
		
		printf("Desja continuar? (s/n): ");
		scanf("%c", &continuar);
		
	} while (continuar == 's' || continuar == 'S');
	
	// Liberar memória alocada para a matriz
	    for (int i = 0; i < 3; i++) {
	        free(matriz[i]);
	    }
	    free(matriz);
}
