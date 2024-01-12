#!/bin/bash

file_to_monitor="Anamoly.log"  # Replace with the actual path to your file

inotifywait -m -e modify,attrib,close_write,move,create,delete "$file_to_monitor" |
while read -r directory events filename; do
    notify-send "Anamoly in weather status detected!" "Check $filename File for new anamolies."
    
done &  # Run the script in the background
