#!/bin/bash

CURRENT_LOCATION=`pwd`

cd ..

if [ -d env ]; then
    rm -rf env
    mkdir -p env/sql
else
    mkdir -p env/sql
fi

cat sql/base/db_auth/*.sql > env/sql/base_auth.sql
cat sql/base/db_characters/*.sql > env/sql/base_characters.sql
cat sql/base/db_hotfixes/*.sql > env/sql/base_hotfixes.sql
cat sql/base/db_world/*.sql > env/sql/base_world.sql

cat sql/updates/auth/4.3.4/*.sql > env/sql/updates_auth.sql
cat sql/updates/characters/4.3.4/*.sql > env/sql/updates_characters.sql
cat sql/updates/hotfixes/4.3.4/*.sql > env/sql/updates_hotfixes.sql
cat sql/updates/world/4.3.4/*.sql > env/sql/updates_world.sql

cd $CURRENT_LOCATION
