#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum{
    ALCOOL,
    DIESEL,
    GASOLINA,
} Combustivel;

typedef struct Veiculo
{
    Combustivel combustivel;
    char modelo[50], cor[20], nChassi[20], placa[7], proprietario[50];
    int ano;
    struct Veiculo *prox;
} Veiculo;

Combustivel validaCombustivel(char combustivel){
    switch (combustivel){
    case 'A':
        return ALCOOL;
    case 'D':
        return DIESEL;
    case 'G':
        return GASOLINA;
    default:
        printf("Combustivel invalido! ------> Tente novamente\n");
        exit(EXIT_FAILURE);
    }
}

Veiculo *criarVeiculo(char proprietario[50], Combustivel combustivel, char modelo[50], char cor[20], char nChassi[20], int ano, char placa[7]){
    Veiculo *novoVeiculo = (Veiculo *)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL){
        perror("Erro ao alocar memoria para o veiculo!!!");
        exit(EXIT_FAILURE);
    }

    strcpy(novoVeiculo->proprietario, proprietario);
    novoVeiculo->combustivel = combustivel;
    strcpy(novoVeiculo->modelo, modelo);
    strcpy(novoVeiculo->cor, cor);
    strcpy(novoVeiculo->nChassi, nChassi);
    novoVeiculo->ano = ano;
    strcpy(novoVeiculo->placa, placa);
    novoVeiculo->prox = NULL;

    return novoVeiculo;
}

int validarPlaca(char placa[]){
    if (strlen(placa) != 7){
        printf("A placa nao possui 7 caracteres.\n");
        return 0;
    }
    for (int i = 0; i < 2; ++i){
        if (!((placa[i] >= 'A' && placa[i] <= 'Z') || (placa[i] >= 'a' && placa[i] <= 'z'))){
            printf("Os tres primeiros caracteres nao sao alfabeticos.\n");
            return 0;
        }
    }
    for (int i = 3; i < 7; ++i){
        if (!(placa[i] >= '0' && placa[i] <= '9')){
            printf("Os quatro ultimos caracteres nao sao numericos.\n");
            return 0;
        }
    }
    printf("Placa valida!!!\n");
    return 1;
}

void cadastrarVeiculo(Veiculo **lista){
    char proprietario[50], modelo[50], cor[20], nChassi[20], placa[7];
    Combustivel combustivel;
    int ano;

    printf("Proprietario: ");
    scanf("%s", &proprietario);
    fflush(stdin);
    printf("Combustivel | A - Alcool | D - Diesel | G - Gasolina |: ");
    scanf(" %c", &combustivel);
    fflush(stdin);
    combustivel = validaCombustivel(combustivel);
    printf("Modelo: ");
    scanf("%s", &modelo);
    fflush(stdin);
    printf("Cor: ");
    scanf("%s", &cor);
    fflush(stdin);
    printf("Numero do Chassi: ");
    scanf("%s", &nChassi);
    fflush(stdin);
    printf("Ano: ");
    scanf("%d", &ano);
    int placaValida;
        do{
        printf("Placa: (somente 7 caracteres)");
        scanf("%s", &placa);
        fflush(stdin);
        placaValida = validarPlaca(placa);

     } while (!placaValida);
     validarPlaca(placa);

    Veiculo *novoVeiculo = criarVeiculo(proprietario, combustivel, modelo, cor, nChassi, ano, placa);

    novoVeiculo->prox = *lista;
    *lista = novoVeiculo;
}

void imprimirLista(Veiculo *lista){
    Veiculo *atual = lista;
    while (atual != NULL){
        printf("Proprietario: %s\n", atual->proprietario);
        printf("Combustivel: ");
        switch (atual->combustivel){
        case ALCOOL:
            printf("Alcool\n");
            break;
        case DIESEL:
            printf("Diesel\n");
            break;
        case GASOLINA:
            printf("Gasolina\n");
            break;
        }
        printf("Modelo: %s\n", atual->modelo);
        printf("Cor: %s\n", atual->cor);
        printf("Numero do Chassi: %s\n", atual->nChassi);
        printf("Ano: %d\n", atual->ano);
        printf("Placa: %s\n", atual->placa);
        printf("----------------------------------------------------------\n");

        atual = atual->prox;
    }
}

void funcaoA(Veiculo *lista){
    Veiculo *atual = lista;
    printf("Proprietarios cujos carros sao do ano de 2010 ou mais e que sejam movidos a diesel.\n");

    while (atual != NULL){
        if (atual->ano >= 2010 && atual->combustivel == DIESEL){
            printf("Proprietario: %s\n", atual->proprietario);
            printf("Combustivel: Diesel\n");
            printf("Modelo: %s\n", atual->modelo);
            printf("Cor: %s\n", atual->cor);
            printf("Numero do Chassi: %s\n", atual->nChassi);
            printf("Ano: %d\n", atual->ano);
            printf("Placa: %s\n", atual->placa);
            printf("-----------------------------------------------------------------------\n");
        }
        atual = atual->prox;
    }
}
// b. Uma função que liste todas as placas que comecem com a letra J e terminem com 0, 2, 4 ou 7 e seus respectivos proprietários. (1,0 ponto)
void funcaoB(Veiculo *lista){
    Veiculo *atual = lista;
    printf("As placas que comecam com j e terminam com 0, 2, 4 ou 7\n");

    while (atual != NULL){
        if (atual->placa[0] == 'j' && (atual->placa[6] == '0' || atual->placa[6] == '2' || atual->placa[6] == '4' || atual->placa[6] == '7')){
            // liste a placa
            printf("Placa: %s\n", atual->placa);
            printf("Proprietario: %s\n", atual->proprietario);
            printf("--------------------------------------------------------------------\n");
        }
        atual = atual->prox;
    }
}
// c. Uma função que liste o modelo e a cor dos veículos cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numéricos fornece um número par. (1,0 ponto)
void funcaoC(Veiculo *lista){
    Veiculo *atual = lista;
    printf("Modelo e cor dos veiculos que as placas possuem vogal no segundo caractere e a soma de valores numericos da placa seja numero par\n");

    while (atual != NULL){
        int somaN = 0;
        for (int i = 3; i < 7; i++){
            somaN += atual->placa[i] - '0';
        }
        if ((atual->placa[1] == 'a' || atual->placa[1] == 'e' || atual->placa[1] == 'i' || atual->placa[1] == 'o' || atual->placa[1] == 'u') && somaN % 2 == 0){
            printf("Modelo: %s\n", atual->modelo);
            printf("Cor: %s\n", atual->cor);
            printf("---------------------------------------------------------------------\n");
        }
        atual = atual->prox;
    }
}
// d. Uma função que permita a troca de proprietário com o fornecimento do número do chassi apenas para carros com placas que não possuam nenhum dígito igual a zero. (1,0 ponto)
void funcaoD(Veiculo *lista, char nChassi[]){
    Veiculo *atual = lista;
    int encontrado = 0;

    while (atual != NULL){
        int temZero = 0;
        for (int i = 0; i < 7; i++){
            if (atual->placa[i] == '0'){
                temZero = 1; // verdadeiro
                break;
            }
        }

        if (temZero == 0 && strcmp(atual->nChassi, nChassi) == 0){
            printf("Troca de proprietario, apenas para carros com placas que nao possuam nenhum digito igual a zero\n");
            printf("Informe o numero do chassi para troca de proprietario: %s\n", atual->nChassi);
            printf("Placa: %s\n", atual->placa);
            printf("Digite o novo proprietario: ");
            scanf("%s", atual->proprietario);
            printf("Troca de proprietario realizada com sucesso!\n");

            encontrado = 1; // Defina a flag para indicar que o veículo foi encontrado
            break;
        }

        atual = atual->prox;
    }
    if (!encontrado){
        printf("Veiculo com o numero do chassi fornecido nao encontrado ou placa possui digito igual a zero.\n");
    }
}

int main(void){
    Veiculo *listaVeiculos = NULL;
    int opcao;

    do{
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("1 - Cadastrar veiculo\n");
        printf("2 - Imprimir lista\n");
        printf("3 - Lista todos os proprietarios cujos carros sao do ano de 2010 ou posterior e que sejam movidos a diesel.\n");
        printf("4 - Lista de todas as placas que comecem com a letra J e terminem com 0, 2, 4 ou 7 e seus respectivos proprietarios.\n");
        printf("5 - Lista do modelo e a cor dos veiculos cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numericos fornece um numero par.\n");
        printf("6 - Troca de proprietario\n");
        printf("0 - Sair \n");
        printf("Escolha uma opcao:");
        scanf("%d", &opcao);
        fflush(stdin);
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------------- \n");

        switch (opcao){
        case 1:
            cadastrarVeiculo(&listaVeiculos);
            break;
        case 2:
            imprimirLista(listaVeiculos);
            break;
        case 3:
            funcaoA(listaVeiculos);
            break;
        case 4:
            funcaoB(listaVeiculos);
            break;
        case 5:
            funcaoC(listaVeiculos);
            break;
        case 6:
            printf("Digite o numero do Chassi para trocar de proprietario: ");
            char nChassi[20];
            scanf("%s", &nChassi);
            fflush(stdin);
            funcaoD(listaVeiculos, nChassi);
            break;
        default:
            break;
        }
    } while (opcao != 0);

    // Liberar a memória alocada ao final do programa
    while (listaVeiculos != NULL){
        Veiculo *temp = listaVeiculos;
        listaVeiculos = listaVeiculos->prox;
        free(temp);
    }
}