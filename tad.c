//Printa uma sequencia de quebra de linha de forma que no terminal só apareça o necessário para o usuário
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Printa na tela uma mensagem de abertura do programa
void opening(){
    printf("\n\n---------------------------------\n");
    printf("|  BEM VINDO AO JOGO DA FORCA!  |");
    printf("\n---------------------------------\n");
    printf("\n\n\n\n\n\n");
}

//Printa na tela um trofeu
void printTrophy(){
    printf("           ___________\n");
    printf("          '._==_==_=_.'\n");
    printf("          .-|:      |-.\n");
    printf("         | (|:.     |) |\n");
    printf("          '-|:.     |-'\n");
    printf("            |::.    |\n");
    printf("             '::. .'\n");
    printf("               ) (\n");
    printf("             _.' '._\n");
    printf("            `''''''''\n");
}

//Um gatilho para quebrar linha
void lineBreak(){
    printf ("\nAperte ENTER para continuar!\n");
    char aux;
    scanf ("%c", &aux);
    scanf ("%c", &aux);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

//Printa o menu e suas opções
void menu(){
    lineBreak();
    printf("\n-------------MENU-------------\n");
    printf ("Escolha uma opcao:\n");
    printf("\n\n");
    printf("1- Novo Jogo;\n");
    printf("2- Regras;\n");
    printf("3- Creditos;\n");
    printf("4- Encerrar.\n");
    printf("\n");
}

void newWord(){
    FILE* f;

    f = fopen("C:/Users/Marcos/Desktop/Projetos/C/Alura/Forca/words.txt", "r+");
    if (!f){
        perror("Erro ao abrir arquivo 'palavras.txt'\n");
        exit(1);
    }

    printf("A palavre deve conter ate SECRETWORD_SIZE letras,\n");
    printf("caso a palavra tenha acento, nao o coloque,\n");
    printf("caso a palavra tenha 'c cedilha', coloque um 'c' normal,\n");
    printf("e deve ser escrita em letras maiusculas!\n");
    printf("Ex.: 'MARCOS', 'FEIRA', 'GABIGOL' etc\n\n");

    printf("Escreva a palavra que deseja adicionar ao jogo: ");
    char newUserWord[SECRETWORD_SIZE];
    scanf("%s", newUserWord);
    printf(".\n");

    //Criando uma variavel que verifica e salva a quantidade de palavras que temos no BD
    int amountOfWords;
    //Tratamento de erro
    if (fscanf(f, "%d", &amountOfWords) != 1) {
        printf("Erro ao ler quantidade de palavras!\n");
        exit(1);
    }
    //Incremento +1 nessa variavel de verificacao
    amountOfWords++;
    //Retorno para a primeira posicao da lista com a constante SEEK_SET
    fseek(f, 0, SEEK_SET);
    //Altero o valor da primeira linha da lista
    fprintf(f, "%d", amountOfWords);
    //Vou para a ultima posicao da lista com a constante SEEK_END
    fseek(f, 0, SEEK_END);
    //Incremento a palavra escolhida pelo usuario na lista
    //O '\n' antes do '%s' e utilizado para realizar uma quebra de linha antes
    //de incrementar a palavra
    fprintf(f, "\n%s", newUserWord);

    fclose(f);
}

//O programa irá gerar um número aleatório que corresponderá à uma palavra no conjunto de palavras secretas
void chooseWord(char secretWord[SECRETWORD_SIZE]){
    FILE* f;
    
    f = fopen("C:/Users/Marcos/Desktop/Projetos/C/Alura/Forca/words.txt", "r");
    if (!f){
        perror("Erro ao abrir arquivo 'words.txt'\n");
        exit(1);
    }

    int amountOfWords;
    if (fscanf(f, "%d", &amountOfWords) != 1) {
        printf("Erro ao ler quantidade de palavras!\n");
        exit(1);
    }
    
    srand(time(0));
    int random = rand() % amountOfWords;

    for (int i = 0; i < random; i++) {
        if (fscanf(f, "%19s", secretWord) != 1) {
            printf("Erro ao ler palavra!\n");
            exit(1);
        }
    }

    if (fscanf(f, "%19s", secretWord) != 1) {
        printf("Erro ao ler palavra secreta!\n");
        exit(1);
    }

    fclose(f);
}

//Recebe do usuário uma letra que corresponde ao chute e salva no array Guess[]
void readGuess(char guess[GUESS_SIZE], int *attempts){
    char shot;

    printf("\nLetras escolhidas: ");
    for(int i = 0; i<(*attempts);i++){
        printf("%c", guess[i]);
        if (i < (*attempts - 1)) {
            printf(", ");
        } else {
            printf(".\n");
        }
    }

    printf("\n\nEscolha uma nova letra!\n\n");
    scanf(" %c", &shot);
    printf("\n\nVoce escolheu a letra <%c>!\n", shot);
    guess[(*attempts)] = shot;
    (*attempts)++;
}

//Faz a verificação entre o chute do usuário e a palavra secreta
int verifyGuess(char guess[GUESS_SIZE], int *attempts, char word){
    int rightGuess = 0;
    for (int i = 0; i < *attempts; i++) {
        if (guess[i] == word) {
            rightGuess = 1;
            break;
        }
    }
    return rightGuess;
}

//Printa a palavra secreta mostrando somente as letras que o jogador já acertou.
void printWords(char guess[GUESS_SIZE], int *attempts, char secretWord[SECRETWORD_SIZE]){
    for (unsigned int i = 0; i < strlen(secretWord); i++) {
        if (verifyGuess(guess, attempts, secretWord[i])) {
            printf("%c ", secretWord[i]);
        } else {
            printf("_");
        }

        if (i < (strlen(secretWord) - 1)) {
            printf(" ");
        } else {
            printf(".\n");
        }
    }
}

//Printa a forca de acordo com os erros do jogador.
void printHangman(int body){
    if (body == 0){
        printf("  _______\n");
        printf(" |/     |\n");
        printf(" |\n");
        printf(" |\n");
        printf(" |\n");
        printf(" |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }else if (body == 1){
        printf("  _______\n");
        printf(" |/     |\n");
        printf(" |     (_)\n");
        printf(" |\n");
        printf(" |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }else if (body == 2){
        printf("  _______\n");
        printf(" |/     |\n");
        printf(" |     (_)\n");
        printf(" |      |\n");
        printf(" |      |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }else if (body == 3){
        printf("  _______\n");
        printf(" |/     |\n");
        printf(" |     (_)\n");
        printf(" |      |\\");printf("\n");
        printf(" |      |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }else if (body == 4){
        printf("  _______\n");
        printf(" |/     |\n");
        printf(" |     (_)\n");
        printf(" |     /|\\"); printf("\n");
        printf(" |      |\n");
        printf(" |\n");
        printf("_|___\n\n");
    }else if (body == 5){
        printf("  _______\n");
        printf(" |/     |\n");
        printf(" |     (_)\n");
        printf(" |     /|\\");printf("\n");
        printf(" |      |\n");
        printf(" |     / \n");
        printf("_|___\n\n");
    }else if (body == 6){
        printf("  _______\n");
        printf(" |/     |\n");
        printf(" |     (_)\n");
        printf(" |     /|\\");printf("\n");
        printf(" |      |\n");
        printf(" |     / \\");printf("\n");
        printf("_|___\n\n");
    }
}

//Verifica o número tentativas erradas
int hanged(char guess[GUESS_SIZE], int *attempts, char secretWord[SECRETWORD_SIZE]){
    int wrongGuess = 0;

    for (int i = 0; i < (*attempts); i++){
        int rightGuess = 0;
        for (unsigned int j = 0; j < (strlen(secretWord)); j++){
            if (guess[i] == secretWord[j]){
                rightGuess = 1;
                break;
            }
        }
        if ((!rightGuess)){
            wrongGuess++;
        }
    }

    return wrongGuess;
}

//Verifica se todas as letras do Array secretWord corresponde à alguma letra do Array guess
int won(char guess[GUESS_SIZE], int *attempts, char secretWord[SECRETWORD_SIZE]){
    for (unsigned int i = 0; i < (strlen(secretWord)); i++){
        if(!verifyGuess(guess, attempts, secretWord[i])){
            return 0;
        }
    }
    return 1;
}

//O corpo do jogo
void newGame(){

    char secretWord[SECRETWORD_SIZE];
    char guess[GUESS_SIZE];
    int attempts = 0;

    //free(guess);
    //free(secretWord);

    printf("\nVamos comecar?\n");

    chooseWord(secretWord);

    lineBreak();

    printf("A palavra secreta tem %d letras!\nBoa sorte!\n", strlen(secretWord));
    
    do{
        lineBreak();

        printHangman(hanged(guess, &attempts, secretWord));
        printWords(guess, &attempts, secretWord);
        readGuess(guess, &attempts);

        if(won(guess, &attempts, secretWord)){
            lineBreak();

            printf("A palavra secreta e: ' %s '!!!!\n\n", secretWord);

            lineBreak();

            printTrophy();
            printf("\n\nParabens, voce ganhou!\n\n");

            lineBreak();

            int putNewWord = 0;
            printf("Como recompensa a sua vitoria agora voce\n");
            printf("pode fazer parte desse jogo!!!\n\n");
            printf("Deseja inserir uma palavra secreta no jogo e deixar sua marca?\n");
            printf("1- Sim;\n2- Nao.\n\n");

            scanf("%d", &putNewWord);

            if (putNewWord == 1){
                lineBreak();
                newWord();
            }
        }

        if((hanged(guess, &attempts, secretWord) == 6)){
            lineBreak();

            printf("\n\nInfelizmente as suas chances acabaram e voce perdeu!\n\n");
        }


        printf("\n");

    }while ((!won(guess, &attempts, secretWord)) && (hanged(guess, &attempts, secretWord)<6));
}

//Printa as regras do jogo
void rules(){
    lineBreak();
    printf("\n------------REGRAS------------\n\n");
    printf("- O objetivo deste jogo e\ndescobrir uma palavra adivinhando\nsuas letras!\n");
    printf("- O jogo escolhera uma palavra\naleatoria do nosso banco de palavras\ne esta sera a palavra misteriosa!\n");
    printf("- Voce deve descobrir qual palavra\ne essa escolhendo uma letra\ndo alfabeto por vez!\n");
    printf("- Se voce errar a palavra sera desenhado\numa parte do boneco na forca\n(cabeca, corpo, um braco, outro braco,\numa perna e outra perna).\n");
}

//Printa os créditos do jogo
void credits(){
    lineBreak();
    printf("\n-----------CREDITOS-----------\n");
    printf("O Jogo da Forca.\n");
    printf("Julho de 2023.\n");
    printf("\n");
    printf("Desenvolvido por Marcos Paulo Silva.\n");
    printf("www.linkedin/in/souomarcos\n");
    printf("www.github.com/souomarcos\n");
    printf("\n");
    printf("Projeto desenvolvido com o auxilio do curso\n'C: avan�ando na linguagem' da Alura.\n");
}

//Printa os créditos do jogo e encerra o programa
void shutDown(){
    lineBreak();
    printf("\nObrigado por jogar O Jogo da Forca!\n");
    printf("Julho de SECRETWORD_SIZE23.\n");
    printf("\n");
    printf("Desenvolvido por Marcos Paulo Silva.\n");
    printf("www.linkedin/in/souomarcos\n");
    printf("www.github.com/souomarcos\n");
    printf("\n");
    printf("Projeto desenvolvido com o auxilio do curso\n'C: avancando na linguagem' da Alura.\n");
    printf("\n\n");
}