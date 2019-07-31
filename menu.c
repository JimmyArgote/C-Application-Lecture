//formataca o de tela
void imprimechar(int n, char c)
{
	int i;
    printf("\n\t");
    for(i=0; i<=(n*3); i++)
    {
        putchar(c);
    }
    printf("\n");
}
void imprime(int n, char c)
{
	int i;
    printf("\n\t\t\t\t\t\t");
    for(i=0; i<=(n*3); i++)
    {
        putchar(c);
    }
    printf("\n");
}

int re_opcao;

int menu_inicial()
{
    system("cls");
    char *a = "\t\t\t\t\t\t\t\t BEM VINDO ADMINISTRADOR! ";
    register int b = 0;
    b = strlen(a);
    imprimechar(45, '*');
    imprime(b, ' ');
    printf("%s\n", a);
    imprimechar(45, '*');

    printf("\n\n");
    imprime(16, '-');
    printf("\t\t\t\t\t\t|\t 1- Gerenciar Participante       ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 2- Preencher Assentos(teste)    ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 3- Fazer o Sorteio              ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 4- Enviar Email                 ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 5- Sair                         ==> \t|\t");
    imprime(16, '-');

    printf("\t\t\t\t\t\t Escolha uma opcao:           ==>  ");
    scanf("\n\t\t\t\t\t\t%d", &re_opcao);
    return re_opcao;
}

int menu_visitante()
{
    system("cls");
    imprimechar(40, '-');
    printf("\n\t\t\t\t\t\t\t\tMENU INICIAL\n");
    imprimechar(40, '-');
    imprime(16, '-');
    printf("\t\t\t\t\t\t|\t 1- Incluir Visitante        ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 2- Excluir Visitante        ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 3- Listar Lugares Livres    ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 4- Listar Lugares Ocupado   ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 5- Listar Todos os Lugares  ==> \t|\t\n");
    printf("\t\t\t\t\t\t|\t 6- Retornar ao Menu Inicial ==> \t|\t");
    imprime(16, '-');
    printf("\t\t\t\t\t\t Escolha uma opcao:       ==>  ");
    scanf("\n\t\t\t\t\t\t%d", &re_opcao);
    return re_opcao;
}
