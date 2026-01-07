#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;
bool flagGk = false;
bool flagCk = false;

int inputNum(){
    int n;
    
    do{
        cout << "Nhap si so: ";
        cin >> n;
    }while(n<=0 || n>MAX);
    
    return n;
}

void nhap1Sv(int mssv[], string hoTen[], int index){
    cout << "Nhap mssv: ";
    cin >> mssv[index];
    cin.ignore();
    cout << "Nhap ho ten: ";
    getline(cin, hoTen[index]);
}

void nhapDsSv(int mssv[], string hoTen[], int siSo){
    for(int i=0; i<siSo; i++){
        nhap1Sv(mssv,hoTen,i);
    }
}

double tinhDtb(double diemGk, double diemCk);

//Toi uu them
void xuat1Sv(int mssv[], string hoTen[], double diemGk[], double diemCk[], int index){
    cout << "=============================\n";
    cout << "Nhap mssv: " << mssv[index] << endl;
    cout << "Nhap ho ten: " << hoTen[index] << endl;
    cout << "Diem GK: ";
    if (flagGk)
        cout << diemGk[index] << endl;
    else
        cout << "CHUA THI\n";
    cout << "Diem CK: ";
    if (flagCk)
        cout << diemCk[index] << endl;
    else
        cout << "CHUA THI\n";
    
    if(flagGk&&flagCk)
        cout << "Diem tong ket: " << tinhDtb(diemGk[index], diemCk[index]) << endl;
    cout << "=============================\n";
}

void xuatDsSv(int mssv[], string hoTen[], double diemGk[], double diemCk[], int siSo){
    for(int i=0; i<siSo; i++){
        xuat1Sv(mssv,hoTen,diemGk,diemCk,i);
    }
}

void nhapDiem(int mssv[], double diemGk[], const int siSo, string title="MH"){
    for(int i=0; i<siSo; i++){
        cout << "Nhap diem "<< title <<" cua SV " << mssv[i] << ": ";
        cin >> diemGk[i];
    }
}

bool min(double a, double b){
    return a<b;
}

bool max(double a, double b){
    return a>b;
}

int findExtrem(double diem[], int siSo, bool func(double, double)=min){
    int pos = 0;
    
    for(int i=1; i<siSo;i++){
        if(func(diem[i],diem[pos]))
            pos = i;
    }
    
    return pos;
}
//Nguyen mau ham
double tinhDiemBq(double diem[], const int siSo);

void xuatThongKe(double diem[], const int siSo, string title=""){
    cout << "=======THONG KE " << title << "========\n";
    cout << "====> TIM MIN <====\n";
    cout << diem[findExtrem(diem, siSo, min)] << endl;
    cout << "====> TIM MAX <====\n";
    cout << diem[findExtrem(diem, siSo, max)] << endl;
    cout << "====> DIEM BINH QUAN <====\n";
    cout << tinhDiemBq(diem, siSo) << endl;
}

double tinhDtb(double diemGk, double diemCk){
    return diemGk*0.4+diemCk*0.6;
}

int search(int mssv[], int siSo, int id){
    for(int i=0; i<siSo;i++)
        if(mssv[i]==id)
            return i;
    return -1;
}

int search(string hoTen[], int siSo, string name){
    for(int i=0; i<siSo;i++)
        if(hoTen[i]==name)
            return i;
    return -1;
}

void sort(int mssv[], string hoTen[], double diemGk[], double diemCk[], const int siSo){
    for(int i=0; i<siSo-1; i++){
        //Tim phan tu nho nhat trong doan [i, n-1]
        int pos = i;
        for(int j=i+1; j<siSo; j++){
            if(tinhDtb(diemGk[j], diemCk[j])<tinhDtb(diemGk[pos], diemCk[pos])){
                pos = j;
            }
        }
        //Hoan vi phan tu nho nhat voi phan tu dau day dang xet
        swap(mssv[i], mssv[pos]);
        swap(hoTen[i], hoTen[pos]);
        swap(diemGk[i], diemGk[pos]);
        swap(diemCk[i], diemCk[pos]);
    }
}

int main(){
    int mssv[MAX], siSo;
    string hoTen[MAX];
    double diemGk[MAX];
    double diemCk[MAX];
    
    //Thao tac nhap mang
    ///Nhap si so
    siSo = inputNum();
    ///Nhap tung SV
    nhapDsSv(mssv, hoTen, siSo);
    //Thao tac xuat mang
    xuatDsSv(mssv, hoTen, diemGk, diemCk, siSo);
    //Nhap diem GK
    cout << "====> NHAP DIEM GK <====\n";
    nhapDiem(mssv, diemGk, siSo, "GK");
    flagGk = true;
    cout << "====> NHAP DIEM CK <====\n";
    nhapDiem(mssv, diemCk, siSo);
    flagCk = true;
    xuatDsSv(mssv, hoTen, diemGk, diemCk, siSo);
    xuatThongKe(diemGk, siSo, "GK");
    xuatThongKe(diemCk, siSo);
    
    cout << "====> TIM KIEM <====\n";
    string name;
    cout << "Nhap ho ten can tim: ";
    cin.ignore();
    getline(cin, name);
    int res = search(hoTen, siSo, name);
    
    if(res!=-1)
        xuat1Sv(mssv, hoTen, diemGk, diemCk, res);
    else
        cout << "Khong tim thay!\n";
    
    cout << "====> SAP XEP <====\n";
    sort(mssv, hoTen, diemGk, diemCk, siSo);
    xuatDsSv(mssv, hoTen, diemGk, diemCk, siSo);
    return 0;
}

double tinhDiemBq(double diem[], const int siSo){
    double tong = 0;
    
    for(int i=0; i<siSo; i++){
        tong += diem[i];
    }
    
    return tong/siSo;//Can than khi chia cho 0
}
