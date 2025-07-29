# Static Variables

| Memory Section   | Purpose                                       |
| ---------------- | --------------------------------------------- |
| **Stack**        | Local (automatic) variables                   |
| **Heap**         | Dynamically allocated memory (`malloc`)       |
| **Data Segment** | `global/static` variables with initial values |
| **BSS Segment**  | `global/static` variables without init value  |
| **Text**         | Program code                                  |

## Where Does `static` Go?

- It’s stored in the **data segment** (because it has an initial value of 0).
- Because it’s `static`:  
   → It is **allocated only once** in memory.  
   → Every time the function is called, the same memory address is used.

```c
void my_function() {
    static int counter = 0;
    counter++;
    printf("%d\n", counter);
}
```

Every time you call `my_function()`, the `counter` at address `0x100` is updated — but it is **never destroyed** until the program ends.

| Feature          | `int x = 0;` (non-static) | `static int x = 0;` |
| ---------------- | ------------------------- | ------------------- |
| Memory Location  | Stack                     | Data Segment        |
| Lifetime         | Until function ends       | Until program ends  |
| Remembers Value? | No                        | Yes                 |

- `static` in C allows you to:
  - Persist memory **without global scope**.
  - Avoid memory leaks by not needing `malloc/free`.
