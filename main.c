#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

typedef struct{
 char letra[2];
 char morse[10];
} cadenaMorse; //Creamos un tipo de variable con 2 tablas.

void leerArchivo(cadenaMorse cadena[]){
 FILE *fit;
 int i;
 char morse[20];
 i = 0;
 fit = fopen ("morse.txt", "r"); //Abrimos archivo
 bool esLetra = true;
 while (!feof(fit)) //Con este bucle, leemos la letra y la separamos con su morse respectivo.
 {
     if(esLetra){
         esLetra = false;
         fscanf(fit, "%s", cadena[i].letra); //Con este if, solo cogemos la letra del morse
     }
     else{
         esLetra = true;
         fscanf(fit, "%s", cadena[i].morse); //Con este otro, cogeremos la traduccion en morse y avanzamos su posicion
         i++;
     }
 }
 fclose (fit); //Cerramos fichero
}

void codificarMorse(cadenaMorse cadena[]){
  system("cls");
  printf("-Codificar una palabra-\n\n");
  char paraulaMorse[100], paraula[16];
  char opcion;
  int j=0; //Posicion del archivo morse
  int k; //Posicion de la traduccion Morse
  int i=0; //Posicion de la palabra
  bool superaMax=true;
  printf("Escribe una palabra: ");
  scanf("%s", paraula);
    while (superaMax==true){
      i=0;
      while (paraula[i]!='\0'){ //Si no llegamos al final de la palabra
          i++;
      }
      if (i>15){ //Si la palabra supera el tamaño de 15 letras!
          printf("Error! La palabra introducida tiene que ser mas pequeña!!\n");
          funcionMenu();
      }
      else{ //Si la letra es correcta!
          printf("La paraula introduida es -> %s\n", paraula);
          superaMax=false;

      }
  }
  i=0; //Reiniciamos contador, porque esta variable la volvemos a utilizar
  while (paraula[i]!='\0'){
      paraula[i]=toupper(paraula[i]); //Cambiar a mayuscula la letra seleccionada, esta funcion le resta -32 a la ASCII
      if (paraula[i]==cadena[j].letra[0]){
           k = 0; //Si la letra coincide con la posicion 0 del fichero de morse, la (k) se posiciona en la posicion inicial.
          while(cadena[j].morse[k] != '*'){
               paraulaMorse[k] = cadena[j].morse[k]; //Mientras que no llega al centinela (*) vamos a ir rellenando con letras en su posicion y avanzando una posicion
               k++;
          }
          paraulaMorse[k] = ' '; //Damos espacios entre letra y letra
          paraulaMorse[k+1] = ' ';
          paraulaMorse[k+2] = ' ';
          paraulaMorse[k+3] = '\0';
          printf(paraulaMorse);
          j=0; //Reiniciamos la cadena, para volver a comparar desde el principio
          i++; //Avanzamos una posicion a la palabra
      }

      else{
          j++;
      }

  } //Esto es para si queremos volver a traducir otra palabra, tenemos la posibilidad de traducirla o de volver al menu
    printf("\n\nQuieres traducir otra palabra? ");
    scanf("%s", &opcion);
    if (opcion=='s'){
        codificarMorse(cadena);
    }
    else if (opcion=='n'){
        system("cls");
        funcionMenu();
    }
    else{
        printf("Hasta otra! ");
        return 0;
    }
}

void funcionMenu(){

    int num;
    cadenaMorse cadena[35]; //Definimos esta variable global, que la necesitaremos para llamar a las demas acciones.
    leerArchivo(cadena); //Llamamos a la funcion de diccionario
    printf("----Bienvenido al traductor Morse----\n\n");
    printf("1-Codificar una palabra\n");
    printf("2-Codificar un fichero\n");
    printf("3-Descodificar un fichero\n");
    printf("0-Sortir\n\n");
    printf("Escoge una opcion: ");
    scanf("%d", &num); //Leemos la opcion que queremos
    switch (num){
    case 1:
        codificarMorse(cadena); //Llamamos a la accion de codificar morse
        break;
    case 2:
        codificarFitxer(cadena); //Llamamos a la accion de codificar archivo
        break;

    case 3:
        decodificarFitxer(cadena); //Llamamos a la accion de descodificar archivo
        break;

    case 0:
        printf("Hasta luego!!!! ");
        break;

    }
}

void codificarFitxer(cadenaMorse cadena[]){
   FILE * fit;
   FILE * fit2;
   char frase[50],paraulaMorse[200];
   int i = 0; //posicion de la letra de la frase a codificar
   int j = 0; //posicion de la letra del archivo morse
   int k; //posicion del signo morse
   int count = 0; //posicion de la frase en morse
   bool esFinal=false;
   fit = fopen ("original.txt", "r");
   fit2 = fopen ("codificat.txt", "w");

   if (fit!=NULL){ //Si el archivo no esta vacio, entraremos y no dara ningun error
       while (!feof(fit)){ //Con este bucle, leemos la letra y la separamos con su morse respectivo.
           fgets(frase, 50, fit); //Obtenemos la frase, de hasta tamaño 50 y del archivo fit
           while (frase[i]!='\n'){
               if(frase[i] != ' '){
                   frase[i]=toupper(frase[i]); //Cambiar a mayuscula la letra seleccionada
                   if (frase[i]==cadena[j].letra[0]){
                       k = 0; //Si la posicion de la frase coincide con la letra, reiniciamos contador
                       while(cadena[j].morse[k] != '*'){
                           paraulaMorse[count] = cadena[j].morse[k]; //Mientras que no llega al centinela (*) vamos a ir rellenando con letras en su posicion y avanzando una posicion
                           k++;
                           count++; //Avanzamos posicion
                       }
                       if(frase[i+1] != '\n'){
                           paraulaMorse[count] = ' '; //Damos espacios entre letra y letra
                           paraulaMorse[count+1] = ' ';
                           paraulaMorse[count+2] = ' ';
                           count = count + 3; //Avanzamos 3 posiciones
                       }
                       else { //Llega al final de la frase
                           paraulaMorse[count] = '\0'; //Con esto cerramos cada palabra y evitamos que se nos llene de basura
                           count = 0;
                           k = 0; //Reiniciamos contadores
                           if (esFinal){
                                fprintf (fit2, "%s",paraulaMorse);
                                printf("%s \n", paraulaMorse);
                           }//Imprimimos y escribimos la primera linia
                           else{
                               fprintf (fit2, "%s \n", paraulaMorse);
                               printf("%s \n", paraulaMorse);
                           } //Imprimimos y escribimos las demas linias
                       }
                       j=0;
                       i++;
                   }
                   else {
                       j++;
                       if (frase[i+1]=='\0'){//Si llegamos al final del archivo, avanzamos una posicion y añadimos un salto de linia y salimos del bucle
                            esFinal=true;
                            frase[i+1]='\n';
                        }

                   }
               } else {
                   paraulaMorse[count] = ' '; //Damos espacios entre letra y letra
                   paraulaMorse[count+1] = ' ';
                   count = count + 2;
                   i++;
               }

           }
           i = 0;
       }
   }
   else{
       printf ("Hay un error con el fichero!!\n\n");
   }
   fclose(fit);
   fclose(fit2); //Cerramos archivos
   printf("\nSe ha codificado con exito!!\n");
}

void decodificarFitxer(cadenaMorse cadena[]){
   FILE * fit;
   FILE * fit2;
   char lletraMorse[50], fraseLetras[200],fraseMorse[200];
   int posFraseMorse = 0;
   int posLletraMorse = 0;
   int posFraseLetras = 0;
   int contadorEspais = 0;
   fit = fopen ("codificat.txt", "r");
   fit2 = fopen ("decodificat.txt", "w");

   if (fit!=NULL){
       while (!feof(fit)){ //Con este bucle, leemos la letra y la separamos con su morse respectivo.
           fgets(fraseMorse, 200, fit); //Obtenemos cada frase del archivo de un maximo de 200.
           while (fraseMorse[posFraseMorse]!='\n'){
               if(fraseMorse[posFraseMorse]!=' '){
                   contadorEspais = 0;
                   posLletraMorse = 0;
                   while(fraseMorse[posFraseMorse]!=' ' && fraseMorse[posFraseMorse]!='\n'){
                       lletraMorse[posLletraMorse]=fraseMorse[posFraseMorse];
                       posFraseMorse++;
                       posLletraMorse++;
                   } //Si la posicion es diferente a un espacio/salto de linia, comparamos las letras y avanzamos posicion
                   lletraMorse[posLletraMorse] = '*'; //Cada vez que llegamos al final del morse, ponemos asterico
                   // Comparar y decodificar el Morse para obtener la letra
                    bool trobat = false;
                    int i=0;
                    while(!trobat && i<35) {
                        int j=0;
                        bool lletraCoincideix = true;
                        while (lletraCoincideix && lletraMorse[j] != '*' && cadena[i].morse[j] != '*') {
                            if (lletraMorse[j] != cadena[i].morse[j]) {
                                lletraCoincideix = false;
                            } //Si el morse no coincide, avanzamos la posicion
                            j++;
                        }
                        if (lletraCoincideix && lletraMorse[j] == '*' && cadena[i].morse[j] == '*')
                            trobat = true; //Si la letra coincide, trobat vuelve a true
                        else i++;
                    }

                    if (trobat) {
                        // Metemos la letra y avanzamos posicion
                        fraseLetras[posFraseLetras] = tolower(cadena[i].letra[0]); //Y la pasamos a miniscula, tolower añade 32 a la tabla ASCII
                        posFraseLetras++;
                    }
               } else if (fraseMorse[posFraseMorse] == ' ')
                    contadorEspais++; //Si tenim 5 espais, significa que canviem de paraula i afegim un espai
                if (contadorEspais == 4) {
                    fraseLetras[posFraseLetras] = ' ';
                    posFraseLetras++;
                }

               posFraseMorse++;
           }
           if (fraseMorse[posFraseMorse] == '\n') { //Llega al final de la frase
               fraseLetras[posFraseLetras] = '\0'; //Cerramos la frase
               fprintf (fit2, "%s \n", fraseLetras);
               printf("%s \n", fraseLetras);
            }
           posFraseMorse=0;
           posFraseLetras=0;
       }
   }

   else{
       printf ("Hay un error con el fichero!!\n\n");
       funcionMenu();
   }
   fclose (fit);
   fclose(fit2);
   printf("\nSe ha codificado con exito!!\n");
}

int main()
{
    funcionMenu();

return 0;
}
