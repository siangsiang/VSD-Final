// #include <stdio.h>
// #include <stdint.h>

// #include "fixed32.h"
// #include "sim.h"

// int main()
// {
//     FILE* fp = fopen("input_0.dat", "r");
//     fixed32 buf[360];
//     int i = 0;
//     while (fscanf(fp, "%x", &buf[i++]) != EOF)
//         ;

//     int cls = inference(buf);
//     printf("%d\n", cls);

//     return 0;
// }