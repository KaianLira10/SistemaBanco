#ifndef BANCO_H
#define BANCO_H

#define MAX_CLIENTES 100
#define MAX_CONTAS 3

typedef struct
{
    int tipo;
    char numero[15];
    float saldo;
    int tituloCapitalizacao;
} Conta;

typedef struct
{
    char nome[50];
    Conta contas[MAX_CONTAS];
    int qtdContas;
    int possuiEmprestimo;
    float valorEmprestimo;
    int participouSorteio;
    float premioRecebido;
} Cliente;

typedef struct
{
    int indiceCliente;
    float saldoTotal;
} Ranking;

extern Cliente *banco;
extern int qtdClientes;
extern int contadorConta;
extern int bancoAberto;

void gerarNumeroConta(char numero[], int tipo);
int localizarCliente(char nome[]);
float saldoTotalCliente(Cliente c);
int fibonacci(int n);

void cadastrarCliente();
void abrirConta();
void depositar();
void sacar();
void solicitarEmprestimo();
void comprarTitulo();
void verificarNegativo(Cliente c);
void ordenarRanking(Ranking r[], int n);
int possuiTitulo(Cliente c);
void realizarSorteio();
void historico();
void abrirBanco();

#endif
