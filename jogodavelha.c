#include <stdio.h>
// para usar a matriz em todas as funcoes
char MatTabu[3][3];
int jogador = 1;

void IniTab()
{
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
        MatTabu[i][j] = ' ';
        }
    }
}

void Tabuleiro()
{
    int i, j;
    for (i = 0; i < 3; i++){
        printf("  %d",i);
    }
    printf("\n");
    for (i = 0; i < 3; i++){
        printf("%d",i);
        for (j = 0; j < 3; j++){
            if (MatTabu[i][j] == 'X'){
                printf("\033[0;31m");
            }else{
                printf("\033[0;32m");
            }
            printf("%c", MatTabu[i][j]);
            printf("\033[0m");
            if (j < 2) {
                printf(" |");
            }
        }
        if (i < 2){
            printf("\n --------");    
        }
        printf("\n");
    }
}

int eValido(char letra)
{
    if(letra == 'X' || letra == 'O'){
        return 1;
    }else{
        return 0;
    }
}

int TesteLinhas()
{
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(MatTabu[i][j]) && MatTabu[i][j] == MatTabu[i][j+1]){
                igual++;
            }
        }
        if(igual == 3){
            return 1;
        }
        igual = 1;
    }
    return 0;
}

int TesteColunas()
{
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(MatTabu[j][i]) && MatTabu[j][i] == MatTabu[j+1][i]){
                igual++;
            }
        }
        if(igual == 3){
            return 1;
        }
        igual = 1;
    }
    return 0;
}

int TestediagPrincipal()
{
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(MatTabu[i][i]) && MatTabu[i][i] == MatTabu[i+1][i+1]){
            igual++;
        }
    }
    if(igual == 3){
        return 1;
    }else
        return 0;
}

int TestediagSecundaria()
{
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(MatTabu[i][3-i-1]) && MatTabu[i][3-i-1] == MatTabu[i+1][3-i-2]){
            igual++;
        }
    }
    if(igual == 3){
        return 1;
    }else
        return 0;
}

int LeituraTestes(int ganhou)
{
    ganhou += TesteLinhas();
    ganhou += TesteColunas();
    ganhou += TestediagPrincipal();
    ganhou += TestediagSecundaria();
    return ganhou;
}

void Funcao_Ganhou(int ganhou, int ordem, int aux)
{
    if (ganhou != 0){
            Tabuleiro();
            if (ordem - 1 == 1){
                printf("\nJogador 1, voce venceu\n");
                jogador = 1;
            }else{
                printf("\njogador 2, Voce venceu \n");
                jogador = aux;
            }
    }else{
        printf("Empate\n");
    }
}

void jogo()
{
    int linha, coluna, ordem  = 1, ganhou = 0, NJogadas = 0, aux = 0;
        do {
            do {
                Tabuleiro();
                printf("Jogador %d, digite a posicao onde devo marcar. Ex:\"0 2\" (0 linha, 2 coluna): ", jogador);
                scanf("%d%d", &linha, &coluna);
            }while(linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || MatTabu[linha][coluna] != ' ');
            if (jogador == 0){
                jogador = 1;
            }
            if (ordem == 1){
                MatTabu[linha][coluna] = 'O';
                jogador++;
            }else{
                MatTabu[linha][coluna] = 'X';
                aux = jogador;
                jogador = 1;
            }
            if (jogador == 3){
                jogador = 1;
            }
            NJogadas++;
            ordem++;
            if (ordem == 3){
                ordem = 1;
            }
            ganhou = LeituraTestes(ganhou);
            
        }while(ganhou == 0 && NJogadas < 9);
        Funcao_Ganhou(ganhou, ordem, aux);
}

int main()
{
    int opcao;
    
    printf("\033[0;34m");
    printf("--------------------------\n");
    printf("BEM VINDO AO JOGO DA VELHA\n");
    printf("--------------------------\n");
    printf("\033[0m");
    
    do {
        IniTab();
        jogo();
        printf("Quer jogar novamente?(digite 1 pra sim ou 2 pra não): ");
        scanf("%d", &opcao);
    }while(opcao == 1);
    
    return 0;
}







