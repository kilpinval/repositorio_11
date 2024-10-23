#include <16F876>
#fuses XT,NOWDT,NOPROTECT,NOLVP
#use delay(clock=4000000)
#use standard_io(a)

#include <lcd.c>
#include <kbd.c>
#include <stdlib.h>
#rom 0x2100={`7)´,´2´,´3´}  //Posicion 0,1 y 2 de la Eepromcon los datos...
                           //7,2, y 3 respectivamente

void main(){
  char k;
  int i;
  char data[3], clave[3]; //Matrices para guardar clave y datos
  lcd_init();
  kbd_init;
  port_b_pullups(TRUE);
  while(TRUE){
    i=0;    //Posicion de la matriz
    printf(lcd_putc,"\fpulsar tecla 1\n");  //Para primer dato
    while(i<=2){
      k=kbbd_getc();      //Lee el teclado
      if((k!=0)    //Si se ha pulsado alguna tecla
        {data[i]=k; //Seguarda en al posicion correspondiente  
          i++;
          printf(lcd_putc,"\fpulsar tecla %u\n",i+1); //Sigue dato
        }
        
    }
    for (i=0;i<=2;i++){   //Pasa dato}s de eeprom  a la matriz clave
      clave[i]=read_eeprom(i);
      
    }
    if((data[0]==clave[0])&&(data[1]==clave[1]&&(data[2]==clave[2])){
      printf(lcd_putc,"\fpuerta Abierta");  //Compara los datos y la clave
      output_high(PIN_A0);
      delay_ms(500),
      output_low(PIN_A0);}
    else printf(lcd_putc,"\fPuerta Cerrada");   //Clave erronea
    delay_ms(1000),
      }
    
      
    
  }
}
