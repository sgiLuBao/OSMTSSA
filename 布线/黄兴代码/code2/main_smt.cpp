#include"header.h"
#include"Initialize.cpp"
#include"kruscal.cpp"
#include"maketable.cpp"
#include"smt.cpp"
#include"corner_select.cpp"
#include"judge.cpp"
#include"count_length.cpp"
#include"repeat_select_corner.cpp"
#include"optimal_substructure.cpp"
#include"judge_corner.cpp"
#include"refine.cpp"
#include"print_result.cpp"
int main()
{
	srand(time(NULL));
	clock_t start1=clock();
	Initialize();
	kruscal();
    maketable();
	smt();
	repeat_select_corner();
//	print_result();
	refine();
	print_result();
    clock_t finish1=clock();
    printf("running time:%lf\n",(double)(finish1-start1)/CLOCKS_PER_SEC);
	return 0;
}
