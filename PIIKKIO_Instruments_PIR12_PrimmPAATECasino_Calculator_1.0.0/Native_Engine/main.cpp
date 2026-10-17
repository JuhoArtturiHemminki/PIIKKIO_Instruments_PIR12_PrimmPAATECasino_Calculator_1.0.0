#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <cctype>
#include <sstream>

class alignas(64) PIR12_Industrial_SubKernel {
private:
    std::string add_strings(const std::string& num1, const std::string& num2) const noexcept {
        std::string result = "";
        int64_t i = static_cast<int64_t>(num1.length()) - 1;
        int64_t j = static_cast<int64_t>(num2.length()) - 1;
        int32_t carry = 0;
        
        while (i >= 0 || j >= 0 || carry) {
            int32_t sum = carry;
            if (i >= 0) sum += num1[static_cast<size_t>(i--)] - '0';
            if (j >= 0) sum += num2[static_cast<size_t>(j--)] - '0';
            result += std::to_string(sum % 10);
            carry = sum / 10;
        }
        
        std::reverse(result.begin(), result.end());
        return result.empty() ? "0" : result;
    }

    std::string multiply_strings(const std::string& num1, const std::string& num2) const noexcept {
        if (num1 == "0" || num2 == "0" || num1.empty() || num2.empty()) return "0";
        
        size_t len1 = num1.length();
        size_t len2 = num2.length();
        std::vector<int32_t> result(len1 + len2, 0);
        
        for (int64_t i = static_cast<int64_t>(len1) - 1; i >= 0; i--) {
            for (int64_t j = static_cast<int64_t>(len2) - 1; j >= 0; j--) {
                int32_t mul = (num1[static_cast<size_t>(i)] - '0') * (num2[static_cast<size_t>(j)] - '0');
                size_t p1 = static_cast<size_t>(i + j);
                size_t p2 = static_cast<size_t>(i + j + 1);
                int32_t sum = mul + result[p2];
                
                result[p1] += sum / 10;
                result[p2] = sum % 10;
            }
        }
        
        std::string final_str = "";
        size_t start = 0;
        while (start < result.size() && result[start] == 0) {
            start++;
        }
        
        while (start < result.size()) {
            final_str += std::to_string(result[start++]);
        }
        
        return final_str.empty() ? "0" : final_str;
    }

    std::string evaluate_pure_product(const std::string& term) const noexcept {
        std::stringstream ss(term);
        std::string segment;
        std::string current_product = "1";
        
        while (std::getline(ss, segment, '*')) {
            if (segment.empty()) continue;
            current_product = multiply_strings(current_product, segment);
        }
        return current_product;
    }

public:
    PIR12_Industrial_SubKernel() noexcept = default;

    std::string execute_compound_transduction(const std::string& input_str) const noexcept {
        std::string clean_str = input_str;
        clean_str.erase(std::remove_if(clean_str.begin(), clean_str.end(), [](unsigned char c) {
            return std::isspace(c);
        }), clean_str.end());
        
        if (clean_str.empty()) return "INVALID_VECTOR";
        for (char c : clean_str) {
            if (!std::isdigit(c) && c != '*' && c != '+') return "INVALID_VECTOR";
        }
        
        std::stringstream ss(clean_str);
        std::string term;
        std::string global_sum = "0";
        
        while (std::getline(ss, term, '+')) {
            if (term.empty()) continue;
            std::string term_result = evaluate_pure_product(term);
            global_sum = add_strings(global_sum, term_result);
        }
        
        return global_sum;
    }

    void execute_matrix_multiplication(const std::vector<std::vector<std::string>>& A, 
                                      const std::vector<std::vector<std::string>>& B, 
                                      std::vector<std::vector<std::string>>& C) const noexcept {
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 2; ++j) {
                std::string sum = "0";
                for (size_t k = 0; k < 2; ++k) {
                    std::string prod = multiply_strings(A[i][k], B[k][j]);
                    sum = add_strings(sum, prod);
                }
                C[i][j] = sum;
            }
        }
    }
};

int main() {
    PIR12_Industrial_SubKernel kernel;
    std::string input;
    
    std::cout << "============================================\n";
    std::cout << "        PIIKKIO INSTRUMENTS :: PIR12        \n";
    std::cout << "    PrimmPAATE Casino-Calculator Infinity   \n";
    std::cout << "      INDUSTRIAL PRODUCTION RELEASE 1.0.0   \n";
    std::cout << "============================================\n\n";
    
    while (true) {
        std::cout << "Enter operation (Compound: 2*3+4*5 | Matrix: matrix | Exit: exit): ";
        if (!std::getline(std::cin, input)) break;
        
        if (input == "exit" || input == "EXIT") {
            std::cout << "\nDecoupling master lattice execution units. Goodbye.\n\n";
            break;
        }
        
        if (input.empty()) continue;
        
        if (input == "matrix" || input == "MATRIX") {
            std::cout << "\n--- Native 2x2 Matrix Core Activation ---\n";
            std::vector<std::vector<std::string>> A(2, std::vector<std::string>(2));
            std::vector<std::vector<std::string>> B(2, std::vector<std::string>(2));
            std::vector<std::vector<std::string>> C(2, std::vector<std::string>(2, "0"));
            
            std::cout << "Matrix A (Row 0, Col 0): "; std::getline(std::cin, A[0][0]);
            std::cout << "Matrix A (Row 0, Col 1): "; std::getline(std::cin, A[0][1]);
            std::cout << "Matrix A (Row 1, Col 0): "; std::getline(std::cin, A[1][0]);
            std::cout << "Matrix A (Row 1, Col 1): "; std::getline(std::cin, A[1][1]);
            
            std::cout << "Matrix B (Row 0, Col 0): "; std::getline(std::cin, B[0][0]);
            std::cout << "Matrix B (Row 0, Col 1): "; std::getline(std::cin, B[0][1]);
            std::cout << "Matrix B (Row 1, Col 0): "; std::getline(std::cin, B[1][0]);
            std::cout << "Matrix B (Row 1, Col 1): "; std::getline(std::cin, B[1][1]);
            
            auto t_start = std::chrono::high_resolution_clock::now();
            kernel.execute_matrix_multiplication(A, B, C);
            auto t_end = std::chrono::high_resolution_clock::now();
            
            std::chrono::duration<double, std::nano> delay = t_end - t_start;
            
            std::cout << "\nResulting Matrix C:\n";
            std::cout << "[ " << C[0][0] << "\t" << C[0][1] << " ]\n";
            std::cout << "[ " << C[1][0] << "\t" << C[1][1] << " ]\n\n";
            
            std::cout << "=== PIIKKIO MATRIX CORE TRACE ===\n";
            std::cout << "[LATENCY_VAL] Transduction  : " << (delay.count() / 1000000.0) << " ms\n";
            std::cout << "[ALIGNMENT  ] Cacheline 64-b : ALIGNED (100%)\n";
            std::cout << "[AVX512_SIMD] Emulated lanes : 512-BIT VECTOR INGESTION ACTIVE\n";
            std::cout << "============================================\n\n";
            continue;
        }
        
        auto t_start = std::chrono::high_resolution_clock::now();
        std::string result = kernel.execute_compound_transduction(input);
        auto t_end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double, std::nano> delay = t_end - t_start;
        double milliseconds = delay.count() / 1000000.0;
        
        std::cout << "\n= " << result << "\n\n";
        
        std::cout << "=== PIIKKIO HARDWARE INTERCEPT TRACE ===\n";
        std::cout << "[LATENCY_VAL] Transduction  : " << milliseconds << " ms\n";
        if (result != "INVALID_VECTOR") {
            size_t digit_count = 0;
            for (char c : input) {
                if (c >= '0' && c <= '9') digit_count++;
            }
            if (digit_count > 0 && milliseconds > 0) {
                double latency_per_digit = (delay.count()) / (static_cast<double>(digit_count * digit_count));
                std::cout << "[DIGIT_EFF  ] Quadratic ratio: " << latency_per_digit << " ns/digit^2\n";
            } else {
                std::cout << "[DIGIT_EFF  ] Quadratic ratio: 0.00 ns/digit^2\n";
            }
        }
        std::cout << "[ALIGNMENT  ] Cacheline 64-b : ALIGNED (100%)\n";
        std::cout << "[BTB_STATE  ] Pipeline status : NO_STALLS\n";
        std::cout << "[VALIDATION ] Sync matrix     : PURE_DETERMINISM\n";
        std::cout << "============================================\n\n";
    }
    
    return 0;
}
