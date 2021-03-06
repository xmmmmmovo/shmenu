//
// Created by xmmmmmovo on 2020/8/28.
//

#include "actions.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define HOST_NAME_LENGTH 128

void quitAction() {
    exit(0);
}

void dateAction() {
    time_t now = time(NULL);
    // ps 没法用std::move好烦啊
    printf("now time is : %s\n", ctime(&now));
}

void randomAction(int argc, char *argv[]) {
    bool s        = false;
    bool m        = false;
    int  seed     = 0;
    int  maxValue = 1;

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--seed")) {
                seed = atoi(argv[++i]);
                s    = true;
            } else if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--max")) {
                maxValue = atoi(argv[++i]);
                m        = true;
            }
        }
    }

    if (!s) {
        printf("please enter a seed value\n");
        scanf("%d", &seed);
        getchar();
    }
    if (!m) {
        printf("please enter the max value\n");
        scanf("%d", &maxValue);
        getchar();
    }
    srand(seed);
    printf("rand answer is: %d\n", rand() % maxValue);
}

void pwdAction() {
    char *buffer;
    if ((buffer = getcwd(NULL, 0)) == NULL) {
        perror("getcwd error");
    } else {
        printf("%s\n", buffer);
        free(buffer);
    }
}

void helloAction() {
    char hostname[HOST_NAME_LENGTH];
    gethostname(hostname, HOST_NAME_LENGTH);
    printf("hello, %s\n", hostname);
}

void sysAction() {
    FILE *osFile = fopen("/proc/version", "r");
    if (osFile == NULL) {
        printf("failed to open version file\n");
    }
    char szTest[1000] = {0};
    while (!feof(osFile)) {
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest) - 1, osFile);// leave out \n
        printf("%s", szTest);
    }
    fclose(osFile);
}

void versionAction() {
}

void unknownAction() {
    printf("Unknown command!\nPlease enter 'help' to get help.\n");
}
