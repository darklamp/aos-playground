#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {


    int ret = fork();

    if (ret == 0) {
        // Child
        for (int i=0; i<50; i++) {
            printf("%d ", i);        
        }
    } else {
        wait(NULL);
        printf("\n");
        for (int i=51; i<100; i++) {
            printf("%d ", i);        
        }
        printf("\n");        
    }

    return 0;
}
