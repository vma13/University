// g++ -I /usr/local/include/gsl -lgsl -lgslcblas -lm my_tenzor.cpp
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

const int count = 24;

std::string files[count] = {"norma/00003601", "norma/00002802", "norma/00002602","norma/00002501","norma/00002301",
			    "norma/00001801","norma/00001702", "norma/00001701", "norma/00001207", "norma/00001206", "norma/00000101", "norma/00000102", 
			    "ibs_pics/00004701","ibs_pics/00004702","ibs_pics/00004703","ibs_pics/00005301","ibs_pics/00005803", 
			    "ibs_pics/00005303", "ibs_pics/00005801", "ibs_pics/00002001", "ibs_pics/00000602", "ibs_pics/00000603", "ibs_pics/00004301", "ibs_pics/00004302"
};


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
    //    normalize_data(); 
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
    //std::cout << filename  << std::endl;    
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
	/*
    void flatten(Tensor<2> &matrix, size_t dim) {
      if (matrix.size() != size()) throw std::bad_alloc();

      matrix.sizes[0] = size(dim);
      matrix.sizes[1] = size()/size(dim);
      const size_t matrix_size = matrix.size();

      std::swap(sizes[0], sizes[dim]); // лишнее действие
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
	*/
    void flatten(Tensor<2> &matrix, size_t dim) {
      if (matrix.size() != size()){
	throw std::bad_alloc();
      }
      matrix.sizes[0] = size(dim);
      matrix.sizes[1] = size()/size(dim);
      const size_t matrix_size = matrix.size();
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

template<typename T>
struct array{
    T* data;
    int w,h;
    array():data(NULL),w(0),h(0){}
    array(int width,int height){
        data=new T[width*height];
        w=width;
        h=height;}
    ~array(){
        delete[] data;}
    T& operator()(int x,int y){
        return data[y*w+x];}};

void print(  std::vector< std::vector<double> > data, int m, int n) {
  int i, j;
  for (i = 0; i<m; ++i) {
    for (j = 0; j<n; ++j) {
        std::cout << data[i][j] <<  " ";
    }
    std::cout << std::endl;
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
  std::vector< std::vector< std::vector<double> > > patients(count);
  
  for(i = 0; i<count; ++i) {
    std::cout << files[i] << std::endl;
    patients[i] = Patient(files[i]).data;
  } 

  gsl_matrix* A_avg = gsl_matrix_alloc(3, 64);
  for(i = 0; i<3; ++i) {
    for(j = 0; j<64; ++j) { 
      s = 0;
      for(k = 0; k < count; ++k) {
        s+=patients[k][i][j];
      }
      gsl_matrix_set(A_avg, i, j, s/count);            
    }
  }
  //std::cout << "A_avg" << std::endl; 
  gsl_matrix_print(A_avg, 3, 64);

  gsl_matrix* S = gsl_matrix_alloc(3, 64);
  for(i = 0; i<3; ++i) {
    for(j = 0; j<64; ++j) { 
      s = 0;
      for(k = 0; k < count; ++k) {
        s += pow((patients[k][i][j] - gsl_matrix_get(A_avg, i, j)), 2);            
      }
      gsl_matrix_set(S, i, j, sqrt(s/count));            	
    }
  }
  //  std::cout << "S" << std::endl; 
  gsl_matrix_print(S, 3, 64);
  gsl_matrix *T[count];    
  for(k = 0; k < count; ++k) {
    T[k] =  gsl_matrix_alloc(3, 64);
    for(i = 0; i<3; ++i) {
      for(j = 0; j<64; ++j) { 
        s = (patients[k][i][j] - gsl_matrix_get(A_avg, i, j)) / gsl_matrix_get(S, i, j);            
	//s = patients[k][i][j];
        gsl_matrix_set(T[k], i, j, s);            	
      }
    }
  }
  size_t cube_sizes[3] = {3, 64, count};
  Tensor<3> cube(cube_sizes);
  size_t matrix_sizes[3] = {cube.size(), 1};
  Tensor<2> matrix(matrix_sizes);
  int M, N;
  std::cout << cube.size() << std::endl;
  for (size_t offset = 0; offset < cube.size(); ++offset) {
    i = offset/(3*64); //0...20
    j = (offset%(3*64))/64; //0...3
    k = (offset%(3*64))%64; //0...64 
    cube.data[offset] = gsl_matrix_get(T[i], j, k); // patients[i][j][k];
  }

  // start calculating, flatten
  std::cout << "HOSVD 3x(64*20)" << std::endl; 
  cube.flatten(matrix, 0);

  gsl_matrix* Ax = TensorToGSLMatrix(matrix);
  gsl_matrix* Ux;
  gsl_matrix* Vx;
  gsl_vector* Sx;
  gsl_vector* workx;

  workx = gsl_vector_alloc(Ax->size2);
  Sx = gsl_vector_alloc(Ax->size2);
  Vx = gsl_matrix_alloc(Ax->size2, Ax->size2);

  gsl_linalg_SV_decomp(Ax, Vx, Sx, workx);
  //Ux = Ax;

  gsl_matrix_transpose(Vx); 

  std::cout << "S1" << std::endl;
  gsl_vector_print(Sx, Ax->size2);
  std::cout << "V" << std::endl;
  gsl_matrix_print(Vx, Vx->size1, Vx->size2);

  //Нам нужен Vx, это наше U; V(3x3)


/* FLATTEN HOSVD 64x(3*24) */
  std::cout << "HOSVD 64x(3*24)" << std::endl;
  cube.flatten(matrix, 1);
  //print(matrix);

  N = (int) matrix.sizes[0]; // 64
  M = (int) matrix.sizes[1]; // 72
  std::cout << M << " +++ " << N << std::endl;


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
  gsl_matrix_transpose(Vy); 
  //Uy = Ay;
  //std::cout << "A = U S V^T" << std::endl;
  //std::cout << "U" << std::endl;
  //gsl_matrix_print(Uy, Uy->size1, Uy->size2);
  std::cout << "S2" << std::endl;
  gsl_vector_print(Sy, Ay->size2);
  //std::cout << "V" << std::endl;
  //gsl_matrix_print(Vy, Vy->size1, Vy->size2);
  //  std::cout << Vy->size1 << ' ' << Vy->size2 << std::endl;
  //std::cout << "work" << std::endl;
  //gsl_vector_print(worky, Ay->size2);

  //Нам нужен Vy, это наше V; V(3x3)


  /* FLATTEN HOSVD 24x(3*64) */
  std::cout << "HOSVD 24x(3*64)" << std::endl;
  cube.flatten(matrix, 2);
  //print(matrix);

  N = (int) matrix.sizes[0]; //24
  M = (int) matrix.sizes[1]; // 3*64
  std::cout << M << " +++ " << N << std::endl;

  gsl_matrix* Az = TensorToGSLMatrix(matrix);
  gsl_matrix* Uz;
  gsl_matrix* Vz;
  gsl_vector* Sz;
  gsl_vector* workz;

  //gsl_matrix_print(Ay, Ay->size1, Ay->size2);
  workz = gsl_vector_alloc(Az->size2);
  Sz = gsl_vector_alloc(Az->size2);
  Vz = gsl_matrix_alloc(Az->size2, Az->size2);

  gsl_linalg_SV_decomp(Az, Vz, Sz, workz);
  Uz = Az;
  //std::cout << "A = U S V^T" << std::endl;
  //std::cout << "U" << std::endl;
  //gsl_matrix_print(Uy, Uy->size1, Uy->size2);
  std::cout << "S3" << std::endl;
  gsl_vector_print(Sz, Az->size2);
  //std::cout << "V" << std::endl;
  //gsl_matrix_print(Vz, Vz->size1, Vz->size2);
  //std::cout << Vz->size1 << ' ' << Vz->size2 << std::endl;
  //std::cout << "work" << std::endl;
  //gsl_vector_print(worky, Ay->size2);

  //Нам нужен Vz, это наше W; W(24x24)

  gsl_matrix *Vx_t, *tmp[count], *Z[count], *Z_avg;
  Vx_t = gsl_matrix_alloc(Vx->size2, Vx->size1);
  gsl_matrix_transpose_memcpy (Vx_t, Vx);
  

  for(i =0; i<count; ++i) {
    Z[i] = gsl_matrix_alloc(3,64);
    tmp[i] = gsl_matrix_alloc(3,64);
    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, Vx_t, T[i], 0.0, tmp[i]);
    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, tmp[i], Vy, 0.0, Z[i]);
  }



  std::cout << "qqq111" <<std::endl; 
  double ss = 0; 
  for(i = 0; i<24; ++i) {
    for(k =0; k<1; ++k) {
      ss = 0.0; 
      for(j =0; j<3; ++j) {	
	ss = ss + pow(gsl_matrix_get(Z[i], j, k), 2); 
	std::cout << gsl_matrix_get(Z[i], j, k) << " ";
      }
      std::cout << sqrt(ss); 
      std::cout << std::endl;
    }
    if(i == 11) 
      std::cout << std::endl;
  }    
  /*
  std::cout << std::endl;
  std::cout << std::endl;
  for(i = 0; i<1; ++i) {
    for(k =0; k<64; ++k) {
      for(j =0; j<3; ++j) {	
	std::cout << patients[i][j][k] << " ";
      }
      std::cout << std::endl;
    }
    if(i == 11) 
      std::cout << std::endl;
  }    

  */

  return 0;
}


  /*
  // check it is ok 
  int yy = Vx->size1; 
  gsl_matrix * t1 = gsl_matrix_alloc(yy, yy);
  gsl_matrix * t2 = gsl_matrix_alloc(yy, yy);

  for(int i = 0; i<yy; i++) 
    for(int j = 0; j<yy; j++){
      gsl_matrix_set(t1, i, j, gsl_matrix_get(Vx, i, j));    
      gsl_matrix_set(t2, i, j, gsl_matrix_get(Vx, j, i));    
    }
  std::cout <<std::endl;
  std::cout <<std::endl;
  gsl_matrix_print(t1, t1->size1, t1->size2);
  std::cout <<std::endl;
  gsl_matrix_print(t2, t2->size1, t2->size2);

  gsl_matrix * t3 = gsl_matrix_alloc(yy, yy);
  gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 
                  1.0, t1, t2,
                  0.0, t3);
 
  std::cout << "V x Vt"<<std::endl;
  gsl_matrix_print(t3, t3->size1, t3->size2);
  */


