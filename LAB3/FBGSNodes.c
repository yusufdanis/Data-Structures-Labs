#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() {
    //int *fbArr = fb_arr();
    //int *gsArr = gs_arr();
	print_fb(create_fb(fb_arr()));
    print_gs(create_gs(gs_arr()));
}
