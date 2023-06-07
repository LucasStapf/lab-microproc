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
#define RESOLUCAO_T 0.001

unsigned adc_value;
char buff_v[12], buff_t[12];
float resultado;

void main(){
  ANSELA.f1 = 1;
  ANSELB = 0;                        // Configure AN pins as digital I/O
  ANSELE.f2 = 1;
  
  TRISA.f1  = 1;              // PORTA is input
  TRISE.f2  = 1;              // PORTE is input
  TRISB = 0;

  Lcd_Init();                        // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);


  while(1){
delay_ms(100);
TRISA.f1  = 1;
          //Multimetro
          ADC_Init_Advanced(_ADC_INTERNAL_REF);
          adc_value = ADC_Get_Sample(1);    // read analog value from ADC module channel 1
          resultado = adc_value * RESOLUCAO_V;
          sprintf(buff_v, "AN1 = %.2fV", resultado);
          Lcd_Out(1,1,buff_v);

delay_ms(100);
TRISA.f1  = 0;
          //Temperatura
          ADC_Init_Advanced(_ADC_INTERNAL_FVRH1 | _ADC_INTERNAL_VREFL);
          adc_value = ADC_Get_Sample(7);    // read analog value from ADC module channel 1
          resultado = (adc_value * RESOLUCAO_T)/0.01;
          sprintf(buff_t, "RE1 = %.1fC", resultado);
          Lcd_Out(2,1,buff_t);
  }
}
