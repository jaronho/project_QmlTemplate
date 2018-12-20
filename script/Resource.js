/***********************************************************************
 ** Author:	jaron.ho
 ** Date:	2018-08-21
 ** Brief:  资源模块
 ***********************************************************************/
.pragma library
Qt.include("ResourceImageList.js")

if (!Array.indexOf) {
    Array.prototype.indexOf = function(obj) {
        for (var i = 0; i < this.length; ++i) {
            if (obj === this[i]) {
                return i;
            }
        }
        return -1;
    }
}

/* 字体大小 */
function fontSize(size, factor) {
    return size + ('number' === typeof(factor) ? factor : 0);
}

/* 图片路径 */
function urlimg(name, sizeType) {
    var fullPath = "";
    if (1 === sizeType) {
        fullPath = "image/middle/" + name;
    } else if (2 === sizeType) {
        fullPath = "image/large/" + name;
    }
    if (0 === fullPath.length || resource_image_list.indexOf(fullPath) < 0) {
        if (fullPath.length > 0) {
            console.log("can't file image file: \"" + fullPath + "\"");
        }
        fullPath = "image/default/" + name;
    }
    return "qrc:/" + fullPath;
}

/* qml路径 */
function urlqml(name) {
    return "qrc:/qml/" + name;
}

/* 着色器路径 */
function urlshader(name) {
    return "qrc:/shader/" + name;
}
