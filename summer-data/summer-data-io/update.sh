#! /bin/bash
echo "Updating local headers and libraries..."
if [ ! -d "/usr/include/org" ]; then
	mkdir /usr/include/org
fi
if [ ! -d "/usr/include/org/summerframework" ]; then
    	mkdir /usr/include/org/summerframework
fi
if [ ! -d "/usr/include/org/summerframework/data" ]; then
    	mkdir /usr/include/org/summerframework/data
fi
cp -r ./include/. /usr/include/org/summerframework/data

echo "Complete"
