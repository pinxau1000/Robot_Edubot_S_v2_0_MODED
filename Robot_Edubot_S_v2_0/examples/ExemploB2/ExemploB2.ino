/* 
- Programa exemplo para testar as funcionalidades da placa desenvolvida:
- Controlo dos motores
- Se botão 1 pressionado anda em frente durante 2s;
 */
 
#include <Edubot.h>

Edubot robot;

void setup() {
  
   robot.Setup();
}

void loop() {
 
  
  if (digitalRead(robot.SWITCH1) == LOW){ 
    robot.setMotorSpeed(robot.DIR, 50); // andar para a frente com velocidade 100
    robot.setMotorSpeed(robot.ESQ, 50);
    digitalWrite(robot.LED1, LOW);
    delay(2000);
    digitalWrite(robot.LED1, HIGH);
  }  
  
  robot.setMotorSpeed(robot.DIR, 0); // motores parados
  robot.setMotorSpeed(robot.ESQ, 0);
  
}


