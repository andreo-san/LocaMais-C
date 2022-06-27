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
            printf("Cod %d --- Descricao: %-8s --- Valor R$ %4.2f\n",clientes.senha, clientes.usuario);
            achei = 1;
        }
}
}

if (!achei)
printf ("Usuário não cadastrado!!\n");

fclose(arq);
menuLogado();
}
