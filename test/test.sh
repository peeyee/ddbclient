#/bin/bash
echo "case 1:---"
../bin/ddbclient --help

echo "case 2:---"
../bin/ddbclient -h localhost -p 8848 -u admin --password 123456  -s "(1..10).reshape(2:5)"
if [ $? -eq 0 ];then
    echo "test command line input successfully."
fi

echo "case 3:---"
echo "1..10" > case3.dos
../bin/ddbclient -h localhost -p 8848 -u admin --password 123456  -f case3.dos
if [ $? -eq 0 ];then
    echo "test file input successfully."
fi
