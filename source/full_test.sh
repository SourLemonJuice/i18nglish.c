#!/usr/bin/env bash

if [[ ${OSTYPE} != "linux-gnu" ]]; then
    echo "Don't run it outside Linux, please.";
    return 1;
fi

# remember, keep other command safe, but not this target. It's a Test.
test_examples="'hello, world. -,hello --world,. --- lastOneNormal'"

echo Raw: "${test_examples}"

# args mode
./i18nglish.out --mode arguments ${test_examples} || exit $?

# stdin mode
echo "${test_examples}" | ./i18nglish.out --mode stdin || exit $?

# invalid file path
./i18nglish.out --mode file ./null
if [[ $? != 0 ]]; then
    echo "app return non zero"
fi

# file mode
echo "${test_examples}" >| ./justForTest.tmp && \
./i18nglish.out --mode file ./justForTest.tmp || exit $?
