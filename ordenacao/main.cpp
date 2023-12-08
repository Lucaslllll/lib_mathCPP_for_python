#include <Python.h>
#include <vector>
#include <iostream>





// configuration

static PyMethodDef ordenacao_methods[] = {
	{"quick_sort", quick_sort, METH_VARARGS, "sort of a list"},
	{NULL, NULL, 0, NULL}

};


static struct PyModuleDef ordenacao_module = {
	PyModuleDef_HEAD_INIT, 
	"ordenacao",
	NULL,
	-1,
	ordenacao_methods

};


PyMODINIT_FUNC PyInit_ordenacao(void){
	return PyModule_Create(&ordenacao_module);
}