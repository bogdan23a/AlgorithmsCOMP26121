#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    if(currentPower % mod == result)
      return i;
  }
}
unsigned long long imp(unsigned long long y, unsigned long long mod, unsigned long long result)
{
  for(int i = 1; i < mod; i++)
    if(((i % mod) * (y % mod)) % mod == result)
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
  char *comp = malloc(100 * sizeof(char));
  char *compt = malloc(100 * sizeof(char));
  comp = "5";
  int notExit = 1;
  while(notExit)
  {
    
    printf("Prime modulus is 65537\nPrimitive root wrt 65537 is 3\nChoose: e (encrypt) | d (decrypt) | k (get public key)  | x(exit)?\n");
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
      unsigned long long k = rand() % atoi(comp);
      
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

      
      unsigned long long M = imp(fme(fme(3, atoi(pk), 65537), k, 65537), 65537, b);
      printf("%d\n", M);
      printf("The decrypted secret is: %d\n", M);
    }
    else
    if(strcmp(tokenized, "x") == 0)
      notExit = 0;
  }
}

int main(int argc, char **argv) 
{
  doElGamal();
}