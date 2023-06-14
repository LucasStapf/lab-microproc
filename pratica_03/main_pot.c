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

#define RESOLUCAO_V 0.0048876

unsigned adc_value;
char buff_v[12];
float resultado;

void main() {

    ANSELA.f1 = 1;
    ANSELB = 0;                 // Configure AN pins as digital I/O
      
    TRISA.f1  = 1;              // PORTA is input
    TRISB = 0;
    
    Lcd_Init();                 // Initialize LCD
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    ADC_Init();

    while(1) {
        adc_value = ADC_Get_Sample(1);    // read analog value from ADC module channel 1
        resultado = adc_value * RESOLUCAO_V;
        sprintf(buff_v, "AN1 = %.2fV", resultado);
        Lcd_Out(1,1,buff_v);
    }
}