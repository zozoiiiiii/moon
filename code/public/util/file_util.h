/************************************************************************/
/*
@author:   [junliang]
@time:     [8/7/2019]
@desc:     file utility
*/
/************************************************************************/
#pragma once

#include <string>
#include "public/object/mn_type.h"
#include "public/object/mn_memory.h"

class FileUtil
{
public:
    static bool MkFile(const std::string& file);
    static bool RmFile(const std::string& file); // will not backup in recycle bin.
    static bool IsFileExist(const std::string& file);
    static bool IsFile(const std::string& file);
    static sint64 GetFileSize(const std::string& file);
    static bool CopySingleFile(const std::string& dst, const std::string& src);

    static bool MkDir(const std::string& dir);
    static bool RmDir(const std::string& dir); // will not backup in recycle bin.
    static bool RenameDir(const std::string& old_name, std::string& new_name);
    static bool IsDir(const std::string& dir);
    static bool IsDirExist(const std::string& dir);
    static bool CopyDir(const std::string& dst, const std::string& src);

    static std::string ExePath();

    //f:\misc\util_file.h -> f:\misc
    //f:\inc\misc\ -> f:\inc
    //f:\inc\misc  -> f:\inc
    static std::string GetPrePath(const std::string& path);
    static std::string GetFileNameFromPath(const std::string& path);

    // windows:"\\", linux: "/"
    static std::string SlashTrim(const std::string& val, bool slash_end=false);
};