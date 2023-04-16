#!/bin/bash

#Upload arduino romeo sketch
echo "Uploading romeo sketch"
if [ -f /dev/ttyACM1 ] ; then 
    arduino-cli compile arduino-rov-romeo-controller.ino || { echo "Failed to compile romeo sketch" ; exit 1; }
    arduino-cli upload -p /dev/ttyACM1 -b arduino:avr:uno arduino-rov-romeo-controller.ino || { echo "Failed to upload romeo sketch" ; exit 1; }
else
  echo "Failed to upload romeo sketch device missing"   
  exit 1
fi
#Waiting for arduino to complete
sleep 1000
#Check result from romeo
printf '\x21\0x10' & answer=$(head -n1 /dev/ttyACM1)
if ["$answer" = "OK"] ; then
    echo "Got successful response from romeo"
else
    echo "Got fail response from romeo"
    exit 1
fi