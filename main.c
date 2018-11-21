#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
//includes do programa
#include "login.c"
#include "menu.c"

#define TIMEOUT          5  //segundos
#define TIME_SLEEP       10 //30000ms == 30segundos
#define ATTEMPS          3  //numero de tentativas autenticar login e senha
#define G_PARTICIPANTE   1  //OP gerenciar participante
#define G_CONVIDADO      2  //OP Gerencial convidado
#define SORTEIO          3  //OP Sorteio
#define ENVIAR_EMAIL     4  //OP Enviar Email
#define SAIR             5  //OP Sair

/*capacidade de assentos na palestra*/
#define QTD_TT 179
//typedef struct administrator Admin;
//login
typedef struct
{
    char login[30];
    char password[30];
    int attempts;
}administrator;
    //struct administrator admin;

    int i, op, num_seat, flag, re_opcao, l, c, o, s;
    /*Criando a struct */
typedef struct participant
{
    int     b;
    int     flag;
    int     free;
    int     adm;
    int     cod_visitante;
    char    nome[50];
    char    data_nasc[20];
    char    sexo[20];
    char    rg[20];
    char    email[30];
    char    convidado[3]; //convidado -> sim ou nao (maximos 10 convidados)
    char    assento_especial[3]; //Lugar especial -> sim ou nao (maximos 3)
    int     assento_reservado;
	char    dateStr[9];
    char    timeStr[9];
}participant;
    //(S)TRUCT (P)ARTICIPANT sP => struct-matriz do tipo participant
    struct participant sP[QTD_TT];

    struct participant Aux;
    struct participant *aux = &Aux;
    //struct participant *aux = &sP;

int authLogin;
int authPassword;
char login[30], password[30];
char getAuthParams(char l, char password)
{
}
void lista_tds_assentos(void);
void zerarAssentos(void);

int main(void)
{
    printf("%d", QTD_TT);
    /* Ponteiro para struct participant */
    administrator Admin;
    administrator *pAdmin = &Admin;

    zerarAssentos();

    strcpy(pAdmin->login, "");
    strcpy(pAdmin->password, "");

    pAdmin->attempts = 0;

    while(op != SAIR)
    {
        //ENQUANTO NUMERO DE TENTATIVAS FOR MENOR OU IGUAL A 3 ? REPITA
        while(pAdmin->attempts <= 3)
        {
            printf("\t\t+-----------------------------------------------------------------------------+\n");
            printf("\t\t|                                 FACA LOGIN                                  |\n");
            printf("\t\t+-----------------------------------------------------------------------------+\n");
            printf("\n\t\tDigite seu Login ==> ");
            fflush(stdin);
            gets(login);
            printf("\n\t\tDigite sua Senha ==> ");

            s = strlen(pAdmin->password);
            fflush(stdin);
            for (i=0;i<=(s-1);i++) 
            {
                password[i] = getch();
                putchar('*');
            }
            printf("\n");
            password[i]='\0';

            //RETORNA 0 SE AS STRINGS SÃO IGUAIS
            authLogin = strcmp(login, pAdmin->login);
            authPassword = strcmp(password, pAdmin->password);

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
                                    re_opcao = op;
                                    //re_opcao = menu_visitante();
	                                do
									{
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

                               		}while(re_opcao != 6);

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


                //if((authLogin > 0) || (authPassword > 0) || (authLogin < 0) || (authPassword < 0))
                if((authLogin != 0) || (authPassword != 0))
                {
                    printf("\n\t\tLogin ou senha incorretos!\n");
                    getch();
                    //system("cls");
                }

                printf("\n\t\tTentativas: %d", pAdmin->attempts);
                getch();
                system("cls");
            } // Errou SENHA

            //se o numero de tentativas for = 3 entao esperar 30 segundos para tentar novamente
            if(pAdmin->attempts == ATTEMPS)
            {
                printf("\n\t\tVoce errou nas %d tentativas!\n", pAdmin->attempts);
                printf("\t\tEspere %d Segundo para tentar novamente!!!\n", TIMEOUT);

                Sleep(TIME_SLEEP);
                if(timeout(TIMEOUT) == 0)
                {
                    printf("\n\t\tTempo finalizado.\n");
                }

                pAdmin->attempts = 0;
            }

        } //ENQUANTO NUMERO DE TENTATIVAS FOR <= 3 REPITA AS INSTRUÇÕES DO{}

    }

    return 0;

} // MAIN METODO PRINCIPAL


void zerarAssentos(void)
{
    i=0;
    fflush(stdin);
     for(i=0; i<=QTD_TT; i++)
    {
        sP[i].assento_reservado = 0;
        l++;
    }
    printf("\n\t\tAssentos zerados = %d\n", l);
}

// OP == 1
int incluir_visitante()
{
    getchar();
    system("cls");
    //struct participant *aux;
    //cadParticipant( &aux);
	cadParticipant( &aux);
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
    i=0;l=0;c=0;
    //if(re_opcao == 1)
    //getch();
    system("cls");
    system("color 0B");

    for(i=0; i<=QTD_TT; i++)
    {
        if (sP[i].assento_reservado == 0 )
        {
            printf(" %03d:L\t", i+1);
            l++;
        }
    }
    printf("\nTecle Enter para Continuar...");
    getch();
    system("color 0F");

    return re_opcao;
}
// OP == 4
lista_assentos_ocupados(void)
{
    i=0;l=0;c=0;
    //if(re_opcao == 1)
    //getch();
    system("cls");
    system("color 0C");

    for(i=0; i<=QTD_TT; i++)
    {
        if (sP[i].assento_reservado > 0 )
        {
            printf(" %03d:O\t", i+1);
            l++;
        }
    }
    if (l == 0)
        printf("\nNAO HA ASSENTO(S) OCUPADO(S).\n");
    getch();
    system("color 0F");

    return re_opcao;
}
// OP == 5
lista_tds_assentos(void)
{
    //system("color 1F");
    //background(GREEN);
    system("cls");
    //system("color 0B");
    printf("\nInstrucoes:\n");
    //system("color 07");
    //foreground(BLUE);
    printf("Assentos LIVRES estao com letra: L\n");
    //background(GREEN);
    printf("Assentos OCUPADOS estao com letra: O\n\n");
    //style(RESETALL);
    i=0;l=0;
    for(i=0; i<=QTD_TT; i++)
    {
        //for(int a='A';a!='Z';a++)printf("%c ",a);
        if(sP[i].assento_reservado == 0)
        {
            //contagem de assentos livres
            l++;
            //system("color 0B");
            printf(" %03d:L\t", i+1);
            //printf(ANSI_COLOR_GREEN " %03d:L\t" ANSI_COLOR_RESET, i);
        }
        else
        {
            //contagem de assentos ocupados
            o++;
            //system("color 0C");
            printf(" %03d:O\t", i+1);
            //printf(ANSI_COLOR_RED " %03d:O\t" ANSI_COLOR_RESET, i);
        }
    }

    printf("\n\t\t\t\t%d ASSENTO(S) OCUPADO(S) \t%d ASSENTO(S) LIVRE(S) \n\n", o, l);
    o=0;l=0;
    printf("\nTecle Enter para Continuar...");
    getch();
    system("color 0F");

    return re_opcao;
}

//verifica e cadastra participante
int cadParticipant(struct participant *aux)
{
    lista_tds_assentos();
    printf("\nPreencha seus dados:");
    printf("\nNome                ==> ");
    //fgets(aux->nome, 50, stdin);
    fflush(stdin);
    gets(aux->nome);
    printf("\nData de Nasc ex.: 00/00/00 ==> ");
    gets(aux->data_nasc);
    //fgets(aux->data_nasc, 20, stdin);
    printf("\nSexo \t\t==> ");
    gets(aux->sexo);
    //fgets(aux->sexo, 20, stdin);
    printf("\nRG \t\t==> ");
    gets(aux->rg);
    //fgets(aux->rg, 20, stdin);
    printf("\nEmail \t\t==> ");
    gets(aux->email);
    //fgets(aux->email, 30, stdin);
    printf("\nConvidado (S/N) \t==> ");
    fgets(aux->convidado, 3, stdin);
    printf("\nAssento Especial(S/N) \t==> ");
    fgets(aux->assento_especial, 3, stdin);
    /*
    
    do
    {
        fflush(stdin);
        printf("\nConvidado (S/N) \t==> ");
        scanf("%s", &aux->convidado);
        if(isupper(aux->convidado))
        {
            tolower(*aux->convidado);
        }

    }while( (aux->convidado != 's' ) || (aux->convidado != 'n') );
    do
    {
        printf("\nAssento Especial(S/N) \t==> ");
        scanf("%s", &aux->assento_especial);
    }while(aux->assento_especial != 's');

    */

    i=0;l=0;c=0;
    //lista_tds_assentos(); ENCONTRAR ERRO

    do
    {
        printf("\nEscolha um assento:   ==> ");
        scanf("%d", &aux->assento_reservado);
        num_seat = aux->assento_reservado;
        if( !(isdigit(aux->assento_reservado)) )
        {
            printf("\n\t\tDIGITE SOMENTE NUMEROS! ");
            getch();
            system("cls");
        }
        if( (num_seat) == (sP[num_seat-1].assento_reservado) )
        {
            printf("\n\t\tO NUMERO DE ASSENTO REQUISITADO ESTA OCUPADO! \n");
            printf("***********************\n");
            getch();
            system("cls");
        }

    }while( (!isdigit(aux->assento_reservado) && (aux->assento_reservado == sP[num_seat-1].assento_reservado) ) && ( (aux->assento_reservado < 1) || ( (aux->assento_reservado > (QTD_TT+1) ) ) ) );

    // pega a data atual
     _strdate(  aux->dateStr );
    // pega a hora atual
    _strtime( aux->timeStr );

    sP[num_seat-1] = *aux;
    //getch();
    system("cls");
    system("color 1F");
    printf("\n");
    printf("\t\t\t+------------------------------------------------+\n");
    printf("\t\t\t|           Ticket Informativo                   |\n");
    printf("\t\t\t+------------------------------------------------+\n");
    printf("\t\t\t|    Codigo do Participante .....: %d \n", sP[num_seat-1].cod_visitante);
    printf("\t\t\t|    B ..........................: %d \n", sP[num_seat-1].b);
    printf("\t\t\t|    Nome .......................: %s \n", sP[num_seat-1].nome);
    printf("\t\t\t|    Data de nascimento .........: %s \n", sP[num_seat-1].data_nasc);
    printf("\t\t\t|    Sexo .......................: %s \n", sP[num_seat-1].sexo);
    printf("\t\t\t|    RG .........................: %s \n", sP[num_seat-1].rg);
    printf("\t\t\t|    Email ......................: %s \n", sP[num_seat-1].email);
    printf("\t\t\t|    Convidado ..................: %s \n", sP[num_seat-1].convidado);
    printf("\t\t\t|    Assento Especial ...........: %s \n", sP[num_seat-1].assento_especial);
    printf("\t\t\t|    Assento Reservado ..........: %d \n", sP[num_seat-1].assento_reservado);
    printf("\t\t\t|    Data atual do sistema ......: %s \n", sP[num_seat-1].dateStr);
    printf("\t\t\t|    Hora atual do sistema ......: %s \n", sP[num_seat-1].timeStr);
    printf("\t\t\t+------------------------------------------------+\n");
    printf("\nTecle Enter para Continuar...");
    getch();
    system("cls");
    system("color 0F");

    return re_opcao;
}


