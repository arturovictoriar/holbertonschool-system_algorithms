#include "huffman.h"

/**
* symbol_create - creates a symbol_t data structure
* @data: data to be stored in the structure
* @freq: is its associated frequency
* Return: pointer to the created structure, or NULL otherwise
*/
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *new_sym = NULL;

	new_sym = malloc(sizeof(symbol_t));
	if (!new_sym)
		return (NULL);

	new_sym->data = data;
	new_sym->freq = freq;

	return (new_sym);
}
