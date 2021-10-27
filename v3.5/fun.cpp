#ifndef ALL_H
#define ALL_H
#include "all.h"
#include <cmath>
#endif
template <class T> Matrix<Matrix<T>> Complicated_Matrix (const Matrix<T>& matrix1,int new_size);
void fun(){
	try{
		ofstream in;
		in.open("input.txt");
		ofstream out;
		out.open("output.txt");
		ofstream doc;
		doc.open("Matrix_Info.txt");
		Matrix_T_Info(doc,"\n");
		int size=4*16;
		//cout<<"Enter size:";
		//cin>>size;
		//size=10*10;
		Matrix<long double> matrix1(size,size);
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				matrix1[i][j]=fabs(i-j);
			}
		}
		in<<matrix1;
		cout<<Complicated_Matrix(Complicated_Matrix(matrix1,2).det(),4).det().det()<<endl;
		
		cout<<matrix1.det()<<endl;
	}catch(MyException x){
		ofstream err;
		err.open("errors.txt");
		err<<x;
	}
	
}

bool Is_Equal(const long double& l,const long double& r){
	return (fabs(l-r)<1e-15);
}

bool Is_Equal(const int& l,const int& r){
	return l==r;
}
bool Cannot_Be_Divided(const int& x){
	int null=0;
	return Is_Equal(x,null);
}
bool Cannot_Be_Divided(const long double& x){
	double null=0.0;
	return Is_Equal(x,null);
}

//You can replace only template argument
template <class T>
Matrix<Matrix<T>> Complicated_Matrix (const Matrix<T>& matrix1,int new_size){
	if(matrix1.Is_Squared()){
		if(matrix1.rows()%new_size == 0){
			VectorNd<Matrix<T>> vector_temp(new_size);
			int n=int(matrix1.rows()/new_size);
			if(1==1){
				Matrix<T> matrix_temp(n,n);
				for(int i=0;i<new_size;i++){
					vector_temp[i]=matrix_temp;
				}
			}
			Matrix<Matrix<T>> result(new_size,new_size);
			for(int i=0;i<new_size;i++){
				for(int j=0;j<n;j++){
					for(int k=0;k<new_size;k++){
						for(int l=0;l<n;l++){
							vector_temp[k][j][l]=matrix1[i*n+j][k*n+l];
						}
					}
				}
				result[i]=vector_temp;
			}
			return result;
		}else{
			cout<<"Given n doesn't divide matrix size"<<endl;
			Matrix<Matrix<T>> result(1,1);
			result[0][0]=matrix1;
			return result;
		}
	}else{
		cout<<"Given matrix isn't squared"<<endl;
		Matrix<Matrix<T>> result(1,1);
		result[0][0]=matrix1;
		return result;
		
	}
}