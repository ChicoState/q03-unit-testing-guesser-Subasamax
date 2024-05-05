/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};



// constructor

TEST(GuesserTest, pass_of_length_5)
{
	Guesser guess = Guesser("hello");
	bool actual = guess.match("hello");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, pass_of_length_33_gets_cut_to_32)
{
	Guesser guess = Guesser("HelloThisPasswordIsLengthThirty33");  
	bool actual = guess.match("HelloThisPasswordIsLengthThirty3");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, pass_of_above_length_50_gets_cut_to_32)
{
	Guesser guess = Guesser("HelloThisPasswordIsAboveLengthFiftyToTestTheClassConstructor");    
	bool actual = guess.match("HelloThisPasswordIsAboveLengthFi");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, pass_of_above_length_50_gets_cut_to_32_guess_original_pass)
{
	Guesser guess = Guesser("HelloThisPasswordIsAboveLengthFiftyToTestTheClassConstructor");    
	bool actual = guess.match("HelloThisPasswordIsAboveLengthFiftyToTestTheClassConstructor");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, pass_of_only_spaces)
{
	Guesser guess = Guesser("     ");  
	bool actual = guess.match("     ");
	ASSERT_EQ(true, actual);
}


TEST(GuesserTest, pass_of_length_0)
{
	Guesser guess = Guesser("");  
	bool actual = guess.match("");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, pass_of_length_0_guess_space)
{
	Guesser guess = Guesser("");  
	bool actual = guess.match(" ");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, constructor_sets_remaingin_guess_correctly)
{
	Guesser guess = Guesser("");  
	int actual = guess.remaining();
	ASSERT_EQ(3, actual);
}

/// end construct


// distance test


TEST(GuesserTest, no_distance)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorld");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, distance_test_of_distance_of_1_char_diff)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWarld");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, distance_test_of_distance_of_2_char_diff)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HekloWarld");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, distance_test_of_distance_of_3_char_diff)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("MekloWarld");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_test_of_distance_of_1_extra)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorld_");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(true, actual);
}


TEST(GuesserTest, distance_test_of_distance_of_2_extra)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorld__");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(true, actual);
}


TEST(GuesserTest, distance_test_of_distance_of_3_extra)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorld__K");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_test_of_10_extra)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorld__________");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_test_of_distance_of_2_mixed)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWarld_");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, distance_test_of_distance_of_3_mixed)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWarld__");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_test_of_distance_of_10_mixed)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("PeOloWaZld__PKU");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(false, actual);
}



// lock tests


TEST(GuesserTest, distance_of_guess_above_two_gets_locked)
{
	Guesser guess = Guesser("Hello");
	bool actual = guess.match("Hello003");
	actual = guess.match("Hello"); 
	ASSERT_EQ(false, actual);
}


TEST(GuesserTest, distance_of_guess_above_two_gets_locked_remaining_guess_normal)
{
	Guesser guess = Guesser("Hello");
	bool testActual = guess.match("Hello003");
	int actual  = guess.remaining();
	ASSERT_EQ(2, actual);
}

TEST(GuesserTest, distance_of_guess_above_two_gets_locked_use_guesses_to_one)
{
	Guesser guess = Guesser("Hello");
	bool testActual = guess.match("Hello003");
	testActual = guess.match("Hello");
	int actual  = guess.remaining();
	ASSERT_EQ(1, actual);
}

TEST(GuesserTest, distance_of_guess_above_two_gets_locked_use_guesses_to_zero)
{
	Guesser guess = Guesser("Hello");
	bool testActual = guess.match("Hello003");
	testActual = guess.match("Hello");
	testActual = guess.match("Hello");
	int actual  = guess.remaining();
	ASSERT_EQ(0, actual);
}

TEST(GuesserTest, distance_of_guess_above_two_gets_locked_can_guess_but_never_succeed)
{
	Guesser guess = Guesser("Hello");
	bool testActual = guess.match("Hello003");
	testActual = guess.match("Hello");
	testActual = guess.match("Hello");
	int actual  = guess.remaining();
	ASSERT_EQ(0, actual);
}


TEST(GuesserTest, incorrect_gueses_until_remaing_is_zero_then_lock)
{
	Guesser guess = Guesser("Hello");
	bool testActual = guess.match("Hello03");
	testActual = guess.match("Hello0");
	testActual = guess.match("Hellok");
	testActual = guess.match("Hello");
	int actual  = guess.remaining();
	ASSERT_EQ(0, actual);
}


TEST(GuesserTest, lower_case_locks_if_distance_of_three)
{
	Guesser guess = Guesser("HelloWorlD");  
	bool actual = guess.match("helloworld");
	actual = guess.match("HellowWrlD");
	ASSERT_EQ(false, actual);
}



TEST(GuesserTest,  upper_case_locks_if_distance_of_three)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HELLoWorld");
	actual = guess.match("HelloWorld");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, mixed_case_locks_if_distance_of_three)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HeLowoRld");
	ASSERT_EQ(false, actual);
}

/// lock test end

// Match test


TEST(GuesserTest, Correct_guess_resets_remaining_guess_to_3)
{
	Guesser guess = Guesser("HelloWorld");  
	bool TempActual = guess.match("HelloWorld");
	int actual = guess.remaining();
	ASSERT_EQ(3, actual);
}

TEST(GuesserTest, Correct_guess_resets_remaining_guess_to_3_after_two_guesses)
{
	Guesser guess = Guesser("HelloWorld");  
	bool TempActual = guess.match("HelloWorl_d");
	TempActual = guess.match("HelloWorld_");
	TempActual = guess.match("HelloWorld");
	int actual = guess.remaining();
	ASSERT_EQ(3, actual);
}

TEST(GuesserTest, correct_guess_after_remaining_zero_doesnt_reset_remaining)
{
	Guesser guess = Guesser("HelloWorld");  
	bool TempActual = guess.match("HelloWorl_d");
	TempActual = guess.match("HelloWorld_");
	TempActual = guess.match("HelloWorld_");
	TempActual = guess.match("HelloWorld");
	int actual = guess.remaining();
	ASSERT_EQ(0, actual);
}


TEST(GuesserTest, correct_guess_always_resets_remaining_to_3)
{
	Guesser guess = Guesser("HelloWorld");  
	bool TempActual = guess.match("HelloWorld");
	TempActual = guess.match("HelloWorld");
	TempActual = guess.match("HelloWorld");
	TempActual = guess.match("HelloWorld");
	int actual = guess.remaining();
	ASSERT_EQ(3, actual);
}


TEST(GuesserTest, distance_of_one_char_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HeKloWorld");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_of_two_char_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HeKloWPrld");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_of_multiple_char_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("GeKlIWPrSd");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_of_extra_char_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorldK");
	ASSERT_EQ(false, actual);
}
TEST(GuesserTest, distance_of_two_extra_char_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorldKp");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_of_three_extra_char_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorldKp_");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_of_extra_char_upper_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorldK");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_of_extra_char_lower_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorldk");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_of_extra_mixed_lower_upper__fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HelloWorldkL_76");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, lower_case_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("helloworld");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, upper_case_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HELLOWORLD");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, mixed_case_fails_match)
{
	Guesser guess = Guesser("HelloWorld");  
	bool actual = guess.match("HeLoWoRlD");
	ASSERT_EQ(false, actual);
}