#include <iostream>
#include <fstream>

#include <stdexcept>

using namespace std;

template <class T>
class Matrix
{
    private:
        int rows, cols;
        T *values;

    public:
        // constructs
        Matrix(int _rows, int _cols)
        {
            cols = _cols;
            rows = _rows;
            values = new T[rows * cols]; 
        }

        Matrix(int size)
        {
            cols = size;
            rows = size;
            values = new T[rows * cols];
        }

        Matrix(const Matrix& matrix)
        {
            rows = matrix.rows;
            cols = matrix.cols;
            values = new T[rows * cols]; 

            for(int i = 0; i < rows; i++)
            {
                values[i] = matrix.values[i];         
            }
        }

        // destructs
        ~Matrix(){
            delete[] values;
        }

        // compare
        bool operator== (const Matrix& matrix)
        {
            if(rows != matrix.rows || cols != matrix.cols)
            {
                return false;
            }

            for(int i = 0; i < rows * cols; i++)
            {
                if(values[i] != matrix.values[i])
                {
                    return false;
                }
            }

            return true;
        }

        bool operator!= (const Matrix matrix)
        {
            if(rows != matrix.rows || cols != matrix.cols)
            {
                return true;
            }

            for(int i = 0; i < rows * cols; i++)
            {
                if(values[i] != matrix.values[i])
                {
                    return true;
                }
            }

            return false;
        }

        // operator
        Matrix& operator= (const Matrix& matrix)
        {
            this->~Matrix();
            this->rows = matrix.rows;
            this->cols = matrix.cols;

            for(int i = 0; i < rows * cols; i++)
            {
                this->values[i] = matrix.values[i];
            }
            return *this;
        }

        Matrix operator- (const Matrix& matrix){
            if(rows != matrix.rows || cols != matrix.cols)
            {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            Matrix result(rows, cols);
            for(int i = 0; i < rows * cols; i++)
            {
                result.values[i] = values[i] - matrix.values[i]; 
            }
            return result;
        }

        Matrix& operator-= (const Matrix& matrix){
            if(rows != matrix.rows || cols != matrix.cols)
            {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            for(int i = 0; i < rows * cols; i++)
            {
                values[i] -= matrix.values[i]; 
            }
            return *this;
        }

        Matrix operator+ (const Matrix& matrix){
            if(rows != matrix.rows || cols != matrix.cols)
            {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            Matrix result(rows, cols);
            for(int i = 0; i < rows * cols; i++)
            {
                result.values[i] = values[i] + matrix.values[i]; 
            }
            return result;
        }

        Matrix& operator+= (const Matrix& matrix){
            if(rows != matrix.rows || cols != matrix.cols)
            {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            for(int i = 0; i < rows * cols; i++)
            {
                values[i] += matrix.values[i]; 
            }
            return *this;
        }

        Matrix operator/(T n)
        {
            Matrix result(rows, cols);
            for(int i = 0; i < rows * cols; i++)
            {
                result.values[i] = values[i] / n; 
            }
            return result;
        }

        Matrix& operator/=(T n)
        {
            for(int i = 0; i < rows * cols; i++)
            {
                values[i] /= n; 
            }
            return *this;
        }

        Matrix operator*(T n)
        {
            Matrix result(rows, cols);
            for(int i = 0; i < rows * cols; i++)
            {
                result.values[i] = values[i] * n; 
            }
            return result;
        }

        Matrix& operator*=(T n)
        {
            for(int i = 0; i < rows * cols; i++)
            {
                values[i] *= n; 
            }
            return *this;
        }

        // input & output 
        friend void operator>>(istream& s, Matrix& matrix)
        {
            for(int i = 0; i < matrix.rows * matrix.cols; i++){
                s>>matrix.values[i];
            }
        }

        friend void operator<<(ostream& s, Matrix& matrix)
        {
            for(int i = 0; i < matrix.rows * matrix.cols; i++){
                s<<matrix.values[i]<<" ";
            }
        }

        friend void operator>>(ifstream& fs, Matrix& matrix)
        {
            for(int i = 0; i < matrix.rows * matrix.cols; i++){
                fs>>matrix.values[i];
            }
        }

        friend void operator<<(ofstream& fs, Matrix& matrix)
        {
            for(int i = 0; i < matrix.rows * matrix.cols; i++){
                fs<<matrix.values[i]<<" ";
            }
        }
};

