
#define SEVEN_SEG_DP 0b10000000
#define SEVEN_SEG_0 0b00111111
#define SEVEN_SEG_1 0b00000110
#define SEVEN_SEG_2 0b01011011
#define SEVEN_SEG_3 0b01001111
#define SEVEN_SEG_4 0b01100110
#define SEVEN_SEG_5 0b01101101
#define SEVEN_SEG_6 0b01111101
#define SEVEN_SEG_7 0b00000111
#define SEVEN_SEG_8 0b01111111
#define SEVEN_SEG_9 0b01100111

unsigned short dig = 0;
const int v[] = {SEVEN_SEG_0, SEVEN_SEG_1, SEVEN_SEG_2, SEVEN_SEG_3, SEVEN_SEG_4, SEVEN_SEG_5, SEVEN_SEG_6, SEVEN_SEG_7, SEVEN_SEG_8, SEVEN_SEG_9};


void reload_tmr0(int h, int l) {
    TMR0L = l;
    TMR0H = h;
    INTCON.TMR0IF = 0;
}

void print_7seg() {
    latd = v[dig % 10];
    dig++;
}

void interrupt_high() iv 0x0008 ics ICS_AUTO {
    if (INTCON.TMR0IF) {
        reload_tmr0(0x0B, 0xDC);
        print_7seg();
    }
}

void main() {

    anselb = 0; // Porta B como digital
    anseld = 0; // Porta D como digital
    ansela = 0; // Porta A como digital

    trisb = 1; // Porta B como entrada
    trisd = 0; // Porta D como saida
    trisa = 0; // Porta A como saida
    
    lata = 0b00000001;

    bit freqFlag = 0; // 0 : 0.25s | 1: 1s

    reload_tmr0(0x0B, 0xDC); // valores pro H0 L0 0xBDC
    T0CON.TMR0ON = 1;

    while (1) {
        if (portb == 0) { // pull up
            if (freqFlag) {
                T0CON = 0b00000010; // 1:8
            } else {
                T0CON = 0b00000100; // 1:32
            }
            freqFlag = ~freqFlag;
        }
    }
}
