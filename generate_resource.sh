#! /bin/sh
workpath=$(cd `dirname $0`; pwd)
cd $workpath/tool
./image_qrc_generator ../image
mv $workpath/ResourceImageList.js $workpath/script