#include <iostream>
using namespace std;

void introduction()
{
    cout<<"********Instructions for input********"<<endl<<endl;
    cout<<"For a problem of type"<<endl<<"-------------------------"<<endl<<"Max : Z = C1X1+C2X2+C3X3...........+CrXr"<<endl<<"where C1,C2,...,Cr are coefficients of variables in objective function"<<endl;
    cout<<"***Constraints***"<<endl;
    cout<<"a[1][1]x1+a[1][2]x2+.....+a[1][n]=b[1]"<<endl;
    cout<<"a[2][1]x1+a[2][2]x2+.....+a[2][n]=b[2]"<<endl;
    cout<<"|  |   |   |   |   |   |   |   |   |  "<<endl;
    cout<<"|  |   |   |   |   |   |   |   |   |  "<<endl;
    cout<<"a[m][1]x1+a[m][2]x2+.....+a[m][n]=b[n]"<<endl<<endl;

    cout<<"Matrix A is a mxn matrix"<<endl;
    cout<<"Matrix B is a nx1 column matrix"<<endl;
    cout<<"------------------------------------------------------------------------------------------------------"<<endl<<endl;
}

int main()
{
    introduction();
    int m,n,i,j,check,column,row,proceed,table;
    float minimum,pivot,sum;
    int iteration=1;
    while(iteration==1)
    {
        check=1;
        sum=0;
        table=1;
    cout<<"Input the number of constraints ";
    cin>> m;
    cout<<"Input the number of variables ";
    cin>> n;
    float C[n],B[m];
    float A[m][n];
    float X[n];
    int z[n];
    for(i=0;i<n;i++)
    {
        X[i]=-1;
    }
    cout<<"Input values of coefficients of variable in objective function: ";
    for(i=0;i<n;i++)
    {
        cin>>C[i];
    }
    cout<<"Input values of A matrix row wise "<<endl;
    for(i=0;i<m;i++)
    {
        cout<<" enter values of row "<<i+1<<"   ";
        for(j=0;j<n;j++)
        {
            cin>>A[i][j];
        }
    }
    cout<<"enter B column value ";
    for(i=0;i<m;i++)
    {
        cin>>B[i];
    }
    float T[m+1][n+1];
    for(i=0;i<m;i++)
    {
        for(j=0;j<n+1;j++)
        {
            if(j!=n)
            {
              T[i][j]=A[i][j];
            }
            else
            T[i][j]=B[i];
        }
    }
     for(j=0;j<n;j++)
    {
        T[m][j]=(-1)*(C[j]);
    }
    T[m][n]=0;
    cout<<"simplex table "<<table<<" is "<<endl;
    table=table+1;
    for(i=0;i<m+1;i++)
    {
        for(j=0;j<n+1;j++)
        {
            cout<<T[i][j]<<"     " ;
        }
        cout<<endl;
    }
    while(check==1)
    {
    for(j=0;j<n;j++)
    {
        if(T[m][j]<0)
        {
            check=1;
            break;
        }
        else
        check=0;
    }
    if(check==1)
    {
        minimum=T[m][0];
        column=0;
        for(j=1;j<n;j++)
        {
            if(T[m][j]<minimum)
            {
                minimum=T[m][j];
                column=j;
            }
        }
        for(i=0;i<m;i++)
        {
            if(T[i][column]>0)
            {
               minimum=T[i][n]/T[i][column];
               proceed=1;
               row=i;
               break;
            }
        }
        if(proceed==1)
        {
            for(j=i+1;j<m;j++)
            {
                if(T[j][column]>0 && (T[j][n]/T[j][column])<minimum)
                {
                    minimum=T[j][n]/T[j][column];
                    row=j;
                }
            }
            pivot=T[row][column];
            for(i=0;i<m+1;i++)
            {
                for(j=0;j<n+1;j++)
                {
                    if(i!=row && j!=column)
                    {
                        T[i][j]=((T[i][j]*pivot)-(T[i][column]*T[row][j]))/pivot;
                    }
                }
            }
            T[row][column]=1/pivot;
            for(i=0;i<m+1;i++)
            {
                if(i!=row)
                {
                    T[i][column]=(-1)*(T[i][column]/pivot);
                }
            }
             for(i=0;i<n+1;i++)
            {
                if(i!=column)
                {
                    T[row][i]=(T[row][i]/pivot);
                }
            }
            cout<< "Simplex Table "<<table<<" is "<<endl;
            for(i=0;i<m+1;i++)
            {
              for(j=0;j<n+1;j++)
              {
                cout<<T[i][j]<<"     " ;
              }
              cout<<endl;
            }
            table=table+1;
            z[column]=row;
            X[column]=0;

        }
        else
        {
        cout<< " unbounded ";
        break;
        }
    }
        else
        {
         for(i=0;i<n;i++)
         {
             if(X[i]<0)
             {
                 X[i]=0;
             }
             else
             {
                 X[i]=T[z[i]][n];
             }
         }
        }
    }
        for(i=0;i<n;i++)
        {
            cout<<"X["<<i+1<<"]="<<X[i]<<endl;
            sum=sum+C[i]*X[i];
        }
        cout<<"The maximum value of LPP is "<<sum;
        cout<<endl<<endl<<"Press 1 to test again else press 0"<<endl;
        cin>>iteration;
    }
}


