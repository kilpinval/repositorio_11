#nclude <16f876.h>
#fuses XT,NOWDT,NOPROTECT,NOLVP
#USE DELAY (CLOCK=4000000)
#INCLUDE <kbd.c>
#USE STANDARD_IO (a)

VOID MAIN()
{
  CHAR K,KANT=´0´;    //k valor de teclado, k valor anterior de teclado
  char PWMH=0,PWML=0;  //Semiperiodo alto y bajo
  kbd_init();
  PORT_B_PULLUPS(TRUE);

WHILE(1){     //Bucle infinito (siempre consulta el teclado)
  k=kbd_getc);    //Lee en ASSII el valor de la tecla pulsada
  if (k==´\0´) k=kant;        //Si no se pulsa tecla (\0) se usa el valor anterior
  if ((k==´*´) || (k==´#´)) k=´0´;    //Si se pulsa * o # se asigna un valor cero
  kant=k;      //Se guarda tecla pulsada
  k=k-48;      //se convierte de ASSII a valor numerico
  PWMH=K*28;    Proporcion entre valor tecla y semiperiodo Alto.
  PWML=255-PWMH;      //Semiperiodo bajo;
  for(PWMH;PWMH>0;PWMH--){    //Obtencion de salida a nivel alto
    OUTPUT_HIGH(PIN_A0);
  }
  for(PWML;PWML>0;PWMP--){    //Obtencion de salida a nivel bajo
    OUTPUT_LOW(PIN_A0);
    
  }
  
}
}
