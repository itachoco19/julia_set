#ifndef JULIA_MPI
#define JULIA_MPI

/*
is_divergence
double real : ジュリア集合に含まれるかを判定したい複素数の実部
double image : ジュリア集合に含まれるかを判定したい複素数の虚部
double c_real : 定数部の実部
double c_image : 定数部の虚部
*/

/*
make_julia_set
double real_start : 計算を開始したい点の実部の値
double image_start : 計算を開始したい点の虚部の値
double interval : 実部、虚部をずらしていく大きさ
int real_count : 実部をずらす回数
int image_count : 虚部をずらす回数
char* result_julia : ジュリア集合の結果を入れるchar配列、点の数だけ必要
double c_real : 定数項の実部
double c_image : 定数項の虚部
*/
void make_julia_set(double real_start, double image_start, double interval,int real_count, int image_count, char* result_julia, double c_real, double c_image);

#endif