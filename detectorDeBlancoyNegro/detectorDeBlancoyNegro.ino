




/* Programa para una sola línea*/
int infraPin1 = 10;    // pin del infrarrojos utilizado como entrada digital en el lado izquierdo(#1).
int infraPin2 = 11;    // pin del infrarrojos utilizado como entrada digital en el lado derecho(#2).
int valorInfra1 = 0;  // Valor inicial de la lectura digital del infrarrojos #1.
int valorInfra2 = 0;  // Valor inicial de la lectura digital del infrarrojos #2.
int OUTPUT4 = 4;    // Output4 conectada al pin 4.
int OUTPUT3 = 3;    // Ouput3 conectada al pin 3.
int OUTPUT2 = 6;    // Output3 conectada al pin 6.
int OUTPUT1 = 7;    // Output4 conectada al pin 7.
int PWM_Derecho = 8;
int PWM_Izquierdo = 9;
const int sensorPin = A0;    // seleccionar la entrada para el sensor
int sensorValue;     // variable que almacena el valor raw (0 a 1023)
int LED = 12; //Alarma parpadente

void setup() 

{ 
  Serial.begin(9600); // Comenzamos comunicacion serial.
  pinMode(infraPin1, INPUT);     // Inicializa el pin 1 como entrada digital.
  pinMode(infraPin2, INPUT);     // Inicializa el pin 2 como entrada digital.
  pinMode (OUTPUT1, OUTPUT);     // Inicializa el pin 7  como entrada digital.
  pinMode (OUTPUT2, OUTPUT);     // Inicializa el pin 6 como entrada digital.
  pinMode (OUTPUT3, OUTPUT);     // Inicializa el pin 3 como entrada digital.
  pinMode (OUTPUT4, OUTPUT);     // Inicializa el pin 4 como entrada digital.  
  pinMode(PWM_Derecho, OUTPUT);
  pinMode(PWM_Izquierdo, OUTPUT);
  pinMode(LED, OUTPUT);
  } 

void loop() 
{ 
   //mandar mensaje a puerto serie en función del valor leido
   //Serial.println(sensorValue);
  if(valorInfra1==0)   // Si la lectura del infrarrojos#1 es 0, entonces se cumplira una de las siguientes condiciones:
  {
  if(valorInfra2==1)  // Si la lectura del infrarrojos#2 es 0, es decir los dos sensores estan sobre la linea negra, entonces los dos motores avanzaran en linea recta.
  {
  //Programación para movimiento de reversa
  digitalWrite(OUTPUT1,1);
  digitalWrite(OUTPUT2,0);
  digitalWrite(OUTPUT3,0);
  digitalWrite(OUTPUT4,1); 
  analogWrite(PWM_Derecho,175);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,120);//Velocidad motor izquierdo 200
  Serial.println("Adelante");

  }
  else // Si la lectura del infrarrojos#2 es 1, el sensor#1 esta sobre la linea negra y el sensor#2 esta fuera de la linea negra, entonces solo una rueda gira y esto causara el giro.
  {
  //Programación para giro a la izquierda
  digitalWrite(OUTPUT1,0);
  digitalWrite(OUTPUT2,0);
  digitalWrite(OUTPUT3,0);
  digitalWrite(OUTPUT4,1); 
  analogWrite(PWM_Derecho,175);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,75);//Velocidad motor izquierdo 200
  Serial.println("Rutina");
  }
  }
  else // Si la lectura del infrarrojos#1 no es 0, sera 1, se daran las siguientes posibilidades:
  {if(valorInfra2==0)  // Como el sensor#1 esta fuera de la linea negra y el sensor#2 esta sobre la linea negra, entonces solo una rueda gira y esto causara el giro.
  /*{
  //Programación para giro a la derecha
  digitalWrite(OUTPUT3,0);
  digitalWrite(OUTPUT4,0);
  digitalWrite(OUTPUT1,1);
  digitalWrite(OUTPUT2,0);
  analogWrite(PWM_Derecho,175);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,200);//Velocidad motor izquierdo 200
  Serial.println("Derecha");
  }*/
 // else
 { // si ambos sensores dan lectura 1, los dos estan fuera de la linea negra, para que vuelva a su trayectoria tiene que retroceder.
  //Programación para movimiento derecho
  digitalWrite(OUTPUT1,0);
  digitalWrite(OUTPUT2,1);
  digitalWrite(OUTPUT3,1);
  digitalWrite(OUTPUT4,0);
  analogWrite(PWM_Derecho,130);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,200);//Velocidad motor izquierdo 200
  Serial.println("Reversa");
  }
  }
}
