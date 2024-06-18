#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "i7h/i7h_processor.h"

void test_i7hProcessor(void)
{
    struct I7hDataStruct i7h_D;

    i7hInitStructure(&i7h_D);
    assert(i7h_D.buffer != NULL);

    char *test_example[] = {"hello,", "world.", "-,hello", "--world,.", "---", "lastOneNormal"};

    for (int i = 0; i < 6; i++) {
        assert(i7hProcessor(&i7h_D, test_example[i]) == 0);
        printf("i7hProcessor() output: %s\n", i7h_D.buffer);
    }

    assert(i7hFreeStructure(&i7h_D) == 0);
}

/*
void test_deletePunctuations()
{
// int deletePunctuations(char src_string[], int src_size, char des_string[], int des_size);
    char src_buffer[256];
    char des_buffer[256];
    char *test_example[] = {"hello,", "world.", "-,hello", "--world,.", "---", "lastOneNormal"};

    for (int i = 0; i < 6; i++) {
        strcpy(test_example[i], src_buffer);
        assert(deletePunctuations(src_buffer, 256, des_buffer, 256) == 0);
        printf("deletePunctuations() output: %s\n", des_buffer);
    }
}
*/

int main(void)
{
    test_i7hProcessor();
    // test_deletePunctuations();

    puts("test finished");
    return 0;
}
