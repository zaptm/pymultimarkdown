from distutils.core import setup, Extension

multimarkdown = Extension('multimarkdown',
						  sources = ['multimarkdown.c'],
						  library_dirs = ["."],
						  libraries = ["MultiMarkdown"],
						  )

setup(name = 'Multimarkdown',
	  version = '1.0',
	  description = 'Python interface to libmultimarkdown',
	  ext_modules = [multimarkdown])
