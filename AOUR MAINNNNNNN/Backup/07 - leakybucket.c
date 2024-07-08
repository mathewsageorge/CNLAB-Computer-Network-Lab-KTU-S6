#include <stdio.h>
int min(int x, int y) {
    return (x < y) ? x : y;
}
int main() {
    int drop = 0, input, cap, count = 0, outgoing;
    int i, incoming[25];
    printf("Enter the Bucket Size: ");
    scanf("%d", &cap);
    printf("Enter the Output Rate: ");
    scanf("%d", &outgoing);
    printf("Enter The No. Of Inputs: ");
    scanf("%d", &input);
    for (i = 0; i < input; i++) {
        printf("Enter the [%d] Incoming Packet Size: ", i + 1);
        scanf("%d", &incoming[i]);
    }
    printf("\nInput|Packet Received|Packet Sent|Packet Left|Packet Dropped|\n");
    printf("--------------------------------------------------------------\n");
    for (i = 0; i < input; i++) {
        count += incoming[i];
        if (count > cap) {
            drop = count - cap;
            count = cap;
        }
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, incoming[i], min(count, outgoing), count - min(count, outgoing), drop);
        count -= min(count, outgoing);
        drop = 0;
    }
    for (; count > 0; i++) {
        printf("%d\t0\t\t%d\t\t%d\t\t0\n", i + 1, min(count, outgoing), count - min(count, outgoing));
        count -= min(count, outgoing);
    }
    return 0;
}