#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>
#include <SoftwareSerial.h>
 
 
SoftwareSerial bt(0,1);
int motorA1 = 4;  //IN4//output1
int motorA2 = 3;  //IN3//output1
int motorB1 = 6;  //IN9//output
int motorB2 = 7;  //IN10//output4
int enableA = 8;  //
int enableB = 9;
const int sensorPin = A0;
int sensorValue;
int infraPin1 = 10;
int infraPin2 = 11;
int valorInfra2 = 0;
int valorInfra1 = 0;


// Step 1 -  Instantiating an object library
Fuzzy* fuzzy = new Fuzzy();
 
void setup(){
 Serial.begin(9600);
 bt.begin(9600);
 pinMode(infraPin1, INPUT);     // Inicializa el pin 10 como entrada digital.
  pinMode(infraPin2, INPUT);     // Inicializa el pin 11 como entrada digital.
  //pinMode (OUTPUT1, OUTPUT);     // Inicializa el pin 7  como entrada digital.
  //pinMode (OUTPUT2, OUTPUT);     // Inicializa el pin 6 como entrada digital.
  //pinMode (OUTPUT3, OUTPUT);     // Inicializa el pin 3 como entrada digital.
  //pinMode (OUTPUT4, OUTPUT);     // Inicializa el pin 4 como entrada digital.  
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
 
 // Step 2 - Creating a FuzzyInput distance
 FuzzyInput* indicacion = new FuzzyInput(1);// With its ID in param
 
 //creating FuzzySet
 FuzzySet* muyFrio = new FuzzySet(0, 10, 10, 15);
 indicacion->addFuzzySet(muyFrio);
 FuzzySet* frio = new FuzzySet(15, 20, 20, 25);
 indicacion->addFuzzySet(frio);
 FuzzySet* caliente = new FuzzySet(25, 30, 30, 35);
 indicacion->addFuzzySet(caliente);
 FuzzySet* muyCaliente = new FuzzySet(35, 40, 40, 45);
 indicacion->addFuzzySet(muyCaliente);
 
 fuzzy->addFuzzyInput(indicacion);
 
 FuzzyOutput* velocity = new FuzzyOutput(1);
 
 FuzzySet* superSlow = new FuzzySet(0, 10, 10, 20); // Super Slow velocity
 velocity->addFuzzySet(superSlow); // Add FuzzySet slow to velocity
 FuzzySet* slow = new FuzzySet(10, 20, 20, 30);
 velocity->addFuzzySet(slow);
 FuzzySet* average = new FuzzySet(20, 30, 30, 40); // Average velocity
 velocity->addFuzzySet(average); // Add FuzzySet average to velocity
 FuzzySet* fast = new FuzzySet(30, 40, 40, 50); // Fast velocity
 velocity->addFuzzySet(fast); // Add FuzzySet fast to velocity
 
 fuzzy->addFuzzyOutput(velocity); // Add FuzzyOutput to Fuzzy object
 
 //Passo 4 - Assembly the Fuzzy rules
 // FuzzyRule "IF indicacion = muyCaliente THEN velocity = Superslow"
 FuzzyRuleAntecedent* ifIndicacionMuyCaliente = new FuzzyRuleAntecedent(); // Instantiating an Antecedent to expression
 ifIndicacionMuyCaliente->joinSingle(muyCaliente); // Adding corresponding FuzzySet to Antecedent object
 FuzzyRuleConsequent* thenVelocitySuperSlow = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
 thenVelocitySuperSlow->addOutput(superSlow);// Adding corresponding FuzzySet to Consequent object
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifIndicacionMuyCaliente, thenVelocitySuperSlow); // Passing the Antecedent and the Consequent of expression
  
 fuzzy->addFuzzyRule(fuzzyRule01); // Adding FuzzyRule to Fuzzy object
 
 // FuzzyRule "IF indicacion = caliente THEN velocity = slow"
 FuzzyRuleAntecedent* ifIndicacionCaliente = new FuzzyRuleAntecedent(); // Instantiating an Antecedent to expression
 ifIndicacionCaliente->joinSingle(caliente); // Adding corresponding FuzzySet to Antecedent object
 FuzzyRuleConsequent* thenVelocitySlow = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
 thenVelocitySlow->addOutput(slow); // Adding corresponding FuzzySet to Consequent object
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifIndicacionCaliente, thenVelocitySlow); // Passing the Antecedent and the Consequent of expression
  
 fuzzy->addFuzzyRule(fuzzyRule02); // Adding FuzzyRule to Fuzzy object
 
  
 // FuzzyRule "IF indicacion = frio THEN velocity = normal"
 FuzzyRuleAntecedent* ifIndicacionFrio = new FuzzyRuleAntecedent(); // Instantiating an Antecedent to expression
 ifIndicacionFrio->joinSingle(frio); // Adding corresponding FuzzySet to Antecedent object
 FuzzyRuleConsequent* thenVelocityAverage = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
 thenVelocityAverage->addOutput(average); // Adding corresponding FuzzySet to Consequent object
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifIndicacionFrio, thenVelocityAverage); // Passing the Antecedent and the Consequent of expression
  
 fuzzy->addFuzzyRule(fuzzyRule03); // Adding FuzzyRule to Fuzzy object
  
 // FuzzyRule "IF indicacion = muyFrio THEN velocity = fast"
 FuzzyRuleAntecedent* ifIndicacionMuyFrio = new FuzzyRuleAntecedent(); // Instantiating an Antecedent to expression
 ifIndicacionMuyFrio->joinSingle(muyFrio); // Adding corresponding FuzzySet to Antecedent object
 FuzzyRuleConsequent* thenVelocityFast = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
 thenVelocityFast->addOutput(fast);// Adding corresponding FuzzySet to Consequent object
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule04 = new FuzzyRule(4, ifIndicacionMuyFrio, thenVelocityFast); // Passing the Antecedent and the Consequent of expression
  
 fuzzy->addFuzzyRule(fuzzyRule04); // Adding FuzzyRule to Fuzzy object
}

void loop(){
  float output = 0.0;
 if (bt.available() > 0){
   int indication = bt.read(); 
   // Step 5 - Report inputs value, passing its ID and value
   fuzzy->setInput(1, indication); 
   // Step 6 - Exe the fuzzification
   fuzzy->fuzzify(); 
   // Step 7 - Exe the desfuzzyficação for each output, passing its ID
    output = fuzzy->defuzzify(1);
 Serial.println(output);
 }
 blancoNegro();
 if(output==40){
   muyFrio();
 }else if(output==30)
 {
   frio();
   
 }else if(output==20){
   caliente();
 }else if(output==10){
   muyCaliente();
 }
 
 delay(100);
}

void muyFrio()
{
  digitalWrite(motorA1,0);
  digitalWrite(motorA2,0);
  digitalWrite(motorB1,1);
  digitalWrite(motorB2,0);
  analogWrite(enableA,175);//Velocidad motor derecho 1750
  analogWrite(enableB,200);//Velocidad motor izquierdo 200
  Serial.println("Derecha");
}

void frio()
{
  digitalWrite(motorA1,200);
   digitalWrite(motorA2, 200);
   digitalWrite(motorB1, 200);
   digitalWrite(motorB2, 200);
}

void caliente()
{
  analogWrite(enableA, 50);
   analogWrite(enableB, 50);
}

void muyCaliente()
{
  analogWrite(enableA, 25);
  analogWrite(enableB, 25);
}
void blancoNegro() 
{ 
   //mandar mensaje a puerto serie en función del valor leido
   //Serial.println(sensorValue);
  if(valorInfra1==0)   // Si la lectura del infrarrojos#1 es 0, entonces se cumplira una de las siguientes condiciones:
  {
  if(valorInfra2==1)  // Si la lectura del infrarrojos#2 es 0, es decir los dos sensores estan sobre la linea negra, entonces los dos motores avanzaran en linea recta.
  {
  //Programación para movimiento de reversa
  digitalWrite(motorA2,1);
  digitalWrite(motorA1,0);
  digitalWrite(motorB1,0);
  digitalWrite(motorB2,1); 
  analogWrite(enableA,175);//Velocidad motor derecho 200
  analogWrite(enableB,120);//Velocidad motor izquierdo 200
  Serial.println("Adelante");

  }
  else // Si la lectura del infrarrojos#2 es 1, el sensor#1 esta sobre la linea negra y el sensor#2 esta fuera de la linea negra, entonces solo una rueda gira y esto causara el giro.
  {
  //Programación para giro a la izquierda
  digitalWrite(motorA1,0);
  digitalWrite(motorA2,0);
  digitalWrite(motorB1,0);
  digitalWrite(motorB2,1); 
  analogWrite(enableA,175);//Velocidad motor derecho 200
  analogWrite(enableB,75);//Velocidad motor izquierdo 200
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
  digitalWrite(motorA1,0);
  digitalWrite(motorA2,1);
  digitalWrite(motorB1,1);
  digitalWrite(motorB2,0);
  analogWrite(enableA,130);//Velocidad motor derecho 200
  analogWrite(enableB,200);//Velocidad motor izquierdo 200
  Serial.println("Reversa");
  }
  }
}
