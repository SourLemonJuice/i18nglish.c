source_files = main.c i7h_processor.c
executable_base_name = i18nglish

# About git repo info
git_commit_info = $(shell git describe --abbrev=40 --dirty --tags --always --long)
# Add more build info(remote CI or just a local PC)
build_host_description = Not explicit declared

# ' and " in shell is so... Ugly!!
# And I'll use cli to overwrite them with github ci, uglier then ugly.
# It took me 6 commits to figure this out.

# 1 == enabled
releaseBuild = 0

ALL: i18nglish.out

i18nglish.out: $(source_files)
	/usr/bin/clang $(source_files) \
		--output $(executable_base_name).out \
		-DAPP_GIT_COMMIT_INFO="\"$(git_commit_info)\"" \
		-DAPP_BUILD_HOST_DESCRIPTION="\"$(build_host_description)\"" \
		-DAPP_BUILD_RELEASE_MODE="$(releaseBuild)"

# just hope the clang and gcc flags are exactly the same
i18nglish.exe: $(source_files)
	/usr/bin/x86_64-w64-mingw32-gcc $(source_files) \
		--output $(executable_base_name).exe \
		-DAPP_GIT_COMMIT_INFO="\"$(git_commit_info)\"" \
		-DAPP_BUILD_HOST_DESCRIPTION="\"$(build_host_description)\"" \
		-DAPP_BUILD_RELEASE_MODE="$(releaseBuild)"

clean:
	rm -i ./$(executable_base_name).*
