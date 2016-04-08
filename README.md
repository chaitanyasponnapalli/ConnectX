Chaitanya ponnapalli


Bugs:
1. In inBounds(int w, int h) method, if the value of height is in bounds(valid value) but width is invalid(out of bounds), the flag(inside) is set to true. This will result in the return value for an invalid location, to be returned as true, indicating the invalid location to be in bounds. This results in incorrect bound checking. 
The branch condition should be:
if( (w>=width || w<0) ||   (h<0 || h>=height ) ){
	return false;
}

Eg: w = -5, h = 10. When inbounds(-5,10) is called, true is returned. However, these are invalid dimensions.

This is covered in the test case: TEST(ConnectXTest, InvalidNegPiecePlaceCheck). In this testcase, eventhough player places the piece in an invalid column, the piece is still placed in some location. The functionality should be such that, the inbounds should return false and the player just loses his turn.

2. The second bug in the code is when the at(int w, int h) function is called after placing a piece at some valid location. When this function is called for some out of bounds location, instead of returning INVALID, it shows that the location is EMPTY.

Eg: As seen in the testcase TEST(ConnectXTest, singleInvalidCheck), when the piece is placed at some valid location(which is in bounds for dimensions (10,5,3)) after which an invalid location is checked, such as (12,1), instead of showing the location as INVALID, EMPTY is returned for that location.

3. The third bug, which is present in the code, is when a piece is placed at some invalid location(at column -1). After this, when a valid location is checked, then the code breaks. A double free corruption is thrown. The code should just ignore the invalid place request and turn should be toggled. Also, the valid location which is checked, should just return EMPTY.

This is covered in the test case, TEST(ConnectXTest, InvalidExceptionCheck). It is commented out because, the exception breaks the test cases.

4. The fourth bug occurs when a piece is placed at some invalid location, which is out of bounds. This should just ignore the place request with the player losing his turn. However, the piece is placed at some random valid solution. This is incorrect, because the value at this invalid(out of bounds) column is considered as EMPTY, while it is infact supposed to be INVALID.

This is covered in the test case TEST(ConnectXTest, InvalidPiecePlacement).

5. Due to the bug in the inBounds function, the branch condition, at(column,i)==EMPTY as TRUE and inBounds(column,i) as FALSE can never be checked(code coverage for this is 0).
