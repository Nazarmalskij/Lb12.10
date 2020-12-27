#include "pch.h"
#include "CppUnitTest.h"
#include "../Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1210
{
	TEST_CLASS(UnitTest1210)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int c;
			c = all_lines();
			Assert::AreEqual(c,0);

		}
	};
}
