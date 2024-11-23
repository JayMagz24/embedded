// minimal_exit.c
void _exit(int status) {
    // Trap the program in an infinite loop if exit is called
    while (1) {
    }
}
