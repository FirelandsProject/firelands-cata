## HOW TO SCRIPT IN C++

<hr />
WARNING: THIS DOCUMENTATION IS NOT ALWAYS UP TO DATE.
FOR MORE UP-TO-DATE INFORMATION, CHECK THE TRINITY WIKI.
<hr />

1. create a file myscript.cpp in the scripts/custom folder.
2. Find the appropriate examples script in the scripts/examples folder and copy its contents. **Don't forget to rename the classes as appropriate!**
1. Rename the AddSC functions as appropriate.
2. Make sure to change the initializations in the AddSC function to the appropriate script names!
3. Under ScriptLoader.cpp, add your AddSC function near the top and in AddCustomScripts(), call it.
4. Add your myscript.cpp file to the scripts CMakeLists.txt: under: set(scripts_STAT_SRCS add: Custom/myscript.cpp
5. Redefine the virtual functions you want to override in your script.
6. If the script you are writing is database bound, add the scriptname to the appropriate location in the database.
7. Recompile and restart the server, and your script should be up and running.
