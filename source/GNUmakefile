cc_path = /usr/bin/gcc
source_files = main.c i7h_processor.c
executable_name = i18nglish.out

ALL: i18nglish.out

i18nglish.out: $(source_files)
	$(cc_path) \
	$(source_files) \
	--output $(executable_name)

clean:
	rm -i ./$(executable_name)
