/* 
 * 
 * Programa exemplo para testar as funcionalidades da placa desenvolvida:
- Seguidor de linha com base nos dois sensores centrais
 */
 
#include <Edubot.h>

Edubot robot;

void setup() {
  
  robot.Setup();
  
  // espera até pressionar o botão de pressão
  while(digitalRead(robot.SWITCH1)){};  
  // espera até largar o botão de pressão
  while(!digitalRead(robot.SWITCH1)){}; 
  
}

void loop() {
  
  robot.readSensors();
  
  // Segue linha utilizando os dois sensores centrais
  if ((robot.sensor_values[1] > robot.sensor_thresh) &&  (robot.sensor_values[2] > robot.sensor_thresh)){ // anda em frente
    robot.setMotorSpeed(robot.DIR, robot.baseSpeed);
    robot.setMotorSpeed(robot.ESQ, robot.baseSpeed); 
    digitalWrite(robot.LED1, LOW); // acende o LED
    
  }else if ((robot.sensor_values[1] < robot.sensor_thresh) &&  (robot.sensor_values[2] > robot.sensor_thresh)){ // rodar um pouco no sentido dos ponteiros do relógio
    robot.setMotorSpeed(robot.DIR, robot.baseSpeed);
    robot.setMotorSpeed(robot.ESQ, 0.5*robot.baseSpeed);
    digitalWrite(robot.LED1, HIGH); // apaga o LED
    
  }else if ((robot.sensor_values[1] > robot.sensor_thresh) && (robot.sensor_values[2] < robot.sensor_thresh)){ // rodar um pouco no sentido contrário aos ponteiros do relógio
    robot.setMotorSpeed(robot.DIR, 0.5*robot.baseSpeed);
    robot.setMotorSpeed(robot.ESQ, robot.baseSpeed);
    digitalWrite(robot.LED1, HIGH); // apaga o LED
    
  }else if ((robot.sensor_values[1] < robot.sensor_thresh) && (robot.sensor_values[2] < robot.sensor_thresh)){   // sensores centrais detetam branco - o robo para
    robot.setMotorSpeed(robot.DIR, 0);
    robot.setMotorSpeed(robot.ESQ, 0);
    digitalWrite(robot.LED1, HIGH); // apaga o LED
  }  
  
}


