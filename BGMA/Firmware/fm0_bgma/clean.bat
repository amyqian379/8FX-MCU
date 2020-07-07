echo Clean project output files
echo Start clean, Please wait for......

rmdir /q/s IAR\output\debug\exe
rmdir /q/s IAR\output\debug\list
rmdir /q/s IAR\output\debug\obj

rmdir /q/s IAR\output\release\exe
rmdir /q/s IAR\output\release\list
rmdir /q/s IAR\output\release\obj

echo Clean complete!
pause
