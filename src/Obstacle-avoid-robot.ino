/*
 * Project Obstacle-avoid-robot
 * Description: 
 * Author: Jams
 * Date: 08-04-2023
 */
// Ejecutamos esta linea para que el codigo inicie antes de que el Photon se conecte a la nube
SYSTEM_THREAD(ENABLED);
#include <HC_SR04.h>

// Variables puente H
// Motor A
#define PWMA D0 
#define AIN1 D1
// Motor B
#define PWMB D2
#define BIN1 D3
// Pin ENABLE y PAUSE
#define EN D4
#define PAUSEPIN D5

// Variables Sensores
// Sensor frente
#define trigPinF  A0
#define echoPinF  A1
HC_SR04 sensorF = HC_SR04(trigPinF, echoPinF, 5.0, 15.0);
// Sensor izquierda
#define trigPinI  A2
#define echoPinI  A3
HC_SR04 sensorI = HC_SR04(trigPinI, echoPinI, 5.0, 15.0);
// Sensor derecha
#define trigPinD  A4
#define echoPinD  A5
HC_SR04 sensorD = HC_SR04(trigPinD, echoPinD, 5.0, 15.0);

// Funciones de movimiento
void forward(unsigned int speed);
void back(unsigned int speed);
void turn_left(unsigned int speed);
void turn_right(unsigned int speed);
void stop(unsigned int speed);

// Variables bucle sin delay
unsigned long prevMillis = 0;
unsigned const long INTERVALO = 100;

// Variables lectura de distancia
// double DistanciaF =0.0;
// double DistanciaD = 0.0;
// double DistanciaI = 0.0;
int obstaculo = 0.0;

void setup() {
  // Configuracion pines
  // Motor A
  pinMode(AIN1, OUTPUT);
  pinMode(PWMA, OUTPUT);
  // Motor B
  pinMode(BIN1, OUTPUT);
  pinMode(PWMB, OUTPUT);
  // Velocidad inicial, detenido
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  // Enable (Activar o desactivar puente H)
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
}

void loop() {

  unsigned long currMillis = millis();
  // Leer sensores ultrasonicos cada 100ms
  if (currMillis - prevMillis >= INTERVALO)
  {
    prevMillis = currMillis;
    // DistanciaF = sensorF.getDistanceDigital();
    // DistanciaD = sensorD.getDistanceDigital();
    // DistanciaI = sensorI.getDistanceDigital();
    obstaculo = sensorF.getDistanceDigital() + 2*sensorD.getDistanceDigital() + -2*sensorI.getDistanceDigital();
    switch (obstaculo)
    {
    case -1:
      turn_right(127);
      break;
    case 0:
      forward(255);
      break;
    case 1:
      turn_right(160);
      break;
    case 3:
      turn_left(127);
      break;
    default:
      forward(255);
      break;
    }
  }
  
  
}

void forward(unsigned int speed)
{
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    analogWrite(PWMA, speed);
    analogWrite(PWMB, speed);
}

void back(unsigned int speed)
{
    digitalWrite(PWMA, LOW);
    digitalWrite(PWMB, LOW);
    analogWrite(AIN1, speed);
    analogWrite(BIN1, speed);
}

void turn_left(unsigned int speed)
{
    digitalWrite(AIN1, speed);
    digitalWrite(BIN1, LOW);
    analogWrite(PWMA, LOW);
    analogWrite(PWMB, speed);
}

void turn_right(unsigned int speed)
{
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, speed);
    analogWrite(PWMA, speed);
    analogWrite(PWMB, LOW);
}

void stop(unsigned int speed)
{
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    analogWrite(PWMA, speed);
    analogWrite(PWMB, speed);
}