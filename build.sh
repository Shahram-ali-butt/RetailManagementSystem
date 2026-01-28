echo "--- Starting Compilation ---"

g++ -Iinclude src/*.cpp -o "main.exe"

if [ $? -eq 0 ]; then
    echo "--- Compilation Successful ---"
    ./"main.exe"
else
    echo "--- Compilation Failed! Check the errors printed above. ---"
    read -p "Press [Enter] key to continue..."
fi