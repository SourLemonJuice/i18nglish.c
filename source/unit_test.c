#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "i7h/i7h_processor.h"

void test_i7hProcessor(void)
{
    struct I7hDataStruct i7h_D;

    i7hInitStructure(&i7h_D);
    assert(i7h_D.buffer != NULL);

    char *test_example[] = {"hello,", "world.", "-,hello", "--world,.", "---", "lastOneNormal"};
    char *test_example_answer[] = {"h4,", "w4.", "-5o", "-7.", "-1-", "l11l"};

    for (int i = 0; i < 6; i++) {
        assert(i7hProcessor(&i7h_D, test_example[i]) == 0);
        printf("i7hProcessor(): |%s| -> |%s|\n", test_example[i], i7h_D.buffer);
        assert(strcmp(i7h_D.buffer, test_example_answer[i]) == 0);
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
    puts("一个非常草率的单元测试...");
    test_i7hProcessor();
    // test_deletePunctuations();

    puts("test finished");
    return 0;
}
