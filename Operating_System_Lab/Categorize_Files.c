#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void deleteNonFilesFolders(const char* dirPath) {
    DIR* dir;
    struct dirent* ent;
    char filePath[256];

    if ((dir = opendir(dirPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, ent->d_name);
                if (strstr(ent->d_name, "Files") == NULL) {
                    deleteNonFilesFolders(filePath);
                    char command1[100];
                    snprintf(command1, sizeof(command1), "rm -r %s", filePath);
                    system(command1);
                } else {
                    deleteNonFilesFolders(filePath);  // Recurse into the subdirectory
                }
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Error opening directory: %s\n", dirPath);
        exit(1);
    }
}


void createDirectory(const char* path) {
    char command1[100];
    snprintf(command1, sizeof(command1), "mkdir -p %s", path);
    system(command1);
}

void moveFile(const char* source, const char* extension) {
    char command2[100];
    snprintf(command2, sizeof(command2), "mv %s Categorize/%sFiles", source, extension);
    system(command2);
}

char* getFileExtension(const char* filename) {
    char* dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        return "";
    }
    return dot + 1;
}

void categorizeFile(const char* filename, const char* categorizedDir) {
    char* extension = getFileExtension(filename);
    char destinationPath[256];

    // Create a directory for the extension if it doesn't exist
    snprintf(destinationPath, sizeof(destinationPath), "%s/%sFiles", categorizedDir, extension);
    createDirectory(destinationPath);

    // Move the file to the corresponding directory
    char sourcePath[256];
    snprintf(sourcePath, sizeof(sourcePath), "%s/%s", categorizedDir, filename);
    snprintf(destinationPath, sizeof(destinationPath), "%s/%sFiles/%s", categorizedDir, extension, filename);
    moveFile(sourcePath, extension);
}

void processFiles(const char* dirPath, const char* categorizedDir, int depth) {
    DIR* dir;
    struct dirent* ent;
    char filePath[256];

    if ((dir = opendir(dirPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {  // Regular file
                snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, ent->d_name);
                int pid;
                pid = vfork();
                if (pid == 0) { 
                    categorizeFile(ent->d_name, categorizedDir);
                    remove(filePath);
                    exit(0);
                }
            } else if (ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 && depth > 0) {
                // Process subdirectories up to the specified depth
                snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, ent->d_name);
                
                
                processFiles(filePath, filePath, depth - 1);
                rmdir(filePath);  // Remove the empty directory after processing its contents
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Error opening directory: %s\n", dirPath);
        exit(1);
    }
}

int main() {
    const char* categorizedDir = "Categorize";  // Set your desired path here

    int depth;
    printf("Enter the depth of subfolders to check for files: ");
    scanf("%d", &depth);

    processFiles(categorizedDir, categorizedDir, depth);
    
    deleteNonFilesFolders(categorizedDir);

    return 0;
}

