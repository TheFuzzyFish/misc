@echo off
title Loading...
REM Author: Zachary Kline
REM Written: 2015 October 20
REM When a string of text says "REM" or "::" before it, that means that it is a comment that is not read by the command processor and only by the person editing this file as a text document (who just so happens to be you at this time).
REM Screen dimensions are from over there<<< to over here>>>                             |
:LoadingScreen0
cls
color 1f
echo.
echo                         ####  #  ###  #      *  ###
echo                         #        #    #      *  #
echo                         ###   #  ###  ####      ###
echo                         #     #    #  #  #        #
echo                         #     #  ###  #  #      ###
echo.
echo.
echo                     #####              #  #
echo                       #                #  #
echo                       #    ####  ####  #  ####  ####  # #
echo                       #    #  #  #  #  #  #  #  #  #   #
echo                       #    ####  ####  #  ####  ####  # #
echo.
ping localhost -n 3 >nul
:Welcome0
cls
color 1f
title Swiss Batch File
echo.
echo                       Welcome to the Swiss Batch File
echo                               by Zachary Kline
echo.
ping localhost -n 3 >nul
::USED TO SKIP THE FAULTY LOGIN SCREEN:
goto GUI0
:LOGIN0
cls
color 0a
title Login
echo.
echo Please Login:
set/p "loginusername=Username:"
set/p "loginpassword=Password:"
if %loginusername%=="thefuzzyfish" if %loginpassword%=="1775" goto GUI0
:LOGINFAIL0
cls
color 4f
title Invalid Login
echo.
echo  The login credentials you have provided are invalid.
echo  Please try again.
ping localhost -n 3 >nul
goto LOGIN0
:GUI0
title Swiss Batch File
color 1f
cls
echo.
echo     Please enter a choice of what you want to do from the list below in
echo                           numerical format:
echo.
echo.
echo  (1) Folder Locker (default password = "password123")
:: The password for the Folder Locker is located on line 130 and editable. (It's directly after the ==)
echo  (2) Epilepsy Freak-out
echo  (3) Matrix
echo  (4) File Information
echo  (5) System Crash
echo  (6) Debugger
echo  (7) Shutdown
echo  (8) Reboot
echo  (9) More Options...
echo.
set /p "menuselect=Choice: "
if %menuselect%==1 goto menuselect1
if %menuselect%==2 goto menuselect2
if %menuselect%==3 goto menuselect3
if %menuselect%==4 goto menuselect4
if %menuselect%==5 goto menuselect5
if %menuselect%==6 goto menuselect6
if %menuselect%==7 goto menuselect7
if %menuselect%==8 goto menuselect8
if %menuselect%==9 goto menuselect9
if %menuselect%==school goto shittycomputercrash
if %menuselect%==School goto shittycomputercrash
if %menuselect%==SCHOOL goto shittycomputercrash
:invalid0
cls
color 4f
echo.
echo  The choice you have entered is not an option.
echo  Please try again.
ping localhost -n 5 >nul
goto GUI0
REM FOLDER LOCKER START------------------------------------------------------------------------------------------------------------------------------------------
:menuselect1
cls
color 0a
title Folder Locker
:STATUSCHECK1
if EXIST "071642fa72ba780ee90ed36350d82745" goto UNLOCK1
if NOT EXIST Locker goto MAKELOCKER1
:CONFIRM1
cls
echo.
echo  Are you sure u want to Lock the folder(Y/N)
set/p "response= >"
if %response%==Y goto LOCK1
if %response%==y goto LOCK1
if %response%==n goto GUI0
if %response%==N goto GUI0
echo.
echo  Invalid choice.
ping localhost -n 3 >nul
goto CONFIRM1
:LOCK1
cls
attrib -r "Locker" /s
rename "Locker" "071642fa72ba780ee90ed36350d82745"
attrib +h +s +r "071642fa72ba780ee90ed36350d82745"
cls
echo.
echo  Folder locked
ping localhost -n 3 >nul
goto GUI0
:UNLOCK1
cls
echo.
echo  Enter password to Unlock folder
set/p "pass=>"
REM FOLDER LOCKER PASSWORD \/
if NOT %pass%==password123 goto FAIL1
cls
attrib -r -h -s "071642fa72ba780ee90ed36350d82745"
rename "071642fa72ba780ee90ed36350d82745" "Locker"
echo.
echo  Folder Unlocked successfully
ping localhost -n 3 >nul
goto STATUSCHECK1
:FAIL1
cls
echo.
echo  Invalid password
ping localhost -n 3 >nul
goto UNLOCK1
:MAKELOCKER1
cls
echo.
echo  A hidden folder does not exist in this directory.
echo  Do you want to make one now?(Y/N)
set/p "response=>"
if %response%==Y goto MAKELOCKERFUNCTION1
if %response%==y goto MAKELOCKERFUNCTION1
if %response%==n goto END
if %response%==N goto END
cls
echo.
echo  Invalid choice.
ping localhost -n 3 >nul
goto MAKELOCKER1
:MAKELOCKERFUNCTION1
cls
md "Locker"
echo.
echo  Locker created successfully
ping localhost -n 3 >nul 
goto GUI0
REM FOLDER LOCKER END--------------------------------------------------------------------------------------------------------------------------------------------
:menuselect2
REM EPILEPSY START-----------------------------------------------------------------------------------------------------------------------------------------------
cls
echo.
echo                              DISCLAIMER:
echo  I am not responsible for any damage done with this file in any way, shape,
echo  or form.
ping localhost -n 5 >nul
cls
title Epilepsy
mode 227
:A2
color 0a
color 1a
color 2a
color 3a
color 4a
color 5a
color 6a
color 7a
color 8a
color 9a
color a0
color ba
color ca
color da
color ea
color fa
goto :A2
REM EPILEPSY END-------------------------------------------------------------------------------------------------------------------------------------------------
:menuselect3
REM MATRIX START-------------------------------------------------------------------------------------------------------------------------------------------------
cls
color 0a
title Matrix
mode 227
:Matrix3
echo 010011010110000101110100011100100110100101110100110101100001011101000111001001101001011101001101011000010111010001110010011010010111010011010110000101110100011100100110100101110100110101100001011101000111001001101001011111
echo 100101111000111000011000101111100100010111001001011110001110000110001011111001000101110010010111100011100001100010111110010001011100100101111000111000011000101111100100010111001001011110001110000110001011111001000101110011
echo 101111110110000000111110111000110100100100001011111101100000001111101110001101001001000010111111011000000011111011100011010010010000101111110110000000111110111000110100100100001011111101100000001111101110001101001001000001
echo 101100110100110110010000101110000111001010111011001101001101100100001011100001110010101110110011010011011001000010111000011100101011101100110100110110010000101110000111001010111011001101001101100100001011100001110010101111
echo 000000111100011011011111000100011000111110100000001111000110110111110001000110001111101000000011110001101101111100010001100011111010000000111100011011011111000100011000111110100000001111000110110111110001000110001111101000
echo 101011011001010011111110000110101000010101001010110110010100111111100001101010000101010010101101100101001111111000011010100001010100101011011001010011111110000110101000010101001010110110010100111111100001101010000101010000
echo 001101000111101111001010000100101111000011100011010001111011110010100001001011110000111000110100011110111100101000010010111100001110001101000111101111001010000100101111000011100011010001111011110010100001001011110000111001
echo 100110100101001001110010001001101011001011111001101001010010011100100010011010110010111110011010010100100111001000100110101100101111100110100101001001110010001001101011001011111001101001010010011100100010011010110010111110
echo 110011001100100111000010010100111000011111011100110011001001110000100101001110000111110111001100110010011100001001010011100001111101110011001100100111000010010100111000011111011100110011001001110000100101001110000111110100
echo 000010100111010111111111001000100000011100110000101001110101111111110010001000000111001100001010011101011111111100100010000001110011000010100111010111111111001000100000011100110000101001110101111111110010001000000111001110
echo 110011100111010000000001100001111101110101011100111001110100000000011000011111011101010111001110011101000000000110000111110111010101110011100111010000000001100001111101110101011100111001110100000000011000011111011101010110
echo 010110101100111100100100011000100011110101010101101011001111001001000110001000111101010101011010110011110010010001100010001111010101010110101100111100100100011000100011110101010101101011001111001001000110001000111101010111
echo 111010001101100000110101111001010110000011101110100011011000001101011110010101100000111011101000110110000011010111100101011000001110111010001101100000110101111001010110000011101110100011011000001101011110010101100000111001
echo 001100111011101110000001010101001010111010010011001110111011100000010101010010101110100100110011101110111000000101010100101011101001001100111011101110000001010101001010111010010011001110111011100000010101010010101110100100
echo 010001100000100101101110011110101010011010110100011000001001011011100111101010100110101101000110000010010110111001111010101001101011010001100000100101101110011110101010011010110100011000001001011011100111101010100110101111
echo 011110010010011000011111000111101000000011110111100100100110000111110001111010000000111101111001001001100001111100011110100000001111011110010010011000011111000111101000000011110111100100100110000111110001111010000000111100
echo 000001111111000101001000011111101110010110000000011111110001010010000111111011100101100000000111111100010100100001111110111001011000000001111111000101001000011111101110010110000000011111110001010010000111111011100101100010
echo 100010010100101001011111100010101101000110111000100101001010010111111000101011010001101110001001010010100101111110001010110100011011100010010100101001011111100010101101000110111000100101001010010111111000101011010001101100
echo 010001110111100000001001101010100111110011010100011101111000000010011010101001111100110101000111011110000000100110101010011111001101010001110111100000001001101010100111110011010100011101111000000010011010101001111100110101
echo 011000100111111000011000111011010011000111000110001001111110000110001110110100110001110001100010011111100001100011101101001100011100011000100111111000011000111011010011000111000110001001111110000110001110110100110001110010
echo 000011010111011100111001100100100011100001110000110101110111001110011001001000111000011100001101011101110011100110010010001110000111000011010111011100111001100100100011100001110000110101110111001110011001001000111000011111
echo 001110000110011001101000111010010111101110000011100001100110011010001110100101111011100000111000011001100110100011101001011110111000001110000110011001101000111010010111101110000011100001100110011010001110100101111011100010
echo 000111011110111010000000101011100101110000110001110111101110100000001010111001011100001100011101111011101000000010101110010111000011000111011110111010000000101011100101110000110001110111101110100000001010111001011100001100
goto Matrix3
REM MATRIX END---------------------------------------------------------------------------------------------------------------------------------------------------
:menuselect4
REM FILE INFORMATION START---------------------------------------------------------------------------------------------------------------------------------------
cls
title File Information
color 0a
echo.
echo This batch file's full path is %~dpnx0
echo This batch file's filename is %~nx0
echo This batch file's timestamp is %~t0
echo This batch file's size in bytes is %~z0
echo.
echo  This file was created on a bored Tuesday night: October 20th, 2015 by
echo  Zachary Kline.
echo.
echo  Please contact me if any information of importance surfaces, 
echo  including bugs and suggestions (which I will consider)
echo  Email: thefuzzyfish2@gmail.com
pause>nul
goto GUI0
REM FILE INFORMATION END-----------------------------------------------------------------------------------------------------------------------------------------
:menuselect5
REM CRASH START--------------------------------------------------------------------------------------------------------------------------------------------------
cls
color 0a
title SYSTEM CRASH IMMINENT
cls
echo.
echo  You have about 5 seconds to cancel this program.
echo  If you don't, all work will be lost.
ping localhost -n 7 >nul
:crash5
color 0c
cls
echo SYSTEM CRASH IMMINENT
color c0
cls
echo SYSTEM CRASH IMMINENT
start "%~nx0"
start "%~nx0"
start "%~nx0"
start "%~nx0"
start "%~nx0"
start "%~nx0"
start "%~nx0"
start "%~nx0"
start "%~nx0"
start "%~nx0"
goto crash5
REM CRASH END----------------------------------------------------------------------------------------------------------------------------------------------------
:menuselect6
REM DEBUGGER START-----------------------------------------------------------------------------------------------------------------------------------------------
cls
title Debugger
color 0a
echo.
echo  If you do not exactly know what this does, I suggest you leave it alone.
echo  This protocal is meant to fix any issues you may be having with your Folder Locker protocal.
echo.
echo  Do you want to continue? (Y/N)
set/p "debuggerchoice= >"
if %debuggerchoice%==Y goto debuggercontinue
if %debuggerchoice%==y goto debuggercontinue
if %debuggerchoice%==N goto GUI0
if %debuggerchoice%--n goto GUI0
cls
echo.
echo  Invalid choice.
ping localhost -n 3 >nul
goto menuselect6
:debuggercontinue
cls
color 0a
title Debugger
echo.
echo Debugging...
cd %~dp0
attrib -r * /s
cls
echo.
echo  Debugging complete.
ping localhost -n 3 >nul
goto GUI0
REM DEBUGGER END-------------------------------------------------------------------------------------------------------------------------------------------------
:menuselect7
REM SHUTDOWN START-----------------------------------------------------------------------------------------------------------------------------------------------
cls
color 0a
echo.
echo  Are you sure you want to shut down? (Y/N)
set /p "rebootchoice= >"
if %rebootchoice%==Y goto continue7
if %rebootchoice%==y goto continue7
if %rebootchoice%==N goto GUI0
if %rebootchoice%==n goto GUI0
cls
echo.
echo  Invalid entry.
ping localhost -n 3 >nul
goto menuselect7
:continue7
shutdown /s /t 0
goto end
REM SHUTDOWN END-------------------------------------------------------------------------------------------------------------------------------------------------
:menuselect8
REM REBOOT START-------------------------------------------------------------------------------------------------------------------------------------------------
cls
color 0a
echo.
echo  Are you sure you want to reboot? (Y/N)
set /p "rebootchoice= >"
if %rebootchoice%==Y goto continue8
if %rebootchoice%==y goto continue8
if %rebootchoice%==N goto GUI0
if %rebootchoice%==n goto GUI0
cls
echo.
echo  Invalid entry.
ping localhost -n 3 >nul
goto menuselect8
:continue8
shutdown /r /t 0
goto end
REM REBOOT END---------------------------------------------------------------------------------------------------------------------------------------------------
:menuselect9
REM MORE OPTIONS START-------------------------------------------------------------------------------------------------------------------------------------------
cls
color 1f
title Swiss Batch File
echo.
echo  (1) NetStat
echo  (2) NetView
echo  (3) Exit
echo  (4) Go back
echo.
set/p "secondmenuselect=>"
if %secondmenuselect%==1 goto menuselect21
if %secondmenuselect%==2 goto menuselect22
if %secondmenuselect%==3 goto end
if %secondmenuselect%==4 goto GUI0
:invalid2
cls
color 4f
echo.
echo  The choice you have entered is not an option.
echo  Please try again.
ping localhost -n 5 >nul
goto menuselect9
REM MORE OPTIONS END---------------------------------------------------------------------------------------------------------------------------------------------
:menuselect21
REM NETSTAT START------------------------------------------------------------------------------------------------------------------------------------------------
cls
color 0a
title Netstat
echo.
echo  What you do with this information is not a concern of mine.
ping localhost -n 3 >nul
netstat
echo.
echo  Press any key to go back to the menu.
pause>nul
goto GUI0
REM NETSTAT END--------------------------------------------------------------------------------------------------------------------------------------------------
:menuselect22
REM NETVIEW START------------------------------------------------------------------------------------------------------------------------------------------------
cls
color 0a
title Net View
echo.
echo  What you do with this information is not a concern of mine.
ping localhost -n 3 >nul
net view
echo.
echo  Press any key to go back to the menu.
pause>nul
goto GUI0
:shittycomputercrash
REM SHITTYCOMPUTERCRASH START------------------------------------------------------------------------------------------------------------------------------------
cls
color 0a
echo.
echo  If you're on the school computers (I.E. If you're on a shitty computer)
echo  you can probably crash the system by generating all of these random numbers.
echo  Minimize this window now, and I'll take care of the rest :)
ping localhost -n 10 >nul
:shittycomputercrashfunction
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
echo %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%
goto shittycomputercrashfunction
REM SHITTYCOMPUTERCRASH END--------------------------------------------------------------------------------------------------------------------------------------
:end
cls
color 4f
ping localhost -n 1 >nul
exit
