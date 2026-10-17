# PIIKKIO INSTRUMENTS :: PIR12 INDUSTRIAL
## Comprehensive Character, Operator, and Syntax Guide — Version 1.0.0

This document acts as the definitive operational protocol for the PIIKKIO Instruments PIR12 Industrial Transduction Architecture. To maintain absolute bitwise precision and prevent microarchitectural stalls, all inputs must strictly adhere to the structural boundaries detailed below.

---

## 1. Mathematical Operators & Token Meanings

The native compiled Industrial Sub-Kernel processes text-based string vectors digit-by-digit. It identifies two specific operational tokens within the incoming stream:

*   **`*` (The Multiplication Vector)**
    *   *Meaning:* Triggers the infinite-precision long multiplication engine (`multiply_strings`).
    *   *Execution:* Intercepts the numeric strings on both sides of the token and multiplies them using ASCII byte manipulation. It is fully immune to floating-point truncation boundaries.
*   **`+` (The Addition Vector)**
    *   *Meaning:* Triggers the infinite-precision linear accumulation engine (`add_strings`).
    *   *Execution:* Adds both sides of the vector digit-by-digit with sequential carry propagation.

---

## 2. Multi-Vector Compound Syntax Rules

Unlike older versions, Version 1.0.0 natively evaluates chained, multi-stage equations (e.g., `A*B+C*D`) sequentially without intermediate memory-allocation flushes.

1.  **Zero Whitespace Policy (No Spaces)**
    *   *Rule:* Do **NOT** insert spaces anywhere within the data vector.
    *   *Correct Syntax:* `254353543*5345253+233*323232+2325234*3232`
    *   *Incorrect Syntax:* `254353543 * 5345253 + 233 * 323232`
2.  **Explicit Multipliers Only (No 'x' Characters or Hyphens)**
    *   *Rule:* Never use the alphabetical character `x` or `X` to indicate multiplication. Only the literal asterisk `*` token is valid. Additionally, subtraction/hyphen flags (`-`) are strictly forbidden in this release.
    *   *Correct Syntax:* `45893759*85294572+123*456`
    *   *Incorrect Syntax:* `45893759x85294572-123*456`
    *   *Microarchitectural Impact:* Passing alphabetical characters or negative hyphens into the matrix core trips the parser, resulting in an immediate `INVALID_VECTOR` state return to protect cache security.

---

## 3. Subsystem Activation Protocols

*   **Continuous CLI Input Loop:** The console stays active indefinitely. Type your operations sequentially. To close the transduction stream safely, type `exit` or `EXIT`.
*   **Matrix Core Mode:** Type `matrix` or `MATRIX` into the main prompt to instantiate the 2x2 multi-vector grid layout subsystem. Follow the prompts to input individual cell values.

---

## 4. Telemetry Feedback Interpretation

When running the compiled binary `./pir12_industrial`, observe the following validation traces to verify execution health:

*   **`[LATENCY_VAL] Transduction`**
    *   *Description:* Real-time hardware compute window. For massive multi-stage chained equations, it stabilizes into an exceptionally fast sub-millisecond domain (e.g., `0.064 ms`), bypassing any browser clock-dithering constraints.
*   **`[DIGIT_EFF] Quadratic ratio`**
    *   *Description:* Displays the exact nanoseconds spent per single digit squared (ns/digit²). A lower number indicates higher microarchitectural efficiency. Values breaking below `13.00 ns/digit²` confirm extreme cache line saturation.

---
SECURED BY THE ABSOLUTE TRUTH LAYER • INDUSTRIAL ENGINE VERSION 1.0.0
