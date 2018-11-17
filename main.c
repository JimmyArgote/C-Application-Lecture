#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
//#include <iostream>
//#include <cstdlib>
#include "login.c"
#include "menu.c"

//constantes
#define TIMEOUT          5  //segundos
#define TIME_SLEEP       10 //30000ms == 30segundos
#define ATTEMPS          3  //numero de tentativas autenticar login e senha
#define G_PARTICIPANTE   1  //OP gerenciar participante
#define G_CONVIDADO      2  //OP Gerencial convidado
#define SORTEIO          3  //OP Sorteio
#define ENVIAR_EMAIL     4  //OP Enviar Email
#define SAIR             5  //OP Sair

/*capacidade de assentos na palestra*/
#define QTD_L       8  /* LINHAS */
#define QTD_C      19 /* Colunas */

//typedef struct administrator Admin;
    //login
typedef struct
{
    char login[30];
    char password[30];
    int attempts;
}administrator;
    //struct administrator admin;

    int i, op, num_seat, flag, re_opcao, l, c;
    /*Criando a struct */
struct participant
{
    int     b;
    int     flag;
    int     adm;
    int     cod_visitante;
    char    nome[50];
    char    data_nasc[9];
    char    sexo[8];
    char    rg[10];
    char    email[30];
    int     convidado; //convidado -> sim ou n�o (m�ximos 10 convidados)
    int     assento_especial; //Lugar especial -> sim ou n�o (m�ximos 3)
    int     assento_reservado;
	char    dateStr[9];
    char    timeStr[9];
};
    // sP => struct-matriz do tipo participant
    struct participant sP[QTD_L][QTD_C];

    //P sP;
//ficha_do_participante[QTD_L][QTD_L];

//struct ficha_do_participante participant[QTD_L][QTD_C];

    //P sera do tipo struct participant
    //participant P[QTD_L][QTD_C];

    //*pP será do tipo struct ponteiro
    //participant *pP = &P;



int authLogin;
int authPassword;
char login[30], password[30];

char getAuthParams(char l, char password)
{

}

//int main(int argc, char * argv[])
int main(void)
{
    //pAdmin *adm;
    //adm = &administrator;

    //(*adm).login= "jimmy";
    //(*adm).password = "12345";
    //(*adm).attemps = 0;

    //pAdmin->login= "jimmy";
    //pAdmin->password = "12345";

    /* Ponteiro para struct participant */

    administrator Admin;
    administrator *pAdmin = &Admin;

    zerarAssento();

    //char *c;
    //c = &Admin.login;

    strcpy(pAdmin->login, "j");
    strcpy(pAdmin->password, "j");



    //Admin.login = "jimmy";
    //Admin.password = "teste";
    pAdmin->attempts = 0;

    while(op != SAIR)
    {
        //ENQUANTO NUMERO DE TENTATIVAS FOR MENOR OU IGUAL A 3 ? REPITA
        while(pAdmin->attempts <= 3)
        {
            //true;
            //getch();
            printf("+-----------------------------------------------------------------------------+\n");
            printf("|                                 FACA LOGIN                                  |\n");
            printf("+-----------------------------------------------------------------------------+\n");
            printf("\nDigite seu Login ==> ");
            gets(login);
            printf("\nDigite sua Senha ==> ");
            //fgets(password);
            gets(password);

            //system("read password");

            //authenticate = logar(login, password);


            //RETORNA 0 SE AS STRINGS SÃO IGUAIS
            authLogin = strcmp(login, pAdmin->login);
            authPassword = strcmp(password, pAdmin->password);

            //printf("L: %d\nS: %d\n\n", authLogin, authPassword);

            //printf("login: %s\n senha: %s\n", login, password);
            //printf("login: %s\n senha: %s\n", pAdmin->login, pAdmin->password);

            //if( ((strcmp(login, pAdmin->login)) && (strcmp(password, pAdmin->password))) == 0 )
            //if( !((authLogin && authPassword) != 0) )

            //SE AS VARIAVEIS CONTIVEREM VALOR 0, ENTAO AUTENTICARÁ LOGIN E SENHA
            if( (authLogin == 0) && (authPassword == 0) )
            {
                do
                {
                    //if(op==0) getch();
                    op = 0;

                    if(op != SAIR)
                    {
                        int re_opcao;
                        //if(isdigit)
                        op = menu_inicial(); // se autenticado chama a funcao menu

                        switch(op)
                        {
                            case 1 :
                                printf("\nGerencia participante!\n");
                                    //incluir_visitante();

                                    re_opcao = menu_visitante();

                                    switch(re_opcao)
                                    {
                                        case 1 :
                                                incluir_visitante();
                                            break;

                                        case 2 :
                                                excluir_visitante();
                                            break;

                                        case 3 :
                                                lista_assentos_livres();
                                            break;

                                        case 4 :
                                                lista_assentos_ocupados();
                                            break;

                                        case 5 :
                                                lista_tds_assentos();
                                            break;

                                        case 6 :
                                            system("cls");
                                            // retornar ao menu inicial
                                            continue;

                                        default :
                                        printf("\nOpcao Invalidada!\n");
                                        getch();
                                        system("cls");
                                    } //switch(re_opcao) MENU DE VISITANTE

                                //getch();
                            break;

                            case 2 :
                                printf("\nGerencia convidado!\n");
                                    excluir_visitante();
                                getch();
                            break;

                            case 3 :
                                printf("\nFazer sorteio!\n");
                                getch();
                            break;

                            case 4 :
                                printf("\nEnvia Email!\n");
                                getch();
                            break;

                            case 5 :
                                printf("\nSair!\n");
                                getchar();
                                system("cls");
                            break;

                            default :
                                printf("\nOpcao invalida!\n");
                                break;
                        } //switch(op) MENU INICIAL
                    } //if(op != SAIR)

                }while(op != SAIR);
            } // admin LOGADO
            else
            {
                pAdmin->attempts++;


                if((authLogin > 0) || (authPassword > 0) || (authLogin < 0) || (authPassword < 0))
                {
                    printf("\nLogin ou senha incorretos!\n");
                    getch();
                    //system("cls");
                }

                printf("\nTentativas: %d", pAdmin->attempts);
                getch();
                system("cls");
            } // Errou SENHA

            //se o numero de tentativas for = 3 entao esperar 30 segundos para tentar novamente
            if(pAdmin->attempts == ATTEMPS)
            {
                printf("\nVoce errou nas %d tentativas!\n", pAdmin->attempts);
                printf("Espere %d Segundo para tentar novamente!!!\n", TIMEOUT);

                Sleep(TIME_SLEEP);
                //int time;
                //time = timeout(TIMEOUT);
                if(timeout(TIMEOUT) == 0)
                {
                    printf("\nTempo finalizado.\n");
                }

                pAdmin->attempts = 0;
            }

        } //ENQUANTO NUMERO DE TENTATIVAS FOR <= 3 REPITA AS INSTRUÇÕES DO{}

    }

    //listar op��es
    //optionsList();

    //Executar Op��o
    //optionsExecute();

} // MAIN METODO PRINCIPAL


//Chamar opçoes de menu

//options execute

//Fun�ao para registrar um participante

//Listar todos os assentos
//findBySeat()
//listAllSeat()

zerarAssento()
{
     for(l=0; l<=8; l++)
    {
        for(c=0; c<=19; c++)
        {
            if( sP[l][c].assento_reservado != NULL)
            {
                sP[l][c].assento_reservado = 0;
            }
            else
            {
                sP[l][c].assento_reservado = 0;
            }
        }
    }
}


struct participant Aux;
struct participant *aux = &Aux;
// OP == 1
int incluir_visitante()
{
    getchar();
    system("cls");

    //struct participant *aux;

    cadParticipant( &aux);
    //sP[]

    getch();
    system("cls");
	printf("\t+------------------------------------------------+\n");
	printf("\t|           Ticket Informativo                   |\n");
	printf("\t+------------------------------------------------+\n");
    printf("\t|    Codigo do Participante .....: %d             \n", sP[l+1][c+1].cod_visitante);
	printf("\t|    B ...........: %s                            \n", sP[l+1][c+1].b);
	printf("\t|    Nome ...........: %s                         \n", sP[l+1][c+1].nome);
	printf("\t|    Data de nascimento .....: %d                 \n", sP[l+1][c+1].data_nasc);
	printf("\t|    Sexo ...........: %s                         \n", sP[l+1][c+1].sexo);
	printf("\t|    RG .....: %d                                 \n", sP[l+1][c+1].rg);
	printf("\t|    Email ...........: %s                        \n", sP[l+1][c+1].email);
	printf("\t|    Convidado .....: %s                          \n", sP[l+1][c+1].convidado);
	printf("\t|    Assento Especial ...........: %s             \n", sP[l+1][c+1].assento_especial);
	printf("\t|    Assento Reservado ...........: %d            \n", sP[l+1][c+1].assento_reservado);
	printf("\t|    Data atual do sistema e: %s                  \n", sP[l+1][c+1].dateStr);
	printf("\t|    Hora atual do sistema e: %s                  \n", sP[l+1][c+1].timeStr);
	printf("\t+------------------------------------------------+\n");
	getch();

    return re_opcao;
}
// OP == 2
int excluir_visitante()
{
    getch();
    system("cls");

    return re_opcao;
}
// OP == 3
int lista_assentos_livres()
{
    //if(re_opcao == 1)
    getch();
    system("cls");
        //listAllSeat();
}
// OP == 4
int lista_assentos_ocupados()
{
    getch();
    system("cls");
}
// OP == 5
lista_tds_assentos()
{
    int seat;
    //printf("Digite o numero do assento: \n");
    //scanf("%d", &seat);

    for(l=0; l<=8; l++)
    {
        for(c=0; c<=19; c++)
        {
            if(sP[l][c].assento_reservado != NULL)
            {
                printf("\n%d: Ocupado\t", sP[l+1][c+1].assento_reservado);
            }
            else
            {
                printf("%d: Livre\t", sP[l+1][c+1].assento_reservado);
            }
        }
    }

    printf("%d ", sizeof(sP)/sizeof(int));
    printf("\nTecle Enter para Continuar...");
    getch();
}


int cadParticipant(struct participant *aux)
{
    printf("\nNome                ==> ");
    fgets(aux->nome, 256, stdin);
    //scanf ( "%256[^\n]", str);
    //scanf ( "%[^\n]", aux->nome);
    //printf("\nteste\n");
    printf("\nData de nascimento  ==> ");
    fgets(aux->data_nasc, 256, stdin);
    printf("\Sexo                 ==> ");
    fgets(aux->sexo, 256, stdin);
    printf("\RG                   ==> ");
    fgets(aux->rg, 256, stdin);
    printf("\nEmail               ==> ");
    fgets(aux->email, 256, stdin);
    printf("\nConvidado           ==> ");
    scanf("%d", &aux->convidado);
    printf("\nAssento Especial    ==> ");
    scanf("%d", &aux->assento_especial);
    printf("\nAssento Reservado   ==> ");
    scanf("%d", &aux->assento_reservado);

    aux->b = 10;
    aux->assento_reservado = 10;

    //(*aux).nome = {0 => 'j', 1 => 'i', 2 => 'm', 3 => 'm', 4 => 'y'};
    printf("\n%s", aux->nome);
    printf("Data de nascimento ==> \n");
    printf("Data de nascimento ==> \n");
    printf("Data de nascimento ==> \n");
    printf("Data de nascimento ==> \n");
    printf("Data de nascimento ==> \n");
    printf("Data de nascimento ==> \n");
    printf("Data de nascimento ==> \n");

    system("PAUSE");
}

