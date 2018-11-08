#include <stdio.h>
#include <conio.h>
#include <time.h>

int main(void)
{
    registrar();
}

//Funçao para registrar um participante
registrar()
{
    int i;
    /*Criando a struct */
	struct ficha_de_aluno
	{
	    int assento;
		char nome[50];
		char disciplina[30];
		float nota_prova1;
		float nota_prova2;
		char dateStr[9];
        char timeStr[9];
	};

    struct ficha_de_aluno aluno[10];
	//struct ficha_de_aluno vetorAluno[10];

	/*Criando a variável aluno que será do
	tipo struct ficha_de_aluno */
	//struct ficha_de_aluno aluno;

	for(i=0; i<10; i++)
    {
        printf("\n---------- Cadastro de aluno -----------\n\n\n");

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

        printf("Disciplina ......: ");
        fflush(stdin);
        fgets(aluno[i].disciplina, 40, stdin);

        printf("Informe a 1a. nota ..: ");
        scanf("%f", &aluno[i].nota_prova1);

        printf("Informe a 2a. nota ..: ");
        scanf("%f", &aluno[i].nota_prova2);

        // pega a data atual
        _strdate(  aluno[i].dateStr);
        // pega a hora atual
        _strtime( aluno[i].timeStr );

        getch();
        printf("\nASSENTO RESERVADO COM SUCESSO!\n");
        getch();
        system("cls");
    }

	printf("\n\n --------- Ticket informativo ---------\n\n");
    //printf("Dados importantes para entrada na palestra!\n");
    printf("        Assento .....: %d \n", aluno[i+1].assento);
	printf("        Nome ...........: %s", aluno[i+1].nome);
	printf("        Disciplina .....: %s", aluno[i+1].disciplina);
	printf("        Nota da Prova 1 ...: %.2f\n" , aluno[i+1].nota_prova1);
	printf("        Nota da Prova 2 ...: %.2f\n" , aluno[i+1].nota_prova2);
	printf("        Data atual do sistema e: %s \n", aluno[i+1].dateStr);
	printf("        Hora atual do sistema e: %s \n", aluno[i+1].timeStr);
	printf("\n -------------------------------------- \n\n");

	getch();
	//return(0);

	//system("cls");
}

verifyEmpty()
{

}
