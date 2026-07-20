#include <iostream>
#include <chrono>
#include <random>

uint32_t newRand(std::mt19937& gen, uint32_t max_val) {

    uint64_t range = static_cast<uint64_t>(max_val) + 1;

    uint32_t r = (- static_cast<uint32_t>(range)) % range;

    while (true) {

    uint32_t raw_rand = gen();
    uint64_t B = static_cast<uint64_t>(raw_rand) * range;

    uint32_t y = B & 0xFFFFFFFFULL;



    if (y >= range || y >= r) {
        return static_cast<uint32_t>(B >> 32);
    }
    // Mostly y >= range is true. Even it is false, y >= r then okay.
    }

}

uint32_t oldRand(std::mt19937& gen, uint32_t num) {

	std::uniform_int_distribution<uint32_t> dis(0, num);

    return dis(gen);
}



/**************** main
 * **********/

int main()
{
	uint32_t p = static_cast<uint32_t>(
	    std::chrono::high_resolution_clock::now().time_since_epoch().count()
	    );

	std::mt19937 gen_old(p);
    std::mt19937 gen_new(p);

    auto start_old = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 500; i++) {
        uint32_t random_max = gen_old(); // 32 bits random maximum
        uint32_t result = oldRand(gen_old, random_max);
    }
    auto end_old = std::chrono::high_resolution_clock::now();
    auto total_old = std::chrono::duration_cast<std::chrono::nanoseconds>(end_old - start_old).count();



    auto start_new = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 500; j++) {
        uint32_t random_max = gen_new();
        uint32_t result = newRand(gen_new, random_max);
    }
    auto end_new = std::chrono::high_resolution_clock::now();
    auto total_new = std::chrono::duration_cast<std::chrono::nanoseconds>(end_new - start_new).count();



    std::cout << "============= 500 times =============" << std::endl;
    std::cout << "1. oldRand : " << total_old << " ns" << std::endl;
    std::cout << "2. newRand: " << total_new << " ns" << std::endl;
    std::cout << "================================================" << std::endl;


	return 0;
}
