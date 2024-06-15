source_files = main.c i7h_processor.c
executable_name = i18nglish.out

# About git repo info
git_commit_info = $(shell git describe --abbrev=40 --dirty --always)

ALL: i18nglish.out

i18nglish.out: $(source_files)
	/usr/bin/clang $(source_files) \
		--output $(executable_name) \
		-DAPP_GIT_COMMIT_INFO=\"$(git_commit_info)\"

clean:
	rm -i ./$(executable_name)
