/* 
Programa exemplo para testar as funcionalidades da placa desenvolvida:
- Leitura  dos valores dos sensores
- Teste dos sensores de infravermelhos TCRT5000, com resultados no terminal série
*/

#include <Edubot.h>

Edubot robot;
  
void setup(){

  robot.Setup();
  
}

void loop() {
  
  int i;

  robot.readSensors();
    
  // visualizar os valores no monitor série (Hyperterminal)
  for (i = 0; i < robot.NSENSORS; i++){
    Serial.print(robot.sensor_values[i],DEC);
    Serial.print("\t");
  }
    
  Serial.println();
    
  delay(100);
}

