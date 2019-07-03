# Test file for Lab2_introToAVR


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n


Test "PINA: 1  => PORTC: 7"
set state = start
setPINA 0x00
Continue 2
expectPORTC 0x07
expect state init
checkResult

Test "PINA: 1  => PORTC: 8"
set state = start
setPINA 0x01
Continue 2
expectPORTC 0x08
expect state A0press
checkResult

Test "PINA: 2  => PORTC: 6"
set state = start
setPINA 0x02
Continue 2
expectPORTC 0x06
expect state A1press
checkResult

Test "PINA: 0,1,0,1,0,1,0,1,0,1  => PORTC: 9"
set state = start
setPINA 0x00
Continue 2
expect state init
setPINA 0x01
Continue 1
expect state A0press
setPINA 0x00
Continue 1
expect state A0release
setPINA 0x01
Continue 1
expect state A0press
setPINA 0x00
Continue 1
expect state A0release
setPINA 0x01
Continue 1
setPINA 0x00
Continue 1
setPINA 0x01
Continue 1
expectPORTC 0x09
expect state A0press
checkResult

Test "PINA: 2,0,2,0,2,0,2  => PORTC: 3"
set state = start
setPINA 0x02
Continue 2
expectPORTC 0x06
setPINA 0x00
Continue 1
expectPORTC 0x06
setPINA 0x02
Continue 1
expectPORTC 0x05
setPINA 0x00
Continue 1
expectPORTC 0x05
setPINA 0x02
Continue 1
expectPORTC 0x04
setPINA 0x00
Continue 1
expectPORTC 0x04
setPINA 0x02
Continue 1
expectPORTC 0x03
expect state A1press
checkResult

Test "PINA: 2,0,1,0,2,3  => PORTC: 0"
set state = start
setPINA 0x02
Continue 2
setPINA 0x00
Continue 2
setPINA 0x01
Continue 2
setPINA 0x00
Continue 2
setPINA 0x02
Continue 2
setPINA 0x03
Continue 2
expectPORTC 0x00
expect state reset
checkResult
# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
