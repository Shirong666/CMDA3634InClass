#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */
FILE* public_key;
public_key = fopen("public_key.txt", "r");

FILE * mes;
mes = fopen("message.txt","w");
fscanf(public_key,"%u\n%u\n%u\n%u\n",&n,&p,&g,&h);

unsigned int charsPerInt = (n-1)/8;
padString(message,charsPerInt);


 unsigned int Nchars = strlen(message);
  unsigned int Nints  = strlen(message)/charsPerInt;

  //storage for message as elements of Z_p
  unsigned int *Zmessage =
      (unsigned int *) malloc(Nints*sizeof(unsigned int));

  //storage for extra encryption coefficient
  unsigned int *a =
      (unsigned int *) malloc(Nints*sizeof(unsigned int));

  // cast the string into an unsigned int array
  convertStringToZ(message, Nchars, Zmessage, Nints);

  //Encrypt the Zmessage with the ElGamal cyrptographic system
  ElGamalEncrypt(Zmessage,a,Nints,p,g,h);

fprintf(mes,"%u\n",Nints);
  for (unsigned int i=0;i<Nints;i++) {
    fprintf(mes,"%u %u\n", Zmessage[i], a[i]);
  }

fclose(public_key);
fclose(mes);


  return 0;
}
