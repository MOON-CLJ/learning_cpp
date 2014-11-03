#include <iostream>
#include <dirent.h>
#include <sys/stat.h>

#include "queue.h"

int main() {
    DIR* dirp=NULL;
    struct dirent *drnt = NULL;
    struct stat st;
    queue<std::string> myqueue;
    myqueue.enqueue(std::string("/tmp"));
    char abs_p[300];
    char parent_p[300];
    while (!myqueue.isEmpty()) {
        strcpy(parent_p, myqueue.dequeue().c_str());
        dirp = opendir(parent_p);
        if (dirp) {
            std::cout << parent_p << " |" << std::endl;
            while ((drnt = readdir(dirp)) != NULL) {
                std::cout << " -" << drnt->d_name << std::endl;
                if ((strcmp(drnt->d_name, ".") == 0) || (strcmp(drnt->d_name, "..") == 0))
                    continue;
                memset(abs_p, 0, sizeof(abs_p));
                strcpy(abs_p, parent_p);
                strcat(abs_p, "/");
                strcat(abs_p, drnt->d_name);
                if ((stat(abs_p, &st) == 0) && ((st.st_mode & S_IFDIR) != 0))
                    myqueue.enqueue(std::string(abs_p));
            }
            std::cout << std::endl;
            closedir(dirp);
        }
    }
    return 0;
}
