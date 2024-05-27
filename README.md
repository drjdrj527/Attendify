# Attendify

Welcome to Attendify, a smart and efficient attendance tracking system powered by the ESP32 microcontroller. Attendify simplifies the process of recording attendance, ensuring accurate and real-time data logging.

# Features

Automated Attendance Logging: Automatically logs attendance based on connected devices' MAC addresses.

Real-Time Updates: Web interface updates in real-time to show the latest attendance records.

Easy Setup and Configuration: Simple setup with predefined SSID and password for the ESP32 access point.

# Hardware Requirements

ESP32 Development Board

Wi-Fi network

# Software Requirements

Arduino IDE with ESP32 board support

Web server (e.g., 000webhost)

MySQL database

# Step-by-Step Guide:

Setting Up the Development Environment:

Install the Arduino IDE

Install the required libraries.

Set up your MySQL database and web server.

# ESP32 Setup

Upload Code: Paste the Attendify.ino code into the Arduino IDE and upload it to your ESP32 board.

# Database Table Creation:

Open the Database_table_creation.txt file in a text editor.

Review the SQL script within the file. It defines a table named EspData to store attendance records.

Execute this SQL query into your MySQL database.

# Configure the following files for the web interface:

post-esp-data.php: This script on the web server receives data from the ESP32 and stores it in the database. Edit the script's database connection details.

index.php: This script displays the attendance records on the web dashboard. Customize its appearance and data formatting as desired.

# Running the System:

Power up your ESP32 board with uploaded code file.

