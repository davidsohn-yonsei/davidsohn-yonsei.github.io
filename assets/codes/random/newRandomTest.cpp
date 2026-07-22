#include <iostream>
#include <chrono>
#include <random>


std::mt19937 gen;
uint32_t range[100'000];


uint32_t newRand(std::mt19937& gen, uint32_t max_val) {





    uint32_t current_rand = gen();
    uint64_t B = static_cast<uint64_t>(current_rand) * max_val;

    uint32_t y = B & 0xFFFFFFFFULL;  // it is same as static_cast<uint32_t>(B)



    if (y < max_val) {  // Moved while into the if.

        uint32_t r = (-max_val) % max_val;

        while (y < r) {
            current_rand = gen();
            B = static_cast<uint64_t>(current_rand) * max_val;
            y = static_cast<uint32_t>(B);
        }
    }
    return static_cast<uint32_t>(B >> 32);
}

uint32_t oldRand(std::mt19937& gen, uint32_t num) {
    static std::uniform_int_distribution<uint32_t> dis;

     return dis(gen, std::uniform_int_distribution<uint32_t>::param_type(0, num-1));
}



/**************** main
 * **********/


int main()
{
    uint32_t result = 0;

    uint32_t seed = 1234567;  // Just any number.
    gen.seed(seed);

	for (int k = 0; k < 100'000; k++){

        uint32_t t = gen();
	    if ( (t & (t - 1)) == 0) {
                t = ~t;
	    }
	    // If t is 2 ^ n, then t will become 2^32 - 1 - t

	    range[k] = t;



	}


    gen.seed(seed);
    auto start_old = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100'000; i++) {
        // 32 bits random maximum
        result += oldRand(gen, range[i]);
    }
    auto end_old = std::chrono::high_resolution_clock::now();
    auto total_old = std::chrono::duration_cast<std::chrono::nanoseconds>(end_old - start_old).count();

    gen.seed(seed);
    auto start_new = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 100'000; j++) {
        result += newRand(gen, range[j]);
    }
    auto end_new = std::chrono::high_resolution_clock::now();
    auto total_new = std::chrono::duration_cast<std::chrono::nanoseconds>(end_new - start_new).count();



    std::cout << "============= 100,000 times =============" << std::endl;
    std::cout << "1. oldRand : " << total_old << " ns" << std::endl;
    std::cout << "2. newRand: " << total_new << " ns" << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << result << std::endl;

	return 0;
}
