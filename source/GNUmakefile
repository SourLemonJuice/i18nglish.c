SHELL := /usr/bin/bash

source_files := main.c i7h_processor.c
executable_base_name := i18nglish

# About git repo info
git_commit_info := $(shell git describe --abbrev=40 --dirty --tags --always --long)
# Add more build info(remote CI or just a local PC)
build_host_description := Not explicit declared
# get build UTC+0 date and time
build_date_UTC := $(shell env LANG=en_US.UTF-8 LANGUAGE=en_US date --universal "+%c %:z")

# ' and " in shell is so... Ugly!!
# And I'll use cli to overwrite them with github ci, uglier then ugly.
# It took me 6 commits to figure this out.

# 1 == enabled
releaseBuild := 0

# combining compiler's flags
CFlag_clang_define += -DAPP_GIT_COMMIT_INFO="\"$(git_commit_info)\""
CFlag_clang_define += -DAPP_BUILD_HOST_DESCRIPTION="\"$(build_host_description)\""
CFlag_clang_define += -DAPP_BUILD_RELEASE_MODE="$(releaseBuild)"
CFlag_clang_define += -DAPP_BUILD_DATE_UTC="\"$(build_date_UTC)\""

ALL: i18nglish.out

i18nglish.out: $(source_files)
	/usr/bin/clang $(source_files) \
		--output $(executable_base_name).out \
		$(CFlag_clang_define)

# need to run in MSYS2 bash
# if I want add some OS detection, then will see OSTYPE(bash var), but makefile just don't use it...
# or con't use standard bash to get it. Even if will conflict with it. I want to curse, then I will be as ugly as Makefile.
# ====
# Rather then saying use makefile/shell to detection OS, is better to say use "PATH not found" detect is.
i18nglish.exe: $(source_files)
	/ucrt64/bin/clang.exe $(source_files) \
		--output $(executable_base_name).exe \
		$(CFlag_clang_define)

clean:
	rm -i ./$(executable_base_name).*
