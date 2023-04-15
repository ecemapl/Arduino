#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/* Para Arduino micro
https://store.arduino.cc/products/arduino-micro */
const int inputPin = 11;
LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int valorPin = 0; // estado actual del pulsador
int valorPinAnterior = 0; // estado anterior del pulsador
int estado = 0; //(0 es reloj a cero, 1 es reloj corriendo, 2 es reloj en pausa)


// Variables para los cálculos internos del cronómetro
int horas = 0;
int minutos = 0;
int segundos = 0;
int decimas = 0;
long milisegundos = 0;

void setup()
{
  pinMode(inputPin, INPUT);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{
  valorPin = digitalRead(inputPin); //lectura del pulsador
  //Serial.println(valorPin);

  if ((valorPin == 1) && (valorPinAnterior == 0)) { // si el pin se pulsa cambia el estado 
    if (estado == 0) { 
      estado = 1; 
      //Serial.println("reloj corriendo"); 
    }
    else if (estado == 1) { 
      estado = 2; 
      //Serial.println("reloj en pausa"); 
    }
    else { 
      estado = 0; 
      //Serial.println("reloj a cero"); 
    }
    
    valorPinAnterior = 1; 

  }
  else if (valorPin == 0) {
    valorPinAnterior = 0;
  }

  if (estado == 0) { 
    
    horas = 0;
    minutos = 0;
    segundos = 0;
    decimas = 0;

    // Mostramos el tiempo a través del LCD
    lcd.setCursor(0,0);
    if(horas < 10)
    {
      lcd.print("0");
    }
    lcd.print(horas);
    lcd.print(":");
    lcd.setCursor(3,0);
    if(minutos < 10)
    {
      lcd.print("0");
    }
    lcd.print(minutos);
    lcd.print(":");
    lcd.setCursor(6,0);
    if(segundos < 10)
    {
      lcd.print("0");
    }
    lcd.print(segundos);
    lcd.print("(");
    lcd.setCursor(9,0);
    lcd.print(decimas);
    lcd.print(")");
  }
  else if (estado == 1) {
    // Se cuentan los milisegundos transcurridos
    milisegundos = millis();
   
    // Si el tiempo transcurrido es mayor a una décima de segundo
    if(milisegundos % 100 == 0)
    {
      decimas++;
      // Si han pasado 10 décimas de segundo se cuenta un segundo
      if(decimas == 10)
      {
        decimas = 0;
        segundos++;
      }
      // Si han pasado 60 segundos se cuenta un minuto
      if(segundos == 60)
      {
        segundos = 0;
        minutos++;
      }
      // Si han pasado 60 minutos se cuenta una hora
      if(minutos == 60)
      {
        minutos = 0;
        horas++;
      }
     
      // Mostramos el tiempo a través del LCD
      lcd.setCursor(0,0);
      if(horas < 10)
      {
        lcd.print("0");
      }
      lcd.print(horas);
      lcd.print(":");
      lcd.setCursor(3,0);
      if(minutos < 10)
      {
        lcd.print("0");
      }
      lcd.print(minutos);
      lcd.print(":");
      lcd.setCursor(6,0);
      if(segundos < 10)
      {
        lcd.print("0");
      }
      lcd.print(segundos);
      lcd.print("(");
      lcd.setCursor(9,0);
      lcd.print(decimas);
      lcd.print(")");
    }
  }
  else { // reloj en pausa
    // Mostramos el tiempo a través del LCD
    lcd.setCursor(0,0);
    if(horas < 10)
    {
      lcd.print("0");
    }
    lcd.print(horas);
    lcd.print(":");
    lcd.setCursor(3,0);
    if(minutos < 10)
    {
      lcd.print("0");
    }
    lcd.print(minutos);
    lcd.print(":");
    lcd.setCursor(6,0);
    if(segundos < 10)
    {
      lcd.print("0");
    }
    lcd.print(segundos);
    lcd.print("(");
    lcd.setCursor(9,0);
    lcd.print(decimas);
    lcd.print(")");
  }  
}
