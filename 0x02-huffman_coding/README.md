# 0x02. C - Huffman coding

## Resources:books:
Read or watch:
* [Binary Heap](https://intranet.hbtn.io/rltoken/X-mSXekgpykOalUNPSjNXw)
* [Huffman coding](https://intranet.hbtn.io/rltoken/4NVFM5ypwNQgV_eRj4nPxw)
* [Enumerated Types](https://intranet.hbtn.io/rltoken/ngRaRIK6vf1pXr_aQ5r1Sg)
* [Huffman Coding and Huffman Trees](https://intranet.hbtn.io/rltoken/dojXS3orEWOev_47OEyU4w)

---
## Learning Objectives:bulb:
What you should learn from this project:

* What is a binary Heap (min and max)
* What is a priority queue
* What is a Huffman code

---

### [0. Min Binary Heap - Create heap](./heap/heap_create.c)
* Write a function that creates a Heap data structure


### [1. Min Binary Heap - Create node](./heap/binary_tree_node.c)
* Write a function that creates a generic Binary Tree node


### [2. Min Binary Heap - Insert node](./heap/heap_insert.c)
* Write a function that inserts a value in a Min Binary Heap


### [3. Min Binary Heap - Extract](./heap/heap_extract.c)
* Write a function that extracts the root value of a Min Binary Heap


### [4. Min Binary Heap - Delete heap](./heap/heap_delete.c)
* Write a function that deallocates a heap


### [5. Symbols: Create symbol](./symbol.c)
* Write a function that creates a symbol_t data structure


### [6. Huffman coding - Step 1: Priority queue](./huffman_priority_queue.c)
* The first step to get the Huffman codes of our letters is to build a priority queue. The value of frequency field will be used to compare two nodes in this min heap. Once built, the least frequent character will be stored in the root node of our priority queue.


### [7. Huffman coding - Step 2: Extract](./huffman_extract_and_insert.c)
* Once we have our priority queue initialized, the next step is to build the Huffman tree. First we need to understand the process of building such a tree. We need to extract the two least frequent symbols from our priority queue, add their frequencies, and store this new frequency back in our priority queue.


### [8. Huffman coding - Step 3: Build Huffman tree](./huffman_tree.c)
* Following the previous step, we now have to iterate the same operation until there is only one node remaining in our priority queue. This final node will store the root node of our Huffman tree.


### [9. Huffman coding - Step 4: Huffman codes](./huffman_codes.c)
* Now that we have our Huffman tree, we are able to get the Huffman codes for each letter. This process is pretty straight forward: go through the Huffman tree starting at the root node. Each time you go to the left node, append a 0 to the code. Each time you go to the right, append a 1 to the code. When you hit a leaf node, get the letter and print its corresponding Huffman code.

---

## Author
* **Arturo Victoria Rincon** - [arvicrin](https://github.com/arvicrin)