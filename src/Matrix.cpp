/*
 * Matrix.cpp
 *
 *  Created on: 24 juli 2017
 *      Author: mateusz.fraszczynski
 */

#include "../include/Matrix.h"
#include "../include/MatrixOperations.h"
#include <stdio.h> 							// printf

#define matrixData matrixDataPtr.get()


Matrix::Matrix( ) {
	matrixDataPtr = shared_ptr < vector < vector < double > > > ( new vector < vector < double > > );
	this->allocateMatrixVectors( 0 , 0 );
}

Matrix::Matrix( unsigned int no_of_rows , unsigned int no_of_colums ) {
	matrixDataPtr = shared_ptr < vector < vector < double > > > ( new vector < vector < double > > );
	this->allocateMatrixVectors( no_of_rows , no_of_colums );
}

Matrix::Matrix( const Matrix & base_M ) {
	matrixDataPtr = shared_ptr < vector < vector < double > > > ( new vector < vector < double > > );
	this->allocateMatrixVectors( base_M.getRowsNo() , base_M.getColumnsNo() );
	for ( unsigned int i = 0 ; i < base_M.getRowsNo() ; i++ ) {
		for ( unsigned int j = 0 ; j < base_M.getColumnsNo() ; j++ ) {
			this->matrixDataPtr->at( i ).at( j ) = base_M.matrixDataPtr->at( i ).at( j );
		}
	}
}

Matrix::~Matrix() {

}

bool Matrix::isEmpty( void ) const {
	if ( this->getColumnsNo() || this->getRowsNo() ) {
		return 0;
	}
	return 1;
}

bool Matrix::isEqualSize( const Matrix & argument ) const {
	if ( this->getColumnsNo() == argument.getColumnsNo() && this->getRowsNo() == argument.getRowsNo() ) {
		return 1;
	}
	return 0;
}

bool Matrix::isColumnsNoEqualRowsNo( const Matrix & argument ) const {
	if ( this->getColumnsNo() == argument.getRowsNo() ) {
		return 1;
	}
	return 0;
}

bool Matrix::isSquareSize( void ) const {
	if ( this->getRowsNo() == this->getColumnsNo() ) {
			return 1;
	}
	return 0;
}

void Matrix::allocateMatrixVectors( unsigned int no_of_rows , unsigned int no_of_colums ) {
	for ( unsigned int i = 0 ; i < no_of_rows ; i++ ) {
		this->allocateVectorInVector( );
	}
	for ( unsigned int i = 0 ; i < no_of_rows ; i++ ) {
		for ( unsigned int j = 0 ; j < no_of_colums ; j++ ) {
			matrixData->at( i ).push_back( 0 );
		}
	}
}

void Matrix::allocateVectorInVector( void ) {
	vector < double > allocation_vector;
	matrixData->push_back( allocation_vector );
}

bool Matrix::verifyRowIndex( unsigned int row_index ) const {
	if ( row_index >= matrixData->size() ) {
		printf ( "Error: row_index out of matrix range, matrix row size: %d, row_index %d\n" , matrixData->size() , row_index );
		return 1;
	}
	return 0;
}

bool Matrix::verifyColumnIndex( unsigned int column_index ) const {
	if ( column_index >= matrixData->begin()->size() ) {
		printf ( "Error: column_index out of matrix range, matrix column size: %d, column_index %d\n" , matrixData->begin()->size() , column_index );
		return 1;
	}
	return 0;
}

void Matrix::printMatrix( void ) const {
	printf( "\n" );
	for ( unsigned i = 0 ; i < matrixData->size() ; i++ ) {
		printf( "|" );
		for ( vector < double >::iterator it = matrixData->at( i ).begin() ; it != matrixData->at( i ).end() ; ++it ) {
			printf( "%5.3lf " , * it );
		}
		printf( "|\n" );
	}
	printf( "\n" );
}

void Matrix::addRow( void ) {
	this->allocateVectorInVector( );
	vector < vector < double > >::iterator it = matrixData->end();
	it--;																// Iterator set on new added row
	unsigned int y_size;
	matrixData->size() > 1 ? y_size = ( it - 1 )->size() : y_size = 1; // it - 1 because new row must be the same y size as previous
	for ( unsigned int i = 0 ; i < y_size ; i++ ) {
		( it )->push_back( 0 );
	}
}

bool Matrix::addRowWithData( vector < double > * data_ptr ) {
	if ( data_ptr == NULL ) return 1;
	if ( ! matrixData->empty() ) {
		this->addRow();
	} else {
		this->allocateMatrixVectors( 1 ,  data_ptr->size() );
	}
	return this->fillRowWithData( data_ptr , matrixData->size() - 1 );
}

bool Matrix::fillRowWithData( double * data_ptr , unsigned int row_index ) {
	if ( data_ptr == NULL ) return 1;
	if ( this->verifyRowIndex( row_index ) ) {
		return 1;
	} else {
		for ( vector < double >::iterator it = matrixData->at( row_index ).begin() ; it < matrixData->at( row_index ).end() ; it++ , data_ptr++ ) {
			 * it = * data_ptr;
		}
		return 0;
	}
	printf ( "Cannot fill: Unexpected error, while filling Row\n" );
	return 1;
}

bool Matrix::fillRowWithData( vector < double > * data_ptr , unsigned int row_index ) {
	if ( data_ptr == NULL ) return 1;
	if ( this->verifyRowIndex( row_index ) ) {
		return 1;
	} else {
		if ( data_ptr->size() !=  matrixData->at( row_index ).size() ) {
			printf ( "Cannot fill: Size of data vector doesn't match the Matrix! data size %d, Matrix row size %d\n" , data_ptr->size() , matrixData->at( row_index ).size() );
			return 1;
		} else {
			matrixData->at( row_index ) = * data_ptr;
			return 0;
		}
	}
	printf ( "Cannot fill: Unexpected error, while filling Row\n" );
	return 1;
}

void Matrix::eraseRow( unsigned int index ) {
	if( this->isEmpty() ) {
		printf( "ERROR: Cannot cut row - Matrix is empty!\n" );
		return;
	}
	if ( index > this->getRowsNo() - 1 ) {
		printf( "ERROR: Cannot cut row - Index out of Matrix!\n" );
		return;
	}
	vector < vector < double > >::iterator it = matrixData->begin();
	for ( unsigned int i = 0 ; it != matrixData->end() ; ++it , i++ ) {
		if ( i == index ) {
			matrixData->erase( it );
			return;
		}
	}
}

unsigned int Matrix::getRowsNo( void ) const {
	if ( matrixData->empty() ) return 0;
	return matrixData->size();
}

const vector < double > * Matrix::getRow( unsigned int index ) const {
	if ( matrixData->empty() ) {
		printf( "ERROR: Cannot getRow - Matrix is empty\n" );
		return NULL;
	} else if ( this->verifyRowIndex( index ) ) {
		printf( "ERROR: Cannot getRow - index of of range\n" );
		return NULL;
	}
	return & matrixData->at( index );
}

void Matrix::addColumn( void ) {
	if ( matrixData->empty() ) {
		this->addRow();
	} else {
		vector < vector < double > >::iterator it;
		for ( it = matrixData->begin() ; it != matrixData->end() ; ++it ) {
			it->push_back( 0 );
		}
	}
}

bool Matrix::addColumnWithData( vector < double > * data_ptr ) {
	if ( data_ptr == NULL ) return 1;
	if ( ! matrixData->empty() ) {
		this->addColumn();
	} else {
		this->allocateMatrixVectors( data_ptr->size() , 1 );
	}
	return this->fillColumnWithData( data_ptr , matrixData->begin()->size() - 1 );
}

bool Matrix::fillColumnWithData( double * data_ptr , unsigned int column_index ) {
	if ( data_ptr == NULL ) return 1;
	if ( this->verifyColumnIndex( column_index ) ) {
		return 1;
	} else {
		for ( vector < vector < double > >::iterator it = matrixData->begin() ; it < matrixData->end() ; it++ , data_ptr++ ) {
			it->at( column_index ) = * data_ptr;
		}
		return 0;
	}
	printf ( "Cannot fill: Unexpected error, while filling Column\n" );
	return 1;
}

bool Matrix::fillColumnWithData( vector < double > * data_ptr , unsigned int column_index ) {
	if ( data_ptr == NULL ) return 1;
	if ( this->verifyColumnIndex( column_index ) ) {
		return 1;
	} else {
		if ( data_ptr->size() !=  matrixData->size() ) {
			printf ( "Cannot fill: Size of data vector doesn't match the Matrix!\n" );
			return 1;
		} else {
			vector < vector < double > >::iterator it = matrixData->begin();
			for ( vector < double >::iterator it_data = data_ptr->begin() ;  it != matrixData->end() ; it++ , it_data++ ) {
				it->at( column_index ) = * it_data;
			}
			return 0;
		}
	}
	printf ( "Cannot fill: Unexpected error, while filling Column\n" );
	return 1;
}

void Matrix::eraseColumn( unsigned int index ) {
	if( this->isEmpty() ) {
		printf( "ERROR: Cannot cut column - Matrix is empty!\n" );
		return;
	}
	if ( index > this->getColumnsNo() - 1 ) {
		printf( "ERROR: Cannot cut column - Index out of Matrix!\n" );
		return;
	}
	vector < vector < double > >::iterator it_row = matrixData->begin();
	for ( ; it_row != matrixData->end() ; ++it_row ) {
		vector < double >::iterator it_col = it_row->begin();
		for ( unsigned int i = 0 ; it_col != it_row->end() ; ++it_col , i++ ) {
			if ( i == index ) {
				it_row->erase( it_col );
				break;
			}
		}
	}
}

unsigned int Matrix::getColumnsNo( void ) const {
	if ( matrixData->empty() ) return 0;
	return matrixData->begin()->size();
}

bool Matrix::getColumn( vector < const double * > * column_vector , unsigned int index ) const {
	if ( this->verifyColumnIndex( index ) ) {
		printf( "ERROR: Cannot getColumn - index of of range\n" );
		return 1;
	} else {
		for ( unsigned int i = 0 ; i < matrixData->size() ; i++ ) {
			column_vector->push_back( & matrixData->at( i ).at( index ) );
		}
		return 0;
	}
	return 1;
}

void Matrix::operator =( shared_ptr < Matrix > argument ) {
	this->copyData( argument );
}

shared_ptr < Matrix > Matrix::operator *( const Matrix & argument ) {
	shared_ptr < Matrix > result ( new Matrix( ) );
	if ( this->isColumnsNoEqualRowsNo( argument ) ) {
		MatrixOperations::multiplication( * result , * this , argument );
	} else {
		printf( "ERROR: Cannot multiple - size of Matrix doesn't match!\n" );
		return NULL;
	}
	return result;
}

shared_ptr < Matrix > Matrix::operator *( shared_ptr < Matrix > argument ) {
	shared_ptr < Matrix > result ( new Matrix( ) );
	if ( this->isColumnsNoEqualRowsNo( * argument ) ) {
		MatrixOperations::multiplication( * result , * this , * argument );
	} else {
		printf( "ERROR: Cannot multiple - size of Matrix doesn't match!\n" );
		return NULL;
	}
	return result;
}

shared_ptr < Matrix > Matrix::operator *( double argument ) {
	shared_ptr < Matrix > result ( new Matrix( ) );
	if ( ! this->isEmpty() ) {
		MatrixOperations::scalarmultiplication( * result , * this , argument );
	} else {
		printf( "ERROR: Cannot multiple - Matrix is empty!\n" );
		return NULL;
	}
	return result;
}

void Matrix::operator *=( double argument ) {
	if ( ! this->isEmpty() ) {
		MatrixOperations::scalarmultiplication( * this , argument );
	} else {
		printf( "ERROR: Cannot multiple - Matrix is empty!\n" );
	}
}

shared_ptr < Matrix > Matrix::operator +( const Matrix & argument ) {
	shared_ptr < Matrix > result ( new Matrix( ) );
	if ( this->isEqualSize( argument ) ) {
		MatrixOperations::addition( * result , * this , argument );
	} else {
		printf( "ERROR: Cannot add - size of Matrix doesn't match!\n" );
		return NULL;
	}
	return result;
}

shared_ptr < Matrix > Matrix::operator -( const Matrix & argument ) {
	shared_ptr < Matrix > result ( new Matrix( ) );
	if ( this->isEqualSize( argument ) ) {
		MatrixOperations::subtraction( * result , * this , argument );
	} else {
		printf( "ERROR: Cannot subtract - size of Matrix doesn't match!\n" );
		return NULL;
	}
	return result;
}

double Matrix::det( void ) {
	if ( ! this->isEmpty() ) {
		return MatrixOperations::determinant( * this );
	} else {
		printf( "ERROR: Cannot calculate determinant - Matrix is empty!\n" );
	}
	return 0;
}

unsigned int Matrix::rank( void ) {
	if ( ! this->isEmpty() ) {
		return MatrixOperations::rank( * this );
	} else {
		printf( "ERROR: Cannot calculate rank - Matrix is empty!\n" );
	}
	return 0;
}

void Matrix::transIntra( void ) {
	shared_ptr < Matrix > result ( new Matrix( ) );
	if ( ! this->isEmpty() ) {
		MatrixOperations::transposition( * result , * this );
		this->copyData( result );
	} else {
		printf( "ERROR: Cannot transposing - Matrix is empty!\n" );
	}
}

shared_ptr < Matrix > Matrix::transInter( void ) {
	shared_ptr < Matrix > result ( new Matrix( ) );
	if ( ! this->isEmpty() ) {
		MatrixOperations::transposition( * result , * this );
	} else {
		printf( "ERROR: Cannot transposing - Matrix is empty!\n" );
		return NULL;
	}
	return result;
}

void Matrix::copyData( shared_ptr < Matrix > base_M ) {
	this->matrixDataPtr = shared_ptr < vector < vector < double > > > ( new vector < vector < double > > );
	this->allocateMatrixVectors( base_M->getRowsNo() , base_M->getColumnsNo() );
	for ( unsigned int i = 0 ; i < base_M->getRowsNo() ; i++ ) {
		for ( unsigned int j = 0 ; j < base_M->getColumnsNo() ; j++ ) {
			this->matrixDataPtr->at( i ).at( j ) = base_M->matrixDataPtr->at( i ).at( j );
		}
	}
}
