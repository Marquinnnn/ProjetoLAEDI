/* Trabalho de AED I
 *
 *           Lucas de Godoi Moraes
 *  Autores: Marcus Vinícius Ribeiro
 *           Nícholas César F. Pereira
 *
 * Data de criação: 23/05/20
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"funcoes.h"

int main()
{
    Streets ruas[QUANTIDADE_RUAS];
    Parking estacionar;
    Parking_Storage estacionado1[VAGAS_TOTAIS];
    Parking_Storage estacionado2[VAGAS_TOTAIS];
    Parking_Storage estacionado3[VAGAS_TOTAIS];
    int     i, j, k, x1 = 0, x2 = 0, x3 = 0, opt1, opt3, opt4, contador = 0, sair, aux_carrosestacionados = 0, aux = 0;
    int     vaga_disponivel = 0, rua_escolhida, aux_vagadisponivel, vaga_liberada;
    int     cont_carros_rua0 = 0, cont_carros_rua1 = 0, cont_carros_rua2 = 0;
    float   soma1, soma2, soma3, media;
    char    opt2, confirmacao;
    time_t  tempo_data;

    printf(".............................Trabalho de AED I..................................");

    do
    {
        opt1 = menu1();

        switch ( opt1 )
        {

        case 1:
            printf("..............................Cadastrar Ruas....................................");
            if ( contador == 0 )
            {
                cadastra_ruas( ruas );
                contador = 1;
            }
            else
            {
                printf("\nRuas ja foram cadastradas. Favor prossiga para opcao %d do menu.\n", contador + 1);
            }
            break;

        case 2:
            printf("..........................Cadastrar Numero de Vagas.............................\n");
            if ( contador == 1 )
            {
                cadastra_numero_vagas( ruas );
                contador = 2;
            }
            else if ( contador < 1 )
            {
                printf("\nRuas nao foram cadastradas. Favor prossiga para opcao %d do menu.\n", contador + 1);
            }
            else
            {
                printf("\nO numero de vagas ja foram cadastradas. Favor prossiga para opcao %d do menu.\n", contador + 1);
            }
            printf("\n");
            break;

        case 3:
            printf("..........................Cadastrar o Valor das Vagas...........................\n");
            if ( contador == 2)
            {
                cadastra_valor_vagas( ruas );
                contador = 3;
            }
            else if ( contador < 2 )
            {
                if ( contador == 0 )
                {
                    printf("\nRuas nao foram cadastradas. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
                else
                {
                    printf("\nNumero de vagas nao foram cadastradas. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
            }
            else
            {
                printf("\nO valor das vagas ja foram cadastrados. Favor prossiga para opcao %d do menu.\n",contador + 1);
            }
            printf("\n");
            break;

        case 4:
            printf(".............................Estacionar um Carro.............................\n\n");
            if ( contador >= 3 )
            {
                aux_vagadisponivel = 0;
                do
                {
                    opt3 = menu3( ruas );

                    if(opt3 > 3 || opt3 < 0)
                        printf("\nEsta rua nao existe, digite uma rua valida!\n");

                }
                while ( opt3 > 3 || opt3 < 0 );

                if(opt3 == 0)
                    break;

                estacionar.cod_rua = opt3-1 ;
                rua_escolhida = estacionar.cod_rua;
                printf("\nRua escolhida: %s\n", ruas[rua_escolhida].nome_rua);
                printf("Digite a placa do veiculo (FORMATO: XXX0000): ");
                fflush( stdin );
                fgets( estacionar.license_plate, PLACA, stdin );

                do
                {
                    estacionar.parking_time = menu4();

                    if(estacionar.parking_time > 4 || estacionar.parking_time < 1)
                        printf("\nOpcao invalida! Digite uma opcao valida!");

                }
                while ( estacionar.parking_time > 4 || estacionar.parking_time < 1 );

                estacionar.total_value = ruas[rua_escolhida].valor * estacionar.parking_time;

                for( j = 0 ; j < ruas[rua_escolhida].num_vagas ; j++ )
                {
                    if( ruas[rua_escolhida].status_vaga[j] == 0 )
                    {
                        printf("\nRua %s\nVaga numero %d disponivel.",ruas[rua_escolhida].nome_rua, j+1);
                        aux_vagadisponivel = 1;
                        break;
                    }
                }
                if(aux_vagadisponivel == 0)
                {
                    printf("\nNao ha vagas disponiveis na Rua %s.", ruas[rua_escolhida].nome_rua);
                    break;
                }

                estacionar.spot_number = j;

                printf("\nCusto total da vaga selecionada: R$%.2f", estacionar.total_value);

                printf("\n..........................Informacoes do estacionamento..........................\n");
                printf("Rua: %s\nVaga numero %d\nPlaca do veiculo: %s\nTempo: %d minutos\nValor total: R$%.2f\n",
                       ruas[rua_escolhida].nome_rua, j+1, estacionar.license_plate, estacionar.parking_time*30, estacionar.total_value);

                printf("\nDeseja confirmar a operacao?<S/N>");
                fflush(stdin);
                scanf("%c",&confirmacao);

                if(toupper(confirmacao) == 'S')
                {
                    if(rua_escolhida == 0)
                    {
                        time(&tempo_data); // recupera data e hora do sistema
                        agora_data = *localtime(&tempo_data); // atribui a data e hora recuperadas para a variável agora_data
                        estacionado1[x1].cod_rua = estacionar.cod_rua;
                        estacionado1[x1].spot_number = estacionar.spot_number;
                        strcpy(estacionado1[x1].license_plate, estacionar.license_plate);
                        estacionado1[x1].parking_time = estacionar.parking_time*30;
                        estacionado1[x1].total_value = estacionar.total_value;
                        printf("\nHorario da confirmacao: %d:%d:%d", agora_data.tm_hour, agora_data.tm_min, agora_data.tm_sec);
                        printf("\nDia da confirmacao: %d/%d/%d\n", agora_data.tm_mday, agora_data.tm_mon+1, agora_data.tm_year+1900);

                        ruas[rua_escolhida].status_vaga[j] = 1;
                        estacionado1[x1].jasaiu = 0;//tirar bug na hora de liberar o carro
                        cont_carros_rua0++;
                        x1++;
                    }

                    else if(rua_escolhida == 1)
                    {
                        time(&tempo_data); // recupera data e hora do sistema
                        agora_data = *localtime(&tempo_data); // atribui a data e hora recuperadas para a variável agora_data
                        estacionado2[x2].cod_rua = estacionar.cod_rua;
                        estacionado2[x2].spot_number = estacionar.spot_number;
                        strcpy(estacionado2[x2].license_plate, estacionar.license_plate);
                        estacionado2[x2].parking_time = estacionar.parking_time*30;
                        estacionado2[x2].total_value = estacionar.total_value;
                        printf("\nHorario da confirmacao: %d:%d:%d", agora_data.tm_hour, agora_data.tm_min, agora_data.tm_sec);
                        printf("\nDia da confirmacao: %d/%d/%d\n", agora_data.tm_mday, agora_data.tm_mon+1, agora_data.tm_year+1900);

                        ruas[rua_escolhida].status_vaga[j] = 1;
                        estacionado2[x2].jasaiu = 0;
                        cont_carros_rua1++;
                        x2++;
                    }


                    else if(rua_escolhida == 2)
                    {
                        time(&tempo_data); // recupera data e hora do sistema
                        agora_data = *localtime(&tempo_data); // atribui a data e hora recuperadas para a variável agora_data
                        estacionado3[x3].cod_rua = estacionar.cod_rua;
                        estacionado3[x3].spot_number = estacionar.spot_number;
                        strcpy(estacionado3[x3].license_plate, estacionar.license_plate);
                        estacionado3[x3].parking_time = estacionar.parking_time*30;
                        estacionado3[x3].total_value = estacionar.total_value;
                        printf("\nHorario da confirmacao: %d:%d:%d", agora_data.tm_hour, agora_data.tm_min, agora_data.tm_sec);
                        printf("\nDia da confirmacao: %d/%d/%d\n", agora_data.tm_mday, agora_data.tm_mon+1, agora_data.tm_year+1900);

                        ruas[rua_escolhida].status_vaga[j] = 1;
                        estacionado3[x3].jasaiu = 0;
                        cont_carros_rua2++;
                        x3++;
                    }
                }
                else
                {
                    printf("\nOperacao cancelada!");
                }
                contador = 4;
            }

            else
            {
                if ( contador == 0 )
                {
                    printf("\nRuas nao foram cadastradas. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
                else if ( contador == 1 )
                {
                    printf("\nNumero de vagas nao foram cadastradas. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
                else
                {
                    printf("\nValor das vagas nao foram cadastrados. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
                printf("\n");
            }
            break;

        case 5:
            printf("................................Liberar Vaga....................................\n\n");
            if ( contador >= 4 )
            {
                do
                {
                    opt4 = menu3( ruas );

                    if(opt4 > 3 || opt4 < 0)
                        printf("\nEsta rua nao existe, digite uma rua valida!\n");

                }
                while ( opt4 > 3 || opt4 < 0 );

                if(opt4 == 0)
                    break;

                printf("................................Carros Estacionados....................................\n");

                aux_carrosestacionados = 0;

                switch( opt4 )
                {
                case 1:
                    for( i = 0 ; i < x1 ; i++)
                    {
                        aux = 0;//auxiliar para tirar o bug na hora de liberar as vagas de maneira crescente
                        for( j = 0 ; j < ruas[opt4-1].num_vagas ; j++)
                        {
                            if( estacionado1[i].cod_rua == opt4-1 && ruas[opt4-1].status_vaga[j] != 0 && estacionado1[i].jasaiu != 1 )
                            {
                                printf("%d) %s", estacionado1[i].spot_number+1, estacionado1[i].license_plate);
                                aux_carrosestacionados = 1;
                                aux = 1;
                            }
                            if( aux == 1 )
                                break;
                        }
                    }
                    if( aux_carrosestacionados == 1 )
                    {
                        do
                        {
                            printf("\nDigite a vaga que deseja liberar: ");
                            scanf("%d", &vaga_liberada);

                            if( ruas[opt4-1].status_vaga[vaga_liberada-1] == 0 || vaga_liberada > ruas[opt4-1].num_vagas || vaga_liberada <= 0 )
                                printf("\nEsta vaga nao esta ocupada ou nao existe, escolha outra ocupada!\n");
                        }
                        while ( ruas[opt4-1].status_vaga[vaga_liberada-1] == 0 || vaga_liberada > ruas[opt4-1].num_vagas || vaga_liberada <= 0 );
                        ruas[opt4-1].status_vaga[vaga_liberada-1] = 0;
                        estacionado1[vaga_liberada-1].jasaiu = 1;
                        estacionado1[vaga_liberada-1].license_plate[0]='\0';

                        printf("\nVaga %d liberada com sucesso!", vaga_liberada);
                    }
                    else
                        printf("\nNao ha carros estacionados nesta rua.");
                    break;

                case 2:
                    for( i = 0 ; i < x2 ; i++)
                    {
                        aux = 0;
                        for( j = 0 ; j < ruas[opt4-1].num_vagas ; j++)
                        {
                            if( estacionado2[i].cod_rua == opt4-1 && ruas[opt4-1].status_vaga[j] != 0 && estacionado2[i].jasaiu != 1 )
                            {
                                printf("%d) %s", estacionado2[i].spot_number+1, estacionado2[i].license_plate);
                                aux_carrosestacionados = 1;
                                aux = 1;
                            }
                            if( aux == 1 )
                                break;
                        }
                    }
                    if( aux_carrosestacionados == 1 )
                    {
                        do
                        {
                            printf("\nDigite a vaga que deseja liberar: ");
                            scanf("%d", &vaga_liberada);

                            if( ruas[opt4-1].status_vaga[vaga_liberada-1] == 0 || vaga_liberada > ruas[opt4-1].num_vagas || vaga_liberada <= 0 )
                                printf("\nEsta vaga nao esta ocupada ou nao existe, escolha outra ocupada!\n");
                        }
                        while ( ruas[opt4-1].status_vaga[vaga_liberada-1] == 0 || vaga_liberada > ruas[opt4-1].num_vagas || vaga_liberada <= 0 );
                        ruas[opt4-1].status_vaga[vaga_liberada-1] = 0;
                        estacionado2[vaga_liberada-1].jasaiu = 1;
                        estacionado2[vaga_liberada-1].license_plate[0]='\0';

                        printf("\nVaga %d liberada com sucesso!", vaga_liberada);
                    }
                    else
                        printf("\nNao ha carros estacionados nesta rua.");
                    break;

                case 3:
                    for( i = 0 ; i < x3 ; i++ )
                    {
                        aux = 0;
                        for( j = 0 ; j < ruas[opt4-1].num_vagas ; j++ )
                        {
                            if( estacionado3[i].cod_rua == opt4-1 && ruas[opt4-1].status_vaga[j] != 0 && estacionado3[i].jasaiu != 1 )
                            {
                                printf("%d) %s", estacionado3[i].spot_number+1, estacionado3[i].license_plate);
                                aux_carrosestacionados = 1;
                                aux = 1;
                            }
                           if( aux == 1 )
                                break;
                        }
                    }
                    if( aux_carrosestacionados == 1 )
                    {
                        do
                        {
                            printf("\nDigite a vaga que deseja liberar: ");
                            scanf("%d", &vaga_liberada);

                            if( ruas[opt4-1].status_vaga[vaga_liberada-1] == 0 || vaga_liberada > ruas[opt4-1].num_vagas || vaga_liberada <= 0 )
                                printf("\nEsta vaga nao esta ocupada ou nao existe, escolha outra ocupada!\n");
                        }
                        while ( ruas[opt4-1].status_vaga[vaga_liberada-1] == 0 || vaga_liberada > ruas[opt4-1].num_vagas || vaga_liberada <= 0 );
                        ruas[opt4-1].status_vaga[vaga_liberada-1] = 0;
                        estacionado3[vaga_liberada-1].jasaiu = 1;
                        estacionado3[vaga_liberada-1].license_plate[0]='\0';

                        printf("\nVaga %d liberada com sucesso!", vaga_liberada);
                    }
                    else
                        printf("\nNao ha carros estacionados nesta rua.");
                    break;
                }
                contador = 5;
            }
            else
            {
                if ( contador == 0 )
                {
                    printf("\nRuas nao foram cadastradas. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
                else if ( contador == 1 )
                {
                    printf("\nNumero de vagas nao foram cadastradas. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
                else if ( contador == 2 )
                {
                    printf("\nValor das vagas nao foram cadastrados. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
                else
                {
                    printf("\nNenhum carro foi estacionado. Favor prossiga para opcao %d do menu.\n",contador + 1);
                }
            }
            printf("\n");
            break;

        case 6:
            do
            {
                sair = 0;
                opt2 = menu2();

                switch ( tolower(opt2) )
                {
                case 'a':
                    printf("..............................Ruas Cadastradas..................................\n");
                    if ( contador > 0 )
                    {
                        for( i = 0 ; i < QUANTIDADE_RUAS ; i++ )
                        {
                            printf("\nRua %d: %s ",i+1, ruas[i].nome_rua);
                        }
                    }
                    else
                    {
                        printf("\nRuas nao foram cadastradas. Favor, prossiga para opcao 1 do menu.\n");
                    }
                    printf("\n");
                    break;

                case 'b':
                    printf("......................Total de Vagas Disponiveis por Rua........................\n");
                    if ( contador > 1 )
                    {
                        for( i = 0 ; i < QUANTIDADE_RUAS ; i++ )
                        {
                            for ( j = 0 ; j < ruas[i].num_vagas ; j++ )
                            {
                                if( ruas[i].status_vaga[j] == 0 )
                                {
                                    vaga_disponivel++;
                                }
                            }
                            printf("\nVagas disponiveis na rua %s: %d",ruas[i].nome_rua, vaga_disponivel);
                            vaga_disponivel = 0;
                        }
                    }
                    else
                    {
                        if ( contador == 0 )
                        {
                            printf("\nRuas nao foram cadastradas. Favor, prossiga para opcao 1 do menu.\n");
                        }
                        else
                        {
                            printf("\nO numero de vagas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                    }
                    printf("\n");
                    break;

                case 'c':
                    printf("..........................Todos Carros Estacionados.............................\n");
                    if ( contador > 2 )
                    {
                        for( k = 0 ; k < QUANTIDADE_RUAS ; k++)
                        {
                            aux = 0;
                            switch( k )
                            {
                            case 0:
                                printf("\nRua: %s:\n", ruas[k].nome_rua);
                                for( i = 0 ; i < x1 ; i++)
                                {
                                    for( j = 0 ; j < ruas[k].num_vagas ; j++)
                                    {
                                        if( estacionado1[i].cod_rua == k && ruas[k].status_vaga[j] != 0 && estacionado1[i].jasaiu != 1 )
                                        {
                                            printf("Vaga: %d) %s", estacionado1[i].spot_number+1, estacionado1[i].license_plate);
                                            aux = 1;
                                        }
                                        if( aux == 1)
                                            break;
                                    }
                                }
                                break;

                            case 1:
                                printf("\nRua: %s:\n", ruas[k].nome_rua);
                                for( i = 0 ; i < x2 ; i++)
                                {
                                    for( j = 0 ; j < ruas[k].num_vagas ; j++)
                                    {
                                        if( estacionado2[i].cod_rua == k && ruas[k].status_vaga[j] != 0 && estacionado2[i].jasaiu != 1 )
                                        {
                                            printf("Vaga: %d) %s", estacionado2[i].spot_number+1, estacionado2[i].license_plate);
                                            aux = 1;
                                        }
                                        if( aux == 1)
                                            break;
                                    }
                                }
                                break;

                            case 2:
                                printf("\nRua: %s:\n", ruas[k].nome_rua);
                                for( i = 0 ; i < x3 ; i++ )
                                {
                                    for( j = 0 ; j < ruas[k].num_vagas ; j++ )
                                    {
                                        if( estacionado3[i].cod_rua == k && ruas[k].status_vaga[j] != 0 && estacionado3[i].jasaiu != 1 )
                                        {
                                            printf("Vaga: %d) %s", estacionado3[i].spot_number+1, estacionado3[i].license_plate);
                                            aux = 1;
                                        }
                                        if( aux == 1 )
                                            break;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if ( contador == 0 )
                        {
                            printf("\nRuas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else if ( contador == 1 )
                        {
                            printf("\nNumero de vagas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else
                        {
                            printf("\nValor das vagas nao foram cadastrados. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                    }
                    printf("\n");
                    break;

                case 'd':
                    printf("..........................Carros Estacionados por Rua...........................\n");
                    if ( contador > 2 )
                    {
                        printf("................................Carros Estacionados....................................\n");
                        for( i=0 ; i<QUANTIDADE_RUAS ; i++ )
                        {
                            printf( "\nRua %s  ", ruas[i].nome_rua );

                            for( j=0 ; j<ruas[i].num_vagas ; j++ )
                            {
                                if( ruas[i].status_vaga[j] != 0 )
                                {
                                    printf("1  ");
                                }
                                else
                                    printf("0  ");
                            }
                        }
                    }
                    else
                    {
                        if ( contador == 0 )
                        {
                            printf("\nRuas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else if ( contador == 1 )
                        {
                            printf("\nNumero de vagas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else
                        {
                            printf("\nValor das vagas nao foram cadastrados. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                    }
                    printf("\n");
                    break;

                case 'e':
                    printf("........................Custo Medio por Estacionamento...........................\n");
                    if ( contador > 3 )
                    {
                        soma1 = 0;
                        soma2 = 0;
                        soma3 = 0;
                        for ( i = 0 ; i < x1 ; i++)
                        {
                            soma1 = soma1 + estacionado1[i].total_value;
                        }
                        for ( i = 0 ; i < x2 ; i++)
                        {
                            soma2 = soma2 + estacionado2[i].total_value;
                        }
                        for ( i = 0 ; i < x3 ; i++)
                        {
                            soma3 = soma3 + estacionado3[i].total_value;
                        }

                        media = ( soma1 + soma2 + soma3) / (x1 + x2 + x3 );

                        printf("\nO custo medio por estacionamento e: R$ %.2f", media);
                    }
                    else
                    {
                        if ( contador == 0 )
                        {
                            printf("\nRuas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else if ( contador == 1 )
                        {
                            printf("\nNumero de vagas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else if (contador == 2)
                        {
                            printf("\nValor das vagas nao foram cadastrados. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else
                        {
                            printf("\nNenhum carro foi estacionado ate o momento. Favor, prossiga para a opcao %d do menu.\n", contador + 1);
                        }
                    }
                    printf("\n");
                    break;
                case 'f':
                    printf("........................Total de carros do dia...........................\n");
                    if( contador >= 4 )
                    {
                        //Quantos carros foram estacionados ate o momento
                        printf("\nCarros estacionados(ao total) ate o momento: %d", x1+x2+x3);
                    }

                    else
                    {
                        if ( contador == 0 )
                        {
                            printf("\nRuas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else if ( contador == 1 )
                        {
                            printf("\nNumero de vagas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else if (contador == 2)
                        {
                            printf("\nValor das vagas nao foram cadastrados. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else
                        {
                            printf("\nNenhum carro foi estacionado ate o momento. Favor, prossiga para a opcao %d do menu.\n", contador + 1);
                        }
                    }
                    break;

                case 'g':
                    printf(".....................Total de carros do dia(por rua).......................\n");
                    if( contador >= 4 )
                    {
                        printf("Carros estacionados na Rua 1: %d\n", cont_carros_rua0);
                        printf("Carros estacionados na Rua 2: %d\n", cont_carros_rua1);
                        printf("Carros estacionados na Rua 3: %d\n", cont_carros_rua2);
                    }
                    else
                    {
                        if ( contador == 0 )
                        {
                            printf("\nRuas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else if ( contador == 1 )
                        {
                            printf("\nNumero de vagas nao foram cadastradas. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else if (contador == 2)
                        {
                            printf("\nValor das vagas nao foram cadastrados. Favor, prossiga para opcao %d do menu.\n",contador + 1);
                        }
                        else
                        {
                            printf("\nNenhum carro foi estacionado ate o momento. Favor, prossiga para a opcao %d do menu.\n", contador + 1);
                        }
                    }
                    break;

                case 'h':
                    sair = 1;
                    break;

                default:
                    printf("\nOpcao Invalida! Por Favor, escolha outra opcao!\n\n");
                    break;
                }
            }
            while ( sair != 1 );
            break;

        case 7:
            printf("\nPrograma Encerrado!\n\n");
            printf("\n................................................................................\n");
            break;

        default:
            printf("\nOpcao Invalida! Por Favor, escolha outra opcao!\n\n");
            break;
        }
    }
    while ( opt1 != 7 );

    return 0;
}
