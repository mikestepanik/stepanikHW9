#!/bin/bash
# build file for the file control_GPIO.cpp also includes commands for configuring pins p9.12 and p816 
echo "Building the file control_GPIO.cpp......"
config-pin p9.12 gpio
config-pin p8.16 gpio_pu
g++ -Wall control_GPIO.cpp -o control_GPIO    
echo "Finished"
