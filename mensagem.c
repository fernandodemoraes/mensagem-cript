#include <stdio.h>
#include <string.h>
#include <math.h>

/* 
Autores: Fernando de Moraes Sousa
  	 Fernando Santos
  	 Luiz Gabriel
  		 
Proposta: Este software tem o objetivo de atender uma demanda proposta pelo Projeto Integrado Multidisciplinar (PIM).
O software encripta e desencripta mensagens usando criptografia RSA.

Baseado em algoritmo feito por Lionel em 2008: http://cppgm.blogspot.com.br/2008/01/rsa-algorithm.html
*/
char msg[1024];
int msgint[1024];
int tamanhoDaString;
int qq; // quociente de Euler
int n; // produto dos números primos p e q
int e; // chave Pública
int d; // chave Privada
int c; // criptografia
int primo;
int indice;
int cont;

/*
Verifica se o número é primo
*/
int verificar_primo(unsigned int numero) {
  int primo;
  primo = (numero / 2) + 1;

  while (numero % primo != 0) {
    primo--;
  }

  // é primo	
  if (primo == 1) {
    printf("\n\tNumero primo\n");
  } else {
    // não é primo
    printf("\n\tNumero nao e Primo\n");
    return;
  }
}

/*
Função desenvolvida Elgio Schlemer http://www.vivaolinux.com.br/script/Algoritmo-de-euclides-estendido-%28calcula-o-D-RSA%29
*/
long mod(long a, long b) {
	
  long r = a % b;

  // uma correção é necessária se r e b não forem do mesmo sinal
  // se r for negativo e b positivo, precisa corrigir */
  if ((r < 0) && (b > 0)) {
    return (b + r);
  }
	
  /* Se r for positivo e b negativo, nova correcao */
  if ((r > 0) && (b < 0)) {
    return (b + r);
  }

  return (r);
}

/*
Função desenvolvida Elgio Schlemer http://www.vivaolinux.com.br/script/Algoritmo-de-euclides-estendido-%28calcula-o-D-RSA%29
*/
long euclides_ext(long a, long b, long c) {
  // cálculo de Euclides Extendido para retornar o valor de 'd'
  long r;

  r = mod(b, a);

  // retorna (c/a) % (b/a)
  if (r == 0) {
    return (mod((c / a), (b / a)));
  }

  return ((euclides_ext(r, a, -c) * b + c) / (mod(a, b)));
}

/*
Função para encriptar a mensagem
*/
void criptografia() {
  c = 1;
  cont; // contador que percorre todo o calculo M ^ e % n, onde 'e' é a chave pública e também a quantidade de interações com o cálculo

  for (cont = 0; cont < e; cont++) {
    c = c * msg[indice] % n; // cálculo de criptografia
    msgint[indice] = msg[indice]; // igualdade de vetores de caracteres para inteiros
    msgint[indice] = c; // igualdade do cálculo de 'c' para o vetor de inteiros, necessário para usar na descriptografia
  }

  printf("%d ", c);

  return;
}

/*
Função para encriptar a mensagem
*/
void descriptografar() {
  int m = 1;
  cont; // contador que percorre todo o calculo M ^ d % n, onde 'd' é a chave privada e também a quantidade de interações com o cálculo

  // cálculo de descriptografia
  for (cont = 0; cont < d; cont++) {
    m = m * msgint[indice] % n;
  }

  printf("%c", m);

  return;
}

/*
Função principal
*/
int main() {
  system("color 8F"); // definição da cor do fundo da tela e a cor da letra

  int opcao;
  int p; // primeiro número primo
  int q; // segundo número primo
  int result;

  FILE * arquivo;

  // nesse arquivo será guardada a mensagem codificada
  arquivo = fopen("codigo.txt", "w");

  printf("::::::::::::::::MENSAGEMCRIPT:::::::::::::::::");
  printf("\n\n\t  Bem vindo ao MensagemCript           \n\n");
  sleep(1);

  do {
    //Menu

    printf("\n\n.---------------------------------------------.\n");
    printf("| 0. Criar chaves publica e privada.          |\n");
    printf(".---------------------------------------------.\n");
    printf("| 1. Digitar e criptografar a mensagem.       |\n");
    printf(".---------------------------------------------.\n");
    printf("| 2. Descriptografar a mensagem.              |\n");
    printf(".---------------------------------------------.\n");
    printf("| 3. Sobre.                                   |\n");
    printf(".---------------------------------------------.\n");
    printf("| 4. Sair.                                    |\n");
    printf(".---------------------------------------------.\n\n");
    printf("Digite sua opcao: ");
    scanf("%d", & opcao);

    switch (opcao) {
    case 0:

      system("cls");

      printf(":::::::::::::::::MENSAGEMCRIPT:::::::::::::::::");
      printf("\n\n\t        CRIE SUA CHAVE             \n\n");

      // se o número não for primo e nem maior que 255 ele entra em um loop
      while (primo != 1 && n < 256) {
        printf("\nDigite o primeiro numero primo: ");
        scanf("%d", & p);

        verificar_primo(p);

        printf("\nDigite o segundo numero primo: ");
        scanf("%d", & q);

        verificar_primo(q);

        // produto dos número primos
        n = p * q;

        // cálculo do quociente de Euler
        qq = (p - 1) * (q - 1);

        // algoritmo trabalha com caracteres, que na tabela ASCII são 255 caracteres
        // caso valor seja menor que 255 o cálculo não satisfaz a criptografia saindo incorrentamente
        if (n < 256) {
          system("cls");

          printf("\nValores invalidos ou o produto dos numeros primos sao menores que 255.\n\n");
          printf("\nTente novamente.\n\n");
          continue;
        }

        // mostra na tela o Quociente de Euler
        printf("\n\tF(n)\t= %d\n", qq);
        printf("\nDigite um numero primo para a chave publica: ");
        scanf("%d", & e);

        verificar_primo(e);

        // o valor de 'e' não pode ser maior que o Quociente de Euler				
        if (qq < e) {
          system("cls");
          printf("\nValores invalidos ou chave publica maior que %d.\n\n", qq);
        }

        // limpar o valor das variáveis
        fflush(stdin);

      }

      // cálculos da chave privada

      d = euclides_ext(e, qq, 1);

      system("cls");
      printf(":::::::::::::::::MENSAGEMCRIPT:::::::::::::::::");
      printf("\n\n\t            CHAVES                  \n\n");
      printf("\nOs valores da chave publica sao necessario para\n");
      printf("que alguem lhe envie uma mensagem.\n\n");

      printf("\nOs valores da chave privada e pessoal e somente\n");
      printf("o usuario deve ter acesso para descriptografar suas\n");
      printf("mensagens.\n\n");

      printf("\n\t{Chave Publica: %d, Modulo: %d}\n", e, n);
      printf("\n\t{Chave Privada: %d, Modulo: %d}\n\n", d, n);
      printf("\nDeseja voltar ao Menu Principal? 1. Sim / 2. Nao: ");
      scanf("%d", & opcao);
      printf("\n");

      if (opcao == 1) {
        opcao == 5;
      } else {
        system("PAUSE");
        return 0;
      }

      break;

    case 1:

      // criptografando o texto
      system("cls");
      printf(":::::::::::::::::MENSAGEMCRIPT:::::::::::::::::");
      printf("\n\n\t          MENSAGEM                  \n\n");
      printf("\nDigite o valor da chave publica: ");
      scanf("%d", & e);

      verificar_primo(e);

      printf("\nDigite um valor do modulo: ");
      scanf("%d", & n);

      printf("\n\nDigite sua mensagem: ");
      //[^\n] necessário para ignorar os espaços
      scanf(" %[^\n]s", msg);
      printf("\n\nMensagem criptografada...\n\n");

      tamanhoDaString = strlen(msg);

      // faz o cálculo em cada caractere para criptografar	
      for (indice = 0; indice < tamanhoDaString; indice++) {
        criptografia();
        fprintf(arquivo, "%d ", c); // grava a criptografia no arquivo		
      }

      // fecha a escrita do arquivo
      fclose(arquivo);

      break;

    case 2:

      // desencriptografando o texto			
      system("cls");
      printf(":::::::::::::::::MENSAGEMCRIPT:::::::::::::::::");
      printf("\n\n\t        DESCRIPTOGRAFIA                  \n\n");
      printf("\nDigite um valor da chave privada: ");
      scanf("%d", & d);

      verificar_primo(d);

      printf("\nDigite um valor do modulo: ");
      scanf("%d", & n);

      printf("\n\nMensagem descriptografada...\n\n");
		    
      //Faz o cálculo em cada caractere para descriptografar
      for (indice = 0; indice < tamanhoDaString; indice++)
      {
        descriptografar();
      }

      break;

    case 3:

      // sobre o mensangem_cript						
      system("cls");
      printf(":::::::::::::::::MENSAGEMCRIPT:::::::::::::::::");
      printf("\n\nO MensagemCript %c um servi%co do governo que\npermite criptografar ", 130, 135);
      printf("mensagens com total\nseguran%ca.\n\n", 135);
      break;

    case 4:

      // sair do mensangem_cript				
      system("cls");
      printf(":::::::::::::::::MENSAGEMCRIPT:::::::::::::::::");
      printf("\n\nObrigado por utilizar o MensagemCript \n\n\n");
      printf("---------------------------------------------\n\n");
      system("PAUSE");
      return 0;

    case 5:

      system("cls");
      break;

    default:

      // mensagem padrão caso a opção seja inválida
      system("cls");
      printf(":::::::::::::::::MENSAGEMCRIPT:::::::::::::::::");
      printf("\n\nOpcao invalida! Tente novamente.\n\n");
      break;
    }
  } while (opcao);
}
