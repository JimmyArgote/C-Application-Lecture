
int re_opcao;

int menu_inicial()
{
    system("cls");
    printf("\n*******************************************************************************\n");
    printf("                           BEM VINDO AMINISTRADOR!       \n");
    printf("*******************************************************************************\n\n");
    printf("1- Gerenciar Participante       ==>\n");
    printf("2- Gerenciar Convidado          ==>\n");
    printf("3- Gerenciar Fazer o Sorteio    ==>\n");
    printf("4- Gerenciar Enviar Email       ==>\n");
    printf("5- Sair                         ==>\n");
    scanf("%d", &re_opcao);
    printf("\n%d", re_opcao);
    //getch();

    return re_opcao;
}


int menu_visitante()
{
    system("cls");
    printf("1- Incluir Visitante        ==> \n");
    printf("2- Excluir Visitante        ==>\n");
    printf("3- Listar Lugares Livres    ==> \n");
    printf("4- Listar Lugares Ocupado   ==> \n");
    printf("5- Listar Todos os Lugares  ==>\n");
    printf("6- Retornar ao Menu Inicial ==>\n");
    scanf("%d", &re_opcao);
    printf("\n%d", re_opcao);

    return re_opcao;
}



