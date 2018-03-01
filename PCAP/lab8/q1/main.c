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
	int i, LIST_SIZE;
	char A[100];
	printf("Enter String : ");
	scanf("%s",&A);

	LIST_SIZE = strlen(A);

	int len[100], lenindex=0;

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("kernel.cl","r");
	if(!fp){
		fprintf(stderr,"Failed to load kernel\n");
		getchar();
		exit(1);
	}
	source_str = (char *) malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE, fp);

	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU,1,&device_id,&ret_num_devices);

	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);

	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE*sizeof(char),NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, LIST_SIZE*sizeof(char), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(char), A, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);

	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"sort_vector",&ret);

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem),(void *)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem),(void *)&b_mem_obj);

	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);

	char b[LIST_SIZE];
	ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0, LIST_SIZE*sizeof(char), b, 0, NULL, NULL);

	b[LIST_SIZE]='\0';
	printf("\n Sorted Array!!\n");
	printf("%s\n",b);

	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	//free(A);
	//free(RES);
	getchar();
	return 0;
}