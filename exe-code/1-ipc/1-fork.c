#include <unistd.h>
#include <stdio.h>

int main() {

    printf("Starting with PID %d!\n", getpid());


    int ret = fork();
    printf("Both print this message\n");

    /*
    *******************************************
    NOTA: se il parent process muore prima che il figlio printi,
    il figlio printerà il pid non del parent (morto) ma del parent del parent, che lo ha ereditato.
    *******************************************
    */

    /* ESEMPIO

    Starting with PID 17634!
    Both print this message
    I'm the parent and the child has pid 17635!
    Both print this message
    I'm the child and my parent is 1! // "1" è il pid del processo init

    */

    if (ret == 0) {
        // Child
        printf("I'm the child and my parent is %d!\n", getppid());
    } else {
        // Parent
        printf("I'm the parent and the child has pid %d!\n", ret);
    }

    return 0;
}
