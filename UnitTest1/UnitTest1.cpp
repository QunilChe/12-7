#include "pch.h"
#include "CppUnitTest.h"
#include "../12,7/12,7.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Textbook* head = NULL;
			int t = isListEmpty(head);
			Assert::AreEqual(1, t);
		}
	};
}
