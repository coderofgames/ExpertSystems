#ifndef MY_CPMPLEX_MATRIX
#define MY_CPMPLEX_MATRIX


#include "base_mattrix.h"

namespace LINALG
{


	//============================================================================
	//
	//============================================================================
	template<class T>
	class matrix_complex// : public BaseMatrix
	{
	public:

		//============================================================================
		//
		//============================================================================
		matrix_complex(){
			this->SX = 0; SY = 0;
			data = 0;
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex(matrix_complex *p){
			this->SX = p->SX; SY = p->SY;
			this->create();
			for (int i = 0; i < SX; i++)
			{
				for (int j = 0; j < SY; j++)
					data[i * SY + j] = (*p)(i, j);
			}
			is_transposed = false;
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex(matrix_complex &p){
			this->create(p.SX, p.SY);
			for (int i = 0; i < SX; i++)
			{
				for (int j = 0; j < SY; j++)
					data[i * SY + j] = p(i, j);
			}
			is_transposed = false;
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex(unsigned int n, unsigned int m)
		{
			create(n, m);
		}

		//============================================================================
		//
		//============================================================================
		~matrix_complex()
		{
			destroy();
			if (out_start) delete out_start;
		}

		//============================================================================
		//
		//============================================================================
		void destroy()
		{
			if (data != 0)
			{
				delete[] data;
			}
			data = 0;
			is_transposed = false;
		}

		//============================================================================
		//
		//============================================================================
		void create()
		{
			if (SY > 0 && SX > 0)
			{
				data = new complex< T >[SX * SY];
				for (int r = 0; r < SX; r++)
				{

					for (int c = 0; c < SY; c++)
						data[r * SY + c] = complex< T >(0.0, 0.0);
				}
			}
			else
			{
				cout << "Error (Create): Matrix dimensions should not be zero" << endl;
			}
			is_transposed = false;
		}

		//============================================================================
		//
		//============================================================================
		void create(int sx, int sy)
		{
			SX = sx; SY = sy;
			create();
		}

	private:
	
		matrix_complex* Find_out(int r, int c)
		{
			if (out_start)
			{
				out = out_start;

				while (true)
				{
					if ((out->NumRows() == r) && (out->NumCols() == c))
						break;

					out = out->out;

					if (!out)
						break;
				}
				if (!out)
				{
					out = new matrix_complex(r, c);
				}
				return out;
			}
			else
			{
				out = new matrix_complex(r, c);
				out_start = out;
				return out;
			}
		}
	
	public:
		//============================================================================
		//
		//============================================================================
		void operator=(matrix_complex &b)
		{
			if (!this->EqualSize(b))
			{
				this->destroy();
				this->create(b.NumRows(), b.NumCols());
			}
			for (int i = 0; i < SX; i++)
			{
				for (int j = 0; j < SY; j++)
					data[i * SY + j] = b(i, j);
			}
		}

		//============================================================================
		//
		//============================================================================
		inline bool NotEqual(complex<T> test_value, complex<T> compare)
		{
			//complex<T> precis(this->precision, this->precision);
			//return ((test_value > compare.real + this->precision) || (test_value < compare - this->precision));
			return test_value != compare;
		}

		//============================================================================
		//
		//============================================================================
		void operator=(matrix_complex *b)
		{
			if (!this->EqualSize(b))
			{
				this->destroy();
				this->create(b->NumRows(), b->NumCols());
			}

			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j < this->NumCols(); j++)
					data[i * SY + j] = (*b)(i, j);
			}
		}

		//============================================================================
		//
		//============================================================================
		bool operator==(matrix_complex &b)
		{
			if (!this->EqualSize(b))
			{
				return false;
			}
			for (int i = 0; i < NumRows(); i++)
			{
				for (int j = 0; j < NumCols(); j++)
				{
					if (NotEqual(get(i, j), b(i, j)))
						return false;
				}
			}
			return true;
		}

		//============================================================================
		//
		//============================================================================
		inline bool operator!=(matrix_complex& b)
		{
			return !((*this) == b);
		}

		//============================================================================
		//
		//============================================================================
		inline complex< T >& operator()(unsigned int i, unsigned int j)
		{
			if (i < NumRows() && j < NumCols())
				return get(i, j);

			return complex< T >(0.0, 0.0); // i don't know why this was compiling without the default return statement
		}

		// access without bounds ... checking ...
		
	private:

		//============================================================================
		//
		//============================================================================
		inline complex< T >& get(unsigned int i, unsigned int j)
		{
			return data[i * NumCols() + j];
		}

	public:

		// operators that must be defined outside the class
		void operator = (matrix<T> &b);
		matrix_complex& operator | (matrix<T> &b);
		matrix_complex& operator*(matrix<T> &b);
		matrix_complex& operator+(matrix<T> &b);
		matrix_complex& operator-(matrix<T> &b);


		//============================================================================
		// Hadamard element wise product
		//============================================================================
		matrix_complex& operator | (matrix_complex &b)
		{
			if (this->EqualSize(b))
			{

				out = Find_out(this->NumRows(), this->NumCols());

				for (int i = 0; i < this->NumRows(); i++)
				{
					for (int j = 0; j < this->NumCols(); j++)
					{
						(*out)(i, j) = get(i, j) * b(i, j);
					}
				}

				return *out;
			}

			return matrix_complex(0, 0);
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& operator*(matrix_complex &b)
		{
			if (this->NumCols() == b.NumRows())
			{
				out = Find_out(this->NumRows(), b.NumCols());
				
				for (int r = 0; r < this->NumRows(); r++)
				{

					for (int c = 0; c < b.NumCols(); c++)
					{
						(*out)(r, c) = complex < T >(0.0, 0.0);
						for (int k = 0; k < this->NumCols(); k++)
						{
							(*out)(r, c) += get(r, k) * b(k, c);
						}
					}
				}

				return *out;
			}
			return matrix_complex(0, 0);
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& operator*(T s)
		{
			// prevent infinity, negative infinity, complex infinity or other NAN's from anihilating our matrix
			/*if (s != s)
			{
			cout << "Error (operator * scalar): attempt to multiply by a NAN" << endl;
			return (*this);
			}*/



			out = Find_out(this->NumRows(), this->NumCols());


			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j < this->NumCols(); j++)
				{
					(*out)(i, j) = get(i, j) * s;
				}
			}
			return *out;
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& operator*(complex<T> s)
		{

			out = Find_out(this->NumRows(), this->NumCols());

			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j < this->NumCols(); j++)
				{
					(*out)(i, j) = get(i, j) * s;
				}
			}
			return *out;
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& operator/(T s)
		{
			out = Find_out(this->NumRows(), this->NumCols());

			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j < this->NumCols(); j++)
				{
					(*out)(i, j) = get(i, j) / s;
				}
			}
			return *out;
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& operator/(complex<T> s)
		{
			out = Find_out(this->NumRows(), this->NumCols());

			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j < this->NumCols(); j++)
				{
					(*out)(i, j) = get(i, j) / s;
				}
			}
			return *out;
		}

		//============================================================================
		//complex<T>(1.0, 0.0) 
		//============================================================================
		matrix_complex& operator+(T s)
		{
			out = Find_out(this->NumRows(), this->NumCols());

			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j < this->NumCols(); j++)
				{
					(*out)(i, j) = get(i, j) + s;
				}
			}
			return *out;
		}
		

		//============================================================================
		//complex<T>(1.0, 0.0) 
		//============================================================================
		matrix_complex& operator+(complex<T> s)
		{
			out = Find_out(this->NumRows(), this->NumCols());

			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j < this->NumCols(); j++)
				{
					(*out)(i, j) = get(i, j) + s;
				}
			}
			return *out;
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& operator+(matrix_complex &b)
		{
			if (this->EqualSize(b))
			{
				out = Find_out(this->NumRows(), this->NumCols());

				for (int i = 0; i < this->NumRows(); i++)
				{
					for (int j = 0; j < this->NumCols(); j++)
					{
						(*out)(i, j) = this->get(i, j) + b.get(i, j);
					}
				}

				return *out;
			}
			return matrix_complex(0, 0);
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& operator-(matrix_complex &b)
		{
			if (this->EqualSize(b))
			{
				out = Find_out(this->NumRows(), this->NumCols());

				for (int i = 0; i < this->NumRows(); i++)
				{

					for (int j = 0; j < this->NumCols(); j++)
					{
						(*out)(i, j) = this->get(i, j) - b.get(i, j);
					}
				}

				return *out;
			}
			return matrix_complex(0, 0);
		}

		matrix<T> Real();
		matrix<T> Imag();

		//============================================================================
		// may need to override this for different matrix types
		//============================================================================
		void print(int precis)
		{
			if (this->NumRows() == 0 || this->NumCols() == 0 || this->data == 0)
			{
				cout << "Empty Matrix" << endl;
				return;
			}
			for (int r = 0; r < this->NumRows(); r++)
			{
				for (int c = 0; c < this->NumCols(); c++)
				{
					T real = get(r, c).real();
					T imag = get(r, c).imag();
					//cout << get(i, j)  << "  ";
					if (precis == -1)
					{
						cout << get(r, c) << "  ";

					}
					if (precis == 2)
					{
						if ( imag > 0 )
							printf("(%8.2f + %8.2f i )     ", real, imag);
						else
							printf("(%8.2f   %8.2f i )     ", real, imag);
					}
					else if (precis == 3)
					{
						if (imag > 0)
							printf("(%8.3f + %8.3f i )     ", real, imag);
						else
							printf("(%8.3f   %8.3f i )     ", real, imag);
					}
					else if (precis == 4)
					{
						if (imag > 0)
							printf("(%8.4f + %8.4f i )     ", real, imag);
						else
							printf("(%8.4f   %8.4f i )     ", real, imag);
					}
					else if (precis == 5)
					{
						if (imag > 0)
							printf("(%8.5f + %8.5f i )     ", real, imag);
						else
							printf("(%8.5f   %8.5f i )     ", real, imag);
					}
					else if (precis == 6)
					{
						if (imag > 0)
							printf("(%8.6f + %8.6f i )     ", real, imag);
						else
							printf("(%8.6f   %8.6f i )     ", real, imag);
					}
					else if (precis == 7)
					{
						if (imag > 0)
							printf("(%8.7f + %8.7f i )     ", real, imag);
						else
							printf("(%8.7f   %8.7f i )     ", real, imag);
					}
					else if (precis == 8)
					{
						if (imag > 0)
							printf("(%8.8f + %8.8f i )     ", real, imag);
						else
							printf("(%8.8f   %8.8f i )     ", real, imag);
					}
				}
				cout << endl;
			}
		}


		//============================================================================
		//
		//============================================================================
		complex<T> trace()
		{
			complex<T> sum = complex<T>( 0.0, 0.0 );
			if (SX != SY) return 0.0f;

			for (int i = 0; i < this->NumRows(); i++)
			{
				sum += get(i, i);
			}
			return sum;
		}


		//============================================================================
		//
		//============================================================================
		bool ContainsNAN()
		{
			for (int i = 0; i < SX; i++)
			{
				for (int j = 0; j < SY; j++)
				{
					if (get(i, j) != get(i, j))
						return true;
				}
			}
			return false;
		}

		//============================================================================
		//
		//============================================================================
		void transpose()
		{
			if (this->IsSquare())
			{
				for (int i = 0; i < SX; i++)
				{
					for (int j = i; j < SY; j++)
					{
						SWAP< complex < T >>(get(i, j), get(j, i));
					}
				}
			}
			else if (this->NumCols() == 1 || this->NumRows() == 1)
			{
				SWAP<unsigned int>(SX, SY);
			}
			else
			{
				//matrix_complex Y(this->NumCols(), this->NumRows());
				out = Find_out(this->NumCols(), this->NumRows());

				for (int i = 0; i < SX; i++)
				{
					for (int j = 0; j < SY; j++)
					{
						(*out)(j, i) = get(i, j);
					}
				}

				//this->destroy();
				this->SX = out->NumRows();
				this->SY = out->NumCols();
				//this->create();

				for (int i = 0; i < SX; i++)
				{
					for (int j = 0; j < SY; j++)
					{
						get(i, j) = (*out)(i, j);
					}
				}

				is_transposed = !is_transposed;
			}
		}


		//============================================================================
		//
		//============================================================================
		inline unsigned int NumRows()
		{
			return SX;
		}

		//============================================================================
		//
		//============================================================================
		inline unsigned int NumCols()
		{
			return SY;
		}

		//============================================================================
		//
		//============================================================================
		inline bool IsSquare()
		{
			return SX == SY;
		}

		//============================================================================
		//
		//============================================================================
		bool IsSymmetric()
		{
			if (!this->IsSquare())
			{
				cout << "Error (IsSymmetric): matrix must be square " << endl;
				return false;
			}

			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j <= i; j++)
				{
					// if get(i,j) is a NAN then this will accidently return false
					// when i==j, so i!=j ignores NAN entries
					if (i != j)
						if (NotEqual(get(i, j), get(j, i)))
							return false;
				}
			}

			return true;
		}

		//============================================================================
		//
		//============================================================================
		bool IsSkewSymmetric()
		{
			if (!this->IsSquare())
			{
				cout << "Error (IsSymmetric): matrix must be square " << endl;
				return false;
			}

			for (int i = 0; i < this->NumRows(); i++)
			{
				for (int j = 0; j <= i; j++)
				{
					if (i != j)
						if (NotEqual(get(i, j), -get(j, i)))
							return false;
				}
			}

			return true;
		}

		//============================================================================
		//
		//============================================================================
		bool IsPositiveDefinite()
		{
			if (!this->IsSquare())
			{
				cout << "Error: Positive Definite Matrixces must be square" << endl;
				return false;
			}

			matrix_complex X(this->NumRows(), 1);

			for (int i = 0; i < this->NumRows(); i++)
				X(i, 0) = RandomFloat(1, 5);

			matrix_complex XT = X;
			XT.transpose();

			matrix_complex res = XT * (*this) * X;

			for (int i = 0; i < res.NumCols(); i++)
			{
				for (int j = 0; j < res.NumRows(); j++)
				{
					if (res(j, i).real() <= 0) return false;
				}
			}
			return true;
		}

		//============================================================================
		// For solution of the system Ax = b, 
		// relies on the condition that this matrix A is square and 
		// that b has the same number of rows as A
		//
		// inputs b, outputs x, 
		//
		// For more information please consult Krezig: Advanced Engineering Mathematics, sec 19.1
		//
		//============================================================================
		matrix_complex& Gauss_Elimination(matrix_complex &b)
		{
			if (!this->IsSquare())
			{
				cout << "Error in Gauss calculation: System Matrix must be square." << endl;
				return b;
			}

			if (b.NumRows() != this->NumRows())
			{
				cout << "Error in Gauss calculation: b must have the same number of rows as A" << endl;
				return b;
			}

			unsigned int n = b.NumRows();

			for (int k = 0; k < n - 1; k++)
			{
				bool bSolutionExists = false;
				unsigned int j = k + 1;
				for (j = k + 1; j < n; j++)
				{
					if ((get(j, k).real() != 0.0) && (get(j, k).imag() != 0.0) )
					{
						bSolutionExists = true;
						break;
					}
				}

				if (!bSolutionExists)
				{
					cout << "No Unique Solution Exists" << endl;
					return b; // no solution
				}

				for (int i = 0; i < n; i++)
				{
					SWAP(get(j, i), get(k, i));

					SWAP(b(j, 0), b(k, 0));
				}
				for (j = k + 1; j < n; j++)
				{
					complex<T> mjk = get(j, k) / get(k, k);
					for (int p = k; p < n; p++)
					{
						get(j, p) = get(j, p) - mjk * get(k, p);
					}
					b(j, 0) = b(j, 0) - mjk * b(k, 0);
				}
			}
			if (get(n - 1, n - 1).real() == 0 )
			{
				cout << "No Unique Solution Exists" << endl;
				return b; // no solution
			}


			out = Find_out(n, 1);

			(*out)(n - 1, 0) = b(n - 1, 0) / get(n - 1, n - 1);

			for (int i = n - 2; i > -1; i--)
			{
				complex<T> the_sum = complex<T>(0.0, 0.0);

				for (int j = i + 1; j < n; j++)
					the_sum += get(i, j)*(*out)(j, 0);

				(*out)(i, 0) = (complex<T>(1.0,0.0) / get(i, i)) * (b(i, 0) - the_sum);
			}

			return *out;
		}

		//============================================================================
		// For solution of the system Ax = b, 
		// relies on the condition that this matrix A is square and 
		// that b has the same number of rows as A
		//
		// inputs b, outputs x, 
		//
		// For more information please consult Krezig: Advanced Engineering Mathematics, sec 19.1
		//
		//============================================================================
		matrix_complex& Gauss_Elimination_Save_Original(matrix_complex &b)
		{
			if (!this->IsSquare())
			{
				cout << "Error in Gauss calculation: System Matrix must be square." << endl;
				return b;
			}

			if (b.NumRows() != this->NumRows())
			{
				cout << "Error in Gauss calculation: b must have the same number of rows as A" << endl;
				return b;
			}

			matrix_complex X = (*this);

			unsigned int n = b.NumRows();

			for (int k = 0; k < n - 1; k++)
			{
				bool bSolutionExists = false;
				unsigned int j = k + 1;
				for (j = k + 1; j < n; j++)
				{
					if (X(j, k).real() != 0 && X(j, k).imag() != 0)
					{
						bSolutionExists = true;
						break;
					}
				}

				if (!bSolutionExists)
				{
					cout << "No Unique Solution Exists" << endl;
					return b; // no solution
				}

				for (int i = 0; i < n; i++)
				{
					SWAP(X(j, i), X(k, i));

					SWAP(b(j, 0), b(k, 0));
				}
				for (j = k + 1; j < n; j++)
				{
					complex<T> mjk = X(j, k) / X(k, k);
					for (int p = k; p < n; p++)
					{
						X(j, p) = X(j, p) - mjk * X(k, p);
					}
					b(j, 0) = b(j, 0) - mjk * b(k, 0);
				}
			}
			if (X(n - 1, n - 1) == 0)
			{
				cout << "No Unique Solution Exists" << endl;
				return b; // no solution
			}

			out = Find_out(n, 1);

			(*out)(n - 1, 0) = b(n - 1, 0) / X(n - 1, n - 1);

			for (int i = n - 2; i > -1; i--)
			{
				complex<T> the_sum = 0;
				for (int j = i + 1; j < n; j++)
					the_sum += X(i, j)*(*out)(j, 0);

				(*out)(i, 0) = (complex<T>(1.0, 0.0) / X(i, i)) * (b(i, 0) - the_sum);
			}

			return *out;
		}

		//============================================================================
		// generalization of the reduction to triangular form above
		//============================================================================
		bool ReduceToUpperTriangularForm(T &sign)
		{
			if (!this->IsSquare())
			{
				cout << "Error (ReduceToLowerTriangularForm) : System Matrix must be square." << endl;
				return false;
			}

			unsigned int n = this->NumRows();

			sign = 1;

			// this part is almost exactly the same as the section from the Gauss method 
			for (int k = 0; k < n - 1; k++)
			{
				bool bSolutionExists = false;
				unsigned int j = n - 1;
				for (j = k + 1; j < n; j++)
				{
					if ((get(j, k).real() != 0) && (get(j, k).imag() != 0 ))
					{
						bSolutionExists = true;
						break;
					}
				}

				if (!bSolutionExists) return false;

				for (int p = 0; p < n; p++)
				{
					SWAP(get(j, p), get(k, p));
					sign = -sign;
				}

				for (j = k + 1; j < n; j++)
				{
					complex<T> mjk = get(j, k) / get(k, k);
					for (int p = k; p < n; p++)
					{
						get(j, p) = get(j, p) - mjk * get(k, p);
					}
				}
			}
		}


		//============================================================================
		// Matrix Inversion via Gauss-Jordan elimination
		// The matrix should be square, returns the inverse
		//
		//============================================================================
		matrix_complex& Gauss_Jordan()
		{
			if (!this->IsSquare())
			{
				cout << "Error in Gauss calculation: System Matrix must be square." << endl;
				return (*this);
			}

			matrix_complex A = (*this);

			unsigned int n = this->NumRows();

			/*if (out)
			{
			if (!((out->NumRows() == this->NumRows()) &&
			(out->NumCols() == this->NumCols())))
			{
			delete out;
			out = new matrix(this->NumRows(), this->NumCols());
			}
			}
			else
			{
			out = new matrix(this->NumRows(), this->NumCols());
			}*/
			
			out = Find_out(this->NumRows(), this->NumCols());
			
			out->Identity();


			// this part is almost exactly the same as the section from the Gauss method 
			for (int k = 0; k < n - 1; k++)
			{
				bool bSolutionExists = false;
				unsigned int j = n - 1;
				for (j = k + 1; j < n; j++)
				{
					if ((A(j, k).real() != 0) && (A(j, k).imag() != 0) )
					{
						bSolutionExists = true;
						break;
					}
				}

				if (!bSolutionExists)
				{
					cout << "Error (Gauss_Jordan): No Unique Solution Exists." << endl;
					return (*this);
				}

				for (int p = 0; p < n; p++)
				{
					SWAP<complex<T>>(A(j, p), A(k, p));
					//SWAP<complex<T>>(get(j, p), get(k, p));
					SWAP<complex<T>>((*out)(j, p), (*out)(k, p));
				}
				for (j = k+1; j < n; j++)
				{
					complex<T> mjk = A(j, k) / A(k, k);

					for (int p = k; p < n; p++)
					{

						A(j, p) = A(j, p) - mjk * A(k, p);
						 
						(*out)(j, p) = (*out)(j, p) - mjk * (*out)(k, p);
					}
					A(j, k) = complex<T> (0.0, 0.0 );
					//b(j, 0) = b(j, 0) - mjk * b(k, 0);
				}


			}

			// make sure all the elements on the diagonal are 1 by dividing all 
			// rows by the elements in the diagonals of that row
			// need this for the next loop
			for (int k = 0; k < n; k++)
			{
				complex<T> val = A(k, k);
				for (int c = 0; c < n; c++)
				{

					A(k, c) = A(k, c) / val;
					(*out)(k, c) = (*out)(k, c) / val;
				}
				A(k, k) = complex<T>(1.0, 0.0);
			}

			// starting at the n-1 th row, we have
			// a matrix in echelon form with ones on the main diagonal
			// the 
			for (int r = n - 2; r >-1; r--) // n-2 here because we index from zero instead of one
			{


				// the next element after the diagonal is Row+1
				for (int c = r + 1; c < n; c++)
				{
					// A the value in the row / column position, we will make the element in (r,c) into zero
					// by multiplying by the *next* row, elemnts before the diagonal are already zero, and 
					// the next elements in this row will be handled next ...
					// ...
					complex<T> val = A(r, c);
					for (int p = 0; p < n; p++)
					{
						// we use c to use a mulitiple of c's row, subtracting a multiple of the 1's on the diagonal
						A(r, p) = A(r, p) - A(c, p)*val;

						// all operations are mirrored on the other *output* matrix, or the inverse
						(*out)(r, p) = (*out)(r, p) - (*out)(c, p)*val;
					}
					A(r, c) = complex<T>(0.0, 0.0);

				}
			}
			return *out;
		}



		//============================================================================
		//
		//============================================================================
		complex< T > Det_2x2(int r, int c)
		{
			if ((r + 1 < NumRows()) &&
				(c + 1 < NumCols()))
			{
				return get(r, c) * get(r + 1, c + 1) - get(r + 1, c)*get(r, c + 1);
			}
			return complex<T>(0.0, 0.0);
		}
	private:

		// recognising the fact that C(n,r) = n! /(k! (n-k)!) ... here '!' denotes the factorial sign
		// we have k = (n-1) so ... C(n,r) = n! /((n-1)!( n-(n-1))!) = n! /((n-1)!(-1)!) ...
		// what is (-1)! ... I cannot remember ... so ... but it looks like C(n,n-1) = n
		//
		// Note I am not using permutations here - these are combinations



		//============================================================================
		//
		// C(n,k) = C(5,4) = 5*4*3*2*1 / ((4*3*2*1) * (5-4)!) = 5 
		//============================================================================
		inline complex<T> Det_5x5_internal(int r1, int r2, int r3, int r4, int r5, int c)
		{
			complex<T> c1 = get(r1, c);
			complex<T> c2 = -get(r2, c);
			complex<T> c3 = get(r3, c);
			complex<T> c4 = -get(r4, c); 
			complex<T> c5 = get(r5, c);

			return c1 * Det_4x4_internal(r2, r3, r4, r5, c + 1) +
				c2 * Det_4x4_internal(r1, r3, r4, r5, c + 1) +
				c3 * Det_4x4_internal(r1, r2, r4, r5, c + 1) +
				c4 * Det_4x4_internal(r1, r2, r3, r5, c + 1) +
				c5 * Det_4x4_internal(r1, r2, r3, r4, c + 1);
		}

		//============================================================================
		//
		//============================================================================
		inline complex<T> Det_4x4_internal(int r1, int r2, int r3, int r4, int c)
		{
			complex<T> c1 = get(r1, c);
			complex<T> c2 = -get(r2, c);
			complex<T> c3 = get(r3, c);
			complex<T> c4 = -get(r4, c);

			return c1 * Det_3x3_internal(r2, r3, r4, c + 1) +
				c2 * Det_3x3_internal(r1, r3, r4, c + 1) +
				c3 * Det_3x3_internal(r1, r2, r4, c + 1) +
				c4 * Det_3x3_internal(r1, r2, r3, c + 1);
		}

		//============================================================================
		//
		//============================================================================
		inline complex< T > Det_3x3_internal(int r1, int r2, int r3, int c)
		{
			complex<T> c1 = get(r1, c);
			complex<T> c2 = -get(r2, c);
			complex<T> c3 = get(r3, c);

			return c1 * Det_2x2_internal( r2, r3, c + 1) + 
				   c2 * Det_2x2_internal( r1, r3, c + 1) + 
				   c3* Det_2x2_internal( r1, r2, c + 1);
		}

		//============================================================================
		//
		//============================================================================
		inline complex< T > Det_2x2_internal(int r1, int r2, int c)
		{
			return get(r1, c) * get(r2, c + 1) - get(r2, c) * get(r1, c + 1);
		}

	public:

		//============================================================================
		//
		//============================================================================
		complex< T > DiagonalEntryProduct()
		{
			if (!this->IsSquare())
			{
				cout << "Error (DiagonalEntryProduct): error matrix should be square" << endl;
				return complex<T>(0.0, 0.0);
			}
			complex<T> prod = get(0, 0);
			for (int r = 1; r < this->NumRows(); r++)
				prod *= get(r, r);

			return prod;
		}


		//============================================================================
		// interesting way of evaluating the determinant
		//============================================================================
		complex< T > Determinant()
		{
			if (!this->IsSquare())
			{
				cout << "Error (Determinant):  matrix must be square" << endl;
				return complex<T>(0.0, 0.0);
			}
			if (SX == 2 && SY == 2) return Det_2x2(0, 0);
			if (SX == 3 && SY == 3) return Det_3x3(0, 0);
			matrix_complex temp = (*this);
			T sign = 1;
			if (temp.ReduceToUpperTriangularForm(sign))
				return sign*temp.DiagonalEntryProduct();

			return complex<T>( 0.0, 0.0 );
		}

		//============================================================================
		//
		//============================================================================
		inline bool EqualSize(matrix_complex& b){ return (this->NumRows() == b.NumRows()) && (this->NumCols() == b.NumCols()); }

		//============================================================================
		//
		//============================================================================
		void Identity()
		{
			if (!this->IsSquare())
			{
				cout << "Error (Identity): Identity Matrix must be square" << endl;
				return;
			}
			for (int r = 0; r < this->NumRows(); r++)
			{
				for (int c = 0; c < this->NumCols(); c++)
				{
					if (r == c)
					{
						get(r, c) = complex<T>(1.0, 0.0);
					}
					else
					{
						get(r, c) = complex<T>(0.0, 0.0);
					}

				}
			}
		}

		//============================================================================
		//
		//============================================================================
		void Conjugate()
		{
			for (int r = 0; r < this->NumRows(); r++)
			{
				for (int c = 0; c < this->NumCols(); c++)
				{
					get(r, c) = std::conj(get(r, c));
				}
			}
		}

		//============================================================================
		//
		//============================================================================
		void ConjugateTranspose()
		{
			this->Conjugate();
			this->transpose();
		}

		//============================================================================
		//
		//============================================================================
		bool IsHermitian()
		{
			if (!this->IsSquare())
			{
				cout << "Error (IsHermitian): Identity Matrix must be square" << endl;
				return false;
			}
			
			for (int r = 0; r < this->NumRows(); r++)
			{
				for (int c = 0; c < this->NumCols(); c++)
				{
					//if (r != c) // breakdown in the case of the NAN
					{
						if (get(r, c) != std::conj(get(c, r)))
							return false;
					}
					/*else
					{
						if ((get(r, c).imag() > 0.0 + precision) || 
							(get(r, c).imag() < 0.0 - precision))
							return false;
					}*/
				}
			}

			return true;
		}

		//============================================================================
		//
		//============================================================================
		bool IsSkewHermitian()
		{
			if (!this->IsSquare())
			{
				cout << "Error (IsHermitian): Identity Matrix must be square" << endl;
				return false;
			}

			for (int r = 0; r < this->NumRows(); r++)
			{
				for (int c = 0; c < this->NumCols(); c++)
				{
					//if (r != c)
					{
						if (get(r, c) != -std::conj(get(c, r)))
							return false;
					}
					/*else
					{
						if ((get(r, c).real() > 0.0 + precision) ||
							(get(r, c).real() < 0.0 - precision))
							return false;
					}*/
				}
			}

			return true;
		}


		//============================================================================
		// Solve a matrix system of the form Ly = b by back substitution
		// L, is Lower triangular, y is the solution vector, b is the output
		// inputs L, y, b
		//============================================================================
		matrix_complex & Solve_Lower_TriangularSystem(matrix_complex & L, matrix_complex & y, matrix_complex & b)
		{
			if (!L.IsSquare())
			{
				cout << "Error (Solve_Lower_TriangularSystem): Lower Triangular Matrix should be square" << endl;
				return y;
			}

			if (!y.NumRows() == L.NumRows()) {
				cout << "Error (Solve_Lower_TriangularSystem): vector y should have the same number of rows as L" << endl;
				return y;
			}
			if (!b.NumRows() == y.NumRows())
			{
				cout << "Error (Solve_Lower_TriangularSystem): vector y should have the same number of rows as b" << endl;
				return y;
			}

			y(0, 0) = b(0, 0) / L(0, 0);

			for (int i = 1; i < L.NumRows(); i++)
			{
				complex<T> sum0 = complex<T>( 0.0, 0.0 );
				for (int s = 0; s < i; s++)
				{
					sum0 += L(i, s) * y(s, 0);
				}
				y(i, 0) = (complex<T> (1.0, 0.0) / L(i, i)) * (b(i, 0) - sum0);
			}

			return y;
		}

		//============================================================================
		// Solve a system of the form Ux = y by back substitution
		// U is upper triangular, x is the solution vector, y is the output
		// inputs U,x,y
		//============================================================================
		matrix_complex & Solve_Upper_TriangularSystem(matrix_complex & U, matrix_complex  & x, matrix_complex & y)
		{
			if (!U.IsSquare()) {
				cout << "Error (Solve_Upper_TriangularSystem): matrix should be square" << endl;
				return y;
			}
			if (!y.NumRows() == U.NumRows())
			{
				cout << "Error (Solve_Upper_TriangularSystem): vector y should have same number of rows as matrix" << endl;
				return y;
			}
			if (!x.NumRows() == y.NumRows()) {
				cout << "Error (Solve_Upper_TriangularSystem): x should be same shape as y" << endl;
				return y;
			}

			int n = x.NumRows();

			x(n - 1, 0) = y(n - 1, 0) / U(n - 1, n - 1);

			for (int i = n - 2; i > -1; i--)
			{
				complex<T> sum0 = complex<T>( 0.0, 0.0 );
				for (int j = i + 1; j < n; j++)
					sum0 += U(i, j)*x(j, 0);

				x(i, 0) = (complex<T>(1.0, 0.0) / U(i, i)) * (y(i, 0) - sum0);
			}

			return x;
		}
		
		//============================================================================
		// Solves a system Ax = b via the Cholesky method
		// this matrix must be symmetric and positive definite
		// inputs b, output vector
		// returns x, solution vector
		//============================================================================
		matrix_complex& Cholesky(matrix_complex& b)
		{
			if (!this->IsSymmetric()) {
				cout << "Error (Cholesky): Matrix should be symetric" << endl;
				return b;
			}
			if (!this->IsPositiveDefinite())
			{
				cout << "Error (Cholesky): Matrix should be positive definite" << endl;
				return b;
			}

			int n = this->NumRows();
			matrix_complex M(n, n);

			M(0, 0) = std::sqrt(get(0, 0));


			for (int j = 1; j < n; j++)
			{
				M(j, 0) = get(j, 0) / M(0, 0);
			}

			for (int k = 1; k < this->NumCols(); k++)
			{
				for (int j = k; j < n; j++)
				{
					if (j == k)
					{
						complex<T> sum1 = complex<T>( 0.0, 0.0 );
						for (int s = 0; s < j; s++) sum1 += M(j, s) * M(j, s);

						M(j, j) = std::sqrt(get(j, j) - sum1);
					}
					else
					{
						complex<T> sum2 = complex<T>(0.0, 0.0);
						for (int s = 0; s < k; s++) sum2 += M(j, s) * M(k, s);

						M(j, k) = (complex<T>(1.0, 0.0) / M(k, k)) * (get(j, k) - sum2);
					}
				}
			}

			matrix_complex y(n, 1);
			Solve_Lower_TriangularSystem(M, y, b);
			M.transpose();


			out = Find_out(n, 1);

			Solve_Upper_TriangularSystem(M, *out, y);

			return *out;
		}



		//============================================================================
		// The LU decomposition using doolittles method, this function
		// does not solve a system, it simple decompses this matrix into two
		//matrices such that A = LU
		//============================================================================
		int LU_Decomposition_Doolittle(matrix_complex& L, matrix_complex& U)
		{
			if (!L.EqualSize(U))
			{
				cout << "Error (LU_Decomposition_Doolittle): L and U must be equal size" << endl;
				return 0;
			}
			if (!this->EqualSize(L))
			{
				cout << "Error (LU_Decomposition_Doolittle):  L and U must be the same size as the source matrix" << endl;
				return 0;
			}
			if (!this->IsSquare())
			{
				cout << "Error (LU_Decomposition_Doolittle):  source matrix must be square" << endl;
				return 0;
			}



			int n = this->NumCols();

			L.Identity();

			for (int k = 0; k < n; k++)
			{
				U(0, k) = get(0, k);

				L(k, 0) = get(k, 0) / U(0, 0); // loop 1 with rows indexed with k, ignore cols

				L(k, k) = complex< T >(1.0, 0.0); // loop 1 as L(k,k)
			}

			for (int j = 1; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					if (k >= j)
					{
						complex<T> sum0 = complex<T>( 0.0, 0.0 );
						for (int s = 0; s < j; s++) sum0 += L(j, s) * U(s, k);

						U(j, k) = get(j, k) - sum0;
					}
					else
					{
						complex<T> sum1 = complex<T>( 0.0, 0.0 );
						for (int s = 0; s < k; s++) sum1 += L(j, s) * U(s, k);

						L(j, k) = (complex< T >( 1.0, 0.0) / U(k, k))*(get(j, k) - sum1);
					}

				}
			}

			return 1;
		}

		//============================================================================
		// Solves the system via doolittles method, for the equation Ax = b
		// it first factorizes A into LU such that A=LU, then solves the 
		// lower triangular system Ly = b and then the upper triangular system Ux=y
		// returns x
		//
		//============================================================================
		matrix_complex& Solve_System_Doolittle(matrix_complex& b)
		{

			if (!this->IsSquare())
			{
				cout << "Error (Solve_System_Doolittle):  source matrix must be square" << endl;
				return b;
			}
			if (!(b.NumRows() == this->NumRows()))
			{
				cout << "Error (Solve_System_Doolittle):  matrix b must have same number of rows as source matrix" << endl;
				return b;
			}


			int n = this->NumCols();

			matrix_complex L(n, n);
			matrix_complex U(n, n);


			this->LU_Decomposition_Doolittle(L, U);

			matrix_complex y(n, 1);
			Solve_Lower_TriangularSystem(L, y, b);


			out = Find_out(n, 1);

			Solve_Upper_TriangularSystem(U, *out, y);

			return *out;
		}


		//============================================================================
		// Very similar to the Doolittle method, solves A = LU for L and U
		// inputs require L and U to be of the same dimensionality as A
		//============================================================================
		int LU_Decomposition_Crout(matrix_complex& L, matrix_complex& U)
		{
			if (!L.EqualSize(U))
			{
				cout << "Error (LU_Decomposition_Doolittle): L and U must be equal size" << endl;
				return 0;
			}
			if (!this->EqualSize(L))
			{
				cout << "Error (LU_Decomposition_Doolittle):  L and U must be the same size as the source matrix" << endl;
				return 0;
			}
			if (!this->IsSquare())
			{
				cout << "Error (LU_Decomposition_Doolittle):  source matrix must be square" << endl;
				return 0;
			}



			int n = this->NumCols();

			U.Identity();

			for (int j = 0; j < n; j++)
			{
				L(j, 0) = get(j, 0);

				U(0, j) = get(0, j) / L(0, 0);

				U(j, j) = complex <T> (1.0, 0.0);

			}

			for (int k = 1; k < n; k++)
			{
				for (int j = 0; j < n; j++)
				{
					if (j >= k)
					{
						complex<T> sum0 = complex<T>( 0.0, 0.0 );
						for (int s = 0; s < k; s++) sum0 += L(j, s) * U(s, k);

						L(j, k) = get(j, k) - sum0;
					}
					else
					{
						complex< T > sum1 = complex< T >( 0.0, 0.0 );
						for (int s = 0; s < j; s++) sum1 += L(j, s) * U(s, k);

						U(j, k) = (complex<T>(1.0, 0.0) / L(j, j))*(get(j, k) - sum1);
					}
				}
			}

			return 1;
		}

		//============================================================================
		//
		// TODO: optimize this...
		// thanks to
        // http://mathworld.wolfram.com/MatrixInverse.html
        // and 
		// http://www.gamedev.net/page/resources/_/technical/math-and-physics/matrix-inversion-using-lu-decomposition-r3637
		// for this solution 
		//============================================================================
		matrix_complex& Invert_Crout()
		{
			int n = this->NumCols();

			matrix_complex A_inv(n, n);

			matrix_complex b(n, 1);

			matrix_complex sol(n, 1);

			for (int c = 0; c < n; c++)
			{
				//b.ToZero();
				b(c, 0) = complex<T>(1.0, 0.0);

				sol = Solve_System_Crout(b);

				for (int r = 0; r < n; r++)
				{
					A_inv(r, c) = sol(r, 0);
				}

				b(c, 0) = complex<T>(0.0, 0.0);
			}

			out = Find_out(n, n);
			(*out) = A_inv;

			return (*out);
			
		}

		/* UNTESTED */
		matrix_complex& Invert_Gauss()
		{
			if (!this->IsSquare())
			{
				cout << "Error (Invert_Gauss): matrix should be square" << endl;
				return matrix_complex(0, 0);
			}
	

			int n = this->NumCols();
			matrix_complex sol(n, 1);
			matrix_complex I_Col(n, 1);
			matrix_complex X(n, n);

			for (int i = 0; i < n; i++)
			{
				I_Col(i, 0) = complex< T >(1.0, 0.0);
				sol = Gauss_Elimination_Save_Original(I_Col);
				I_Col(i, 0) = complex<T>(0.0, 0.0);

				for (int j = 0; j < n; j++)
					X(j, i) = sol(j, 0);
			}

			// out exists as a solution to the gauss elimination
			// next phase is to use the "out" stored in out, as 
			// a linked list
			
			out = Find_out(n, n);
			(*out) = X;

			/* UNTESTED */
			return (*out);
		}
		
		//============================================================================
		// note for this method, inv can be arbitrary iff every eigenvalue of (I-AX(0)) is of absolute value < 1
		// the method is mostly used for improving an innaccurate inverse obtained by another method.
		//============================================================================
		matrix_complex& Newtons_Iteration_for_Inverse(matrix_complex& inv, int num_iterations)
		{
			if (!inv.IsSquare() || !this->IsSquare())
			{
				cout << "Error (Newtons_Iteration_for_Inverse): Matrices should be square" << endl;
			}

			int n = inv.NumCols();

			// need an identity matrix
			matrix_complex I(n,n);
			I.Identity();

			for (int i = 0; i < num_iterations; i++)
			{
				// incrementally update the inverse ...
				// could possibly test for convergence here using a norm
				inv = inv * (I * 2 - (*this) * inv);
			}

			return inv;
		}

		//============================================================================
		// Solves the system via Crout method, for the equation Ax = b
		// it first factorizes A into LU such that A=LU, then solves the
		// lower triangular system Ly = b and then the upper triangular system Ux=y
		// returns x
		//
		//============================================================================
		matrix_complex& Solve_System_Crout(matrix_complex& b)
		{

			if (!this->IsSquare())
			{
				cout << "Error (Solve_System_Doolittle):  source matrix must be square" << endl;
				return b;
			}
			if (!(b.NumRows() == this->NumRows()))
			{
				cout << "Error (Solve_System_Doolittle):  matrix b must have same number of rows as source matrix" << endl;
				return b;
			}


			int n = this->NumCols();

			matrix_complex L(n, n);
			matrix_complex U(n, n);


			this->LU_Decomposition_Crout(L, U);

			matrix_complex y(n, 1);
			Solve_Lower_TriangularSystem(L, y, b);


			out = Find_out(n, 1);

			Solve_Upper_TriangularSystem(U, *out, y);

			return *out;
		}

		//============================================================================
		// Solves the system via Doolittles or Crouts method, for the equation Ax = b
		// If the matrices L and U satisfy A = LU (where A is the system matix)
		// it solves the lower triangular system Ly = b and then the upper triangular system Ux=y
		// returns x
		//
		//============================================================================
		matrix_complex& Solve_System_LU(matrix_complex& L, matrix_complex& U, matrix_complex& b)
		{

			if (!this->IsSquare())
			{
				cout << "Error (Solve_System):  source matrix must be square" << endl;
				return b;
			}
			if (!L.EqualSize(U))
			{
				cout << "Error (Solve_System): L and U must be equal size" << endl;
				return b;
			}
			if (!this->EqualSize(L))
			{
				cout << "Error (Solve_System):  L and U must be the same size as the source matrix" << endl;
				return b;
			}

			int n = this->NumCols();

			//this->LU_Decomposition_Crout(L, U);

			matrix_complex y(n, 1);
			Solve_Lower_TriangularSystem(L, y, b);

			
			out = Find_out(n, 1);

			Solve_Upper_TriangularSystem(U, *out, y);

			return *out;
		}


		
		T Euclidean_Norm_column(matrix_complex &v, int r1, int c)
		{

			complex< T > S = complex< T >(0.0, 0.0);
			for (int r = r1; r < v.NumRows(); r++)
			{
				S += std::abs(v(r, c)) * std::abs(v(r, c));
			}

			return std::sqrt(S.real());
		}

		complex< T > Sum_Norm_column(matrix_complex &v, int r1, int c)
		{

			complex< T > S = complex< T >(0.0, 0.0);
			for (int r = r1; r < v.NumRows(); r++)
			{
				S += v(r, c);
			}

			return S;
		}
		
		//============================================================================
		//wikipedia calculation
//	https://en.wikipedia.org/wiki/QR_decomposition
		// since ||x|| at one time refers to the euclidean norm, and for complex numbers this
		// is defined as sqrt( sum( abs(z)^2 ) ) 
		// http://mathworld.wolfram.com/L2-Norm.html

		// This produces a different result from the version above
		// I am not sure which is "correct" however this version is much faster
		// since there is no need to iterate.
		// WORKING / STABLE
		//============================================================================
		matrix_complex& complex_decomposition_qr_householder_shur(bool useQR)
		{

			int n = this->NumRows();

			matrix_complex  X(n, 1);
			matrix_complex  X_CT(1, n); // conjugate transpose
			matrix_complex  V;
			matrix_complex  V_CT; // conjugate transpose
			matrix_complex  Inn(n, n);
			matrix_complex V_VH;

			matrix_complex U(n, 1);

			Inn.Identity();

			matrix_complex R_ = (*this);
			matrix_complex Q;
			matrix_complex Q2;

			out = Find_out(n, n);
			out->Identity();

			complex< T > S = complex< T >(0.0, 0.0);
			
			int end_loop = n - 1;
			
			if (useQR) end_loop += 1;


			for (int c = 0; c < end_loop; c++)
			{
	

				
				int Row = c + 1;

				if (useQR) Row = c;

				for (int r = Row; r < n; r++)
				{
					X(r, 0) = R_(r, c); // store X
					X_CT(0, r) = std::conj(X(r, 0)); // conjugate transpose
				}
				
				// changing the length of the vector on the pivot axis, keeping the rest the same ...
				// these formulas find a unit normal on the plane of reflection (V) and they are used
				// to construct the reflection matrix (orthogonal matrix) Q that takes the
				// vector X from "Row" to the vector aligned to the (alpha, 0,0,...0) or e_row * alpha
				// where e_row is a column of the identity matrix with a 1 at the row entry ...
				// alpha is computed as a polar complex number (wiki) to form the sign on the complex
				// hyperplane.
				//T  arg_z = std::atan2(R_(Row, c).imag(), R_(Row, c).real()); 
				T  arg_z = std::atan(R_(Row, c).imag() / R_(Row, c).real());
				T mag_z = Euclidean_Norm_column(X, Row, 0);

				
			
				U = X;

				// Instead of the sign of a complex number (i.e. on unit circle z / |z| )
				// The correct answer here was the CSGN function which is defined on wikipedia 
				
				U(Row, 0) = X(Row, 0) + mag_z * CSGN< T > (R_(Row, c));

				complex<T > col_norm = Euclidean_Norm_column(U, Row, 0);

				V = U / col_norm;

				V_CT = V;

				V_CT.ConjugateTranspose();

				Q = Inn - V*V_CT * (complex<T>(1.0, 0.0) + (X_CT * V)(0, 0) / (V_CT * X)(0, 0));
				
				//=======================================================================
				// swapping the order of operations of storing Q by recognizing the fact
				// that the algorithm solved for the case of the hermitian and the hermitian
				// is exactly equal to its own conjugate transpose ... calculating the 
				// conjugate transpose before the combined mulitplication is clearly correct
				// and does not affect either the QR decomposition or the Hessenburg methods
				//=======================================================================

				// Effectively this is now a Shur Decomposition solver too .
				// http://mathworld.wolfram.com/SchurDecomposition.html
				/*if (true)  // testing
				{
					Q2 = Q;
					Q2.ConjugateTranspose();
					Q2 = Q.Newtons_Iteration_for_Inverse(Q2, 10);
					Q = Q2.Newtons_Iteration_for_Inverse(Q, 10);
				}*/
				R_ = Q * R_;

				Q.ConjugateTranspose();

				(*out) = (*out) * Q;  // storing Q just in case it is needed
				

				// then this should be the Householder tridiagonalization method, creating tridiagonal matrices
				// this takes the example Hermitian matrix into a Tridiagonal form
				

				if (!useQR)  
					R_ = R_ * Q; 
				
				// zero the vectors again
				V.ToZero();
				V_CT.ToZero();
				X.ToZero();
				X_CT.ToZero();
				U.ToZero();
			}

			(*this) = R_;

			

			return *out;

		}


		//============================================================================
		// have the values swapped?
		// WORKING / STABLE
		//============================================================================
		void Eigenvalues_2x2(int r, int c, complex<T> &L1, complex<T> &L2)
		{
			if (r + 1 >= this->NumRows() || c + 1 >= this->NumCols())
			{
				cout << "Error (Eigenvalues_2x2): index out of bounds" << endl;
				return;// false;
			}

			complex<T> trace = get(r, c) + get(r + 1, c + 1);
			complex<T> det = get(r, c)*get(r + 1, c + 1) - get(r + 1, c)*get(r, c + 1);

			L1 = trace * 0.5 + std::sqrt(trace*trace / 4.0 - det);
			L2 = trace * 0.5 - std::sqrt(trace*trace / 4.0 - det);
		}

		//============================================================================
		// Application specific QR algorithm using complex Householder reflectors
		// This removes the need for extra copies and streamlines the functionality
		// also seems to be absolutely convergent (so far, tested with 450 iterations
		// and also with 1450 iterations)
		// the function mimics the QR algorithm for real valued matrices, with 
		// similar solution for non-zero subdiagonal entries, the question of 
		// what happens when the top corner (0,0) element is part of a 2*2 block
		// with non-zero subdiagonal element still needs some testing.
		//============================================================================
		void solve_eigen_values_shur_decomposition(matrix_complex& eigen_values)
		{

			int n = this->NumRows();

			matrix_complex  X(n, 1);
			matrix_complex  X_CT(1, n); // conjugate transpose
			matrix_complex  V;
			matrix_complex  V_CT; // conjugate transpose
			matrix_complex  Inn(n, n);
			matrix_complex V_VH;

			matrix_complex U(n, 1);

			Inn.Identity();

			matrix_complex R_ = (*this);
			matrix_complex R_2 = R_;
			matrix_complex R_3 = R_;
			matrix_complex Q;
			matrix_complex Q1(n,n);
			matrix_complex Q2(n, n);
			matrix_complex Q3(n, n);
			Q1.Identity();
			Q2.Identity();
			Q3.Identity();
			out = Find_out(n, n);
			out->Identity();

			complex< T > S = complex< T >(0.0, 0.0);

			// the more iterations, the more it converges
			for (int i = 0; i < 450; i++ )
			{ 
				for (int c = 0; c < n; c++)
				{
					int Row = c;

					for (int r = Row; r < n; r++)
					{
						X(r, 0) = R_(r, c); // store X
						X_CT(0, r) = std::conj(X(r, 0)); // conjugate transpose
					}

					T mag_z = Euclidean_Norm_column(X, Row, 0);

					U = X;

					// Instead of the sign of a complex number (i.e. on unit circle z / |z| )
					// The correct answer here was the CSGN function which is defined on wikipedia 

					U(Row, 0) = X(Row, 0) + mag_z * CSGN< T >(R_(Row, c));

					complex<T > col_norm = Euclidean_Norm_column(U, Row, 0);

					V = U / col_norm;

					V_CT = V;

					V_CT.ConjugateTranspose();

					Q = Inn - V*V_CT * (complex<T>(1.0, 0.0) + (X_CT * V)(0, 0) / (V_CT * X)(0, 0));

					Q1 = Q * Q1;

					R_ = Q * R_;

					//R_3 = Q * R_3;
				
					Q.ConjugateTranspose();

					Q2 = Q2 * Q;  // storing Q just in case it is needed

					//R_3 = R_3 * Q;
					// zero the vectors again
					V.ToZero();
					V_CT.ToZero();
					X.ToZero();
					X_CT.ToZero();
					U.ToZero();
				}
				
				R_ = R_ * Q2;
				
				Q2.Identity();

			}

			bool flag_last = false;
			for (int j = 0; j < n - 1; j++)
			{
				complex<T> sub_diag2 = R_(j + 1, j);
				//precision = FLT_EPSILON;
				if ((sub_diag2.real() > precision || sub_diag2.real() < -precision /*FLT_EPSILON*/) ||
					(sub_diag2.imag() > precision || sub_diag2.imag() < -precision /*FLT_EPSILON*/))
				{
					complex<T> L1, L2;
					R_.Eigenvalues_2x2(j, j, L1, L2);

					T c1 = std::abs(eigen_values(j, 0) - L1);
					T c2 = std::abs(eigen_values(j, 0) - L2);

					// pyrotechnical hackery
					cout << "L1: " << L1 << ", c1: " << c1 << ", eigen_values(j, 0): " << eigen_values(j, 0);
					cout << "    L2: " << L2 << ", c2: " << c2 << ", eigen_values(j+1, 0): " << eigen_values(j + 1, 0) << endl;
					
					if (eigen_values(j, 0).real() == 0.0 && eigen_values(j, 0).imag() == 0.0)
					{
						eigen_values(j, 0) = L1;
						eigen_values(j + 1, 0) = L2;
					}
					else if ( c2 < 1.0 && 
						     (std::abs(L2.real() - eigen_values(j, 0).real()) < std::abs(L1.real() - eigen_values(j, 0).real()) &&
							  std::abs(L2.imag() - eigen_values(j, 0).imag()) < std::abs(L1.imag() - eigen_values(j, 0).imag())))
						//(c2 < 1.0 && c1 > c2)
					{
						// basically the question is whether this was set last time.
						// and if so, was the value the correct L

						/*if (c1 < c2)
						{
							eigen_values(j, 0) = L1;
							eigen_values(j + 1, 0) = L2;
						}
						else*/
						{
							eigen_values(j, 0) = L2;
							//eigen_values(j, 0) = L2;
						}
							
							eigen_values(j + 1, 0) = L1;
					}
					else
					{

						eigen_values(j, 0) = L1;
						eigen_values(j + 1, 0) = L2;
					}

					

					flag_last = true;
				}
				else
				{
					if (!flag_last)
						eigen_values(j, 0) = R_(j, j);

					flag_last = false;
				}
			}

			if (flag_last == false)
			{
				eigen_values(n - 1, 0) = R_(n - 1, n - 1);
			}

			
		/*	Q3 = Q1;
			Q3.ConjugateTranspose();
			R_2 = Q1 * R_2 * Q3;
			R_2.print(3);
			eigen_values = R_2.get_diag_vector();*/

	

		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& get_column_vector(int col)
		{
			if (col < this->NumCols())
			{
				out = Find_out(this->NumRows(), 1);
				for (int r = 0; r < this->NumRows(); r++)
				{
					(*out)(r, 0) = get(r, col);
				}
			}
			else
			{
				cout << "error (get_column_vector): column range out of bounds"
			}

			return *out;
		}
		
		//============================================================================
		//
		//============================================================================
		matrix_complex& get_row_vector(int row)
		{
			if (row < this->NumRows())
			{
				out = Find_out(1, this->NumCols());
				for (int c = 0; c < this->NumCols(); c++)
				{
					(*out)(0, c) = get(row, c);
				}
			}
			else
			{
				cout << "error (get_row_vector): row range out of bounds"
			}

			return *out;
		}

		//============================================================================
		//
		//============================================================================
		matrix_complex& get_diag_vector()
		{
			if (!this->IsSquare())
			{
				cout <<endl<< "warning (get_diag_vector): Usually you get the diagonal of a Square matrix" << endl;
			}

			if (this->NumRows() > this->NumCols())
			{
				out = Find_out(this->NumCols(), 1);
			}
			else if (this->NumRows() < this->NumCols())
			{
				out = Find_out(this->NumRows(), 1);
			}
			else
			{
				out = Find_out(this->NumRows(), 1);
			}

			for (int r = 0; r < this->NumRows(); r++)
				{
					for (int c = 0; c < this->NumCols(); c++)
					{
						if (r == c)
						{
							(*out)(r, 0) = get(r, c);
						}
					}
				}


			return *out;
		}

		//============================================================================
		// http://www.netlib.org/lapack/lawnspdf/lawn148.pdf
		// notes about precision issues ... not computing the full case
		// here.  WORKING  as QRQ* shur decomposition using QR Householder reflectors 
		// slight numerical instability, but to be expected with complex numbers
		// and ~hard to read~ math
		//============================================================================
		void QR_algorithm(matrix_complex& eigen_values)
		{
			
			if (!this->IsSquare())
			{
				cout << "Error (QR_algorithm): Matrix must be square" << endl;
				return;
			}

			//if (this->IsHermitian())
			{
				matrix_complex A = (*this);
				matrix_complex Q = A.complex_decomposition_qr_householder_shur(true);
				A = A * Q;
				//matrix_complex Q2 = Q;
				for (int i = 0; i < 400; i++) // lazy ... need to test for convergence
				{
					Q = A.complex_decomposition_qr_householder_shur(true);
					
					
					A = A * Q;
				}
				//Q2 = Q;
				//Q.ConjugateTranspose();

				//A = (*this);
				if (true)  // testing
				{
					
					
				//	Q2 = Q.Newtons_Iteration_for_Inverse(Q2, 10);
					//Q = Q2.Newtons_Iteration_for_Inverse(Q, 10);
				}
				//A = Q * A * Q2;
				eigen_values = A.get_diag_vector();
				A.print(4);
			}
		/*	else
			{

			

				int n = this->NumCols();

				matrix_complex C_n(n, n);
				C_n.Identity();

				matrix_complex R_n(n, n);
				R_n.Identity();

				matrix_complex I_b(2, 2);
				I_b.Identity();

				matrix_complex *C = new matrix_complex<T>[n - 1]; // an array of n 4x4 matrices
				for (int i = 0; i < n - 1; i++)
					C[i] = I_b;

				complex<T> tan_theta, sin_theta, cos_theta;

				// to compute R0 = C

				T z4 = std::numeric_limits<T>::epsilon()/std::numeric_limits<T>::denorm_min();
				T zm4 = std::numeric_limits<T>::denorm_min() / std::numeric_limits<T>::epsilon();

				T z2 = std::sqrt(z4);
				T zm2 = std::sqrt(zm4);

				for (int loop = 0; loop < 100; loop++)
				{
					for (int j = 0; j < n - 1; j++)
					{
						complex<T> f = get(j, j); // f
						complex<T> g = get(j + 1, j); // g

					

						// cos_theta = x/r = f / sqrt(f**2 + g**2)
						// sin_theta = y/r = g / sqrt(f**2 + g**2)
						// tan_theta = y/x = g/f = sin_theta / cos_theta 
						// => cos_theta * g/f = sin_theta
						// cos_theta = 1.0 / sqrt(1+tan_theta**2) = 1/ sqrt(1+g**2/f**2)
						// = f / sqrt(f**2 + g**2)
						// sin_theta = tan_theta / sqrt(1+tan_theta**2) =
						// = g / sqrt(f**2 + g**2)
						T scale_g = std::abs(g);
						T scale_f = std::abs(f);
						if (scale_g == 0.0)
						{
							cos_theta = complex<T>(1.0, 0.0);
							sin_theta = complex<T>(0.0, 0.0);
						}
						else if (scale_f == 0)
						{
						
							while (true)
							{
								if ((scale_g < z2) && (scale_g > zm2))
									break;

								if (scale_g > z2)
								{
									complex<T> g2 = g*zm4;
									if (g2.real() == g2.real())
										g = g2;
								
								}
								else if (scale_g < zm2)
								{
									complex<T> g2 = g*z4;
									if (g2.real() == g2.real())
										g = g2;
								}

							

								scale_g = std::abs(g);
							}
						
						
						
							cos_theta = complex<T>(0.0, 0.0);
							sin_theta = std::conj(g) / std::abs(g);
						}
						else
						{
							T absF2 = f.real() * f.real() + f.imag() * f.imag();
							T absG2 = g.real() * g.real() + g.imag() * g.imag();

							if (scale_f < std::numeric_limits<T>::epsilon() * scale_g)
							{
								cos_theta = absF2 / (scale_f * scale_g);
								sin_theta = f * std::conj(g) / (scale_f * scale_g);
							} 
							else if (scale_g < std::numeric_limits<T>::epsilon() * scale_f)
							{
								cos_theta = complex<T>(1.0, 0.0);
								sin_theta = f * std::conj(g) / absF2;
							}
							else
							{

								sin_theta = std::conj(g) * f / (scale_f * std::sqrt(absF2 + absG2));
								cos_theta = scale_f / (std::sqrt(absF2 + absG2));
							}
							//tan_theta = (g / f);

							//cos_theta = std::abs(f) / std::sqrt(1.0 + tan_theta*tan_theta);
							//sin_theta = tan_theta / std::sqrt(1.0 + tan_theta*tan_theta);
						}
	
						C[j](0, 0) = cos_theta;      C[j](0, 1) = sin_theta;
						C[j](1, 0) = -sin_theta;      C[j](1, 1) = cos_theta;


						C_n.Overwrite_Submatrix(C[j], j, j);

						(*this) = C_n * (*this);

						C_n.Overwrite_Submatrix(I_b, j, j); // set back to identity for next C_j
					}
					//C_n.Identity();

					for (int j = 0; j < n - 1; j++)
					{
						C_n.Overwrite_Submatrix_transposed(C[j], j, j);

						(*this) = (*this) * C_n;

						C_n.Overwrite_Submatrix(I_b, j, j); // set back to identity for next C_j
					}
				}

				// set the eigen values and exit
				bool flag_last = false;
				for (int j = 0; j < n - 1; j++)
				{
					complex<T> sub_diag2 = get(j + 1, j);
					//precision = FLT_EPSILON;
					if (NotEqual(sub_diag2, complex<T>(0.0, 0.0)) == false )
					{
						complex<T> L1, L2;
						//Eigenvalues_2x2(j, j, L1, L2);

						eigen_values(j, 0) = L1;
						//eigen_values(j, 1) = L1.imag();

						eigen_values(j + 1, 0) = L2;
						//eigen_values(j + 1, 1) = L2.imag();

						flag_last = true;
					}
					else
					{
						if (!flag_last)
							eigen_values(j, 0) = get(j, j);

						flag_last = false;
					}
				}

				if (flag_last == false)
				{
					eigen_values(n - 1, 0) = get(n - 1, n - 1);
				}

				delete[] C;
			}*/
		}
		

		//============================================================================
		//
		//============================================================================
		// this should be rewritten for complex types too.
		// also a tolerance should be built in to all tests for equality.
		bool IsOrthogonal()
		{
			if (!this->IsSquare())
			{
				cout << "Error (IsOrthogonal): Matrix should be square" << endl;
				return false;
			}
			matrix_complex AT = (*this);

			AT.transpose();

			matrix_complex I = AT * (*this);

		/*	for (int i = 0; i < this->NumRows(); i++)
				for (int j = 0; j < this->NumRows(); j++)
					if ((i == j && NotEqual(I(i, j), 1.0)) ||
						(i != j && NotEqual(I(i, j), 0.0)))
						return false;
*/
			/*matrix<T> I2 = (*this) * AT;

			for (int i = 0; i < this->NumRows(); i++)
			for (int j = 0; j < this->NumRows(); j++)
			if ((i == j && NotEqual( I2(i, j), 1.0)) ||
			(i != j && NotEqual( I2(i, j), 0.0)))
			return false;
			*/

			return true;

		}


		//============================================================================
		//
		//============================================================================
		void Overwrite_Submatrix(matrix_complex b, int r, int c)
		{
			if (b.NumCols() > this->NumCols() || b.NumRows() > this->NumRows())
			{
				cout << "Error (Overwrite_Submatrix): sub matrix dimensions exceed destination dimensions" << endl;
				return;
			}

			if ((r + b.NumRows() > this->NumRows()) || (c + b.NumCols() > this->NumCols()))
			{
				cout << "Error (Overwrite_Submatrix): sub matrix size plus dimensions exceed destination dimensions" << endl;
				return;
			}

			for (int i = 0; i < b.NumRows(); i++)
			{
				for (int j = 0; j < b.NumCols(); j++)
				{
					get(r + i, c + j) = b(i, j);
				}
			}

		}


		//============================================================================
		//
		//============================================================================
		void Overwrite_Submatrix_transposed(matrix_complex b, int r, int c)
		{
			if (b.NumCols() > this->NumCols() || b.NumRows() > this->NumRows())
			{
				cout << "Error (Overwrite_Submatrix): sub matrix dimensions exceed destination dimensions" << endl;
				return;
			}

			if ((r + b.NumCols() > this->NumRows()) || (c + b.NumRows() > this->NumCols()))
			{
				cout << "Error (Overwrite_Submatrix): sub matrix size plus dimensions exceed destination dimensions" << endl;
				return;
			}

			for (int i = 0; i < b.NumRows(); i++)
			{
				for (int j = 0; j < b.NumCols(); j++)
				{
					get(r + j, c + i) = b(i, j);
				}
			}

		}




		//============================================================================
		//
		//============================================================================
		complex< T > Det_3x3(int r, int c)
		{
			if (r + 2 >= NumRows() || c + 2 >= NumCols())
			{
				cout << "Error (Det_3x3): Out of bounds error" << endl;
				return complex<T>( 0.0, 0.0 );
			}

			complex<T> c1 = get(r, c);
			complex<T> c2 = -get(r, c + 1);
			complex<T> c3 = get(r, c + 2);

			return  c1 * (get(r + 1, c + 1) * get(r + 2, c + 2) - get(r + 1, c + 2)*get(r + 2, c + 1)) +
				c2 * (get(r + 1, c) * get(r + 2, c + 2) - get(r + 1, c + 2) * get(r + 2, c)) +
				c3 * (get(r + 1, c) * get(r + 2, c + 1) - get(r + 2, c) * get(r + 1, c + 1));

		}

		//============================================================================
		//
		//============================================================================
		void ToZero()
		{
			for (int i = 0; i < this->NumRows(); i++)
				for (int j = 0; j < this->NumCols(); j++)
					get(i, j) = complex<T>(0.0, 0.0);
		}


		//============================================================================
		//
		//============================================================================
		void Round_to_N_digits(int N)
		{
			for (int r = 0; r < this->NumRows(); r++)
				for (int c = 0; c < this->NumCols(); c++)
					get(r, c) = complex< T >(round_to_n_digits(get(r, c).real(), N), round_to_n_digits(get(r, c).imag(), N));
		}
		

		//============================================================================
		//
		//============================================================================
		void ClipToZero(T eps)
		{
			for (int i = 0; i < this->NumRows(); i++)
				for (int j = 0; j < this->NumCols(); j++)
					if ((( (get(i, j).real() > 0) && (get(i, j).real() < eps)) || 
						  ((get(i, j).imag() > 0) && (get(i, j).imag() < eps)))||
						(((get(i, j).real() < 0) && (get(i, j).real() >-eps)) ||
						  ((get(i, j).imag() < 0) && (get(i, j).imag() >-eps))))
					{
						get(i, j) = complex<T>(0.0, 0.0);
					}
						
		}



		//============================================================================
		//
		//============================================================================
		inline void SwapRow(int r1, int r2)
		{
			if (r1 >= this->NumRows() || r2 >= this->NumRows())
			{
				cout << "Error (SwapRow): index out of bounds" << endl;
				return;
			}

			for (int c = 0; c < this->NumCols(); c++)
			{
				SWAP<complex<T>>(get(r1, c), get(r2, c));
			}
		}

		//============================================================================
		//
		//============================================================================
		inline void SwapColumn(int c1, int c2)
		{
			if (c1 >= this->NumCols() || c2 >= this->NumCols())
			{
				cout << "Error (SwapColumn): index out of bounds" << endl;
				return;
			}

			for (int r = 0; r < this->NumRows(); r++)
			{
				SWAP<complex<T>>(get(r, c1), get(r, c2));
			}
		}

		//============================================================================
		//
		//============================================================================
		complex< T > Frobenius_Norm()
		{
			complex< T > sum = complex< T >( 0.0, 0.0);
			for (int r = 0; r < NumRows(); r++)
			{
				for (int c = 0; c < NumCols(); c++)
				{
					sum += get(r, c)*get(r, c);
				}
			}

			return std::sqrt(sum);
		}

		//============================================================================
		//
		//============================================================================
		//http://stackoverflow.com/questions/19840213/how-to-read-values-from-a-2d-initializer-list-and-put-them-in-a-2d-vector
		matrix_complex(const std::initializer_list<std::initializer_list<complex<T>>>& list)
		{

			this->SX = list.size();
			this->SY = (*list.begin()).size();
			this->create();

			int r = 0;
			for (const auto& l : list) {
				int c = 0;
				for (const auto d : l) {
					(*this)(r, c++) = d; // rather than get() because of the bounds check
				}
				++r;
			}
		}





		//	virtual void Set_Zero_Epsilon() = 0;

		T precision = numeric_limits<T>::epsilon(); // defaults to float eps
	private:


		//============================================================================
		//
		//============================================================================
		void CopyData(T *p)
		{
			memcpy(data, p, SX*SY*sizeof(complex<T>));
		}



		bool is_transposed = false;
		unsigned int SX = 0;
		unsigned int SY = 0;


		matrix_complex < T > *out_start = 0;
		matrix_complex < T > *out = 0;

		complex < T >* data = 0;

	};









};



#endif