
/* lg = login, ps = password */
/* função de atenticação*/
int logar(char lg[30], char ps[30])
{
    int auth;
    if( (lg && ps) != NULL )
    {
        if(strcmp(lg, ps) == 0)
        {
            auth = TRUE;
        }
    }

    return auth;
}

exit()
{
    return;
}

int timeout ( int seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}

    return  1;
}
