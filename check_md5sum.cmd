@echo off
set md5sum=36b72c25de983078b68625b7610e7673
.\Release\ip_filter.exe < .\ip_filter.tsv > output.txt
set answer=
for /f "skip=1 tokens=* delims=" %%# in ('certutil -hashfile "output.txt" MD5') do (
	if not defined answer (
		for %%Z in (%%#) do set "answer=%%Z"
	)
)
del /F /Q .\output.txt
if "%answer%"=="%md5sum%" ( set err=1 ) else ( set err=0 )
exit /B %err%
