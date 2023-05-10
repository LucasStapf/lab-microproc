
#define SEVEN_SEG_DP 0b10000000
#define SEVEN_SEG_0 0b10111111
#define SEVEN_SEG_1 0b00000110
#define SEVEN_SEG_2 0b11011011
#define SEVEN_SEG_3 0b01001111
#define SEVEN_SEG_4 0b11100110
#define SEVEN_SEG_5 0b01101101
#define SEVEN_SEG_6 0b11111101
#define SEVEN_SEG_7 0b00000111
#define SEVEN_SEG_8 0b11111111
#define SEVEN_SEG_9 0b01100111

unsigned short dig = 0;
const int v[] = {SEVEN_SEG_0, SEVEN_SEG_1, SEVEN_SEG_2, SEVEN_SEG_3, SEVEN_SEG_4, SEVEN_SEG_5, SEVEN_SEG_6, SEVEN_SEG_7, SEVEN_SEG_8, SEVEN_SEG_9};
bit print, freq;


void print_7seg() {
    latd = v[dig % 10];
    dig++;
}

void interrupt_high() iv 0x0008 ics ICS_AUTO {
    if (INTCON.TMR0IF == 1) {
        INTCON.TMR0IF = 0;
        TMR0L = 0xDC;
        TMR0H = 0x0B;
        print = 1;
    }
}

void ConfigInterrupt_Global() {
  INTCON.GIEH = 1;   //Chave Geral, Habilita o vetor de alta prioridade de interrupção
  INTCON.GIEL = 1;   //Habilita o vetor de baixa prioridade (obs: não é chave geral)
  RCON.IPEN = 1; //0 -> (default) herança da família PIC16F, onde existe apenas
                            //um nível de prioridade de interrupção
                     //1 -> dois (2) níveis de prioridade de interrupção encontrado no PIC18
}

void main() {

    anselb = 0; // Porta B como digital
    anseld = 0; // Porta D como digital
    ansela = 0; // Porta A como digital

    trisb = 1; // Porta B como entrada
    trisd = 0; // Porta D como saida
    trisa = 0; // Porta A como saida

    lata = 0b00000001;
    freq = 1;   // 0 : 0.25s | 1: 1s
    print = 0;
    
    ConfigInterrupt_Global();
    
    T0CON = 0b00000100;
    
    TMR0L = 0xDC;
    TMR0H = 0x0B;
    INTCON.TMR0IF = 0;
    INTCON2.TMR0IP = 1;
    INTCON.TMR0IE = 1;
    T0CON.TMR0ON = 1;

    while (1) {

        if (print) {
           print = 0;
           print_7seg();
        }

        if (portb.rb0 == 0) { // pull up
            if (freq) {
                T0CON = 0b10000010; // 1:8
            } else {
                T0CON = 0b10000100; // 1:32
            }
            freq = ~freq;
        }
    }
}
