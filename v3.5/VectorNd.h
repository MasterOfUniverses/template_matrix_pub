#ifndef VECTORND_T_H
#define VECTORND_T_H

#include "MyException.h"
template <class T> class VectorNd;
namespace {
template<class T> std::ostream& operator<<(std::ostream& out,const VectorNd<T>& x);
template<class T> std::istream& operator>>(std::istream& in,VectorNd<T>& x);
template<class T> VectorNd<T> operator* (const T& Const,const VectorNd<T>& vec2);
template<class T> bool Is_Equal(const VectorNd<T>& l,const VectorNd<T>& r);
void VectorNd_T_Info(std::ostream& out,std::string separator);
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
#endif
