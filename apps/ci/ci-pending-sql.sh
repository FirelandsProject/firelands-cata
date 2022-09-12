#!/usr/bin/env bash

UPDATES_PATH="data/sql/updates/"

function import()
{
    db=$1
    folder="db_"$db
    pendingPath="data/sql/updates/pending_$folder"
    updPath="$UPDATES_PATH/$folder"

    latestUpd=`ls -1 $updPath/ | tail -n 1`

    dateToday=`date +%Y_%m_%d`
    counter=0

    dateLast=$latestUpd
    tmp=${dateLast#*_*_*_}
    oldCnt=${tmp%.sql}
    oldDate=${dateLast%_$tmp}

    if [ "$oldDate" = "$dateToday" ]; then
        ((counter=10#$oldCnt+1)) # 10 # is needed to explictly add to a base 10 number
    fi

    for entry in "$pendingPath"/*.sql; do
        if [[ -e $entry ]]; then
            cnt=$(printf -v counter "%02d" $counter ; echo $counter)
            newFile="$updPath/"$dateToday"_"$cnt".sql"
            cat $entry >> "$newFile"
            rm $entry;
            oldDate=$dateToday
            oldCnt=$cnt
            ((counter+=1))
        fi
    done
}

import "world"
import "hotfixes"
import "characters"
import "auth"

echo "Done."
