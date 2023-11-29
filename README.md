# ddbclient
A terminal that supports connecting to DolphinDB >= 1.30.21, 2.00.9.By now, It supports the following operating system.

|OS|Version|
| ------ | ----- |
|Linux|Ubuntu>=18.04, CentOS>=7.9|
|MacOS|Not supported yet|


## 1 install

### 1.1 binary install
```shell
tar -zxvf ddbclient-0.1.0-Linux.tar.gz
```
### 1.2 centos
```
rpm -ivh ddbclient-0.1.0-Linux.tar.gz
```
### 1.3 ubuntu
```
dpkg -i ddbclient-0.1.0-Linux.deb
```
Ddbclient will be copied to /usr/local/bin and configure the environment variables.

### 1.2 build by source
Clone this project, and use cmake to build it. Currently, it only supports linux.
```shell
git clone https://github.com/peeyee/ddbclient
git checkout 0.1.0
cmake -B build -DCMAKE_BUILD_TYPE=release -S .
cd build/ && make
sudo make install
```
By default, it will be installed at /usr/local/in. append it into your $PATH.


```shell
cd ~ && vi .bashrc
export PATH="$PATH:$HOME/bin:/usr/local/bin" #add this to .bashrc
source .bashrc
```

## 2 basic usage
Run `ddbclient` to get a brief mannual.
```
(base) peter@DESKTOP-1OB2067:~$ ddbclient
DolphinDB client 0.1.alpha:
  --help                show help message
  -h [ --host ] arg     the ip/hostname connect to
  -p [ --port ] arg     the port of DolphinDB node
  -u [ --username ] arg username
  --password arg        password
  -f [ --file ] arg     read script from a file
  -s [ --script ] arg   the script to run
```
### 2.1 activeMode
Without -f or -s options, it is considered as active mode, which you can
send script to server and watch the result and continue doing this. The result may be formatted to make it more readable. Set the basic options to connect to dolphindb.
``` shell
(base) peter@DESKTOP-1OB2067:~$ ddbclient -h localhost -p 8848 -u admin --password 123456
============================================================
  _____          _         _      _         _____   ____
 |  __ \        | |       | |    (_)       |  __ \ |  _ \
 | |  | |  ___  | | _ __  | |__   _  _ __  | |  | || |_) |
 | |  | | / _ \ | || '_ \ | '_ \ | || '_ \ | |  | ||  _ <
 | |__| || (_) || || |_) || | | || || | | || |__| || |_) |
 |_____/  \___/ |_|| .__/ |_| |_||_||_| |_||_____/ |____/
                   | |
                   |_|

official website: https://www.dolphindb.com/
github: https://github.com/dolphindb
support email：support@dolphindb.com
============================================================

Welcome to DolphinDB 2.00.9.7 2023.06.08
>  
```
Input your command.
```shell
>  now()
2023.07.23T20:02:02.372
>  1..10
[1,2,3,4,5,6,7,8,9,10]
>  version()
2.00.9.7 2023.06.08
>  print("hello world!")
hello world!
```
Use **q** or **quit** to exit the terminal.
```shell
>  q
Bye.
```

### 2.2 inActiveMode
* s, script

Wrapping dolphinDB script with double quotes, For example:
```shell
(base) peter@DESKTOP-1OB2067:~$ ddbclient -h localhost -p 8848 -u admin --password 123456 -s "(1..10).reshape(2:5)"
#0 #1 #2 #3 #4
-- -- -- -- --
1  3  5  7  9
2  4  6  8  10
```
The result will be send to standard output.
* f, file

Read the script from a file, absolute paths are recommended, make sure you have the right to access it.
```shell
(base) peter@DESKTOP-1OB2067:~$ echo "now()" > now.dos
(base) peter@DESKTOP-1OB2067:~$ ddbclient -h localhost -p 8848 -u admin --password 123456 -f ~/now.dos
2023.07.23T20:15:35.954
```

