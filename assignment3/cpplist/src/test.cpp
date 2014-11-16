#include "list.h"
#include "apply.h"
#include "reduce.h"
#include <iostream>
#include <assert.h>

int main() {
    try {
        const int N = 100;
        List olist{};
        
        int array[ N  + 2 ];
        for( int i = 0; i < N; ++i ) {
            olist.append( i );
            array[ i ] = i;
        }
        
        assert( olist.equals( array ) == 1 );
        
        List olist2{};
        olist2 = olist;
        assert( olist2.equals( array ) == 1 );
        
        array[ N ] = 5;
        olist2.append( 5 );
        assert( olist2.equals( array ) == 1 );
        
        for ( int i = 0 ; i < N ; i ++ ){
            array[ i ] = array[ i + 1 ];
        }
        olist2.deleteAll( 0 );
        assert( olist2.equals( array ) == 1 );
        
        olist2.deleteAll( N );
        assert( olist2.equals( array ) == 1 );
        
        for ( int i = 0 ; i < N ; i ++ ) {
            if ( array[ i ] == N - 1 ) {
                array[ i ] = array[ i + 1 ];
            }
        }
        olist2.deleteAll( N - 1 );
        assert( olist2.equals( array ) );
        
        for ( int i = 0 ; i < N ; i ++ ) {
            array[ i ] *= array[ i ];
        }
        
        List list{olist2};
        list = list;
        list.apply( SquareApply{} );
        assert( list.equals( array ) == 1 );
    
        int result = 0;
        for ( int i = 0 ; i < N - 1 ;  i ++ ) {
            result += array[ i ];
        }
        
        assert( list.reduce( SumReduce{} ) == result );
        
        std::cout << "Passed all test.\n";
        return 0;
        
        
    } catch( const std::exception &e ) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
