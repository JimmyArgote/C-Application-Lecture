#include <stdio.h>
#include <conio.h>
#include <time.h>
    //variáveis
    int i, op, num_seat, flag;
    /*Criando a struct */
	struct ficha_de_aluno
	{
	    int assento;
		char nome[50];
		char dateStr[9];
        char timeStr[9];
	};

    struct ficha_de_aluno aluno[50];

int main(void)
{
    //listar opções
    optionsList();

    //Executar Opção
    optionsExecute();
}


//Chamar opções de menu
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



//Funçao para registrar um participante
int reserveSeat()
{
	//struct ficha_de_aluno vetorAluno[10];

	/*Criando a variável aluno que será do
	tipo struct ficha_de_aluno */
	//struct ficha_de_aluno aluno;

	for(i=0; i<10; i++)
    {
        printf("\n---------- Cadastro de Assento -----------\n\n\n");
        printf("Assento ......: ");
        scanf("%d", &aluno[i].assento);
        printf("Nome do aluno ......: ");
        fflush(stdin);

        /*usaremos o comando fgets() para ler strings, no caso o nome
        do aluno e a disciplina
        fgets(variavel, tamanho da string, entrada)
        como estamos lendo do teclado a entrada é stdin (entrada padrão),
        porém em outro caso, a entrada tambem poderia ser um arquivo */

        fgets(aluno[i].nome, 40, stdin);

        // pega a data atual
        _strdate(  aluno[i].dateStr);
        // pega a hora atual
        _strtime( aluno[i].timeStr );

        //getch();
        printf("\nASSENTO RESERVADO COM SUCESSO!\n");
        getch();
        system("cls");
    }

	printf("\n\n --------- Ticket Informativo ---------\n\n");
    //printf("Dados importantes para entrada na palestra!\n");
    printf("        Assento .....: %d \n", aluno[i+1].assento);
	printf("        Nome ...........: %s", aluno[i+1].nome);
	printf("        Data atual do sistema e: %s \n", aluno[i+1].dateStr);
	printf("        Hora atual do sistema e: %s \n", aluno[i+1].timeStr);
	printf("\n -------------------------------------- \n\n");

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
        if(aluno[i].assento != 0)
        {
            printf("\n%d: Ocupado", aluno[i+1].assento);
        }
        else
        {
            printf("\n%d: Livre", aluno[i+1].assento);
        }
    }
}


verifyEmpty()
{

}

