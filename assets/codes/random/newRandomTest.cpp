#include <iostream>
#include <chrono>
#include <random>


std::mt19937 gen[100'000];
uint32_t range[100'000];

std::mt19937 gen_dice[100'000];
uint32_t dice[100'000];



uint32_t newRand(uint32_t raw_rand, uint32_t max_val) {

    static std::mt19937 bad(1234);

    uint32_t current_rand = raw_rand;
    uint32_t r = (- static_cast<uint32_t>(max_val)) % max_val;

    while (true) {


    uint64_t B = static_cast<uint64_t>(current_rand) * max_val;

    uint32_t y = B & 0xFFFFFFFFULL;  // it is same as static_cast<uint32_t>(B)



    if (y >= max_val || y >= r) {
        return static_cast<uint32_t>(B >> 32);
    }
    // Mostly y >= max_val is true. Even it is false, y >= r then okay.


    current_rand = bad();
    }
}

uint32_t oldRand(int idx, uint32_t num) {
    static std::uniform_int_distribution<uint32_t> dis;

     return dis(gen[idx], std::uniform_int_distribution<uint32_t>::param_type(0, num-1));
}



/**************** main
 * **********/


int main()
{
    uint32_t result = 0;


	for (int k = 0; k < 100'000; k++){
        uint32_t p = static_cast<uint32_t>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count()
	    );
        uint32_t t1 = p + k; // Adding k just for the cause if same p occurs
	    if ( (t1 & (t1 - 1)) == 0) {
                t1 = ~t1;
	    }
	    // If t1 is 2 ^ n, then t1 will become 2^32 - 1 - t1

	    uint32_t t2 = p + k + 10000;
        if ((t2 & (t2 - 1)) == 0) t2 = ~t2;
        gen_dice[k].seed(t2);


	    gen[k].seed(t1);

	    range[k] = gen[k]();


	    dice[k] = gen_dice[k]();

	}



    auto start_old = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100'000; i++) {
        // 32 bits random maximum
        result += oldRand(i, range[i]);
    }
    auto end_old = std::chrono::high_resolution_clock::now();
    auto total_old = std::chrono::duration_cast<std::chrono::nanoseconds>(end_old - start_old).count();


    auto start_new = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 100'000; j++) {
        result += newRand(dice[j], range[j]);
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
