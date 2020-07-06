echo OFF
echo -------------------------------------------------------
echo USB Driver installation batch file for ICE.
echo    COPYRIGHT (c) 2014-2015 Spansion
echo    (Ver.20150414-01)
echo -------------------------------------------------------

REM ----------Change Directory-----------
cd /d %~dp0%
IF %ERRORLEVEL% NEQ 0 goto ERR_UNC

REM --------------Check OS---------------
:CHECK_NT
IF "%OS%" NEQ "Windows_NT" goto ERR_OLDOS

:CHECK_PROCESSOR
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" goto W64_WD
if "%PROCESSOR_ARCHITECTURE%" == "x86" goto W32_WD
goto ERR_UKMCU

:W32_WD
if "%PROCESSOR_ARCHITEW6432%" EQU "" goto W32_WD32

:W32_WD64
if "%PROCESSOR_ARCHITEW6432%" EQU "AMD64" goto W32_WDAMD64

:W32_WDUK64
goto ERR_UKARCHI

REM ---- 64bit process on 64bit OS. ----
:W64_WD
REM Do Install for 64bit OS.
goto INSTALL_64BIT

REM ---- 32bit process on 64bit OS. ----
:W32_WDAMD64
REM 32bit process on 64bit OS. Do Install.
goto INSTALL_64BIT

REM ---- 32bit process on 32bit OS. ----
:W32_WD32
REM Do Install for 32bit OS.
goto INSTALL_32BIT


REM ---------Install for 64bit OS--------
:INSTALL_64BIT
IF NOT EXIST .\64bit\NUL goto ERR_64BITOS

echo --------------------------------
echo Start installation for 64bit OS.
echo --------------------------------
cd 64bit
wdreg.exe -silent -inf windrvr6.inf    install
IF %ERRORLEVEL% NEQ 0 goto WDFAIL64
wdreg.exe -silent -inf SiUSBd_wdrv.inf install
IF %ERRORLEVEL% NEQ 0 goto SIUSBFAIL64
copy /Y .\wdapi1150_32.dll %windir%\sysWOW64\wdapi1150.dll
IF %ERRORLEVEL% NEQ 0 goto ERR_DLLCOPY64
cd ..
goto SUCCESSEND

:ERR_DLLCOPY64
cd ..
goto ERR_DLLCOPY

:WDFAIL64
cd ..
goto WDFAIL

:SIUSBFAIL64
cd ..
goto SIUSBFAIL

REM ---------Install for 32bit OS--------
:INSTALL_32BIT
echo --------------------------------
echo Start installation for 32bit OS.
echo --------------------------------
wdreg.exe -silent -inf windrvr6.inf    install
IF %ERRORLEVEL% NEQ 0 goto WDFAIL
wdreg.exe -silent -inf SiUSBd_wdrv.inf install
IF %ERRORLEVEL% NEQ 0 goto SIUSBFAIL
copy /Y .\wdapi1150.dll %windir%\system32\wdapi1150.dll
IF %ERRORLEVEL% NEQ 0 goto ERR_DLLCOPY
goto SUCCESSEND

REM -------Normal End---------
:SUCCESSEND
echo ---------------------------------
echo Installation success!
echo ---------------------------------
IF NOT EXIST .\Bin\NUL goto SUCCESSE_2
echo ---------------------------------
echo   When you use the new driver,
echo   please update the DLL files
echo   in "Bin" folder as below.
echo ---------------------------------
dir .\Bin

:SUCCESSE_2
goto EXIT

REM -------Error End---------
:ERR_UNC
echo =================================================
echo ** INSTALLATION FAILED                         **
echo **  This program cannot use on network.        **
echo **  Please copy the files to your local drive. **
echo =================================================
goto FAILEND

:ERR_OLDOS
echo =========================================================
echo ** INSTALLATION FAILED                                 **
echo **   Can not be installed on this OS(%OS%).       **
echo =========================================================
goto FAILEND

:ERR_UKARCHI
echo =================================
echo ** INSTALLATION FAILED         **
echo **   "%PROCESSOR_ARCHITEW6432%" is not supported.  **
echo =================================
goto FAILEND

:ERR_UKMCU
echo =================================
echo ** INSTALLATION FAILED         **
echo **   "%PROCESSOR_ARCHITECTURE%" is not supported.  **
echo =================================
goto FAILEND

:ERR_64BITOS
echo ======================================
echo ** INSTALLATION FAILED              **
echo **   Can not install to 64bit OS.   **
echo ======================================
goto FAILEND


:ERR_DLLCOPY
echo ====================================
echo ** INSTALLATION FAILED(WDAPI-DLL) **
echo ====================================
goto FAILEND

:SIUSBFAIL
echo ==========================================
echo ** INSTALLATION FAILED(SiUSBd_wdrv.inf) **
echo ==========================================
goto FAILEND

:WDFAIL
echo =======================================
echo ** INSTALLATION FAILED(windrvr6.inf) **
echo =======================================

:FAILEND

:EXIT
PAUSE
