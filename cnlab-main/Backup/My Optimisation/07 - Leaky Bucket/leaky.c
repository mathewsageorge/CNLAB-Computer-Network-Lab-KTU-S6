#include <stdio.h>
int min(int x, int y) {
    return (x < y) ? x : y;
}
int main() {
    int bucket, outgoing, input;
    printf("Enter Bucket Size: ");
    scanf("%d", &bucket);
    printf("Enter Outgoing Rate: ");
    scanf("%d", &outgoing);
    printf("Enter number of inputs: ");
    scanf("%d", &input);
    int incoming[input], drop = 0, count = 0, minimum, i;
    for (i = 0; i < input; i++) {
        printf("Enter [%d] incoming packet size: ", i + 1);
        scanf("%d", &incoming[i]);
    }
    printf("Input\tReceived\tSent\tLeft\tDropped\n");
    for (i = 0; i < input; i++) {
        count += incoming[i];
        if (count > bucket) {
            drop = count - bucket;
            count = bucket;
        }
        minimum = min(count, outgoing);
        printf("%d\t%d\t\t%d\t%d\t%d\n", i + 1, incoming[i], minimum, count - minimum, drop);
        count -= minimum;
        drop = 0;
    }
    for (; count > 0; i++){
        minimum = min(count, outgoing);
        printf("[%d]\t0\t\t%d\t%d\t%d\n", i + 1, minimum, count - minimum, drop);
        count -= minimum;
    }
}