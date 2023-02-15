#include <UnitTest/stdafx.h>
#include <UnitTest/UnitTest.h>
#include <core/smartview/SmartView.h>
#include <core/addin/mfcmapi.h>
#include <core/addin/addin.h>
#include <core/utility/strings.h>

namespace SmartViewTest
{
#define TEST(PARSERTYPE, NAME, NUM) \
	TEST_METHOD(PARSERTYPE##_##NUM) \
	{ \
		test(parserType::PARSERTYPE, IDR_SV##NAME##NUM##IN, IDR_SV##NAME##NUM##OUT); \
	}

	TEST_CLASS(SmartViewTest)
	{
	private:
		// Without this, clang gets weird
		static const bool dummy_var = true;

		void test(
			const std::wstring testName, parserType structType, std::vector<BYTE> hex, const std::wstring expected)
			const
		{
			auto actual = smartview::InterpretBinary({static_cast<ULONG>(hex.size()), hex.data()}, structType, nullptr)
							  ->toString();
			unittest::AreEqualEx(expected, actual, testName.c_str());

			if (unittest::parse_all)
			{
				for (const auto parser : SmartViewParserTypeArray)
				{
					try
					{
						actual = smartview::InterpretBinary(
									 {static_cast<ULONG>(hex.size()), hex.data()}, parser.type, nullptr)
									 ->toString();
					} catch (const int exception)
					{
						Logger::WriteMessage(strings::format(
												 L"Testing %ws failed at %ws with error 0x%08X\n",
												 testName.c_str(),
												 addin::AddInStructTypeToString(parser.type).c_str(),
												 exception)
												 .c_str());
						Assert::Fail();
					}
				}
			}
		}

		void test(parserType structType, DWORD hexNum, DWORD expectedNum) const
		{
			static auto handle = GetModuleHandleW(L"UnitTest.dll");
			// See comments on loadfile for best file encoding strategies for test data
			const auto testName = strings::format(L"%d/%d", hexNum, expectedNum);
			auto hex = strings::HexStringToBin(unittest::loadfile(handle, hexNum));
			const auto expected = unittest::loadfile(handle, expectedNum);
			test(testName, structType, hex, expected);
		}

	public:
		TEST_CLASS_INITIALIZE(initialize) { unittest::init(); }

		TEST_METHOD(SmartViewAddInTest1)
		{
			test(
				std::wstring(L"SmartViewAddInTest1"),
				parserType::END,
				std::vector<BYTE>{1, 2, 3, 4},
				std::wstring(L"Unknown Parser 39\r\n"
							 L"\tcb: 4 lpb: 01020304"));
		}

		TEST(ADDITIONALRENENTRYIDSEX, 1AEI, 1)
		TEST(ADDITIONALRENENTRYIDSEX, 1AEI, 2)
		TEST(ADDITIONALRENENTRYIDSEX, 1AEI, 3)
		TEST(ADDITIONALRENENTRYIDSEX, 1AEI, 4)

		TEST(APPOINTMENTRECURRENCEPATTERN, 2ARP, 1)
		TEST(APPOINTMENTRECURRENCEPATTERN, 2ARP, 2)
		TEST(APPOINTMENTRECURRENCEPATTERN, 2ARP, 3)
		TEST(APPOINTMENTRECURRENCEPATTERN, 2ARP, 4)

		TEST(CONVERSATIONINDEX, 3CI, 1)
		TEST(CONVERSATIONINDEX, 3CI, 2)
		TEST(CONVERSATIONINDEX, 3CI, 3)
		TEST(CONVERSATIONINDEX, 3CI, 4)

		TEST(ENTRYID, 4EID, 1)
		TEST(ENTRYID, 4EID, 2)
		TEST(ENTRYID, 4EID, 3)
		TEST(ENTRYID, 4EID, 4)
		TEST(ENTRYID, 4EID, 5)
		TEST(ENTRYID, 4EID, 6)
		TEST(ENTRYID, 4EID, 7)
		TEST(ENTRYID, 4EID, 8)
		TEST(ENTRYID, 4EID, 9)
		TEST(ENTRYID, 4EID, 10)
		TEST(ENTRYID, 4EID, 11)
		TEST(ENTRYID, 4EID, 12)
		TEST(ENTRYID, 4EID, 13)
		TEST(ENTRYID, 4EID, 14)
		TEST(ENTRYID, 4EID, 15)
		TEST(ENTRYID, 4EID, 16)
		TEST(ENTRYID, 4EID, 17)
		TEST(ENTRYID, 4EID, 18)
		TEST(ENTRYID, 4EID, 19)
		TEST(ENTRYID, 4EID, 20)
		TEST(ENTRYID, 4EID, 21)
		TEST(ENTRYID, 4EID, 22)
		TEST(ENTRYID, 4EID, 23)
		TEST(ENTRYID, 4EID, 24)
		TEST(ENTRYID, 4EID, 25)
		TEST(ENTRYID, 4EID, 26)
		TEST(ENTRYID, 4EID, 27)
		TEST(ENTRYID, 4EID, 28)
		TEST(ENTRYID, 4EID, 29)
		TEST(ENTRYID, 4EID, 30)
		TEST(ENTRYID, 4EID, 31)
		TEST(ENTRYID, 4EID, 32)
		TEST(ENTRYID, 4EID, 33)
		TEST(ENTRYID, 4EID, 34)
		TEST(ENTRYID, 4EID, 35)
		TEST(ENTRYID, 4EID, 36)
		TEST(ENTRYID, 4EID, 37)
		TEST(ENTRYID, 4EID, 38)
		TEST(ENTRYID, 4EID, 39)
		TEST(ENTRYID, 4EID, 40)

		TEST(ENTRYLIST, 5EL, 1)
		TEST(ENTRYLIST, 5EL, 2)

		TEST(EXTENDEDFOLDERFLAGS, 6EFF, 1)
		TEST(EXTENDEDFOLDERFLAGS, 6EFF, 2)

		TEST(EXTENDEDRULECONDITION, 7EXRULE, 1)
		TEST(EXTENDEDRULECONDITION, 7EXRULE, 2)
		TEST(EXTENDEDRULECONDITION, 7EXRULE, 3)
		TEST(EXTENDEDRULECONDITION, 7EXRULE, 4)

		TEST(FLATENTRYLIST, 8FE, 1)
		TEST(FLATENTRYLIST, 8FE, 2)
		TEST(FLATENTRYLIST, 8FE, 3)

		TEST(FOLDERUSERFIELDS, 9FUF, 1)
		TEST(FOLDERUSERFIELDS, 9FUF, 2)
		TEST(FOLDERUSERFIELDS, 9FUF, 3)
		TEST(FOLDERUSERFIELDS, 9FUF, 4)
		TEST(FOLDERUSERFIELDS, 9FUF, 5)

		TEST(GLOBALOBJECTID, 10GOID, 1)
		TEST(GLOBALOBJECTID, 10GOID, 2)

		TEST(PROPERTIES, 11PROP, 1)
		TEST(PROPERTIES, 11PROP, 2)
		TEST(PROPERTIES, 11PROP, 3)
		TEST(PROPERTIES, 11PROP, 4)
		TEST(PROPERTIES, 11PROP, 5)
		TEST(PROPERTIES, 11PROP, 6)
		TEST(PROPERTIES, 11PROP, 7)
		TEST(PROPERTIES, 11PROP, 8)

		TEST(PROPERTYDEFINITIONSTREAM, 12PROPDEF, 1)
		TEST(PROPERTYDEFINITIONSTREAM, 12PROPDEF, 2)
		TEST(PROPERTYDEFINITIONSTREAM, 12PROPDEF, 3)
		TEST(PROPERTYDEFINITIONSTREAM, 12PROPDEF, 4)
		TEST(PROPERTYDEFINITIONSTREAM, 12PROPDEF, 5)
		TEST(PROPERTYDEFINITIONSTREAM, 12PROPDEF, 6)
		TEST(PROPERTYDEFINITIONSTREAM, 12PROPDEF, 7)
		TEST(PROPERTYDEFINITIONSTREAM, 12PROPDEF, 8)

		TEST(RECIPIENTROWSTREAM, 13RECIPROW, 1)
		TEST(RECIPIENTROWSTREAM, 13RECIPROW, 2)

		TEST(RECURRENCEPATTERN, 14ARP, 1)
		TEST(RECURRENCEPATTERN, 14ARP, 2)
		TEST(RECURRENCEPATTERN, 14ARP, 3)

		TEST(RESTRICTION, 16RES, 1)
		TEST(RESTRICTION, 16RES, 2)
		TEST(RESTRICTION, 16RES, 3)
		TEST(RESTRICTION, 16RES, 4)

		TEST(RULECONDITION, 17RULECON, 1)
		TEST(RULECONDITION, 17RULECON, 2)
		TEST(RULECONDITION, 17RULECON, 3)
		TEST(RULECONDITION, 17RULECON, 4)

		TEST(SEARCHFOLDERDEFINITION, 18SF, 1)
		TEST(SEARCHFOLDERDEFINITION, 18SF, 2)
		TEST(SEARCHFOLDERDEFINITION, 18SF, 3)
		TEST(SEARCHFOLDERDEFINITION, 18SF, 4)
		TEST(SEARCHFOLDERDEFINITION, 18SF, 5)
		TEST(SEARCHFOLDERDEFINITION, 18SF, 6)
		TEST(SEARCHFOLDERDEFINITION, 18SF, 7)

		TEST(SECURITYDESCRIPTOR, 19SD, 1)
		TEST(SECURITYDESCRIPTOR, 19SD, 2)
		TEST(SECURITYDESCRIPTOR, 19SD, 3)
		TEST(SECURITYDESCRIPTOR, 19SD, 4)

		TEST(SID, 20SID, 1)
		TEST(SID, 20SID, 2)
		TEST(SID, 20SID, 3)
		TEST(SID, 20SID, 4)
		TEST(SID, 20SID, 5)

		TEST(TIMEZONEDEFINITION, 23TZD, 1)
		TEST(TIMEZONEDEFINITION, 23TZD, 2)
		TEST(TIMEZONEDEFINITION, 23TZD, 3)

		TEST(WEBVIEWPERSISTSTREAM, 24WEBVIEW, 1)
		TEST(WEBVIEWPERSISTSTREAM, 24WEBVIEW, 2)
		TEST(WEBVIEWPERSISTSTREAM, 24WEBVIEW, 3)
		TEST(WEBVIEWPERSISTSTREAM, 24WEBVIEW, 4)
		TEST(WEBVIEWPERSISTSTREAM, 24WEBVIEW, 5)
		TEST(WEBVIEWPERSISTSTREAM, 24WEBVIEW, 6)
		TEST(WEBVIEWPERSISTSTREAM, 24WEBVIEW, 7)

		TEST(NICKNAMECACHE, 25NICKNAME, 2)
		TEST(NICKNAMECACHE, 25NICKNAME, 3)
		TEST(NICKNAMECACHE, 25NICKNAME, 4)

		TEST(ENCODEENTRYID, 26EIDENCODE, 1)
		TEST(DECODEENTRYID, 27EIDDECODE, 1)

		TEST(VERBSTREAM, 28VERBSTREAM, 1)
		TEST(VERBSTREAM, 28VERBSTREAM, 2)
		TEST(VERBSTREAM, 28VERBSTREAM, 3)
		TEST(VERBSTREAM, 28VERBSTREAM, 4)
		TEST(VERBSTREAM, 28VERBSTREAM, 5)
		TEST(VERBSTREAM, 28VERBSTREAM, 6)
		TEST(VERBSTREAM, 28VERBSTREAM, 7)

		TEST(TOMBSTONE, 29TOMBSTONE, 1)
		TEST(TOMBSTONE, 29TOMBSTONE, 2)
		TEST(TOMBSTONE, 29TOMBSTONE, 3)

		TEST(PCL, 30PCL, 1)
		TEST(PCL, 30PCL, 2)
		TEST(PCL, 30PCL, 3)

		TEST(FBSECURITYDESCRIPTOR, 31FREEBUSYSID, 1)
		TEST(FBSECURITYDESCRIPTOR, 31FREEBUSYSID, 2)

		TEST(XID, 32XID, 1)
		TEST(XID, 32XID, 2)
		TEST(XID, 32XID, 3)
		TEST(XID, 32XID, 4)

		//TEST(RULEACTION, 33RULEACTION, 1)
		TEST(EXTENDEDRULEACTION, 34EXRULEACTION, 1) // OP_MOVE, OP_TAG
		TEST(EXTENDEDRULEACTION, 34EXRULEACTION, 2) // OP_DEFER_ACTION
		TEST(EXTENDEDRULEACTION, 34EXRULEACTION, 3) // OP_TAG, OP_MARK_AS_READ, OP_FORWARD, OP_COPY

		TEST(SWAPPEDTODO, 38SWAPTODO, 1)
		TEST(SWAPPEDTODO, 38SWAPTODO, 2)
	};
} // namespace SmartViewTest