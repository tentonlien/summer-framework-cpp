g++ $(mysql_config --cflags) summer/*.cpp summer/xml/*.cpp summer/sql/*.cpp controller/*.cpp -o build/app $(mysql_config --libs)
./build/app