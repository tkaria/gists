#include "KMsgCache.h"
#include <iostream>

int 
main()
{

#ifdef SID_TEST
	strategy_id_t s1(true);
	strategy_id_t s2(true);
	s1 = s2;
	assert (s1 == s2);

	strategy_id_t s3(true);
	strategy_id_t s4(true);
	// Don't assign
	//s1 = s2;
	assert (s3 == s4);
#endif // SID_TEST

	std::cout << "sizeof(strategy_id_t): " << sizeof(strategy_id_t) << std::endl;	
	std::cout << "sizeof(order_id_t): " << sizeof(order_id_t) << std::endl;	
	std::cout << "sizeof(route_t): " << sizeof(route_t) << std::endl;	
	std::cout << "sizeof(node_t): " << sizeof(node_t) << std::endl;	
	route_t route;	
	std::cout << "sizeof(route_t.nodes): " << sizeof(route.nodes) << std::endl;	

    route_t r1;
    r1.addNode("11111111111111111", 17);
    r1.addNode("22222222222222222", 17);
    r1.addNode("33333333333333333", 17);

    route_t r2;
    r2.addNode("44444444444444444", 17);
    r2.addNode("55555555555555555", 17);
    r2.addNode("66666666666666666", 17);
	
    r2.addNode("77777777777777777", 17);
	r2.delNode();

	route_t r3;
	r3 = r2;
	assert(r3 == r2);

	route_t r4(r2);
	assert(r2 == r4);
	
}	

