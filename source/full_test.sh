#!/usr/bin/env bash

if [[ ${OSTYPE} != "linux-gnu" ]]; then
    echo "Don't run it outside Linux, please.";
    return 1;
fi

# remember, keep other command safe, but not this target. It's a Test.
test_examples="hello, world. -,hello --world,. ---"

./i18nglish.out --mode argument ${test_examples} || exit $?

echo "${test_examples}" | ./i18nglish.out --mode stdin || exit $?

echo "${test_examples}" >| ./a.tmp && \
./i18nglish.out --mode file ./a.tmp || exit $?
