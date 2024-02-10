#/bin/bash
dir=../build/bin

echo "case 1:---"
$dir/ddbclient --help

echo ""
echo "case 2:---"
$dir/ddbclient -h localhost -p 8848 -u admin --password 123456  -s "(1..10).reshape(2:5)"
if [ $? -eq 0 ];then
    echo "test command line input successfully."
fi

echo ""
echo "case 3:---"
echo "1..10" > case3.dos
$dir/ddbclient -h localhost -p 8848 -u admin --password 123456  -f case3.dos
if [ $? -eq 0 ];then
    echo "test file input successfully."
fi
