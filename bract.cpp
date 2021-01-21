
#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<cfloat>


using namespace std;

void base_poly(int arr[], int m, int n,int k){
	for(int i=k-1;i>=0;i--){
		break;
	}

}

//////////////////
//check if PRIME/
////////////////
bool isPrime(int n){
	if (n <= 1)  return false; 
    if (n <= 3)  return true; 
  
    // This is checked so that we can skip  
    // middle five numbers in below loop 
    if (n%2 == 0 || n%3 == 0) return false; 
  
    for (int i=5; i*i<=n; i=i+6) 
        if (n%i == 0 || n%(i+2) == 0) 
           return false; 
  
    return true; 
}

/////////////////////////////
//polynomia function ::f(x)
////////////////////////////
bool poly_func(vector<int>& poly, int r,int p){
	int temp=0;
	/*for(int it =0;it<poly.size();it++){
		temp+=poly[it] * (pow(r,it));
	}*/
	temp+=8; //poly[0] * (pow(r,0));
	temp+=poly[1] * (pow(r,1));
	temp+=poly[2] * (pow(r,2));
	temp+=poly[3] * (pow(r,3));
	//cout<<temp<<"--"<<r<<" "<<p<<"\n";
	temp = temp%p;
	if(temp<0){temp=p+temp;}
	
	if(temp==0){return true;}
	else{return false;}
	
}
//////////////////////////////////////////
///////////  Poly F(x)
///////////////////////////////////////
int poly_f(vector<int>& poly, int a, int b){
	int temp =8; 
	//temp+=8; //poly[0] * (pow(r,0));
	temp+=poly[1] * (pow(-a/b,1));
    temp+=poly[2] * (pow(-a/b,2));
    temp+=poly[3] * (pow(-a/b,3));

	return temp;
}




////////////////////
//////  R A Q Base 
////////////////////

void base_fill(int m,int n,vector<int>& poly,vector<int>& Rbase, multimap<int,int>& Abase,multimap<int, int>& Qbase){
	//list of primes
	vector<int> prime;
	for(int i=2;i<110;i++){
		if(isPrime(i)){
			prime.push_back(i);
		}
	}

	int sz = prime.size();
	//cout<<sz<<"--\n";
	Rbase.assign(prime.begin(),prime.begin()+10);


	//filling A_base
	vector<int>::iterator ait = prime.begin();
	for(;*ait<90;ait++){
		for(int j=0;j<90;j++){
			int p = *ait;
			//if(j==0){cout<<p<<" ";}
			if(poly_func(poly,j,p)){
				//cout<<".\n";
				Abase.insert({p,j});
			}
		}
	}


	//filling Q_base
	
	for(;ait!=prime.end();ait++){
		for(int j=0; j<=prime.back();j++){
			int q = *ait;
			if(poly_func(poly,j,q)){
				Qbase.insert({q,j});
			}
		}
	}
	
}


///////////////////////
//// R Smooth
//////////////////////
void R_smooth(int m,vector<int>& Rbase, multimap<int,int>& siv){
	for(int a=-400;a<=400;a++){
		for(int b=1;b<=41;b++){
			for(int it=0;it<Rbase.size();it++){
				int mod=Rbase[it];
				int lhs=a%mod;
				int rhs=(-1*b*m)%mod;
				if(lhs<0){lhs=mod+lhs;}
				if(rhs<0){rhs=mod+rhs;}
				if(lhs==rhs){
					//cout<<a<<"-"<<b<<">>>>"<<mod<<"\n";
					siv.insert({a,b});
					break;
				}
			}
		}
	}
}


////////////////////
//// A Smooth
///////////////////

void A_smooth(multimap<int,int>& Abase,multimap<int,int>& siv,multimap<int,int>& siv2,vector<int>& poly){
	multimap<int,int>::iterator it=siv.begin();
	for(;it!=siv.end();++it){
		vector<int> mult_p;
		int a=(*it).first;
		int b=(*it).second;
		if(b==0){siv.erase(it);}
		else{
		//cout<<"TEsting:"<<a<<" "<<b<<"\n";
		multimap<int,int>::iterator itr=Abase.begin();
		for(;itr!=Abase.end();itr++){
			//int r=(*itr).first;
			int p=(*itr).first;
			int lhs=a%p;
			int rhs=(-1*b*((*itr).second))%p;
			if(lhs<0){lhs=lhs+p;}
			if(rhs<0){rhs=rhs+p;}
			if(lhs==rhs){mult_p.push_back(p);siv2.insert({a,b});break;}

		}
		/*long int mul=1;
		/*if(b==11){
			for(auto x:mult_p){
				cout<<x<<" ";
				
			}
			cout<<"\n";
		}//
		
		for(int i=0;i<mult_p.size();i++){mul *= mult_p[i];}	
		
		long int mul1 = pow(-1*b,3);
		mul1*=poly_f(poly,a,b);
		
		//cout<<abs(mul-mul1)<<"\n";
		if(abs(mul-mul1)< 5 ){
			cout<<">>>>"<<mul1<<">>"<<poly_f(poly,a,b)<<"\n";
			siv2.insert({a,b});
		}
		}
		//mult_p.clear();*/

		}

	}
	

}






int main(){
	int m =31;
	int n = 45113;
	
	vector<int> poly{8,29,15,1};
	//cout<<"test:";
	vector<int> R_base;
	multimap<int,int> A_base;
	multimap<int,int> Q_base;
	
	base_fill(m,n,poly,R_base,A_base,Q_base);
	
	/////////////////
	///check in bases
	/////////////////
	/*for(auto x: A_base){
		cout<<x.second<<" "<<x.first<<"\n";
	}
	cout<<"-------------------------------\n";
	for(auto x: Q_base){
		cout<<x.second<<" "<<x.first<<"\n";
	}*/
	
	
	
	multimap<int,int> sieve;
	multimap<int,int> sieve2;
	R_smooth(m,R_base,sieve);
	//for(auto x:sieve){cout<<x.first<<"-"<<x.second<<"\n";}
	
	A_smooth(A_base,sieve,sieve2,poly);
    for(auto x:sieve2){cout<<x.first<<"-"<<x.second<<"\n";}
	cout<<"siv1 -->"<<sieve.size()<<"\n";
	cout<<"siv2-->"<<sieve2.size();
	
	
	
return 0;
}
