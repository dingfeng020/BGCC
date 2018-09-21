perl -h >nul 2>&1
set lastError=%ERRORLEVEL%
IF %lastError% == 1 (
 ECHO perl 5.16 should been installed !
 EXIT 1
) 

set IDE_VS2010="%VS100COMNTOOLS%/../IDE/Devenv"

call "%VS100COMNTOOLS%/../../vc/vcvarsall.bat"
cd deps\openssl
if not exist output md output
perl Configure VC-WIN32 no-asm --prefix=./output
call ms\do_ms.bat
set cl=-wd4244
nmake -f ms\nt.mak vclean
nmake -f ms\nt.mak
nmake -f ms\nt.mak install
if not exist ..\..\output md ..\..\output
if not exist ..\..\output\lib md ..\..\output\lib
copy .\output\lib\libeay32.lib ..\..\output\lib\libeay32.lib
copy .\output\lib\ssleay32.lib ..\..\output\lib\ssleay32.lib
if not exist ..\..\output\include md ..\..\output\include
cd ..\..\output\include
xcopy ..\..\deps\openssl\output\include /e /y
cd ..\..\

%IDE_VS2010% "bgcc.sln" /rebuild Release /project bgcc
%IDE_VS2010% "bgcc.sln" /build Debug /project bgcc
%IDE_VS2010% "bgcc.sln" /rebuild Release /project bgcc-MD
%IDE_VS2010% "bgcc.sln" /rebuild Debug /project bgcc-MD

%IDE_VS2010% "bgcc.sln" /build Release /project bidl2sl
