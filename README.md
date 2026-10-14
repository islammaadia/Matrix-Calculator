# Advanced Matrix Calculator in C

A robust, command-line-based matrix calculator written in pure **C**. This project demonstrates advanced low-level programming concepts, including dynamic memory allocation, error handling, and numerical algorithms.

## 🚀 Features

- **Dynamic Memory Allocation:** Safely allocates and manages 2D matrices using `malloc` and `calloc` with strict memory leak prevention.
- **Matrix Operations:** Supports Addition, Subtraction, and Multiplication with dimensional compatibility checks.
- **Determinant Calculation:** Computes the determinant of any square matrix using **Gaussian Elimination** (with partial pivoting for numerical stability).
- **Matrix Resizing:** Dynamically resizes existing matrices while preserving existing data where possible.
- **Robust Input Validation:** Prevents infinite loops and crashes on invalid user inputs (handling non-numeric characters gracefully).

---

## 💻 How to Compile and Run

Make sure you have a C compiler installed (like `gcc`).

1. **Clone the repository:**
   ```bash
   git clone https://github.com/islammaadia/Matrix-Calculator.git
   cd Matrix-Calculator
