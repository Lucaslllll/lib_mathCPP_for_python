#include <Python.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include<time.h>// necessário p/ função time()
#include <math.h>



int potencia(int base, int expoente){
	int i = 0;
	int resultado = 1;
	while(expoente > i){
		resultado = resultado * base;
		i++;
	}

	return resultado;
}
static PyObject* potencia(PyObject* self, PyObject* args){
	int base, expoente;
	if(!PyArg_ParseTuple(args, "ii", &base, &expoente)){
		return NULL;
	}

	return Py_BuildValue("i", potencia(base, expoente));
}



int mdc(int a, int b){
	int resto;
	
	while( (a % b) > 0 ){
		resto = (a % b);
		a = b;
		b = resto;

	}

	return b;

}
static PyObject* mdc(PyObject* self, PyObject* args){
	int a, b;
	if(!PyArg_ParseTuple(args, "ii", &a, &b)){
		return NULL;
	}

	return Py_BuildValue("i", mdc(a, b));
}


// MMC(a,b) × MDC(a,b) = a×b
int mmc(int a, int b){
	int max = (a > b) ? a : b;
	int min = (b > a) ? a : b;
	
	int mmc = (a * b) / mdc(max, min);

	return mmc;

}
static PyObject* mmc(PyObject* self, PyObject* args){
	int a, b;
	if(!PyArg_ParseTuple(args, "ii", &a, &b)){
		return NULL;
	}

	return Py_BuildValue("i", mmc(a, b));
}



// definição de congruência
// a ≡ b (mod n)
// 0 para verdadeiro e 1 para falso
int teste_de_congruencias(int a, int b, int n){
	int diferenca = a - (b);

	return (diferenca % n == 0) ? 0 : 1;
}
static PyObject* teste_de_congruencias(PyObject* self, PyObject* args){
	int a, b, n;
	if(!PyArg_ParseTuple(args, "iii", &a, &b, &n)){
		return NULL;
	}
	return Py_BuildValue("i", teste_de_congruencias(a, b, n));
}



int fatorial(int n){
	if(n == 0 || n == 1){
    	return n;
  	}

  	return fatorial(n-1)*n;

}
static PyObject* fatorial(PyObject* self, PyObject* args){
	int n;
	if(!PyArg_ParseTuple(args, "i", &n)){
		return NULL;
	}
	return Py_BuildValue("i", fatorial(n));
}


// fermat teste pequeno para testar números primos
// a^n−1 ≡ 1 (mod n) => n | a^n-1 - 1
// a > 0 && a < n 
// retorna 1 para verdade e 0 para falso
int fermat(int n){
	srand(time(NULL));
	
	int a = rand() % (n-1);

	// a^n-1
	int potencia = (int) pow(a, ( n-1 ));

			// n | a^n-1 - 1
	return  ( (potencia - (-1)) % n == 0 ) ? 0 : 1; 

}
static PyObject* fermat(PyObject* self, PyObject* args){
	int n;
	if(!PyArg_ParseTuple(args, "i", &n)){
		return NULL;
	}
	return Py_BuildValue("i", fermat(n));
}


// teorema de wilson para verificação de primos
// se p é um número primo
// então (p - 1)! ≡ -1 (mod p)
// 0 para verdadeiro e 1 para falso
int wilson(int p) {
  int dif = fatorial(p - 1) - (-1);

  if (dif % p == 0) {
    return 0;
  }

  return 1;
}
static PyObject* wilson(PyObject* self, PyObject* args){
	int p;
	if(!PyArg_ParseTuple(args, "i", &p)){
		return NULL;
	}
	return Py_BuildValue("i", wilson(p));
}








// configuration

static PyMethodDef calculus_methods[] = {
	{"potencia", potencia, METH_VARARGS, "Power of a number in a base"},
	{"mdc", mdc, METH_VARARGS, "MDC of two numbers"},
	{"mmc", mmc, METH_VARARGS, "MMC of two numbers"},
	{"teste_de_congruencias", teste_de_congruencias, METH_VARARGS, "test of congruencia"},
	{"fatorial", fatorial, METH_VARARGS, "fatorial of one number"},
	{"wilson", wilson, METH_VARARGS, "teorema de wilson to test numbers primes"},
	{"fermat", fermat, METH_VARARGS, "teorema de fermat to test numbers primes"},
	{NULL, NULL, 0, NULL}

};


static struct PyModuleDef calculus_module = {
	PyModuleDef_HEAD_INIT, 
	"calculus",
	NULL,
	-1,
	calculus_methods

};


PyMODINIT_FUNC PyInit_calculus(void){
	return PyModule_Create(&calculus_module);
}

