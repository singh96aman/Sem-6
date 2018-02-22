#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <cl.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCE_SIZE 100000
#define WA 3
#define HA 2
#define WB 3
#define HB 3
#define WC 3
#define HC 2
#define BLOCK_SIZE 1

int main()
{
	int size_A = WA*HA;
	int size_B = WB*HB;

	int *a = (int*) malloc(size_A*sizeof(int));
	int *b = (int*) malloc(size_B*sizeof(int));

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("kernel.cl","r");

	if(!fp)
	{
		fprintf(stderr,"Failed to load kernel\n");
		getchar();
		exit(1);
	}

	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);

	fclose(fp);
	int i;

	for(i=0; i<size_A; i++)
		scanf("%d",&a[i]);

	for(i=0; i<size_B; i++)
		scanf("%d",&b[i]);

	unsigned int size_C = WC*HC;
	int *c = (int*) malloc(size_C*sizeof(int));


	cl_platform_id pid = NULL;
	cl_device_id did = NULL;
	cl_uint dno;
	cl_uint pno;

	cl_int ret = clGetPlatformIDs(1,&pid,&pno);
	ret = clGetDeviceIDs(pid,CL_DEVICE_TYPE_CPU,1,&did,&dno);

	cl_context context = clCreateContext(NULL,1,&did,NULL,NULL,&ret);

	cl_command_queue queue = clCreateCommandQueue(context,did,NULL,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,size_A*sizeof(int),NULL,&ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,size_B*sizeof(int),NULL,&ret);
	cl_mem c_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,size_C*sizeof(int),NULL,&ret);

	ret = clEnqueueWriteBuffer(queue,a_mem_obj,CL_TRUE,0,size_A*sizeof(int),a,0,NULL,NULL);
	ret = clEnqueueWriteBuffer(queue,b_mem_obj,CL_TRUE,0,size_B*sizeof(int),b,0,NULL,NULL);

	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t *)&source_size,&ret);

	ret = clBuildProgram(program,1,&did,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"mat_mul",&ret);

	int widthA = WA;
	int widthB = WB;
	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void *)&b_mem_obj);
	ret = clSetKernelArg(kernel,2,sizeof(cl_mem),(void *)&c_mem_obj);
	ret = clSetKernelArg(kernel,3,sizeof(cl_mem),(void *)&widthA);
	ret = clSetKernelArg(kernel,4,sizeof(cl_mem),(void *)&widthB);

	size_t global_item_size[2] = {HC,WC};
	size_t local_item_size[2] = {BLOCK_SIZE,BLOCK_SIZE};

	cl_event event;
	//printf("\n aman");
	ret = clEnqueueNDRangeKernel(queue,kernel,2,NULL,&global_item_size,&local_item_size,0,NULL,NULL);

	ret = clFinish(queue);

	ret = clEnqueueReadBuffer(queue,c_mem_obj,CL_TRUE,0,size_C*sizeof(int),c,0,NULL,NULL);

	printf("\n Matrix C\n");
	for(i=0; i<size_C; i++)
	{
		printf("%d\t",c[i]);
		if(((i+1)%WC)==0)
			printf("\n");
	}

	clFlush(queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(a_mem_obj);
	clReleaseMemObject(b_mem_obj);
	clReleaseMemObject(c_mem_obj);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);

	//free(a);
	//free(b);
	return 0;
}