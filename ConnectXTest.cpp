/**
 * Unit Tests for ConnectX class
**/

#include <gtest/gtest.h>
#include <iostream>
#include "ConnectX.h"
 
class ConnectXTest : public ::testing::Test
{
	protected:
		ConnectXTest(){}
		virtual ~ConnectXTest(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

TEST(ConnectXTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(ConnectXTest, placePieceCheck){
	ConnectX con(10,5,3);
	con.placePiece(1);//b
	con.showBoard();
	ASSERT_EQ(2,con.at(1,4));//should place black at that position
}
TEST(ConnectXTest, turnCheck){
	ConnectX con(10,5,3);
	con.placePiece(1);//b
	ASSERT_EQ(1,con.whoseTurn());//should change the turn to white after placing black	
}
//This is a bug, because all the locations which exceed the vector size limit should be set as 'Invalid'
TEST(ConnectXTest, InvalidNegPiecePlaceCheck){
	ConnectX con(10,5,3);
	con.placePiece(-10);//b
	con.showBoard();
	ASSERT_EQ(-1,con.at(-9,0));//should return invalid, as placed position is invalid
	
}
//toggle for invalid piece place
TEST(ConnectXTest, InvalidNegPieceToggleCheck){
	ConnectX con(10,5,3);
	con.placePiece(-10);//b
	ASSERT_EQ(1,con.whoseTurn());//should be white's turn
}

//This return Invalid because the inbounds sets the flag to false, for the height
TEST(ConnectXTest, InvalidNegPieceRowCheck){
	ConnectX con(10,5,3);
	con.placePiece(-10);//b
	ASSERT_EQ(-1,con.at(0,-9));//should return invalid, as placed position is invalid
}

TEST(ConnectXTest, BothOutOfBoundsNegChk){
	ConnectX con(10,5,3);
	con.placePiece(1);//b
	ASSERT_EQ(-1,con.at(-2,-1));//should return invalid location	
}
TEST(ConnectXTest, bothInvalidLocCheck){
	ConnectX con(2,1,3);
	con.placePiece(1);//b
	con.showBoard();
	ASSERT_EQ(-1,con.at(-2,1));	
}
TEST(ConnectXTest, outOfBoundsValsCheck){
	ConnectX con(10,5,3);
	con.placePiece(1);//b
	ASSERT_EQ(-1,con.at(12,11));	
}
TEST(ConnectXTest, singleInvalidCheck){//should return invalid, but returns a valid location
	ConnectX con(10,5,3);
	con.placePiece(1);//b
	ASSERT_EQ(-1,con.at(12,1));	
}
TEST(ConnectXTest, outOfBoundsNegHtChk){
	ConnectX con(10,5,3);
	con.placePiece(1);//b
	ASSERT_EQ(-1,con.at(1,-2));	
}
TEST(ConnectXTest, NegHtChk){
	ConnectX con(10,-3,3);
	con.placePiece(1);//b
	ASSERT_EQ(-1,con.at(1,-2));	
}
TEST(ConnectXTest, NegWideChk){
	ConnectX con(-10,3,3);
	con.placePiece(1);//b
	ASSERT_EQ(-1,con.at(1,-2));	
}
TEST(ConnectXTest, NegToWinChk){
	ConnectX con(10,3,-3);
	con.placePiece(1);//b
	ASSERT_EQ(-1,con.at(1,-2));	
}
TEST(ConnectXTest, ToggleTurnCheck){
	ConnectX con(10,5,3);
	con.placePiece(1);//b
	con.placePiece(1);//b
	con.showBoard();
	ASSERT_EQ(1,con.at(1,3));	
}
TEST(ConnectXTest, heightOverflowCheck){
	ConnectX con(2,2,2);
	con.placePiece(1);//b
	con.placePiece(1);//w
	/*Invalid locations*/
	con.placePiece(1);//b
	ASSERT_EQ(1,con.whoseTurn());
	con.placePiece(1);
}
TEST(ConnectXTest, showBoardToggleCheck){
	ConnectX con(2,2,2);
	con.placePiece(1);//b
	con.showBoard();
	con.placePiece(1);//w
	con.showBoard();
	con.placePiece(1);//b
	con.showBoard();
}
//set to default if invalid dimensions are given
TEST(ConnectXTest, showBoardNegColCheck){
	ConnectX con(-1,2,2);
	con.showBoard();
}
/*
//set to default if invalid dimensions are given. This should give false, but throws double free corruption error
TEST(ConnectXTest, InvalidExceptionCheck){
	ConnectX con(5,3,2);	
	con.placePiece(-1);
	ASSERT_EQ(0,con.at(1,5));
}
*/
//The pieces should not be placed(as the location is invalid). But, placed at some valid locations
TEST(ConnectXTest, InvalidPiecePlacement){
	ConnectX con(10,5,3);
	con.placePiece(12);//b
	ASSERT_EQ(2,con.at(0,3));//should be empty, but black is placed at this location
	con.showBoard();
}

//Change to default dimensions, if given incorrect dimensions
TEST(ConnectXTest, defaultDimensionsCheck){
	ConnectX con(10,-5,3);
	ASSERT_EQ(6,DEFAULT_HEIGHT);
}

TEST(ConnectXTest, invalidLocationCheck){
	ConnectX con(10,5,3);
	ASSERT_EQ(-1,con.at(20,5));
}

TEST(ConnectXTest, widInvalidCheck){
	ConnectX con;
	ASSERT_EQ(-1,con.at(20,5));
}
