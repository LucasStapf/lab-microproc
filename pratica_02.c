// Lucas Stapf
// Vitor Favrin

#define B1 0b11101110
#define B2 0b11101101
#define B3 0b11101011
#define B4 0b11011110
#define B5 0b11011101
#define B6 0b11011011
#define B7 0b10111110
#define B8 0b10111101

unsigned short index = 0;
int v[] = {0b01111111, 0b10111111, 0b11011111, 0b11101111};
int timel, timeh;

int port_on() {

}

void main() {
     
     ANSELA = 0; // TESTAR LED TIRAR DPS
     TRISA = 0;
     
     ANSELB = 0;
     INTCON2.RBPU = 0; // Habilitar pullup interno
     WPUB = 0b00001111;
     TRISB = 0b00001111; // Definindo os ports de entrada e saida
     
     while (1) {
           LATB = v[index % 4];
           switch (PORTB) {
                  case B1:
                       LATA = 0b00000001;        // 1
                       break;
                  case B2:
                       LATA = 0b00000010;
                       break;
                  case B3:
                       LATA = 0b00000100;
                       break;
                  case B4:
                       LATA = 0b00001000;
                       break;
                  case B5:
                       LATA = 0b00010000;
                       break;
                  case B6:
                       LATA = 0b00100000;
                       break;
                  case B7:
                       LATA = 0b00000010;
                       break;
                  case B8:
                       LATA = 0b00000010;
                       break;
                  default:
                       LATA = 0b00000000;
                       break;
           }
           index++;
     }
}