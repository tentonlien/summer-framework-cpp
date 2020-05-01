if [ ! -d "/usr/include/nlohmann-json/" ]; then
    mkdir /usr/include/nlohmann-json
fi

cp -r ./include/. /usr/include/nlohmann-json