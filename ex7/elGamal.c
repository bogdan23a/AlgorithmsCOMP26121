#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <gmp.h>

unsigned long long hcf(unsigned long long a, unsigned long long b)
{
  unsigned long long r = a % b;
  while(r != 0)
  {
    a = b;
    b = r;
    r = a%b;
  }
  return b;
}

unsigned long long fme(unsigned long long  base, unsigned long long power, unsigned long long mod)
{
  unsigned long long result = 1;
  base %= mod;
  while(power != 0)
  {

    if(power & 1)
      result = (result * base) % mod;
    power = power>>1;
    base = (base * base) % mod;
  }
  return result;
}
unsigned long long dl(unsigned long long result, unsigned long long base, unsigned long long mod)
{
  unsigned long long currentPower;
  for(int i = 1; i < mod; i++)
  {
    currentPower = 1;
    for(int j = 1; j <= i; j++)
      currentPower *= base;
    // printf("currentPower : %d\n currentIndex :%d\n", currentPower, i);
    if(currentPower % mod == result)
      return i;
  }
}
unsigned long long imp(unsigned long long y, unsigned long long mod)
{
  for(int i = 1; i < mod; i++)
    if(fme(y*i, 1, mod) == 1)
      return i;
}

void doElGamal()
{
  char *input = malloc(100 * sizeof(char));
  char *tokenized = malloc(100 * sizeof(char));
  char *privateK = malloc(100 * sizeof(char));
  char *pkt = malloc(100 * sizeof(char));
  char *secretNumber = malloc(100 * sizeof(char));
  char *snt = malloc(100 * sizeof(char));
  char *rPrivateKey = malloc(100 * sizeof(char));
  char *rPublicKey = malloc(100 * sizeof(char));
  char *rpkt = malloc(100 * sizeof(char));
  char *message = malloc(100 * sizeof(char));
  char *msgt = malloc(100 * sizeof(char));
  char *privateKr = malloc(100 * sizeof(char));
  char *pk = malloc(100 * sizeof(char));
  char *first = malloc(100 * sizeof(char));
  char *second = malloc(100 * sizeof(char));
  int notExit = 1;
  while(notExit)
  {
    
    printf("Prime modulus is 65537\nPrimitive root wrt 65537 is 3\nChoose: e (encrypt) | d (decrypt) | k (get public key) | x(exit)?\n");
    fgets(input, 100 * sizeof(char), stdin);
    tokenized = strtok(input, ":\n");
    unsigned long long privateKey = 0;
    if(strcmp(tokenized, "k")  == 0)
    {
      printf("Type private key: ");
      fgets(privateK, 100 * sizeof(char), stdin);
      pkt = strtok(privateK, ":\n");
      privateKey = fme(3, atoi(pkt), 65537);
      printf("Public key is: %d\n", privateKey);
    }
    else
    if(strcmp(tokenized, "e") == 0)
    {
      printf("Type secret number to send: ");
      fgets(secretNumber, 100 * sizeof(char), stdin);
      snt = strtok(secretNumber, ":\n");

      printf("Type recipent's public key: ");

      fgets(rPublicKey, 100 * sizeof(char), stdin);
      rpkt = strtok(rPublicKey, ":\n");
      
      unsigned long long M = atoi(snt);
      srand(time(NULL));
      unsigned long long k = rand() % 65537;
      
      printf("%d\n", k);
      unsigned long long a = fme(3, k, 65537);
      unsigned long long b = ((M % 65537) * fme(atoi(rpkt), k, 65537)) % 65537;

      printf("The encrypted key is: (%d, %d)\n", a, b);
    }
    else
    if(strcmp(tokenized, "d") == 0)
    {
      printf("Type in received message in form (a,b): ");
      fgets(message, 100 * sizeof(char), stdin);
      msgt = strtok(message, ":\n");

      first = strtok(msgt,"(), ");
      second = strtok(NULL, "(), ");
      unsigned long long a = atoi(first);
      unsigned long long b = atoi(second);

      printf("Type in your private key: ");
      fgets(privateKr, 100 * sizeof(char), stdin);
      pk = strtok(privateKr, ":\n");
      

      unsigned long long k = dl(a, 3, 65537);

      // printf("%d\n", k);
      unsigned long long M = imp(fme(atoi(pk), k, 65537), 65537);

      printf("The decrypted secret is: %d\n", M);
    }
    else
    if(strcmp(tokenized, "x") == 0)
      notExit = 0;
  }
}

int main(int argc, char **argv) 
{
  // printf("%d\n", hcf(atoi(argv[1]), atoi(argv[2])));
  // printf("%d\n", fme(5, atoi(argv[1]), 19));
  // printf("%d\n", dl(fme(5, atoi(argv[1]), 19), 5, 19));
  // printf("%d\n", imp(atoi(argv[1]), atoi(argv[2])));

  doElGamal();
  // srand(time(NULL));
  // unsigned long long k = rand() % 65537;
  // printf("random k = %d\n", k);

  // unsigned long long M = atoi(argv[1]);
  // printf("secret message M = %d\n", M);

  // unsigned long long privateKey = atoi(argv[2]);
  // printf("private key = %d\n", privateKey);

  // unsigned long long a = fme(3, k, 65537);
  // printf("a = fme( %d, %d, %d ) = %d\n", 3, k, 65537, a);

  // unsigned long long b = ((M % 65537) * fme(privateKey, k, 65537)) % 65537;
  // printf("b = ((%d , %d) * fme( %d, %d, %d) ,%d  =  %d\n", M, 65537, privateKey, k, 65537, 65537, b);




  
  
  // // printf("a = %d, b = %d\n", a, b);


  // printf("decripted k = %d\n",dl(a, 3, 65537));
  // printf("decripted M = %d\n", imp(fme(privateKey, dl(a, 3, 65537), 65537), 65537));
}