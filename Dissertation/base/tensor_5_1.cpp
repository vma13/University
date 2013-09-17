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
#include <math.h>

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_blas.h>

#define NORMA 0

const int count = 10;

#if NORMA
  /* FOR LEARNING DATA */
   std::string files[count] = {"0101","0201","0301","0501","1201","1701","0102","0202", "0302", "0502"};
  /* FOR TEST DATA */  
  //std::string files[count] = {"3601", "2802", "2602","2501","2301","1801","1702", "1701", "1207", "1206"};
  std::string folder_name = "norma/0000";
#else
  /* FOR LEARNING DATA */
   std::string files[count] = {"0602","0603","0605","2001","2002","3501", "3502", "4301", "4302", "4501"};
  /* FOR TEST DATA */  
  //std::string files[count] = {"4701","4702","4703","5301","5803", "5303", "5801", "2001", "0602", "0603"};
  std::string folder_name = "ibs_pics/0000";
#endif
  

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
      normalize_data();
  }
  ~Patient() {}

private:
    void normalize_data() {
        int i,j;
        double sum = 0;
        for(j = 0; j < 64; j++ ) { 
          sum += this->data[0][j]*this->data[0][j] + this->data[1][j]*this->data[1][j] +  
                 this->data[2][j]*this->data[2][j];
        }
        sum = sqrt(sum);
        for(j = 0; j < 64; j++ ) { 
          this->data[0][j] /= sum;
          this->data[1][j] /= sum;
          this->data[2][j] /= sum;
        }
        

    }
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
        std::swap(sizes[0], sizes[dim]);
        matrix.data[matrix_offset] = data[offset(iterator.indices)];
        std::swap(iterator.indices[0], iterator.indices[dim]);
        std::swap(sizes[0], sizes[dim]);
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

bool nearly_equal(double a, double b, double epsilon) {
  const double abs_a = fabs(a);
  const double abs_b = fabs(b);
  const double diff  = fabs(a - b);

  if (a == b) { // shortcut, handles infinities
    return true;
  } else if (a * b == 0.0) { // a or b or both are zero
    // relative error is not meaningful here
    return diff < (epsilon * epsilon);
  } else { // use relative error
    return diff / (abs_a + abs_b) < epsilon;
  }
}

int main() {
  int i,j,k;
  double s;

#if 1



  std::vector< std::vector< std::vector<double> > > patients(count);
  
  for(i = 0; i<count; ++i) {
    std::cout << files[i] << std::endl;
    patients[i] = Patient(folder_name + files[i]).data;
  }

  gsl_matrix* A_avg = gsl_matrix_alloc(3, 16);
  for(i = 0; i<3; ++i) {
    for(j = 0; j<16; ++j) { 
      s = 0;
      for(k = 0; k < count; ++k) {
        s+=patients[k][i][4*j];
      }
      gsl_matrix_set(A_avg, i, j, s/count);            
    }
  }
  // gsl_matrix_print(A_avg, 3, 64);


  gsl_matrix* S = gsl_matrix_alloc(3, 16);
  for(i = 0; i<3; ++i) {
    for(j = 0; j<16; ++j) { 
      s = 0;
      for(k = 0; k < count; ++k) {
        s += pow((patients[k][i][4*j] - gsl_matrix_get(A_avg, i, j)), 2);            
      }
      gsl_matrix_set(S, i, j, sqrt(s/count));            	
    }
  }
  // gsl_matrix_print(S, 3, 64);
  gsl_matrix *T[count];    
  for(k = 0; k < count; ++k) {
    T[k] =  gsl_matrix_alloc(3, 16);
    for(i = 0; i<3; ++i) {
      for(j = 0; j<16; ++j) { 
        s = (patients[k][i][4*j] - gsl_matrix_get(A_avg, i, j)) / gsl_matrix_get(S, i, j);            
        gsl_matrix_set(T[k], i, j, s);            	
      }
    }
  }

  size_t cube_sizes[3] = {3, 16, count};
  Tensor<3> cube(cube_sizes);
  size_t matrix_sizes[3] = {cube.size(), 1};
  Tensor<2> matrix(matrix_sizes);
  int M, N;
  std::cout << cube.size() << std::endl;
  for (size_t offset = 0; offset < cube.size(); ++offset) {
    i = offset/(3*16);
    j = (offset%(3*16))/16;
    k = (offset%(3*16))%16;
    cube.data[offset] = gsl_matrix_get(T[i], j, k); // patients[i][j][k];
  }

#else

  size_t cube_sizes[3] = {3, 3, 3};
  Tensor<3> cube(cube_sizes);
  size_t matrix_sizes[3] = {cube.size(), 1};
  Tensor<2> matrix(matrix_sizes);
  int M, N;

  double tdata[27] = {
    0.9073,  0.7158, -0.3698,
    0.8924, -0.4898,  2.4288,
    2.1488,  0.3054,  2.3753,

    1.7842,  1.6970,  0.0151,
    1.7753, -1.5077,  4.0337,
    4.2495,  0.3207,  4.7146,

    2.1236, -0.0740,  1.4429,
   -0.6631,  1.9103, -1.7495,
    1.8260,  2.1335, -0.2716
  };

  for (size_t offset = 0; offset < cube.size(); ++offset) {
    cube.data[offset] = tdata[offset];
  }

#endif

  /* FLATTEN X */
  // std::cout << "X flatten:" << std::endl;
  cube.flatten(matrix, 0);
  // print(matrix);

  M = (int) matrix.sizes[1];
  N = (int) matrix.sizes[0];

  gsl_matrix* Ax = TensorToGSLMatrix(matrix);
	gsl_matrix* Ux;
  gsl_matrix* Vx;
  gsl_vector* Sx;
  gsl_vector* workx;

  //gsl_matrix_print(Ax, Ax->size1, Ax->size2);
  workx = gsl_vector_alloc(N);
  Sx = gsl_vector_alloc(N);
  Vx = gsl_matrix_alloc(N, N);

  gsl_linalg_SV_decomp(Ax, Vx, Sx, workx);
  Ux = Ax;
  //std::cout << "A = U S V^T" << std::endl;
  //std::cout << "U" << std::endl;
  //gsl_matrix_print(Ux, M, N);
  std::cout << "S1" << std::endl;
  gsl_vector_print(Sx, N);
  //std::cout << "V" << std::endl;
  //gsl_matrix_print(Vx, Vx->size1, Vx->size2);
  //std::cout << "work" << std::endl;
  //gsl_vector_print(workx, N);

  if (M < N) {
    Vx = gsl_matrix_alloc(Ux->size1, Ux->size1);
    for(i = 0; i < Ux->size1; ++i) {
      for(j = 0; j < Ux->size1; ++j) {
        if (j < Ux->size2 )
          gsl_matrix_set(Vx, j, i, gsl_matrix_get(Ux,i,j));
        else
          gsl_matrix_set(Vx, j, i, 0.0);
      }
    }
  }


  /* FLATTEN Y */
  //std::cout << "Y flatten:" << std::endl;
  cube.flatten(matrix, 1);
  //print(matrix);
  M = (int) matrix.sizes[1];
  N = (int) matrix.sizes[0];

  gsl_matrix* Ay = TensorToGSLMatrix(matrix);
	gsl_matrix* Uy;
  gsl_matrix* Vy;
  gsl_vector* Sy;
  gsl_vector* worky;

  //gsl_matrix_print(Ay, Ay->size1, Ay->size2);
  worky = gsl_vector_alloc(Ay->size2);
  Sy = gsl_vector_alloc(Ay->size2);
  Vy = gsl_matrix_alloc(Ay->size2, Ay->size2);

  gsl_linalg_SV_decomp(Ay, Vy, Sy, worky);
  Uy = Ay;
  //std::cout << "A = U S V^T" << std::endl;
  //std::cout << "U" << std::endl;
  //gsl_matrix_print(Uy, Uy->size1, Uy->size2);
  std::cout << "S2" << std::endl;
  gsl_vector_print(Sy, Ay->size2);
  //std::cout << "V" << std::endl;
  //gsl_matrix_print(Vy, Vy->size1, Vy->size2);
  //std::cout << "work" << std::endl;
  //gsl_vector_print(worky, Ay->size2);

  if (M < N) {
    Vy = gsl_matrix_alloc(Uy->size1, Uy->size1);
    for(i = 0; i < Uy->size1; ++i) {
      for(j = 0; j < Uy->size1; ++j) {
        if (j < Uy->size2 )
          gsl_matrix_set(Vy, j, i, gsl_matrix_get(Uy,i,j));
        else
          gsl_matrix_set(Vy, j, i, 0.0);
      }
    }
  }

  /* FLATTEN Z */
  //std::cout << "Z flatten:" << std::endl;
  cube.flatten(matrix, 2);
  //print(matrix);

  M = (int) matrix.sizes[1];
  N = (int) matrix.sizes[0];

  gsl_matrix* Az = TensorToGSLMatrix(matrix);
	gsl_matrix* Uz;
  gsl_matrix* Vz;
  gsl_vector* Sz;
  gsl_vector* workz;

  //gsl_matrix_print(Az, Az->size1, Az->size2);
  workz = gsl_vector_alloc(Az->size2);
  Sz = gsl_vector_alloc(Az->size2);
  Vz = gsl_matrix_alloc(Az->size2, Az->size2);
  gsl_linalg_SV_decomp(Az, Vz, Sz, workz);
  Uz = Az;
  //std::cout << "A = U S V^T" << std::endl;
  //std::cout << "U" << std::endl;
  //gsl_matrix_print(Uz, Uz->size2, Uz->size2);
  std::cout << "S3" << std::endl;
  gsl_vector_print(Sz, Az->size2);
  //std::cout << "V" << std::endl;
  //gsl_matrix_print(Vz, Vz->size1, Vz->size2);
  //std::cout << "work" << std::endl;
  //gsl_vector_print(workz, Az->size2);

  if (M < N) {
    Vz = gsl_matrix_alloc(Uz->size1, Uz->size1);
    for(i = 0; i < Uz->size1; ++i) {
      for(j = 0; j < Uz->size1; ++j) {
        if (j < Uy->size2 )
          gsl_matrix_set(Vz, j, i, gsl_matrix_get(Uz,i,j));
        else
          gsl_matrix_set(Vz, j, i, 0.0);
      }
    }
  }

/*
  gsl_matrix *Vx_t, *Uy_t, *Vz_t;
  Vx_t = gsl_matrix_alloc(Vx->size2, Vx->size1);
  gsl_matrix_transpose_memcpy (Vx_t, Vx);

  std::cout << "M = " << Uy->size1 << " N = " << Uy->size2 << std::endl;
  Uy_t = gsl_matrix_alloc(Uy->size1, Uy->size1);
  for(i = 0; i < Uy->size1; ++i) {
    for(j = 0; j < Uy->size1; ++j) {
      if (j < Uy->size2 )
        gsl_matrix_set(Uy_t, j, i, gsl_matrix_get(Uy,i,j));
      else
        gsl_matrix_set(Uy_t, j, i, 0.0);
    }
  }
  //gsl_matrix_transpose_memcpy (Uy_t, Uy);
  gsl_matrix_print(Uy_t,64,64);

  Vz_t = gsl_matrix_alloc(Vz->size2, Vz->size1);
  gsl_matrix_transpose_memcpy (Vz_t, Vz);

  std::cout << "M = " << Uy_t->size1 << " N = " << Uy_t->size2 << std::endl;
 */

  Tensor<3> G(cube_sizes);
  /* compute G */ {
    gsl_matrix *Vs[3] = {Vx, Vy, Vz};
    double component, summand;

    for(IndexIterator<3> IJK(cube_sizes); IJK; ++IJK) {
      component = 0.0;
      for(IndexIterator<3> ijk(cube_sizes); ijk; ++ijk) {
        summand = cube[*ijk];
        for (size_t dim = 0; dim < 3; ++dim) {
          summand *= gsl_matrix_get(Vs[dim], (*IJK)[dim], (*ijk)[dim]);
        }
        component += summand;
      }
      G[*IJK] = component;
    }
  }

  /* HOSVD(cube) = G * Vs[0] * Vs[1] * Vs[2] */

  /* validate result */ {
    Tensor<3> T(cube_sizes);
    
    gsl_matrix *Vs[3] = {Vx, Vy, Vz};
    double component, summand;

    for(IndexIterator<3> ijk(cube_sizes); ijk; ++ijk) {
      component = 0.0;
      for(IndexIterator<3> IJK(cube_sizes); IJK; ++IJK) {
        summand = G[*IJK];
        for (size_t dim = 0; dim < 3; ++dim) {
          summand *= gsl_matrix_get(Vs[dim], (*IJK)[dim], (*ijk)[dim]);
        }
        component += summand;
      }
      T[*ijk] = component;
    }

    /* T is restored cube tensor */
    bool valid_HOSVD = true;

    for(IndexIterator<3> ijk(cube_sizes); ijk; ++ijk) {
      if (!nearly_equal(cube[*ijk], T[*ijk], 1e-3)) {
        // wrong HOSVD
        valid_HOSVD = false;

        printf("Error in HOSVD: [");
        for (size_t dim = 0; dim < 3; ++dim) {
          printf("%d%c ", (*ijk)[dim], dim == 2 ? ']' : ',');
        }
        printf("%.15lf != %.15lf\n", cube[*ijk], T[*ijk]);
      }
    }
    if (valid_HOSVD) {
      printf("OK: HOSVD work!\n");
    } else {
      printf("HOSVD computation FAILED.\n");
    }
  }
 

  gsl_matrix *Vx_t, *tmp[count], *Z[count], *Z_avg;
  Vx_t = gsl_matrix_alloc(Vx->size2, Vx->size1);
  gsl_matrix_transpose_memcpy (Vx_t, Vx);
  

  for(i =0; i<count; ++i) {
    Z[i] = gsl_matrix_alloc(3,16);
    tmp[i] = gsl_matrix_alloc(3,16);
    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, Vx_t, T[i], 0.0, tmp[i]);
    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, tmp[i], Vy, 0.0, Z[i]);
  }
  Z_avg = gsl_matrix_alloc(3,16);
  double avg = 0;
  for(i =0; i<3; ++i) {
    for(j =0; j<16; ++j) {
      avg = 0;
      gsl_matrix_set(Z_avg, i, j, 0);
      for(k =0; k<count; ++k) 
        avg += gsl_matrix_get(Z[k], i, j);
      avg /= count;
      gsl_matrix_set(Z_avg, i, j, avg);
    }
  }
  std::cout << "Z_avg" << std::endl;
  //gsl_matrix_print(Z_avg, Z_avg->size1, Z_avg->size2);
  // for(k =0; k<count; ++k) 
   // std::cout << gsl_matrix_get(Z[k], 0, 0) << std::endl;

#if NORMA
  std::ofstream data ("data_norm");
#else
  std::ofstream data ("data_ibs");
#endif
  /*
  for(j =0; j<64; ++j) {
    data << gsl_matrix_get(Z_avg, 0, j) << " " << gsl_matrix_get(Z_avg, 1, j) << " " << gsl_matrix_get(Z_avg, 2, j) << std::endl;
  }  
  */
  /*
  for(i =0; i<count; ++i) {
    for(j =0; j<64; ++j) {
      data << gsl_matrix_get(Z[i], 0, j) << " " << gsl_matrix_get(Z[i], 1, j) << " " << gsl_matrix_get(Z[i], 2, j) << std::endl;
    }  
  }
  */
  
  for(j =0; j<3; ++j) {
    for(k =0; k<16; ++k) {
      data << gsl_matrix_get(Z_avg, j, k) << " ";
    }
    data << std::endl;
  }

  for(i =0; i<count; ++i) {
    for(j =0; j<3; ++j) {
      for(k =0; k<16; ++k) {
        data << gsl_matrix_get(Z[i], j, k) << " ";
      }
      data << std::endl;
    }
  }    
  
  std::ofstream dataV1 ("data_V1");
  for(i = 0; i < Vx -> size1; ++i) {
    for(j = 0; j < Vx -> size2; ++j) {
      dataV1 << gsl_matrix_get(Vx, i, j) << " " ;
    }
    dataV1 << std::endl;
  }  

  std::ofstream dataV2 ("data_V2");
  for(i = 0; i < Vy -> size1; ++i) {
    for(j = 0; j < Vy -> size2; ++j) {
      dataV2 << gsl_matrix_get(Vy, i, j) << " " ;
    }
    dataV2 << std::endl;
  }  

  data.close();
  dataV1.close();
  dataV2.close();
  std::cout << "Ядро" << std::endl;
  for(i = 0; i < 3*16*10; ++i) {
    std::cout << G.data[i] << " ";
    if (i > 1 && (i-1)%16 == 0) std::cout <<std::endl;
  }

  return 0;
};
