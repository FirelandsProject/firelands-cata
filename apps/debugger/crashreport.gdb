set logging overwrite on
set logging file backtrace.log
set style enabled off
set height unlimited
set width unlimited
set disassembly-flavor intel
handle SIG33 pass nostop noprint
set pagination 0
set logging on
echo \n--- DEBUG: --- START\n\n
run
echo \n--- DEBUG: BACKTRACE FULL\n
if FirelandsAssertionFailedMessage != 0
  printf "%s\n", FirelandsAssertionFailedMessage
end
echo \n
backtrace full
echo \n--- DEBUG: INFO REGISTERS\n\n
info registers
echo \n--- DEBUG: CALLS (x/16i $pc)\n\n
x/16i $pc
echo \n--- DEBUG: THREAD APPLY ALL BACKTRACE\n
thread apply all backtrace
echo \n--- DEBUG: --- STOP\n\n
echo Generated by crashreport.gdb script version 1.3\n
set logging off
quit