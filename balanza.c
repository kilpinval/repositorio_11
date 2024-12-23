/************************************************************************************** 
*   Balanza Digital con PIC + HX711 + Celda de Carga de 5kg                           * 
*                                                                                     *
*   by Sergio Andres Castaño Giraldo                                                  *
*   website: https://controlautomaticoeducacion.com/                                  *
*   YouTube Chanel: https://www.youtube.com/channel/UCdzSnI03LpBI_8gXJseIDuw          *
**************************************************************************************/ 

#INCLUDE <18f4550.h>
#USE DELAY(CLOCK=20000000,crystal)
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,NOPUT,NOLVP
#use i2c(Master,Fast=100000, sda=PIN_B0, scl=PIN_B1)  
#include "i2c_Flex_LCD.c"  
#include "hx711.c"  
#define MODO       PIN_B4
#define TARA       PIN_B5
float escala= 0;
float peso_conocido[4] = {550,1000,3000,5000};


//Escribir en la EEPROM
WRITE_FLOAT_EEPROM(long int n, float data) { 
   int i;

   for (i = 0; i < 4; i++) 
      write_eeprom(i + n, *((int8*)&data + i) ) ; 
}
//Leer en la EEPROM
float READ_FLOAT_EEPROM(long int n) { 
   int i; 
   float data;

   for (i = 0; i < 4; i++) 
      *((int8*)&data + i) = read_eeprom(i + n);

   return(data); 
}

//Funcion de calibracion y ajuste
void calibration(){
  
  int i = 0,cal=1;
  int32 adc_lecture;
  
  // Escribimos el Mensaje en el LCD
  lcd_gotoxy(2, 1);        
  printf(lcd_putc, "Calibracion de");
  lcd_gotoxy(4, 2);        
  printf(lcd_putc, "Balanza");
  delay_ms(1500);
  tare(10);  //El peso actual es considerado Tara.
  
  lcd_clear();

  //Inicia el proceso de ajuste y calibraciÃ³n
  while(cal == 1){
    
    lcd_gotoxy(1, 1);        
    printf(lcd_putc, "Peso Conocido:");
    lcd_gotoxy(1, 2);
    printf(lcd_putc, "%4.0f g             ",peso_conocido[i]);
    
    //Busca el peso conocido con el boton tara
    if(input(TARA) == 1){  
      delay_ms(200); // Anti-debounde
      i =(i>2) ? 0:i+1; //if-else en una linea
    }

    //Selecciona el peso conocido con el boton modo
    if(input(MODO)){
      delay_ms(200);
      lcd_clear();
      lcd_gotoxy(1, 1);        
      printf(lcd_putc, "Ponga el Peso");
      lcd_gotoxy(1, 2);        
      printf(lcd_putc, "y espere ...");
      
      delay_ms(3000);

      //Lee el valor del HX711
      adc_lecture = get_value(10);

      //Calcula la escala con el valor leido dividido el peso conocido
      escala = adc_lecture / peso_conocido[i];

      //Guarda la escala en la EEPROM
      WRITE_FLOAT_EEPROM(0, escala);
      
      delay_ms(100);
      cal = 0; //Cambia la bandera para salir del while
      lcd_clear();
    }
    
  }
}



void main() {  
     
     float peso=0,factor = 1;
     int unidad = 1;
     lcd_init(0x4E,16,2);
     lcd_backlight_led(ON); //Enciende la luz de Fondo
     init_hx(128);
     lcd_clear();
     
     //Lee el valor de la escala en la EEPROM
     escala = READ_FLOAT_EEPROM(0);  
      
     //Pregunta si se entra al modo de ajuste y calibración
     if( input(MODO) == 1 && input(TARA) == 1)
          calibration();
          
     lcd_gotoxy(1, 1);        
     printf(lcd_putc, "Retire el Peso");
     lcd_gotoxy(1, 2);        
     printf(lcd_putc, "y espere ...");
     set_scale(escala);
     tare(10);
     delay_ms(2000);
     lcd_clear();
     
     lcd_gotoxy(1, 1);        
     printf(lcd_putc, "Listo....");
     delay_ms(3000);
     lcd_clear();
     tare(10);
     while(1){
          
          peso = get_units(10); //Lee el peso y hace un promedio de 10 muestras
          lcd_gotoxy(3, 1);        
          printf(lcd_putc, "Balanza CAE"); 
           
          switch (unidad) {
               case 1:        
                    factor = 1.0;
                    lcd_gotoxy(1, 2);        
                    printf(lcd_putc, "Peso: %4.1f g       ",peso/factor); 
                    break;
               case 2:
                    factor = 1000.0;
                    lcd_gotoxy(1, 2);        
                    printf(lcd_putc, "Peso: %4.2f Kg       ",peso/factor); 
                    break;
               case 3:
                    factor = 28.35;
                    lcd_gotoxy(1, 2);        
                    printf(lcd_putc, "Peso: %4.2f oz       ",peso/factor); 
                    break;
          }
          if(input(TARA)==1){
               delay_ms(200);
               tare(10);
          }
          if(input(MODO)==1){
               delay_ms(200);
               unidad = (unidad>2)? 1:unidad+1;
          }
          delay_ms(100);
          
     }

}
