#include "file_util.h"
#include <stdio.h>
#include <sys/stat.h>
#include <string>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <io.h>

// to fix warning like: warning C4996: 'access': The POSIX name for this item is deprecated.
#define access _access
#define stat _stat
#define S_IFDIR _S_IFDIR
#elif __ANDROID__
#include <dirent.h>
#include <unistd.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#elif __APPLE__
#endif




#ifdef _WIN32

#elif __ANDROID__
// http ://www.50ply.com/blog/2013/01/19/loading-compressed-android-assets-with-file-pointer/

extern ANativeActivity* g_pNativeActivity;

int android_read(void* cookie, char* buf, int size);
int android_write(void* cookie, const char* buf, int size);
fpos_t android_seek(void* cookie, fpos_t offset, int whence);
int android_close(void* cookie);
FILE* android_fopen(const char* fname, const char* mode)
{
    if (mode[0] == 'w') return NULL;

    AAsset* asset = AAssetManager_open(g_pNativeActivity->assetManager, fname, AASSET_MODE_UNKNOWN);
    if (!asset) return NULL;

    return funopen(asset, android_read, android_write, android_seek, android_close);
}


int android_read(void* cookie, char* buf, int size)
{
    return AAsset_read((AAsset*)cookie, buf, size);
}

int android_write(void* cookie, const char* buf, int size)
{
    return EACCES; // can't provide write access to the apk
}

fpos_t android_seek(void* cookie, fpos_t offset, int whence)
{
    return AAsset_seek((AAsset*)cookie, offset, whence);
}

int android_close(void* cookie)
{
    AAsset_close((AAsset*)cookie);
    return 0;
}


#elif __APPLE__
#endif




bool FileUtil::MkFile(const std::string& file)
{
    FILE* pFile = fopen(file.c_str(), "w");

    // errno is used for c++ runtime library. GetLastError is used for windows api, like CreateFile
    if(NULL == pFile)
        return false;
    fclose(pFile);
    return true;
}

bool FileUtil::RmFile(const std::string& file)
{
    if(0 == remove(file.c_str()))
        return true;

    return false;
}

bool FileUtil::IsFileExist(const std::string& file)
{
    //00: existence, 02:w, 04:r, 06:wr
    if (-1 == access(file.c_str(), 0))
    {
        return false;
    }

    return true;
}

bool FileUtil::IsFile(const std::string& file)
{
#ifdef _WIN32
    struct __stat64 buf;

    // ENOENT, EINVAL
    if(0 != _stat64(file.c_str(), &buf))
        return false;

    if (_S_IFMT&buf.st_mode)
        return true;

#elif __ANDROID__

    struct stat buf;

    // ENOENT, EINVAL
    throw_assert(0 == stat(file.c_str(), &buf), "errno:" << errno);
    if (S_IFMT&buf.st_mode)
        return true;
#elif __APPLE__
#endif

    return false;
}

sint64 FileUtil::GetFileSize(const std::string& file)
{

#ifdef _WIN32
    struct __stat64 buf;

    // ENOENT, EINVAL
    if(0 != _stat64(file.c_str(), &buf))
        return 0;

    return buf.st_size;

#elif __ANDROID__
    struct stat buf;
    throw_assert(0 == stat(file.c_str(), &buf), "errno:" << errno);
    return buf.st_size;
#elif __APPLE__
#endif
}


bool FileUtil::MkDir(const std::string& val)
{
    std::string tmp_dir = SlashTrim(val, false);
    if(IsDirExist(tmp_dir))
        return true;

    size_t len = tmp_dir.length();
    MN::AutoMem<char, 512> tmpDirPath(len+1);
    char* pTmpDir = tmpDirPath.GetBuf();
    strcpy(pTmpDir, tmp_dir.c_str());

    // create the pre dir.
    for(size_t i=0; i<len; i++)
    {
        if('\\' == pTmpDir[i])
        {
            pTmpDir[i] = '\0';

            //check whether dir is exist
            if(IsDirExist(pTmpDir))
            {
                pTmpDir[i] = '\\';
                continue;
            }

#ifdef _WIN32
            if(_mkdir(pTmpDir) != 0)
                return false;
#elif __ANDROID__
            throw_assert(mkdir(pTmpDir, 777) == 0, "make dir:" << pTmpDir << "error.errno:" << errno);
#elif __APPLE__
#endif

            pTmpDir[i] = '\\';
        }
    }

#ifdef _WIN32
    if(_mkdir(pTmpDir) != 0)
        return false;

#elif __ANDROID__
    throw_assert(mkdir(pTmpDir, 777) == 0, "make dir:" << pTmpDir << "error.errno:" << errno);
#elif __APPLE__
#endif

    return true;
}

bool FileUtil::RmDir(const std::string& dir)
{
    //dir is end of slash
    std::string strTmpDirPath = SlashTrim(dir, true);
#ifdef _WIN32
    strTmpDirPath += "*.*";

    int hasfile=-1;
    std::string path;
    struct _finddatai64_t c_file;
    intptr_t handle = _findfirsti64(strTmpDirPath.c_str(), &c_file);
    if(-1 == handle)
        return false;

    do
    {
        if((strcmp(c_file.name, ".") !=0 )
            && (strcmp(c_file.name, "..") != 0))
        {
            path =dir + "\\" + std::string(c_file.name);

            if(c_file.attrib & _A_SUBDIR)
            {
                RmDir(path);
            }
            else
            {
                RmFile(path);
            }
        }

        hasfile=_findnexti64(handle, &c_file);
    }
    while(0 == hasfile);

    _findclose(handle);
    if(-1 == _rmdir(dir.c_str()))
        return false;

#elif __ANDROID__
    std::string path;
    struct dirent *ent = NULL;
    DIR* pDir = opendir(strTmpDirPath.c_str());
    throw_assert(pDir != NULL, "opendir failed:" << strTmpDirPath.c_str());

    while ((ent = readdir(pDir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
        {
            path = dir + "/" + std::string(ent->d_name);

            if (ent->d_type & DT_DIR)
            {
                RmDir(path);
            }
            else
            {
                RmFile(path);
            }
        }
    }

    closedir(pDir);
    throw_assert(-1 != rmdir(dir.c_str()), "remove dir:" << path << "error. errorno:" << errno);

#elif __APPLE__
#endif

    return true;
}


bool FileUtil::RenameDir(const std::string& old_name, std::string& new_name)
{
    if(!IsDirExist(old_name))
        return false;

    if(0 != rename(old_name.c_str(), new_name.c_str()))
        return false;

    return true;
}

bool IsDir(const std::string& dir)
{
    struct stat _buf;
    int nRet = stat(dir.c_str(), &_buf);

    // ENOENT, EINVAL
    if(0 != nRet)
        return false;

    if(S_IFDIR&_buf.st_mode)
        return true;

    return false;
}

bool FileUtil::IsDirExist(const std::string& dir)
{
    if(-1 == access(dir.c_str(), 0))
    {
        return false;
    }

    return true;
}

bool FileUtil::CopySingleFile(const std::string& dst, const std::string& src)
{
    //use fopen or iostream to non-platform specific
    std::string dstPath = FileUtil::GetPrePath(dst);
    if (!FileUtil::IsDirExist(dstPath))
        FileUtil::MkDir(dstPath);

    FILE* pSrc = fopen(src.c_str(), "rb");
    FILE* pDst = fopen(dst.c_str(), "wb");
    int i;
    for (i = getc(pSrc); i != EOF; i = getc(pSrc))
    {
        putc(i, pDst);
    }
    fclose(pDst);
    fclose(pSrc);
    return true;

#ifdef _WIN32
    //use windows api:copyfile
    if(false == ::CopyFileA(src.c_str(), dst.c_str(), false))
    {
        //copy fail, mayge the dir is not exist.
        std::string str_file(dst);
        int index=(int)str_file.find_last_of('\\');
        std::string str_path=str_file.substr(0, index);
        if(!FileUtil::IsDirExist(str_path.c_str()))
        {
            FileUtil::MkDir(str_path.c_str());
            BOOL ret = ::CopyFileA(src.c_str(), dst.c_str(), false);
            if(!ret)
                return false;
        }
    }
#endif

    return true;
}

bool FileUtil::CopyDir(const std::string& dst, const std::string& src)
{

#ifdef _WIN32
    std::string strDst = SlashTrim(dst, false);
    std::string strSrc = SlashTrim(src, false);

    if(!IsDirExist(strDst))
    {
        MkDir(strDst);
    }

    int hasfile=-1;
    std::string dirpathwc = strSrc + "\\*.*";

    std::string strSubDst;
    std::string strSubSrc;
    struct _finddatai64_t c_file;
    intptr_t ret = _findfirsti64(dirpathwc.c_str(), &c_file);
    if(-1 == ret)
        return false;

    do
    {
        if(strcmp(c_file.name, ".")!=0 && strcmp(c_file.name, "..") != 0)
        {
            strSubDst = strDst + "\\" + std::string(c_file.name);
            strSubSrc = strSrc + "\\" + std::string(c_file.name);

            if(c_file.attrib & _A_SUBDIR)
            {
                CopyDir(strSubDst, strSubSrc);
            }
            else
            {
                CopySingleFile(strSubDst, strSubSrc);
            }
        }

        hasfile=_findnexti64(ret, &c_file);
    }
    while(0 == hasfile);

    _findclose(ret);
    return true;

#elif __ANDROID__
    std::string strDst = SlashTrim(dst, false);
    std::string strSrc = SlashTrim(src, false);
    std::string strSubDst;
    std::string strSubSrc;

    if (!IsDirExist(strDst))
    {
        MkDir(strDst);
    }

    std::string path;
    struct dirent *ent = NULL;
    DIR* pDir = opendir(strSrc.c_str());
    throw_assert(pDir != NULL, "opendir failed:" << strSrc.c_str());

    while ((ent = readdir(pDir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
        {
            strSubDst = strDst + "\\" + std::string(ent->d_name);
            strSubSrc = strSrc + "\\" + std::string(ent->d_name);

            if (ent->d_type & DT_DIR)
            {
                CopyDir(strSubDst, strSubSrc);
            }
            else
            {
                CopyFile(strSubDst, strSubSrc);
            }
        }
    }

    closedir(pDir);

#elif __APPLE__
#endif
}


std::string FileUtil::ExePath()
{
#ifdef _WIN32

    char buffer[1024];
    GetModuleFileNameA(NULL, buffer, 1024);
    std::string::size_type pos = std::string(buffer).find_last_of("\\");
    return std::string(buffer).substr(0, pos);
#elif __ANDROID__
    char buffer[1024];
    ssize_t res = readlink("/proc/self/exe", buffer, 1024);
    if ((res < 0) || (res >= 1024))
    {
        buffer[0] = 0;
        return false;
    }

    buffer[res] = 0;
    return buffer;
#elif __APPLE__
#endif

}

std::string FileUtil::GetPrePath(const std::string& path)
{
    std::string strTmp = SlashTrim(path, false);
    std::string::size_type pos = strTmp.find_last_of( "\\" );
    return strTmp.substr( 0, pos);
}


std::string FileUtil::GetFileNameFromPath(const std::string& path)
{
    std::string strTmp = SlashTrim(path, false);
    std::string::size_type pos = strTmp.find_last_of("\\");
    return strTmp.substr(pos+1);
}


std::string FileUtil::SlashTrim(const std::string& val, bool slash_end)
{
    int strLen = (int)val.length();
    MN::AutoMem<char, 512> auto_mem(strLen + 2);
    char* data = auto_mem.GetBuf();
    strcpy(data, val.c_str());

    // "/" 统一转换成"\\"
    for(int i=0; i<strLen; i++)
    {
        char tmp=*(data+i);
        if('/'==tmp)
            data[i]='\\';
        else
            data[i]=tmp;
    }

    // should end with "\\"
    if(slash_end)
    {
        if(data[strLen-1] != '\\')
        {
            data[strLen]='\\';
            data[strLen+1]='\0';
        }
        else
        {
            data[strLen]='\0';
        }
    }
    // no need to end with "\\"
    else    
    {
        if(data[strLen-1] != '\\')
        {
            data[strLen]='\0';
        }
        else
        {
            data[strLen-1]='\0';
        }
    }


    return data;
}

