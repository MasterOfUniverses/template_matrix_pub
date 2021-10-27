#pragma once
#ifndef MATRIX_T_H
#define MATRIX_T_H
//#include "VectorNd.h"
#include "MyException.h"
template <class T> class VectorNd;
template <class T> class Matrix;
namespace {
template<class T> std::ostream& operator<<(std::ostream& out,const VectorNd<T>& x);
template<class T> std::istream& operator>>(std::istream& in,VectorNd<T>& x);
template<class T> VectorNd<T> operator* (const T& Const,const VectorNd<T>& vec2);
template<class T> bool Is_Equal(const VectorNd<T>& l,const VectorNd<T>& r);
void VectorNd_T_Info(std::ostream& out,std::string separator);
}
namespace{
template<class T> std::ostream& operator<<(std::ostream& out,const Matrix<T>& x);
template<class T> std::istream& operator>>(std::istream& in,Matrix<T>& x);
template<class T> Matrix<T> operator* (const T& Const,const Matrix<T>& matrix2);
template<class T> bool Is_Equal(const Matrix<T>& l,const Matrix<T>& r);
template <class T> bool Cannot_Be_Divided(const Matrix<T>& matrix1);
void Matrix_T_Info(std::ostream& out,std::string separator);
}

template <class T> class VectorNd{
	private:
	int n_cols_;
	T* cols_;
	void PreOrder(){
		Is_Equal( *this, *this);
		return;
	}
	public:
	VectorNd():
	n_cols_(0),
	cols_(nullptr)
	{}
	
	explicit VectorNd(int n_cols):
	n_cols_(n_cols),
	cols_(nullptr)
	{
		if(n_cols_>0){
			cols_= new T[n_cols_];
		}else if(n_cols_<0){
			MyException err(-101,(std::string)"VectorNd err: VectorNd(int i): i<0");
			throw err;
		}
	}
	
	VectorNd(const VectorNd<T>& other):
	n_cols_(other.n_cols_),
	cols_(nullptr)
	{
		if(n_cols_>0){
			cols_= new T[n_cols_];
		}
		for(int i=0;i<n_cols_;i++){
			cols_[i]=other.cols_[i];
		}
	}
	
	template <class D> explicit VectorNd(const VectorNd<D>& other):
	n_cols_(other.size()),
	cols_(nullptr)
	{
		if(n_cols_>0){
			cols_= new T[n_cols_];
		}
		for(int i=0;i<n_cols_;i++){
			cols_[i]=T(other[i]);
		}
	}
	
	~VectorNd() {
		if(cols_){
			delete [] cols_;
		}
	}
	
	
	
	
	
	int size() const{
		return n_cols_;
	}
	
	T& operator[](int i){
		if((0<=i)&&(i<n_cols_)){
			return cols_[i];
		}else{
			MyException err(-103,(std::string)"VectorNd err: VectorNd[index] : invalid index");
			throw err;
		}
	}
	const T& operator[](int i) const{
		if((0<=i)&&(i<n_cols_)){
			return cols_[i];
		}else{
			MyException err(-104,(std::string)"VectorNd err: const VectorNd[index] : invalid index");
			throw err;
		}
	}
	
	bool TestId(int i) const{
		return ((0<=i)&&(i<n_cols_));
	}
	
	
	
	
	const VectorNd<T>& operator=(const VectorNd<T>& vec1){
		delete [] cols_;
		n_cols_=vec1.n_cols_;
		if(n_cols_>=0){
			cols_=new T[n_cols_];
			for(int i=0;i<n_cols_;i++){
				cols_[i]=vec1.cols_[i];
			}
			return vec1;
		}else{
			MyException err(-102,(std::string)"VectorNd err: VectorNd = vec1 : vec1.size()<0");
			throw err;
		}
	}
	
	bool operator==(const VectorNd<T>& vec2)const{
		if((*this).size()!=vec2.size()){
			return false;
		}
		int flag=1;
		for(int i=0;i<(*this).size();i++){
			if(! Is_Equal((*this)[i],vec2[i])){
				flag*=0;
			}
		}
		return (flag==1);
	}
	
	bool operator!=(const VectorNd<T>& vec2)const{
		return !((*this)==vec2);
	}
	
	bool operator==(const T& Const)const{
		return (((*this).size()==1)&&(Is_Equal((*this)[0],Const)));
	}
	
	
	
	VectorNd<T> operator+ (const VectorNd<T>& vec2)const{
		if((*this).size()!=vec2.size()){
			MyException err(-105,(std::string)"VectorNd err: vec1+vec2 : vec1.size()!=vec2.size()");
			throw err;
		}else{
			VectorNd<T> res((*this));
			for(int i=0;i<(*this).size();i++){
				res[i]=res[i]+vec2[i];
			}
			return res;
		}
	}
	
	VectorNd<T> operator- (const VectorNd<T>& vec2)const{
		if((*this).size()!=vec2.size()){
			MyException err(-107,(std::string)"VectorNd err: vec1-vec2 : vec1.size()!=vec2.size()");
			throw err;
		}else{
			VectorNd<T> res((*this));
			for(int i=0;i<(*this).size();i++){
				res[i]=res[i]-vec2[i];
			}
			return res;
		}
	}
	
	VectorNd<T> operator* (const T& Const)const{
		VectorNd<T> res((*this));
		for(int i=0;i<(*this).size();i++){
			res[i] = Const*res[i];
		}
		return res;
	}
	
	VectorNd<T> operator/(const T& Const)const{
		VectorNd<T> res((*this));
		for(int i=0;i<(*this).size();i++){
			res[i] = res[i]/Const;
		}
		return res;
	}
	
	T operator^ (const VectorNd<T>& vec2)const{
		if(((*this).size()!=vec2.size())||((*this).size()<=0)||(vec2.size()<=0)){
			MyException err(-106,(std::string)"VectorNd err: vec1^vec2 : vec1.size()!=vec2.size()");
			throw err;
		}else{
			T res((*this)[0]*vec2[0]);
			for(int i=1;i<(*this).size();i++){
				res=res+(*this)[i]*vec2[i];
			}
			return res;
		}
	}
	
	
	
	std::ostream& Print (std::ostream& out)const{
		//out<<std::endl;
		out<<'(';
		for(int i=0;i<(*this).size();i++){
			out<<(*this)[i];
			if(i<(*this).size()-1){
				out<<';';
			}
		}
		out<<')';
		
		return out;
	}
	
	std::istream& Scan (std::istream& in){
		for(int i=0;i<(*this).size();i++){
			in>>(*this)[i];
		}
		return in;
	}
};

template <class T> class Matrix{
	private:
	friend class VectorNd<T>;
	int n_rows_;
	int n_cols_;
	VectorNd<T>* rows_;
	void PreOrder(){
		Is_Equal( *this, *this);
		return;
	}
	int Rows_Sorting(){
		int result=1;/*
		std::string type=typeid(*this).name();
		//std::cout<<type<<std::endl;
		std::string cm_type_name="MatrixIS";
		
		std::size_t t_flag=type.find(cm_type_name,0);
		//std::cout<<t_flag<<std::endl;
		bool flag=(t_flag<type.size())&&(0<=t_flag);
		*/
		T Null=(*this)[0][0]-(*this)[0][0];
		VectorNd<T> Null_row((*this).cols());
		for(int i=0;i<this->cols();i++){
			Null_row[i]=Null;
		}/*
		if(flag){
			std::cout<<(*this)<<std::endl<<std::endl;
		}*/
		for(int i=0;i<this->cols();i++){
			for(int j=i;j<this->rows();j++){
			
				if(Cannot_Be_Divided((*this)[j][i])){
						for(int k=j;k<this->rows();k++){
							if(!(Is_Equal((*this)[k][i],Null))){
								VectorNd<T> temp(this->cols());
								temp=(*this)[j];
								(*this)[j]=(*this)[k];
								(*this)[k]=temp;
								for(int r=0;r<k-j;r++){
									result*=-1;
								}
								break;
							}
						}
					
				}
				
			}/*
			if(flag){
				std::cout<<(*this)<<std::endl<<std::endl;
			}*/
		}
		
		return result;
	}
	
	
	public:
	
	Matrix():
	n_rows_(0),
	n_cols_(0),
	rows_(nullptr)
	{}
	
	explicit Matrix(int n_rows,int n_cols):
	n_rows_(n_rows),
	n_cols_(n_cols),
	rows_(nullptr)
	{
		if((n_rows_>0)&&(n_cols_>0)){
			//rows_=new VectorNd<T>(n_cols_) [n_rows_];
			rows_=new VectorNd<T> [n_rows_];
			VectorNd<T> temp(n_cols_);
			for(int i=0;i<n_rows_;i++){
				rows_[i]=temp;
			}
		}else if((n_rows_<0)||(n_cols_<0)){
			MyException err(-201,(std::string)"Matrix err: Matrix(int i,j): i<0 or j<0");
			throw err;
		}
	}
	
	explicit Matrix(std::pair<int,int> size):
	n_rows_(size.first),
	n_cols_(size.second),
	rows_(nullptr)
	{
		if((n_rows_>0)&&(n_cols_>0)){
			//rows_=new VectorNd<T>(n_cols_) [n_rows_];
			rows_=new VectorNd<T> [n_rows_];
			VectorNd<T> temp(n_cols_);
			for(int i=0;i<n_rows_;i++){
				rows_[i]=temp;
			}
		}else if((n_rows_<0)||(n_cols_<0)){
			MyException err(-202,(std::string)"Matrix err: Matrix(pair<int,int>): i<0 or j<0");
			throw err;
		}
	}
	
	explicit Matrix(const VectorNd<T>& vec1):
	n_rows_(1),
	n_cols_(vec1.n_cols_),
	rows_(nullptr)
	{
		//rows_=new VectorNd<T>(n_cols_) [n_rows_];	
		rows_=new VectorNd<T> [n_rows_];
		VectorNd<T> temp(n_cols_);
		for(int i=0;i<n_rows_;i++){
			rows_[i]=temp;
		}	
		for(int j=0;j<n_cols_;j++){
			rows_[0][j]=vec1[j];
		}
	}
	
	Matrix(const Matrix<T>& other):
	n_rows_(other.n_rows_),
	n_cols_(other.n_cols_),
	rows_(nullptr)
	{
		//rows_=new VectorNd<T>(n_cols_) [n_rows_];
		rows_=new VectorNd<T> [n_rows_];
		VectorNd<T> temp(n_cols_);
		for(int i=0;i<n_rows_;i++){
			rows_[i]=temp;
		}
		for(int i=0;i<n_rows_;i++){
			for(int j=0;j<n_cols_;j++){
				rows_[i][j]=other.rows_[i][j];
			}
		}
	}
	
	template <class D> explicit Matrix(const Matrix<D>& other):
	n_rows_(other.rows()),
	n_cols_(other.cols()),
	rows_(nullptr)
	{
		rows_=new VectorNd<T> [n_rows_];
		VectorNd<T> temp(n_cols_);
		for(int i=0;i<n_rows_;i++){
			rows_[i]=temp;
		}
		for(int i=0;i<n_rows_;i++){
			for(int j=0;j<n_cols_;j++){
				rows_[i][j]=T(other[i][j]);
			}
		}
	}
	
	~Matrix() {delete [] rows_;}
	
	
	
	VectorNd<T>& operator[](int i){
		return rows_[i];
	}
	const VectorNd<T>& operator[](int i) const{
		return rows_[i];
	}
	/*
	T& operator[](int i,int j);
	const T& operator[](int i,int j) const;
	*/
	std::pair<int,int> size() const{
		return {n_rows_,n_cols_};
	}
	int rows() const{
		return n_rows_;
	}
	int cols() const{
		return n_cols_;
	}
	bool TestId(int i,int j) const{
		return ((0<=i && i<n_cols_)&&(0<=j && j<n_rows_));
	}
	
	
	
	const Matrix<T>& operator=(const Matrix<T>& matrix1){
		delete [] rows_;
		n_rows_=matrix1.n_rows_;
		n_cols_=matrix1.n_cols_;
		if((n_rows_>=0)&&(n_cols_>=0)){
			//rows_=new VectorNd<T>(n_cols_) [n_rows_];
			rows_=new VectorNd<T> [n_rows_];
			VectorNd<T> temp(n_cols_);
			for(int i=0;i<n_rows_;i++){
				rows_[i]=temp;
			}
			for(int i=0;i<n_rows_;i++){
				for(int j=0;j<n_cols_;j++){
					rows_[i][j]=matrix1.rows_[i][j];
				}
			}
			return matrix1;
		}else{
			MyException err(-203,(std::string)"Matrix err: Matrix=Matrix: i<0 or j<0");
			throw err;
		}
	}
	
	const Matrix<T> Transponed()const{
		Matrix<T> result(n_cols_,n_rows_);
		for(int i=0;i<n_cols_;i++){
			for(int j=0;j<n_rows_;j++){
				result[i][j]=rows_[j][i];
			}
		}
		return result;
	}
	
	Matrix<T> Minor(int row,int col) const{
		if(n_rows_==n_cols_){
			if(n_rows_>1){
				Matrix<T> result(n_rows_-1,n_cols_-1);
				for(int i=0;i<n_rows_-1;i++){
					for(int j=0;j<n_cols_-1;j++){
						int ind_row=i,ind_col=j;
						if(i>=row){
							ind_row++;
						}
						if(j>=col){
							ind_col++;
						}
						result[i][j]=(*this)[ind_row][ind_col];
					}
				}
				return result;
			}else{
				MyException err(-207,(std::string)"Matrix err: Matrix.Minor(int,int) : matrix is too small (1*1)");
				throw err;
			}
		}
		else{
			MyException err(-206,(std::string)"Matrix err: Matrix.Minor(int,int) : Matrix isn't squared ");
			throw err;
		}
	}
	
	T Det()const{
		if(n_rows_==n_cols_){
			if(n_rows_==0){
				MyException err(-209,(std::string)"Matrix err: Matrix.Minor(int,int) : matrix is empty (0*0)");
				throw err;
			}else if(n_rows_==1){
				return (*this)[0][0];
			}else if(n_rows_==2){
				return (*this)[0][0]*(*this)[1][1] - (*this)[1][0]*(*this)[0][1];
			}else{
				T result;
				result=(*this)[0][0]*(this->Minor(0,0).Det());
				int flag=-1;
				for(int i=1;i<n_rows_;i++){
					result=result+flag*(*this)[0][i]*(this->Minor(0,i).Det());
					flag*=-1;
				}
				return result;
			}
		}else{
			MyException err(-208,(std::string)"Matrix err: Matrix.Det : Matrix isn't squared ");
			throw err;
		}
	}
	
	Matrix<T> Const_Rows_Sorting(int& result)const{
		Matrix<T> Sorted_Matrix((*this));
		result*=Sorted_Matrix.Rows_Sorting();
		return Sorted_Matrix;
	}	
	Matrix<T> Const_Rows_Sorting()const{
		Matrix<T> Sorted_Matrix((*this));
		Sorted_Matrix.Rows_Sorting();
		return Sorted_Matrix;
	}
	
	Matrix<T> Gauss_Down(int& ratio) const{
		Matrix<T> result(*this);
		T Null=(*this)[0][0]-(*this)[0][0];
		ratio*=result.Rows_Sorting();
		for(int i=0;i<result.rows();i++){
			int j=i;
			while((j<result.cols())&&(Is_Equal(result[i][j],Null))){j++;}
			if(j<result.cols()){
				if(! Is_Equal(result[i][j],Null)){
					for(int k=i+1;k<result.rows();k++){
						result[k]=result[k] - result[i]*(result[k][j]/result[i][j]);
					}
				}
			}
			ratio*=result.Rows_Sorting();
			//std::cout<<result<<std::endl<<std::endl;
		}
		return result;
	}
	Matrix<T> Gauss_Down() const{
		Matrix<T> result(*this);
		T Null=(*this)[0][0]-(*this)[0][0];
		result.Rows_Sorting();
		for(int i=0;i<result.rows();i++){
			int j=i;
			while((j<result.cols())&&(Is_Equal(result[i][j],Null))){j++;}
			if(j<result.cols()){
				if(!Is_Equal(result[i][j],Null)){
					for(int k=i+1;k<result.rows();k++){
						result[k]=result[k] - result[i]*(result[k][j]/result[i][j]);
					}
				}
			}
			result.Rows_Sorting();
		}
		return result;
	}
	
	Matrix<T> Gauss(int& ratio) const{
		Matrix<T> result(this->Gauss_Down(ratio));
		T Null=(*this)[0][0]-(*this)[0][0];
		for(int i=result.rows()-1;i>-1;i--){
			for(int j=0;j<result.cols();j++){
				if(!Is_Equal(result[i][j],Null)){
					result[i]=result[i]/result[i][j];
					for(int k=i-1;k>-1;k--){
						result[k]=result[k]-result[i]*(result[k][j]/result[i][j]);
					}
					ratio*=result.Rows_Sorting();
					break;
				}
			}
		}
		ratio*=result.Rows_Sorting();	
		return result;
	}
	Matrix<T> Gauss() const{
		Matrix<T> result(this->Gauss_Down());
		T Null=(*this)[0][0]-(*this)[0][0];
		for(int i=result.rows()-1;i>-1;i--){
			for(int j=0;j<result.cols();j++){
				if(!Is_Equal(result[i][j],Null)){
					result[i]=result[i]/result[i][j];
					for(int k=i-1;k>-1;k--){
						result[k]=result[k]-result[i]*(result[k][j]/result[i][j]);
					}
					result.Rows_Sorting();
					break;
				}
			}
		}
		result.Rows_Sorting();
		return result;
	}
	
	//Det?=det ?!!!
	T det()const{
		if(this->Is_Squared()){
			int ratio=1;
			Matrix<T> temp(this->Gauss_Down(ratio));
			T det=temp[0][0];
			for(int i=1;i<this->rows();i++){
				det=det*temp[i][i];
			}
			if(ratio==-1){
				T new_det;
				new_det=det-det-det;
				return new_det;
			}
			return det;
		}else{
			MyException err(-212,(std::string)"Matrix err: Matrix.det() : Matrix isn't squared ");
			throw err;
		}
	}
	bool Is_Degenerate()const{
		if(this->cols()==this->rows()){
			T det=this->det();
			if(Is_Equal(det-det,det)){
				return false;
			}else{
				return true;
			}
		}else{
			return false;
		}
	}
	bool Is_Squared()const{
		return this->cols()==this->rows();
	}
	
	Matrix<T> RUnion(const Matrix<T>& matrix2)const{
		if(this->rows()==matrix2.rows()){
			Matrix<T> result(matrix2.rows(),(this->cols()+matrix2.cols()));
			for(int i=0;i<matrix2.rows();i++){
				for(int j=0;j<this->cols();j++){
					result[i][j]=(*this)[i][j];
				}
				for(int j=0;j<matrix2.cols();j++){
					result[i][j+this->cols()]=matrix2[i][j];
				}
			}
			return result;
		}else{
			MyException err(-211,(std::string)"Matrix err: Matrix.RUnion(Matrix) : differente number of rows");
			throw err;
		}
	}
	
	Matrix<T> Inversed()const{
		if(this->Is_Squared()){
			T Null=(*this)[0][0]-(*this)[0][0];
			T One=Null;
			for(int i=0;i<this->rows();i++){
				for(int j=0;j<this->cols();j++){
					if(Is_Equal((*this)[i][j],Null)){
						
					}else{
						One = (*this)[i][j] / (*this)[i][j];
					}
				}
			}
			if(Is_Equal(One,Null)){
				MyException err(-214,(std::string)"Matrix err: Matrix.Inversed() : All fields are Null ");
				throw err;
			}
			Matrix<T> neutral(this->size());
			for(int i=0;i<this->rows();i++){
				for(int j=0;j<this->rows();j++){
					if(i!=j){
						neutral[i][j]=Null;
					}else{
						neutral[i][j]=One;
					}
				}
			}
			
			Matrix<T> Union=this->RUnion(neutral);
			
			Union=Union.Gauss();
			Matrix<T> left(neutral.rows(),neutral.rows()),right(neutral.rows(),neutral.rows());
			for(int i=0;i<Union.rows();i++){
				for(int j=0;j<neutral.cols();j++){
					left[i][j]=Union[i][j];
					right[i][j]=Union[i][j+neutral.cols()];
				}
			}
			if(left==neutral){
				return right;
			}else{
				//std::cout<<left<<std::endl;
				MyException err(-215,(std::string)"Matrix err: Matrix.Inversed() : Matrix is degenerate");
				throw err;
			}
		}else{
			MyException err(-213,(std::string)"Matrix err: Matrix.Inversed() : Matrix isn't squared ");
			throw err;
		}
	}
	
	bool operator==(const Matrix<T>& matrix2)const{
		if(this->size()!=matrix2.size()){
			return false;
		}
		int flag=1;
		for(int i=0;i<this->size().first;i++){
			if(! Is_Equal((*this)[i],matrix2[i])){
				flag*=0;
			}
		}
		return (flag==1);
	}
	
	bool operator!=(const Matrix<T>& matrix2)const{
		return !((*this)==matrix2);
	}
	
	bool operator==(const T& Const)const{
		return ((this->size==(1,1))&&(Is_Equal(Const,(*this)[0][0])));
	}
	
	bool operator==(const VectorNd<T>& vec1)const{
		if(this->size==(1,vec1.size())){
			int flag=1;
			for(int i=0;i<vec1.size();i++){
				if(! Is_Equal((*this)[0][i],vec1[i])){
					flag*=0;
				}
			}
			return (flag==1);
		}/*else if(matrix2.size==(vec1.size(),1)){
			int flag=1;
			for(int i=0;i<vec1.size();i++){
				if(matrix2[i][0]!=vec1[i]){
					flag*=0;
				}
			}
			return (flag==1);
		}*/
		return false;
	}
	
	
	
	Matrix<T> operator+ (const Matrix<T>& matrix2)const{
		if(this->size()==matrix2.size()){
			Matrix<T> result((*this));
			for(int i=0;i<this->size().first;i++){
				result[i] = result[i] + matrix2[i];
			}
			return result;
		}else{
			MyException err(-204,(std::string)"Matrix err: Matrix+Matrix: diffrent sizes");
			throw err;
		}
	}
	
	Matrix<T> operator- (const Matrix<T>& matrix2)const{
		if(this->size()==matrix2.size()){
			Matrix<T> result((*this));
			for(int i=0;i<this->size().first;i++){
				result[i] = result[i] - matrix2[i];
			}
			return result;
		}else{
			MyException err(-210,(std::string)"Matrix err: Matrix-Matrix: diffrent sizes");
			throw err;
		}
	}
	
	Matrix<T> operator* (const T& Const)const{
		Matrix<T> result((*this));
		for(int i=0;i<this->size().first;i++){
			result[i]=result[i]*Const;
		}
		return result;
	}
	
	Matrix<T> operator/ (const T& Const)const{
		Matrix<T> result((*this));
		for(int i=0;i<this->size().first;i++){
			result[i]=result[i]/Const;
		}
		return result;
	}
	
	Matrix<T> operator* (const Matrix<T>& matrix2)const{
		if(this->size().second==matrix2.size().first){
			Matrix<T> result(this->size().first,matrix2.size().second);
			for(int i=0;i<this->size().first;i++){
				for(int j=0;j<matrix2.size().second;j++){
					result[i][j]=(*this)[i][0]*matrix2[0][j];
					for(int k=1;k<this->size().second;k++){
						result[i][j]=result[i][j]+(*this)[i][k]*matrix2[k][j];
					}
				}
			}
			return result;
		}else{
			MyException err(-205,(std::string)"Matrix err: Matrix*Matrix: diffrent sizes");
			throw err;
		}
	}
	
	Matrix<T> operator/ (const Matrix<T>& matrix2)const{
		return (*this) * matrix2.Inversed();
	}
	
	
	
	std::ostream& Print (std::ostream& out)const{
		//out<<std::endl;
		out<<'(';
		for(int i=0;i<this->rows();i++){
			out<<(*this)[i];
			if(i<this->rows()-1){
				out<<';'<<std::endl;
			}
		}
		out<<')';
		
		return out;
	}
	
	std::istream& Scan (std::istream& in){
		for(int i=0;i<this->rows();i++){
			in>>(*this)[i];
		}
		return in;
	}
	bool Is_det_Null()const{
		T det,null;
		det=this->det();
		null=det-det;
		return Is_Equal(det,null);
	}
};

namespace {
template<class T> std::ostream& operator<<(std::ostream& out,const VectorNd<T>& x){
	return x.Print(out);
}
template<class T> std::istream& operator>>(std::istream& in,VectorNd<T>& x){
	return x.Scan(in);
}
template<class T> VectorNd<T> operator* (const T& Const,const VectorNd<T>& vec2){
	return vec2*Const;
}
template<class T> bool Is_Equal(const VectorNd<T>& l,const VectorNd<T>& r){
	return l==r;
}

void VectorNd_T_Info(std::ostream& out,std::string separator = "\n"){
	MyException_Info(out,separator);
	out<<"--- VectorNd.h (Info) ---"<<separator;
	out<<"Was created and wroten by Pavel Chekalov in September 2021"<<separator;
	out<<"All rights reserved"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Targets ---"<<separator;
	out<<"Template library for algepra"<<separator;
	out<<"--- Included libraries ---"<<separator;
	out<<" MyException.h "<<separator;
	out<<"--- Requests ---"<<separator;
	out<<"T* new[](int) ; T* new delete[] ; operator<< (std::ostream&,const T&)"<<separator;
	out<<"operator>> (std::istream&,const T&) ; operator= (const T&)"<<separator;
	out<<"T operator+ (const T&,const T&) ; T operator- (const T&,const T&)"<<separator;
	out<<"T operator* (const T&,const T&) ; T operator/ (const T&,const T&)"<<separator;
	out<<"--- Spesial Requests ---"<<separator;
	out<<"bool Is_Equal(const T&,const T&)"<<separator;
	out<<"--- Warning ---"<<separator<<"This function must be pre-declarated BEFORE including this library"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Types ---"<<separator;
	out<<"VectorNd <class T> {int size, T* data}"<<separator;
	out<<"--- Constructors ---"<<separator;
	out<<"();explicit(int);(const VectorNd<T>&)"<<separator<<"operator=(VectorNd<T>,const VectorNd<T>&)"<<separator;
	out<<"--- Types changing ---"<<separator;
	out<<"<class D> VectorNd<D>(const VectorNd<T>&)"<<separator;
	out<<"--- Warning ---"<<separator;
	out<<"Types changing from VectorNd<T> to VectorNd<D> needs types changing from T to D and explicit declaration."<<separator;
	out<<"--- Destructors ---"<<separator;
	out<<"delete [] data"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Memory access ---"<<separator;
	out<<"T& operator[](int) ; const T& operator[](int)const"<<separator;
	out<<"int VectorNd.size() ; bool VectorNd.TestId(int)"<<separator;
	out<<"--- Comparison functions ---"<<separator;
	out<<"bool operator== (const VectorNd<T>&,const VectorNd<T>&) ; bool operator!= (const VectorNd<T>&,const VectorNd<T>&)"<<separator;
	out<<"bool operator== (const VectorNd<T>&,const T&) ; bool Is_Equal(const VectorNd<T>&,const VectorNd<T>&)"<<separator;
	out<<"--- Math functions ---"<<separator;
	out<<"VectorNd<T> operator+ (const VectorNd<T>&,const VectorNd<T>&)"<<separator;
	out<<"VectorNd<T> operator- (const VectorNd<T>&,const VectorNd<T>&)"<<separator;
	out<<"VectorNd<T> operator* (const VectorNd<T>&,const T&)"<<separator;
	out<<"VectorNd<T> operator* (const T&,const VectorNd<T>&) ; VectorNd<T> operator/ (const VectorNd<T>&,const T&)"<<separator;
	out<<"T operator^ (const VectorNd<T>&,const VectorNd<T>&) --- scalar product"<<separator;
	out<<"--- Print functions ---"<<separator;
	out<<"VectorNd.Print(std::ostream&)"<<separator<<"std::ostream& operator<< (std::ostream&, const VectorNd<T>&)"<<separator;
	out<<"--- Scan functions ---"<<separator;
	out<<"VectorNd.Scan(std::istream&)"<<separator<<"std::istream& operator>> (std::istream&, const VectorNd<T>&)"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	return;
}

}


namespace{
template<class T> std::ostream& operator<<(std::ostream& out,const Matrix<T>& x){
	return x.Print(out);
}
template<class T> std::istream& operator>>(std::istream& in,Matrix<T>& x){
	return x.Scan(in);
}
template<class T> Matrix<T> operator* (const T& Const,const Matrix<T>& matrix2){
	return matrix2*Const;
}
template<class T> bool Is_Equal(const Matrix<T>& l,const Matrix<T>& r){
	return l==r;
}
template <class T> bool Cannot_Be_Divided(const Matrix<T>& matrix1){
	return matrix1.Is_det_Null();
}
void Matrix_T_Info(std::ostream& out,std::string separator = "\n"){
	VectorNd_T_Info(out,separator);
	out<<"--- Matrix.h (Info) ---"<<separator;
	out<<"Was created and wroten by Pavel Chekalov in September 2021"<<separator;
	out<<"All rights reserved"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Targets ---"<<separator;
	out<<"Template library for algepra"<<separator;
	out<<"--- Included libraries ---"<<separator;
	out<<" VectorNd.h (in file \" matrix.h \")"<<separator;
	out<<"--- Requests ---"<<separator;
	out<<"T* new[](int) ; T* new delete[] ; operator<< (std::ostream&,const T&)"<<separator;
	out<<"operator>> (std::istream&,const T&) ; operator= (const T&)"<<separator;
	out<<"T operator+ (const T&,const T&) ; T operator- (const T&,const T&)"<<separator;
	out<<"T operator* (const T&,const T&) ; T operator/ (const T&,const T&)"<<separator;
	out<<"--- Spesial Requests ---"<<separator;
	out<<"bool Is_Equal(const T&,const T&), bool Cannot_Be_Divided(const T&)"<<separator;
	out<<"--- Warning ---"<<separator<<"This functions must be pre-declarated BEFORE including this library"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Types ---"<<separator;
	out<<"Matrix <class T> {int rows,int cols, VectorNd<T>* rows}"<<separator;
	out<<"--- Constructors ---"<<separator;
	out<<"();explicit (int,int);explicit (std::pair<int,int>);explicit (const VectorNd<T>&);(const Matrix<T>&)"<<separator;
	out<<"operator=(Matrix<T>,const Matrix<T>&)"<<separator;
	out<<"--- Types changing ---"<<separator;
	out<<"<class D> Matrix<D>(const Matrix<T>&)"<<separator;
	out<<"--- Warning ---"<<separator;
	out<<"Types changing from Matrix<T> to Matrix<D> needs types changing from T to D and explicit declaration."<<separator;
	out<<"--- Destructors ---"<<separator;
	out<<"delete [] rows"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Memory access ---"<<separator;
	out<<"VectorNd<T>& operator[](int) ; const VectorNd<T>& operator[](int)const"<<separator;
	out<<"std::pair<int,int> Matrix.size() ; int Matrix.cols(); int Matrix.rows() ; bool Matrix.TestId(int,int)"<<separator;
	out<<"--- Comparison functions ---"<<separator<<"bool operator== (const Matrix<T>&,const Matrix<T>&)"<<separator;
	out<<"bool operator!= (const Matrix<T>&,const Matrix<T>&)"<<separator;
	out<<"bool operator== (const Matrix<T>&,const VectorNd<T>&) ; bool operator== (const Matrix<T>&,const T&)"<<separator;
	out<<"bool Is_Equal(const Matrix<T>&,const Matrix<T>&)"<<separator;
	out<<"--- Math functions ---"<<separator;
	out<<"Matrix<T> operator+ (const Matrix<T>&,const Matrix<T>&) ; Matrix<T> operator- (const Matrix<T>&,const Matrix<T>&)"<<separator;
	out<<"Matrix<T> operator* (const Matrix<T>&,const T&) ; Matrix<T> operator* (const T&,const Matrix<T>&)"<<separator;
	out<<"Matrix<T> operator/ (const Matrix<T>&,const T&)"<<separator;
	out<<"Matrix<T> operator* (const Matrix<T>&,const Matrix<T>&) ; Matrix<T> operator/ (const Matrix<T>&,const Matrix<T>&)"<<separator;
	out<<"--- Math methods ---"<<separator;
	out<<"bool Matrix.Is_Degenerate() ; bool Matrix.Is_Squared() ; Matrix<T> Matrix.RUnion(const Matrix<T>&) ( A.(B) --> (A|B) )"<<separator;
	out<<"Matrix<T> Matrix.Transponed() ; Matrix<T> Matrix.Minor(int row,int col) ; T Matrix.Det() ; T Matrix.det() (by Gauss method)"<<separator;
	out<<"Matrix<T> Matrix.Const_Rows_Sorting([int&]) ; Matrix<T> Matrix.Gauss_Down([int&]) ; Matrix<T> Matrix.Gauss([int&])"<<separator;
	out<<" [int&] - optonal argument for counting rows rotation in rows sorting "<<separator;
	out<<"Matrix<T> Matrix.Inversed()"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Print functions ---"<<separator;
	out<<"Matrix.Print(std::ostream&)"<<separator<<"std::ostream& operator<< (std::ostream&, const Matrix<T>&)"<<separator;
	out<<"--- Scan functions ---"<<separator;
	out<<"Matrix.Scan(std::istream&)"<<separator<<"std::istream& operator>> (std::istream&, const Matrix<T>&)"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	return;
}

}
#endif
