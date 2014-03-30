//fichier : fonctions.c


#include "fonctions.h"

//***************************
//fonction : initRandom,     Initialise la fonction g�n�rant des nombres al�atoires.
//entree : rien
//sortie : rien
//***************************
void initRandom(){
    srand(time(NULL));
}


//***************************
//fonction : alea,     Renvoie un nombre choisi al�atoirement entre les deux bornes entr�es en param�tre. Ces deux bornes peuvent "sortir".
//entree : Un minimum, un maximum.
//sortie : Un nombre(int) choisit al�atoirement.
//***************************
int alea(int min, int max){

    return (int) (rand()%(max+1)+min); //on tire un nombre al�atoire entre 0 et 7
}