## Comparing Lookup Type Data Structures
Conclusion
Hashtables are best for large insert-heavy and lookup-heavy workloads and outperform the other structures. AVL trees perform more rotations than BSTs, which are fast for small datasets, ensuring balanced height and predictable performance. LinkedLists perform poorly with lookups, and SortedArraySets have great overhead for insert/delete, despite its quick search. There are limits with Hashtables, however they produced the best outcomes with the workloads provided.

### Workload: workload_D_10000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 379286     | 9533      | 10000   | 0       | 0       | 0         |
| AVL          | 423350     | 150345    | 10000   | 0       | 0       | 0         |
| HashTable    | 5306       | 9544      | 10000   | 0       | 0       | 11        |
| LinkedList   | 46970621   | 9533      | 10000   | 0       | 10000   | 0         |
| SortedArray  | 128689     | 22787428  | 10000   | 0       | 0       | 10        |

### Workload: workload_A_1000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 26429      | 958       | 1000    | 0       | 0       | 0         |
| AVL          | 30626      | 11618     | 1000    | 0       | 0       | 0         |
| HashTable    | 522        | 966       | 1000    | 0       | 0       | 8         |
| LinkedList   | 470492     | 958       | 1000    | 0       | 1000    | 0         |
| SortedArray  | 9556       | 225491    | 1000    | 0       | 0       | 7         |

### Workload: workload_C_20000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 278886     | 19916     | 10000   | 9921    | 0       | 0         |
| AVL          | 369998     | 136698    | 10000   | 9921    | 0       | 0         |
| HashTable    | 14476      | 19921     | 10000   | 9921    | 0       | 5         |
| LinkedList   | 449019     | 19916     | 10000   | 9921    | 10000   | 0         |
| SortedArray  | 124298     | 440050    | 10000   | 9921    | 0       | 4         |

### Workload: workload_D_20000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 828142     | 19084     | 20000   | 0       | 0       | 0         |
| AVL          | 917685     | 320118    | 20000   | 0       | 0       | 0         |
| HashTable    | 10682      | 19096     | 20000   | 0       | 0       | 12        |
| LinkedList   | 187933901  | 19084     | 20000   | 0       | 20000   | 0         |
| SortedArray  | 277298     | 91404880  | 20000   | 0       | 0       | 11        |

### Workload: workload_C_1000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 10188      | 986       | 500     | 488     | 0       | 0         |
| AVL          | 11977      | 4916      | 500     | 488     | 0       | 0         |
| HashTable    | 733        | 989       | 500     | 488     | 0       | 3         |
| LinkedList   | 6699       | 986       | 500     | 488     | 500     | 0         |
| SortedArray  | 4394       | 6332      | 500     | 488     | 0       | 2         |

### Workload: workload_D_1000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 26429      | 958       | 1000    | 0       | 0       | 0         |
| AVL          | 30626      | 11618     | 1000    | 0       | 0       | 0         |
| HashTable    | 522        | 966       | 1000    | 0       | 0       | 8         |
| LinkedList   | 470492     | 958       | 1000    | 0       | 1000    | 0         |
| SortedArray  | 9556       | 225491    | 1000    | 0       | 0       | 7         |

### Workload: workload_A_10000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 379286     | 9533      | 10000   | 0       | 0       | 0         |
| AVL          | 423350     | 150345    | 10000   | 0       | 0       | 0         |
| HashTable    | 5306       | 9544      | 10000   | 0       | 0       | 11        |
| LinkedList   | 46970621   | 9533      | 10000   | 0       | 10000   | 0         |
| SortedArray  | 128689     | 22787428  | 10000   | 0       | 0       | 10        |

### Workload: workload_D_5000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 172491     | 4754      | 5000    | 0       | 0       | 0         |
| AVL          | 193484     | 69826     | 5000    | 0       | 0       | 0         |
| HashTable    | 2706       | 4764      | 5000    | 0       | 0       | 10        |
| LinkedList   | 11698096   | 4754      | 5000    | 0       | 5000    | 0         |
| SortedArray  | 59351      | 5658510   | 5000    | 0       | 0       | 9         |

### Workload: workload_A_5000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 172491     | 4754      | 5000    | 0       | 0       | 0         |
| AVL          | 193484     | 69826     | 5000    | 0       | 0       | 0         |
| HashTable    | 2706       | 4764      | 5000    | 0       | 0       | 10        |
| LinkedList   | 11698096   | 4754      | 5000    | 0       | 5000    | 0         |
| SortedArray  | 59351      | 5658510   | 5000    | 0       | 0       | 9         |

### Workload: workload_A_20000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 828142     | 19084     | 20000   | 0       | 0       | 0         |
| AVL          | 917685     | 320118    | 20000   | 0       | 0       | 0         |
| HashTable    | 10682      | 19096     | 20000   | 0       | 0       | 12        |
| LinkedList   | 187933901  | 19084     | 20000   | 0       | 20000   | 0         |
| SortedArray  | 277298     | 91404880  | 20000   | 0       | 0       | 11        |

### Workload: workload_C_10000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 129058     | 9915      | 5000    | 4920    | 0       | 0         |
| AVL          | 187394     | 69510     | 5000    | 4920    | 0       | 0         |
| HashTable    | 8452       | 9920      | 5000    | 4920    | 0       | 5         |
| LinkedList   | 252899     | 9915      | 5000    | 4920    | 5000    | 0         |
| SortedArray  | 63542      | 274913    | 5000    | 4920    | 0       | 4         |

### Workload: workload_B_10000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 142900871  | 9533      | 10000   | 0       | 0       | 0         |
| AVL          | 499785     | 160423    | 10000   | 0       | 0       | 0         |
| HashTable    | 5388       | 9544      | 10000   | 0       | 0       | 11        |
| LinkedList   | 45434745   | 9533      | 10000   | 0       | 10000   | 0         |
| SortedArray  | 113483     | 9543      | 10000   | 0       | 0       | 10        |

### Workload: workload_B_1000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 1443700    | 958       | 1000    | 0       | 0       | 0         |
| AVL          | 36632      | 12702     | 1000    | 0       | 0       | 0         |
| HashTable    | 524        | 966       | 1000    | 0       | 0       | 8         |
| LinkedList   | 458445     | 958       | 1000    | 0       | 1000    | 0         |
| SortedArray  | 8014       | 965       | 1000    | 0       | 0       | 7         |

### Workload: workload_B_5000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 35707442   | 4754      | 5000    | 0       | 0       | 0         |
| AVL          | 229861     | 75134     | 5000    | 0       | 0       | 0         |
| HashTable    | 2777       | 4764      | 5000    | 0       | 0       | 10        |
| LinkedList   | 11298127   | 4754      | 5000    | 0       | 5000    | 0         |
| SortedArray  | 51775      | 4763      | 5000    | 0       | 0       | 9         |

### Workload: workload_B_20000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 572130280  | 19084     | 20000   | 0       | 0       | 0         |
| AVL          | 1079813    | 341019    | 20000   | 0       | 0       | 0         |
| HashTable    | 10921      | 19096     | 20000   | 0       | 0       | 12        |
| LinkedList   | 182090902  | 19084     | 20000   | 0       | 20000   | 0         |
| SortedArray  | 246976     | 19095     | 20000   | 0       | 0       | 11        |

### Workload: workload_C_5000.json
| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |
|---------------|------------|-----------|--------|--------|--------|----------|
| BST          | 57768      | 4934      | 2500    | 2436    | 0       | 0         |
| AVL          | 82339      | 31068     | 2500    | 2436    | 0       | 0         |
| HashTable    | 4201       | 4938      | 2500    | 2436    | 0       | 4         |
| LinkedList   | 82780      | 4934      | 2500    | 2436    | 2500    | 0         |
| SortedArray  | 28238      | 84204     | 2500    | 2436    | 0       | 3         |
