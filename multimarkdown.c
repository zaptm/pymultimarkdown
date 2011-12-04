#include <Python.h>
#include "markdown_lib.h"

#ifndef BOOL
typedef unsigned char BOOL;
#endif

#define formatConstant(f) PyModule_AddObject(m, #f, Py_BuildValue("i", f ## _FORMAT))

static PyObject *mmd_process(PyObject *self, PyObject *args, PyObject *kw)
{
	 static char *kwlist[] = {"mmdText", "format", "smart", "notes", "filterHtml", "filterStyles", "compatibility", "processHtml", "labels", NULL};
	 char *text;
	 int format = HTML_FORMAT;
	 BOOL smart = 1;
	 BOOL notes = 1;
	 BOOL filterHtml = 0;
	 BOOL filterStyles = 0;
	 BOOL compatibility = 0;
	 BOOL processHtml = 0;
	 BOOL labels = 1;

	 int options = 0;
	 char *output;
	 PyObject *outputObj;

	 if(!PyArg_ParseTupleAndKeywords(args, kw, "s|ibbbbbbb", kwlist, &text, &format, &smart, &notes, &filterHtml, &filterStyles, &compatibility, &processHtml, &labels))
		  return NULL;

	 if(smart)         options |= EXT_SMART;
	 if(notes)         options |= EXT_NOTES;
	 if(filterHtml)    options |= EXT_FILTER_HTML;
	 if(filterStyles)  options |= EXT_FILTER_STYLES;
	 if(compatibility) options |= EXT_COMPATIBILITY;
	 if(processHtml)   options |= EXT_PROCESS_HTML;
	 if(!labels)       options |= EXT_NO_LABELS;

	 output = markdown_to_string(text, options, format);
	 outputObj = Py_BuildValue("s", output);
	 
	 free(output);

	 return outputObj;
}

static PyMethodDef MmdMethods[] = {
	 {"process",  (PyCFunction)mmd_process, (METH_VARARGS | METH_KEYWORDS),
	              "process(mmdText, format=multimarkdown.HTML, smart=True, notes=True, filterHtml=False, filterStyles=False, compatibility=False, processHtml=False, labels=True)\nTranslate the given MMD string into the given format using the defined options."},
	 {NULL, NULL, 0, NULL} /* Sentinel */
};

PyMODINIT_FUNC initmultimarkdown(void)
{
    PyObject *m = Py_InitModule("multimarkdown", MmdMethods);

	if(m == NULL)
		 return;

	formatConstant(HTML);
	formatConstant(LATEX);
	formatConstant(MEMOIR);
	formatConstant(BEAMER);
	formatConstant(OPML);
	formatConstant(GROFF_MM);
	formatConstant(ODF);
	formatConstant(ODF_BODY);
}
