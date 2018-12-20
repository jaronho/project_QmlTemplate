#if defined(win32) || defined(_win32) || defined(WIN32) || defined(_WIN32) || \
    defined(win64) || defined(_win64) || defined(WIN64) || defined(_WIN64)
#define _SYSTEM_WINDOWS_
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#ifdef _SYSTEM_WINDOWS_
#include <direct.h>
#include <io.h>
#include <windows.h>
#pragma warning(disable: 4996)
#else
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#endif

#define NAME_SIZE		128		/* 目录名字符最大数 */

static std::vector<std::string> splitString(std::string str, const std::string& pattern) {
    std::vector<std::string> result;
    if (str.empty() || pattern.empty()) {
        return result;
    }
    str.append(pattern);
    std::string::size_type pos;
    for (size_t i = 0; i < str.size(); ++i) {
        pos = str.find(pattern, i);
        if (pos < str.size()) {
            result.push_back(str.substr(i, pos - i));
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

static std::string replaceString(std::string str, const std::string& rep, const std::string& dest) {
    if (str.empty() || rep.empty()) {
        return str;
    }
    std::string::size_type pos = 0;
    while (std::string::npos != (pos = str.find(rep, pos))) {
        str.replace(pos, rep.size(), dest);
        pos += dest.size();
    }
    return str;
}

static std::string revisalPath(std::string path) {
    if (path.empty()) {
        return path;
    }
    path = replaceString(path, "\\", "/");
    path = replaceString(path, "//", "/");
    if ('/' == path.at(path.size() - 1)) {
        return path.substr(0, path.size() - 1);
    }
    return path;
}

static void searchFile(std::string dirName, const std::vector<std::string>& extList,
    std::function<void(const std::string& fileName,
        unsigned long fileSize,
        long createTime,
        long writeTime,
        long accessTime)> callback,
    bool recursive) {
    if (!callback) {
        return;
    }
    dirName = revisalPath(dirName);
#ifdef _SYSTEM_WINDOWS_
    _finddata_t fileData;
    int handle = _findfirst((dirName + "/*.*").c_str(), &fileData);
    if (-1 == handle || !(_A_SUBDIR & fileData.attrib)) {
        return;
    }
    while (0 == _findnext(handle, &fileData)) {
        if (0 == strcmp(".", fileData.name) || 0 == strcmp("..", fileData.name)) {
            continue;
        }
        std::string subName = dirName + "/" + fileData.name;
        /* is sub directory */
        if (_A_SUBDIR & fileData.attrib) {
            if (recursive) {
                searchFile(subName, extList, callback, true);
            }
            continue;
        }
        /* all file type */
        if (extList.empty()) {
            callback(subName, fileData.size, fileData.time_create, fileData.time_write, fileData.time_access);
            continue;
        }
        /* specific file type */
        std::string::size_type index = subName.find_last_of(".");
        if (std::string::npos == index) {
            continue;
        }
        std::string ext = subName.substr(index, subName.size() - index);
        for (size_t i = 0; i < extList.size(); ++i) {
            if (extList[i] == ext) {
                callback(subName, fileData.size, fileData.time_create, fileData.time_write, fileData.time_access);
            }
        }
    }
    _findclose(handle);
#else
    DIR* dir = opendir(dirName.c_str());
    if (!dir) {
        return;
    }
    struct dirent* dirp = NULL;
    while (dirp = readdir(dir)) {
        if (0 == strcmp(".", dirp->d_name) || 0 == strcmp("..", dirp->d_name)) {
            continue;
        }
        std::string subName = dirName + "/" + dirp->d_name;
        DIR* subDir = opendir(subName.c_str());
        if (NULL == subDir) {
            struct stat fileStat;
            if (0 != stat(subName.c_str(), &fileStat)) {
                continue;
            }
            if (extList.empty()) {
                callback(subName, fileStat.st_size, fileStat.st_ctime, fileStat.st_mtime, fileStat.st_atime);
                continue;
            }
            std::string::size_type index = subName.find_last_of(".");
            if (std::string::npos == index) {
                continue;
            }
            std::string ext = subName.substr(index, subName.size() - index);
            for (size_t i = 0; i<extList.size(); ++i) {
                if (extList[i] == ext) {
                    callback(subName, fileStat.st_size, fileStat.st_ctime, fileStat.st_mtime, fileStat.st_atime);
                }
            }
            continue;
        }
        closedir(subDir);
        if (recursive) {
            searchFile(subName, extList, callback, true);
        }
    }
    closedir(dir);
#endif
}

static std::vector<std::string> stripFileInfo(const std::string& filePath) {
    std::string dirname = "", filename = filePath, basename = "", extname = "";
    size_t pos = filePath.find_last_of("/\\");
    if (pos < filePath.size()) {
        dirname = filePath.substr(0, pos + 1);
        filename = filePath.substr(pos + 1, filePath.size() - 1);
    }
    pos = filename.find_last_of(".");
    if (pos < filename.size()) {
        basename = filename.substr(0, pos);
        extname = filename.substr(pos, filename.size() - 1);
    }
    std::vector<std::string> infos;
    infos.push_back(dirname);
    infos.push_back(filename);
    infos.push_back(basename);
    infos.push_back(extname);
    return infos;
}

static std::string getParentDir(std::string dir) {
    if (dir.empty()) {
#ifdef _SYSTEM_WINDOWS_
        char* buffer = _getcwd(NULL, 0);
#else
        char* buffer = getcwd(NULL, 0);
#endif
        if (!buffer) {
            return "";
        }
        dir = buffer;
        free(buffer);
    }
    if (dir.length() > 0 && '/' == dir[dir.length() - 1]) {
        dir.pop_back();
    }
    std::string::size_type pos = dir.find_last_of('/');
    if (std::string::npos == pos) {
        return dir;
    }
    return dir.substr(0, pos + 1);
}

static std::vector<std::string> imageList;

int main(int argc, char* argv[]) {
    char path[NAME_SIZE] = { 0 };
    /* 目录名称 */
    if (2 == argc) {	/* 读取目录名 */
        if (strlen(argv[1]) > NAME_SIZE) {
            memcpy(path, argv[1], NAME_SIZE);
        }
        else {
            memcpy(path, argv[1], strlen(argv[1]));
        }
    }
    else {				/* 输入目录名 */
        printf("please input image directory: ");
        scanf("%s", (char*)&path);
    }
    printf("directory: \"%s\"\n", path);
    std::string dir(path);
    dir = revisalPath(dir);
    /* 搜索文件 */
    std::vector<std::string> extList;
    searchFile(dir, extList, [](const std::string& fileName, unsigned long fileSize, long createTime, long writeTime, long accessTime)->void {
        imageList.push_back(fileName);
    }, true);
    /* 文件名排序 */
    std::sort(imageList.begin(), imageList.end(), [](const std::string& v1, const std::string& v2)->bool {
        return v1 < v2;
    });
    /* 字符串组装 */
    std::vector<std::string> dirInfo = splitString(dir, "/");
    std::string fileName;
    if (dirInfo.size() > 0) {
        fileName = dirInfo[dirInfo.size() - 1];
    }
    std::string bufferQRC;
    bufferQRC += "<RCC>\n";
    bufferQRC += "    <qresource prefix=\"/\">\n";
    std::string bufferJS;
    bufferJS += ".pragma library\n";
    bufferJS += "var resource_image_list = [\n";
    for (size_t i = 0; i < imageList.size(); ++i) {
        std::vector<std::string> fileInfo = stripFileInfo(imageList[i]);
        std::string::size_type pos = fileInfo[0].find_first_of(fileName);
        std::string filePath = fileInfo[0].substr(pos) + fileInfo[1];
        bufferQRC += "        <file>" + filePath + "</file>\n";
        bufferJS += "\"" + filePath + "\"" + (i < imageList.size() - 1 ? "," : "") + "\n";
    }
    bufferQRC += "    </qresource>\n";
    bufferQRC += "</RCC>\n";
    bufferJS += "];";
    /* 写文件 */
    FILE* fpQRC = fopen((getParentDir(dir) + "/" + fileName + ".qrc").c_str(), "wb");
    if (fpQRC) {
        fwrite(bufferQRC.c_str(), bufferQRC.size(), sizeof(char), fpQRC);
        fflush(fpQRC);
        fclose(fpQRC);
    }
    FILE* fpJS = fopen((getParentDir(dir) + "/ResourceImageList.js").c_str(), "wb");
    if (fpJS) {
        fwrite(bufferJS.c_str(), bufferJS.size(), sizeof(char), fpJS);
        fflush(fpJS);
        fclose(fpJS);
    }
    return 0;
}