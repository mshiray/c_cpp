#include <windows.h>
#include <stdio.h>
#include <string.h>

#define SIGNATURE1 "GIF89a"
#define SIGNATURE2 "GIF87a"
#define SIG_LEN 6

void process_file(const char *filepath)
{
    FILE *fp = fopen(filepath, "rb");
    if (!fp)
        return;

    char buf[SIG_LEN];
    size_t n = fread(buf, 1, SIG_LEN, fp);
    fclose(fp);

    if (n == SIG_LEN && 
        (memcmp(buf, SIGNATURE1, SIG_LEN) == 0 || memcmp(buf, SIGNATURE2, SIG_LEN) == 0))
    {
        // Rename .jpg to .gif
        char newname[MAX_PATH];
        strcpy(newname, filepath);
        char *ext = strrchr(newname, '.');
        if (ext && _stricmp(ext, ".jpg") == 0)
        {
            strcpy(ext, ".gif");
            if (MoveFile(filepath, newname))
            {
                printf("Renamed: %s -> %s\n", filepath, newname);
            }
            else
            {
                printf("Failed to rename: %s\n", filepath);
            }
        }
    }
}

void scan_dir(const char *dir)
{
    char search[MAX_PATH];
    snprintf(search, MAX_PATH, "%s\\*", dir);

    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(search, &fd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0)
            continue;

        char path[MAX_PATH];
        snprintf(path, MAX_PATH, "%s\\%s", dir, fd.cFileName);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            scan_dir(path);
        }
        else
        {
            char *ext = strrchr(fd.cFileName, '.');
            if (ext && _stricmp(ext, ".jpg") == 0)
            {
                process_file(path);
            }
        }
    } while (FindNextFile(hFind, &fd));
    FindClose(hFind);
}

int main()
{
    char cwd[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, cwd);
    scan_dir(cwd);
    return 0;
}