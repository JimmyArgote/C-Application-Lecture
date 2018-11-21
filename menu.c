
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
    printf("\n\t");
    for(i=0; i<=(n); i++)
    {
        putchar(c);
    }
}

int re_opcao;

int menu_inicial()
{
    system("cls");
    char *a = " BEM VINDO ADMINISTRADOR! ";
    register int b = 0;
    b = strlen(a);
    imprimechar(b, '*');
    imprime(b, ' ');
    printf("%s\n", a);
    imprimechar(b, '*');

    imprimechar(16, '-');
    printf("\t|\t1- Gerenciar Participante       ==> \t|\t\n");
    printf("\t|\t2- Gerenciar Convidado          ==> \t|\t\n");
    printf("\t|\t3- Gerenciar Fazer o Sorteio    ==> \t|\t\n");
    printf("\t|\t4- Gerenciar Enviar Email       ==> \t|\t\n");
    printf("\t|\t5- Sair                         ==> \t|\t");
    imprimechar(16, '-');
    printf("\t\t");
    scanf("%d", &re_opcao);
    printf("\n\t\t%d", re_opcao);
    //getch();

    return re_opcao;
}


int menu_visitante()
{
    system("cls");
    printf("\t|\t1- Incluir Visitante        ==> \n");
    printf("\t|\t2- Excluir Visitante        ==> \n");
    printf("\t|\t3- Listar Lugares Livres    ==> \n");
    printf("\t|\t4- Listar Lugares Ocupado   ==> \n");
    printf("\t|\t5- Listar Todos os Lugares  ==> \n");
    printf("\t|\t6- Retornar ao Menu Inicial ==> \n");
    scanf("%d", &re_opcao);
    //printf("\n%d", re_opcao);

    return re_opcao;
}
