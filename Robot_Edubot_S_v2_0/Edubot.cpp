/* 
Funções e definições do EduBot, o robô educativo da ESTG/IPLeiria
*/

#include <Arduino.h>
#include <Edubot.h>

///Constructor
Edubot::Edubot()
{
};



void Edubot::Setup(unsigned int _sensor_thresh){
  
  
	// inicializa comunicação serie a 9600 bps
	Serial.begin(9600); 
	
 	sensor_pins[0] = A0;
	sensor_pins[1] = A1;
	sensor_pins[2] = A2;
	sensor_pins[3] = A3;
	sensor_thresh = _sensor_thresh;
  
    // Define pinos de controlo como saídas
    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(BIN1, OUTPUT);  
    pinMode(BIN2, OUTPUT);
  
    // Motores parados no arranque
    digitalWrite(PWMA, LOW);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(PWMB, LOW);
    digitalWrite(BIN1, LOW);  
    digitalWrite(BIN2, LOW);
  
    // Define o LED do arduino como saída
    pinMode(LEDPIN, OUTPUT);
    
    // definir os terminais onde estão ligados os LEDs como saídas
    pinMode(LED1, OUTPUT);
    
    // Desligar os leds
    digitalWrite(LED1, HIGH);

    // definir os pinos dos interruptores como entrada
    pinMode(SWITCH1, INPUT);
  
}


void Edubot::readSensors(){
  
  unsigned char i, j;
    
  // reset the values
  for(i = 0; i < NSENSORS; i++)
  	sensor_values[i] = 0;
  
  for (j = 0; j < num_samples_per_sensor; j++)
  	for (i = 0; i < NSENSORS; i++)
  		sensor_values[i] += analogRead(sensor_pins[i]);	// add the conversion result
  
  // get the rounded average of the readings for each sensor
  for (i = 0; i < NSENSORS; i++)
  	sensor_values[i] = (sensor_values[i] + (num_samples_per_sensor >> 1)) / num_samples_per_sensor;
  

}



void Edubot::setMotorSpeed(boolean motor, int s){
  
  s=constrain(s,-255,255);
  
   if(motor){
    
    if (s>0){
         digitalWrite(AIN1, HIGH);  // anda para a frente
         digitalWrite(AIN2, LOW);
         analogWrite(PWMA, s);
      }else if (s<0){
         digitalWrite(AIN1, LOW);  // anda para trás
         digitalWrite(AIN2, HIGH);
         analogWrite(PWMA, -s); 
      } else {         
         digitalWrite(AIN1, LOW);  // pára
         digitalWrite(AIN2, LOW); 
         digitalWrite(PWMA, HIGH);          
      }
    
  }else{
        
      if (s>0){
         digitalWrite(BIN1, HIGH);  // anda para a frente
         digitalWrite(BIN2, LOW);
         analogWrite(PWMB, s);
      }else if (s<0){
         digitalWrite(BIN1, LOW);  // anda para trás
         digitalWrite(BIN2, HIGH);
         analogWrite(PWMB, -s); 
      } else {         
         digitalWrite(BIN1, LOW);  // pára
         digitalWrite(BIN2, LOW); 
         digitalWrite(PWMB, HIGH);     
      }
     
    }
    //Serial.println(s); 
}


bool Edubot::irLine(int sensor)
{
	return (sensor_values[sensor] > sensor_thresh);
}

bool Edubot::chkLine(int sensor_val)
{
	return (sensor_val > sensor_thresh);
}

void Edubot::turnRobotBackToLine(){

  // roda 180 graus
  // gira sobre o proprio eixo
      setMotorSpeed(ESQ, 0.8*baseSpeed);
      setMotorSpeed(DIR, -0.8*baseSpeed);
    // roda até todos os sensores sairem de cima da linha
  do{     
    readSensors();
//    Serial.println("1o do while - turn");
    }while( sensor_values[0] > sensor_thresh && sensor_values[1] > sensor_thresh && sensor_values[2] > sensor_thresh && sensor_values[3] > sensor_thresh);
    
    // roda até o sensor 2 estar por cima da linha
    do{
       readSensors(); 
//           Serial.println("2o do while - turn");
      }while(sensor_values[2] < sensor_thresh);
  
   setMotorSpeed(DIR, 0 );
   setMotorSpeed(ESQ, 0 );
   
}


void Edubot::turnRobotInCross(boolean dir){

  
  if (!dir){
 // roda 90 graus no sentido contrario aos ponterios do relogio
   
       // roda
      setMotorSpeed(ESQ, -0.3*baseSpeed);
      setMotorSpeed(DIR, baseSpeed);
    // roda até o sensor 3 sair de cima da linha
    do{
      readSensors();
    }while(sensor_values[3] > sensor_thresh);
    // roda até o sensor 1 estar por cima da linha
    do{
       readSensors(); 
      }while(sensor_values[1] < sensor_thresh);   
   
    setMotorSpeed(DIR, 0 );
    setMotorSpeed(ESQ, 0 );
   
   
   
  }else {
   // roda 90 graus no sentido dos ponterios do relogio
   
    // roda
      setMotorSpeed(ESQ, baseSpeed);
      setMotorSpeed(DIR, -0.3*baseSpeed);
    // roda até o sensor 0 sair de cima da linha
    do{
      readSensors();
    }while(sensor_values[0] > sensor_thresh);

    // roda até o sensor 2 estar por cima da linha
    do{
       readSensors(); 
      }while(sensor_values[2] < sensor_thresh);   
   
    setMotorSpeed(DIR, 0 );
    setMotorSpeed(ESQ, 0 );

  }
}
