# not a GNU package. You can remove this line, if
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 1.4

SUBDIRS = buffer image parser osdep exception dtrace
bin_PROGRAMS = encoder

encoder_LDADD = $(top_builddir)/parser/libparser.a\
	$(top_builddir)/image/libimage.a\
	$(top_builddir)/exception/libexception.a\
	$(top_builddir)/dtrace/libdtrace.a $(top_builddir)/buffer/libbuffer.a
encoder_SOURCES = encoder_usage.cpp main.cpp encoder_buffer.cpp
noinst_HEADERS = encoder.h encoder_usage.h encoder_buffer.h
