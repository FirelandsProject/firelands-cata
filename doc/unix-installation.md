# Firelands Core -- Linux installation
*Copyright (C) 2022 Firelands Core (https://github.com/FirelandsProject)*

<hr/>
WARNING: THIS DOCUMENTATION IS NOT ALWAYS UP TO DATE.
FOR MORE UP-TO-DATE INFORMATION, CHECK THE TRINITY WIKI.
<hr/>

Installing Firelands Core is fairly simple on a Linux machine, assuming you
have all required applications

The most important ones are:

    git
    cmake
    make
    gcc
    g++
    clang
    libssl-dev
    libbz2-dev
    libreadline-dev
    libncurses-dev
    libboost-all-dev
    mariadb-server
    mariadb-client
    libmariadb-dev
    libmariadb-dev-compat

Most of these are included on common Linux distros, others you may have
to install by your self. Please check your distro's repos.

Make a directory to build in, you can call it anything you want like
build or bin etc, then go into the directory and cmake and make. E.G.
you created a dir named build ad want to have your finalcompiled product
installed in /home/${user}/firelands/server, an example sequence of commands can
be :

```
    cmake ../ -DCMAKE_INSTALL_PREFIX=/home/firelands/server -DTOOLS=1 -DWITH_WARNINGS=1 -DSCRIPTS=static
    make -j ${number-of-processors}
    make install
```

Or If you want to install the core without Map tools:
```
    cmake ../ -DCMAKE_INSTALL_PREFIX=/home/firelands/server -DTOOLS=0 -DWITH_WARNINGS=1 -DSCRIPTS=static
    make -j ${number-of-processors}
    make install
```

Thats just about all thats needed. You can however tweak more settings
than where to install using flags built into our cmake files. Just open
up CMakeLists.txt in the main folder and take a look at some of the
flags like

    SERVERS             Build worldserver and bnetserver
    SCRIPTS             Build core with scripts included
    TOOLS               Build map/vmap extraction/assembler tools
    USE_SCRIPTPCH       Use precompiled headers when compiling scripts
    USE_COREPCH         Use precompiled headers when compiling servers
    WITH_WARNINGS       Show all warnings during compile
    WITH_COREDEBUG      Include additional debug-code in core
    PREFIX              Set installation directory
    NOJEM               Do not build with jemalloc (advanced users only)
    CONF_DIR            Set path as default configuration directory
    LIBSDIR             Set path as default library directory
    CMAKE_C_FLAGS       Set C_FLAGS for compile (advanced users only)
    CMAKE_CXX_FLAGS     Set CXX_FLAGS for compile (advanced users only)
    CMAKE_BUILD_TYPE    Set buildtype - the supported modes are :
                        Release, MinSizeRel, RelWithDebInfo, Debug

Of course, replace the paths in PREFIX, CONF_DIR and LIBSDIR with the
directories you wish to install Firelands Core to. The datadir is where maps,
DBCs, and SQLs are stored. The sysconfdir is where configuration files are stored.

Once Firelands Core is installed you will need to apply database updates
where necessary. Furthermore, you must configure your installation by
editing the config files in the sysconfdir.
