#ifndef FUNCTION_H
#define FUNCTION_H

namespace ArraySpace{
	int *tot, *ff;
	const int xo[] = { 1, -1, 0, 0 };
	const int yo[] = { 0, 0, 1, -1 };
	int find(int a){
		if (ff[a] == a) return a;
		ff[a] = find(ff[a]);
		return ff[a];
	}
	int **newArray(int n, int m){
		int **a = new int*[n];
		for (int i = 0; i < n; i++) a[i] = new int[m]();
		return a;
	}
	void deleteArray(int** a, int n, int m){
		for (int i = n - 1; i >= 0; i--) delete[] a[i];
		delete[] a;
	}
	int inMap(int a, int b, int n, int m){
		return a >= 0 && b >= 0 && a < n&&b <m;
	}
	int inMap1(int a, int b, int n, int m){
		return a >= 1 && b >= 1 && a <= n&&b <= m;
	}
}


class Point3D{
public:
	int x, y, z;
	Point3D(int x = 0, int y = 0, int z = 0) :x(x), y(y), z(z){};
	Point3D operator + (const Point3D &B){
		return Point3D(x + B.x, y + B.y, z + B.z);
	}
	Point3D operator - (const Point3D &B){
		return Point3D(x - B.x, y - B.y, z - B.z);
	}
	void print(){
		printf("%d %d %d\n", x, y, z);
	}
};

#endif 