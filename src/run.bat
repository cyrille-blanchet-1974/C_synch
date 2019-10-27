@echo off
set HD=D
goto cherche_WD

:cherche_WD
set WD=E
if exist %WD%:\WD.flg goto sauve 
set WD=F
if exist %WD%:\WD.flg goto sauve
set WD=G
if exist %WD%:\WD.flg goto sauve
set WD=H
if exist %WD%:\WD.flg goto sauve
set WD=I
if exist %WD%:\WD.flg goto sauve
set WD=J
if exist %WD%:\WD.flg goto sauve
set WD=K
if exist %WD%:\WD.flg goto sauve
set WD=L
if exist %WD%:\WD.flg goto sauve
set WD=M
if exist %WD%:\WD.flg goto sauve
goto fin

:sauve
echo old
%WD%:\synch %HD%: %WD%:\portable    >oldexec.cmd
echo new
synch %HD%: %WD%:\portable          newexec.cmd
echo fini



:fin
pause





