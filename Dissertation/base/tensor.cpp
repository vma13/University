#include <new>
#include <limits>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_matrix_double.h>



class Patient {

public:
  std::string name;  
  std::vector<double> x, y, z;
  std::vector< std::vector<double> > data;

  Patient(std::string name) {
      this->name = name;
      this->x = getData("x0l.dat");
      this->y = getData("y0l.dat");
      this->z = getData("z0l.dat");
      (this->data).push_back(this->x);
      (this->data).push_back(this->y);
      (this->data).push_back(this->z);

      /*
      for(std::vector<double>::iterator it = (this->x).begin(); it != (this->x).end(); ++it) {
        std::cout << *it << " ";
      }          
      std::cout << std::endl;
      
      std::cout << data[0][6] << std::endl;
      */
  }
  ~Patient() {}

private:
    std::vector<double> getData(std::string filename){
        std::string tmp = filename;
        filename = this->name + "/Tables/" + filename;
        // cout << filename << endl;
        // cout << (this->name).substr((this->name).size() - 4, 4) << endl;
        std::string line;
        std::vector<std::string> array;
        std::vector<double> data;

        std::fstream _file ((filename).c_str());
        if (!(_file.is_open()) && (this->name).substr((this->name).size() - 4, 4) != ".000")  {
            this->name += ".000";
            return getData(tmp);
        } 

        getline (_file,line);
        getline (_file,line);

        split(line, "        \t", array);            
        for(std::vector<std::string>::iterator it = array.begin()+1; it != array.end(); ++it) {
            data.push_back(atof((*it).c_str()));
        }          
        return data;
    }
    void split(const std::string& str, const std::string& delimiters , std::vector<std::string>& tokens) {
        // Skip delimiters at beginning.
        std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        // Find first "non-delimiter".
        std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            // Found a token, add it to the vector.
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of(delimiters, pos);
            // Find next "non-delimiter"
            pos = str.find_first_of(delimiters, lastPos);
        }
    }
};

void print(  std::vector< std::vector<double> > data, int m, int n) {
  int i, j;
  for (i = 0; i<m; ++i) {
    for (j = 0; j<n; ++j) {
        std::cout << data[i][j] <<  " ";
    }
    std::cout << std::endl;
  }
}


template <size_t Dimention>
class IndexIterator {
  public:
    size_t indices[Dimention];
    const size_t *sizes;

    IndexIterator(const size_t *sizes) : sizes(sizes) {
      for (size_t i = 0; i < Dimention; ++i) {
        indices[i] = 0;
      }
    }

    size_t *operator *() {
      return indices;
    }

    IndexIterator &operator ++() {
      for(size_t i = Dimention - 1; ++indices[i] >= sizes[i] && i > 0; --i) {
        indices[i] = 0;
      }
      return *this;
    }

    IndexIterator operator ++(int) {
      IndexIterator tmp(*this); 
      operator ++(); 
      return tmp;
    }

    bool operator ==(const IndexIterator &rhs) const {
      for (size_t i = 0; i < Dimention; ++i) {
        if (indices[i] != rhs.indices[i]) return false;
      }
      return true;
    }

    bool operator !=(const IndexIterator &rhs) const {
      return !this->operator ==(rhs);
    }

    operator bool() const {
      return indices[0] < sizes[0];
    }
};

template <size_t Dimention>
class Tensor {
  public:
    size_t sizes[Dimention];
    double *data;

    explicit Tensor(size_t sizes_v[Dimention]) : data(NULL) {
      size_t summary_size = 1;

      for (size_t i = 0; i < Dimention; ++i) {
        sizes[i] = sizes_v[i];
        if (std::numeric_limits<size_t>::max()/sizes_v[i] < summary_size) {
          throw std::bad_alloc();
        }
        summary_size *= sizes_v[i];
      }

      data = new double[summary_size];

      for (size_t offset = 0; offset < summary_size; ++offset) {
        data[offset] = 0.0;
      }
    }

    ~Tensor() {
      if (data) delete[] data;
    }

    size_t size() const {
      size_t summary_size = 1;

      for (size_t i = 0; i < Dimention; ++i) {
        summary_size *= sizes[i];
      }

      return summary_size;
    }

    size_t size(size_t dim) const {
      return sizes[dim];
    }

    size_t offset(size_t *indices) const {
      size_t offset_value = indices[0];

      for (size_t i = 1; i < Dimention; ++i) {
        offset_value = offset_value*sizes[i] + indices[i];
      }

      return offset_value;
    }

    double &operator [](size_t *indices) {
      return data[offset(indices)];
    }

    void flatten(Tensor<2> &matrix, size_t dim) {
      if (matrix.size() != size()) throw std::bad_alloc();

      matrix.sizes[0] = size(dim);
      matrix.sizes[1] = size()/size(dim);
      const size_t matrix_size = matrix.size();

      std::swap(sizes[0], sizes[dim]);
      IndexIterator<Dimention> iterator(sizes);
      for (size_t matrix_offset = 0; matrix_offset < matrix_size; ++matrix_offset) {
        std::swap(iterator.indices[0], iterator.indices[dim]);
        matrix.data[matrix_offset] = data[offset(iterator.indices)];
        std::swap(iterator.indices[0], iterator.indices[dim]);
        ++iterator;
      }
      std::swap(sizes[0], sizes[dim]);
    }
};


void print(const Tensor<2> &matrix) {
  size_t i, j;

  for (i = 0; i < matrix.sizes[0]; ++i) {
    for (j = 0; j < matrix.sizes[1]; ++j) {
      std::cout << " " << matrix.data[i*matrix.sizes[1] + j];
    }
    std::cout << std::endl;
  }
}

gsl_matrix* TensorToGSLMatrix(const Tensor<2> &tensor) {
  size_t i, j;
  int M, N;

  M = (int) tensor.sizes[0];  
  N = (int) tensor.sizes[1];  

  gsl_matrix* matrix = gsl_matrix_alloc(M, N);


  for (i = 0; i < tensor.sizes[0]; ++i) {
    for (j = 0; j < tensor.sizes[1]; ++j) {
      gsl_matrix_set(matrix, i, j, tensor.data[i*tensor.sizes[1] + j]);    
    }
  }
  if (M < N) {
    gsl_matrix* matrix_t = gsl_matrix_alloc(N, M);
    gsl_matrix_transpose_memcpy (matrix_t, matrix);
    return matrix_t;
  } else {
    return matrix;
  }
}

void gsl_matrix_print(gsl_matrix* A, int M, int N) {
  int i,j;
  for (i=0; i<M; i++) {
    for (j=0; j<N; j++)
      printf("%g ", gsl_matrix_get(A, i, j));
    printf("\n");
  }
}

void gsl_vector_print(gsl_vector* A, int N) {
  int i;
  for (i=0; i<N; i++) 
    printf("%g ", gsl_vector_get(A, i));
  printf("\n");
}


int main() {
  const int count = 6;
  int i,j,k;
  std::string files[count] = {"0101", "0201", "0301", "0501", "1201", "1701"};
  std::vector< std::vector< std::vector<double> > > patients(count);
  
  for(i = 0; i<count; ++i)
    patients[i] = Patient("norma/0000" + files[i]).data;
 
  

  size_t cube_sizes[3] = {3, 64, count};
  Tensor<3> cube(cube_sizes);
  size_t matrix_sizes[3] = {cube.size(), 1};
  Tensor<2> matrix(matrix_sizes);
  int M, N;
  std::cout << cube.size() << std::endl;
  for (size_t offset = 0; offset < cube.size(); ++offset) {
    i = offset/(3*64);
    j = (offset%(3*64))/64;
    k = (offset%(3*64))%64;
    cube.data[offset] = patients[i][j][k];
  }

  /* FLATTEN X */
  std::cout << "X flatten:" << std::endl;
  cube.flatten(matrix, 0);
  // print(matrix);

  M = (int) matrix.sizes[1];
  N = (int) matrix.sizes[0];

  gsl_matrix* Ax = TensorToGSLMatrix(matrix);
	gsl_matrix* Ux;
  gsl_matrix* Vx;
  gsl_vector* Sx;
  gsl_vector* workx;

  gsl_matrix_print(Ax, Ax->size1, Ax->size2);
  workx = gsl_vector_alloc(N);
  Sx = gsl_vector_alloc(N);
  Vx = gsl_matrix_alloc(N, N);

  gsl_linalg_SV_decomp(Ax, Vx, Sx, workx);
  Ux = Ax;
  std::cout << "A = U S V^T" << std::endl;
  std::cout << "U" << std::endl;
  gsl_matrix_print(Ux, M, N);
  std::cout << "S" << std::endl;
  gsl_vector_print(Sx, N);
  std::cout << "V" << std::endl;
  gsl_matrix_print(Vx, Vx->size1, Vx->size2);
  std::cout << "work" << std::endl;
  gsl_vector_print(workx, N);



  /* FLATTEN Y */
  std::cout << "Y flatten:" << std::endl;
  cube.flatten(matrix, 1);
  //print(matrix);
  M = (int) matrix.sizes[1];
  N = (int) matrix.sizes[0];

  gsl_matrix* Ay = TensorToGSLMatrix(matrix);
	gsl_matrix* Uy;
  gsl_matrix* Vy;
  gsl_vector* Sy;
  gsl_vector* worky;

  gsl_matrix_print(Ay, Ay->size1, Ay->size2);
  worky = gsl_vector_alloc(Ay->size2);
  Sy = gsl_vector_alloc(Ay->size2);
  Vy = gsl_matrix_alloc(Ay->size2, Ay->size2);

  gsl_linalg_SV_decomp(Ay, Vy, Sy, worky);
  Uy = Ay;
  std::cout << "A = U S V^T" << std::endl;
  std::cout << "U" << std::endl;
  gsl_matrix_print(Uy, Uy->size1, Uy->size2);
  std::cout << "S" << std::endl;
  gsl_vector_print(Sy, Ay->size2);
  std::cout << "V" << std::endl;
  gsl_matrix_print(Vy, Vy->size1, Vy->size2);
  std::cout << "work" << std::endl;
  gsl_vector_print(worky, Ay->size2);

  /* FLATTEN Z */
  std::cout << "Z flatten:" << std::endl;
  cube.flatten(matrix, 2);
  //print(matrix);

  M = (int) matrix.sizes[1];
  N = (int) matrix.sizes[0];

  gsl_matrix* Az = TensorToGSLMatrix(matrix);
	gsl_matrix* Uz;
  gsl_matrix* Vz;
  gsl_vector* Sz;
  gsl_vector* workz;

  gsl_matrix_print(Az, Az->size1, Az->size2);
  workz = gsl_vector_alloc(Az->size2);
  Sz = gsl_vector_alloc(Az->size2);
  Vz = gsl_matrix_alloc(Az->size2, Az->size2);
  gsl_linalg_SV_decomp(Az, Vz, Sz, workz);
  Uz = Az;
  std::cout << "A = U S V^T" << std::endl;
  std::cout << "U" << std::endl;
  gsl_matrix_print(Uz, Uz->size2, Uz->size2);
  std::cout << "S" << std::endl;
  gsl_vector_print(Sz, Az->size2);
  std::cout << "V" << std::endl;
  gsl_matrix_print(Vz, Vz->size1, Vz->size2);
  std::cout << "work" << std::endl;
  gsl_vector_print(workz, Az->size2);

  return 0;
};
