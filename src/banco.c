#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/banco.h"

Cliente *banco;
int qtdClientes = 0;
int contadorConta = 1000;
int bancoAberto = 0;

void gerarNumeroConta(char numero[], int tipo)
{
    sprintf(numero,"%d-%02d",contadorConta++,tipo);
}

int localizarCliente(char nome[])
{
    for(int i=0;i<qtdClientes;i++)
    {
        if(strcmp(nome,banco[i].nome)==0)
            return i;
    }

    return -1;
}

float saldoTotalCliente(Cliente c)
{
    float total = 0;

    for(int i=0;i<c.qtdContas;i++)
        total += c.contas[i].saldo;

    return total;
}

int fibonacci(int n)
{
    if(n <= 1)
        return n;

    int a=0,b=1,c;

    for(int i=2;i<=n;i++)
    {
        c=a+b;
        a=b;
        b=c;
    }

    return b;
}

void cadastrarCliente()
{
    Cliente novo;

    printf("Nome do cliente: ");
    scanf(" %[^\n]", novo.nome);

    novo.qtdContas = 0;
    novo.possuiEmprestimo = 0;
    novo.valorEmprestimo = 0;
    novo.participouSorteio = 0;
    novo.premioRecebido = 0;

    banco[qtdClientes++] = novo;

    printf("Cliente cadastrado!\n");
}

void abrirConta()
{
    char nome[50];
    int tipo;

    printf("Cliente: ");
    scanf(" %[^\n]", nome);

    int id = localizarCliente(nome);

    if(id == -1)
    {
        printf("Cliente nao encontrado.\n");
        return;
    }

    Cliente *c = &banco[id];

    int possuiCorrente = 0;
    int possuiSalario = 0;

    for(int i=0;i<c->qtdContas;i++)
    {
        if(c->contas[i].tipo == 1)
            possuiCorrente = 1;

        if(c->contas[i].tipo == 2)
            possuiSalario = 1;
    }

    printf("1-Corrente\n");
    printf("2-Salario\n");
    printf("3-Poupanca\n");
    scanf("%d",&tipo);

    if((tipo == 1 && possuiSalario) ||
       (tipo == 2 && possuiCorrente))
    {
        printf("Nao pode possuir conta corrente e salario ao mesmo tempo.\n");
        return;
    }

    if(c->qtdContas >= MAX_CONTAS)
    {
        printf("Limite de contas atingido.\n");
        return;
    }

    Conta nova;

    nova.tipo = tipo;
    nova.saldo = 0;
    nova.tituloCapitalizacao = 0;

    gerarNumeroConta(nova.numero,tipo);

    c->contas[c->qtdContas++] = nova;

    printf("Conta criada: %s\n",nova.numero);
}

void depositar()
{
    char numero[20];
    float valor;

    printf("Conta: ");
    scanf("%s",numero);

    printf("Valor: ");
    scanf("%f",&valor);

    for(int i=0;i<qtdClientes;i++)
    {
        for(int j=0;j<banco[i].qtdContas;j++)
        {
            if(strcmp(numero,banco[i].contas[j].numero)==0)
            {
                banco[i].contas[j].saldo += valor;
                printf("Deposito realizado.\n");
                return;
            }
        }
    }

    printf("Conta nao encontrada.\n");
}

void sacar()
{
    char numero[20];
    float valor;

    printf("Conta: ");
    scanf("%s",numero);

    printf("Valor: ");
    scanf("%f",&valor);

    for(int i=0;i<qtdClientes;i++)
    {
        for(int j=0;j<banco[i].qtdContas;j++)
        {
            if(strcmp(numero,banco[i].contas[j].numero)==0)
            {
                banco[i].contas[j].saldo -= valor;
                printf("Saque realizado.\n");
                return;
            }
        }
    }

    printf("Conta nao encontrada.\n");
}

void solicitarEmprestimo()
{
    char nome[50];

    printf("Cliente: ");
    scanf(" %[^\n]", nome);

    int id = localizarCliente(nome);

    if(id == -1)
        return;

    Cliente *c = &banco[id];

    if(c->possuiEmprestimo)
    {
        printf("Cliente ja possui emprestimo.\n");
        return;
    }

    int corrente = 0;
    int poupanca = 0;
    float saldoTotal = 0;

    for(int i=0;i<c->qtdContas;i++)
    {
        saldoTotal += c->contas[i].saldo;

        if(c->contas[i].tipo == 1)
            corrente = 1;

        if(c->contas[i].tipo == 3)
            poupanca = 1;
    }

    if(corrente && poupanca)
    {
        float limite = (10 * saldoTotal) * 0.25;

        c->possuiEmprestimo = 1;
        c->valorEmprestimo = limite;

        printf("Emprestimo aprovado: %.2f\n",limite);
    }
    else
    {
        printf("Cliente nao atende aos requisitos.\n");
    }
}

void comprarTitulo()
{
    char nome[50];

    printf("Cliente: ");
    scanf(" %[^\n]", nome);

    int id = localizarCliente(nome);

    if(id == -1)
        return;

    Cliente *c = &banco[id];

    for(int i=0;i<c->qtdContas;i++)
    {
        if(c->contas[i].tipo == 2 &&
           c->contas[i].saldo >= 1000 &&
           c->contas[i].saldo <= 1500)
        {
            c->contas[i].tituloCapitalizacao = 1;
            printf("Titulo adquirido.\n");
            return;
        }
    }

    printf("Cliente nao apto.\n");
}

void verificarNegativo(Cliente c)
{
    for(int i=0;i<c.qtdContas;i++)
    {
        if(c.contas[i].tipo == 1 &&
           c.contas[i].saldo < 0)
        {
            printf("\nALERTA!\n");
            printf("Conta Corrente %s negativa.\n",
                   c.contas[i].numero);

            printf("Saldo: %.2f\n",
                   c.contas[i].saldo);
        }
    }
}

int possuiTitulo(Cliente c)
{
    for(int i=0;i<c.qtdContas;i++)
    {
        if(c.contas[i].tituloCapitalizacao)
            return 1;
    }

    return 0;
}

void ordenarRanking(Ranking r[], int n)
{
    Ranking aux;

    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(r[j].saldoTotal > r[i].saldoTotal)
            {
                aux = r[i];
                r[i] = r[j];
                r[j] = aux;
            }
        }
    }
}

void realizarSorteio()
{
    if(qtdClientes < 5)
    {
        printf("Necessario minimo de 5 clientes.\n");
        return;
    }

    Ranking ranking[MAX_CLIENTES];

    for(int i=0;i<qtdClientes;i++)
    {
        ranking[i].indiceCliente = i;
        ranking[i].saldoTotal = saldoTotalCliente(banco[i]);
    }

    ordenarRanking(ranking,qtdClientes);

    for(int i=0;i<5;i++)
    {
        if(!possuiTitulo(banco[ranking[i].indiceCliente]))
        {
            printf("Todos os 5 maiores saldos devem possuir titulo.\n");
            return;
        }
    }

    srand(time(NULL));

    int valorFib = fibonacci((rand()%10)+5);
    int vencedor = valorFib % 5;

    int indiceReal = ranking[vencedor].indiceCliente;

    float saldoAtual =
        saldoTotalCliente(banco[indiceReal]);

    float premio = saldoAtual * 10;

    banco[indiceReal].participouSorteio = 1;
    banco[indiceReal].premioRecebido = premio;

    if(banco[indiceReal].qtdContas > 0)
    {
        banco[indiceReal].contas[0].saldo += premio;
    }

    printf("\n===== VENCEDOR =====\n");
    printf("Nome: %s\n",
            banco[indiceReal].nome);
    printf("Premio: %.2f\n",
            premio);
}

void historico()
{
    float saldoBanco = 0;

    printf("\n== SALDO TOTAL DO BANCO ==\n");

    for(int i=0;i<qtdClientes;i++)
        saldoBanco += saldoTotalCliente(banco[i]);

    printf("%d | R$ %.2f\n",
           qtdClientes,
           saldoBanco);

 printf("\n== CLIENTES APTOS A EMPRESTIMO ==\n");

for(int i = 0; i < qtdClientes; i++)
{
    int possuiCorrente = 0;
    int possuiPoupanca = 0;
    char numeroConta[15] = "";
    float saldoTotal = 0;

    for(int j = 0; j < banco[i].qtdContas; j++)
    {
        saldoTotal += banco[i].contas[j].saldo;

        if(banco[i].contas[j].tipo == 1)
        {
            possuiCorrente = 1;
            strcpy(numeroConta,
                   banco[i].contas[j].numero);
        }

        if(banco[i].contas[j].tipo == 3)
        {
            possuiPoupanca = 1;
        }
    }

    printf("\nDEBUG: %s\n", banco[i].nome);
    printf("Corrente: %d\n", possuiCorrente);
    printf("Poupanca: %d\n", possuiPoupanca);
    printf("Saldo Total: %.2f\n", saldoTotal);

    if(possuiCorrente && possuiPoupanca)
    {
        float limite = (10 * saldoTotal) * 0.25;

        printf("%s | %s | %.2f\n",
               banco[i].nome,
               numeroConta,
               limite);
    }
}

    printf("\n== CLIENTES COM SALDO NEGATIVO NA CONTA CORRENTE ==\n");

    for(int i=0;i<qtdClientes;i++)
    {
        for(int j=0;j<banco[i].qtdContas;j++)
        {
            if(banco[i].contas[j].tipo == 1 &&
               banco[i].contas[j].saldo < 0)
            {
                printf("%s | %s | %.2f\n",
                       banco[i].nome,
                       banco[i].contas[j].numero,
                       banco[i].contas[j].saldo);
            }
        }
    }

    printf("\n== CLIENTES APTOS A COMPRA DE TITULOS ==\n");

    for(int i=0;i<qtdClientes;i++)
    {
        for(int j=0;j<banco[i].qtdContas;j++)
        {
            if(banco[i].contas[j].tipo == 2 &&
               banco[i].contas[j].saldo >= 1000 &&
               banco[i].contas[j].saldo <= 1500)
            {
                printf("%s | %s | %.2f\n",
                       banco[i].nome,
                       banco[i].contas[j].numero,
                       banco[i].contas[j].saldo);
            }
        }
    }

    printf("\n== CLIENTES CONTEMPLADOS NO SORTEIO ==\n");

    for(int i=0;i<qtdClientes;i++)
    {
        if(banco[i].participouSorteio)
        {
            printf("%s | %.2f\n",
                   banco[i].nome,
                   banco[i].premioRecebido);
        }
    }
}

void abrirBanco()
{
    bancoAberto = 1;

    int op;

    do
    {
        printf("\n===== BANCO ABERTO =====\n");
        printf("1-Cadastrar Cliente\n");
        printf("2-Abrir Conta\n");
        printf("3-Depositar\n");
        printf("4-Sacar\n");
        printf("5-Solicitar Emprestimo\n");
        printf("6-Comprar Titulo\n");
        printf("0-Voltar\n");

        scanf("%d",&op);

        switch(op)
        {
            case 1: cadastrarCliente(); break;
            case 2: abrirConta(); break;
            case 3: depositar(); break;
            case 4: sacar(); break;
            case 5: solicitarEmprestimo(); break;
            case 6: comprarTitulo(); break;
        }

    }while(op != 0);
}

