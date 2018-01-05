/* 
Funções e definições do EduBot, o robô educativo da ESTG/IPLeiria
*/

#ifndef Edubot_h
#define Edubot_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

class Edubot
{
public:
	Edubot();
	void Setup(unsigned int _sensor_thresh=700); 	// configuração inicial do EduBot
	void readSensors();  							// ler os sensores de IV
	void setMotorSpeed(boolean motor, int s); 		// coloca o motor indicado  a girar com uma velocidade entre -255 e +255
	void turnRobotBackToLine();						// roda 180º sobre o próprio eixo
	void turnRobotInCross(boolean dir);				// roda 90º para a esquerda ou direita
	
	bool irLine(int sensor);
	bool chkLine(int sensor_val);
	
	// número de sensores que vamos ler
	static const int NSENSORS = 4;
	
	// Variável que armazena os valores das leituras dos sensores
	unsigned int sensor_values[NSENSORS]; 			// vetor com as leituras de cada sensor	
	
	// Variável que define o nível de thresold 
	unsigned int sensor_thresh;
	
	// definição para seleção dos motores
	static const int DIR = 1;
	static const int ESQ = 0;
	
	// Interruptores
	static const int SWITCH1 = A4;
	
	// LEDs
	static const int LED1 = A5;    // Led verde da placa de interface
	static const int LEDPIN = 13;  // Led do Arduino
	
	// Velocidade base para os motores
	int baseSpeed = 150;
	
private:
	unsigned char sensor_pins[4];	    // definição das entradas analogicas A0 a A3
	static const unsigned char num_samples_per_sensor = 5; 			// número de leituras para cada sensor
		
	// Ponte em H
	static const int PWMA = 6;  // Left Motor PWMA
	static const int AIN1 = 5;  // Left Motor   A IN1  Motor do lado direito é o A 
	static const int AIN2 = 7;  // Left Motor   A IN2
	static const int PWMB = 3;  // Right Motor PWMB
	static const int BIN1 = 4;  // Right Motor  B IN1 Motor do lado esquerdo é o B 
	static const int BIN2 = 2;  // Right Motor  B IN2
		
};


#endif



