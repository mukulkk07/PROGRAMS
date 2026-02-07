/*
 * CppSyntaxMaster_v17.cpp
 * A high-level tour of C++ syntax (Adjusted for C++17 compatibility).
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>       // Smart pointers
#include <thread>       // Concurrency
#include <mutex>        // Locking
#include <functional>   // std::function
#include <algorithm>    // Algorithms
#include <map>
#include <variant>      // C++17 Type-safe union
#include <future>       // Async tasks
#include <type_traits>  // For type checking

// ==========================================
// 1. TEMPLATES & META-PROGRAMMING
// ==========================================

namespace MetaUtils {

    // VARIADIC TEMPLATE: Recursion base case
    void log() { std::cout << std::endl; }

    // VARIADIC TEMPLATE: Recursive parameter pack expansion
    template<typename First, typename ...Rest>
    void log(First&& first, Rest&& ...rest) {
        std::cout << first << (sizeof...(rest) > 0 ? ", " : "");
        log(std::forward<Rest>(rest)...);
    }

    // FUNCTION TEMPLATE (Standard C++17 style)
    // Replaced C++20 'concept' with standard 'typename'
    template<typename T> 
    auto add(T a, T b) {
        // Simple compile-time check to ensure T is arithmetic
        static_assert(std::is_arithmetic<T>::value, "Type must be numeric");
        return a + b;
    }
}

// ==========================================
// 2. RESOURCE MANAGEMENT (RAII & Rule of 5)
// ==========================================

namespace MemoryOps {

    class Buffer {
    private:
        int* data;
        size_t size;
        std::string name;

    public:
        // Constructor
        Buffer(std::string n, size_t s) : name(std::move(n)), size(s) {
            data = new int[size];
            std::fill(data, data + size, 0);
            std::cout << "[Alloc] " << name << " created.\n";
        }

        // 1. Destructor
        ~Buffer() {
            if (data) {
                delete[] data;
                std::cout << "[Free] " << name << " destroyed.\n";
            }
        }

        // 2. Copy Constructor
        Buffer(const Buffer& other) : size(other.size), name(other.name + "_copy") {
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "[Copy] " << name << " created.\n";
        }

        // 3. Copy Assignment
        Buffer& operator=(const Buffer& other) {
            if (this == &other) return *this;
            delete[] data;
            size = other.size;
            name = other.name + "_assign";
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            return *this;
        }

        // 4. Move Constructor
        Buffer(Buffer&& other) noexcept : data(other.data), size(other.size), name(std::move(other.name)) {
            other.data = nullptr;
            other.size = 0;
            std::cout << "[Move] Ownership transferred to " << name << ".\n";
        }

        // 5. Move Assignment
        Buffer& operator=(Buffer&& other) noexcept {
            if (this == &other) return *this;
            delete[] data;
            data = other.data;
            size = other.size;
            name = std::move(other.name);
            other.data = nullptr;
            other.size = 0;
            return *this;
        }

        void debug() const {
            if(data) std::cout << "Buffer " << name << " is active.\n";
            else     std::cout << "Buffer " << name << " is empty (moved from).\n";
        }
    };
}

// ==========================================
// 3. OOP & POLYMORPHISM
// ==========================================

namespace Graphics {
    
    class IDrawable {
    public:
        virtual void draw() const = 0;
        virtual ~IDrawable() = default;
    };

    class Circle : public IDrawable {
        double radius;
    public:
        Circle(double r) : radius(r) {}
        void draw() const override {
            std::cout << "  -> Drawing Circle (r=" << radius << ")\n";
        }
    };

    class Square : public IDrawable {
        double side;
    public:
        Square(double s) : side(s) {}
        void draw() const override {
            std::cout << "  -> Drawing Square (s=" << side << ")\n";
        }
    };
}

// ==========================================
// 4. CONCURRENCY
// ==========================================

namespace AsyncEngine {
    std::mutex print_mutex;

    void heavy_computation(int id) {
        {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "[Thread " << id << "] Start...\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "[Thread " << id << "] End.\n";
        }
    }
}

// ==========================================
// 5. MAIN
// ==========================================

int main() {
    using namespace MetaUtils;
    using namespace MemoryOps;
    using namespace Graphics;

    std::cout << "=== C++ Syntax Mastery (C++17 Mode) ===\n\n";

    // --- A. Modern Typing ---
    std::cout << "--- A. Modern Typing ---\n";
    std::map<std::string, std::variant<int, float>> dataStore;
    dataStore["Gravity"] = 9.81f;
    dataStore["Answer"] = 42;

    // Structured binding (C++17)
    for (const auto& [key, value] : dataStore) {
        std::visit([&key](auto&& arg) {
            std::cout << "Key: " << key << " | Value: " << arg << "\n";
        }, value);
    }
    std::cout << "\n";

    // --- B. Memory Management ---
    std::cout << "--- B. Memory Management ---\n";
    {
        auto uniqueRes = std::make_unique<Buffer>("UniqueBuf", 1024);
        Buffer buf1("Original", 500);
        Buffer buf3("Temp", 100);     
        buf3 = std::move(buf1); 
        buf1.debug();
    }
    std::cout << "\n";

    // --- C. Polymorphism ---
    std::cout << "--- C. Polymorphism ---\n";
    std::vector<std::unique_ptr<IDrawable>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.5));
    shapes.push_back(std::make_unique<Square>(4.0));

    // Generic lambda (C++14)
    std::for_each(shapes.begin(), shapes.end(), [](const auto& shape) {
        shape->draw();
    });
    std::cout << "\n";

    // --- D. Templates ---
    std::cout << "--- D. Variadic Templates ---\n";
    log("System Status", 200, "OK", 3.14159);
    std::cout << "Templated Addition: " << add(10, 20) << "\n\n";

    // --- E. Concurrency ---
    std::cout << "--- E. Concurrency ---\n";
    std::vector<std::thread> workers;
    for (int i = 0; i < 3; ++i) {
        workers.emplace_back(AsyncEngine::heavy_computation, i);
    }
    for (auto& t : workers) {
        if (t.joinable()) t.join();
    }
    
    std::cout << "\n=== Done ===\n";
    return 0;
}