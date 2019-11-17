# Batlife

A pretty small and simple script that displays the battery life in the Linux terminal.
This was really made because on the Linux distro Manjaro for laptops reading battery life
is not the most accurate thing in the world, it only seems to be accurate when the reading
is at a 25% * X increment (aka 0-25-50-75-100 %). 

# How it works

Pretty simple, reads the file that Linux generates from sys/class/power_supply runs a regex
check to get ignore anything that is not needed then just spams the console with the battery
life until it's told to stop.

# Todo 

Change over the fprintf in main for when it does the linux check