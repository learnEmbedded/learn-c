#define LESSON_MACRO
/*
1. LESSON_MACRO
*/
#ifdef LESSON_MACRO

#include <stdio.h>

#define PRINT_MENU_ITEM(number, item) printf("%d. %s\n", number, item);
#define PRINT_MENU(...) \
        do { \
            const char* items[] = {__VA_ARGS__}; \
            int n = sizeof(items)/sizeof(items[0]); \
            for (int i = 0; i < n; i++) { \
                PRINT_MENU_ITEM(i+1, items[i]); \
            } \
        } while (0);

#define HANDLE_OPTION(option, ...) \
        switch (option) { \
            __VA_ARGS__ \
        default: \
            printf("INVALID OPTION!\n"); \
        }

#define CASE_OPTION(number, function) \
        case number: \
            function(); \
            break;


void feature1() {
    printf("Feature  1 selected.\n");
}

void feature2() {
    printf("Feature  2 selected.\n");
}

void feature3() {
    printf("Feature  3 selected.\n");
}

int main()
{
    PRINT_MENU("OPTION 1", "OPTION 2", "OPTION 3", "EXIT");

    int options;

    scanf("%d", &options);

    HANDLE_OPTION(options, 
        CASE_OPTION(1, feature1)
        CASE_OPTION(2, feature2)
        CASE_OPTION(3, feature3)
    )

    return 0;
}

#elif 

#endif