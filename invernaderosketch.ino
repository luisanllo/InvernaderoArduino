/***INVERNADERO***/


/*LIBRERIAS*/
#include "DHT.h"

/* Objetos */
int regadio = (11);         //relay 1  
int Estufa = (88);         //relay 2
int Frio = (77);            //relay 3
int Humi = (26);            //relay 4
int Deshumi = (55);         //relay 5
int Iluminacion = (44);     //relay 6 


/*Sensores*/
int sensorsuelo = A0;
  
  
#define DHTPIN 2        // pin 
#define DHTTYPE DHT11   // Tipo de sensor DHT 11
                        // Conectar pin 1 (izquierda) a +5V
                        // Connectar pin 2 del sensor a donde el DHTPIN esta
                        // Connectar pin 4 (derecha) del ensor a GROUND
                        // Connecta una resistencia de 10K  desde pin 2 (data) al pin 1 (power) del sensor
int sensortemp = A1;
int sensorhum =  A2;

/* Variables */
int tiemporiego = 10000; //tiempo que riega el sistema (intervalo) esta a 10s ahora
int pinLDR = 1;        //Pin para la LDR (1 analog)
int valorLDR = 0;       //Aquí almacenamos los datos recogidos de los LDR
int LUZ = 100;
int SATURACION = 60;   //Saturacion maxima del aire antes de deshumificar  (Con esta configracion mantenemos siempe la humedad entre el 50 y el 60%)
int SEQUIA = 50;        //Saturacion mínima de humedad que permitimos al aire
int CALOR = 40;         // Definimos el rango de temperatura en la que se mantendra el invernadero
int FRIO = 18;          // En esta configuracion se mueve entre 40 y 18º
int TEMPOPTIMA = 25 ;   //Establecemos la temperatura ideal
int HUMOPTIMA = 55 ;   //HUmedad ideal

DHT dht(DHTPIN, DHTTYPE);


//VARIABLES INTERFAZ DE USUARIO 2 BOTONES         
long previousMillis = 0;        
long interval = 2000;     // Intervalo de transminsion de datos por el puerto serial

 const int buttonPin1 = 2;     // the number of the pushbutton1 pin
const int buttonPin2 = 3;      // the number of the pushbutton2 pin
const int ledPin1 =  12;      // the number of the LED1 pin
const int ledPin2 =  13;       // the number of the LED2 pin
// variables will change:
int buttonState1 = 0; // variable for reading the pushbutton2 status
int buttonState2 = 0; // variable for reading the pushbutton2 status
int clima = 1;        //var del clima que cambia entre uno o dos

void setup() {
 
 
  pinMode(Iluminacion, OUTPUT);    //Relay 1 como salida
  pinMode(Estufa, OUTPUT);          //Relay 2 como salida
  pinMode(Frio, OUTPUT);            //Relay 3 como salida
  pinMode(Humi, OUTPUT);            //Relay 4 como salida
  pinMode(Deshumi, OUTPUT);         //Relay 5 como salida

  
  //BOTONES Y LEDS DEL CLIMA
   pinMode(ledPin1, OUTPUT);      
   pinMode(ledPin2, OUTPUT); 
   pinMode(buttonPin1, INPUT);
   pinMode(buttonPin2, INPUT);    
 


  Serial.begin(9600);               // abrimos salida con el monitor serial
  
  analogReference(EXTERNAL);        //Le decimos que vamos a usar una referencia externa
  pinMode (sensorsuelo , INPUT );        //Sensor de humedad del suelo como entrada
  

}

void loop() {
  
  
  unsigned long currentMillis = millis(); // Tiempo para realizar intervalo del los ciclos, ni caso
  
  
  //Condiciones iniciales 
  
  
   //High y low dependiendo del tipo de relay
  digitalWrite (Estufa ,HIGH);
  digitalWrite (Frio ,HIGH);
  digitalWrite (Humi ,HIGH);
  digitalWrite (Deshumi ,HIGH);
  digitalWrite (Iluminacion ,HIGH);
   digitalWrite (regadio ,HIGH);
 
 
 
 
 
 
 
 
  //Iluminacion por LDR
  valorLDR = analogRead(pinLDR)   ;                   //Guardamos el valor leido en una variable
  if(valorLDR<LUZ) digitalWrite(Iluminacion, LOW);   // Si el valor de la resistencia es menor al deseado (#DEFINE) encendemos la iluminacion
  else digitalWrite(Iluminacion, HIGH);                  // Si la resistencia aumenta apagamos la iluminacion
  
  Serial.print("Valor LDR: ");                          
  Serial.println(valorLDR);                  //Imprime el valor del LDR
  
  
  
  // Sensor Humedad Del Suelo, aire y temperatura
  
  int Hsuelo = analogRead(sensorsuelo);
  int Temp =  analogRead(sensortemp);
  int Hum =   analogRead(sensorhum);
  
  
              if ( Hsuelo < 300 );                   // si humedad menor de 300 
              {                                      //mientras la humedad se mantenga por debajo de 300, el riego efectuara intervalos de riego hasta que la humedad llegue a 500
                 digitalWrite ( regadio , LOW);
              }
               
               if (Hsuelo > 500);                    //si el suelo esta húmedo
               {
                 digitalWrite ( regadio , HIGH);
                            
                            
                            if ( Hum < SEQUIA );
                             {
                               digitalWrite ( Humi , LOW);       //Si la humedad es menor al 50% encendemos el humidificador
                               
                               }
                              
                            if ( Hum > (HUMOPTIMA) );              
                             {                                   //Si la humedad es mayor al 55% apagamos el dehumidificador
                               digitalWrite ( Humi , HIGH);         
                               
                               }
                               
                               
                            if ( Hum > SATURACION); 
                               {
                                digitalWrite (Deshumi , LOW);   //Si la humedad es mayor al 60% encendemos el deshumidificador
                                
                                }
                                
                            if ( Hum < (HUMOPTIMA)); 
                               {
                                digitalWrite (Deshumi , HIGH);   //Si la humedad es menor al 55% apagamos el deshumidificador
                                
                                }
                                
                                
                             if ( Temp < FRIO ); //si las condiciones son de frio encender fuente de calor
                                {  
                                  digitalWrite ( Estufa , LOW );
                                  
                                  }
                                
                              if ( Temp > TEMPOPTIMA ); //si la temperatura ya es correcta apagamos la fuente de calor
                                {  
                                  digitalWrite ( Estufa , HIGH );
                               
                                  }  
                                  
                                  
                              if ( Temp > CALOR ); //si hace calor encender fuente de frio
                                {  
                                  digitalWrite ( Frio , LOW );

                                  }
                                  
                               if ( Temp < TEMPOPTIMA ); //si la temperatura ya es correcta apagamos la fuente de frio
                                {  
                                  digitalWrite ( Frio , HIGH );

                                  }
                            
  
 
  }
 

                                  
                                  
                                
                                  
                                
                              
                            
                              
                            
                            
                            
                        
                 
               
               
               
               
}
