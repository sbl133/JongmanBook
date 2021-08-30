#include<iostream>
#include<vector>
using namespace std;
int n, k, length[50];
double T[50][50];
// C(x) = W*C(x-1) 에서의 W를 사용하기 위한 클래스 선언
class SquareMatrix {
	vector<vector<double>> v;
	int size;
public:
	SquareMatrix(int s) :size(s) {
		v.resize(size, vector<double>(size, 0.0));
	}
	SquareMatrix operator*(SquareMatrix x);
	double* operator[](int i);
	SquareMatrix pow(int num);
	void identity();
};
// SquareMatrix객체를 []연산으로 읽기위한 오버로딩
double* SquareMatrix::operator[](int i) { 
	return &this->v[i][0]; 
}
// 행렬곱을위한 *연산자 오버로딩
SquareMatrix SquareMatrix::operator*(SquareMatrix x) {
	SquareMatrix ret(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				ret.v[i][j] += this->v[i][k] * x.v[k][j];
	return ret;
}
// 행과 열의 크기가 size인 단위행렬 반환
void SquareMatrix::identity() {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (i == j)
				v[i][j] = 1.0;
}
// 분할정복으로 행렬곱 연산횟수 줄이기
SquareMatrix SquareMatrix::pow(int num) {
	if (num == 0) {
		SquareMatrix tmp(size);
		tmp.identity();
		return tmp;
	}
	if (num % 2 == 1) return this->pow(num - 1)* (*this);
	SquareMatrix tmp = this->pow(num / 2);
	return tmp * tmp;
}
// k분후 나올수 있는 각 음악들의 확률을 저장한 벡터반환
vector<double> getProb2() {
	SquareMatrix W(4 * n);
	// 어떤 음악이 시작했을확률 = 1분후 1분전에 어떤음악이 시작했을확률
	for (int i = 0; i < 3 * n; i++)
		W[i][i + n] = 1.0;
	// 지금 어떤 음악이 시작할 확률 == 전 음악에 재생시간만큼 전에 전 음악이 시작했을확률 * T
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			W[3 * n + i][(4 - length[j]) * n + j] = T[j][i];
	// W^k 구하기
	SquareMatrix WK = W.pow(k);
	vector<double> ret(n);
	// WK*C(0) 구하기: C(0)가(0,...,0, 1, 0,...,0)이므로 WK의 3n+1번째 열만 고려
	for (int song = 0; song < n; song++)
		for (int start = 0; start < length[song]; start++)
			ret[song] += WK[(3 - start) * n + song][3 * n];
	return ret;
}
int main() {
	cout.precision(8);
	int testcase;
	cin >> testcase;
	while (testcase--) {
		int m;
		cin >> n >> k >> m;
		for (int i = 0; i < n; i++)
			cin >> length[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> T[i][j];
		vector<double> v = getProb2();
		int likedSong;
		for (int i = 0; i < m; i++) {
			cin >> likedSong;
			cout << v[likedSong] << " ";
		}
		cout << endl;
	}
}
