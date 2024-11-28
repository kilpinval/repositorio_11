#INCLUDE <16f887.h>
#device adc=10
//#USE DELAY(CLOCK=4000000) // Reloj interno 4MHz
#use delay(clock=4000000,crystal)//Crystal Externo 4MHz
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,NOPUT,NOLVP
#INCLUDE <LCD.C>

#BYTE PORTA= 5
#BYTE PORTD= 8

long bits;     //Variable almacena los bits
float tem;     //Almacena la temperatura

void main()
{
   set_tris_a(0b00000001);          //Pongo el RA0 como entrada
   set_tris_d(0);                   //Pongo el PuertoD como Salida
   setup_adc_ports(all_analog);     //Pongo todo el puerto a analogo
   setup_adc(adc_clock_internal);   //Selecciono reloj interno para conversion
   lcd_init();                      //Inicializo el LCD
   lcd_putc("\f");                  //Borro el LCD
   
   while(1)
   {
       set_adc_channel(0);          //Selecciono el canal 0 (RA0)
       delay_ms(1);                 //llamo retardo de 1 ms
       bits=read_adc();             //Guarde el dato del LM en tempe
       
       tem=bits*0.4882;              //Conversion de bits a temperatura
       lcd_gotoxy(1,1);             //Ubiquese en la posicion 1,1
       lcd_putc("LA TEMPERATURA");
       lcd_gotoxy(2,2);             //Ubiquese en la posicion 2,2
       printf(lcd_putc,"ES C= %f    ",tem);  //Muestra el valor numerico de la conversionconversion
       delay_ms(1000);  
   }
}
