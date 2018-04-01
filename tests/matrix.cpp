#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t<int> matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("reading matrix")
{
    std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix;
    std::istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}


TEST_CASE("copying matrix")
{
    std::string input
    {
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int> matrix;
    std::istringstream istream{ input };
    REQUIRE( matrix.read(istream));
    
    matrix_t<int> copy(matrix);
    REQUIRE( copy.rows() == 3);
    REQUIRE( copy.collumns() == 3);
}
    
TEST_CASE("adding matrix")
{
    std::string input_A
    {
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    std::string input_B
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
    std::string input_C
    {
        "3, 3\n"
        "2 2 2\n"
        "3 3 3\n"
        "4 4 4" };
	
    matrix_t<int> A, B, C;
    std::istringstream istream1{ input_A };
    std::istringstream istream2{ input_B };
    std::istringstream istream3{ input_B };
	
    REQUIRE(A.read(istream1));
    REQUIRE(B.read(istream2));
    REQUIRE(C.read(istream3));

    REQUIRE_NOTHROW( A.collumns() == B.collumns() && A.rows() == B.rows() );
	  

    REQUIRE( ( A + B ) == C);
}

TEST_CASE("adding matrix double")
{
    std::string input_A
    {
        "3, 3\n"
        "2.5 2.5 2.5\n"
        "2.5 2.5 2.5\n"
        "2.5 2.5 2.5" };
    std::string input_B
    {
        "3, 3\n"
        "2.5 2.5 2.5\n"
        "2.5 2.5 2.5\n"
        "2.5 2.5 2.5" };
    std::string input_C
    {
        "3, 3\n"
        "5 5 5\n"
        "5 5 5\n"
        "5 5 5" };
    matrix_t<double> A, B, C;
	
    std::istringstream istream1{ input_A };
    std::istringstream istream2{ input_B };
    std::istringstream istream3{ input_C }; 
	
    REQUIRE(A.read(istream1));
    REQUIRE(B.read(istream2));
    REQUIRE(C.read(istream3));

    REQUIRE_NOTHROW( A.collumns() == B.collumns() && A.rows() == B.rows() );
	  
    REQUIRE( ( A + B ) == C );
}

TEST_CASE("substracting matrix")
{
    std::string input_A
    {
        "3, 3\n"
        "3 3 3\n"
        "2 2 2\n"
        "3 3 3" };
    std::string input_B
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
    std::string input_C
    {
        "3, 3\n"
        "2 2 2\n"
        "1 1 1\n"
        "2 2 2" };
    matrix_t<int> A, B, C;
    std::istringstream istream1{ input_A };
    std::istringstream istream2{ input_B };
    std::istringstream istream3{ input_C };
	
    REQUIRE( A.read(istream1));
    REQUIRE( B.read(istream2));
    REQUIRE( C.read(istream3));
    
    REQUIRE_NOTHROW( A.collumns() == B.collumns() && A.rows() == B.rows() );
    
    REQUIRE( ( A - B ) == C );
}

TEST_CASE ("multiplication matrix")
{
    std::string input_A
    {
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    std::string input_B
    {
        "3, 3\n"
        "3 3 3\n"
        "4 4 4\n"
        "5 5 5" };
    std::string input_C
    {
        "3, 3\n"
        "12 12 12\n"
        "24 24 24\n"
        "36 36 36" };
	
    matrix_t<int> A, B, C;
	
    std::istringstream istream1{ input_A };
    std::istringstream istream2{ input_B };
    std::istringstream istream3{ input_C };
	
    REQUIRE(A.read(istream1));
    REQUIRE(B.read(istream2));
    REQUIRE(C.read(istream3));
    
    REQUIRE_NOTHROW( A.collumns() == B.rows() );
       
    REQUIRE( ( A * B ) == C );
}

TEST_CASE ("assignment matrix")
{
    std::string input
    {
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    std::string input2
    {
        "3, 3\n"
        "3 3 3\n"
        "4 4 4\n"
        "5 5 5" };
    matrix_t<int> matrix1, matrix2;
    std::istringstream istream1{ input };
    std::istringstream istream2{ input2 };
    REQUIRE(matrix1.read(istream1));
    REQUIRE(matrix2.read(istream2));
    
    REQUIRE_NOTHROW( matrix1.collumns() == matrix2.collumns() && matrix1.rows() == matrix2.rows() );
    
    matrix1 = matrix2;
    std::ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE( input2 == ostream.str() );
}   

TEST_CASE ("assignment with multiplication")
{
    std::string input_A
    {
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" 
    };
	
    std::string input_B
    {
        "3, 3\n"
        "3 3 3\n"
        "4 4 4\n"
        "5 5 5"
    };
	
    std::string input_C
    {
        "3, 3\n"
        "12 12 12\n"
        "24 24 24\n"
        "36 36 36" 
    };
    
    matrix_t<int> A, B, C;
	
    std::istringstream istream1{ input_A };
    std::istringstream istream2{ input_B };
    std::istringstream istream3{ input_C };
	
    REQUIRE(A.read(istream1));
    REQUIRE(B.read(istream1));
    REQUIRE(C.read(istream2));
    
    REQUIRE_NOTHROW( A.collumns() == B.rows() );
    

    REQUIRE ( ( A * B ) == C );
}

TEST_CASE("assignment with adding")
{
    std::string input
    {
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    std::string input2
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
    std::string input3
    {
        "3, 3\n"
        "2 2 2\n"
        "3 3 3\n"
        "4 4 4" };
    
    matrix_t<int> matrix1, matrix2;
    std::istringstream istream1{ input };
    std::istringstream istream2{ input2 };
    REQUIRE(matrix1.read(istream1));
    REQUIRE(matrix2.read(istream2));
    
    REQUIRE_NOTHROW( matrix1.collumns() == matrix2.collumns() && matrix1.rows() == matrix2.rows() );
    
    matrix1 += matrix2;
    std::ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE (input3 == ostream.str());
}

TEST_CASE("assignment with substraction")
{
    std::string input
    {
        "3, 3\n"
        "3 3 3\n"
        "2 2 2\n"
        "3 3 3" };
    std::string input2
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1" };
    std::string input3
    {
        "3, 3\n"
        "2 2 2\n"
        "1 1 1\n"
        "2 2 2" };
    
    matrix_t<int> matrix1, matrix2;
    std::istringstream istream1{ input };
    std::istringstream istream2{ input2 };
    REQUIRE(matrix1.read(istream1));
    REQUIRE(matrix2.read(istream2));
    
    REQUIRE_NOTHROW( matrix1.collumns() == matrix2.collumns() && matrix1.rows() == matrix2.rows() );
    
    matrix1 -= matrix2;
    std::ostringstream ostream;
    matrix1.write( ostream );
    
    REQUIRE (input3 == ostream.str());
}


