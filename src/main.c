#include <stdio.h>
#include <stdlib.h>
#include "../include/banco.h"

int main()
{
    banco = (Cliente *) malloc(MAX_CLIENTES * sizeof(Cliente));

    if(banco == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    int op;

    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1-Abrir Banco\n");
        printf("2-Consultar Historico\n");
        printf("3-Efetuar Sorteio\n");
        printf("4-Sair\n");

        scanf("%d",&op);

        switch(op)
        {
            case 1:

                abrirBanco();

                break;

            case 2:

                if(bancoAberto)
                    historico();
                else
                    printf("Banco fechado.\n");

                break;

            case 3:

                if(bancoAberto)
                    realizarSorteio();
                else
                    printf("Banco fechado.\n");

                break;

            case 4:

                printf("Sistema encerrado.\n");

                break;

            default:

                printf("Opcao invalida.\n");
        }

    } while(op != 4);
    
	free(banco);
    return 0;
}
