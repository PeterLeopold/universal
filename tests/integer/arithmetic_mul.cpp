//  arithmetic_mul.cpp : arithmetic test suite for multiplication of abitrary precision integers
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <string>
// configure the integer arithmetic class
#define INTEGER_THROW_ARITHMETIC_EXCEPTION 1
#include <universal/integer/integer.hpp>
#include <universal/integer/numeric_limits.hpp>
// is representable
#include <universal/functions/isrepresentable.hpp>
// test helpers, such as, ReportTestResults
#include "../utils/test_helpers.hpp"
#include "../utils/integer_test_helpers.hpp"

/*
   The goal of the arbitrary integers is to provide a constrained big integer type
   that enables fast computation with exceptions for overflow, so that the type
   can be used for forward error analysis studies.
*/

#include <typeinfo>
template<typename Scalar>
void GenerateMulTest(const Scalar& x, const Scalar& y, Scalar& z) {
	using namespace sw::unum;
	z = x * y;
	std::cout << typeid(Scalar).name() << ": " << x << " * " << y << " = " << z << std::endl;
}

// ExamplePattern to check that short and integer<16> do exactly the same
void ExamplePattern() {
	short s = 0;
	GenerateMulTest<short>(2, 16, s);
	sw::unum::integer<16> z = 0;
	GenerateMulTest<sw::unum::integer<16> >(2, 16, z);
}

// enumerate a couple ratios to test representability
void ReproducibilityTestSuite() {
	for (int i = 0; i < 30; i += 3) {
		for (int j = 0; j < 70; j += 7) {
			sw::unum::reportRepresentability(i, j);
		}
	}
}

#define MANUAL_TESTING 1
#define STRESS_TESTING 0

int main()
try {
	using namespace std;
	using namespace sw::unum;

	std::string tag = "Integer Arithmetic tests failed";

#if MANUAL_TESTING

	integer<12> a, b, c;
	a = 0x8000;
	b = 0x8000;
	GenerateMulTest(a, b, c);
	ExamplePattern();
	ReproducibilityTestSuite();

	cout << "done" << endl;

	return EXIT_SUCCESS;
#else
	std::cout << "Integer Arithmetic verfication" << std::endl;

	bool bReportIndividualTestCases = false;
	int nrOfFailedTestCases = 0;

	// allocation is the only functionality of integer<N> at this time

	nrOfFailedTestCases += ReportTestResult(VerifyMultiplication<4>(tag, bReportIndividualTestCases), "integer<4>", "multiplication");
	nrOfFailedTestCases += ReportTestResult(VerifyMultiplication<6>(tag, bReportIndividualTestCases), "integer<6>", "multiplication");
	nrOfFailedTestCases += ReportTestResult(VerifyMultiplication<8>(tag, bReportIndividualTestCases), "integer<8>", "multiplication");
	nrOfFailedTestCases += ReportTestResult(VerifyMultiplication<10>(tag, bReportIndividualTestCases), "integer<10>", "multiplication");
	nrOfFailedTestCases += ReportTestResult(VerifyMultiplication<12>(tag, bReportIndividualTestCases), "integer<12>", "multiplication");

#if STRESS_TESTING

	nrOfFailedTestCases += ReportTestResult(VerifyMultiplication<14>(tag, bReportIndividualTestCases), "integer<14>", "multiplication");

	// VerifyShortMultiplication compares an integer<16> to native short type to make certain it has all the same behavior
	nrOfFailedTestCases += ReportTestResult(VerifyShortMultiplication(tag, bReportIndividualTestCases), "integer<16>", "multiplication");
	// this is a 'standard' comparision against a native int64_t which will not have overflow conditions
	nrOfFailedTestCases += ReportTestResult(VerifyMultiplication<16>(tag, bReportIndividualTestCases), "integer<16>", "multiplication");

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
