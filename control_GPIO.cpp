/* File name: control_GPIO.cpp
 *  This program controls GPIO pins on the BeagleBone Black
 *  It takes three command line arguments
 *  1.) GPIO number (pin used for OUTPUT)
 *  2.) Hi or Low   (setting the state of the output pin in argument 1)
 *  3.) GPIO number (pin used for INPUT)
 *    
 *    Written by Mike Stepanik, November 7, 2022.
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define PATH "/sys/class/gpio/"

string create_path(string number){
	ostringstream s;
	s << PATH << "gpio" << number << "/";
	return s.str();
}

int GPIO_write(string path, string filename, string value){
	fstream fs;
   	fs.open((path+filename).c_str(),fstream::out);
   	if (!fs.is_open()){
		perror("GPIO: write falied to open file");
		return -1;
   	}
   	fs << value;
   	fs.close();
   	return 0;
}

string GPIO_read(string path,string filename){
	fstream fs;
	fs.open((path + filename).c_str(), fstream::in);
   	if (!fs.is_open()){
     		perror("GPIO: read failed to open file");
   	}
 	string input;
 	getline(fs,input);
 	fs.close();
 	return input;
}

void setDirection(int direction, string GPIO_NUMBER){
	switch(direction){
	case 0:
             GPIO_write(GPIO_NUMBER,"direction", "in"); 
		
	case 1:
	     GPIO_write(GPIO_NUMBER, "direction", "out");
	}
}

int getValue(string GPIO_NUMBER){
	string output = GPIO_read(GPIO_NUMBER, "value");
	if (output == "0")
		return 0;
	else 
		return 1;
}

void setValue(int value, string GPIO_NUMBER){
	GPIO_write(GPIO_NUMBER, "value", to_string(value));
}


int main (int argc, char* argv[]){
	if (argc !=4){
	cout << "Incorrect usage of command" << endl;
	cout << "usage is : <pin> , <hi or low>, <pin>" << endl;
	cout << "e.g ./control_GPIO 60 hi 46"<< endl;
	cout << "this would set GPIO60 to hi and read GPIO46" << endl;
	return 4;
	}


	string opin(argv[1]);
	string state (argv[2]);
	string ipin(argv[3]);

	string opin_path = create_path(opin);
	string ipin_path = create_path(ipin);


	if (state=="hi"){
		setValue(1, opin_path);
	}
	else if (state=="low"){
		setValue(0, opin_path);
	}
	else {
		cout << "Invalid state" << endl;
	}

	
	cout << endl;
	cout << "Configuring gpio" << opin << " as an output" << endl;
	cout << "Setting gpio" << opin << " " << state << endl; 
	cout << "The reading on gpio" << ipin << " is: " << getValue(ipin_path) << endl;
	cout << endl;
	
	return 0;

}

