source_files = main.c i7h_processor.c
executable_name = i18nglish.out

# About git repo info
git_commit_info = $(shell git describe --abbrev=40 --dirty --tags --always --long)
# Add more build info(remote CI or just a local PC)
build_host_description = Not explicit declared

# ' and " in shell is so... Ugly!!
# And I'll use cli to overwrite them with github ci, uglier then ugly.
# It took me 6 commits to figure this out.

ALL: i18nglish.out

i18nglish.out: $(source_files)
	/usr/bin/clang $(source_files) \
		--output $(executable_name) \
		-DAPP_GIT_COMMIT_INFO="\"$(git_commit_info)\"" \
		-DAPP_BUILD_HOST_DESCRIPTION="\"$(build_host_description)\""

clean:
	rm -i ./$(executable_name)
