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
char buff[17];
unsigned int count;
char buff_rot[20];

void ConfigInterrupt_Global() {
       INTCON.GIEH = 1;
       INTCON.GIEL = 1;
       RCON.IPEN = 1;
}

void main() {

       ANSELB = 0;
       ANSELD = 0; // Porta D como digital
       TRISD = 0xFF; // Porta D como entrada
       
       ConfigInterrupt_Global();
       
       T3CON = 0b10000100;
       T3CON.TMR3ON = 1;
       
       
       Lcd_Init();                 // Initialize LCD
       Lcd_Cmd(_LCD_CLEAR);
       Lcd_Cmd(_LCD_CURSOR_OFF);

       count = 0;
       duty = 0;
       sprintf(buff, "PWM = 0%%   ");
       PWM1_Init(10000);                    // Initialize PWM2 module at 5KHz
       PWM1_Start();
       while(1){
                if (portD.f0 == 0) {
                      duty = 0;
                      sprintf(buff, "PWM = 0%%   ");
                } else if(portD.f1 == 0){
                      duty = 64;
                      sprintf(buff, "PWM = 25%%  ");
                } else if(portD.f2 == 0) {
                      duty = 127;
                      sprintf(buff, "PWM = 50%%  ");
                } else if(portD.f3 == 0) {
                      duty = 192;
                      sprintf(buff, "PWM = 75%%  ");
                } else if(portD.f4 == 0) {
                      duty = 255;
                      sprintf(buff, "PWM = 100%% ");
                }
                
                count = TMR3L;
                sprintf(buff_rot, "ROT: %d", count);
                Lcd_Out(2,1,buff_rot);
                PWM1_Set_Duty(duty);
                Lcd_Out(1,1,buff);
       }
       
}
