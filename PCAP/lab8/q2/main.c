#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <cl.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SOURCE_SIZE 10000

int main(void)
{
	int i, n, LIST_SIZE;
	printf("\n Enter N : ");
	scanf("%d",&LIST_SIZE);
	int A[100];
	printf("\nEnter Integer Array : ");
	
	for(i=0; i<LIST_SIZE; i++)
		scanf("%d",&A[i]);

	FILE *fp1, *fp2;
	char *source_str;
	size_t source_size1, source_size2;

	fp1 = fopen("odd.cl","r");
	fp2 = fopen("even.cl","r");

	if(!fp1 || !fp2){
		fprintf(stderr,"Failed to load kernel\n");
		getchar();
		exit(1);
	}
	source_str = (char *) malloc(MAX_SOURCE_SIZE);
	source_size1 = fread(source_str,1,MAX_SOURCE_SIZE, fp1);
	source_size2 = fread(source_str,1,MAX_SOURCE_SIZE, fp2);

	fclose(fp1);
	fclose(fp2);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU,1,&device_id,&ret_num_devices);

	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);

	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE*sizeof(int),NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), A, 0, NULL, NULL);

	cl_program program1 = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size1, &ret);

	cl_program program2 = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size2, &ret);


	ret = clBuildProgram(program1,1,&device_id,NULL,NULL,NULL);

	ret = clBuildProgram(program2,1,&device_id,NULL,NULL,NULL);


	cl_kernel kernel1 = clCreateKernel(program1,"odd_even",&ret);

	cl_kernel kernel2 = clCreateKernel(program2,"even_odd",&ret);

	ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem),(void *)&a_mem_obj);
	ret = clSetKernelArg(kernel2, 0, sizeof(cl_mem),(void *)&a_mem_obj);

	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;

	cl_event event;

	for(i=0; i<LIST_SIZE/2; i++)
	{
		ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), A, 0, NULL, NULL);
		ret = clEnqueueNDRangeKernel(command_queue, kernel1, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
		ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), A, 0, NULL, NULL);

		ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), A, 0, NULL, NULL);
		ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
		ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(int), A, 0, NULL, NULL);
	
	}
		ret = clFinish(command_queue);

	printf("\n Sorted Array!!\n");
	for(i=0; i<LIST_SIZE; i++)
		printf("%d ",A[i]);

	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel1);
	ret = clReleaseKernel(kernel2);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	//free(A);
	//free(RES);
	getchar();
	return 0;
}