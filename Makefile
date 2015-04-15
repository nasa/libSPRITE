SUBDIRS:=base net units util math SRTX SCALE

SP:=./
include $(SP)rules.mk

release:
	@echo "Enter version number: "; \
	read VERSION; \
	git branch release-$$VERSION; \
	git push origin release-$$VERSION; \
	RELEASENAME=libSPRITE-$$VERSION; \
	git archive --prefix=$$RELEASENAME/ master | bzip2 > ../$$RELEASENAME.tar.bz2
