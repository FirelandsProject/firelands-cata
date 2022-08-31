#!/bin/bash

CURRENT_LOCATION=`pwd`

clear
echo ""
echo -e "\e[1;37m"
echo "         Remember that the files are generated in the env folder."
echo "         That is in the root of the project. Just at the same height as src."
echo -e "\e[1;32m"
echo "         ------  DB Assembler Version 1  ------"
echo ""
echo "         1. Assemble all SQL (Base and Updates)"
echo "         2. Assemble only the bases"
echo "         3. Assemble only the updates"
echo "         4. Exit"
echo ""
echo -e "\e[1;37m"
read -p "         Choose a number from 1 to 3: " opcion

case $opcion in
    1) all ;;
    2) bases ;;
    3) updates ;;
    4) leave ;;
    *) invalid ;;
esac

cd $CURRENT_LOCATION

all()
{
    echo ""
    echo "         All files"
    createDirectory
    baseFiles
    updatesFiles
}

bases()
{
    echo ""
    echo "         All bases"
    createDirectory
    baseFiles
}

updates()
{
    echo ""
    echo "         All updates"
    createDirectory
    updatesFiles
}

leave()
{
    echo ""
    echo -e "\e[1;32m"
    echo "         Good bye. Thank you for using our script."
}

invalid()
{
    echo ""
    echo -e "\e[1;31m"
    echo "         Invalid option. You must run the script again"
}

createDirectory()
{
    cd ..
    if [ -d env ]; then
        rm -rf env
        mkdir -p env/sql
    else
        mkdir -p env/sql
    fi
}

baseFiles()
{
    verify data/sql/base/db_auth/ env/sql/base_auth.sql
    verify data/sql/base/db_characters/ env/sql/base_characters.sql
    verify data/sql/base/db_hotfixes/ env/sql/base_hotfixes.sql
    verify data/sql/base/db_world/ env/sql/base_world.sql
}

updatesFiles()
{
    verify data/sql/updates/db_auth env/sql/updates_auth.sql
    verify data/sql/updates/db_characters env/sql/updates_characters.sql
    verify data/sql/updates/db_hotfixes env/sql/updates_hotfixes.sql
    verify data/sql/updates/db_world env/sql/updates_world.sql
}

verify()
{
    if [[ `find $1 -type f -iname "*.sql" | wc -l` -gt 0 ]]; then
        cat $1/*.sql > $2
    fi
}
