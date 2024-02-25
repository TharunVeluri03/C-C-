# Compile and link the coursework.c file
gcc -o coursework coursework.c

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable file 'coursework' created."

    # Execute the compiled program
    ./coursework
else
    echo "Compilation failed."
fi
