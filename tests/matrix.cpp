#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t matrix;
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
    matrix_t matrix;
    std::istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}

TEST_CASE("matrix copy")
{
       std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    
    matrix_t matrix;
    std::istringstream istream{ input };
    REQUIRE( matrix.read( istream ) );
    
    matrix_t copy(matrix);
    REQUIRE( copy.rows() == 3 );
    REQUIRE( copy.collumns() == 3 );
}

TEST_CASE("add, [oper+]")
{
    std::string input{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
    std::string input_two
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    matrix_t A;
    matrix_t B;
    std::istringstream istream{ input };
    std::istringstream istream_two { input_two };
    REQUIRE( A.read( istream ) );
    REQUIRE( B.read( istream_two ) );
    
    std::string solution
    {
        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3"
    };
    matrix_t C;
    std::istringstream add{ solution };
    REQUIRE( C.read(add) );
    REQUIRE ( (A + B) == C);
}

TEST_CASE("add, [oper+], double")
{
    std::string input{
        "3, 3\n"
        "1.5 1.5 1.5\n"
        "1.5 1.5 1.5\n"
        "1.5 1.5 1.5" };
    std::string input_two
    {
        "3, 3\n"
        "1.5 1.5 1.5\n"
        "1.5 1.5 1.5\n"
        "1.5 1.5 1.5"
    };
    matrix_t<double> A;
    matrix_t<double> B;
    std::istringstream istream{ input };
    std::istringstream istream_two { input_two };
    REQUIRE( A.read( istream ) );
    REQUIRE( B.read( istream_two ) );
    
    std::string solution
    {
        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3"
    };
    matrix_t<double> C;
    std::istringstream add{ solution };
    REQUIRE( C.read(add) );
    
    REQUIRE_NOTHROW( A.collumns() == B.collumns() && A.rows() == B.rows() );
    
    REQUIRE ( (A + B) == C);
}

TEST_CASE("sub, [oper-]")
{
    std::string input{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
    std::string input_two
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    matrix_t A;
    matrix_t B;
    std::istringstream istream{ input };
    std::istringstream istream_two { input_two };
    REQUIRE( A.read( istream ) );
    REQUIRE( B.read( istream_two ) );
    
    std::string solution
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    matrix_t C;
    std::istringstream add{ solution };
    REQUIRE( C.read(add) );
    REQUIRE( (A - B) == C);
}

TEST_CASE("mul, [oper*]")
{
    std::string input{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
    std::string input_two
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    matrix_t<int> A;
    matrix_t<int> B;
    
    std::istringstream istream{ input };
    std::istringstream istream_two { input_two };
    
    REQUIRE( A.read( istream ) );
    REQUIRE( B.read( istream_two ) );
    
    std::string solution
    {
        "3, 3\n"
        "6 6 6\n"
        "6 6 6\n"
        "6 6 6"
    };
    
    matrix_t<int> C;
    std::istringstream add{ solution };
    
    REQUIRE( C.read(add) );
    REQUIRE( (A * B) == C);
}


TEST_CASE("MINUS, [oper-=]")
{
    std::string input{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
    std::string input_two
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    std::string res_input
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    
    matrix_t<int> A;
    matrix_t<int> B;
    matrix_t<int> C;
    
    std::istringstream istream_res { res_input };
    std::istringstream istream { input };
    std::istringstream istream_two { input_two };
    
    REQUIRE( C.read( istream_res ) );
    REQUIRE( A.read( istream ) );
    REQUIRE( B.read( istream_two ) );
    
    REQIURE_NOTHROW( A.collumns() == B.collumns() && A.rows() == B.rows() );
    
    REQUIRE( (A -= B) == C );
}

TEST_CASE("add, [oper+=]")
{
        std::string input{
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" };
    std::string input_two
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    std::string res_input
    {
        "3, 3\n"
        "3 3 3\n"
        "3 3 3\n"
        "3 3 3"
    };
    
    matrix_t<int> A;
    matrix_t<int> B;
    matrix_t<int> C;
    
    std::istringstream istream_res { res_input };
    std::istringstream istream { input };
    std::istringstream istream_two { input_two };
    
    REQIRE_NOTHROW( A.collunms() == B.collumns() && A.rows() == B.rows() );
    
    REQUIRE( C.read( istream_res ) );
    REQUIRE( A.read( istream ) );
    REQUIRE( B.read( istream_two ) );
    
    REQUIRE( ( A += B ) == C );
}

TEST_CASE("multi, [oper*=]")
{
    std::string input_A
    {
        "3, 3\n"
        "2 2 2\n"
        "2 2 2\n"
        "2 2 2" 
    };
    
    std::string input_B
    {
        "3, 3\n"
        "1 1 1\n"
        "1 1 1\n"
        "1 1 1"
    };
    std::string input_C
    {
        "3, 3\n"
        "6 6 6\n"
        "6 6 6\n"
        "6 6 6"
    };
    
    matrix_t<int> A;
    matrix_t<int> B;
    matrix_t<int> C;
    
    std::istringstream istream_A { input_A };
    std::istringstream istream_B { input_B };
    std::istringstream istream_C { input_C };
   
    REQUIRE_NOTHROW( A.collumns() == B.rows() );
    
    REQUIRE( A.read( istream_A ) );
    REQUIRE( B.read( istream_B ) ); 
    REQUIRE( C.read( istream_C ) );
    
    REQUIRE( ( A * B ) == C);
}
