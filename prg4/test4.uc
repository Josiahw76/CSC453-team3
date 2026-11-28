// test global variables and functions
int counter;
int add(int val) {
    return counter += val;
}

main() {
    counter = $0;
    add(2);
    return add(-1);
}
