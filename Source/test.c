#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char buffer[] = "0 /file.html";

    int start = 3;
    int len = 0;

    for (int i = start; i < 13; i++) {
        if (buffer[i] != '\0') { len++; }
    }
       
    char file_name[len + 1];
    printf("%d\n", len);

    strncpy(file_name, buffer + start, len);

    file_name[len] = '\0';

    printf("%s\n", file_name);
    return 0;
}
