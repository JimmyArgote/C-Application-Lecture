#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>
//#include <iostream>
//#include <cstdlib>
#include "login.c"
#include "menu.c"

//constantes
#define TIMEOUT          30 //segundos
#define TIME_SLEEP       3000 //30000ms == 30segundos
#define ATTEMPS          3 //numero de tentativas autenticar login e senha
#define G_PARTICIPANTE   1
#define G_CONVIDADO      2
#define SORTEIO          3
#define ENVIAR_EMAIL     4
#define SAIR             5

#define QTD_MAX          180 /*capacidade de assentos na palestra*/

//typedef struct administrator Admin;
    //login
typedef struct
{
    char login[30];
    char password[30];
    int attempts;
}administrator;
    //struct administrator admin;

    int i, op, num_seat, flag;
    /*Criando a struct */
	struct ficha_do_participante
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
};//aluno[QTD_MAX];

int authLogin;
int authPassword;
char login[30], password[30];

char getAuthParams(char l, char password)
{

}


    struct ficha_do_participante participant[QTD_MAX];

int main(int argc, char * argv[])
{
    //pAdmin *adm;
    //adm = &administrator;

    //(*adm).login= "jimmy";
    //(*adm).password = "12345";
    //(*adm).attemps = 0;

    //pAdmin->login= "jimmy";
    //pAdmin->password = "12345";

    administrator Admin;
    administrator *pAdmin = &Admin;

    //char *c;
    //c = &Admin.login;

    strcpy(pAdmin->login, "jimmy");
    strcpy(pAdmin->password, "Abc");



    //Admin.login = "jimmy";
    //Admin.password = "teste";
    pAdmin->attempts = 0;

    while(op != SAIR)
    {
        do
        {
            //true;

            printf("\nDigite seu Login ...: ");
            gets(login);
            printf("\nDigite sua Senha ...: ");
            //fgets(password);
            gets(password);

            //system("read password");

            //authenticate = logar(login, password);

            authLogin = strcmp(login, pAdmin->login);
            authPassword = strcmp(password, pAdmin->password);

            printf("L: %d\nS: %d\n\n", authLogin, authPassword);

            printf("login: %s\n senha: %s\n", login, password);
            printf("login: %s\n senha: %s\n", pAdmin->login, pAdmin->password);

            if( (authLogin == 0) && (authPassword == 0) )
            //if( ((strcmp(login, pAdmin->login)) && (strcmp(password, pAdmin->password))) == 0 )
            //if( !((authLogin && authPassword) != 0) )
            {
                printf("\nteste");
                getche();
                //menu_inicial(); // se autenticado chama a funcao menu
                while(op != SAIR)
                {
                    if(op != SAIR)
                    {
                        int re_opcao;
                        op = menu_inicial(re_opcao); // se autenticado chama a funcao menu
                    }
                }
            }
            else
            {
                //esperar 30 segundos para tentar novamente

                pAdmin->attempts++;
            }
        }while(pAdmin->attempts <= ATTEMPS); //ENQUANTO NUMERO DE TENTATIVAS FOR <= 3 REPITA AS INSTRU��ES DO{}

        if(pAdmin->attempts == ATTEMPS)
        {
            pAdmin->attempts = 0;
            printf("Voc� errou nas 3 tentativas!\n");
            printf("Espere 30 Segundo para tentar novamente!!!\n");

            Sleep(TIME_SLEEP);
            if( timeout(TIMEOUT) == 0 )
            {
                printf("Time Out\n");
                return 0;
            }
        }

    }

    //listar op��es
    optionsList();

    //Executar Op��o
    optionsExecute();
}


//Chamar op��es de menu
int optionsList()
{
    printf("\n\n0- Sair >>\n");
    printf("1- Reservar Assento >>\n");
    printf("2- Listar todos os Assentos  >>\n\n");
    printf("Escolha uma opcao: \n");
    scanf("%d", &op);
}


int optionsExecute()
{
    while(op != 0)
    {
        getch();
        if(op == 1)
        {
            //Reservar Assento
            reserveSeat();
        }
        if(op == 2)
        {
            system("cls");
            listAllSeat();
            //findBySeat();
            getch();
            system("cls");
        }
        printf("\n0- Sair >>\n");
        printf("1- Reservar Assento >>\n");
        printf("2- Procurar por Assento >>\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &op);

        getch();
    }
}



//Fun�ao para registrar um participante
int reserveSeat()
{
	//struct ficha_de_aluno vetorAluno[10];

	/*Criando a vari�vel aluno que ser� do
	tipo struct ficha_de_aluno */
	//struct ficha_de_aluno aluno;

	for(i=0; i<2; i++)
    {
        printf("\n---------- Cadastro de Assento -----------\n\n\n");
        printf("Assento ......: ");
        scanf("%d", &participant[i].cod_visitante);
        printf("Nome do aluno ......: ");
        fflush(stdin);

        /*usaremos o comando fgets() para ler strings, no caso o nome
        do aluno e a disciplina
        fgets(variavel, tamanho da string, entrada)
        como estamos lendo do teclado a entrada � stdin (entrada padr�o),
        por�m em outro caso, a entrada tambem poderia ser um arquivo */

        fgets(participant[i].nome, 40, stdin);

        // pega a data atual
        _strdate(  participant[i].dateStr);
        // pega a hora atual
        _strtime( participant[i].timeStr );

        //getch();
        printf("\nASSENTO RESERVADO COM SUCESSO!\n");
        getch();
        system("cls");
    }

    printf("\n\n");

    printf("                    +------------------------------------------------+\n");
	printf("                    |           Ticket Informativo                   |\n");
	printf("                    +------------------------------------------------+\n");
    //printf("Dados importantes para entrada na palestra!\n");
    printf("            		+------------------------------------------------+\n");
    printf("            	    |    Codigo do Participante .....: %d            \n", participant[i+1].cod_visitante);
	printf("            	    |    Nome ...........: %s                        \n", participant[i+1].nome);
	printf("            	    |    Data de nascimento .....: %d                \n", participant[i+1].data_nasc);
	printf("            	    |    Sexo ...........: %s                        \n", participant[i+1].sexo);
	printf("            	    |    RG .....: %d                                \n", participant[i+1].rg);
	printf("            	    |    Email ...........: %s                       \n", participant[i+1].email);
	printf("            	    |    Convidado .....: %s                         \n", participant[i+1].convidado);
	printf("            	    |    Assento Especial ...........: %s            \n", participant[i+1].assento_especial);
	printf("            	    |    Assento Reservado ...........: %d           \n", participant[i+1].assento_reservado);
	printf("            	    |    Data atual do sistema e: %s                 \n", participant[i+1].dateStr);
	printf("            	    |    Hora atual do sistema e: %s                 \n", participant[i+1].timeStr);
	printf("            		+------------------------------------------------+\n");

	getch();
	//return(0);
	//system("cls");
}

//Listar todos os assentos
//findBySeat()
listAllSeat()
{
    int seat;
    //printf("Digite o numero do assento: \n");
    //scanf("%d", &seat);

    for(i=0; i<10; i++)
    {
        if(participant[i].assento_reservado != 0)
        {
            printf("\n%d: Ocupado", participant[i+1].assento_reservado);
        }
        else
        {
            printf("\n%d: Livre", participant[i+1].assento_reservado);
        }
    }

int columns, rows, number;
rows =1;

do{
    columns=0;
    do{
        printf("%d\t", columns*10+rows);

    }while(columns++ <9);
    printf("\n");

}while(rows++ <10);

    return 0;
}


verifyEmpty()
{

}
