#!/bin/bash
set -e
echo "1. Copy files"
cp bin/ddbclient /usr/local/bin
cp lib/libDolphinDBAPI.so /usr/local/lib

echo "    Copy files to /usr/local finished."
echo ""

echo "2. Configure enviroment"
cat >> $HOME/.bashrc<<EOF
export PATH=\$PATH:/usr/local/bin
export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/usr/local/lib
EOF

echo "    Enviroment configure successfully."
echo "    Install finished."
