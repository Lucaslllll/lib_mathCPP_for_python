#include <Python.h>
#include <vector>
#include <iostream>



// obs: eu poderia colocar isso numa função só static PyObject*, porém tanto para fins didaticos
// como para ficar mais organizado, resolvi dividir dessa forma

PyObject* quick_sort(PyObject* vector, int inicioV, int fimV){
	int esquerdaP; // indice da esquerda, iniciar ele com inicioV, que por sua vez deve ser 0
				   // para começar do inicio do vector
	int direitaP; // indice da direita
	int pivo; // valor para conseguir dividir entre os menores que ele e os maiores que ele
	PyObject* aux; // utilizar para trocar valores

	esquerdaP = inicioV;
	direitaP = fimV-1; // tamanho do vetor - 1, todo vetor é do 0 até n-1
	pivo = PyLong_AsLong(PyList_GetItem(vector, inicioV)); // o pivo nesse caso vai ser o primeiro item do vector, PyObject* para long int


	while(direitaP >= esquerdaP){
		// Vai correr o vetor ate que ultrapasse o outro ponteiro
	    // ou ate que o elemento em questão seja menor que o pivô.
		while(pivo > PyLong_AsLong(PyList_GetItem(vector, esquerdaP)) && esquerdaP < fimV){
			esquerdaP++;
		}
	
		// Vai correr o vetor ate que ultrapasse o outro ponteiro
	    // ou ate que o elemento em questão seja maior que o pivô.
		while(pivo < PyLong_AsLong(PyList_GetItem(vector, direitaP)) && direitaP > inicioV){
			direitaP--;
		}
	
	
	
		if (direitaP >= esquerdaP){
			// PyList_SetItem(vector, indice2, item1); exemplo
			aux = PyList_GetItem(vector, direitaP);
			PyList_SetItem(vector, direitaP, PyList_GetItem(vector, esquerdaP));
			PyList_SetItem(vector, esquerdaP, aux);
			
			esquerdaP++;
			direitaP--;
		}
	}

	

	// aqui está a grande engrenagem recursiva
	
	// veja que aqui vou verificar se o indice esquerdo superou o fim do vector
	// se não, então chamo quick_sort, só que dessa vez começando com o 
	// com o inicioV recebendo o indice da esquerda
	if(esquerdaP < fimV){
		quick_sort(vector, esquerdaP, fimV);
	}

	// veja que aqui vou verificar se o indice direito ficou inferior ao ínicio do vector
	// se não, então chamo quick_sort, só que dessa vez começando com o 
	// com o inicioV recebendo o indice da direita
	if (direitaP > inicioV){
		quick_sort(vector, inicioV, direitaP+1);
	}


	return vector;
}
static PyObject* quick_sort(PyObject* self, PyObject* args){
	PyObject* vector;
	int inicioV, fimV;

	
	// Parse os argumentos
    if (!PyArg_ParseTuple(args, "Oii", &vector, &inicioV, &fimV)) {
        return NULL;
    }

    // Verifica se o argumento é uma lista
    if (!PyList_Check(vector)) {
        PyErr_SetString(PyExc_TypeError, "O argumento deve ser uma lista.");
        return NULL;
    }

	return Py_BuildValue("O", quick_sort(vector, inicioV, fimV));
}



// configuration

static PyMethodDef ordenacao_methods[] = {
	{"quick_sort", quick_sort, METH_VARARGS, "sort of a list crescent"},
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