#include <SoftwareSerial.h> 

// Motor A
//#define ENA  4
#define IN1  9
#define IN2  8

// Motor B
//#define ENB  5
#define IN3  7
#define IN4  6

char dato=0;
int atras_prom=0;

SoftwareSerial miBT(10, 11);

void setup() {
  Serial.begin(38400);   // comunicacion de monitor serial a 9600 bps
  Serial.println("Listorti");  // escribe Listo en el monitor
  miBT.begin(38400);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT); 
}

void loop() {
  if (miBT.available()){
    dato = miBT.read();
  }
  Serial.write(dato);
  
  if(dato==0||dato=='0'){
    Serial.println("Nada");
    digitalWrite (IN1, LOW);
    digitalWrite (IN2, LOW);
    //Direccion motor B
    digitalWrite (IN3, LOW);
    digitalWrite (IN4, LOW);
  }
  else if(dato==1||dato=='1'){
    /*if(atras_prom>=3 && atras_prom<8){
      Serial.println("atras");
      ATRAS ();
    }
    else{
      Serial.println("adelante");*/
      Adelante ();
    
  }
  else if(dato==2||dato=='2'){
    Serial.println("atras");
    ATRAS ();
    /*atras_prom++;
    if(atras_prom>10){
      atras_prom=0;
    }*/
  }
  else if(dato==3||dato=='3'){
    Serial.println("derecha");
    Derecha ();
  }
  else if(dato==4||dato=='4'){
    Serial.println("izquierda");
    IZQUIERDA ();
  }
}


void ATRAS ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
}
void Adelante ()
{

 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
}
void Derecha ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
}


void IZQUIERDA ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
}
