# ddbclient
A terminal that supports connecting to DolphinDB >= 1.30.21, 2.00.9. It's designed to be nearly zero-dependency.
Ddbclient is very convenient, has the following features :
* command history
* auto completion
* active and inactive mode
* execute shell
* multi-line input
* support for ARM


By now, It supports the following operating system.

|OS|Version|
| ------ | ----- |
|Linux|Ubuntu>=18.04, CentOS>=7.9|
|MacOS|Not supported yet|


## 1 install

### 1.1 binary install
```shell
tar -zxvf ddbclient-v1.0-Linux.tar.gz
```
### 1.2 centos
```
rpm -ivh ddbclient-v1.0-Linux.tar.gz
```
### 1.3 ubuntu
```
dpkg -i ddbclient-v1.0-Linux.deb
```
Ddbclient will be copied to /usr/local/bin and configure the environment variables.

### 1.4 build by source
Clone this project, and use cmake to build it. Currently, it only supports linux.
```shell
git clone https://github.com/peeyee/ddbclient
git checkout v1.0
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

* Q & A
---

**Q**: error: Failed dependencies:
        libgcc_s.so.1(GCC_7.0.0)(64bit) is needed by ddbclient-0.2.0-1.x86_64

**A**: install gcc
```shell
sudo apt-get update 
sudo apt install -y gcc
```

---

**Q**: bash: cmake: command not found

**A**: install cmake
```shell
sudo apt-get update 
sudo apt-get install cmake=3.1*
```
---


**Q**: CMake Error at CMakeLists.txt:2 (project):
  No CMAKE_CXX_COMPILER could be found.

**A**: install g++
```shell
sudo apt-get update  
sudo apt-get install g++
```

### 1.5 Package
Use cpack to get a appropriate package according to your OS. 

```shell
# rpm
cpack -G RPM

# deb
cpack -G DEB 

# tar.gz
cpack -G TGZ 
```


## 2 basic usage
Run `ddbclient` to get a brief mannual.
```
(base) peter@DESKTOP-1OB2067:~$ ddbclient
usage: ./ddbclient --host=string --port=int --username=string --password=string [options] ... 
options:
  -h, --host        ip/hostname of server (string)
  -p, --port        the port of node (int)
  -u, --username    username (string)
  -P, --password    password (string)
  -f, --file        filename of the script to be executed (string [=])
  -s, --script      the script to execute (string [=])
  -?, --help        print this message
```
### 2.1 activeMode
Without -f or -s options, it is considered as active mode, which you can
send script to server and watch the result and continue doing this. The result may be formatted to make it more readable. Set the basic options to connect to DolphinDB.
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

Ddbclient version 0.2.0
Welcome to DolphinDB 2.00.9.7 2023.06.08

cli>  
```
Input your command.
```shell
cli>  now()
2024.02.11T21:01:25.494
OK. Elapsed: 0.000 sec.

cli>  1..10
[1,2,3,4,5,6,7,8,9,10]
OK. Elapsed: 0.000 sec.

cli> print("hello world!")
hello world!

OK. Elapsed: 0.000 sec.
```
Use **quit** to exit the terminal.
```shell
cli>  quit
Bye.
```


From this version, command history,auto completion, multiline input are supported.

* command history

Use up/down arrow to search for command history. Use the **↑** to find the previous command and **↓** for next command.

* auto completion

Enter a little words, use **TAB** to get a non-ambiguous compeltion. Or double-click the tab key to list available candidate.

```shell
cli> a.msu
msum      msum2     msumTopN
```


```shell
cli> get #TAB TAB
Display all 169 possibilities? (y or n) #y
getActiveCID                         getDBIdByTabletChunk                 getMarketCalendar                    getSmallFileBucketMeta
getActiveMaster                      getDFSDatabases
```

* multi-line input

To make your input more readable, use multi-line input. Each line that ends with a "\\" is recognized as multi-line input. Client will wait until the command is finished.

```
cli> select \
cli> * \
cli> from t1
timestamp sym qty  price 
--------- --- ---- ------
09:34:07  C   2200 49.6  
09:36:42  MS  1900 29.46 
......
09:38:12  C   8800 51.29 

OK. Elapsed: 0.000 sec.
```

* execute shell

When input is started with a !, it's identified  as a shell command.

```shell
cli> !pwd
/home/peter/cppProjects/ddbclient/build
```
You can use `!clear` to clean the screen.


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

