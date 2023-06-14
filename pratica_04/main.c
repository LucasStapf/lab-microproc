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

unsigned short duty;
char buff[12];

void main() {
       anselb = 0;
       anseld = 0; // Porta B como digital
       trisd = 1; // Porta B como entrada
       
       Lcd_Init();                 // Initialize LCD
       Lcd_Cmd(_LCD_CLEAR);
       Lcd_Cmd(_LCD_CURSOR_OFF);

       duty = 0;
       PWM1_Init(5000);                    // Initialize PWM1 module at 5KHz
       while(1){
                if(portd.rd0 == 0){
                      duty = 0;
                }else if(portd.rd1 == 0){
                      duty = 64;
                }else if(portd.rd2 == 0){
                      duty = 127;
                }else if(portd.rd3 == 0){
                      duty = 192;
                }else if(portd.rd4 == 0){
                      duty = 255;
                }
                
                PWM1_Set_Duty(duty);
                
                sprintf(buff, "PWM = %d", duty);
                Lcd_Out(1,1,buff);

             //
       }
       
}
