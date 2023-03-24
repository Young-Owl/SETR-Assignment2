#include "unity.h"
#include "cmdproc.h"

void setUp(void)
{
	resetCmdString();
	return;
}
void tearDown(void)
{
	return;
}

void test_CMD_newCmdChar(void)
{	
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('a'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('.'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('!'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('5'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('%'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('º'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('ç'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('A'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('¨'));
	TEST_ASSERT_EQUAL_INT(CMD_FOUND, newCmdChar('~'));

	TEST_ASSERT_EQUAL_INT(CMD_ERROR_STRING, newCmdChar('.'));
}

void test_MyVectorLib_Find_AreThere(void)
{
	TEST_ASSERT_EQUAL_INT(1, MyVectorLib_Find(0));
	TEST_ASSERT_EQUAL_INT(2, MyVectorLib_Find(27));
	TEST_ASSERT_EQUAL_INT(5, MyVectorLib_Find(900));
	TEST_ASSERT_EQUAL_INT(8, MyVectorLib_Find(999));
}

void test_MyVectorLib_Len_RightSize(void)
{
	TEST_ASSERT_EQUAL_INT(8, MyVectorLib_Len());
}

int main(void)
{
	UNITY_BEGIN();
	
	RUN_TEST(test_CMD_newCmdChar);
		
	return UNITY_END();
}
