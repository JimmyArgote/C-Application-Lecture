#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <locale.h>

//includes do programa
#include "login.c"
#include "menu.c"

#define TIMEOUT          5  //segundos
#define TIME_SLEEP       10 //30000ms == 30segundos
#define ATTEMPS          3  //numero de tentativas autenticar login e senha
#define SAIR             5  //OP Sair
#define BACKGROUND_BLACK    "\033[1;40m"

 /* Quantidade de indices do vetor */
/*capacidade de assentos na palestra 180*/
#define QTD_TT 180

typedef struct
{
    char login[30];
    char password[30];
    int attempts;
}administrator;
    //struct administrator admin;

    int i, op, num_seat, re_opcao, l, c, o, s, retorno;
    char capture[3];
    /*Criando a struct */
typedef struct participant
{
    char    cod_visitante[20];
    char    nome[30];
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
    participant sP[QTD_TT];

    participant Aux;
    participant *aux = &Aux;

    /* Ponteiro para struct participant */
    administrator Admin;
    administrator *pAdmin = &Admin;

int authLogin;
int authPassword;
char login[30], password[30], wireless[30], l_wireless[30];

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    system("color 0F");

    // preenche todos os assentos com valor (0)
    zerarAssentos();
    strcpy(l_wireless, "UNIP-ADS-2018");
    strcpy(wireless, "palestraDH");

    novoCadastro();

    pAdmin->attempts = 0;

    while(op != SAIR)
    {
        //ENQUANTO NUMERO DE TENTATIVAS FOR MENOR OU IGUAL A 3 ? REPITA
        while(pAdmin->attempts <= 3)
        {
            printf("\n\t\t\t\t+-----------------------------------------------------------------------------+\n");
            printf("\t\t\t\t|                                 FAÇA LOGIN                                  |\n");
            printf("\t\t\t\t+-----------------------------------------------------------------------------+\n");
            printf("%s\n", login);
            printf("\n\t\t\t\tDigite seu Login ==> ");
            fflush(stdin);
            gets(login);
            printf("\n\t\t\t\tDigite sua Senha ==> ");

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
                    op = 0;

                    if(op != SAIR)
                    {
                        int re_opcao;
                        op = menu_inicial(); // se autenticado chama a funcao menu

                        switch(op)
                        {
                            case 1 :
                                printf("\nGerenciar participante!\n");
                                    re_opcao = op;
	                                do
									{
                                    	re_opcao = menu_visitante();
	                                    switch(re_opcao)
	                                    {
	                                        case 1 :
                                                retorno = contaAssentosOcupados();
                                                (retorno == QTD_TT)? printf("\nNão há assentos disponíveis!\n"), system("PAUSE") : incluir_visitante();

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
	                                            system("clear || cls");
	                                            // retornar ao menu inicial
	                                            continue;

	                                        default :
	                                        printf("\n\t\tOpção Inválida!\n");
	                                        getch();
	                                        system("clear || cls");

	                                    } //switch(re_opcao) MENU DE VISITANTE

                               		}while(re_opcao != 6);

                                //getch();
                            break;

                            case 2 :
                                printf("\n\t\t\tTodos os Assentos foram Preenchidos para teste!\n");
                                //TESTE DE PREENCHIMENTO DE DADOS AUTOMATIZADO
                                testePreencherAssentos();
                                getch();
                            break;

                            case 3 :
                            retorno = 0;
                                system("clear || cls");
                                imprimechar(40, '-');
                                printf("\n\t\t\t\t\t\t\tFAZER SORTEIO!\n");
                                imprimechar(40, '-');
                                printf("\t\t\t\tDigite quantas pessoas deseja sortear..: ");
                                scanf("%d", &retorno);
                                sorteio(retorno);
                                getch();
                            break;

                            case 4 :
                                system("clear || cls");
                                imprimechar(40, '-');
                                printf("\n\t\t\t\t\t\t\tENVIO DE EMAILS!\n");
                                imprimechar(40, '-');
                                envia_email();
                            break;

                            case 5 :
                                printf("\nSair!\n");
                                getchar();
                                system("clear || cls");
                            break;

                            default :
                                printf("\n\t\tOpcao inválida!\n");
                                break;
                        } //switch(op) MENU INICIAL
                    } //if(op != SAIR)

                }while(op != SAIR);
            } // admin LOGADO
            else
            {
                pAdmin->attempts++;

                if((authLogin != 0) || (authPassword != 0))
                {
                    printf("\n\t\tLogin ou senha incorretos!\n");
                    getch();
                }

                printf("\n\t\tTentativas: %d", pAdmin->attempts);
                getch();
                system("clear || cls");
            } // Errou SENHA

            //se o numero de tentativas for = 3 entao esperar 30 segundos para tentar novamente
            if(pAdmin->attempts == ATTEMPS)
            {
                printf("\n\t\tVoce errou nas %d tentativas!\n", pAdmin->attempts);
                printf("\t\tEspere %d Segundo para tentar novamente!!!\n", TIMEOUT);

                Sleep(TIME_SLEEP);
                (timeout(TIMEOUT) == 0)? printf("\n\t\tTempo finalizado.\n") : TIMEOUT ;

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
     for(i=0; i<QTD_TT; i++)
    {
        sP[i].assento_reservado = 0;
        strcpy(sP[i].convidado, "\0");
        l++;
    }
}

// OP == 1
int incluir_visitante()
{
    getchar();
    system("clear || cls");
	cadParticipant( &aux);
    return re_opcao;
}
// OP == 2
int excluir_visitante()
{
    num_seat = 0;
    printf("\n\t\t\t\t\t\tDigite o número do Assento que deseja Excluir:\n\n\t\t\t\t\t\t");
    scanf("%d", &num_seat);

    // se numero do assento digitado for diferente do numero do indice equivalente do vetor, e seu valor de assento_reservado  forem iguais
    // entao quer dizer que o assento esta livre
    if(num_seat != sP[num_seat-1].assento_reservado)
    {
        printf("\nO número do assento está livre!\n");
    }
    else
    {
        printf("\t\t\t\t\t\tCodigo do Participante .....: %s \n", sP[num_seat-1].cod_visitante);
        printf("\t\t\t\t\t\tNome .......................: %s \n", sP[num_seat-1].nome);
        printf("\t\t\t\t\t\tData de nascimento .........: %s \n", sP[num_seat-1].data_nasc);
        printf("\t\t\t\t\t\tSexo .......................: %s \n", sP[num_seat-1].sexo);
        printf("\t\t\t\t\t\tRG .........................: %s \n", sP[num_seat-1].rg);
        printf("\t\t\t\t\t\tEmail ......................: %s \n", sP[num_seat-1].email);
        printf("\t\t\t\t\t\tConvidado ..................: %s \n", sP[num_seat-1].convidado);
        printf("\t\t\t\t\t\tAssento Especial ...........: %s \n", sP[num_seat-1].assento_especial);
        printf("\t\t\t\t\t\tAssento Reservado ..........: %d \n", sP[num_seat-1].assento_reservado);
        printf("\t\t\t\t\t\tData atual do sistema ......: %s \n", sP[num_seat-1].dateStr);
        printf("\t\t\t\t\t\tHora atual do sistema ......: %s \n", sP[num_seat-1].timeStr);
        printf("\n\t\t\t\t\t\t");
        sP[num_seat-1].assento_reservado = 0;
        strcpy(sP[num_seat-1].convidado, "\0");
        printf("\n\t\t\t\t\t\tParticipante: %s Excluído com sucesso!\n\n\t\t\t\t\t\t", sP[num_seat-1].nome );
    }

    system("PAUSE");
    system("clear || cls");

    return re_opcao;
}
// OP == 3 FUNCAO QUE LISTA TODOS OS ASSENTOS LIVRES
int lista_assentos_livres()
{
    i=0;l=0;c=0;

    system("clear || cls");
    system("color 0B");
    //formatacao do titulo da tela
    imprimechar(40, '-');
    printf("\t\t\t\t\t\t\t\tASSENTOS LIVRES");
    imprimechar(40, '-');
    printf("\nInstruções:\n");
    printf(" - Numeração de Assento com letra final 'E': Assento para Pessoas Portadoras de Necessidades Especiais. \n");
    printf(" - Numeração de Assento com letra final 'C': Assento para Convidados.\n");
    printf(" - Numeração de Assento com letra final 'P': Assento para Participantes.\n\n");

    for(i=0; i<QTD_TT; i++)
    {
        if (sP[i].assento_reservado == 0 )
        {
            if((i >= 0) && (i <= 19))
                printf(" %03d:E\t", i+1);
            if((i >= 20) && (i <= 59))
                printf(" %03d:C\t", i+1);
            if((i >= 60) && (i <= 179))
                printf(" %03d:P\t", i+1);
            l++;
        }
    }
    if (l == 0)
    {
        printf("\nNÃO HÁ ASSENTO(S) LIVRE(S).\n");
        system("PAUSE");
    }
    else
    {
        printf("\n\n");
        system("PAUSE");
    }
    system("color 0F");

    return re_opcao;
}
// OP == 4 FUNCAO QUE LISTA TODOS OS ASSENTOS OCUPADOS
int lista_assentos_ocupados(void)
{
    i=0;l=0;c=0;
    system("clear || cls");
    system("color 0C");

    imprimechar(40, '-');
    printf("\t\t\t\t\t\t\t\tASSENTOS OCUPADOS");
    imprimechar(40, '-');
    printf("\nInstruções:\n");
    printf(" - Numeração de Assento com letra final 'E': Assento para Pessoas Portadoras de Necessidades Especiais. \n");
    printf(" - Numeração de Assento com letra final 'C': Assento para Convidados.\n");
    printf(" - Numeração de Assento com letra final 'P': Assento para Participantes.\n\n");

    for(i=0; i<QTD_TT; i++)
    {
        if (sP[i].assento_reservado > 0 )
        {
            if((i >= 0) && (i <= 19))
                printf(" %03d:E\t", i+1);
            if((i >= 20) && (i <= 59))
                printf(" %03d:C\t", i+1);
            if((i >= 60) && (i <= 179))
                printf(" %03d:P\t", i+1);
            l++;
        }
    }
    if (l == 0)
    {
        printf("\nNÃO HÁ ASSENTO(S) OCUPADO(S).\n");
        system("PAUSE");
    }
    else
    {
        printf("\n\n");
        system("PAUSE");
    }
    system("color 0F");

    return re_opcao;
}
// OP == 5 FUNCAO QUE LISTA TODOS OS ASSENTOS
int lista_tds_assentos(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    system("color 0F");
    system("clear || cls");

    imprimechar(40, '-');
    printf("\t\t\t\t\t\t\t\tTODOS OS ASSENTOS");
    imprimechar(40, '-');
    printf("\n-Instruções:\n");
    printf(" - Assentos LIVRES estão com o número do assento na cor VERDE.\n");
    printf(" - Assentos OCUPADOS estão com o número do assento na cor VERMELHO.\n");
    printf(" - Numeração de Assento com letra final 'E': Assento para Pessoas Portadoras de Necessidades Especiais. \n");
    printf(" - Numeração de Assento com letra final 'C': Assento para Convidados.\n");
    printf(" - Numeração de Assento com letra final 'P': Assento para Participantes.\n\n");
    i=0;l=0;
    for(i=0; i<QTD_TT; i++)
    {
        if(sP[i].assento_reservado == 0)
        {
            //contagem de assentos livres
            l++;
            SetConsoleTextAttribute(hConsole, BACKGROUND_BLACK);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            if((i >= 0) && (i <= 19))
                printf(" %03d:E\t", i+1);
            if((i >= 20) && (i <= 59))
            {
                //(i==20? printf("\n") : printf(""));
                printf(" %03d:C\t", i+1);
            }
            if((i >= 60) && (i <= 179))
            {
                //(i==60? printf("\n") : printf(""));
                printf(" %03d:P\t", i+1);
            }
            SetConsoleTextAttribute(hConsole, saved_attributes);
        }
        else
        {
            //contagem de assentos ocupados
            o++;
            SetConsoleTextAttribute(hConsole, BACKGROUND_BLACK);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            if((i >= 0) && (i <= 19))
                printf(" %03d:E\t", i+1);
            if((i >= 20) && (i <= 59))
                printf(" %03d:C\t", i+1);
            if((i >= 60) && (i <= 179))
                printf(" %03d:P\t", i+1);
            SetConsoleTextAttribute(hConsole, saved_attributes);
        }
    }

    printf("\n\t\t\t\t\t%d ASSENTO(S) OCUPADO(S) \t\t%d ASSENTO(S) LIVRE(S) \n\n", o, l);
    SetConsoleTextAttribute(hConsole, saved_attributes);
    o=0;l=0;
    system("PAUSE");

    return re_opcao;
}

//verifica e cadastra participante
int cadParticipant(participant *aux)
{
    lista_tds_assentos();
    gerarCodigo();

    printf("\nPreencha seus dados:");
    printf("\nNome                ==> ");
    fflush(stdin);
    gets(aux->nome);
    strcpy(sP[num_seat-1].nome, aux->nome);

    printf("\nData de Nasc ex.: 00-00-0000 ==> ");
    fgets(aux->data_nasc, 20, stdin);

    printf("\nSexo \t\t==> ");
    fgets(aux->sexo, 20, stdin);

    printf("\nRG \t\t==> ");
    fgets(aux->rg, 20, stdin);

    printf("\nEmail \t\t==> ");
    fgets(aux->email, 30, stdin);

    do
    {
        printf("\nConvidado (S/N) \t==> ");
        gets(aux->convidado);

        // \0 == VAZIO, enquanto a comparação de aux->convidado para "n" e "s" retornar != de 0 entao repita
        retorno = 1;
        retorno = (strcmpi(aux->convidado, "n") == 0)? strcmpi(aux->convidado, "n") : retorno;
        retorno = (strcmpi(aux->convidado, "s") == 0)? strcmpi(aux->convidado, "s") : retorno;
        (retorno != 0)? printf("\nDigite somente um caracter S ou N!\n") : printf("\t");

    }while( (retorno != 0) );

    do
    {
        printf("\nAssento Especial(S/N) \t==> ");
        gets(aux->assento_especial);

        // \0 == VAZIO, enquanto a comparação de aux->convidado para "n" e "s" retornar != de 0 entao repita
        retorno = 1;
        retorno = (strcmpi(aux->assento_especial, "n") == 0)? strcmpi(aux->assento_especial, "n") : retorno;
        retorno = (strcmpi(aux->assento_especial, "s") == 0)? strcmpi(aux->assento_especial, "s") : retorno;
        (retorno != 0)? printf("\nDigite somente um caracter S ou N!\n") : printf("\t");

    }while( (retorno != 0) );

    i=0;l=0;c=0;
    // convidado
    if( (strcmpi(aux->convidado, "s") == 0 ) && (strcmpi(aux->assento_especial, "n") == 0 ) )
    {
        printf("\n\tAssentos para convidados: de 21 até 60.\n");
        
        do
        {
            printf("\nEscolha um assento:   ==> ");
            scanf("%d", &aux->assento_reservado);
            //num_seat -> recebe o numero do assento digitado pelo usuário para ser verificado
            num_seat = aux->assento_reservado;
            if( isdigit(num_seat) )
            {
                printf("\n\t\tDIGITE SOMENTE NÚMEROS! ");
                getch();
            }
            if( (num_seat > 20) && (num_seat < 61) )
            {
                if( (num_seat) == (sP[num_seat-1].assento_reservado) )
                {
                    printf("\n\t\tO NÚMERO DE ASSENTO REQUISITADO ESTÁ OCUPADO! \n");
                    printf("\t\t***********************\n");
                    getch();
                }
            }
            if ( (num_seat < 21) || (num_seat > 60) )
            {
                printf("\n\t\tDIGITE SOMENTE NÚMEROS DE 21 ATE 60! \n");
                printf("\t\t***********************\n");
                getch();
            }

        }while( ( !isdigit(num_seat) && (num_seat == sP[num_seat-1].assento_reservado) ) || ( (num_seat < 21) || ( (num_seat > 60) ) ) );
    }
    else
    {   
        // não convidado
        if( (strcmpi(aux->convidado, "n") == 0 ) && (strcmpi(aux->assento_especial, "n") == 0 ) )
        {
            printf("\n\tAssentos para não convidados: de 61 até 180.\n");
            do
            {
                printf("\nEscolha um assento:   ==> ");
                scanf("%d", &aux->assento_reservado);
                //num_seat -> recebe o numero do assento digitado pelo usuário para ser verificado
                num_seat = aux->assento_reservado;

                if( isdigit(num_seat) )
                {
                    printf("\n\t\tDIGITE SOMENTE NÚMEROS! ");
                    getch();
                }
                if(num_seat > 0)
                {
                    if( (num_seat) == (sP[num_seat-1].assento_reservado) )
                    {
                        printf("\n\t\tO NÚMERO DE ASSENTO REQUISITADO ESTÁ OCUPADO! \n");
                        printf("\t\t***********************\n");
                        getch();
                    }
                }
                if ( (num_seat < 61) || (num_seat > QTD_TT) )
                {
                    printf("\n\t\tDIGITE SOMENTE NÚMEROS DE 61 ATE 180! \n");
                    printf("\t\t***********************\n");
                    getch();
                }

            }while( ( !isdigit(num_seat) && (num_seat == sP[num_seat-1].assento_reservado) ) || ( (num_seat < 61) || ( (num_seat > QTD_TT) ) ) );
        }
        else
        {
            if(  ((strcmpi(aux->convidado, "n") == 0 ) && (strcmpi(aux->assento_especial, "s") == 0 )) || ((strcmpi(aux->convidado, "s") == 0 ) && (strcmpi(aux->assento_especial, "s") == 0 ))  )
            {
                printf("\n\tAssentos para não convidados: de 1 até 20.\n");
                do
                {
                    printf("\nEscolha um assento:   ==> ");
                    scanf("%d", &aux->assento_reservado);
                    //num_seat -> recebe o numero do assento digitado pelo usuário para ser verificado
                    num_seat = aux->assento_reservado;

                    if( isdigit(num_seat) )
                    {
                        printf("\n\t\tDIGITE SOMENTE NÚMEROS! ");
                        getch();
                    }
                    if(num_seat > 0)
                    {
                        if( (num_seat) == (sP[num_seat-1].assento_reservado) )
                        {
                            printf("\n\t\tO NÚMERO DE ASSENTO REQUISITADO ESTÁ OCUPADO! \n");
                            printf("\t\t***********************\n");
                            getch();
                        }
                    }
                    if ( (num_seat < 1) || (num_seat > 20) )
                    {
                        printf("\n\t\tDIGITE SOMENTE NÚMEROS DE 1 ATE 20! \n");
                        printf("\t\t***********************\n");
                        getch();
                    }

                }while( ( !isdigit(num_seat) && (num_seat == sP[num_seat-1].assento_reservado) ) || ( (num_seat < 1) || ( (num_seat > 20) ) ) );
            }
        }
    }

    // pega a data atual
    _strdate(  aux->dateStr );
    // pega a hora atual
    _strtime( aux->timeStr );
    
    sP[num_seat-1] = *aux;
    strcpy(sP[num_seat-1].cod_visitante, Aux.cod_visitante);
    // alguns problemas com atribuição de struct para ponteiro(valor incoerente de strings), tivemos que usar strcpy para copiar valores importantes
    
    //getch();
    system("clear || cls");
    system("color 3F");
    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t+------------------------------------------------+\n");
    printf("\t\t\t\t\t\t|               Ticket Informativo               |\n");
    printf("\t\t\t\t\t\t+------------------------------------------------+\n");
    printf("\t\t\t\t\t\t    Codigo do Participante .....: %s \n", sP[num_seat-1].cod_visitante);
    printf("\t\t\t\t\t\t    Nome .......................: %s \n", sP[num_seat-1].nome);
    printf("\t\t\t\t\t\t    Data de nascimento .........: %s \n", sP[num_seat-1].data_nasc);
    printf("\t\t\t\t\t\t    Sexo .......................: %s \n", sP[num_seat-1].sexo);
    printf("\t\t\t\t\t\t    RG .........................: %s \n", sP[num_seat-1].rg);
    printf("\t\t\t\t\t\t    Email ......................: %s \n", sP[num_seat-1].email);
    printf("\t\t\t\t\t\t    Convidado ..................: %s \n", sP[num_seat-1].convidado);
    printf("\t\t\t\t\t\t    Assento Especial ...........: %s \n", sP[num_seat-1].assento_especial);
    printf("\t\t\t\t\t\t    Assento Reservado ..........: %d \n", sP[num_seat-1].assento_reservado);
    printf("\t\t\t\t\t\t    Data atual do sistema ......: %s \n", sP[num_seat-1].dateStr);
    printf("\t\t\t\t\t\t    Hora atual do sistema ......: %s \n", sP[num_seat-1].timeStr);
    printf("\t\t\t\t\t\t+------------------------------------------------+\n");
    printf("\n\t\t\t\t\t\tParticipante Cadastrado com sucesso!\n\n\t\t\t\t\t");
    printf("\n\t\t\t\t\t\tLogin do WIFI na Palestra: %s \n\n", l_wireless);
    printf("\t\t\t\t\t\tSenha do WIFI na Palestra: %s \n\n\t\t\t\t\t\t", wireless);
    system("PAUSE");
    system("clear || cls");
    system("color 0F");

    return re_opcao;
}

void testePreencherAssentos()
{
    strcpy(Aux.nome, "teste");
    strcpy(Aux.data_nasc, "00-00-0000");
    strcpy(Aux.sexo, "M");
    strcpy(Aux.rg, "ABCDEF-G");
    strcpy(Aux.email, "teste@teste.com");
    //strcpy(Aux.convidado, "n");
    //strcpy(Aux.assento_especial, "n");
    aux->assento_reservado = 1;
    // pega a data atual
    _strdate(  aux->dateStr );
    // pega a hora atual
    _strtime( aux->timeStr );

    gerarCodigo();
    for (i = 0; i<QTD_TT; ++i)
    {
        sP[i] = *aux;
        if(i==0)
        {
            strcpy(Aux.convidado, "n");
            strcpy(Aux.assento_especial, "s");
        }
        if(i==20)
        {
            strcpy(Aux.convidado, "s");
            strcpy(Aux.assento_especial, "n");
        }
        if(i==60)
        {
            strcpy(Aux.convidado, "n");
            strcpy(Aux.assento_especial, "n");
        }
        aux->assento_reservado++;
        gerarCodigo();
    }
}

int contaAssentosOcupados(void)
{
    int cont = 0;
    for(i=0; i<QTD_TT; i++)
    {
        (sP[i].assento_reservado != 0)? cont++ : cont;
    }

    return cont;
}

// OP == 4 ENVIA EMAIL PARA TODOS OS PARTICIPANTES CADASTRADOS NO SISTEMA
void envia_email(void)
{
    retorno = 0;
    retorno = contaAssentosOcupados();
    (retorno == 0)? printf("\n\t\tNão há pessoas cadastradas no Sistema!!!\n\n\t\t") : printf("\n\t\tPrezado participante,\n\t\tFoi realizado a pesquisa sobre direitos Humanos na palestra.\n\t\tSegue abaixo a conscientização final para o seu melhor conhecimento do tema.\n\n\n\t\tE-mails Enviados ..: %d\n\n\t\t", retorno),system("PAUSE");

}

// OP == 3 SORTEIO DE BRINDES PARA PARTICIPANTES COM EXCESSÃO DOS CONVIDADOS
void sorteio(int qty)
{
    int random, v[qty], cont, cmp, var_sort, j;
    cont = 0;

    for (i = 0; i < QTD_TT; i++)
    {
        cmp = strcmpi(sP[i].convidado, "n");
        if( ( (sP[i].assento_reservado >= 0) && (sP[i].assento_reservado <= 19) ) && (cmp == 0) )
        {
            cont++;
        }
        if( ( (sP[i].assento_reservado >= 20) && (sP[i].assento_reservado <= 179) ) && (cmp == 0) )
        {
            cont++;
        }
    }

    if(cont == 0)
    {
        printf("\t\t\t\tNão é possível fazer o sorteio, não há participantes cadastrados:\t\t\t\t");
    }
    else
    {
        srand( (unsigned)time(NULL) );
        printf("\n\t\t\t%d Participantes\n", cont);
        for (i = 0; i < qty; ++i)
        {
            v[i] = 0;
        }
        for (i = 0; i<qty; i++)
        {
            do
            {   
                for (j = 0; j < qty; j++)
                {
                    random = rand() % QTD_TT+1;
                    v[i] = random;
                }
                cmp = strcmpi(sP[random].convidado, "n");

            }while( (((v[i] < 1) || (v[i] > 18) ) && (cmp != 0)) && ((sP[v[i]].assento_reservado == 0) && (strcmpi(sP[v[i]].convidado, "s") == 0)) );
            printf("\tNome ..: %s \tAssento ..: %d\n", sP[i].nome, v[i]);
        }
    }
}

void gerarCodigo(void)
{
    char *validchars = "abcdefghijklmnopqrstuvwxyz0123456789";
    char *novastr;
    char palavra[4];
    register int i;
    int str_len = 4;

    // inicia o contador aleatório 

    // aloca memoria
    novastr = ( char * ) malloc ( (str_len + 1) * sizeof(char));
    if ( !novastr ){
        printf("[*] Erro ao alocar memoria.\n" );
        exit ( EXIT_FAILURE );
    }

    // gera string aleatória
    srand ( time(NULL ));
    for ( i = 0; i < str_len; i++ ) {
        novastr[i] = validchars[ rand() % strlen(validchars) ];
        novastr[i + 1] = 0x0;
    }

    strcpy(palavra, novastr);
    strcpy(aux->cod_visitante, palavra);
}

// função para criar um novo login e ter acesso ao painel administrativo
void novoCadastro(void)
{
    system("color 3F");
    printf("\n\t\t\t\t\tCADASTRE UM LOGIN E SENHA PARA O ACESSO!\n");
    printf("\n\t\t\t\tDigite um login: \n\t\t\t\t");
    fflush(stdin);
    gets(pAdmin->login);
    printf("\n\t\t\t\tDigite uma senha: \n\t\t\t\t");
    gets(pAdmin->password);
    printf("\n\t\t\t\tLogin e senha cadastrados com sucesso!\n\t\t\t\t");
    system("PAUSE");
    system("color 0F");
    system("clear || cls");
}
