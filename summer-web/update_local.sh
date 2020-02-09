if [ ! -d "/usr/include/summer/" ]; then
    mkdir /usr/include/summer
fi

if [ ! -d "/usr/include/summer/summer-web" ]; then
    mkdir /usr/include/summer/summer-web
fi

if [ ! -d "/usr/lib/summer/" ]; then
    mkdir /usr/lib/summer
fi

if [ ! -d "/usr/lib/summer/summer-web" ]; then
    mkdir /usr/lib/summer/summer-web
fi

cp -r ./include/. /usr/include/summer/summer-web

cp -r ./lib/. /usr/lib/summer/summer-web