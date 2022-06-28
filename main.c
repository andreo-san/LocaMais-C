#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

// Registro / Tipo de Variavel
struct tClientes {
int senha;
int codigo;
char usuario[10];
char deletado; // deletado = '*' / nao deletado = ' ' - exclusao logica
};

// Registro / Tipo de Variavel
struct tVeiculos {
int codigo;
int ocupantes;
int alugado; //se 1 = alugado, se 0 = disponível
int diaAlugado;
int diaDevolucao;
char modelo[30];
char deletado; // deletado = '*' / nao deletado = ' ' - exclusao logica
};

//Prototipos
int menu();
void cadastrar();
void listar();
void consultar();

//Programa Principal
int main(void) {
struct tClientes clientes;
printf("%i", clientes.codigo);
setlocale( LC_ALL, "portuguese");

int op;

do{
op = menu();
switch (op) {

case 1:
printf("===Cadastrar===\n");
cadastrar();
break;

case 2:
printf("===Login===\n");
login();
break;

case 3:
printf("===Listar===\n");
listar();
break;

case 4:
printf("===Cadastrar Veículos===\n");
cadastroDeVeiculos();
break;

case 5:
printf("===Listar Veículos===\n");
listarCarros();
break;

case 6:
printf("===Alugar Veículos===\n");
cadastrarLocacao();
break;
}
}while (op != 0);

// system("pause");
return 0;
}

//Menu pós login
int menuLogado()
{
    int opcao;
    do {
    printf("=== ESCOLHA UMA OPÇÃO ===\n");
    printf("1. Alugar um carro\n");
    printf("2. Devolução de carro alugado\n");
    printf("3. Listar carros alugados\n");
    printf("0. Voltar\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {

    case 1:
    printf("===Listar Veículos===\n");
    listarCarros();
    break;

    case 2:
    printf("===Alugar Veículos===\n");
    cadastrarLocacao();
    break;
    }
    if ((opcao < 0) || (opcao > 8))
    printf ("Opcao Digitada Incorreta!\n");
    } while ((opcao < 0) || (opcao > 8));

    return opcao;
}

//Menu de Opcoes
int menu (void){

int opcao;
do {
printf("=== ESCOLHA UMA OPÇÃO ===\n");
printf("1. Cadastrar\n");
printf("2. Login\n");
printf("3. Listar\n");
printf("0. Sair\n");
printf("Digite sua opcao: ");
scanf("%d", &opcao);
if ((opcao < 0) || (opcao > 8))
printf ("Opcao Digitada Incorreta!\n");
} while ((opcao < 0) || (opcao > 8));

return opcao;
}

//Funcao Inclusao
void cadastrar(){
struct tClientes clientes;
srand(time(NULL));
FILE *arq = fopen("clientes.txt", "ab");
if (arq == NULL){
printf("Erro ao abrir arquivo");
return;
}
printf("Digite o usuario: \n");
fflush(stdin);
gets(clientes.usuario);
printf("Digite a senha: \n");
scanf("%d", &clientes.senha);

fwrite (&clientes, sizeof(clientes), 1, arq);


fclose(arq);
}

//Funcao Listar
void listar (){

struct tClientes clientes;
FILE *arq = fopen("clientes.txt", "rb");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

while (fread (&clientes, sizeof(clientes), 1, arq))
printf("Cod %d --- Descricao: %-8s --- Deletado?(%c) --- Codigo: %i\n",clientes.senha, clientes.usuario, clientes.deletado, clientes.codigo);

fclose(arq);
}

//Funcao Consultar
void login(){

FILE *arq = fopen("clientes.txt", "rb");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

struct tClientes clientes;
int sen, achei = 0;
char usuario[10];
printf ("Digite o seu usuario: \n");
fflush(stdin);
gets(usuario);
printf ("Digite a sua senha: \n");
scanf ("%d", &sen);


while (fread (&clientes, sizeof(clientes), 1, arq)){
if ((sen == clientes.senha) && (clientes.deletado != '*')) {
    int ret = strcmp(usuario, clientes.usuario);
        if(ret == 0){
            achei = 1;
        }
}
}

if (!achei)
printf ("Usuário não cadastrado!!\n");

fclose(arq);
menuLogado();
}


void cadastroDeVeiculos()
{
    struct tVeiculos veiculos;
    FILE *arq = fopen("veiculos.txt", "ab");
    if (arq == NULL){
        printf("Erro ao abrir arquivo");
        return;
    }

    printf("=== CADASTRO DE VEÍCULOS ===\n");
    printf("Digite o modelo do veículo\n");
    fflush(stdin);
    gets(veiculos.modelo);
    printf("Quantas vagas o carro tem\n");
    scanf("%d", &veiculos.ocupantes);

    veiculos.codigo = rand()%100;
    veiculos.alugado = 0;

    fwrite (&veiculos, sizeof(veiculos), 1, arq);

    fclose(arq);
}

//Funcao Listar Carros
void listarCarros (numVagas, dataRetirada, dataDevolucao){

    struct tVeiculos veiculos;
    FILE *arq = fopen("veiculos.txt", "rb");
    if (arq == NULL){
    printf("Arquivo inexistente!");
    return;
    }

    while (fread (&veiculos, sizeof(veiculos), 1, arq))
        if(veiculos.ocupantes >= numVagas)
            printf("Modelo %s --- Vagas: %d --- Alugado?(%i) --- Codigo: %i\n",veiculos.modelo, veiculos.ocupantes, veiculos.alugado, veiculos.codigo);

    fclose(arq);
}

//Cadastro de locação
void cadastrarLocacao()
{
    int numVagas, dataRetirada, dataDevolucao;

    printf("Quantas vagas para o carro?\n");
    scanf("%i", &numVagas);

    printf("Digite a data de retirada\n");
    scanf("%i", &dataRetirada);

    printf("Digite a data de devolução\n");
    scanf("%i", &dataDevolucao);

    listarCarros(numVagas, dataRetirada, dataDevolucao);

}
