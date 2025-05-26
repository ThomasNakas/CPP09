---
### 🔢 ex00 - Bitcoin Exchange
This project involved a straightforward implementation of C++’s `<filesystem>`, `<sstream>`, and `<map>` libraries to build a Bitcoin exchange rate evaluator. The main goal was to calculate the real-world value of a user's Bitcoin holdings based on historical exchange rates tied to specific dates.

The solution reads and parses a `.csv` database of Bitcoin prices and compares them against user-specified dates and values. Parsing logic was carefully implemented to detect and report invalid formats, missing data, and out-of-bounds dates. Custom error handling ensures robustness, while a clean interface allows easy testing with various inputs.

---

# 🔢 ex01 - Reverse Polish Notation (RPN) Evaluator

A robust Reverse Polish Notation (RPN) parser and evaluator built in C++ with a focus on correctness, error handling, and flexible formatting.
This project is a comprehensive tool for validating and computing RPN expressions while highlighting evaluation errors such as missing operands/operators or invalid input formats.

---

## 🧩 Features

* ✅ Supports basic arithmetic: `+`, `-`, `*`, `/`
* ✅ Accepts **multi-digit numbers** and handles flexible spacing
* ✅ Handles **integer and floating-point division**, auto-detecting the correct result type
* ✅ Validates:

  * ✔️ **Balanced expression**: requires `#operands = #operators + 1`
  * ✔️ **Correct spacing** rules between operands and operators
  * ❌ Invalid characters (e.g., letters, unknown symbols)
  * ❌ Division by zero
  * ❌ Improper formatting (e.g., `34` without space, `5 +` with missing operand)
* ✅ Clear parsing and step-by-step evaluation logs for debugging
* 🧮 Intelligent type output:

  * Returns an integer if the result is whole (e.g., `3`)
  * Returns a double if needed (e.g., `3.5`)

---

## 🧩 Evaluation Strategy

The evaluator processes expressions **left-to-right**, using a **stack-based simulation** of the RPN algorithm.

### 🧩 Operand vs Operator Validation Rule:

```txt
Start at 0
+1 → when operand is found
-1 → when operator is found
Expression is valid if final result = 1 and intermediate stack value never < 1
```

### ✅ Valid Expression

```
Input: 3 3 * 6 3 + / 4 5 + * 3 + 1 2 2 1 - - + * 3 + 9 /
Stack trace: [3] → Final result ✔
```

### ❌ Invalid Examples

* `5 +` → Not enough operands
* `5 6` → Not enough operators
* `5 4 / 0 /` → Division by zero
* `45 3` → Improper spacing between numbers

---

## 📘 Parsing Rules

| Rule                                   | Status              |
| -------------------------------------- | ------------------- |
| Spaces required between **numbers**    | ✅                   |
| Operators can be grouped without space | ✅ (`3 4 5+--/+*`)   |
| Floating-point support via division    | ✅                   |
| Invalid characters detection           | ✅                   |
| Improper spacing between digits        | ❌ (`346` = invalid) |

---

## 🧪 Example Expressions

| Expression                                                                              | Result                 |
| --------------------------------------------------------------------------------------- | ---------------------- |
| `3 3 *`                                                                                 | `9`                    |
| `9 3 /`                                                                                 | `3`                    |
| `1 1 4 + 1 + 3 / 2 + 2 / + 3 * 6 3 + / 2 2 * 1 2 2 + + + * 3 + 1 2 2 1 - - + * 3 + 9 /` | `3`                    |
| `5 +`                                                                                   | ❌ Not enough operands  |
| `5 6`                                                                                   | ❌ Not enough operators |
| `9 0 /`                                                                                 | ❌ Division by zero     |

---

## 🧠 Bonus Features

* **Verbose Debug Logs**: Optional mode that prints the evaluation stack at each step.
* **Error Messaging**: Prints meaningful error messages for malformed input.
* **Precision Smart Output**: Evaluates and prints integers as integers and floats with full precision if needed.

---

## 📘 Related Concepts

* [Reverse Polish Notation – Wikipedia](https://en.wikipedia.org/wiki/Reverse_Polish_notation)
* [DCode RPN Tool](https://www.dcode.fr/reverse-polish-notation)

---


---
### 🧠 ex02 - PmergeMe

> A custom implementation inspired by **Ford–Johnson merge-insertion sort**, combined with **Jacobsthal sequence logic** for optimized binary insertions.

---

### 🧩 Step 1: Initial Pairing & Local Sorting

Given input list:

```
2 1 9 3 4 5 6 7 8
```

1. **Split into pairs** (rightmost element remains if odd):

```
[2 1]  [9 3]  [4 5]  [6 7]   8
```

2. **Sort each pair** internally:

```
[1 2]  [3 9]  [4 5]  [6 7]   8
```

3. **Identify `main chain` and `pending elements`:**

   * Larger value in each pair goes to the **main chain**.
   * Smaller value in each pair becomes a **pending element** to be inserted later.

```
Main Chain: [2 9 5 7]
Pending:    [1 3 4 6]
Straggler (if any): 8
```

---

### 🧩 Step 2: Jacobsthal-Guided Insertion

Pending elements are inserted into the main chain using **binary insertion**, following the **Jacobsthal sequence** to define the insertion order.

**Jacobsthal Sequence Example:**

```
1, 3, 5, 11, 21...
```

This ensures more balanced insertions:

1. It avoids excessive comparisons.
2. Guarantees near-optimal placement of each element.

**Insertion Order:**
Using the Jacobsthal sequence, we insert:

```
4 → into [2 9 5 7]
6 → into [2 4 9 5 7]
1 → into [2 4 6 9 5 7]
3 → ...
```

Each step uses **binary search** within the main chain for efficient positioning.

---

### 🧩 Step 3: Final Merge

1. After all **pending elements** are inserted, the straggler (if present) is inserted at its appropriate position.
2. The final array is completely sorted:

```
[1 2 3 4 5 6 7 8 9]
```

---

### Summary of Steps

1. **Pairing & Local Sort:** Create sorted pairs from adjacent values.
2. **Chain Splitting:** Move larger values to the main chain; keep smaller as pending.
3. **Guided Insertion:** Insert pending elements using **binary search**, ordered by **Jacobsthal sequence**.
4. **Finalize:** Add the straggler (if odd count), verify full sort.

---

### Why This Matters

* Mimics **Ford–Johnson sorting** logic: efficient merging without repeated full sorts.
* Uses **Jacobsthal sequence**: reduces depth and improves efficiency during insertions.
* Entirely custom logic with no use of `std::sort`, reinforcing algorithmic understanding.

---
### Final thoughts
For this exercise, I implemented a custom sorting algorithm based on the **Ford–Johnson merge-insertion sort**, incorporating the **Jacobsthal sequence** to guide the binary insertion phase. This approach not only enhances performance but also deepened my understanding of non-trivial sorting algorithms beyond standard library implementations.

Rather than relying on built-in sorting functions, I built my own logic for the binary insertion process following the Jacobsthal sequence. This allowed me to fully grasp the mechanics of efficient comparison and insertion steps within the sorting algorithm.

To support clarity during evaluation, I customized the printed output messages to clearly reflect each step of the process. Furthermore, I created a **Bash script** that runs a comprehensive suite of test cases, covering valid sequences, error handling, and a variety of input sizes. This ensures thorough verification of both functionality and edge cases.

---
