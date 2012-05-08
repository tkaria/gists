#include "JenkinsHash.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>


int 
main()
{

	int x = 0;
	uint32_t hv = hashlittle(&x, sizeof(x), 0);

	printf("Hash value: %d", hv);
}
