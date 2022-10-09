#include <bits/stdc++.h>
using namespace std;
int n=15;
double wt[6]={0,0,0,0,0,0};
double co[6]={0,0,0,0,0,0};
void gradient(int iterate,double learn,double *wt,double *co,double x[15],double m[15],double c[15],double cocc[15],double cuno[15],double xno[15],double peice[15]){
	for(int it=0;it<iterate;it++){
		double dw[6]={0,0,0,0,0,0};
		double db[6]={0,0,0,0,0,0};
		for(int i=0;i<15;i++){
			double z[6];
			double y[6]={m[i],c[i],cocc[i],cuno[i],xno[i],peice[i]};
			for(int j=0;j<6;j++){
				z[j]= (*(wt+j))*x[i] + *(co+j);
				z[j] = 2*(z[j]-y[j]);
				db[j] = db[j] + z[j]/15;
				z[j]= z[j]*x[i];
				dw[j] = dw[j] + z[j]/15;
			}

		}

		for(int j=0;j<6;j++){
			*(wt+j) = *(wt+j) - learn*dw[j];
			*(co+j) = *(co+j) - learn*db[j]; 
		}

	}

}

int main(){
	freopen("data.txt", "r", stdin); // redirects standard input
	double state[15];
	double train_mobility[15];
	double train_corners[15];
	double train_c_occupied[15];
	double train_x_unoccupied[15];
	double train_c_uno[15];
	double train_no_pieces[15];
	int iterate;
	double learn;

	for(int i=0;i<n;i++){
        cin>>state[i];
        cin>>train_mobility[i];
        cin>>train_corners[i];
        cin>>train_c_occupied[i];
        cin>>train_c_uno[i];
        cin>>train_x_unoccupied[i];
        cin>>train_no_pieces[i];
	}

	cin>>iterate;
	cin>>learn;
	cout<<learn<<endl;
	gradient(iterate,learn,wt,co,state,train_mobility,train_corners,train_c_occupied,train_c_uno,train_x_unoccupied,train_no_pieces);
	for(int i=0;i<6;i++){
	//	cout<< wt[i]<<"  "<<co[i]<<endl;
	}
	double error[6]={0,0,0,0,0,0};
	for(int i=0;i<15;i++){
		double y[6]={train_mobility[i],train_corners[i],train_c_occupied[i],train_c_uno[i],train_x_unoccupied[i],train_no_pieces[i]};
		double z[6];
		for(int j=0;j<6;j++){
			z[j]=wt[j]*state[i] + co[j];
			error[j] =+ ((z[j]-y[j])*(z[j]-y[j]))/15;
			//cout<<"("<<z[j]<<" "<<y[j]<<")  ";
		}
		//cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<6;i++){
		cout<<error[i]<<"  ";
	}
	cout<<endl;
	return 0;

}