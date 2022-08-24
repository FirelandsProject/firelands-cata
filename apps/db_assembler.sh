#!/bin/bash

CURRENT_LOCATION=`pwd`

cd ..

if [ -d env ]; then
    rm -rf env
    mkdir -p env/sql
else
    mkdir -p env/sql
fi

cat data/sql/base/db_auth/*.sql > env/sql/base_auth.sql
cat data/sql/base/db_characters/*.sql > env/sql/base_characters.sql
cat data/sql/base/db_hotfixes/*.sql > env/sql/base_hotfixes.sql
cat data/sql/base/db_world/*.sql > env/sql/base_world.sql

cat data/sql/updates/db_auth/*.sql > env/sql/updates_auth.sql
cat data/sql/updates/db_characters/*.sql > env/sql/updates_characters.sql
cat data/sql/updates/db_hotfixes/*.sql > env/sql/updates_hotfixes.sql
cat data/sql/updates/db_world/*.sql > env/sql/updates_world.sql

cd $CURRENT_LOCATION
