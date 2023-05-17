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
int timerl, timerh;


void interrupt_high() iv 0x0008 ics ICS_AUTO {
     if (INTCON.TMR0IF == 1) {
          TMR0L = timerl;
          TMR0H = timerh;    
          INTCON.TMR0IF = 0;
          LATC.F2 = ~LATC.F2
     }
}

void config_global_interruption() {
     INTCON.GIEH = 1; // Chave geral
     INTCON.GIEL = 1; // Vetor de baixa prioridade
     RCON.IPEN = 1;
}

void main() {
     
     ANSELA = 0; // TESTAR LED TIRAR DPS
     TRISA = 0;
     
     ANSELB = 0;
     INTCON2.RBPU = 0; // Habilitar pullup interno
     WPUB = 0b00001111;
     TRISB = 0b00001111; // Definindo os ports de entrada e saida
     
     config_global_interruption();

     T0CON = 0b00000000; // CONFIGURAR O PRESCALER
     INTCON2.TMR0IP = 1;
     INTCON.TMR0IE = 1;
     INTCON.TMR0IF = 0;

     while (1) {
           LATB = v[index % 4];
           switch (PORTB) {
                  case B1:
                       timerl = 0x;
                       timerh = 0x;
                       T0CON.TMRON = 1;
                       break;
                  case B2:
                       timerl = 0x;
                       timerh = 0x;
                       T0CON.TMRON = 1;
                       break;
                  case B3:
                       timerl = 0x;
                       timerh = 0x;
                       T0CON.TMRON = 1;
                       break;
                  case B4:
                       timerl = 0x;
                       timerh = 0x;
                       T0CON.TMRON = 1;
                       break;
                  case B5:
                       timerl = 0x;
                       timerh = 0x;
                       T0CON.TMRON = 1;
                       break;
                  case B6:
                       timerl = 0x;
                       timerh = 0x;
                       T0CON.TMRON = 1;
                       break;
                  case B7:
                       timerl = 0x;
                       timerh = 0x;
                       T0CON.TMRON = 1;
                       break;
                  case B8:
                       timerl = 0x;
                       timerh = 0x;
                       T0CON.TMRON = 1;
                       break;
                  default:
                       T0CON.TMRON = 0; // Desliga o timer0.
                       break;
           }
           index++;
     }
}