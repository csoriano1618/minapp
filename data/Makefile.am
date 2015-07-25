gsettings_SCHEMAS = $(APP_ID).gschema.xml
@GSETTINGS_RULES@

# we need to generate the resources in the same folder as the binary
resource_files=$(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=$(srcdir) --generate-dependencies $(srcdir)/$(APP_ID).gresource.xml)
$(APP_ID)-resources.c: $(top_srcdir)/data/$(APP_ID).gresource.xml $(resource_files)
	glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/data --generate-source --c-name $(APP_ID) $(top_srcdir)/data/$(APP_ID).gresource.xml
$(APP_ID)-resources.h: $(top_srcdir)/data/$(APP_ID).gresource.xml $(resource_files)
	glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/data --generate-header --c-name $(APP_ID) $(top_srcdir)/data/$(APP_ID).gresource.xml

BUILT_SOURCES = \
 $(APP_ID)-resources.c \
 $(APP_ID)-resources.h \
 $(NULL)

EXTRA_DIST = \
	$(resource_files) \
	$(APP_ID).gresource.xml \
        $(gsettings_SCHEMAS) \
	$(NULL)

CLEANFILES = \
	$(BUILT_SOURCES) \
	$(NULL)
