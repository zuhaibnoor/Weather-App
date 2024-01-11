#!/bin/bash

# Set the working directory
cd /home/owais/Desktop/CEW-OEL
export DISPLAY=:0
# Ensure autoscript.sh is executable
chmod +x autoscript.sh

echo "Script executed at $(date)" >> automate_track.log
# Execute autoscript.sh with parameters
./autoscript.sh 1
./autoscript.sh 2
./autoscript.sh 3

# Add this line to your automate.sh script
#/home/owais/Desktop/CEW-OEL/automate.sh 1 >> /home/owais/Desktop/CEW-OEL/automate.log 2>&1
