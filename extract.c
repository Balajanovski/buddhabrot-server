/* extract.h
 *
 */

#define BASE 10
#define INFINITY 1000000000
#define TRUE 1
#define FALSE 0
#define COORDINATE_START 49

typedef struct _triordinate {
   double x;
   double y;
   int z;
} triordinate;

triordinate extract (char *message);
double myAtoD (char* message);
int myAtoL (char* message);

/*
int main () {
   char arr[1000];
   scanf 

}
*/

triordinate extract (char *message) {
   triordinate response;
   int start = COORDINATE_START;
   int i = 0;
   char* buffer = malloc(100 * sizeof char);
   while (message[start + i] != "/") {
      buffer[i] = message[start + i];
      i++;
   }
   buffer[i++] = '\0';
   response.z = myAtoL(buffer);
   while ()
   
}


double myAtoD (char* message) {
   double number = 0;
   int negative = message[0] == '-';
   int i = negative;
   int decimal = 0;
   int loop = TRUE;
   int length = strlen(message);
   while (loop) {
      if (decimal > 0) {
         decimal++;
      }
      if (message[i] == '.') {
         decimal = 1;
      } else {
         number *= BASE;
         number += message[i] - '0';
      }
      i++;
   }
   while (decimal > 1) {
      number /= BASE;
      decimal--;
   }
   if (negative) {
      number = -number;
   }
   return number;
}

int myAtoL (char* message) {
   int number = 0;
   int negative = message[0] == '-';
   int i = negative;
   int loop = TRUE;
   while (loop) {
      if (message[i] == '\0') {
         loop = FALSE;
      } else {
         number *= BASE;
         number += message[i];
      }
   }
   return number;
}



