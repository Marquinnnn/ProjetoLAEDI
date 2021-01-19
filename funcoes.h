#define QUANTIDADE_RUAS  3
#define VAGAS_TOTAIS  60
#define PLACA 7 + 1
#define TAMANHO  50 + 1
#define VAGAS_MIN 5
#define VAGAS_MAX 20
#define VALOR_MIN 1.00
#define VALOR_MAX 2.00

int     menu1();
char    menu2();
int     menu3();
int     menu4();
void    cadastra_ruas();
void    cadastra_numero_vagas();
void    cadastra_valor_vagas();

typedef struct
{
    char    nome_rua[TAMANHO];
    int     num_vagas;
    int     status_vaga[VAGAS_MAX];
    float   valor;
} Streets ;

typedef struct
{
    int     cod_rua;
    int     spot_number;
    char    license_plate[PLACA];
    int     parking_time;
    float   total_value;
} Parking ;

typedef struct
{
    int     cod_rua;
    int     spot_number;
    char    license_plate[PLACA];
    int     parking_time;
    float   total_value;
    int     jasaiu;
} Parking_Storage ;

struct tm agora_data = {0};

/*typedef struct
{
    int tm_sec;     //representa os segundos de 0 a 59
    int tm_min;     //representa os minutos de 0 a 59
    int tm_hour;    //representa as horas de 0 a 24
    int tm_mday;    //dia do mês de 1 a 31
    int tm_mon;     //representa os meses do ano de 0 a 11
    int tm_year;    //representa o ano a partir de 1900
} Time ;*/

int menu1()
{
    int opt1;

    printf("\n...................................MENU.........................................\n");
    printf("Digite uma opcao abaixo\n");
    printf("\n(1)Cadastrar Ruas\n(2)Cadastrar Numero de Vagas\n(3)Cadastrar o Valor das Vagas");
    printf("\n(4)Estacionar um Carro\n(5)Liberar Vaga\n(6)Emitir Relatorios\n(7)Sair\n");
    printf("\nSua opcao:[ ]\b\b");
    fflush( stdin );
    scanf("%d",&opt1);
    printf("\n................................................................................\n");

    return opt1;
}

char menu2()
{
    char opt2;

    printf("\n..............................Emitir Relatorios.................................\n");
    printf("Digite uma opcao abaixo\n");
    printf("\n(a)Ruas Cadastradas\n(b)Total de Vagas Disponiveis por Rua");
    printf("\n(c)Todos Carros Estacionados\n(d)Carros Estacionados por Rua");
    printf("\n(e)Custo Medio por Estacionamento\n(f)Total de carros que foram estacionados\n(g)Total de carros estacionados, por rua, ate o momento\n(h)Voltar para o primeiro menu.\n");
    printf("\nSua opcao:[ ]\b\b");
    fflush( stdin );
    scanf("%c",&opt2);
    getchar();
    printf("\n................................................................................\n");

    return opt2;
}

int menu3( Streets ruas[] )
{
    int i, opt3;

    printf("..............................Ruas Cadastradas....................................");
    printf("\n(0)Sair para o primeiro menu");
    for (i = 0 ; i < QUANTIDADE_RUAS ; i++ )
    {
        printf("\n(%d)%s", i + 1, ruas[i].nome_rua );
    }
    printf("\nDigite uma opcao!");
    printf("\nSua opcao:[ ]\b\b");
    fflush( stdin );
    scanf("%d",&opt3);

    printf("\n................................................................................\n");

    return opt3;
}

int menu4( )
{
    int opt4;
    printf("\n..............................Tempo de Estacionamento....................................\n");
    printf("Escolha o tempo para estacionar, em minutos:\n");
    printf("\n(1)30\n(2)60\n(3)90\n(4)120");
    printf("\nSua opcao:[ ]\b\b");
    fflush( stdin );
    scanf("%d",&opt4);

    printf("\n................................................................................\n");

    return opt4;
}
void    cadastra_ruas( Streets ruas[] )
{
    int     i, tamanho;
    for ( i = 0 ; i < QUANTIDADE_RUAS ; i++ )
    {
        printf("\nEntre com o nome da rua %d: ", i + 1);
        fflush( stdin );
        fgets( ruas[i].nome_rua, TAMANHO, stdin );

        tamanho = strlen(ruas[i].nome_rua) - 1;
        ruas[i].nome_rua[tamanho] = '\0';
    }
    printf("\nRuas cadastradas com sucesso!\n");
}

void    cadastra_numero_vagas( Streets ruas[] )
{
    int     i, j;
    for ( i = 0 ; i < QUANTIDADE_RUAS ; i++ )
    {
        do
        {
            printf("\nDigite a quantidade de vagas da rua %s: ", ruas[i].nome_rua);
            scanf("%d", &ruas[i].num_vagas);
            if( ( ruas[i].num_vagas < VAGAS_MIN ) || ( ruas[i].num_vagas > VAGAS_MAX ) )
            {
                printf("\nO numero de vagas tem que ser entre 5 e 20.\n");
            }
        }
        while ( ( ruas[i].num_vagas < VAGAS_MIN ) || ( ruas[i].num_vagas > VAGAS_MAX ) );
    }
    for( i = 0 ; i < QUANTIDADE_RUAS ; i++ )
    {
        for( j = 0 ; j < ruas[i].num_vagas ; j++ )
        {
            ruas[i].status_vaga[j] = 0;
        }
    }

    printf("\nNumeros de vagas cadastradas com sucesso!\n");

    /*for(i = 0 ; i < QUANTIDADE_RUAS ; i++)
    {
        for (j = 0 ; j < ruas[i].num_vagas ; j++)
        {
            printf("%d", ruas[i].status_vaga[j]);
        }
        printf("\n");
    }*/
}

void   cadastra_valor_vagas( Streets ruas[] )
{
    int     i;
    for ( i = 0 ; i < QUANTIDADE_RUAS ; i++ )
    {
        do
        {
            printf("\nDigite o valor para cada meia hora estacionada, de 1 a 2 reais, da rua %s : R$ ", ruas[i].nome_rua);
            scanf("%f", &ruas[i].valor);
            if( ( ruas[i].valor < VALOR_MIN ) || ( ruas[i].valor > VALOR_MAX ) )
            {
                printf("\nO valor da vaga tem que ser entre 1 e 2 reais.\n");
            }
        }
        while ( ( ruas[i].valor < VALOR_MIN ) || ( ruas[i].valor > VALOR_MAX ) );
    }
    printf("\nValor das vagas cadastrados com sucesso!\n");
    /*for( i = 0 ; i < QUANTIDADE_RUAS ; i++ )
    {
        printf("%.2f\n", ruas[i].valor);
    }*/
}
