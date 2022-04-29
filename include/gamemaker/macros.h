#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef MACROS_H
#define MACROS_H


// Créer des pointeurs vers des structures plus facilement
#define NEW(type) (type *) malloc(sizeof(type))  // Mémoire à libérer
#define NEW_ARR(type, amount) (type *) malloc(sizeof(type) * amount)  // Pour les arrays, mémoire à libérer


// PRINT DES INFORMATIONS
#ifndef LOG_LEVEL
	#define LOG_LEVEL 3
#endif

// Print une information
#if LOG_LEVEL >= 3
	#define LOG(x) printf("(i) %s:%d %s\n", __FILE__, __LINE__, x)
#else
	#define LOG(x)
#endif
// Print un truc important
#if LOG_LEVEL >= 2
	#define WARN(x) printf("(!) %s:%d %s\n", __FILE__, __LINE__, x)
#else
	#define WARN(x)
#endif
// Print une erreur
#if LOG_LEVEL >= 1
	#define ERR(x) { printf("[ERROR] %s:%d %s\n", __FILE__, __LINE__, x);\
		assert (0); }
#else
	#define ERR(x)
#endif


#endif  // MACROS_H