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
	/* First 10 characters to fill the string size. */
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('a'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('.'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('!'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('5'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('X'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('P'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('o'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('S'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('#'));
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('<'));

	/* Test for error. */
	TEST_ASSERT_EQUAL_INT(CMD_ERROR_STRING, newCmdChar('.'));

	/* Reseting and trying again to check if the string is cleared. */
	resetCmdString();
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, newCmdChar('a'));
}

void test_CMD_CmdProcess_CommandFound(void)
{
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, cmdProcessor());

	resetCmdString();
	newCmdChar('#');
	newCmdChar('S');
	newCmdChar((unsigned char)('S'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, cmdProcessor());
}

void test_CMD_CmdProcess_CommandNotFound(void)
{
	resetCmdString();
	newCmdChar('#');
	newCmdChar('A');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(CMD_INVALID, cmdProcessor());
}

void test_CMD_CmdProcess_ErrorParameters(void)
{
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('A');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+'A'+'2'+'3'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(STR_WRONG_FORMAT, cmdProcessor());

	resetCmdString();
	newCmdChar('#');
	newCmdChar('S');
	newCmdChar('1');
	newCmdChar((unsigned char)('S'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(CS_ERROR, cmdProcessor());
}

void test_CMD_CmdProcess_ErrorCS(void)
{
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+'A'+'2'+'3'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(CS_ERROR, cmdProcessor());

	resetCmdString();
	newCmdChar('#');
	newCmdChar('S');
	newCmdChar((unsigned char)('A'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(CS_ERROR, cmdProcessor());
}

void test_CMD_CmdProcess_ErrorEOF(void)
{
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
	newCmdChar('3');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(CMD_ERROR_STRING, cmdProcessor());

	resetCmdString();
	newCmdChar('#');
	newCmdChar('S');
	newCmdChar((unsigned char)('S'));
	newCmdChar('3');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(CMD_ERROR_STRING, cmdProcessor());
}

void test_CMD_CmdProcess_ErrorSOF(void)
{
	resetCmdString();
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
	newCmdChar('3');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(STR_WRONG_FORMAT, cmdProcessor());

	resetCmdString();
	TEST_ASSERT_EQUAL_INT(CMD_ERROR_STRING, cmdProcessor());
}

int main(void)
{
	UNITY_BEGIN();
	
	RUN_TEST(test_CMD_newCmdChar);
	RUN_TEST(test_CMD_CmdProcess_CommandFound);
	RUN_TEST(test_CMD_CmdProcess_CommandNotFound);
	RUN_TEST(test_CMD_CmdProcess_ErrorParameters);
	RUN_TEST(test_CMD_CmdProcess_ErrorCS);
	RUN_TEST(test_CMD_CmdProcess_ErrorEOF);
	RUN_TEST(test_CMD_CmdProcess_ErrorSOF);
		
	return UNITY_END();
}
