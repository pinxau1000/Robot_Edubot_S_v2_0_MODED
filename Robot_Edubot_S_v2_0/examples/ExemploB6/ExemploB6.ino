/* 
Programa exemplo para testar as funcionalidades da placa desenvolvida:
- Seguir a linha
- rodar nas duas direções em cruzamentos
- inverter sentido de rotação no final da linha
- Mostrar logótipo do projeto "Escolher_ciência" e nome do robô "Edubot S v2.0" no lcd
- Mostrar direções atuais do robô no lcd atravérs de setas
*/

#include <Edubot.h>
#include <SPI.h>
#include <LCD_Mega.h>

Edubot robot;
LCD_Mega lcd;

// Variável para contagem de incrementos, acautelando pequenas falhas de linha na pista 
int count=0;
 
void setup() {
  
  robot.Setup();
  
  lcd.begin();  // Iniciar o LCD 
  lcd.LcdClear();
  delay(100);   // datasheet pede 100ms para arrancar
  
  lcd.LCDBitmap(escolher_ciencia);
  delay(2000);
  lcd.LCDBitmap(EdubotS); 
  
  // espera até pressionar o botão de pressão
  while(digitalRead(robot.SWITCH1)){};
  
  // espera até largar o botão de pressão
  while(!digitalRead(robot.SWITCH1)){}; 
 
}

void loop() {
  
  
  
  do{ // segue a linha equanto um dos sensores centrais está em cima da linha e os dois sensores lateriais estão sobre a cor branca
  
    robot.readSensors();
    
  // Segue linha utilizando os dois sensores centrais
  if ((robot.sensor_values[1] > robot.sensor_thresh) &&  (robot.sensor_values[2] > robot.sensor_thresh)){ // anda em frente
      count=0;
      robot.setMotorSpeed(robot.DIR, robot.baseSpeed);
      robot.setMotorSpeed(robot.ESQ, robot.baseSpeed);   
      lcd.LCDBitmap(seta_frente);
      
      
  }else if ((robot.sensor_values[1] < robot.sensor_thresh) &&  (robot.sensor_values[2] > robot.sensor_thresh)){ // rodar um pouco no sentido contrário aos ponteiros do relógio
      robot.setMotorSpeed(robot.DIR, robot.baseSpeed);
      robot.setMotorSpeed(robot.ESQ, 0.5*robot.baseSpeed);
      lcd.LCDBitmap(seta_frente_esquerda);
      
   }else if ((robot.sensor_values[1] > robot.sensor_thresh) && (robot.sensor_values[2] < robot.sensor_thresh)){ // rodar um pouco no sentido dos ponteiros do relógio
      robot.setMotorSpeed(robot.DIR, 0.5*robot.baseSpeed);
      robot.setMotorSpeed(robot.ESQ, robot.baseSpeed);
      lcd.LCDBitmap(seta_frente_direita);
   }
   
       
  }while(((robot.sensor_values[1] > robot.sensor_thresh) || (robot.sensor_values[2] > robot.sensor_thresh)) && (robot.sensor_values[0] < robot.sensor_thresh) && (robot.sensor_values[3] < robot.sensor_thresh));
  
  
  
  // testa primeiro o sensor do lado esquerdo 
 if((robot.sensor_values[0] > robot.sensor_thresh)){
    // se o sensor 0 está sobre a linha preta então roda para a direita
    robot.turnRobotInCross(robot.DIR);
  }
  
  
  // testa depois o sensor do lado direito
 if((robot.sensor_values[3] > robot.sensor_thresh)){
    // se o sensor 3 está sobre a linha preta então roda para a esquerda
    robot.turnRobotInCross(robot.ESQ);
  }
  
  // por último testa se todos os sensores estão fora da linha
 if((robot.sensor_values[0] < robot.sensor_thresh) && (robot.sensor_values[1] < robot.sensor_thresh) && (robot.sensor_values[2] < robot.sensor_thresh) && (robot.sensor_values[3] < robot.sensor_thresh)){
    // se todos os sensores estão fora da linha
     count++;
  
  if (count >= 100)
  robot.turnRobotBackToLine();
  }  



}





