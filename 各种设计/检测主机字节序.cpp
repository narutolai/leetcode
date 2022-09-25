#include <stdio.h>

void byteorder()
{
    union
    {
        short value;
        char union_byte[sizeof(short)];
    }
    test;
    test.value = 0x0102;
    if ((test.union_byte[0] == 1) && (test.union_byte[1] == 2))
        printf("big endian\n");
}
int main()
{
    byteorder();
    return 0;
}
//在一个联合体中加一个一个短整形和union_byte[2];