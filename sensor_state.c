#include <iostream>
#include "sensor_state.h"

int main() {
	
	float sensor1 = 0;
	float sensor2 = 0;
	float sensor3 = 0;
	float sensor4 = 0;
	four_states = first; 

	float avg = 0;

	while (avg == 0) {
		switch (four_states) {
			case first:
				//dbgOutputVal(); //need in every state 
				std::cout << "first state check" << std::endl;
				sensor1 = 3;
				four_states = second;
				break;
			case second:
				//dbgOutputVal(); 
				std::cout << "check for second state" << std::endl;
				sensor2 = 2;
				four_states = third; 
				break;
			case third:
				//dbgOutputVal();
				std::cout << "third state check" << std::endl; 
				sensor3 = 1;
				four_states = fourth; 
				break;
			case fourth:
				//dbgOutputVal();  
				sensor4 = 5;
				avg = (sensor1 + sensor2 + sensor3 + sensor4) / 4;
				std::cout << "This is the average of the sensors" << " " << avg << std::endl;
				//dbgUARTVal(); //print out the average
				break;
			default:
				std::cout << "An Error has occurred\n";
				break;
		}
	}
	return 0; 

}