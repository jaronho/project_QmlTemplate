#! /bin/sh
# 当前工作路径
workpath=$(cd `dirname $0`; pwd)
# 生成资源文件
cd $workpath/tool
./image_qrc_generator ../image
mv $workpath/ResourceImageList.js $workpath/script