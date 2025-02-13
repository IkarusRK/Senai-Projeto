#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>


void cores(int cor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (cor) {
        case 1: SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); break;
        case 2: SetConsoleTextAttribute(hConsole, FOREGROUND_RED); break;
        case 3: SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); break;
        case 4: SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); break;
        default: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
    }
}

typedef struct Fila{
	char nome[50];
    char cpf[12];
    int idade;
    char cell[11];
    struct Fila* prox;
} CadastroCliente;

typedef struct Pilha{
    char Livros[9999];
    float preco;
    struct Pilha* prox;
}Pilha;

typedef struct Lista {
    char Livros[9999];
    float preco;
    int dia, mes, ano;
    struct Lista* prox;
} Lista;

typedef struct{
	int dia, mes, ano;
	float Pagamento_CCredito_cjuros; 
	float Taxa_Domicilio;
    int tempo_limite;
    float Taxa_ultrapassar_limite;
}Taxas;
   
void inserirFila(CadastroCliente **inicio, CadastroCliente **fim, char nome[], char cpf[], int idade, char cell[]) {
    
	CadastroCliente* novoCliente = (CadastroCliente*)malloc(sizeof(CadastroCliente));
    	strcpy(novoCliente->nome, nome);
    	strcpy(novoCliente->cpf, cpf);
    	
    novoCliente->idade = idade;
    	strcpy(novoCliente->cell, cell);
    
	novoCliente->prox = NULL;

    if (*fim == NULL) {
        	*inicio = novoCliente;
    	    	*fim = novoCliente;
    } else {
        (*fim)->prox = novoCliente;
        	*fim = novoCliente;
    }
}

CadastroCliente* removerFila(CadastroCliente **inicio) {
    if (*inicio == NULL) return NULL;

    CadastroCliente* clienteRemovido = *inicio;
    	*inicio = (*inicio)->prox;
    
	return clienteRemovido;
}

void empilharPilha(Pilha **topo, char nome[], float preco) {
    Pilha* novoLivro = (Pilha*)malloc(sizeof(Pilha));
    	strcpy(novoLivro->Livros, nome);
    
	novoLivro->preco = preco;
    	novoLivro->prox = *topo;
    
	*topo = novoLivro;
}

Pilha* desempilharPilha(Pilha **topo) {
    if (*topo == NULL) return NULL;

    Pilha* livroDesempilhado = *topo;
    	*topo = (*topo)->prox;
    
	return livroDesempilhado;
}

void adicionarLista(Lista **inicio, char nome[], float preco, int dia, int mes, int ano) {
    Lista* novoLivro = (Lista*)malloc(sizeof(Lista));
    	strcpy(novoLivro->Livros, nome);
    
		novoLivro->preco = preco;
    		novoLivro->dia = dia;
    			novoLivro->mes = mes;
    				novoLivro->ano = ano;
    					novoLivro->prox = *inicio;  //quase uma escada filho.
    
	
	*inicio = novoLivro;
}

void calcularTaxa(Taxas *t, int diasAtraso) {
    
	if (diasAtraso > t->tempo_limite) {
    	    float taxa = (diasAtraso - t->tempo_limite) * t->Taxa_ultrapassar_limite;
        		printf("Taxa de atraso: R$ %.2f\n", taxa);
    } else {
        printf("Sem taxa de atraso.\n");
    }
}

// Função para contar e imprimir os livros na pilha
void contarLivrosPilha(Pilha* topo) {
    int contador = 0;
    Pilha* atual = topo;
    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }
    printf("Quantidade de livros na pilha: %d\n", contador);
}

// Função para contar e imprimir os livros na lista
void contarLivrosLista(Lista* inicio) {
    int contador = 0;
    Lista* atual = inicio;
    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }
    printf("Quantidade de livros na lista: %d\n", contador);
}

void menu() {
	
	system("cls");
	    printf("\nEscolha uma das opções:\n");
	    printf("1. Adicionar cliente à fila\n");
	    printf("2. Remover cliente da fila\n");
	    printf("3. Empilhar livro\n");
	    printf("4. Desempilhar livro\n");
	    printf("5. Adicionar livro à lista\n");
	    printf("6. Calcular taxa de atraso\n");
	    printf("7. Imprimir Livros\n");
	    printf("0. Sair\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    CadastroCliente* inicioFila = NULL;
    CadastroCliente* fimFila = NULL;
    Pilha* topoPilha = NULL; 
    Lista* inicioLista = NULL;

    Taxas taxa = {5, 10, 2024, 2.50, 15.0, 7, 5.0};  

    int opcao;
    char nome[50], cpf[12], cell[16], livro[100]; //aumentei o limite de numeros pra o caso de numeros fora do pais (DDD do pais ou DDD de estados com 3 digitos)
    float preco;
    int idade, dia, mes, ano, diasAtraso;

    
	while (1) {
        menu();
        printf("\nEscolha a opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
            	system("cls");
            	//Nome
            	printf("Digite o ");
                cores(2); printf("nome"); cores(4); //esquema de cores
                printf(" do cliente: ");
    	            getchar(); 
        		        fgets(nome, 50, stdin);
                			nome[strcspn(nome, "\n")] = 0; 

                //CPF
				printf("Digite o ");
                cores(2); printf("CPF"); cores(4); //esquema de cores
                printf(" do cliente: ");
        			scanf("%s", cpf);
                
                //idade
				printf("Digite a ");
                cores(2); printf("idade"); cores(4); //esquema de cores
                printf(" do cliente: ");
                	scanf("%d", &idade);
                //celular
				printf("Digite o numero de ");
                cores(2); printf("celular"); cores(4); //esquema de cores
                printf(" do cliente: ");
                	scanf("%s", cell);
                
                inserirFila(&inicioFila, &fimFila, nome, cpf, idade, cell);
                
				cores(1); printf("Cliente adicionado à fila.\n");cores(4);
				printf("\nDigite Enter para continuar.\n");
				getchar();
				getchar();
                break;

            case 2: 
            	system("cls");
                	if (inicioFila != NULL) {
                    	CadastroCliente* cliente = removerFila(&inicioFila);
                    	cores(2); printf("\nCliente removido: %s\n", cliente->nome); cores(4); //esquema de cores
					free(cliente);
					
					printf("\nDigite Enter para continuar.\n");
							getchar(); getchar();
                } else {
                    printf("Fila vazia.\n");
                    	printf("\nDigite Enter para continuar.\n");
							getchar(); getchar();
	            }
			break;

            case 3:  
            	system("cls");
                	printf("\nDigite o nome do livro: ");
                		getchar();  
                		fgets(livro, 100, stdin);
                	livro[strcspn(livro, "\n")] = 0;  

                printf("Digite o preco do livro: ");
                	scanf("%f", &preco);
                
                empilharPilha(&topoPilha, livro, preco);
                	printf("Livro empilhado.\n");
                
                printf("\nDigite Enter para continuar.\n");
							getchar(); getchar();
                
				break;

            case 4: 
            	system("cls");
                
				if (topoPilha != NULL) {
                    Pilha* livroDesempilhado = desempilharPilha(&topoPilha);
                	    printf("\nLivro desempilhado: %s\n", livroDesempilhado->Livros);
                  		  	free(livroDesempilhado);
                } else {
                    printf("Pilha vazia.\n");
                }
                printf("\nDigite Enter para continuar.\n");
							getchar(); getchar();
                break;

            case 5:  
				system("cls");
                	
					printf("\nDigite o nome do livro: ");
                		getchar(); 
    						fgets(livro, 100, stdin);
                	livro[strcspn(livro, "\n")] = 0; 

                	printf("Digite o preco do livro: ");
                		scanf("%f", &preco);
                	
					printf("Digite o dia do empréstimo: ");
                		scanf("%d", &dia);
                
					printf("Digite o mes do empréstimo: ");
                		scanf("%d", &mes);
                
					printf("Digite o ano do empréstimo: ");
                		scanf("%d", &ano);

                adicionarLista(&inicioLista, livro, preco, dia, mes, ano);
					printf("Livro adicionado à lista.\n");
                
                printf("\nDigite Enter para continuar.\n");
							getchar(); getchar();
                
				break;

            case 6: 
                system("cls");
					printf("\nDigite o número de dias de atraso: ");
                		scanf("%d", &diasAtraso);
                		calcularTaxa(&taxa, diasAtraso);
                		
                		printf("\nDigite Enter para continuar.\n");
							getchar(); getchar();
                break;

            case 7: //contar e imprimir os livros que estão na pilha e na lista UwU
		    	system("cls");
				    contarLivrosPilha(topoPilha);  // Contar e imprimir livros na pilha
				    contarLivrosLista(inicioLista);  // Contar e imprimir livros na lista
				    printf("\nDigite Enter para continuar.\n");
				    getchar();
					getchar();
		    	break;

                
            case 0:  
            system("cls");
                printf("Saindo...\n");
                exit(0);
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                printf("\nDigite Enter para continuar.\n");
				getchar();
				getchar();
        }
    }

    return 0;
}

