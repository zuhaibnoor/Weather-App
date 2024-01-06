#!/bin/bash

gcc headers/cJSON.c Functions/read.c Functions/retrieval.c Functions/date_utils.c test.c -o run -lcurl

while true; do
    echo "1. DATA RETRIEVAL"
    echo "2. PROCESSING"
    echo "3. REPORT GENERATION"
    echo "4. EXIT"

    echo "Enter your Choice:"
    read choice

    case $choice in
        1)
            clear
            echo "Retrieving..."
            ./run $choice
            ;;
        2)
            clear
            echo "Data has been processed"
            result=$(./run $choice)
            echo "Result: $result"
            if [ "$result" -eq 1 ]; then
                chmod +x send_email_script.sh
                ./send_email_script.sh
            else
                echo "NO ANOMALY"
            fi
            
            
            ;;
        3)
            clear
            echo "Report Generating..."
            ./run $choice
            ;;
        4)
            clear
            echo "Exiting..."
            break
            ;;
        *)
            clear
            echo "Invalid choice"
            ;;
    esac
done

