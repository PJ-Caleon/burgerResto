#!/bin/bash

# Compile main.c and display_menu.c (adjust paths correctly)
gcc ../main.c \
    ../src/display_menu.c \
    ../src/take_order.c\
    -I ../include \
    -o main

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation succeeded, running program..."
    ./main
else
    echo "Compilation failed."
fi
