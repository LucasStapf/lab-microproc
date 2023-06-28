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

/*unsigned short*/int count_me, count_ma;
char buff_1[17], buff_2[17];
short aceita; //0 - madeira 1 - metal

void main() {
     ANSELB = 0; // LCD
     TRISB = 0b00000000; // Porta B
     
     Lcd_Init();                 // Initialize LCD
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     
     ANSELD = 0; // Porta D como digital
     TRISD = 0b00000011; // Porta D como entrada
       
     aceita = -1;
     count_me = 0;
     count_ma = 0;
     
     sprintf(buff_1, "Aceita: ");
     sprintf(buff_2, "MA: %2d  ME: %2d", count_ma, count_me);
     
     while(1){
              Lcd_Out(1,1,buff_1);
              Lcd_Out(2,1,buff_2);
              
              if(portD.f0 == 0){
                    aceita = 0;
                    sprintf(buff_1, "Aceita: MADEIRA");
              }else if(portD.f1 == 0){
                    aceita = 1;
                    sprintf(buff_1, "Aceita: METAL  ");
              }
              
     }
}
