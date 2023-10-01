#include <stdio.h>

int main()
{
    printf("Hello World\n");
    // Test multiplication...

    float speed = 5.3F;
    // 1 000 000 000 (1 billion)
    for(int i = 0; i < 1000000000; i++){
        /* speed *= 1.618; // takes 4 s */
        speed *= 2; // takes 2.66 s
        /* speed *= 1.8; // takes 4 s */
    }
    printf("Speed: %f\n", speed);

    // 4.01 s

    /* double dspeed = 5.3; */
    /* for(int i = 0; i < 1000000000; i++){ */
        /* dspeed *= 1.618; // 2.66 */
         /* dspeed *= 2; // 2.66 */
        //dspeed *= 1.8; // 2.66

    /* } */
    /* printf("Speed: %f\n", dspeed); */

    // 2.66 s

    return 0;
}
