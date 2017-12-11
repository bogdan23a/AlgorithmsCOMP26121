#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gmp.h>

void hcf(mpz_t result, mpz_t a, mpz_t b)
{
  mpz_t r;
  mpz_init(r);
  mpz_mod(r, a, b);
  mpz_t zero;
  mpz_init(zero);
  while(mpz_cmp(r, zero) != 0)
  {
    mpz_set(a,b);
    //a = b;
    mpz_set(b,r);
    // b = r;
    mpz_mod(r, a, b);
    // r = a%b;
  }
  mpz_set(result, b);
}

void fme(mpz_t result, mpz_t base, mpz_t power, mpz_t mod)
{
  mpz_powm(result, base, power, mod); 
}

void dl(mpz_t result, mpz_t res, mpz_t base, mpz_t mod)
{
  mpz_t currentPower;
  mpz_init(currentPower);
  int i;
  for(i = 1; mpz_cmp_ui(mod, i) > 0; i++)
  {
    mpz_set_ui(currentPower, 1);
    int j;
    for(j = 1; j <= i; j++)
      mpz_mul(currentPower, currentPower, base);
    mpz_t modul;
    mpz_init(modul);
    mpz_mod(modul, currentPower, mod);
    if(mpz_cmp(modul, res) == 0){
      mpz_set_ui(result, i);
      break;
    }
  }
}

void imp(mpz_t result, mpz_t y, mpz_t mod, mpz_t res)
{
  int i;
  for(i = 1; mpz_cmp_ui(mod, i) > 0; i++){
    mpz_t first;
    mpz_init(first);

    mpz_t second;
    mpz_init(second);

    mpz_t integer;
    mpz_init(integer);
    mpz_set_ui(integer, i);

    mpz_mod(first, integer, mod);
    mpz_mod(second, y, mod);

    mpz_t prod;
    mpz_init(prod);
    mpz_mul(prod, first, second);

    mpz_t total;
    mpz_init(total);
    mpz_mod(total, prod, mod);

    if(mpz_cmp(total, res) == 0){
      mpz_set_ui(result, i);
      break;
    }
  }
}
int read()
{
  char *input = malloc(3 * sizeof(char));
  fgets(input, 3*sizeof(char), stdin);
  if(strcmp(input, "k\n") == 0)
    return 1;
  else
  if(strcmp(input, "e\n") == 0)
    return 2;
  else
  if(strcmp(input, "d\n") == 0)
    return 3;
  else
  if(strcmp(input, "x\n") == 0)
    return 4;
}
void doElGamal()
{

  char *input = malloc(3 * sizeof(char));
  char *tokenized = malloc(100 * sizeof(char));
  //char *privateK = malloc(100 * sizeof(char));
  char *pkt = malloc(100 * sizeof(char));
  char *secretNumber = malloc(100 * sizeof(char));
  char *snt = malloc(100 * sizeof(char));
  char *rPrivateKey = malloc(100 * sizeof(char));
  //char *rPublicKey = malloc(100 * sizeof(char));
  char *rpkt = malloc(100 * sizeof(char));
  char *message = malloc(100 * sizeof(char));
  char *msgt = malloc(100 * sizeof(char));
  char *privateKr = malloc(100 * sizeof(char));
  char *pk = malloc(100 * sizeof(char));
  char *first = malloc(100 * sizeof(char));
  char *second = malloc(100 * sizeof(char));
  int notExit = 1;
  int readAgain = 0;
  int i;
  while(notExit)
  {
    
    if(readAgain == 0)
    {
      printf("Prime modulus is 65537\nPrimitive root wrt 65537 is 3\nChoose: e (encrypt) | d (decrypt) | k (get public key) | x(exit)?\n");     
      i = read();
      printf("(%d)\n", i);
      readAgain = 1;  
    }
    if(i == 1)
    {
      mpz_t privateK;
      mpz_init(privateK);

      printf("Type private key: ");
      gmp_scanf("%Zd", privateK);
      //fgets(privateK, 100 * sizeof(char), stdin);
     
      //pkt = strtok(privateK, ":\n");
    
      mpz_t public;
      mpz_init(public);

      mpz_t base;
      mpz_init(base);
      mpz_set_ui(base, 3);

      mpz_t prime;
      mpz_init(prime);
      mpz_set_ui(prime, 65537);

       
      fme(public, base, privateK, prime);
      gmp_printf("Public key is: %Zd\n", public);
      readAgain = 0;
      // mpf_clear(public);
      // mpf_clear(base);
      // mpf_clear(privateK);
      // mpf_clear(prime);
    }
    else
    if(i == 2)
    {
      printf("Type secret number to send: ");
      mpz_t input, rPublicKey;
      mpz_init(input);
      mpz_init(rPublicKey);
      gmp_scanf("%Zd", input);
      gmp_printf("%Zd", input);
      //fgets(secretNumber, 100 * sizeof(char), stdin);
      
      //snt = strtok(secretNumber, ":\n");
      printf("Type recipent's public key: ");
      gmp_scanf("%Zd", rPublicKey);
      //fgets(rPublicKey, 100 * sizeof(char), stdin);
     printf("%s,%s", secretNumber, rPublicKey);
     // rpkt = strtok(rPublicKey, "\n");
      
      mpz_t M;
printf("%s", secretNumber);
      mpz_init(M); 
      printf("%s", snt);
      mpz_set_str(M, snt, 10);
      gmp_printf("%s", snt);
      gmp_randstate_t randstate;
      
      mpz_t k;
      mpz_init(k);
      mpz_set_ui(k, gmp_urandomm_ui(randstate, 10));

      
      mpz_t a;
      mpz_init(a);

      mpz_t base;
      mpz_init(base);
      mpz_set_ui(base, 3);
     
      mpz_t prime;
      mpz_init(prime);
      mpz_set_ui(prime, 65537);

      fme(a, base, k, prime);

      mpz_t fmeBase;
      mpz_init(fmeBase);
      mpz_set_str(fmeBase, rpkt, 36);

      mpz_t second;
      mpz_init(second);
      fme(second, fmeBase, k, prime);
     
      mpz_t first;
      mpz_init(first);
      mpz_mod(first, M, prime);

      mpz_t b;
      mpz_init(b);
 
      mpz_mul(b, first, second);
      mpz_mod(b, b, prime);
      gmp_printf("The encrypted key is: (%Zd, %Zd)\n", a, b);
      readAgain = 0;
    }
    else
    if(i == 3)
    {

      gmp_printf("Type in received message in form (a,b): ");
      scanf("%s", message);
      // mpz_inp_str(message, stdin, 36);
      msgt = strtok(message, ":\n");

      first = strtok(msgt,"(), ");
      second = strtok(NULL, "(), ");
      mpz_t a;
      mpz_init(a);
      mpz_set_str(a,first, 36);

      mpz_t b;
      mpz_init(b);
      mpz_set_str(b, second, 36);

      gmp_printf("Type in your private key: ");
      scanf("%s", privateKr);
      //mpz_inp_str(privateKr, stdin, 36);
      pk = strtok(privateKr, ":\n");     
  
      mpz_t base;
      mpz_init(base);
      mpz_set_ui(base, 3);

      mpz_t k;
      mpz_init(k);

      mpz_t prime;
      mpz_init(prime);
      mpz_set_ui(prime, 65537);
 
      dl(k, a, base, prime);

      // printf("%d\n", k);
      mpz_t M;
      mpz_init(M);

      mpz_t fmeBase;
      mpz_init(fmeBase);
      mpz_set_str(fmeBase, pk, 36);

      mpz_t y;
      mpz_init(y);
      fme(y, fmeBase, k, prime);
     
      imp(M, y, prime, b);

      printf("The decrypted secret is: %d\n", M);
      readAgain = 0;
    }
    else
    if(i == 4)
      notExit = 0;
    else
    if(i == -110)
      readAgain = 1; 
  }
}

int main(int argc, char **argv) 
{
 /* mpz_t result;
  mpz_init(result);
  mpz_t arg1;
  mpz_t arg2;
  mpz_t arg3;
  mpz_init(arg1);
  mpz_init(arg2);
  mpz_init(arg3);
  mpz_set_ui(arg1, atoi(argv[1]));
  mpz_set_ui(arg2, atoi(argv[2]));
  mpz_set_ui(arg3, atoi(argv[3]));
  // hcf(result, arg1, arg2);
  // fme(result, arg1, arg2, arg3);
  //  dl(result, arg1, arg2, arg3);
  //  imp(result, arg1, arg2, arg3);
  gmp_printf("%Zd\n", result);
  */doElGamal();
}
