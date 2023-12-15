/*-------------------------------------------
Program 6: Escape The Labyrinth
Course: CS 211, Fall 2023, UIC
System: Advanced zyLab
Author: Zeehan Sharif
------------------------------------------- */

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
  struct ROW {
    T*  Cols;     // array of column elements
    size_t NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // array of ROWs
  size_t NumRows;  // total # of rows (0..NumRows-1)
    
public:
  //
  // default constructor:
  //
  // Called automatically by to construct a 4x4 Grid. 
  // All elements initialized to default value of T.
  //
  Grid() {
    Rows = new ROW[4];  // 4 rows
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (size_t r = 0; r < NumRows; ++r) {

      Rows[r].Cols = new T[4];
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (size_t c = 0; c < Rows[r].NumCols; ++c) {
        Rows[r].Cols[c] = T();  // default value for type T:
      }
    }
  }

  // parameterized constructor:
  // Called automatically to construct a Grid 
  // with R rows, where each row has C columns. 
  // All elements initialized to default value of T.
  Grid(size_t R, size_t C) {
    
    Rows = new ROW[R];//allocate mem for R rows
    NumRows = R;

    //initialize rows
    for(size_t i = 0; i < R; i++){

        Rows[i].Cols = new T[C];
        Rows[i].NumCols = C;

        //set each element to default constructor val
        for(size_t j = 0; j < C; j++){
            Rows[i].Cols[j] = T();
        }
    }
  }
    
  // destructor:
  // Called automatically to free memory for this Grid.
  virtual ~Grid() {

    for(size_t i = 0; i < NumRows; i++){//deallocating columns' memory
        delete[] Rows[i].Cols;
    }

    delete[] Rows;//deallocating rows' memory
  }

  // copy constructor:
  // Called automatically to construct a Grid that contains a
  // copy of an existing Grid.  Example: this occurs when passing
  // Grid as a parameter by value
Grid(const Grid<T>& other) {
      
    Rows = new ROW[other.NumRows];//allocating memory for new rows
    NumRows = other.NumRows;

    //copy data from other grid
    for(size_t r = 0; r < NumRows; r++){

        Rows[r].Cols = new T[other.Rows[r].NumCols];
        Rows[r].NumCols = other.Rows[r].NumCols;
        copy(other.Rows[r].Cols, other.Rows[r].Cols + Rows[r].NumCols, Rows[r].Cols);
    }
}
    
  // copy operator=
  // Called when one Grid is assigned into another, i.e. this = other;
Grid& operator=(const Grid& other) {

    if(this != &other){//check for self assignment
        
        for(size_t r = 0; r < NumRows; r++){
            delete[] Rows[r].Cols;
        }

        delete[] Rows;

        //allocating new resources and copying data from other object
        NumRows = other.NumRows;
        Rows = new ROW[NumRows];

        for(size_t r = 0; r < NumRows; r++){

            Rows[r].Cols = new T[other.Rows[r].NumCols];
            Rows[r].NumCols = other.Rows[r].NumCols;

            for(size_t c = 0; c < Rows[r].NumCols; c++){
                Rows[r].Cols[c] = other.Rows[r].Cols[c];
            }
        }
    }

    return *this;  //return reference to current instance
}

  // numrows
  // Returns the # of rows in the Grid.  
  // The indices for these rows are 0..numrows-1.
  size_t numrows() const {
    return NumRows;
  }
  
  // Returns the # of columns in row r.  
  // The indices for these columns are 0..numcols-1.  
  // For now, each row has the same number of columns.
  size_t numcols(size_t r) const {
      
      if(r >= NumRows){//validate row index

          cout << "Row out of range";
          exit(1);
      }

      return Rows[r].NumCols; 
  }

  // size
  // Returns the total # of elements in the Grid.
  size_t size() const {
      
      size_t totalSize = 0;

      for(size_t i = 0; i < NumRows; i++){
          totalSize += Rows[i].NumCols;
      }

      return totalSize;
  }

  // Returns a reference to the element at location (r, c);
  // this allows you to access or assign the element:
  T& operator()(size_t r, size_t c) {

      if(r >= NumRows || c >= Rows[r].NumCols){//validating indices

          cout << "Out of range";
          exit(1);
      }

      return Rows[r].Cols[c];
  }

  // Outputs the contents of the grid; for debugging purposes.  
  // This is not tested.
    void _output() {
      
        for(size_t r = 0; r < NumRows; r++){

            for(size_t c = 0; c < Rows[r].NumCols; c++){

                cout << Rows[r].Cols[c] << " ";
            }

            cout << endl;
        }   
   }

};
