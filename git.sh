#!/bin/bash


TODAY=`date +"%d%b%Y"`

#mysqldump -h gurdil.be -P 3306 -u root -pSQLforEVER1337 trollnium  > backup/db$





echo "--- Git of NUKA ---"

git add .

#read -p "Commit message : " name
git commit -a -m "Backup of $TODAY"

#git config --global pack.threads 4
#git config --global pack.windowMemory 256m
#git config pack.windowMemory 10m
#git config pack.packSizeLimit 20m

git push origin master


echo "DONE"


