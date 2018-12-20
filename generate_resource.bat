@echo off
set workpath=%~dp0
cd %workpath%\tool
call image_qrc_generator.exe ..\image
copy ..\ResourceImageList.js ..\script\ResourceImageList.js
del ..\ResourceImageList.js
cd %workpath%