// 01-10.set.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <set>
#include <map>
#include "kdt_set.h"

int main()
{
	{
		//			       100
		//		    50			  150
		//    20	    55
		//  19  45    51
		//    25  46
		// https://www.cs.usfca.edu/~galles/visualization/BST.html
		//			               100
		//		            50			       150
		//             20	     55
		//          19   45    51
		//             25  46
		kdt::set<int> Set;
		kdt::set<int>::iterator iter1 = Set.insert(100);
		Set.insert(150);
		Set.insert(50);
		Set.insert(20);
		Set.insert(55);
		Set.insert(45);
		kdt::set<int>::iterator iter2 = Set.insert(51);
		Set.insert(19);
		Set.insert(25);
		Set.insert(46);
		Set.print_inorder();

	
		Set.erase(iter1);
		Set.erase(iter2);

		Set.print_inorder();
	}
}