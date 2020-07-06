echo OFF
echo -------------------------------------------------------
echo USB Driver UN-installation batch file for ICE.
echo    COPYRIGHT (c) Spansion LLC, 2014
echo    (Ver.20140415-02)
echo -------------------------------------------------------

REM ------ Temp variable ------
set TempStat=0

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
REM Do UN-Install for 64bit OS.
goto UNINSTALL_64BIT

REM ---- 32bit process on 64bit OS. ----
:W32_WDAMD64
REM 32bit process on 64bit OS. Do UN-Install.
goto UNINSTALL_64BIT

REM ---- 32bit process on 32bit OS. ----
:W32_WD32
REM Do Un-Install for 32bit OS.
goto UNINSTALL_32BIT


REM ---------UN-Install for 64bit OS--------
:UNINSTALL_64BIT
IF NOT EXIST .\64bit\NUL goto ERR_64BITOS

echo -----------------------------------
echo Start UN-installation for 64bit OS.
echo -----------------------------------
cd 64bit
wdreg.exe -inf SiUSBd_wdrv.inf uninstall
set TempStat=%ERRORLEVEL%
wdreg.exe -inf windrvr6.inf    uninstall
IF %ERRORLEVEL% NEQ 0 goto WDFAIL64
IF %TempStat% NEQ 0 goto SIUSBFAIL64
goto SUCCESSEND

:WDFAIL64
cd ..
goto WDFAIL

:SIUSBFAIL64
cd ..
goto SIUSBFAIL

REM ---------UN-Install for 32bit OS--------
:UNINSTALL_32BIT
echo -----------------------------------
echo Start UN-installation for 32bit OS.
echo -----------------------------------
wdreg.exe -inf SiUSBd_wdrv.inf uninstall
set TempStat=%ERRORLEVEL%
wdreg.exe -inf windrvr6.inf    uninstall
IF %ERRORLEVEL% NEQ 0 goto WDFAIL
IF %TempStat% NEQ 0 goto SIUSBFAIL
goto SUCCESSEND

REM -------Normal End---------
:SUCCESSEND
echo ------------------------
echo UN-Installation success!
echo ------------------------
goto EXIT


REM -------Error End---------
:ERR_UNC
echo =================================================
echo ** UN-INSTALLATION FAILED                      **
echo **  This program cannot use on network.        **
echo **  Please copy the files to your local drive. **
echo =================================================
goto FAILEND

:ERR_OLDOS
echo ============================================================
echo ** UN-INSTALLATION FAILED                                 **
echo **  Can not be installed on this OS(%OS%).       **
echo ============================================================
goto FAILEND

:ERR_UKARCHI
echo =================================
echo ** UN-INSTALLATION FAILED      **
echo **   "%PROCESSOR_ARCHITEW6432%" is not supported.  **
echo =================================
goto FAILEND

:ERR_UKMCU
echo =================================
echo ** UN-INSTALLATION FAILED      **
echo **   "%PROCESSOR_ARCHITECTURE%" is not supported.  **
echo =================================
goto FAILEND

:ERR_64BITOS
echo ======================================
echo ** UN-INSTALLATION FAILED           **
echo **   Can not Uninstall on 64bit OS. **
echo ======================================
goto FAILEND


:SIUSBFAIL
echo =============================================
echo ** UN-INSTALLATION FAILED(SiUSBd_wdrv.inf) **
echo =============================================
goto FAILEND

:WDFAIL
echo ==========================================
echo ** UN-INSTALLATION FAILED(windrvr6.inf) **
echo ==========================================

:FAILEND

:EXIT
PAUSE
