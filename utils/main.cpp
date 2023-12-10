#include <Python.h>
#include <stdlib.h> // necessário p/ as funções rand() e srand()
#include <time.h>   // necessário p/ função time()




typedef struct {
  int numeracao[11];
  int digito1;
  int digito2;
} CPF;


static PyObject* gerador_cpf(PyObject *self, PyObject *args) {
    srand(time(NULL));

    CPF cpf;

    while (true) {
    	int soma; 
    	int v1 = 0;
    	int v2 = 0;
    	int fator_multiplicativo = 10;

    	for (int i = 0; i < 11; i++) {
    		cpf.numeracao[i] = rand() % 10;
    	}
    	cpf.digito1 = cpf.numeracao[9];
    	cpf.digito2 = cpf.numeracao[10];


    	soma = 0;
    	for (int i = 0; i < 9; i++) {
    		soma = soma + (fator_multiplicativo * cpf.numeracao[i]);
    		fator_multiplicativo -= 1;
    	}
    	v1 = (soma * 10) % 11;

    	soma = 0;
    	fator_multiplicativo = 11;
    	for (int i = 0; i < 10; i++) {
    		soma = soma + (fator_multiplicativo * cpf.numeracao[i]);
    		fator_multiplicativo -= 1;
    	}
    	v2 = (soma * 10) % 11;


    	if (v1 == cpf.digito1 && v2 == cpf.digito2) {
    		break;
    	}

    }


    // Cria uma tupla Python para armazenar os dígitos do CPF
    PyObject* cpf_dict = PyDict_New();
    char numeracao_string[16];
    numeracao_string[0] = '\0'; // iniciando e se livrando do lixo

    for (int i = 0; i < 11; ++i) {
    	// sprintf(numeracao_string, "%d", cpf.numeracao[i]); não dá para concatenar com sprintf
    	snprintf(numeracao_string + strlen(numeracao_string), sizeof(numeracao_string) - strlen(numeracao_string), "%d", cpf.numeracao[i]);
  
    }
    PyObject* key = PyUnicode_FromString("numeracao");
    PyObject* value = PyUnicode_FromFormat("%s", numeracao_string);
    
    PyDict_SetItem(cpf_dict, key, value);

    Py_DECREF(key);
    Py_DECREF(value);

    return cpf_dict;
}




// configuração

static PyMethodDef utils_methods[] = {
	{"gerador_cpf", gerador_cpf, METH_NOARGS, "gerador de cpf"},
	{NULL, NULL, 0, NULL}

};


static struct PyModuleDef utils_module = {
	PyModuleDef_HEAD_INIT, 
	"utils",
	NULL,
	-1,
	utils_methods

};


PyMODINIT_FUNC PyInit_utils(void){
	return PyModule_Create(&utils_module);
}