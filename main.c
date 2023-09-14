#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

int main() {
    FILE* file;
    char ch;
    char str[30] = "";
    int maxLength = 0;
    char *res;
    int size = 0;
    bool repetition = false;

    file = fopen("file.txt", "r");

    if (NULL == file) {
        printf("File can't be opened.\n");
        return 0;
    }

    do {
        ch = fgetc(file);

        if ((ch >=65 && ch <= 90) || (ch >=97 && ch <= 122)) {
            strncat(str, &ch, 1);
        }
        else {
            size_t len = strlen(str);

            if (len == maxLength && maxLength != 0) {
                int res_size = strlen(res)-1;

                // Check for the repeating
                for (int j = 0; j < res_size; j = (j+1) * (maxLength+1)) {
                    if (repetition == true) break;
                    else if ((res[j] >=65 && res[j] <= 90) || (res[j] >=97 && res[j] <= 122)) {
                        for (int k = 0; k < maxLength; k++) {
                            if (res[j+k] != str[k]) break;
                            else {
                                repetition = true;
                            }
                        }
                    }
                }

                // if there are no repetitions, add to the result
                if (repetition == false) {
                    size += (len * sizeof(char*))+1;
                    res = (char*)realloc(res,size);
                    strcat(res, str);
                    strcat(res, " ");
                }
            }
            else if (len > maxLength) {
                maxLength = len;
                size = 0;

                size += (len * sizeof(char*))+1;
                res = (char*)calloc(size, sizeof(char*));
                strcpy(res, str);
                strcat(res, " ");
            }

            str[0] = '\0';
        }

    } while (ch != EOF);

    printf("%s", res);
    fclose(file);
    return 0;
}
