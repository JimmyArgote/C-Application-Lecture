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
#define QTD_L       8  /* LINHAS */
#define QTD_C      19 /* Colunas */
const int QTD_TT = ( (QTD_L+1) * (QTD_C+1) );
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
typedef struct participant
{
    int     b;
    int     flag;
    int     adm;
    int     cod_visitante;
    char    nome[50];
    char    data_nasc[20];
    char    sexo[20];
    char    rg[20];
    char    email[30];
    int     convidado; //convidado -> sim ou n?o (m?ximos 10 convidados)
    int     assento_especial; //Lugar especial -> sim ou n?o (m?ximos 3)
    int     assento_reservado;
	char    dateStr[9];
    char    timeStr[9];
}participant;
    //(S)TRUCT (P)ARTICIPANT sP => struct-matriz do tipo participant
    struct participant sP[QTD_L][QTD_C];

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
void zerarAssento(void);

int main(void)
{
    printf("%d", QTD_TT);
    /* Ponteiro para struct participant */
    administrator Admin;
    administrator *pAdmin = &Admin;

    zerarAssento();

    strcpy(pAdmin->login, "j");
    strcpy(pAdmin->password, "j");

    pAdmin->attempts = 0;

    while(op != SAIR)
    {
        //ENQUANTO NUMERO DE TENTATIVAS FOR MENOR OU IGUAL A 3 ? REPITA
        while(pAdmin->attempts <= 3)
        {
            printf("+-----------------------------------------------------------------------------+\n");
            printf("|                                 FACA LOGIN                                  |\n");
            printf("+-----------------------------------------------------------------------------+\n");
            printf("\nDigite seu Login ==> ");
            fflush(stdin);
            gets(login);
            printf("\nDigite sua Senha ==> ");
            gets(password);

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
                if(timeout(TIMEOUT) == 0)
                {
                    printf("\nTempo finalizado.\n");
                }

                pAdmin->attempts = 0;
            }

        } //ENQUANTO NUMERO DE TENTATIVAS FOR <= 3 REPITA AS INSTRUÇÕES DO{}

    }

    return 0;

} // MAIN METODO PRINCIPAL


void zerarAssento(void)
{
    i=0;
    fflush(stdin);
     for(l=0; l<=QTD_L; l++)
    {
        for(c=0; c<=QTD_C; c++)
        {
            sP[l][c].assento_reservado = 0;
            i++;
        }
    }
    printf("\nAssentos zerados = %d\n", i);
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

    for(l=0; l<=QTD_L; l++)
    {
        for(c=0; c<=QTD_C; c++)
        {
            i++;
            if (sP[l][c].assento_reservado == 0 )
            {
                printf(" %03d:L\t", i);
            }

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

    for(l=0; l<=QTD_L; l++)
    {
        for(c=0; c<=QTD_C; c++)
        {
            i++;
            if (sP[l][c].assento_reservado > 0 )
            {
                printf(" %03d:O\t", i);
            }
            else
            {
                i = 0;
            }

        }
    }
    if (i==0)
        printf("\nNao ha assentos ocupados.\n");
    getch();
    system("color 0F");
    
    return re_opcao;
}
// OP == 5
lista_tds_assentos(void)
{
    int seat;
    //printf("Digite o numero do assento: \n");
    //scanf("%d", &seat);

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

    i=0;l=0;c=0;
    for(l=0; l<=QTD_L; l++)
    {
        //for(int a='A';a!='Z';a++)printf("%c ",a);
        for(c=0; c<=QTD_C; c++)
        {
            i++;
            if(sP[l][c].assento_reservado != 0)
            {
                //printf("\n%d:O\t", sP[l+1][c+1].assento_reservado);
                //incremento para linha com valor > 0
                //i++;
                //system("color 0C");
                printf(" %03d:O\t", i);
                //printf(ANSI_COLOR_RED " %03d:O\t" ANSI_COLOR_RESET, i);
            }
            else
            {
                i--;
                if(sP[l][c].assento_reservado == 0)
                {
                    //decremento para linha com valor == 0

                    //printf("%d:L\t", sP[l+1][c+1].assento_reservado);
                    //incremento para linha com valor == 0
                    i++;
                    //system("color 0B");
                    printf(" %03d:L\t", i);
                    //printf(ANSI_COLOR_GREEN " %03d:L\t" ANSI_COLOR_RESET, i);
                }
                else
                {
                    i++;
                    //system("color 0C");
                    printf(" %03d:O\t", i);
                    //printf(ANSI_COLOR_RED " %03d:O\t" ANSI_COLOR_RESET, i);
                }
            }
            //incremento para coluna
        }
    }

    //printf("%d ", sizeof(sP)/sizeof(int));
    printf("\nTecle Enter para Continuar...");
    getch();
    system("color 0F");
    
    return re_opcao;
}

//verifica e cadastra participante
int cadParticipant(struct participant *aux)
{
    int v[3];
    //int y=0,x=0;
    printf("\nPreencha seus dados:");
    getch();
    printf("\nNome                ==> ");
    //fgets(aux->nome, 50, stdin);
    fflush(stdin);
    gets(aux->nome);
    printf("\nData de Nasc ex.: 00/00/00 ==> ");
    gets(aux->data_nasc);
    //fgets(aux->data_nasc, 20, stdin);
    printf("\nSexo                 ==> ");
    gets(aux->sexo);
    //fgets(aux->sexo, 20, stdin);
    printf("\nRG                   ==> ");
    gets(aux->rg);
    //fgets(aux->rg, 20, stdin);
    printf("\nEmail               ==> ");
    gets(aux->email);
    //fgets(aux->email, 30, stdin);
    printf("\nConvidado           ==> ");
    scanf("%d", &aux->convidado);
    printf("\nAssento Especial(S/N)    ==> ");
    scanf("%d", &aux->assento_especial);

    i=0;l=0;c=0;
    //lista_tds_assentos(); ENCONTRAR ERRO
    do
    {

        do
        {
            printf("\nEscolha um assento:   ==> ");
            scanf("%d", &aux->assento_reservado);
        }while( (!isdigit(aux->assento_reservado)) && ( (aux->assento_reservado < 1) || ( (aux->assento_reservado > (QTD_TT) ) ) ) );
        //while( !(isdigit(aux->assento_reservado)) && (aux->assento_reservado <) );

        // pega a data atual
         _strdate(  aux->dateStr );
        // pega a hora atual
        _strtime( aux->timeStr );

        for(l=0; l<=QTD_L; l++)
        {
            //i++;
            if (i==0)
                i++;
            //printf("\n%d\t", l);
            //printf("\n%d\t", i);
            if (i == 1)
                i--;
            for(c=0; c<=QTD_C; c++)
            {
                //sP[l][c].assento_reservado = 0;
                i++;
                //if(aux->assento_reservado == i)
                //printf("%d\t", c);
                //printf("%d\t", i);
                if(i == aux->assento_reservado)
                {
                    if( (sP[l][c].assento_reservado) == (aux->assento_reservado) )
                    {
                        v[3] = 0, 0, 0;
                        v[0] = i; //indices percorridos equivalente ao numero do assento digitado pelo usuario
                        v[1] = l; //numero do indice
                        v[2] = c;
                        printf("\nO lugar esta Ocupado!\n");
                        printf("***********************\n");
                        //printf("assento = %d\t linha = %d\t coluna = %d\n", aux->assento_reservado, l, c);
                        getch();
                    }
                    else
                    {
                        //sP[l][c].assento_reservado = aux->assento_reservado;
                        sP[l][c] = *aux;
                        //getch();
                        system("cls");
                        system("color 1F");
                        printf("\t+------------------------------------------------+\n");
                        printf("\t|           Ticket Informativo                   |\n");
                        printf("\t+------------------------------------------------+\n");
                        printf("\t|    Codigo do Participante .....: %d             \n", sP[l][c].cod_visitante);
                        printf("\t|    B ...........: %d                            \n", sP[l][c].b);
                        printf("\t|    Nome ...........: %s                         \n", sP[l][c].nome);
                        printf("\t|    Data de nascimento .....: %s                 \n", sP[l][c].data_nasc);
                        printf("\t|    Sexo ...........: %s                         \n", sP[l][c].sexo);
                        printf("\t|    RG .....: %s                                 \n", sP[l][c].rg);
                        printf("\t|    Email ...........: %s                        \n", sP[l][c].email);
                        printf("\t|    Convidado .....: %d                          \n", sP[l][c].convidado);
                        printf("\t|    Assento Especial ...........: %d             \n", sP[l][c].assento_especial);
                        printf("\t|    Assento Reservado ...........: %d            \n", sP[l][c].assento_reservado);
                        printf("\t|    Data atual do sistema e: %s                  \n", sP[l][c].dateStr);
                        printf("\t|    Hora atual do sistema e: %s                  \n", sP[l][c].timeStr);
                        printf("\t+------------------------------------------------+\n");
                        printf("\nTecle Enter para Continuar...");
                        getch();
                        system("cls");
                        system("color 0F");
                    }
                }
            }
        }
            //printf("\nTecle Enter para Continuar...");
            //printf("\nI = Assento %d\n", v[0]);
            //printf("L = Linha %d\n", v[1]);
            //printf("C = Coluns %d\n", v[2]);
            //getch();

    }while( (aux->assento_reservado) == (sP[v[1]][v[2]].assento_reservado) );

    return re_opcao;
}
