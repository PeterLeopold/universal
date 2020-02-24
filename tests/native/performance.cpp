//  performance.cpp : performance benchmarking for block binary number arithmetic
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <string>
#include <chrono>

//#include <universal/integer/integer.hpp>
#include <universal/native/blockbinary.hpp>

// test helpers, such as, ReportTestResults
#include "../utils/test_helpers.hpp"
#include "../utils/performance_runner.hpp"

// workload for testing shift operations on integer types
template<typename IntegerType>
void ShiftPerformanceWorkload(size_t NR_OPS) {
	IntegerType a = 0xFFFFFFFFFFFFFFFF;
	for (uint64_t i = 0; i < NR_OPS; ++i) {
		a >>= 13;
		a <<= 37;
	}
}

// test performance of shift operator on integer<> class
void TestShiftOperatorPerformance() {
	using namespace std;
	cout << endl << "Logical shift operator performance" << endl;

	uint64_t NR_OPS = 1000000;

	PerformanceRunner("blockbinary<16>   shifts        ", ShiftPerformanceWorkload< sw::unum::blockbinary<16> >, NR_OPS);
	PerformanceRunner("blockbinary<32>   shifts        ", ShiftPerformanceWorkload< sw::unum::blockbinary<32> >, NR_OPS);
	PerformanceRunner("blockbinary<64>   shifts        ", ShiftPerformanceWorkload< sw::unum::blockbinary<64> >, NR_OPS);
	PerformanceRunner("blockbinary<128>  shifts        ", ShiftPerformanceWorkload< sw::unum::blockbinary<128> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<256>  shifts        ", ShiftPerformanceWorkload< sw::unum::blockbinary<256> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<512>  shifts        ", ShiftPerformanceWorkload< sw::unum::blockbinary<512> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<1024> shifts        ", ShiftPerformanceWorkload< sw::unum::blockbinary<1024> >, NR_OPS / 16);
}

void TestBlockPerformanceOnShift() {
	using namespace std;
	cout << endl << "Block size performance on logical shift operators" << endl;

	uint64_t NR_OPS = 1000000;

	PerformanceRunner("blockbinary<16,uint8>    shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<16, uint8_t> >, NR_OPS);
	PerformanceRunner("blockbinary<16,uint16>   shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<16, uint16_t> >, NR_OPS);

	PerformanceRunner("blockbinary<32,uint8>    shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<32, uint8_t> >, NR_OPS);
	PerformanceRunner("blockbinary<32,uint16>   shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<32, uint16_t> >, NR_OPS);
	PerformanceRunner("blockbinary<32,uint32>   shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<32, uint32_t> >, NR_OPS);

	PerformanceRunner("blockbinary<64,uint8>    shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<64, uint8_t> >, NR_OPS);
	PerformanceRunner("blockbinary<64,uint16>   shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<64, uint16_t> >, NR_OPS);
	PerformanceRunner("blockbinary<64,uint32>   shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<64, uint32_t> >, NR_OPS);

	PerformanceRunner("blockbinary<128,uint8>   shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<128, uint8_t> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<128,uint16>  shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<128, uint16_t> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<128,uint32>  shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<128, uint32_t> >, NR_OPS / 2);

	PerformanceRunner("blockbinary<256,uint8>   shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<256, uint8_t> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<256,uint16>  shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<256, uint16_t> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<256,uint32>  shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<256, uint32_t> >, NR_OPS / 4);

	PerformanceRunner("blockbinary<512,uint8>   shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<1024, uint8_t> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<512,uint16>  shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<1024, uint16_t> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<512,uint32>  shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<1024, uint32_t> >, NR_OPS / 8);

	PerformanceRunner("blockbinary<1024,uint8>  shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<1024, uint8_t> >, NR_OPS / 16);
	PerformanceRunner("blockbinary<1024,uint16> shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<1024, uint16_t> >, NR_OPS /16);
	PerformanceRunner("blockbinary<1024,uint32> shifts  ", ShiftPerformanceWorkload< sw::unum::blockbinary<1024, uint32_t> >, NR_OPS / 16);
}

template<typename IntegerType>
void AdditionSubtractionWorkload(size_t NR_OPS) {
	IntegerType a, b, c, d;
	a = b = c = d = 0xFFFFFFFFFFFFFFFF;
	for (uint64_t i = 0; i < NR_OPS; ++i) {
		c = a + b;
		a = c - b;
	}
}

template<typename IntegerType>
void MultiplicationWorkload(size_t NR_OPS) {
	IntegerType a, b, c, d;
	a = b = c = d = 0xFFFFFFFFFFFFFFFF;
	for (uint64_t i = 0; i < NR_OPS; ++i) {
		c = a * b;
		c.clear(); // reset to zero so d = c is fast
		d = c;
	}
}

template<typename IntegerType>
void DivisionWorkload(size_t NR_OPS) {
	IntegerType a, b, c, d;
	a = b = c = d = 0xFFFFFFFFFFFFFFFF;
	for (uint64_t i = 0; i < NR_OPS; ++i) {
		c = a / b;
		c.clear(); // reset to zero so d = c is fast
		d = c;
	}
}

template<typename IntegerType>
void RemainderWorkload(size_t NR_OPS) {
	IntegerType a, b, c, d;
	a = b = c = d = 0xFFFFFFFFFFFFFFFF;
	for (uint64_t i = 0; i < NR_OPS; ++i) {
		c = a % b;
		c.clear(); // reset to zero so d = c is fast
		d = c;
	}
}

void TestArithmeticOperatorPerformance() {
	using namespace std;
	cout << endl << "Arithmetic operator performance" << endl;

	size_t NR_OPS = 1000000;

	PerformanceRunner("blockbinary<16>   add/subtract  ", AdditionSubtractionWorkload< sw::unum::blockbinary<16> >, NR_OPS);
	PerformanceRunner("blockbinary<32>   add/subtract  ", AdditionSubtractionWorkload< sw::unum::blockbinary<32> >, NR_OPS);
	PerformanceRunner("blockbinary<64>   add/subtract  ", AdditionSubtractionWorkload< sw::unum::blockbinary<64> >, NR_OPS);
	PerformanceRunner("blockbinary<128>  add/subtract  ", AdditionSubtractionWorkload< sw::unum::blockbinary<128> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<256>  add/subtract  ", AdditionSubtractionWorkload< sw::unum::blockbinary<256> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<512>  add/subtract  ", AdditionSubtractionWorkload< sw::unum::blockbinary<512> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<1024> add/subtract  ", AdditionSubtractionWorkload< sw::unum::blockbinary<1024> >, NR_OPS / 16);

	/*
	NR_OPS = 1024 * 32;
	PerformanceRunner("blockbinary<16>   division      ", DivisionWorkload< sw::unum::blockbinary<16> >, NR_OPS);
	PerformanceRunner("blockbinary<32>   division      ", DivisionWorkload< sw::unum::blockbinary<32> >, NR_OPS);
	PerformanceRunner("blockbinary<64>   division      ", DivisionWorkload< sw::unum::blockbinary<64> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<128>  division      ", DivisionWorkload< sw::unum::blockbinary<128> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<512>  division      ", DivisionWorkload< sw::unum::blockbinary<512> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<1024> division      ", DivisionWorkload< sw::unum::blockbinary<1024> >, NR_OPS / 16);

	NR_OPS = 1024 * 32;
	PerformanceRunner("blockbinary<16>   remainder     ", RemainderWorkload< sw::unum::blockbinary<16> >, NR_OPS);
	PerformanceRunner("blockbinary<32>   remainder     ", RemainderWorkload< sw::unum::blockbinary<32> >, NR_OPS);
	PerformanceRunner("blockbinary<64>   remainder     ", RemainderWorkload< sw::unum::blockbinary<64> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<128>  remainder     ", RemainderWorkload< sw::unum::blockbinary<128> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<512>  remainder     ", RemainderWorkload< sw::unum::blockbinary<512> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<1024> remainder     ", RemainderWorkload< sw::unum::blockbinary<1024> >, NR_OPS / 16);

	// multiplication is the slowest operator

	NR_OPS = 1024 * 32;
	PerformanceRunner("blockbinary<16>   multiplication", MultiplicationWorkload< sw::unum::blockbinary<16> >, NR_OPS);
	PerformanceRunner("blockbinary<32>   multiplication", MultiplicationWorkload< sw::unum::blockbinary<32> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<64>   multiplication", MultiplicationWorkload< sw::unum::blockbinary<64> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<128>  multiplication", MultiplicationWorkload< sw::unum::blockbinary<128> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<512>  multiplication", MultiplicationWorkload< sw::unum::blockbinary<512> >, NR_OPS / 16);
	PerformanceRunner("blockbinary<1024> multiplication", MultiplicationWorkload< sw::unum::blockbinary<1024> >, NR_OPS / 32);
	*/
}

void TestBlockPerformanceOnAdd() {
	using namespace std;
	cout << endl << "block size performance" << endl;

	size_t NR_OPS = 1000000;

	PerformanceRunner("blockbinary<16,uint8>     add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<16, uint8_t> >, NR_OPS);
	PerformanceRunner("blockbinary<16,uint16>    add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<16, uint16_t> >, NR_OPS);
	PerformanceRunner("blockbinary<32,uint8>     add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<32, uint8_t> >, NR_OPS);
	PerformanceRunner("blockbinary<32,uint16>    add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<32, uint16_t> >, NR_OPS);
	PerformanceRunner("blockbinary<32,uint32>    add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<32, uint32_t> >, NR_OPS);
	PerformanceRunner("blockbinary<64,uint8>     add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<64, uint8_t> >, NR_OPS);
	PerformanceRunner("blockbinary<64,uint16>    add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<64, uint16_t> >, NR_OPS);
	PerformanceRunner("blockbinary<64,uint32>    add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<64, uint32_t> >, NR_OPS);
	PerformanceRunner("blockbinary<128,uint8>    add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<128, uint8_t> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<128,uint16>   add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<128, uint16_t> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<128,uint32>   add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<128, uint32_t> >, NR_OPS / 2);
	PerformanceRunner("blockbinary<256,uint8>    add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<256, uint8_t> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<256,uint16>   add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<256, uint16_t> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<256,uint32>   add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<256, uint32_t> >, NR_OPS / 4);
	PerformanceRunner("blockbinary<512,uint8>    add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<512, uint8_t> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<512,uint16>   add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<512, uint16_t> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<512,uint32>   add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<512, uint32_t> >, NR_OPS / 8);
	PerformanceRunner("blockbinary<1024,uint8>   add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<1024, uint8_t> >, NR_OPS / 16);
	PerformanceRunner("blockbinary<1024,uint16>  add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<1024, uint16_t> >, NR_OPS / 16);
	PerformanceRunner("blockbinary<1024,uint32>  add   ", AdditionSubtractionWorkload< sw::unum::blockbinary<1024, uint32_t> >, NR_OPS / 16);
}

#define MANUAL_TESTING 0
#define STRESS_TESTING 0

int main()
try {
	using namespace std;
	using namespace sw::unum;

	std::string tag = "Integer operator performance benchmarking";

#if MANUAL_TESTING

	TestShiftOperatorPerformance();
	TestArithmeticOperatorPerformance();

	cout << "done" << endl;

	return EXIT_SUCCESS;
#else
	std::cout << tag << std::endl;

	int nrOfFailedTestCases = 0;

	TestShiftOperatorPerformance();
	TestArithmeticOperatorPerformance();

	TestBlockPerformanceOnShift();
	TestBlockPerformanceOnAdd();

#if STRESS_TESTING

#endif // STRESS_TESTING
	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);

#endif // MANUAL_TESTING
}
catch (char const* msg) {
	std::cerr << msg << '\n';
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Uncaught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << '\n';
	return EXIT_FAILURE;
}

/*
ETLO
Date run : 2/23/2020
Processor: Intel Core i7-7500 CPU @ 2.70GHz, 2 cores, 4 threads, 15W mobile processor
Memory   : 16GB
System   : 64-bit Windows 10 Pro, Version 1803, x64-based processor, OS build 17134.165

Integer operator performance benchmarking

Logical shift operator performance
integer<16>   shifts            1000000 per       0.0099091sec -> 100 Mops/sec
integer<32>   shifts            1000000 per       0.0453919sec ->  22 Mops/sec
integer<64>   shifts            1000000 per        0.178824sec ->   5 Mops/sec
integer<128>  shifts             500000 per        0.269217sec ->   1 Mops/sec
integer<256>  shifts             250000 per        0.266083sec -> 939 Kops/sec
integer<512>  shifts             125000 per        0.285764sec -> 437 Kops/sec
integer<1024> shifts              62500 per        0.277351sec -> 225 Kops/sec

Arithmetic operator performance
integer<16>   add/subtract      1000000 per       0.0095743sec -> 104 Mops/sec
integer<32>   add/subtract      1000000 per       0.0148453sec ->  67 Mops/sec
integer<64>   add/subtract      1000000 per       0.0474723sec ->  21 Mops/sec
integer<128>  add/subtract       500000 per       0.0382776sec ->  13 Mops/sec
integer<256>  add/subtract       250000 per       0.0268772sec ->   9 Mops/sec
integer<512>  add/subtract       125000 per       0.0275169sec ->   4 Mops/sec
integer<1024> add/subtract        62500 per       0.0294444sec ->   2 Mops/sec
integer<16>   division            32768 per       0.0050946sec ->   6 Mops/sec
integer<32>   division            32768 per       0.0083216sec ->   3 Mops/sec
integer<64>   division            16384 per       0.0074452sec ->   2 Mops/sec
integer<128>  division             8192 per       0.0071203sec ->   1 Mops/sec
integer<512>  division             4096 per       0.0148553sec -> 275 Kops/sec
integer<1024> division             2048 per       0.0154237sec -> 132 Kops/sec
integer<16>   remainder           32768 per       0.0051223sec ->   6 Mops/sec
integer<32>   remainder           32768 per       0.0082141sec ->   3 Mops/sec
integer<64>   remainder           16384 per       0.0077429sec ->   2 Mops/sec
integer<128>  remainder            8192 per       0.0078737sec ->   1 Mops/sec
integer<512>  remainder            4096 per       0.0148961sec -> 274 Kops/sec
integer<1024> remainder            2048 per       0.0150371sec -> 136 Kops/sec
integer<16>   multiplication      32768 per       0.0232329sec ->   1 Mops/sec
integer<32>   multiplication      16384 per       0.0424617sec -> 385 Kops/sec
integer<64>   multiplication       8192 per         0.08589sec ->  95 Kops/sec
integer<128>  multiplication       4096 per        0.166093sec ->  24 Kops/sec
integer<512>  multiplication       2048 per         1.33028sec ->   1 Kops/sec
integer<1024> multiplication       1024 per         2.58557sec -> 396  ops/sec
*/