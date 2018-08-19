#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <cl.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCE_SIZE 10000

int main()
{
	char arr[50];
	gets(arr);
	int len = strlen(arr);
	arr[len]='\0';

	FILE *fp;
	fp = fopen("kernel.cl","r");

	char *source_str;
	size_t *source_size;

	source_str = (char*) malloc(sizeof(MAX_SOURCE_SIZE));
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);

	if(!fp)
		printf("\n Error in file opening!");

	fclose(fp);

	cl_platform_id pid = NULL;
	cl_device_id did = NULL;
	cl_uint pno, dno;

	cl_int ret = clGetPlatformIDs(1,&pid,&pno);
	ret = clGetDeviceIDs(pid,CL_DEVICE_TYPE_ALL,1,&did,&dno);

	cl_context context = clCreateContext(NULL,1,&did,NULL,NULL,&ret);
	cl_command_queue queue = clCreateCommandQueue(context,did,NULL,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(char)*len,NULL,&ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(char)*len,NULL,&ret);

	ret = clEnqueueWriteBuffer(queue,a_mem_obj,CL_TRUE,0,sizeof(char)*len,arr,0,NULL,NULL);
	
	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str, (const size_t*)&source_size, &ret);
	ret = clBuildProgram(program,1,&did,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"copy",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&b_mem_obj);

	size_t global_item_size = len;
	size_t local_item_size = 1;

	char b[100];

	ret = clEnqueueNDRangeKernel(queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);

	ret = clFinish(queue);

	ret = clEnqueueReadBuffer(queue,b_mem_obj,CL_TRUE,0,sizeof(char)*len,arr,0,NULL,NULL);
	b[len]='\0';

	printf("\n%s",b);

	clReleaseKernel(kernel);
	clReleaseProgram(program);
	//clReleaseMemObject(a_mem_obj);
	//clReleaseMemObject(b_mem_obj);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);

	return 0;

	
}