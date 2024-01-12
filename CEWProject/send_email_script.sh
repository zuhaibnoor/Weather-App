#!/bin/bash

recipient_email="owais4500107@cloud.neduet.edu.pk"
subject="Warning! Weather anamoly detected!"
attachment="Anamoly.log"

# Check if uuencode is installed
if ! command -v uuencode &> /dev/null; then
    echo "Error: uuencode is not installed. Please install the 'sharutils' package."
    exit 1
fi

# Send email with attachment
(echo "Dear User, this is an automatically generated Email. You are recieving this mail because your weather app has detected an anamoly in the weather status. To stay safe and prevent any mishaps please have a look at the attached log file for more information. STAY SAFE ! Thank you" && uuencode "$attachment" "$attachment") | mail -s "$subject" "$recipient_email"

if [ $? -eq 0 ]; then
    echo "Email sent successfully."
else
    echo "Error: Failed to send email."
fi

