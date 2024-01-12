#!/bin/bash

# Set the working directory
cd /home/owais/Desktop/CEW-OEL

# Compile the C program using the following terminal command
gcc headers/cJSON.c Functions/read.c Functions/retrieval.c Functions/date_utils.c test.c -o run -lcurl

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Weather app has been compiled successfully"
else
    echo "Weather app compilation failed"
    exit 1
fi

# Set the choice parameter
choice="$1"

# Ensure the executable is not busy
while fuser ./run &>/dev/null; do
    echo "Waiting for ./run to be available..."
    sleep 1
done

echo "Choice $choice"
echo "Weather app has started successfully"

case $choice in
    1)
        # echo "Retrieving..."
        ./run $choice
        ;;
    2)
        # echo "Data has been processed"
        result=$(./run $choice)
        # echo "Result: $result"
        if [ "$result" -eq 1 ]; then
            chmod +x send_email_script.sh
            ./send_email_script.sh
        #else
        #    echo "NO ANOMALY"
        fi
        ;;
    3)
        # echo "Report Generating..."
        ./run $choice
        ;;
    *)
        clear
        # echo "Invalid choice"
        ;;
esac

echo "Weather app Exited successfully"
