#include "huffman.h"

/**
 * print_symbol_code - print the symbol code compressed of a list of letters
 * @root: head of a huffman tree
 * @codes: code of a given letter
 * @len_code: size of the code
 * Return: Nothing
 */
void print_symbol_code(binary_tree_node_t *root, char *codes, int *len_code)
{
	if (!root->left && !root->right)
	{
		if (!*len_code)
			printf("%c: 0\n", ((symbol_t *) root->data)->data);
		else
			printf("%c: %s\n", ((symbol_t *) root->data)->data, codes);
		return;
	}

	codes[*len_code] = 48;
	*len_code = *len_code + 1;
	print_symbol_code(root->left, codes, len_code);
	*len_code = *len_code - 1;
	codes[*len_code] = 49;
	*len_code = *len_code + 1;
	print_symbol_code(root->right, codes, len_code);
	*len_code = *len_code - 1;

	codes[*len_code] = 0;
}

/**
 * free_data_huffman - delete a set of structures
 * @data: data to delete
 * Return: Nothing
 */
void free_data_huffman(void *data)
{
	symbol_t *node = NULL;

	node = (symbol_t *) data;
	free(node);
}

/**
 * huffman_codes - build the Huffman tree and
 * print the resulting Huffman codes for each symbol
 * @data: is a pointer to the priority queue to extract from
 * @freq: is an array containing the associated frequencies
 * @size: lenght of the previous arrays
 * Return: 1 if it succeed, 0 if it fails
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *huf_root = NULL;
	static char codes[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	int len_code = 0;
	heap_t *heap = NULL;

	if (!data || !freq)
		return (0);

	huf_root = huffman_tree(data, freq, size);
	if (!huf_root)
		return (0);
	print_symbol_code(huf_root, codes, &len_code);
	heap = heap_create(data_cmp_huffman);
	heap->root = huf_root;
	heap_delete(heap, free_data_huffman);
	return (1);
}
