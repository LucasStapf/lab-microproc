// LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
// End LCD module connections


int count_me, count_ma;
char buff_1[17], buff_2[17];
short material; //0 - madeira 1 - metal
short opt, cap, ind;

void main() {
     
     ANSELB = 0; // LCD
    
     Lcd_Init();                 // Initialize LCD
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     
     ANSELD = 0; // Porta D como digital
     TRISD = 0xFF; // Porta D como entrada

     ANSELC = 0;
     TRISC = 0b00000111;
     
     material = -1;
     count_me = 0;
     count_ma = 0;
     opt = cap = ind = 0;
     
     sprintf(buff_1, "Aceita: ");
     sprintf(buff_2, "MA: %2d  ME: %2d", count_ma, count_me);
     
     LATC.F7 = 0;
     LATC.F6 = 1;
     LATC.F5 = 0;
     LATC.F4 = 1;
                 
     while(1){
              Lcd_Out(1,1,buff_1);
              Lcd_Out(2,1,buff_2);
              
              if(portD.f0 == 0){
                    material = 0;
                    sprintf(buff_1, "Aceita: MADEIRA");
              }
              
              if(portD.f1 == 0){
                    material = 1;
                    sprintf(buff_1, "Aceita: METAL  ");
              }
              
              if (!PORTC.F0) {
                    LATC.F7 = 0;
                    LATC.F6 = 0;
                    Delay_ms(2000);
                    LATC.F7 = 1;
                    LATC.F6 = 0;
                    while (!PORTC.F0);
              }

              if (!PORTC.F2) {
                 ind = 1;
                 while (!PORTC.F2);
              }

              if (!PORTC.F1) {

                 if (ind != material) {
                    Delay_ms(3450);
                    LATC.F5 = 1;
                    LATC.F4 = 0;
                    Delay_ms(1000);
                    LATC.F5 = 0;
                    LATC.F4 = 1;
                 } else {
                    Delay_ms(5500);
                 }

                 LATC.F7 = 0;
                 LATC.F6 = 1;
                 
                 if (ind) {
                    count_me++;
                 } else {
                   count_ma++;
                 }

                 ind = 0;
              }
              
              sprintf(buff_2, "MA: %2d  ME: %2d", count_ma, count_me);
     }
}
