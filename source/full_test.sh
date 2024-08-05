#!/usr/bin/env bash

i18nglish_exec="./i18nglish"

if [[ ${OSTYPE} != "linux-gnu" ]]; then
    echo "Don't run it outside Linux, please.";
    return 1;
fi

# remember, keep other command safe, but not this target. It's a Test.
test_examples="'hello, world. -,hello --world,. --- lastOneNormal'"

chmod +x ${i18nglish_exec} | exit $?

echo Raw: "${test_examples}"

# args mode
${i18nglish_exec} --mode arguments ${test_examples} || exit $?

# stdin mode
echo "${test_examples}" | ${i18nglish_exec} --mode stdin || exit $?

# invalid file path
${i18nglish_exec} --mode file ./null
if [[ $? != 0 ]]; then
    echo "TEST: Program at least currectly exit with non zero"
fi

# file mode
echo "${test_examples}" >| ./justForTest.tmp && \
${i18nglish_exec} --mode file ./justForTest.tmp || exit $?
